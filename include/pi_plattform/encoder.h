#ifndef ENCODER_H
#define ENCODER_H

#include <wiringPi.h>
#include <iostream>
#include <vector>

/*!
 * \file Encoder.h
 * \author Matthias Jakob & Philipp Knake : Team 8
 * \date 04.06.2016
 * \brief Encoder implementation to estimate motor speed.
 *
 * Encoder impements reading from a hardware encoder and calculating
 * the corresponding speed from it.
 *
 */
class Encoder
{

public:
    //! Constructor
    /*!
      \param nPinEncoderA GPIO
      \param nPinEncoderB GPIO
    */
    Encoder(int nPinEncoderA, int nPinEncoderB);

    ~Encoder();

    //! Returns current true speed from Encoder.
    /*!
     * \return Current true speed from Encoder [m/s].
     */
    double getTrueSpeed();

    //! Reading pin and store encoder ticks.
    void readEncoder();


private:
    int m_nPinEncoderA;
    int m_nPinEncoderB;
    int m_nTicks;
    double m_dTrueSpeed;

    int m_nPreviousEncoderValueA;
    int m_nPreviousEncoderValueB;
    int m_nLastTime; //! Milliseconds

};

#endif // ENCODER_H
