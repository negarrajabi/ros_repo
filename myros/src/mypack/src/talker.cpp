/*opyright (C) 2008, Morgan Quigley and Willow Garage, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
// %Tag(FULLTEXT)%
// %Tag(ROS_HEADER)%
#include "ros/ros.h"
// %EndTag(ROS_HEADER)%
// %Tag(MSG_HEADER)%
#include "std_msgs/String.h"
// %EndTag(MSG_HEADER)%

#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"										// to get desired position command
#include "turtlesim/Pose.h"												// to read current position
#include "geometry_msgs/Twist.h"
	#include <sstream>
void CurPoseCallback(const turtlesim::Pose::ConstPtr& msg);
void CurVelCallback(const geometry_msgs::Twist::ConstPtr& velmsg);
  geometry_msgs::Twist curVel;
  turtlesim::Pose CurPose;


/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
// %Tag(INIT)%
  ros::init(argc, argv, "talker");
// %EndTag(INIT)%

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
// %Tag(NODEHANDLE)%
  ros::NodeHandle n;
// %EndTag(NODEHANDLE)%


  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */
// %Tag(PUBLISHER)%
ros::Publisher turtle_vel =
    n.advertise<turtlesim::Pose>("turtle1/pose", 10);
ros::Publisher vel_pub=
	n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",10);
//ros::Publisher posPub=n.advertise<turtlesim::Pose>("/turtle1/pose",10); 

  
// %EndTag(PUBLISHER)%

// %Tag(LOOP_RATE)%
  ros::Rate loop_rate(20);
//ros::Subscriber CurPose_sub = n.subscribe("/turtle1/cmd_vel",10, CurPoseCallback);


// %EndTag(LOOP_RATE)%

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
// %Tag(ROS_OK)%
//ros::Subscriber CurPose_sub = n.subscribe("/turtle1/pose", 5, CurPoseCallback);

  int count = 0;
ros::Subscriber CurVel_sub = n.subscribe("/turtle1/cmd_vel",10, CurVelCallback);

//ros::Subscriber CurPose_sub = n.subscribe("/turtle1/pose",10, CurPoseCallback);

  while (ros::ok())
  {
//turtlesim::Pose CurPose;
// %EndTag(ROS_OK)%
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
// %Tag(FILL_MESSAGE)%
   

    
//ros::Subscriber CurVel_sub = n.subscribe("/turtle1/cmd_vel",10, CurVelCallback);

ros::Subscriber CurPose_sub = n.subscribe("/turtle1/pose",10, CurPoseCallback);

    //msg.linear.x = 1;



	
//ROS_INFO("Ready to send position commands");	

//ros::Subscriber CurPose_sub = n.subscribe("/turtle1/pose", 5, CurPoseCallback);

// %Tag(ROSCONSOLE)%
    
// %EndTag(ROSCONSOLE)%

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
// %Tag(PUBLISH)%
//    turtle_vel.publish(msg);
curVel.linear.x=0;
turtle_vel.publish(CurPose);
vel_pub.publish(curVel);
// %EndTag(PUBLISH)%

// %Tag(SPINONCE)%
    ros::spinOnce();
// %EndTag(SPINONCE)%

// %Tag(RATE_SLEEP)%
    loop_rate.sleep();
// %EndTag(RATE_SLEEP)%
    ++count;
  }


  return 0;
}
void CurPoseCallback(const turtlesim::Pose::ConstPtr& msg)			
{
	CurPose.x = msg->x;
	CurPose.y=msg->y;
	//CurPose.angular.z = msg->angular.z;
std_msgs::String msgs;
        std::stringstream ss;
    ss << "hello world "<<CurPose.x<<"   "<<CurPose.y;
msgs.data = ss.str();

    ROS_INFO("%s", msgs.data.c_str());
											// copy msg to varible to use elsewhere
	return;
}
void CurVelCallback(const geometry_msgs::Twist::ConstPtr& velmsg){
curVel.linear.x=velmsg->linear.x;
std_msgs::String msgs2;
        std::stringstream ss2;
    ss2 << "cur vel*******   "<<curVel.linear.x;
msgs2.data = ss2.str();

    ROS_INFO("%s", msgs2.data.c_str());
//ROS_INFO("ON FUNCTION");
return;
}


// %EndTag(FULLTEXT)%

