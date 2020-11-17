(setq-default make-backup-files nil)
(add-to-list 'auto-mode-alist '("\\.rkt\\'" . scheme-mode))
(setq scheme-program-name "racket")

(load "~/c-quick-2.el")
(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(cq-paren-only nil)
 '(cq-whitespace nil))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
