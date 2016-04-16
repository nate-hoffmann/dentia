#include <Servo.h>
#include <MyBot.h>
#include "Wire.h"
#include "sensorbar.h"

//Initialize Servo
Servo servo1;
//Prepare Line Sensor to be read
SensorBar FrontSensorBar(LineSensorFrontADD);// Instantiate the motor control object. This only needs to be done once.
//Initialize Super Bot Powers
MyBotAction bottyGo;
MyBotMotors bottyMots;
//Initialize Adafruit Motor Shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

//To count Hall Sensors
volatile int pulses = 0;

int LoopNum = 1;

void setup() {
  // Set Baud Rate
  //Serial.begin(115200);
  delay(5000);
  //Attach Encoder and Motor Interrupts
  attachInterrupt(digitalPinToInterrupt(ClawEncoderA),EncoderISR,CHANGE);
  attachInterrupt(digitalPinToInterrupt(ClawEncoderB),EncoderISR,CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorEncoderA),EncoderISR,CHANGE);
  attachInterrupt(digitalPinToInterrupt(MotorEncoderA),EncoderISR,CHANGE);
  // Initialize sensor bars
  FrontSensorBar.clearBarStrobe();
  FrontSensorBar.begin();//Don't forget to call .begin() to get the bar ready.  This configures HW.
  //Begin Motor Shield Ops
  AFMS.begin();
  //Attach and Open Servo
  servo1.attach(9);
  servo1.write(0);
  bottyMots.Stop();


  //Test Begins
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (LoopNum)
  {

    bottyGo.DriveToWall();
    Serial.println("1");
    delay(500);
    bottyGo.PegCenter();
    ClawMove(0);
    Serial.println("2");
    delay(1000);
    bottyGo.DriveToCenter(0);
    Hitch();
    Serial.println("3");
    delay(1000);
    RotateBot(1,1);
    Serial.println("4");
    delay(1000);
    bottyGo.DriveToWall();
    Serial.println("5");   
    delay(1000);
    bottyGo.PegCenter();
    ClawMove(1);
    Serial.println("6");
    delay(1000); 
    BackupFromPickup(150);
    bottyGo.DriveToCenter(0);
    Hitch();
    Serial.println("7");
    delay(1000);
    RotateBot(1,1);
    Serial.println("8");
    delay(1000);
    bottyGo.DriveToWall();
    Serial.println("9");
    delay(1000);
    bottyGo.PegCenter();
    ClawMove(0);
    Serial.println("10");
    BackupFromPickup(150);
    bottyGo.DriveToCenter(0);
    Hitch();
    Serial.println("11");
    delay(1000);
    RotateBot(0,1);
    Serial.println("12");
    delay(1000);
    bottyGo.DriveToWall();
    Serial.println("13");
    delay(1000);
    bottyGo.PegCenter();
    ClawMove(1);
    Serial.println("14");
    BackupFromPickup(150);
    bottyGo.DriveToCenter(0);
    Hitch();
    Serial.println("15");
    delay(1000);
    RotateBot(0,1);
    Serial.println("16");
    delay(1000);
    bottyGo.DriveToWall();
    Serial.println("17");
    delay(1000);
    bottyGo.PegCenter();
    GoOffLine(1);
    bottyGo.PegCenter();
    Serial.println("18");
    delay(1000);
    bottyGo.PegCenter();
    ClawMove(0);
    Serial.println("19");
    GoOffLine(0);
    bottyGo.PegCenter();
    Serial.println("20");
    delay(1000);
    bottyGo.DriveToCenter(0);
    Hitch();
    Serial.println("21");
    delay(1000);
    RotateBot(1,1);
    Serial.println("22");
    delay(1000);
    bottyGo.DriveToWall();
    Serial.println("23");
    delay(1000);
    bottyGo.PegCenter();
    ClawMove(1);
    Serial.println("24");
    BackupFromPickup(150);
    bottyGo.DriveToCenter(0);
    Hitch();
    Serial.println("25");
    delay(1000);
    bottyMots.Pivot(1,200);
    delay(10000);
    bottyMots.Stop();
  }
  LoopNum = 0;
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
      servo1.write(90);
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

void BackupFromPickup(int spee)
{
  pulses = 0;
  while(pulses < FromSide)
  {
    bottyMots.Drive(0,spee);
  }
    bottyMots.Stop();
}

void Hitch()
{
  pulses = 0;
  while(pulses < HitchAMT)
  {
    bottyMots.Drive(1,100);
  }
    bottyMots.Stop();
}
void RotateBot(int dir,int Number)
{
  pulses = 0;
  if (dir == 0 && Number == 1) //CCW
  {
    while (pulses < RotateDim90*Number)
    {
       bottyMots.Pivot(dir,150);
    }
       bottyMots.Stop();
  }
  else if (dir == 1 && Number == 1) //CW
  {
    while (pulses < RotateDim90*Number)
    {
      bottyMots.Pivot(dir,150);
    }
      bottyMots.Stop();
  }
  else if (dir == 0 && Number == 2) 
  {
    while (pulses < RotateDim*Number)
    {
       bottyMots.Pivot(dir,150);
    }
       bottyMots.Stop();
  }
  else 
  {
    while (pulses < RotateDim*Number)
    {
      bottyMots.Pivot(dir,150);
    }
      bottyMots.Stop();
  }
}

void GoOffLine(int dir)
{
  pulses = 0;
  while(pulses < SecondarySideSlide)
  {
    bottyMots.Slide(dir,150);
  }
    bottyMots.Stop();
}

void EncoderISR()
{
  pulses++;
}
