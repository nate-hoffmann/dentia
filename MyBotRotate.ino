#include <AFMotor.h>
#include "Wire.h"
#include "sensorbar.h"

const uint8_t SX1509_ADDRESS = 0x3E;
SensorBar mySensorBar(SX1509_ADDRESS);

AF_DCMotor motorFL(1,MOTOR12_64KHZ);
AF_DCMotor motorFR(2,MOTOR12_64KHZ);
AF_DCMotor motorBL(3,MOTOR12_64KHZ);
AF_DCMotor motorBR(4,MOTOR12_64KHZ);

#define IDLE_STATE 0
#define READ_LINE 1
#define ROT_CW 2
#define ROT_CCW 3
#define END_STATE 4

uint8_t state;
uint8_t count=0;
  
void setup() {
  // put your setup code here, to run once:
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

void loop() {
  // put your main code here, to run repeatedly:

  uint8_t nextState = state;
  switch (state) {
  case IDLE_STATE:
    if (count < 5){
      motorFL.run(FORWARD);
      motorFR.run(BACKWARD);
      motorBL.run(FORWARD);
      motorBR.run(BACKWARD);
      motorFL.setSpeed(150);
      motorFR.setSpeed(150);
      motorBL.setSpeed(150);
      motorBR.setSpeed(150);
      nextState = READ_LINE;
    }
    else{
      motorFL.run(BRAKE);
      motorFR.run(BRAKE);
      motorBL.run(BRAKE);
      motorBR.run(BRAKE);
    }
    break;
  case READ_LINE:
    if( mySensorBar.getDensity() < 4 )
    {
      nextState = ROT_CW;  
    }
    else
    {
      nextState=IDLE_STATE;
    }
    break;
  case ROT_CW:
 //   driveBot(200);
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
  count++;
  state = nextState;
  //delay(100);
}
