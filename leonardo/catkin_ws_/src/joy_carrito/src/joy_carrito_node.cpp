#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
//Constante para la velocidad lineal maxima del robot
#define linear_scale 0.6
//Constante para la velocidad angular maxima del robot
#define angular_scale 5
ros::Publisher speeds_pub;
using namespace std;
//Velocidad lineal
float x;
//Velocidad angular
float w;
void joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
 //Posiciones recibidas del nodo joy_node
 x = joy->axes[1];
 w = joy->axes[0];
 ROS_INFO("x: [%f] w: [%f]", x , 10*w );
 geometry_msgs::Twist twist;
 //Asigna los valores de las velocidades
 twist.linear.x = linear_scale * x;
 twist.angular.z = angular_scale * w;
 speeds_pub.publish(twist);
}
int main(int argc, char **argv)
{
 cout<<"Starting joy_carrito_node..."<<endl;
 ros::init(argc, argv, "joy_carrito_node");
 ros::NodeHandle n;
 ros::Rate loop_rate(30);
 //Se suscribe al topico joy del nodo joy_node
 ros::Subscriber joy_sub = n.subscribe("joy", 1, joyCallback);
 //Publica al nodo mobile_base_node para mover al robot
 speeds_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);

 //Mensaje tipo Twist para enviar solo velocidades lineales y angulares
 geometry_msgs::Twist twist_msg;
 while(ros::ok())
 {
 loop_rate.sleep();
 ros::spinOnce();
 }
 return 0;
}
