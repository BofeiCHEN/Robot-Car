#ifndef MOTORDRIVE_H
#define MOTORDRIVE_H
#include <Arduino.h>

class MotorDrive
{
public:
    MotorDrive(int ena,
               int enb,
               int pin1,
               int pin2,
               int pin3,
               int pin4);
    void foward(int speed);
    void back(int speed);

private:
    int m_ENA;
    int m_ENB;
    int m_IN1;
    int m_IN2;
    int m_IN3;
    int m_IN4;
};

#endif