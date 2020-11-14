#lang racket

(require ffi/com)

(define (get-registry-env scope name)
  (let* ([wshell (com-create-instance "WScript.Shell" 'local)]
         [env (com-get-property* wshell "Environment" scope)]
         [result (com-get-property* env "Item" name)])
    (com-release wshell)
    result))

(define (set-registry-env! scope name value)
  (let* ([wshell (com-create-instance "WScript.Shell" 'local)]
         [env (com-get-property* wshell "Environment" scope)])
         (println (com-get-properties env))
         (println (com-methods env))
         (println (com-get-property-type env "Item"))
         (define item (com-get-property* env "Item" name))
         (println item)
    (com-set-property! env (list "Item" name) value)
    (com-release wshell)
    (get-registry-env scope name)))

;(get-registry-env "PROCESS" "PATH")
(get-registry-env "USER" "PATH")
(define path (get-registry-env "USER" "PATH"))
(set-registry-env! "USER" "PATH2" (format "~a;~a" path "X:\\somewhere"))
