#lang racket

(require gregor)
(require ffi/unsafe
         ffi/unsafe/define)
(require msgpack)
(require net/base64)

(require "ipc.rkt")

(define ::pipe-server%
  (class
   object%
   (super-new)
   (init $prefix $client [$debug 0])
   (println (list $prefix $client $debug))
   (define $now (now))
   (define $name (format "~a-~a" $prefix (~t $now "yyyy-MM-dd'T'HH:mm:ss.SSSSSSSS")))
   (define/public (get-name) $name)
   (define $hpipe (::open-pipe-server $name $client $debug))
   (define/public (get-hpipe) $hpipe)
   (define/public (call-api $api $value) (::call-thru-pipe $hpipe $api $value))
   )
  )

(define $pipe-server (new ::pipe-server% [$prefix "prefix"] [$client "racket.exe client.rkt"]))
(send $pipe-server get-name)
(send $pipe-server get-hpipe)
(send $pipe-server call-api "name0" (hash "a" 123 "b" 456.7))

(define $now (now))
(define $name (~t $now "'pipe'-yyyy-MM-dd'T'HH:mm:ss.SSSSSSSS"))

;(define $hPipe (::open-pipe-server $name "client.exe" 1))
(define $hPipe (::open-pipe-server $name "racket.exe client.rkt" 1))
;(define $hPipe (::open-pipe-server $name "racket.exe client.rkt" 0))
(::call-thru-pipe $hPipe "name1" '(11 22 "33"))

(println "end-of-server")
