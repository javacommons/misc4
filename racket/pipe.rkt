#lang racket

(require gregor)
(require ffi/unsafe
         ffi/unsafe/define)
(require msgpack)
(require net/base64)

(require "ipc.rkt")

(define $now (now))
(define $name (~t $now "'pipe'-yyyy-MM-dd'T'HH:mm:ss.SSSSSSSS"))

(define $hPipe (::open-pipe-server $name "client.exe"))
(::call-thru-pipe $hPipe "name1" '(11 22 "33"))
