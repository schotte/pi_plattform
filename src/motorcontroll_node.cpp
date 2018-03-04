/*
 * motorcontroll_node.cpp
 *
 *  Created on: Feb 20, 2018
 *      Author: schotte
 */

#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float32.h"

#define KP 200

float targetspeed;
int pwm;
ros::Publisher motor_pub;

void controllSpeed(float currentspeed) {
	if(targetspeed <= 0.01 && targetspeed >= -0.01) {
		pwm = 0;
	} else {
		float difference = targetspeed - currentspeed;
		pwm += (int)(KP * difference);
	}
	std_msgs::Int16 msg;
	msg.data = pwm;
	motor_pub.publish(msg);
}

void callbackEncoder(std_msgs::Float32 msg) {
	controllSpeed(msg.data);
}

void callbackTargetspeed(std_msgs::Float32 msg) {
	targetspeed = msg.data;
}

int main(int argc, char **argv) {
	targetspeed=0.0;
	ros::init(argc, argv, "motorcontroller");
	ros::NodeHandle n("~");
	std::string side;
	if (!n.getParam("side", side)) {
		ROS_WARN("No side choosen (right or left)");
		return 1;
	}

	std::string pub_topic = std::string("/motor_") + side + std::string("/pwm");
	motor_pub = n.advertise<std_msgs::Int16>(pub_topic, 1);

	std::string vel_topic = std::string("/") + side + std::string("_encoder/vel");
	std::string targetspeed_topic = std::string("/motor_") + side + std::string("/targetvel");

	ros::Subscriber vel_sub = n.subscribe(vel_topic, 1, callbackEncoder);
	ros::Subscriber targetspeed_sub = n.subscribe(targetspeed_topic, 1, callbackTargetspeed);

	ROS_INFO("%s\n%s\n%s\n", pub_topic.c_str(), vel_topic.c_str(), targetspeed_topic.c_str());

	ros::spin();

}
