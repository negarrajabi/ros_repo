#include "ros/ros.h"
#include <math.h>
#include "std_msgs/String.h"
#include "turtlesim/Pose.h" 
#include <geometry_msgs/Twist.h>

turtlesim::Pose msg;
turtlesim::Pose msg2;
geometry_msgs::Twist vel1;
geometry_msgs::Twist vel_msg;
double param,result;
void chatterCallback(const turtlesim::Pose::ConstPtr& CurPose)
{
	
	std_msgs::String msgs;
	std::stringstream ss;
	ss << "hello world "<<CurPose->x<<"     "<<CurPose->y;
	msgs.data = ss.str();
	ROS_INFO("%s", msgs.data.c_str());
         
         msg.x = CurPose->x;
	 
	msg.y=CurPose->y;
return;

               

 	
}
void velCallback(const geometry_msgs::Twist::ConstPtr& velPtr)
{
vel1.linear.x=velPtr->linear.x;
vel1.angular.z=velPtr->angular.z;
}
void secCurPose(const turtlesim::Pose::ConstPtr& secCurPose)


{
        
	vel_msg.angular.z=0;
	vel_msg.linear.x=0;	
double param,result;
 	msg2.x=secCurPose->x;
	msg2.y=secCurPose->y;
	msg2.theta=secCurPose->theta;
	param=(msg.y-msg2.y)/(msg.x-msg2.x);
if(msg.x>msg2.x && msg.y>msg2.y){
result= atan(param);}
else if(msg.x<msg2.x && msg.y>msg2.y){
result= 3.1415+atan(param);}
else if(msg.x<msg2.x && msg.y<msg2.y){
result= 3.1415+atan(param);}
else if(msg.x>msg2.x && msg.y<msg2.y){
result= 6.2831+atan(param);}



	
std_msgs::String msgs;
	std::stringstream ss;	
 ss << "theta "<<result<< "turtle2  "<<msg2.theta<<"***second   "<<msg2.x<<"    "<<msg2.y;
   msgs.data = ss.str();
	
        ROS_INFO("%s", msgs.data.c_str());


// new
double test;
test=result-msg2.theta;
if (test>0.1 ){
vel_msg.angular.z=2;
ROS_INFO("on first if");

}

if (test<-0.1 ){
vel_msg.angular.z=-2;
ROS_INFO("on first if");

}

double testx,testy;
testx=msg.x-msg2.x;
testy=msg.y-msg2.y;
if(vel_msg.angular.z == 0){
if(testx>0.2 && testy>0.2){
vel_msg.linear.x=2;
}
if(testx<-0.2 && testy>0.2){
vel_msg.linear.x=2;
}
if(testx<-0.2 && testy<-0.2){
vel_msg.linear.x=2;
}
if(testx>0.2 && testy<-0.2){
vel_msg.linear.x=2;
}

}

result=0;
param=0;
	
return;
}

int main(int argc, char **argv)
{
       
	ros::init(argc, argv, "listener");
	ros::NodeHandle n;
	ros::Rate loop_rate(20);
	ros::Publisher velocity_publisher = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
        ros::Publisher turtle_vel = n.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 5);
        ros::Subscriber sub = n.subscribe("turtle1/pose", 5, chatterCallback);   
   	ros::Publisher turtle2_pub=n.advertise<turtlesim::Pose>("turtle2/pose",5);       
	ros::Subscriber turtle2_sub=n.subscribe("turtle2/pose",5,secCurPose);
	ros::Subscriber vel1_sub=n.subscribe("turtle1/cmd_vel",10,velCallback);
	while (ros::ok())
	{


	turtle2_pub.publish(msg2);
 turtle_vel.publish(vel_msg);
	
		
		ros::spinOnce();

		loop_rate.sleep();
	}
	return 0;
}

