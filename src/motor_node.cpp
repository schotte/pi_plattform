/*
 * motor_nodelet.cpp
 *
 *  Created on: Feb 17, 2018
 *      Author: schotte
 */

#include "ros/ros.h"
#include "pi_plattform/motor.h"
#include "std_msgs/Int8.h"
#include "wiringPi.h"

Motor* m;

void callback(std_msgs::Int8 msg){
	if(msg.data==0) {
		m->stop();
	}else if(msg.data>0) {
		m->forward();
	}else if(msg.data<0) {
		m->backward();
	}
	m->setSpeed(msg.data);
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "motor");
	ros::NodeHandle n("~");
	wiringPiSetup();

	int pinA, pinB, pinPWM;
	if (!n.getParam("pinA", pinA)) {
		ROS_WARN("No Pin supplied(A)");
		return 1;
	}
	if (!n.getParam("pinB", pinB)) {
		ROS_WARN("No Pin supplied(B)");
		return 1;
	}
	if (!n.getParam("pinPWM", pinPWM)) {
		ROS_WARN("No Pin supplied(PWM)");
		return 1;
	}
	


	m=new Motor(pinA,pinB,pinPWM);

	ros::Subscriber sub = n.subscribe("cmd", 1, callback);

	ros::spin();

}
