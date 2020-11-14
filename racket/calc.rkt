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
(define-calc apicall (_fun _string _string -> _string))

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
  (let* ([packed-args (pack args)]
	 [base64-args (base64-encode packed-args #"")]
	 [base64-result (apicall name base64-args)]
	 [packed-result (base64-decode (string->bytes/latin-1 base64-result))]
	 [result (unpack packed-result)]
	 )
;    (printf "packed-args=~s\n" packed-args)
;    (printf "base64-args=~s\n" base64-args)
;    (printf "base64-result=~s\n" base64-result)
;    (printf "packed-result=~s\n" packed-result)
;    (printf "result=~s\n" result)
    result
    )
  )

(define p3 (pack '[11 77 33]))
(printf "p3=~s\n" p3)
(define b3 (base64-encode p3 #""))
(printf "b3=~s\n" b3)
(define r3 (apicall "sum" b3))

(define api-input (hash "a" 11.11 "b" 22.22))
api-input

(call-api "api1" api-input)
(println "bofore sum")
(call-api "sum" '[11 99 33])
(println "after sum")
