#ifndef MOTOR_H
#define MOTOR_H

#include <wiringPi.h>
#include <softPwm.h>

#define MAXSPEED 200
#define PWMCONVERSION 1

class Motor
{
public:
    Motor(int pinA, int pinB, int pinPWM);
    ~Motor();


    int setSpeed(double speed);
    int forward();
    int backward();
    int stop();

    void spin();

private:
    int speed;
    unsigned int m_nPinMotorForward, m_nPinMotorBackward, m_nPinMotorPWM;
    int pwmcounter;
};

#endif // MOTOR_H
