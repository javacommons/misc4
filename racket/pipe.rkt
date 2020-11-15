#lang racket

(require gregor)

(println 'hello)
(define $now (now))
(~t $now "yyyy-MM-dd'T'HH:mm:ss.SSSSSSSSS")
$now

(require ffi/unsafe
         ffi/unsafe/define)
(require msgpack)
(require net/base64)

(define-ffi-definer define-calc (ffi-lib "calc"))

(define-calc open_pipe_server (_fun _string _string -> _int))
(define-calc read_from_pipe(_fun -> _string))
(define-calc write_to_pipe(_fun _string -> _void))
(define-calc add (_fun _int _int -> _int))
(define-calc sub (_fun _int _int -> _int))
(define-calc ref1 (_fun (ret : (_ptr o _int)) -> _void -> ret))
(define-calc ret_str (_fun -> _string))
(define-calc hello (_fun _string -> _string))

;; (define (call-api name args)
;;   (printf "api-name=~s args=~s\n" name args)
;;   (let* ([packed-args #f] [base64-args #f] [base64-result #f] [packed-result #f] [result #f])
;;     (set! packed-args (pack args))
;;     ;(printf "(A)packed-args=~s\n" packed-args)
;;     (set! base64-args (base64-encode packed-args #""))
;;     ;(printf "(B)base64-args=~s\n" (bytes->string/latin-1 base64-args))
;;     (set! base64-result (apicall name (bytes->string/latin-1 base64-args)))
;;     ;(printf "(C)base64-result=~s\n" base64-result)
;;     (set! packed-result (base64-decode (string->bytes/latin-1 base64-result)))
;;     ;(printf "(D)packed-result=~s\n" packed-result)
;;     (set! result (unpack packed-result))
;;     ;(printf "(E)result=~s\n" result)
;;     result
;;     )
;;   )

(define (encode-input name input)
  (printf "api-name=~s input=~s\n" name input)
  (let* ([args (hash "name" name "input" input)]
	 [packed-args #f]
	 [base64-args #f])
    (set! packed-args (pack args))
    (set! base64-args (base64-encode packed-args #""))
    base64-args
    )
  )

(define (decode-output base64)
  (let* ([packed-output (base64-decode base64)]
	 [output (unpack packed-output)])
    output))

(define $name (~t $now "'pipe'-yyyy-MM-dd'T'HH:mm:ss.SSSSSSSS"))

(open_pipe_server $name "client.exe")
(read_from_pipe)
;(write_to_pipe "abcハロー")
(define $base64 (encode-input "name1" '(11 22 "33")))
$base64
(write_to_pipe $base64)
(decode-output $base64)
