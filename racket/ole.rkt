#lang racket

(require ffi/com)

(define (get-registry-env scope name)
  (let* ([wshell (com-create-instance "WScript.Shell" 'local)]
         [env (com-get-property* wshell "Environment" scope)]
         [result (com-get-property env (list "Item" name))])
    (com-release wshell)
    result))

(define (set-registry-env! scope name value)
  (let* ([wshell (com-create-instance "WScript.Shell" 'local)]
         [env (com-get-property* wshell "Environment" scope)])
    (com-set-property! env (list "Item" name) value)
    (com-release wshell)
    (get-registry-env scope name)))

(get-registry-env "USER" "PATH")
(define path (get-registry-env "USER" "PATH"))
(set-registry-env! "USER" "PATH2" (format "~a;~a" path "X:\\somewhere"))

#|
    function createShorcut2(used, dir, name, icon, target, args) {
      var scPath = dir + "\\" + name + ".lnk";
      if (!used) {
        deleteFile(scPath);
        return;
      }
      var shell = new ActiveXObject("WScript.Shell");
      var sc = shell.CreateShortcut(scPath);
      sc.IconLocation = icon;
      sc.TargetPath = target;
      sc.Arguments = args;
      sc.WorkingDirectory = "";
      sc.Save();
    }
|#

(define $wshell (com-create-instance "WScript.Shell" 'local))
$wshell
