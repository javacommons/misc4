#lang racket

(require gregor)
(require ffi/unsafe
         ffi/unsafe/define)
(require msgpack)
(require net/base64)

(require "ipc.rkt")

(printf "Given arguments: ~s\n"
        (current-command-line-arguments))

;(define $hPipe (::open-pipe-server $name "client.exe"))
;(::call-thru-pipe $hPipe "name1" '(11 22 "33"))

(vector? (current-command-line-arguments))
