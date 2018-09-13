#include "ros/ros.h"
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"
#include <geometry_msgs/Twist.h>
geometry_msgs::Twist msg;

void chatterCallback(const geometry_msgs::Twist::ConstPtr& CurPose)
{
           std_msgs::String msgs;
           std::stringstream ss;
       	   ss << "hello world "<<CurPose->linear.x;<<"     "<<CurPose->angular.z;
           msgs.data = ss.str(); 
           ROS_INFO("%s", msgs.data.c_str());
	   msg.linear.x = CurPose->linear.x;
           msg.angular.z = CurPose->angular.z;


return;		 	
}


int main(int argc, char **argv)
{

        ros::init(argc, argv, "listener");
        ros::NodeHandle n;
        ros::Rate loop_rate(10);
        ros::Publisher turtle_vel = n.advertise<geometry_msgs::Twist>("turtle2/	cmd_vel", 5);
        ros::Subscriber sub = n.subscribe("turtle1/cmd_vel", 5, chatterCallback)

while (ros::ok())
        {

	 turtle_vel.publish(msg);
	 ros::spinOnce();
         loop_rate.sleep();
        }

	return 0;
}



