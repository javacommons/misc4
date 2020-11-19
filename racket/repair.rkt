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

(define (delete-registry-env %scope %name)
  (let* ([%wshell (com-create-instance "WScript.Shell" 'local)]
         [%env (com-get-property* %wshell "Environment" %scope)]
         [%tem1 (println(com-methods %env))]
         [%result (com-get-property %env (list "Item" %name))])
    (if (equal? "" %result) (void) (com-invoke %env "Remove" %name))
    (com-release %wshell)
    %result))

(delete-registry-env "USER" "MSYSTEM_CARCH")
