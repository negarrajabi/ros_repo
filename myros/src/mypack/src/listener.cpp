#include "ros/ros.h"
#include "std_msgs/String.h"
#include "turtlesim/Pose.h"


void chatterCallback(const turtlesim::Pose::ConstPtr& CurPose)
{


//         ROS_INFO("I heard: [%s]", msg->data.c_str());
//         ROS_INFO(CurPose->x);
           std_msgs::String msgs;
           std::stringstream ss;
       	   ss << "hello world "<<CurPose->x;<<"     "<<CurPose->y;
           msgs.data = ss.str(); 
           ROS_INFO("%s", msgs.data.c_str());
		 	
}


int main(int argc, char **argv)
{

        ros::init(argc, argv, "listener");
        ros::NodeHandle n;
        ros::Rate loop_rate(10);
        ros::Publisher turtle = n.advertise<turtlesim::Pose>("turtle2/pose", 5);
        ros::Subscriber sub = n.subscribe("turtle/pose", 10, chatterCallback);

}
