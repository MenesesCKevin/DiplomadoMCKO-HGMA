//Cabeceras para ros
#include <ros/ros.h>
//Cabeceras para mensajes estandar
#include <std_msgs/Int64.h>
#include <std_msgs/Float32.h>
//Cabeceras para el estado de los joints
#include <sensor_msgs/JointState.h>
//Cabeceras para realizar las transformaciones
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

tf::TransformListener * tf_listener;

void callbackEncoder1(const std_msgs::Int64::ConstPtr &msg){
	std::cout << msg->data << std::endl;
}

void callbackEncoder2(const std_msgs::Int64::ConstPtr &msg){
	std::cout << msg->data << std::endl;
}

void publishOdom(float roboX, float robotY, float robotT){
	
}

int main(int argc, char ** argv){
	//Inicializacion del nodo
	ros::init(argc, argv, "mobile_base_node");
	ros::NodeHandle nh;
	ros::Rate rate(30);

	ros::Subscriber subEncoder1 = nh.subscribe("/encoder_1", 1, callbackEncoder1);
	ros::Subscriber subEncoder2 = nh.subscribe("/encoder_2", 1, callbackEncoder2);

	ros::Publisher pubJointState = nh.advertise<sensor_msgs::JointState>("joint_states", 1);

    	tf_listener = new tf::TransformListener();

    	std::string jointNames[2] = {"left_wheel_joint_connect", "right_wheel_joint_connect"};
    	float jointPositions[2] = {0.0,0.0};
    	sensor_msgs::JointState jointState;
    	jointState.name.insert(jointState.name.begin(), jointNames, jointNames +2);
    	jointState.position.insert(jointState.position.begin(), jointPositions, jointPositions + 2);

    	while(ros::ok()){
	    //El objeto que envia las transformaciones
	    tf::TransformBroadcaster br;
	    //Transformaciones
	    tf::Transform transform;
	    //Se calcula la odometria
	    transform.setOrigin(tf::Vector3(0.0,0.0,0.0));
	    tf::Quaternion q;
	    q.setRPY(0,0,0);
	    transform.setRotation(q);
	    //Se envia la transformacion
	    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "base_link", "odom"));
	    //Se publica el estado de los joints
	    pubJointState.publish(jointState);
	    rate.sleep();
	    ros::spinOnce();
	}
}
