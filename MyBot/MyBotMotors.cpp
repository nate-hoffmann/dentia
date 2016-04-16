
#include "MyBot.h"
#include "Arduino.h"



MyBotMotors::MyBotMotors(void)
{}

void MyBotMotors::Drive(int dir,int spee)
{
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    Adafruit_DCMotor *motorBR = AFMS.getMotor(1);
    Adafruit_DCMotor *motorBL = AFMS.getMotor(2);
    Adafruit_DCMotor *motorFL = AFMS.getMotor(3);
    Adafruit_DCMotor *motorFR = AFMS.getMotor(4);

    motorFL->setSpeed(spee);
    motorFR->setSpeed(spee);
    motorBL->setSpeed(spee);
    motorBR->setSpeed(spee);
 
    // FWD for dir = 1, BCKWD for dir = 0
    // Potentiall include an if loop for if the input speed is too slow to give motor 6V
    if (dir == 1) 
    {
        motorFL->run(FORWARD);
        motorFR->run(FORWARD);
        motorBL->run(FORWARD);
        motorBR->run(FORWARD);
    } else 
    {
        motorFL->run(BACKWARD);
        motorFR->run(BACKWARD);
        motorBL->run(BACKWARD);
        motorBR->run(BACKWARD);
    }
}

void MyBotMotors::Pivot(int dir,int spee)
{
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    Adafruit_DCMotor *motorBR = AFMS.getMotor(1);
    Adafruit_DCMotor *motorBL = AFMS.getMotor(2);
    Adafruit_DCMotor *motorFL = AFMS.getMotor(3);
    Adafruit_DCMotor *motorFR = AFMS.getMotor(4);

    motorFL->setSpeed(spee);
    motorFR->setSpeed(spee);
    motorBL->setSpeed(spee);
    motorBR->setSpeed(spee);

    //CW for dir = 1, CCW for dir = 0
    if (dir == 1)
    {
        motorFL->run(FORWARD);
        motorFR->run(BACKWARD);
        motorBL->run(FORWARD);
        motorBR->run(BACKWARD);
    } else
    {
        motorFL->run(BACKWARD);
        motorFR->run(FORWARD);
        motorBL->run(BACKWARD);
        motorBR->run(FORWARD);
    }
}

void MyBotMotors::Slide(int dir,int spee)
{
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    Adafruit_DCMotor *motorBR = AFMS.getMotor(1);
    Adafruit_DCMotor *motorBL = AFMS.getMotor(2);
    Adafruit_DCMotor *motorFL = AFMS.getMotor(3);
    Adafruit_DCMotor *motorFR = AFMS.getMotor(4);

    motorFL->setSpeed(spee);
    motorFR->setSpeed(spee);
    motorBL->setSpeed(spee);
    motorBR->setSpeed(spee);

    //Right for dir = 1, Left for dir = 0
    if (dir == 1)
    {
        motorFL->run(BACKWARD);
        motorFR->run(FORWARD);
        motorBL->run(FORWARD);
        motorBR->run(BACKWARD);
    }
    else
    {
        motorFL->run(FORWARD);
        motorFR->run(BACKWARD);
        motorBL->run(BACKWARD);
        motorBR->run(FORWARD);
    }
}

void MyBotMotors::Turn(int dir)
{
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    Adafruit_DCMotor *motorBR = AFMS.getMotor(1);
    Adafruit_DCMotor *motorBL = AFMS.getMotor(2);
    Adafruit_DCMotor *motorFL = AFMS.getMotor(3);
    Adafruit_DCMotor *motorFR = AFMS.getMotor(4);

    //Right for dir = 1, Left for dir = 0
    if (dir == 1)
    {
        motorFL->run(FORWARD);
        motorFR->run(FORWARD);
        motorBL->run(FORWARD);
        motorBR->run(FORWARD);
    }
    else
    {
        motorFL->run(FORWARD);
        motorFR->run(FORWARD);
        motorBL->run(FORWARD);
        motorBR->run(FORWARD);
    }
}

void MyBotMotors::Stop()
{
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    Adafruit_DCMotor *motorBR = AFMS.getMotor(1);
    Adafruit_DCMotor *motorBL = AFMS.getMotor(2);
    Adafruit_DCMotor *motorFL = AFMS.getMotor(3);
    Adafruit_DCMotor *motorFR = AFMS.getMotor(4);

    motorFL->run(RELEASE);
    motorFR->run(RELEASE);
    motorBL->run(RELEASE);
    motorBR->run(RELEASE);
}

void MyBotMotors::Brake()
{
    Adafruit_MotorShield AFMS = Adafruit_MotorShield();
    Adafruit_DCMotor *motorBR = AFMS.getMotor(1);
    Adafruit_DCMotor *motorBL = AFMS.getMotor(2);
    Adafruit_DCMotor *motorFL = AFMS.getMotor(3);
    Adafruit_DCMotor *motorFR = AFMS.getMotor(4);

    motorFL->run(BACKWARD);
    motorFR->run(BACKWARD);
    motorBL->run(BACKWARD);
    motorBR->run(BACKWARD);
    motorFL->run(RELEASE);
    motorFR->run(RELEASE);
    motorBL->run(RELEASE);
    motorBR->run(RELEASE);
}

