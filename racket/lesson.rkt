#lang racket

; https://learnxinyminutes.com/docs/racket/

#| Block comments
   can span multiple lines and...
    #|
       they can be nested!
    |#
|#

#; (this expression is discarded)

(println "hello")

18446744073709551615
18446744073709551615777

#;(error "my-error")

(/ 1 3) ; => 1/3
(exact->inexact 1/3) ; => 0.3333333333333333
(+ 1+2i  2-3i) ; => 3-1i

;; Strings can be added too!
(string-append "Hello " "world!") ; => "Hello world!"

;; A string can be treated like a list of characters
(string-ref "Apple" 0) ; => #\A

;; format can be used to format strings:
(format "~a can be ~a" "strings" "formatted")

;; Printing is pretty easy
(printf "I'm Racket. Nice to meet you!\n")

;; You can also use unicode characters
(define ⊆ subset?)
(⊆ (set 3 2) (set 1 2 3)) ; => #t

(define rectangle%
  (class
   object% (super-new)
   (init :width :height)
   (define %width :width)
   (define %height :height)
   (define/public (:get-width) %width)
   (define/public (:set-width n) (set! %width n))
   (define/public (:area) (* %width %height))
   )
  )

(define $rect (new rectangle% [:width 15] [:height 20]))
(send $rect :get-width)
(send $rect :area)
(send $rect :set-width 5)
(send $rect :area)
