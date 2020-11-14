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
(define-calc apicall (_fun _string/latin-1 _string/latin-1 -> _string/latin-1))

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

;(define input (read))
;(set! input '777)
;(print input)

(define (call-api name args)
  (printf "api-name=~s args=~s\n" name args)
  (let* ([packed-args #f] [base64-args #f] [base64-result #f] [packed-result #f] [result #f])
    (set! packed-args (pack args))
    (printf "(A)packed-args=~s\n" packed-args)
    (set! base64-args (base64-encode packed-args #""))
    (printf "(B)base64-args=~s\n" (bytes->string/latin-1 base64-args))
    (set! base64-result (apicall name (bytes->string/latin-1 base64-args)))
    (printf "(C)base64-result=~s\n" base64-result)
    (set! packed-result (base64-decode (string->bytes/latin-1 base64-result)))
    (printf "(D)packed-result=~s\n" packed-result)
    (set! result (unpack packed-result))
    (printf "(E)result=~s\n" result)
    result
    )
  )

(define api-input (hash "a" 11.11 "b" 22.22))
api-input

(call-api "api1" api-input)
(println "bofore sum")
(call-api "sum" '[11 99 33])
(println "after sum")
