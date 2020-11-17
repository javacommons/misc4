#lang racket

(define (fib n)
  (if (< n 2)
    n
    (+ (fib (- n 2)) (fib (- n 1)))))

;(write (fib 38))
(write (fib 45))
(newline)