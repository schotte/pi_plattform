#ifndef MOTOR_H
#define MOTOR_H

#include <wiringPi.h>

#define MAXSPEED 200

class Motor
{
public:
    Motor(int pinA, int pinB);
    ~Motor();


    int setSpeed(double speed);
    int forward();
    int backward();
    int stop();

private:
    int speed;
    unsigned int m_nPinMotorForward, m_nPinMotorBackward, m_nPinMotorPWM;
};

#endif // MOTOR_H
