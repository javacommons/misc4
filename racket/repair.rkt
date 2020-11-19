#lang racket

(require "zip-install.rkt")

(get-registry-env "USER" "xyz")

(define $path (get-registry-env "USER" "PATH"))
$path

(define $path-list (string-split $path ";"))
$path-list

(define (is-msys64 %x)
  (regexp-match? (regexp "\\\\msys64\\\\") %x))

(define (not-msys64 %x) (not (is-msys64 %x)))

(is-msys64 "C:\\Users\\user\\.software\\msys64\\mingw64\\bin")

(filter is-msys64 $path-list)
(filter not-msys64 $path-list)

(require ffi/com)

(delete-registry-env "USER" "MSYSTEM_CARCH")
