#lang racket

(find-system-path 'run-file)
(define $path (find-system-path 'run-file))
(resolve-path $path)
(define $abs-path (path->complete-path $path))
$abs-path
(split-path $abs-path)

(define $home-dir (find-system-path 'home-dir))
$home-dir

(define prepare-dir%
  (class
   object%
   (init root-dir)
   (super-new)
   (println root-dir)
   (define %target-dir (build-path $home-dir ".software/racket-7.9-64bit"))
   (println %target-dir)
   (make-directory* %target-dir)
   (define/public (result)
     %target-dir)
   )
  )

(define $pd (new prepare-dir% [root-dir $home-dir]))
(send $pd result)

