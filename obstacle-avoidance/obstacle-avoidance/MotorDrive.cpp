#include "MotorDrive.h"

MotorDrive::MotorDrive(int ena,
                            int enb,
                            int pin1,
                            int pin2,
                            int pin3,
                            int pin4)
{
  m_ENA = ena;
  m_ENB = enb;
  m_IN1 = pin1;
  m_IN2 = pin2;
  m_IN3 = pin3;
  m_IN4 = pin4;
}
void MotorDrive::foward(int speed)
{
  analogWrite(m_ENA, speed);//Set the speed of ENA
  analogWrite(m_ENB, speed);//Set the speed of ENB
    //The right forward
  digitalWrite(m_IN1, HIGH);
  digitalWrite(m_IN2, LOW);
  //The left forward
  digitalWrite(m_IN3, HIGH);
  digitalWrite(m_IN4, LOW);
}

void MotorDrive::back(int speed)
{
  analogWrite(m_ENA, speed);//Set the speed of ENA
  analogWrite(m_ENB, speed);//Set the speed of ENB
  //The rihgt back
  digitalWrite(m_IN1, LOW);
  digitalWrite(m_IN2, HIGH);
  //The left back
  digitalWrite(m_IN3, LOW);
  digitalWrite(m_IN4, HIGH);
}

void MotorDrive::left(int speed, int angle)
{

}

void MotorDrive::right(int speed, int angle)
{

}