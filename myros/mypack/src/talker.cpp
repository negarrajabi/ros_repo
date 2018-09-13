#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <sstream>
  void CurPoseCallback(const geometry_msgs::Twist::ConstPtr& msg); //for sending velocity of turtle1
  geometry_msgs::Twist CurPose;//current vel of turtle1

int main(int argc, char **argv)
{
 ros::init(argc, argv, "talker");
 ros::NodeHandle n;
 ros::Publisher turtle_vel =
    n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 10);
 ros::Rate loop_rate(5);

 while (ros::ok())
  {
	ros::Subscriber CurPose_sub =
             n.subscribe("/turtle1/cmd_vel",10, CurPoseCallback);
        turtle_vel.publish(CurPose);

        ros::spinOnce();
       	loop_rate.sleep();

  }
return 0;
}
  void CurPoseCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
        CurPose.linear.x = msg->linear.x;

        CurPose.angular.z = msg->angular.z;
        return;
}
