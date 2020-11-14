#lang racket

(require ffi/unsafe
         ffi/unsafe/define)
(require json)
(require msgpack)
(require net/base64)

;(define (dbg msg) (println msg))
(define (dbg msg) #f)

(define-ffi-definer define-calc (ffi-lib "calc"))

(define-calc add (_fun _int _int -> _int))
(define-calc sub (_fun _int _int -> _int))
(define-calc ref1 (_fun (ret : (_ptr o _int)) -> _void -> ret))
(define-calc ret_str (_fun -> _string))
(define-calc hello (_fun _string -> _string))

(add 11 33)
(add 11 22)
(sub 11 22)
(ref1)
(ret_str)
(hello "bobボブ©")
(jsexpr->string '[11 22 33])
(hello (jsexpr->string '[11 "あいう" 33]))
(string->jsexpr "{\"a\": 123}")
(hasheq 'a 123 'b 456)
(jsexpr->string (hasheq 'a 123 'b 456))

(define p1 (pack "Hello world!"))
p1
(unpack p1)

(define p2 (pack (hash "a" 123.45 "b" 456.78 "c" '[1 2 3])))
p2
(unpack p2)

(define b2 (base64-encode p2 #""))
b2
(unpack (base64-decode b2))

(define input (read))
(set! input '777)
;(print input)
