/*
 * encoder_node.cpp
 *
 *  Created on: Feb 17, 2018
 *      Author: schotte
 */
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "pi_plattform/encoder.h"
#include "wiringPi.h"

ros::Publisher pub;
Encoder *e;

void timerCallback(const ros::TimerEvent& te) {
	std_msgs::Float32 msg;
	msg.data = e->getTrueSpeed();
	pub.publish(msg);
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "encoder");
	ros::NodeHandle n("~");
	wiringPiSetup();

	int pinA, pinB;
	if (!n.getParam("pinA", pinA)) {
		ROS_WARN("No Pin supplied(A)");
		return 1;
	}
	if (!n.getParam("pinB", pinB)) {
		ROS_WARN("No Pin supplied(B)");
		return 1;
	}
	float wheel, gear;
	if (!n.getParam("gearRatio", gear)) {
		ROS_WARN("No Pin supplied(A)");
		return 1;
	}
	if (!n.getParam("wheelRadius", wheel)) {
		ROS_WARN("No Pin supplied(B)");
		return 1;
	}

	ROS_INFO("A: %d, B:%d", pinA, pinB);
	ros::Rate loop_rate(1000);
	e = new Encoder(pinA, pinB, gear, wheel);
	ROS_INFO("Encoder are setup");
	pub = n.advertise<std_msgs::Float32>("vel", 1);
	ros::Timer timer = n.createTimer(ros::Duration(0.1), timerCallback);

	while (ros::ok()) {

		e->readEncoder();

		ros::spinOnce();
		loop_rate.sleep();
	}

}

