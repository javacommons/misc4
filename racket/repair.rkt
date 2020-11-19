#lang racket

(require "zip-install.rkt")

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

#;(define set-path%
  (class
   object% (super-new)
   (init :member)
   (define %member (if (path? :member) (path->string :member) :member))
   (println %member)
   (set! %member (string-replace %member "/" "\\"))
   (println %member)
   (define %path (get-registry-env "USER" "PATH"))
   (println %path)
   (define %path-list (string-split %path ";"))
   (println %path-list)
   (set! %path-list (cons %member %path-list))
   (set! %path-list (remove-duplicates %path-list equal?))
   (println %path-list)
   (set! %path (string-join %path-list ";"))
   (println %path)
   (set-registry-env! "USER" "PATH" %path)
   )
  )
