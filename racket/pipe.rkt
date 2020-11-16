#lang racket

(require "ipc.rkt")

(define $pipe-server
  (new ::pipe-server%
       [$prefix "prefix"]
       [$client "racket.exe client.rkt"]))
(send $pipe-server get-name)
(send $pipe-server get-hpipe)
(send $pipe-server call-api "name0" (hash "a" 123 "b" 456.7))
(send $pipe-server dbg "debug メッセージ")
(send $pipe-server dbg '("abc" xyz "debug メッセージ"))

(println "end-of-server")
