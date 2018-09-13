#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <sstream>
int main(int argc, char **argv)
{
 ros::init(argc, argv, "talker");
 ros::NodeHandle n;
 while (ros::ok())
  {
	 ros::spinOnce();
       	loop_rate.sleep();

  }
return 0;
}
