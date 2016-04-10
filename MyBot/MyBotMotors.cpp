
#include "MyBot.h"
#include "Arduino.h"
#include <AFMotor.h>



MyBotMotors::MyBotMotors(void)
{

}
 

void MyBotMotors::Drive(int dir,int spee)
{
    AF_DCMotor motorFL(MFL,MOTOR12_64KHZ);
    AF_DCMotor motorFR(MFR,MOTOR12_64KHZ);
    AF_DCMotor motorBL(MBL,MOTOR12_64KHZ);
    AF_DCMotor motorBR(MBR,MOTOR12_64KHZ);
 
    // FWD for dir = 1, BCKWD for dir = 0
    // Potentiall include an if loop for if the input speed is too slow to give motor 6V
    if (dir == 1){
        
    motorFL.run(FORWARD);
    motorFR.run(FORWARD);
    motorBL.run(FORWARD);
    motorBR.run(FORWARD);
    motorFL.setSpeed(spee);
    motorFR.setSpeed(spee);
    motorBL.setSpeed(spee);
    motorBR.setSpeed(spee);
    }
    else
    {
    motorFL.run(BACKWARD);
    motorFR.run(BACKWARD);
    motorBL.run(BACKWARD);
    motorBR.run(BACKWARD);
    motorFL.setSpeed(spee);
    motorFR.setSpeed(spee);
    motorBL.setSpeed(spee);
    motorBR.setSpeed(spee);
    }
}

void MyBotMotors::Pivot(int dir,int spee)
{
    AF_DCMotor motorFL(MFL,MOTOR12_64KHZ);
    AF_DCMotor motorFR(MFR,MOTOR12_64KHZ);
    AF_DCMotor motorBL(MBL,MOTOR12_64KHZ);
    AF_DCMotor motorBR(MBR,MOTOR12_64KHZ);
    //CW for dir = 1, CCW for dir = 0
    if (dir == 1)
    {
    motorFL.run(FORWARD);
    motorFR.run(BACKWARD);
    motorBL.run(FORWARD);
    motorBR.run(BACKWARD);
    motorFL.setSpeed(spee);
    motorFR.setSpeed(spee);
    motorBL.setSpeed(spee);
    motorBR.setSpeed(spee);
    }
    else
    {
    motorFL.run(BACKWARD);
    motorFR.run(FORWARD);
    motorBL.run(BACKWARD);
    motorBR.run(FORWARD);
    motorFL.setSpeed(spee);
    motorFR.setSpeed(spee);
    motorBL.setSpeed(spee);
    motorBR.setSpeed(spee);
    }
}

void MyBotMotors::Slide(int dir,int spee)
{
    AF_DCMotor motorFL(MFL,MOTOR12_64KHZ);
    AF_DCMotor motorFR(MFR,MOTOR12_64KHZ);
    AF_DCMotor motorBL(MBL,MOTOR12_64KHZ);
    AF_DCMotor motorBR(MBR,MOTOR12_64KHZ);
    //Right for dir = 1, Left for dir = 0
    if (dir == 1)
    {
    motorFL.run(BACKWARD);
    motorFR.run(BACKWARD);
    motorBL.run(FORWARD);
    motorBR.run(FORWARD);
    motorFL.setSpeed(spee);
    motorFR.setSpeed(spee);
    motorBL.setSpeed(spee);
    motorBR.setSpeed(spee);
    }
    else
    {
    motorFL.run(FORWARD);
    motorFR.run(FORWARD);
    motorBL.run(BACKWARD);
    motorBR.run(BACKWARD);
    motorFL.setSpeed(spee);
    motorFR.setSpeed(spee);
    motorBL.setSpeed(spee);
    motorBR.setSpeed(spee);
    }
}

void MyBotMotors::Turn(int dir)
{
    AF_DCMotor motorFL(MFL,MOTOR12_64KHZ);
    AF_DCMotor motorFR(MFR,MOTOR12_64KHZ);
    AF_DCMotor motorBL(MBL,MOTOR12_64KHZ);
    AF_DCMotor motorBR(MBR,MOTOR12_64KHZ);
    //Right for dir = 1, Left for dir = 0
    if (dir == 1)
    {
        motorFL.run(FORWARD);
        motorFR.run(FORWARD);
        motorBL.run(FORWARD);
        motorBR.run(FORWARD);
        motorFL.setSpeed(MaxSpeed);
        motorFR.setSpeed(MinSpeed);
        motorBL.setSpeed(MaxSpeed);
        motorBR.setSpeed(MinSpeed);
    }
    else
    {
        motorFL.run(FORWARD);
        motorFR.run(FORWARD);
        motorBL.run(FORWARD);
        motorBR.run(FORWARD);
        motorFL.setSpeed(MinSpeed);
        motorFR.setSpeed(MaxSpeed);
        motorBL.setSpeed(MinSpeed);
        motorBR.setSpeed(MaxSpeed);
    }
}

void MyBotMotors::Stop()
{
    AF_DCMotor motorFL(MFL,MOTOR12_64KHZ);
    AF_DCMotor motorFR(MFR,MOTOR12_64KHZ);
    AF_DCMotor motorBL(MBL,MOTOR12_64KHZ);
    AF_DCMotor motorBR(MBR,MOTOR12_64KHZ);
    motorFL.run(RELEASE);
    motorFR.run(RELEASE);
    motorBL.run(RELEASE);
    motorBR.run(RELEASE);
}

void MyBotMotors::Brake()
{
    AF_DCMotor motorFL(MFL,MOTOR12_64KHZ);
    AF_DCMotor motorFR(MFR,MOTOR12_64KHZ);
    AF_DCMotor motorBL(MBL,MOTOR12_64KHZ);
    AF_DCMotor motorBR(MBR,MOTOR12_64KHZ);
    motorFL.run(BRAKE);
    motorFR.run(BRAKE);
    motorBL.run(BRAKE);
    motorBR.run(BRAKE);
}

