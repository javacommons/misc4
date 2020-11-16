#lang racket

(require gregor)
(require ffi/unsafe
         ffi/unsafe/define)
(require msgpack)
(require net/base64)

(define-ffi-definer define-calc (ffi-lib "calc"))
(define-calc open_pipe_server (_fun _string _string _int -> _ullong))
(define-calc open_pipe_client (_fun _string -> _ullong))
(define-calc read_from_pipe(_fun _ullong -> _string))
(define-calc write_to_pipe(_fun _ullong _string -> _void))

(define (encode-input $name $value)
  (let* ([$input (hash "name" $name "value" $value)]
	 [$packed-input (pack $input)]
	 [$base64-input (base64-encode $packed-input #"")])
    $base64-input))

(define (decode-output $base64)
  (let* ([$packed-output (base64-decode $base64)]
	 [$output (unpack $packed-output)])
    $output))

(define (decode-input $base64)
  (let* ([$packed-input (base64-decode $base64)]
	 [$input (unpack $packed-input)])
    $input))

(define (encode-output $output)
  (let* ([$packed-output (pack $output)]
	 [$base64-output (base64-encode $packed-output)])
    $base64-output))

(define (::open-pipe-server $name $client $show-client)
  (open_pipe_server $name $client $show-client))

(define (::open-pipe-client $name)
  (open_pipe_client $name))

(define (::call-thru-pipe $hPipe $name $value)
  (write_to_pipe $hPipe (encode-input $name $value))
  (decode-output (string->bytes/latin-1 (read_from_pipe $hPipe))))

(define (::receive-input-thru-pipe $hPipe)
  (let* ([$base64 (read_from_pipe $hPipe)])
    (decode-input (string->bytes/latin-1 $base64))))

(define (::return-output-thru-pipe $hPipe $value)
  (write_to_pipe $hPipe (encode-output $value))
  )

(provide
 ::open-pipe-server
 ::open-pipe-client
 ::call-thru-pipe
 ::receive-input-thru-pipe
 ::return-output-thru-pipe)
