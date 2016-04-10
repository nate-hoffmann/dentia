#include <MyBot.h>
#include "Wire.h"
#include "sensorbar.h"

//Prepare Line Sensor to be read
SensorBar mySensorBar(LineSensorADD);// Instantiate the motor control object. This only needs to be done once.

//Initialize Super Bot Powers
MyBotAction bottyGo;

void setup() {
// May need faster for the ultrasonic
Serial.begin(9600);
mySensorBar.begin();//Don't forget to call .begin() to get the bar ready.  This configures HW.

//--------------------------------------------------------------------------------------------//
// Beginning of the Competition

//Action 1: Drive to Center Line
bottyGo.DriveToLine(1,200,(uint8_t) 2);

//Action 2: Rotate
bottyGo.Rotate(0,2);

//Action 3: 
}

void loop() {
  // put your main code here, to run repeatedly:

}
