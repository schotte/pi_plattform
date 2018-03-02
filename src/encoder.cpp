#include "pi_plattform/encoder.h"


#define PI 3.141

Encoder::Encoder(int nPinEncoderA, int nPinEncoderB, float gearratio, float wheelradius)
{
    m_nPinEncoderA = nPinEncoderA;
    m_nPinEncoderB = nPinEncoderB;

    gearRatio = gearratio;
    wheelRadius = wheelradius;
    
    pinMode(m_nPinEncoderA, INPUT);
    pinMode(m_nPinEncoderB, INPUT);
   
	m_nTicks=0;

}

Encoder::~Encoder()
{
}

void Encoder::readEncoder()
{
    int nEncoderA = digitalRead(m_nPinEncoderA);
    int nEncoderB = digitalRead(m_nPinEncoderB);
    int nTicks = 0;

    //! Check if encoder value has changed and count ticks
    //! Encoder thread has to run fast enough so we don't miss a value change
    if(nEncoderA != m_nPreviousEncoderValueA) {
        nTicks++;
    }
    if(nEncoderB != m_nPreviousEncoderValueB) {
        nTicks++;
    }
    if(nTicks == 0) {
        return;
    }

    m_nTicks+= nTicks;
	//printf("Ticks: %d\n", m_nTicks);
    m_nPreviousEncoderValueA = nEncoderA;
    m_nPreviousEncoderValueB = nEncoderB;
}

double Encoder::getTrueSpeed()
{
    double dTrueSpeed;

    ros::Time currentTime = ros::Time::now();
    ros::Duration nDeltaT = currentTime - m_nLastTime;

    //! Calculate detected angle change for wheel and corresponding distance
    double nAngle = m_nTicks / gearRatio ;
    double nDistance = wheelRadius * 2.0 * PI * (nAngle);

    //! Calculate speed from distance and time increment since last measurement
    m_dTrueSpeed = (nDistance) / (nDeltaT.nsec) * pow(10,9);

    //! Reset tick counter
    m_nTicks = 0;
    m_nLastTime = ros::Time::now();
    dTrueSpeed = m_dTrueSpeed;

    return dTrueSpeed;
}
