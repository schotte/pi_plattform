#include "pi_plattform/motor.h"

Motor::Motor(int pinForward, int pinBackward, int pinPWM)
    :m_nPinMotorForward(pinForward),
      m_nPinMotorBackward(pinBackward),
      m_nPinMotorPWM(pinPWM)
{
    pinMode(m_nPinMotorForward,OUTPUT);
    pinMode(m_nPinMotorBackward,OUTPUT);
    pinMode(m_nPinMotorPWM,OUTPUT);
    softPwmCreate(m_nPinMotorPWM, 0, 255);
    stop();
	speed=0;
}

int Motor::backward()
{
    softPwmWrite(m_nPinMotorPWM, speed);
    digitalWrite(m_nPinMotorBackward, 1);
    digitalWrite(m_nPinMotorForward, 0);
	return 0;
}

int Motor::forward()
{
    softPwmWrite(m_nPinMotorPWM, speed);
    digitalWrite(m_nPinMotorForward, 1);
    digitalWrite(m_nPinMotorBackward, 0);
	return 0;
}
int Motor::stop() {
    digitalWrite(m_nPinMotorForward, 0);
    digitalWrite(m_nPinMotorBackward, 0);
	return 0;
}

int Motor::setSpeed(double value){
	
    if(value<MAXSPEED) {
        speed = (int)(value/PWMCONVERSION);
    } else {
        speed = MAXSPEED;
    }
	return 0;
}
