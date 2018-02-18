#include "encoder.h"

#define RATE 1 /*!< Update interval [ms] */
#define WHEEL_RADIUS 32.5 /*!< Wheel radius [mm] */
#define GEAR_TRANSLATION 120 /*!< Gear translation */
#define PI 3.141

Encoder::Encoder(int nPinEncoderA, int nPinEncoderB)
{
    m_nPinEncoderA = nPinEncoderA;
    m_nPinEncoderB = nPinEncoderB;

    if(isValid(nPinEncoderA) && isValid(nPinEncoderB)) {
        pinMode(m_nPinEncoderA, INPUT);
        pinMode(m_nPinEncoderB, INPUT);
    } else {
        std::cout << "Pin configuration not valid." << std::endl;
    }

    //! Initialize QTimer thread

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
    m_nPreviousEncoderValueA = nEncoderA;
    m_nPreviousEncoderValueB = nEncoderB;
}

double Encoder::getTrueSpeed()
{
    double dTrueSpeed;

    int nCurrentTime = millis();
    int nDeltaT = nCurrentTime - m_nLastTime;

    //! Calculate detected angle change for wheel and corresponding distance
    double nAngle = m_nTicks * 30.0 / GEAR_TRANSLATION;
    double nDistance = WHEEL_RADIUS * 2.0 * PI * (nAngle / 360.0);

    //! Calculate speed from distance and time increment since last measurement
    m_dTrueSpeed = (nDistance) / (nDeltaT);

    //! Reset tick counter
    m_nTicks = 0;
    m_nLastTime = millis();
    dTrueSpeed = m_dTrueSpeed;

    return dTrueSpeed;
}
