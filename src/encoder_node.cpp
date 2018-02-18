/*
 * encoder_node.cpp
 *
 *  Created on: Feb 17, 2018
 *      Author: schotte
 */
#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "pi_plattform/encoder.h"
#include "wiringPi.h

ros::Publisher pub;
Encoder *e;

void timerCallback() {
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

	ros::Rate loop_rate(1000);
	e = new Encoder(pinA,pinB);

	pub = n.advertise<std_msgs::Float32>("vel", 1);
	ros::Timer timer = n.createTimer(ros::Duration(0.05), timerCallback);

	while(ros::ok()) {

		e->readEncoder();

		ros::spinOnce();
		loop_rate.sleep();
	}

}

