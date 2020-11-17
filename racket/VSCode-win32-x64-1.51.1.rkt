#lang racket

(require "zip-install.rkt")

(define $home-dir (find-system-path 'home-dir))
$home-dir

(define $pd (new prepare-dir%
		 [:root-dir $home-dir]
		 ;[:zip-path "racket-7.9-64bit.zip"]
		 [:zip-base "VSCode-win32-x64-1.51.1"]
     ))

(define $target-dir (send $pd result))
$target-dir

(define $bin-dir (build-path $target-dir "bin"))

(new set-path% [:member $bin-dir])
