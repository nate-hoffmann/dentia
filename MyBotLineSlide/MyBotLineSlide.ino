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
#define MOVE_LEFT 3
#define MOVE_RIGHT 4
#define GO_BACKWARD 5

uint8_t direct = 0; // THis will be an input to this function
uint8_t stopper = 0; // THis is a variable used to signify the end of the process.

if ( direct == 0 ){
  uint8_t state = GO_RIGHT;
}
else{
  uint8_t state = GO_LEFT;
}
uint8_t stopper = 0;

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

  delay(3000);
  
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
    Serial.println("IDLE");
    stopper = 1;
    break;
  case READ_LINE:
  if (stopper == 0)
  {
    if( mySensorBar.getDensity() < 3 )
    {
      nextState = GO_FORWARD;
      if( mySensorBar.getPosition() < -20 )
      {
        nextState = GO_LEFT;
      }
      if( mySensorBar.getPosition() > 20 )
      {
        nextState = GO_RIGHT;
      }
    Serial.println(mySensorBar.getPosition());
    }
    else
    {
      nextState = IDLE_STATE;
    }
  }
  else
  {
    nextState = IDLE_STATE; 
  }
    Serial.println("READ");
    break;
  case GO_FORWARD:
 //   driveBot(200);
 if (stopper == 0)
 {
    motorFL.run(FORWARD);
    motorFR.run(FORWARD);
    motorBL.run(FORWARD);
    motorBR.run(FORWARD);
    motorFL.setSpeed(150);
    motorFR.setSpeed(100);
    motorBL.setSpeed(130);
    motorBR.setSpeed(130);
    nextState = READ_LINE;
 }
 else
 {
  nextState = IDLE_STATE;
 }
    Serial.println("FWD");
    break;
  case GO_LEFT:
  if (stopper == 0)
  {
//    turnBot(-.75);
    motorFL.run(FORWARD);
    motorFR.run(FORWARD);
    motorBL.run(FORWARD);
    motorBR.run(FORWARD);
    motorFL.setSpeed(100);
    motorFR.setSpeed(255);
    motorBL.setSpeed(100);
    motorBR.setSpeed(255);
    nextState = READ_LINE;
  }
  else
  {
    nextState = IDLE_STATE;
  }
    Serial.println("LEFT");
    break;
  case GO_RIGHT:
//    turnBot(.75);
    if (stopper == 0)
    {
    motorFL.run(FORWARD);
    motorFR.run(FORWARD);
    motorBL.run(FORWARD);
    motorBR.run(FORWARD);
    motorFL.setSpeed(255);
    motorFR.setSpeed(100);
    motorBL.setSpeed(255);
    motorBR.setSpeed(100);
    nextState = READ_LINE;
    }
    else
    {
      nextState = IDLE_STATE;
    }
    Serial.println("RIGHT");
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

}
