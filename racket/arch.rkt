#lang racket

(require "arch-api.rkt")

(printf "Given arguments: ~s\n"
        (current-command-line-arguments))

(define api-input (hash "a" 11.11 "b" 22.22))
api-input

(arch-api "api1" api-input)
(println "bofore sum")
(arch-api "sum" '[11 99 33])
(println "after sum")
(arch-api* "sum" 1 2 33)
(arch-api* "none" 1 "abc" 33)
					;(arch-api "sum" "dummy")

(find-system-path 'run-file)
