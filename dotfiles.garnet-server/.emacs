;; .emacs

;; -------------------------------------------- basic emacs setting

(setq load-path (cons "~/lisp" load-path))
;;(setq load-path (cons "/usr/local/share/gtags" load-path))

(setq default-frame-alist
	(cons '(vertical-scroll-bars . nil)
 	 (cons '(menu-bar-lines . 0)
	  (cons '(tool-bar-lines . 0)
	    default-frame-alist))))

(setq inhibit-startup-message t)        ; �������Ȼ��Υ�å�����������
(setq line-number-mode t)               ; �Կ���ɽ��
(setq column-number-mode t)             ; ������ֹ��ɽ��
(setq scroll-step 1)			; ����������Կ�
(setq-default tab-width 8)		; TAB��
(setq compile-command "make ")		; M-x compile ���ޥ��
(setq-default truncate-lines t)		; ���ޤ��֤�
(setq delete-auto-save-files t)		; ��λ���˥����ȥ����֥ե������ä�
;;(display-time)			; �⡼�ɥ饤��˻���ɽ��
(which-function-mode 1)			; ���ߤδؿ�̾��⡼�ɥ饤���ɽ��
(setq truncate-partial-width-windows nil)

;;; �ǥե���Ȥ�ʸ��������
(set-default-coding-systems 'euc-jp-unix)
(setq-default buffer-file-coding-system 'euc-jp-unix)

;;; ������ɤǿ�ʬ������
(global-font-lock-mode t)

;;; �꡼������ϥ��饤�Ȥ���
(transient-mark-mode t)

;;; ��ԤŤĥ��������� �� �̾�Хåե���
(setq scroll-conservatively 35
	  scroll-margin 0
	  scroll-step 1)
;;; ��ԤŤĥ��������� �� shell �Хåե���
(setq comint-scroll-show-maximum-output t)

;;; kill-ring�򻲾� -- browse-kill-ring
;;  ���� my-pcl-cvs-patch �Υ��顼��ʤ������������Ƴ��
;;;;(require 'browse-kill-ring)

;;; pcl-cvs����
;;  pserver �ϳƼ��δĶ��˹�碌�����ꤷ�Ʋ�������
(setq cvs-cvsroot ":pserver:USER@10.69.95.194:/usr/local/cvsroot");; �� ���Խ�
;; ʸ�������к��ѥå� �� ��������٥ե��������� cvs ci -F ����
;;;(eval-after-load "pcvs"
;;;  '(progn (load "my-pcl-cvs-patch")
;;;		  (setq my-cvs-do-commit-logfile-coding-system 'euc-japan-unix)))
(modify-coding-system-alist 'process "cvs" '(undecided . euc-jp-unix))
;; log �ϤɤΥ����ɤǽ񤯤����� �� ����ʸ���������뤿�������к�ɬ��
(modify-coding-system-alist 'process "cvs" '(undecided . euc-jp-unix))

(autoload 'diff-mode "diff-mode" "Diff major mode" t)
(add-to-list 'auto-mode-alist '("\\.\\(diffs?\\|patch\\|rej\\)\\'" . diff-mode))

;;; ediff ���˥ߥ˥�����ɥ���Ф��ʤ�
(setq ediff-window-setup-function 'ediff-setup-windows-plain)

;;; �Хåե����ꥹ��ɽ������ʬ�䤷�ʤ�
(global-set-key "\C-x\C-b" 'buffer-menu)

;; -------------------------------------------- ���ֹ�
;;(require 'wb-line-number)
;;(wb-line-number-enable)
(set-scroll-bar-mode nil)                 ; no scroll bar, even in x-window system

;(defun lnon ()
;  (interactive)
;  (wb-line-number-enable))
;(defun lnoff ()
;  (interactive)
;  (wb-line-number-disable))

;;(lnon)

;; -------------------------------------------- backup file
(setq make-backup-files t)	; backup file ���
(setq vc-make-backup-files t)
;(setq version-control t)
;(setq trim-versions-without-asking t)

(defun make-backup-file-name (filename)
  (expand-file-name
    (concat "~/emacs-backup/" (file-name-nondirectory filename) "~")
    (file-name-directory filename)))


;; -------------------------------------------- CC-mode / GTAGS
;;;(setq load-path (cons "/usr/local/share/gtags" load-path))

(autoload 'c++-mode "cc-mode" "C++ Editing Mode" t)
(autoload 'c-mode   "cc-mode" "C Editing Mode" t)
(setq auto-mode-alist
      (append '(("\\.C$"  . c++-mode)
                ("\\.cc$" . c++-mode)
                ("\\.cpp$" . c++-mode)
                ("\\.hpp$" . c++-mode)
                ("\\.c$"  . c++-mode)
                ("\\.h$"  . c++-mode)
                ("\\.hh$"  . c++-mode)
                ) auto-mode-alist))


;cc-mode �Υ������ޥ���
(autoload 'gtags-mode "gtags" "" t)
(add-hook 'c-mode-common-hook
	'(lambda ()
	  (turn-on-font-lock)			; 
	  (c-set-style "gnu")
;	  (c-set-style "bsd")
;          (c-set-style "k&r")
;          (c-set-style "linux")
;	  (setq c-basic-offset 2)
;	  (setq tab-width 8)
	  (setq c-basic-offset 4)
	  (setq tab-width 4)
	  (setq c-auto-newline nil)	; ��ư����
	  (gtags-mode 1)		; GTAGS
	  (gtags-make-complete-list)
	  (local-set-key "\M-t" 'gtags-find-tag)
          (local-set-key "\M-r" 'gtags-find-rtag)
	  (local-set-key "\M-s" 'gtags-find-symbol)
	  (local-set-key "\M-p" 'gtags-find-pattern)
	  ;;(local-set-key "\M-f" 'gtags-find-file)    ;�ե�����˥�����
          (local-set-key "\C-t" 'gtags-pop-stack)
	  (setq comment-start "// ") ; //�����Υ�����
	  (setq comment-end "")
	  ))

(defun bsd ()
	(interactive)
	 (set-c-style "BSD")
	 )
(defun gnu ()
	(interactive)
	 (set-c-style "GNU")
	 )
(defun c++ ()
	(interactive)
	 (set-c-style "C++")
	 )
(defun k&r ()
	(interactive)
	 (set-c-style "C++")
	 )

; GTAGS ���������ޥ��
(defun gtags ()
	"create gtags file."
	(interactive)
	(load "gtags")
	(shell-command "gtags >/dev/null")
	(gtags-make-complete-list)
	)

;;gtags mode �λȤ���
;; M-t:�ؿ���������ذ�ư
;; M-r:�ؿ��򻲾ȸ��ΰ�����ɽ����RET �ǻ��ȸ��إ����פǤ���
;; M-s:�ѿ���������Ȼ��ȸ��ΰ�����ɽ����RET �ǳ����ս�إ����פǤ��롥
;; C-t:���ΥХåե������ 
;; gtags-find-pattern:��Ϣ�ե����뤫��θ�����
;; gtags-find-tag-from-here:����������֤δؿ�����ذ�ư�� 

;; GDB setting
;;(defvar gud-gdb-history (list "mn10300-linux-gdb --annotate=1 apl_dispsrv.out"))
;;(defvar gud-gdb-history (list "/opt/montavista/pro/devkit/arm/v5t_le/bin/arm_v5t_le-gdb --annotate=1 drawtool"))
;;;(defvar gud-gdb-history (list "/usr/local/mips-4.3/bin/mips-linux-gnu-gdb --annotate=1 drawtool"))
(defvar gud-gdb-history (list "/opt/redhat/arm-2010q1/bin/arm-none-linux-gnueabi-gdb --annotate=1 "))
;;(defvar gud-gdb-history (list "/home/hirai/sigma/131002_lfbc70/sdk4.2.1rc4/cs_rootfs_1.3.0/host/bin/mipsel-linux-gdb --annotate=1 drawtool"))
					; M-x gdb �Υǥե���ȥ��ޥ�ɥ饤��

;; -------------------------------------------- key bind

(define-key global-map [f1]  'start-kbd-macro)		; F1
(define-key global-map [f2]  'end-kbd-macro)            ; F2
(define-key global-map [f3]  'call-last-kbd-macro)      ; F3
(define-key global-map [f4]  'goto-line)		; F4

(define-key global-map [f5]  'tabbar-mode)      	; F5
(define-key global-map [f6]  'tabbar-backward)          ; F6
(define-key global-map [f7]  'tabbar-forward)		; F7
(define-key global-map [f8]  'yank)                     ; F8

(define-key global-map [f9]  'compile)                  ; F9
(define-key global-map [f10] 'next-error)               ; F10
(define-key global-map [f11] 'query-replace)            ; F11
(define-key global-map [f12] 'replace-string)           ; F12

(define-key global-map "\C-z" 'undo)			; UNDO
(define-key global-map [home] 'other-window)		; HOME
(define-key global-map [insert] 'ignore)		; disable INSERT

;; -------------------------------------------- MISC macro

(defun tab4 ()
	(interactive)
	(message "set tab width '4'")
	(setq tab-stop-list
	      '(4 8 12 16 20 24 28 32 36 40 44 48 52 56 60 64 68 72 76))
	(setq-default tab-width 4))
(defun tab3 ()
	(interactive)
	(message "set tab width '4'")
	(setq tab-stop-list
	      '(3 6 9 12 15 18 21 24 27 30 33 36 39 42 45 48 51 54 57))
	(setq-default tab-width 4)
	(setq c-basic-offset 3)
)

(defun tab8 ()
	(interactive)
	(message "set tab width '8'")
	(setq tab-stop-list
	      '(8 16 24 32 40 48 56 64 72 80 88 96 104 112 120 128 136 144))
	(setq-default tab-width 8))

(defun tmp ()
	(interactive)
	(switch-to-buffer "*tmp*"))

(defun euc ()
	(interactive)
	(set-buffer-file-coding-system (quote euc-japan-unix) nil))

(defun jis ()
	(interactive)
	(set-buffer-file-coding-system (quote junet-unix) nil))

(defun sjis ()
	(interactive)
	(set-buffer-file-coding-system (quote shift_jis-dos) nil))

(defun utf8 ()
	(interactive)
	(set-buffer-file-coding-system (quote utf-8) nil))


;; ===========================================================================

;;; uncomment this line to disable loading of "default.el" at startup
;; (setq inhibit-default-init t)

;; turn on font-lock mode
(global-font-lock-mode t)

;; enable visual feedback on selections
(setq transient-mark-mode t)

;; GDB setting
(defvar gud-gdb-history (list "arm_v5t_le-gdb "))
;;(defvar gud-gdb-history (list "mn10300-linux-gdb --annotate=1 apl_dispsrv.out"))
; M-x gdb 

;; �����ܤ�����
(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(column-number-mode t)
 '(tool-bar-mode nil)
 '(transient-mark-mode nil))
;; ��������
(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(default ((t (:inherit nil :stipple nil :background "#143A81" :foreground "white" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 79 :width normal :foundry "unknown" :family "DejaVu Sans Mono")))))
;;; '(default ((t (:inherit nil :stipple nil :background "#143A81" :foreground "white" :inverse-video nil :box nil :strike-through nil :overline nil :underline nil :slant normal :weight normal :height 79 :width normal :foundry "unknown" :family "DejaVu Sans Mono")))))