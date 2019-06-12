
(cl:in-package :asdf)

(defsystem "simple_move-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "SimpleMove" :depends-on ("_package_SimpleMove"))
    (:file "_package_SimpleMove" :depends-on ("_package"))
  ))