#lang racket

(find-system-path 'run-file)
(define $path (find-system-path 'run-file))
(resolve-path $path)
(define $abs-path (path->complete-path $path))
$abs-path
(split-path $abs-path)

(define $home-dir (find-system-path 'home-dir))
$home-dir

(find-system-path 'pref-dir)
(define $sendto-dir (build-path $home-dir "AppData\\Roaming\\Microsoft\\Windows\\SendTo"))
$sendto-dir

(directory-list $sendto-dir #:build? #t)
(directory-list $sendto-dir #:build? #f)
