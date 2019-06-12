; Auto-generated. Do not edit!


(cl:in-package simple_move-srv)


;//! \htmlinclude SimpleMove-request.msg.html

(cl:defclass <SimpleMove-request> (roslisp-msg-protocol:ros-message)
  ((distance
    :reader distance
    :initarg :distance
    :type cl:float
    :initform 0.0)
   (angle
    :reader angle
    :initarg :angle
    :type cl:float
    :initform 0.0))
)

(cl:defclass SimpleMove-request (<SimpleMove-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SimpleMove-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SimpleMove-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name simple_move-srv:<SimpleMove-request> is deprecated: use simple_move-srv:SimpleMove-request instead.")))

(cl:ensure-generic-function 'distance-val :lambda-list '(m))
(cl:defmethod distance-val ((m <SimpleMove-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader simple_move-srv:distance-val is deprecated.  Use simple_move-srv:distance instead.")
  (distance m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <SimpleMove-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader simple_move-srv:angle-val is deprecated.  Use simple_move-srv:angle instead.")
  (angle m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SimpleMove-request>) ostream)
  "Serializes a message object of type '<SimpleMove-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'distance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SimpleMove-request>) istream)
  "Deserializes a message object of type '<SimpleMove-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'distance) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SimpleMove-request>)))
  "Returns string type for a service object of type '<SimpleMove-request>"
  "simple_move/SimpleMoveRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SimpleMove-request)))
  "Returns string type for a service object of type 'SimpleMove-request"
  "simple_move/SimpleMoveRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SimpleMove-request>)))
  "Returns md5sum for a message object of type '<SimpleMove-request>"
  "ec24e737ddaa2f1769f4aa74f864401d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SimpleMove-request)))
  "Returns md5sum for a message object of type 'SimpleMove-request"
  "ec24e737ddaa2f1769f4aa74f864401d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SimpleMove-request>)))
  "Returns full string definition for message of type '<SimpleMove-request>"
  (cl:format cl:nil "float32 distance~%float32 angle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SimpleMove-request)))
  "Returns full string definition for message of type 'SimpleMove-request"
  (cl:format cl:nil "float32 distance~%float32 angle~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SimpleMove-request>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SimpleMove-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SimpleMove-request
    (cl:cons ':distance (distance msg))
    (cl:cons ':angle (angle msg))
))
;//! \htmlinclude SimpleMove-response.msg.html

(cl:defclass <SimpleMove-response> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass SimpleMove-response (<SimpleMove-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SimpleMove-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SimpleMove-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name simple_move-srv:<SimpleMove-response> is deprecated: use simple_move-srv:SimpleMove-response instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SimpleMove-response>) ostream)
  "Serializes a message object of type '<SimpleMove-response>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SimpleMove-response>) istream)
  "Deserializes a message object of type '<SimpleMove-response>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SimpleMove-response>)))
  "Returns string type for a service object of type '<SimpleMove-response>"
  "simple_move/SimpleMoveResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SimpleMove-response)))
  "Returns string type for a service object of type 'SimpleMove-response"
  "simple_move/SimpleMoveResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SimpleMove-response>)))
  "Returns md5sum for a message object of type '<SimpleMove-response>"
  "ec24e737ddaa2f1769f4aa74f864401d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SimpleMove-response)))
  "Returns md5sum for a message object of type 'SimpleMove-response"
  "ec24e737ddaa2f1769f4aa74f864401d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SimpleMove-response>)))
  "Returns full string definition for message of type '<SimpleMove-response>"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SimpleMove-response)))
  "Returns full string definition for message of type 'SimpleMove-response"
  (cl:format cl:nil "~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SimpleMove-response>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SimpleMove-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SimpleMove-response
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SimpleMove)))
  'SimpleMove-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SimpleMove)))
  'SimpleMove-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SimpleMove)))
  "Returns string type for a service object of type '<SimpleMove>"
  "simple_move/SimpleMove")