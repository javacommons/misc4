#lang racket

(require racket/gui)
;(require racket/gui/event)

; Make a frame by instantiating the frame% class
(define frame (new frame%
                   [label "Example"]
                   [width 800]
                   [height 600]
                   ))

(define list-box (new list-box%
                      (label "List Box")
                      (parent frame)
                      (choices (list "Item 0"
                                     "Item 1"
                                     "Item 2"))
                      (style (list 'single
                                   'column-headers))
                      (columns (list "First Column"))
                      [callback (lambda (button event)
                                  (println (send event get-event-type))
                                  (send msg set-label "Listbox click"))]
                      ))
 
; Make a static text message in the frame
(define msg (new message% [parent frame]
                 [label "No events so far..."]))
 
; Make a button in the frame
(define btn (new button% [parent frame]
                 [label "Click Me"]
                 ; Callback procedure for a button click:
                 [callback (lambda (button event)
                             (println (send event get-event-type))
                             (send msg set-label "Button click"))]))
 
; Show the frame by calling its show method
(send frame show #t)
