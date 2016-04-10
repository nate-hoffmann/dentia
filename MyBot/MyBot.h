

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

#define MinSpeed 150 // Speed where all motors get 6V
#define MaxSpeed 255

#define LineSensorADD 0x3E

#define IDLE_STATE 0
#define SENSOR_READ 1
#define GO_FORWARD 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define ROTATE 5
#define GO_BACKWARD 6

#define TRIGGER_PIN_FRONT  22
#define ECHO_PIN_FRONT     23

#define TRIGGER_PIN_RIGHT  24
#define ECHO_PIN_RIGHT     25

#define TRIGGER_PIN_BACK   26
#define ECHO_PIN_BACK      27

#define TRIGGER_PIN_LEFT   28
#define ECHO_PIN_LEFT      29

#define SDA 20
#define SCL 21


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
    void DriveToLine(int dir, int spee,uint8_t input); // 1 for FWD, 0 for BCKWD
    void Rotate(int dir, int input); // amount is 1/4 turn, 1/2 turn, etc
/*    void ClampRelease(int Dir); // 1 to close, 0 to open
    void ClawMove(int dir); // 1 for up, 0 for down
    void LineSlide(int dir, int spee); // 1 for right, 0 for left
    void NoLineSlide(int dir, int spee); // 1 for right, 0 for left
    void DriveToWall(int dir, int spee); // 1 for FWD, 0 for BCKWD
*/
};

#endif
