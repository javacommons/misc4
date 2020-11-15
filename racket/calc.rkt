#lang racket

(require ffi/unsafe
         ffi/unsafe/define)
(require json)
;(require msgpack)
;(require net/base64)

(require "call-api.rkt")

(printf "Given arguments: ~s\n"
        (current-command-line-arguments))

(define-ffi-definer define-calc (ffi-lib "calc"))

(define-calc add (_fun _int _int -> _int))
(define-calc sub (_fun _int _int -> _int))
(define-calc ref1 (_fun (ret : (_ptr o _int)) -> _void -> ret))
(define-calc ret_str (_fun -> _string))
(define-calc hello (_fun _string -> _string))
;(define-calc apicall (_fun _string/latin-1 _string/latin-1 -> _string/latin-1))

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

;(define input (read))
;(set! input '777)
;(print input)

(define api-input (hash "a" 11.11 "b" 22.22))
api-input

(call-api "api1" api-input)
(println "bofore sum")
(call-api "sum" '[11 99 33])
(println "after sum")
(call-api* "sum" 1 2 33)
(call-api* "none" 1 "abc" 33)
					;(call-api "sum" "dummy")

(find-system-path 'run-file)
