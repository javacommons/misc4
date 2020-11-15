#lang racket

(require gregor)
(require ffi/unsafe
         ffi/unsafe/define)
(require msgpack)
(require net/base64)

(define-ffi-definer define-calc (ffi-lib "calc"))
(define-calc open_pipe_server (_fun _string _string -> _ullong))
(define-calc read_from_pipe(_fun _ullong -> _string))
(define-calc write_to_pipe(_fun _ullong _string -> _void))
(define-calc ret_addr(_fun -> _ullong))

;unsigned long long ret_addr()


(define (encode-input $name $value)
  (let* ([$input (hash "name" $name "value" $value)]
	 [$packed-input (pack $input)]
	 [$base64-input (base64-encode $packed-input #"")])
    $base64-input))

(define (decode-output $base64)
  (let* ([$packed-output (base64-decode $base64)]
	 [$output (unpack $packed-output)])
    $output))

(define $now (now))
(define $name (~t $now "'pipe'-yyyy-MM-dd'T'HH:mm:ss.SSSSSSSS"))

(define (::open-pipe-server $client)
  (let* ([$now (now)]
	 [$name (~t $now "'pipe'-yyyy-MM-dd'T'HH:mm:ss.SSSSSSSS")])
    (open_pipe_server $name $client)))

(define (::call-thru-pipe $hPipe $name $value)
  (write_to_pipe $hPipe (encode-input $name $value))
  (decode-output (string->bytes/latin-1 (read_from_pipe $hPipe))))

(define $hPipe (::open-pipe-server "client.exe"))
(::call-thru-pipe $hPipe "name1" '(11 22 "33"))

(ret_addr)

(provide ::open-pipe-server ::call-thru-pipe)
