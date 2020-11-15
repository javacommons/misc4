#lang racket

(require gregor)

(println 'hello)
(define $now (now))
(~t $now "yyyy-MM-dd'T'HH:mm:ss.SSSSSSSSS")
$now

(require ffi/unsafe
         ffi/unsafe/define)

(define-ffi-definer define-calc (ffi-lib "calc"))

(define-calc open_pipe_server (_fun _string _string -> _int))
(define-calc read_from_pipe(_fun -> _string))
(define-calc write_to_pipe(_fun _string -> _void))
(define-calc add (_fun _int _int -> _int))
(define-calc sub (_fun _int _int -> _int))
(define-calc ref1 (_fun (ret : (_ptr o _int)) -> _void -> ret))
(define-calc ret_str (_fun -> _string))
(define-calc hello (_fun _string -> _string))

(define $name (~t $now "yyyy-MM-dd'T'HH:mm:ss.SSSSSSSS"))

(open_pipe_server $name "client.exe")
(read_from_pipe)
(write_to_pipe "abcハロー")
