#include <MyBot.h>
#include "Wire.h"
#include "sensorbar.h"

//Prepare Line Sensor to be read
SensorBar FrontSensorBar(LineSensorFrontADD);// Instantiate the motor control object. This only needs to be done once.
SensorBar BackSensorBar(LineSensorBackADD);
//Initialize Super Bot Powers
MyBotAction bottyGo;

void setup() {
// May need faster for the ultrasonic
Serial.begin(9600);
delay(5000);
FrontSensorBar.begin();//Don't forget to call .begin() to get the bar ready.  This configures HW.
BackSensorBar.begin();
//--------------------------------------------------------------------------------------------//
// Beginning of the Competition

//Action 1: Drive to Center Line
bottyGo.DriveToLocation(1,200,CenterRight);

//Action 2: Rotate
bottyGo.Rotate(1,CenterForward);

//Action 3: 
bottyGo.DriveToLocation(1,200,ScoringCenter);
}

void loop() {
  // put your main code here, to run repeatedly:

}
