#include <AFMotor.h>
#include "Wire.h"
#include "sensorbar.h"
//#include <RedBot.h>  // This line "includes" the RedBot library into your sketch.
// Provides special objects, methods, and functions for the RedBot.
//The Redbot Library can be found here: https://github.com/sparkfun/RedBot

// Uncomment one of the four lines to match your SX1509's address
//  pin selects. SX1509 breakout defaults to [0:0] (0x3E).
const uint8_t SX1509_ADDRESS = 0x3E;  // SX1509 I2C address (00)
//const byte SX1509_ADDRESS = 0x3F;  // SX1509 I2C address (01)
//const byte SX1509_ADDRESS = 0x70;  // SX1509 I2C address (10)
//const byte SX1509_ADDRESS = 0x71;  // SX1509 I2C address (11)

SensorBar mySensorBar(SX1509_ADDRESS);
// Instantiate the motor control object. This only needs
// to be done once.
AF_DCMotor motorFL(1,MOTOR12_64KHZ);
AF_DCMotor motorFR(2,MOTOR12_64KHZ);
AF_DCMotor motorBL(3,MOTOR12_64KHZ);
AF_DCMotor motorBR(4,MOTOR12_64KHZ);

int count=0;

//Define motor polarity for left and right side -- USE TO FLIP motor directions if wired backwards
/*#define FR_WHEEL_POL 1
#define FL_WHEEL_POL 1
#define BR_WHEEL_POL 1
#define BL_WHEEL_POL 1
*/
//Define the states that the decision making machines uses:
#define IDLE_STATE 0
#define READ_LINE 1
#define GO_FORWARD 2
#define GO_LEFT 3
#define GO_RIGHT 4

uint8_t state;


void setup()
{
  Serial.begin(9600);  // start serial for output
  Serial.println("Program started.");
  Serial.println();
  
  //Default: the IR will only be turned on during reads.
  mySensorBar.setBarStrobe();
  //Other option: Command to run all the time
  //mySensorBar.clearBarStrobe();

  //Default: dark on light
  mySensorBar.clearInvertBits();
  //Other option: light line on dark
  //mySensorBar.setInvertBits();
  
  //Don't forget to call .begin() to get the bar ready.  This configures HW.
  uint8_t returnStatus = mySensorBar.begin();
  if(returnStatus)
  {
    Serial.println("sx1509 IC communication OK");
  }
  else
  {
    Serial.println("sx1509 IC communication FAILED!");
  }
  Serial.println();
  
}

void loop()
{


  uint8_t nextState = state;
  switch (state) {
  case IDLE_STATE:
 //   motors.stop();       // Stops both motors
    motorFL.run(RELEASE);
    motorFR.run(RELEASE);
    motorBL.run(RELEASE);
    motorBR.run(RELEASE);
    nextState = READ_LINE;
    break;
  case READ_LINE:
    if( mySensorBar.getDensity() < 4 )
    {
      nextState = GO_FORWARD;
      if( mySensorBar.getPosition() < -50 )
      {
        nextState = GO_LEFT;
      }
      if( mySensorBar.getPosition() > 50 )
      {
        nextState = GO_RIGHT;
      }
    }
    else
    {
      nextState = IDLE_STATE;
      count=count+1;
    }
    break;
  case GO_FORWARD:
 //   driveBot(200);
    motorFL.run(FORWARD);
    motorFR.run(FORWARD);
    motorBL.run(FORWARD);
    motorBR.run(FORWARD);
    motorFL.setSpeed(200);
    motorFR.setSpeed(200);
    motorBL.setSpeed(200);
    motorBR.setSpeed(200);
    nextState = READ_LINE;
    break;
  case GO_LEFT:
//    turnBot(-.75);
    motorFL.run(BACKWARD);
    motorFR.run(FORWARD);
    motorBL.run(BACKWARD);
    motorBR.run(FORWARD);
    motorFL.setSpeed(150);
    motorFR.setSpeed(150);
    motorBL.setSpeed(150);
    motorBR.setSpeed(150);
    nextState = READ_LINE;
    break;
  case GO_RIGHT:
//    turnBot(.75);
    motorFL.run(FORWARD);
    motorFR.run(BACKWARD);
    motorBL.run(FORWARD);
    motorBR.run(BACKWARD);
    motorFL.setSpeed(150);
    motorFR.setSpeed(150);
    motorBL.setSpeed(150);
    motorBR.setSpeed(150);
    nextState = READ_LINE;
    break;
  default:
 //   motors.stop();       // Stops both motors
    motorFL.run(RELEASE);
    motorFR.run(RELEASE);
    motorBL.run(RELEASE);
    motorBR.run(RELEASE);
    break;
  }
  state = nextState;
  //delay(100);
}
