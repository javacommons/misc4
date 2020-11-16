#lang racket

(require gregor)
(require ffi/unsafe
         ffi/unsafe/define)
(require msgpack)
(require net/base64)

(require "ipc.rkt")

(printf "Given arguments: ~s\n"
        (current-command-line-arguments))

;(::call-thru-pipe $hPipe "name1" '(11 22 "33"))

(define $args (current-command-line-arguments))
(vector? $args)
(vector-ref $args 0)
(define $name (vector-ref $args 0))

(define $hPipe (::open-pipe-client $name))
$hPipe
(::receive-input-thru-pipe $hPipe)
(::return-output-thru-pipe $hPipe '("output1" 1 2 3))
(::receive-input-thru-pipe $hPipe)
(::return-output-thru-pipe $hPipe '("output2" 1 2 3))
(println "end-of-client")
