#lang racket

(require ffi/unsafe
         ffi/unsafe/define)
(require json)
(require msgpack)
(require net/base64)
 
(define-ffi-definer define-calc (ffi-lib "calc"))

(define-calc add (_fun _int _int -> _int))
(define-calc sub (_fun _int _int -> _int))
(define-calc ref1 (_fun (ret : (_ptr o _int)) -> _void -> ret))
(define-calc ret_str (_fun -> _string))
(define-calc hello (_fun _string -> _string))

(println (add 11 22))
(println (sub 11 22))
(println (ref1))
(println (ret_str))
(println (hello "bobボブ"))
(println (jsexpr->string '[11 22 33]))
(println (hello (jsexpr->string '[11 "あいう" 33])))
(println (string->jsexpr "{\"a\": 123}"))
(println (hasheq 'a 123 'b 456))
(println (jsexpr->string (hasheq 'a 123 'b 456)))

(define p1 (pack "Hello world!"))
(println p1)
(println (unpack p1))

(define p2 (pack (hash "a" 123.45 "b" 456.78 "c" '[1 2 3])))
(println p2)
(println (unpack p2))

(define b2 (base64-encode p2 #""))
(println b2)
(println (unpack (base64-decode b2)))
