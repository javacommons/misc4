#lang racket

(require gregor)

(println 'hello)
(define $now (now))
(~t $now "yyyy-MM-dd'T'HH:mm:ss.SSSSSSSSS")
$now
