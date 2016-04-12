

/*
MyBot.h library- Tyler White
This library is used to control a 4 mechanum wheel robot w/ a grabber
*/
#ifndef MyBot_h
#define MyBot_h

#include "Arduino.h"
#include "sensorbar.h"
#include <AFMotor.h>
#include <NewPing.h>


//#define all pin numbers, Motor Numbers, serial addresses
#define MFL 1
#define MFR 2
#define MBL 3
#define MBR 4

#define MinSpeed 200 // Speed where all motors get 6V
#define MaxSpeed 255

#define LineSensorFrontADD  0x3E
#define LineSensorBackADD   0x3F

#define IDLE_STATE          0
#define SENSOR_READ         1
#define GO_FORWARD          2
#define GO_LEFT             3
#define GO_RIGHT            4
#define ROTATE              5
#define GO_BACKWARD         6
#define CHECK_FINAL         7

#define ERROR               10

#define MotorDriverInA1     42
#define MotorDriverInA2     43
#define MotorDriverPWM      44
#define MotorDriverSTDBY    45

#define SDA                 20
#define SCL                 21

#define TRIGGER_PIN_FRONT   27
#define ECHO_PIN_FRONT      26

#define TRIGGER_PIN_RIGHT   53
#define ECHO_PIN_RIGHT      52

#define TRIGGER_PIN_BACK    23
#define ECHO_PIN_BACK       22

#define TRIGGER_PIN_LEFT    25
#define ECHO_PIN_LEFT       24

//Sonar Sensor Coordinates

#define SecondaryRightPeg       60

#define SecondaryMiddlePegRight 45
#define SecondaryMiddlePegLeft  62

#define SecondaryLeftPeg        26

#define CenterFWDRight          47
#define CenterFWDLeft           45
#define CenterFWDFront          64

#define CenterRIGHTRight        109
#define CenterRIGHTLeft         61
#define CenterRIGHTFront        50

#define CenterLEFTRight         61
#define CenterLEFTLeft          109
#define CenterLEFTFront         50

#define PrimaryMiddlePegRight   63
#define PrimaryMiddlePegLeft    109

#define PrimaryRightPeg         42

#define PrimaryLeftPeg          88

#define ScoringPegCenterRight   47
#define ScoringPegCenterLeft    32

#define ScoringPegRight         32

#define ScoringPegLeft          20

//Locations
#define PrimaryRight            1
#define PrimaryCenter           2
#define PrimaryLeft             3
#define CenterForward           4
#define CenterRight             5
#define CenterLeft              6
#define SecondaryCenter         7
#define SecondaryRight          8
#define SecondaryLeft           9
#define ScoringCenter           10
#define ScoringRight            11
#define ScoringLeft             12



class MyBotMotors
{

  public:
    MyBotMotors(void); // Initializes the Motors for our config
    void Drive(int dir, int spee); // 1 FWD, 0 BCKWD
    void Pivot(int dir, int spee); // 1 CW, 0 CCW
    void Slide(int dir, int spee); // 1 Right, 0 Left
    void Turn (int dir); // 1 Right, 0 Left
    void Stop(); // Stop powering motors
    void Brake(); // Force motors to a stop

};

class MyBotAction
{
  public:
    MyBotAction(); // Initialize all sensors needed for ops
    void DriveToLocation(int dir, int spee,int Location); // 1 for FWD, 0 for BCKWD
    void Rotate(int dir, int Location); // amount is 1/4 turn, 1/2 turn, etc
/*    void ClampRelease(int Dir); // 1 to close, 0 to open
    void ClawMove(int dir); // 1 for up, 0 for down
    void LineSlide(int dir, int spee); // 1 for right, 0 for left
    void NoLineSlide(int dir, int spee); // 1 for right, 0 for left
    void DriveToWall(int dir, int spee); // 1 for FWD, 0 for BCKWD
*/
};

class MyBotMap
{
public:
    int* WhatLocation(int Location);
    int CheckLocation (int Location);
    void GoToLocation (int Location);
};

#endif
