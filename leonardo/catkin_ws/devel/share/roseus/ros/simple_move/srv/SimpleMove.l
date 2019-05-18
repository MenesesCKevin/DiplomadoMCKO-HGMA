;; Auto-generated. Do not edit!


(when (boundp 'simple_move::SimpleMove)
  (if (not (find-package "SIMPLE_MOVE"))
    (make-package "SIMPLE_MOVE"))
  (shadow 'SimpleMove (find-package "SIMPLE_MOVE")))
(unless (find-package "SIMPLE_MOVE::SIMPLEMOVE")
  (make-package "SIMPLE_MOVE::SIMPLEMOVE"))
(unless (find-package "SIMPLE_MOVE::SIMPLEMOVEREQUEST")
  (make-package "SIMPLE_MOVE::SIMPLEMOVEREQUEST"))
(unless (find-package "SIMPLE_MOVE::SIMPLEMOVERESPONSE")
  (make-package "SIMPLE_MOVE::SIMPLEMOVERESPONSE"))

(in-package "ROS")





(defclass simple_move::SimpleMoveRequest
  :super ros::object
  :slots (_distance _angle ))

(defmethod simple_move::SimpleMoveRequest
  (:init
   (&key
    ((:distance __distance) 0.0)
    ((:angle __angle) 0.0)
    )
   (send-super :init)
   (setq _distance (float __distance))
   (setq _angle (float __angle))
   self)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:angle
   (&optional __angle)
   (if __angle (setq _angle __angle)) _angle)
  (:serialization-length
   ()
   (+
    ;; float32 _distance
    4
    ;; float32 _angle
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _distance
       (sys::poke _distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _angle
       (sys::poke _angle (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _distance
     (setq _distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _angle
     (setq _angle (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass simple_move::SimpleMoveResponse
  :super ros::object
  :slots ())

(defmethod simple_move::SimpleMoveResponse
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass simple_move::SimpleMove
  :super ros::object
  :slots ())

(setf (get simple_move::SimpleMove :md5sum-) "ec24e737ddaa2f1769f4aa74f864401d")
(setf (get simple_move::SimpleMove :datatype-) "simple_move/SimpleMove")
(setf (get simple_move::SimpleMove :request) simple_move::SimpleMoveRequest)
(setf (get simple_move::SimpleMove :response) simple_move::SimpleMoveResponse)

(defmethod simple_move::SimpleMoveRequest
  (:response () (instance simple_move::SimpleMoveResponse :init)))

(setf (get simple_move::SimpleMoveRequest :md5sum-) "ec24e737ddaa2f1769f4aa74f864401d")
(setf (get simple_move::SimpleMoveRequest :datatype-) "simple_move/SimpleMoveRequest")
(setf (get simple_move::SimpleMoveRequest :definition-)
      "float32 distance
float32 angle
---

")

(setf (get simple_move::SimpleMoveResponse :md5sum-) "ec24e737ddaa2f1769f4aa74f864401d")
(setf (get simple_move::SimpleMoveResponse :datatype-) "simple_move/SimpleMoveResponse")
(setf (get simple_move::SimpleMoveResponse :definition-)
      "float32 distance
float32 angle
---

")



(provide :simple_move/SimpleMove "ec24e737ddaa2f1769f4aa74f864401d")


