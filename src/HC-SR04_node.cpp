/*
 * HC-SR04_node.cpp
 *
 *  Created on: Mar 4, 2018
 *      Author: schotte
 */

#include "ros/ros.h"
#include "sensor_msgs/Range.h"
#include "wiringPi.h"
#include "HC-SR04-Raspberry-Pi-C-/libSonar.h"

int main(int argc, char **argv) {

	ros::init(argc, argv, "motor");
	ros::NodeHandle n("~");
	wiringPiSetup();

	int pinEcho, pinTrig;
	if (!n.getParam("pinEcho", pinEcho)) {
		ROS_WARN("No Pin supplied(A)");
		return 1;
	}
	if (!n.getParam("pinTrig", pinTrig)) {
		ROS_WARN("No Pin supplied(B)");
		return 1;
	}

	ros::Rate loop_rate(25);

	ros::Publisher pub = n.advertise<sensor_msgs::Range>("range", 1);

	Sonar sonar;
	sonar.init(pinTrig, pinEcho);
	sensor_msgs::Range msg;
	msg.header.frame_id = "somethign";
	msg.radiation_type=0;
	msg.min_range = 0.002;
	msg.max_range = 0.450;
	msg.field_of_view = 0.261799;

	while(ros::ok()) {
		msg.range = sonar.distance(30000);
		msg.header.stamp = ros::Time::now();
		pub.publish(msg);
		ros::spinOnce();
		loop_rate.sleep();
	}


}
