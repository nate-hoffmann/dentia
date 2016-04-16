#include <Servo.h>
#include <MyBot.h>
#include "Wire.h"
#include "sensorbar.h"


Servo servo1;
//Prepare Line Sensor to be read
SensorBar FrontSensorBar(LineSensorFrontADD);// Instantiate the motor control object. This only needs to be done once.
SensorBar BackSensorBar(LineSensorBackADD);
//Initialize Super Bot Powers
MyBotAction bottyGo;
MyBotMotors bottyMots;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

//To count Hall Sensors
volatile int pulses = 0;


void setup() {
  // Set Baud Rate
  Serial.begin(115200);
  //Attach Encoder Interrupts
  attachInterrupt(digitalPinToInterrupt(ClawEncoderA),EncoderISR,CHANGE);
  attachInterrupt(digitalPinToInterrupt(ClawEncoderB),EncoderISR,CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorEncoderA),EncoderISR,CHANGE);
    attachInterrupt(digitalPinToInterrupt(MotorEncoderA),EncoderISR,CHANGE);
  // Initialize sensor bars
  FrontSensorBar.begin();//Don't forget to call .begin() to get the bar ready.  This configures HW.
  BackSensorBar.begin();
  AFMS.begin();
  servo1.attach(9);
  servo1.write(0);
  //Claw Movement Demonstration
  ClawMove(0); // Grab Rings
  delay(1000);
  Serial.println("CLAW MOVE (0)");
  ClawMove(1);
  Serial.println("CLAW MOVE (1)");
  delay(1000);
  RotateBot(1,1); //CW
  delay(1000);
  RotateBot(0,1); //CCW
  delay(1000);
  RotateBot(1,2); //CW
  delay(1000);
  RotateBot(0,2); //CCW
}
void loop() {
  // put your main code here, to run repeatedly:
}

void ClawMove(int dir)
{
    if (dir == 0) // Drop Clamp and Raise
    {
      pulses = 0;
      // Drop
      digitalWrite(MotorDriverInA1,LOW);
      digitalWrite(MotorDriverInA2,HIGH);
      while (pulses < ClawDim)
      {
          analogWrite(MotorDriverPWM,255); 
      }
      //Stop
      analogWrite(MotorDriverPWM,0);
      //Prevent Jerking
      delay(1000);
      //Clamp
      servo1.write(95);
      //Prevent Jerking
      delay(1000);
      //Reset pulses
      pulses = 0;
      // Raise
      digitalWrite(MotorDriverInA1,HIGH);
      digitalWrite(MotorDriverInA2,LOW);
      while (pulses < ClawDim)
      {
        analogWrite(MotorDriverPWM,255);
      }
      //Stop
      analogWrite(MotorDriverPWM,0);
      
    }
    else //Drop Release and Raise
    {
      pulses = 0;
      // Drop
      digitalWrite(MotorDriverInA1,LOW);
      digitalWrite(MotorDriverInA2,HIGH);
      while (pulses < ClawDim)
      {
          analogWrite(MotorDriverPWM,255); 
      }
      //Stop
      analogWrite(MotorDriverPWM,0);
      //Prevent Jerking
      delay(1000);
      //Open
      servo1.write(0);
      //Prevent Jerking
      delay(1000);
      //Reset pulses
      pulses = 0;
      // Raise
      digitalWrite(MotorDriverInA1,HIGH);
      digitalWrite(MotorDriverInA2,LOW);
      while (pulses <ClawDim)
      {
        analogWrite(MotorDriverPWM,255);
      }
      //Stop
      analogWrite(MotorDriverPWM,0);
      
    }
}

void RotateBot(int dir,int Number)
{
  pulses = 0;
  if (dir == 0 && Number == 1) //CCW
  {
    while (pulses < RotateDim90*Number)
    {
       bottyMots.Pivot(dir,200);
    }
       bottyMots.Stop();
  }
  else if (dir == 1 && Number == 1) //CW
  {
    while (pulses < RotateDim90*Number)
    {
      bottyMots.Pivot(dir,200);
    }
      bottyMots.Stop();
  }
  else if (dir == 0 && Number == 2) 
  {
    while (pulses < RotateDim*Number)
    {
       bottyMots.Pivot(dir,200);
    }
       bottyMots.Stop();
  }
  else 
  {
    while (pulses < RotateDim*Number)
    {
      bottyMots.Pivot(dir,200);
    }
      bottyMots.Stop();
  }
}
void EncoderISR()
{
  pulses++;
}

