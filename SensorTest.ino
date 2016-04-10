#include <MyBot.h>
//Prepares bot class
MyBotMotors bottyMots;
//Prepare Line Sensor to be read
SensorBar mySensorBar(LineSensorADD);// Instantiate the motor control object. This only needs to be done once.
//Prepares sonar sensors to be read
NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
NewPing sonarRight(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);
NewPing sonarBack(TRIGGER_PIN_BACK, ECHO_PIN_BACK);
NewPing sonarLeft(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
mySensorBar.begin();//Don't forget to call .begin() to get the bar ready.  This configures HW.

}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println("Output of sonar.ping_cm()");
int uS = sonarFront.ping();
Serial.println(uS / US_ROUNDTRIP_CM);
uS = sonarRight.ping();
Serial.println(uS / US_ROUNDTRIP_CM);
uS = sonarLeft.ping();
Serial.println(uS / US_ROUNDTRIP_CM);
uS = sonarBack.ping();
Serial.println(uS / US_ROUNDTRIP_CM);

Serial.println("Outpt of Sensor Bar getRaw, getPosition, and getDensity");
uint8_t x = mySensorBar.getRaw();
int8_t y = mySensorBar.getPosition();
Serial.println(x);
Serial.println(y);
x=mySensorBar.getDensity();
Serial.println(x);

Serial.println("Driving routine to test MyBotMotor Class");
bottyMots.Drive(1,200);
delay(50);
bottyMots.Drive(0,200);
delay(50);
bottyMots.Pivot(1,200);
delay(50);
bottyMots.Pivot(0,200);
delay(50);
bottyMots.Slide(1,200);
delay(50);
bottyMots.Slide(0,200);
delay(50);
bottyMots.Turn(1);
delay(50);
bottyMots.Turn(0);
delay(50);
bottyMots.Stop();
delay(50);
bottyMots.Drive(1,200);
delay(50);
bottyMots.Brake();
delay(50);

//Write out an open close of clamp and motor driver
delay(3000);

}
