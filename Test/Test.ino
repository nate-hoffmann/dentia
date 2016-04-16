#include <Servo.h>
#include <MyBot.h>

//Prepare servo
Servo servo1;
//Prepares bot class
MyBotMotors bottyMots;
MyBotMap  bottyMap;

//For Encoder
volatile int pulses=0;

//Prepare Line Sensor to be read
SensorBar FrontSensorBar(LineSensorBackADD);// Instantiate the motor control object. This only needs to be done once.


//Prepares sonar sensors to be read
NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
FrontSensorBar.clearInvertBits();
delay(1000);
FrontSensorBar.begin();//Don't forget to call .begin() to get the bar ready.  This configures HW.


pinMode(MotorDriverInA1,OUTPUT);
pinMode(MotorDriverInA2,OUTPUT);
pinMode(MotorDriverPWM,OUTPUT);
servo1.attach(9);
  attachInterrupt(digitalPinToInterrupt(ClawEncoderA),EncoderISR,CHANGE);
  attachInterrupt(digitalPinToInterrupt(ClawEncoderB),EncoderISR,CHANGE);
//Setup DC encoder
  pinMode(ClawEncoderA,INPUT);
  pinMode(ClawEncoderB,INPUT);
  digitalWrite(MotorDriverInA1,LOW);
  digitalWrite(MotorDriverInA2,HIGH);

 
  while (pulses < ClawDim )
  {
      analogWrite(MotorDriverPWM,255); 
  }
  analogWrite(MotorDriverPWM,0);
  delay(1000);
  pulses = 0;
  digitalWrite(MotorDriverInA1,HIGH);
  digitalWrite(MotorDriverInA2,LOW);
  while (pulses < ClawDim)
  {
    analogWrite(MotorDriverPWM,255);
  }
  analogWrite(MotorDriverPWM,0);

bottyMots.Stop();
}

void loop() {
  // put your main code here, to run repeatedly:
/*Serial.println("Servo Test Begin");
for (int i=544;i<1000;i++){
  servo1.write(i);
  delay(10);
}*/
/*
servo1.write(90);
delay(1000);
servo1.write(40);
delay(1000);
servo1.write(0);
Serial.println("Servo Test End");
delay(1000);

  for (int i=0;i<20;i++)
  {
    Serial.println(sonarFront.ping_median()/US_ROUNDTRIP_CM);
  }
Serial.println("Outpt of Front Sensor Bar getPosition, and getDensity");

int8_t y = FrontSensorBar.getPosition();
Serial.print(y);
uint8_t x=FrontSensorBar.getDensity();
Serial.print("\t");
Serial.println(x);
delay(300);
*/
/*
Serial.println("Driving routine to test MyBotMotor Class");
bottyMots.Drive(1,200);
delay(1000);
bottyMots.Drive(0,200);
delay(1000);
bottyMots.Pivot(1,200);
delay(1000);
bottyMots.Pivot(0,200);
delay(1000);
bottyMots.Slide(1,200);
delay(1000);
bottyMots.Slide(0,200);
delay(1000);
bottyMots.Stop();
delay(1000);
bottyMots.Drive(1,200);
delay(1000);




//digitalWrite(MotorDriverSTDBY,HIGH);
//Serial.println("MotorDriverTestBegin");
//Serial.println("A1=0 A2=1 PWM = 100");
/*
// CCW
Serial.println("CCW: A1=1 A2=0 PWM = 100");
digitalWrite(MotorDriverInA1,LOW);
digitalWrite(MotorDriverInA2,HIGH);
analogWrite(MotorDriverPWM,255);
delay(100);

//CW
digitalWrite(MotorDriverInA1,HIGH);
digitalWrite(MotorDriverInA2,LOW);
analogWrite(MotorDriverPWM,255);
delay(100);
//Stop
analogWrite(MotorDriverPWM,0);
Serial.println("Test Complete");


Serial.println("CCW: A1=1 A2=0 PWM = 100");
digitalWrite(MotorDriverInA1,HIGH);
digitalWrite(MotorDriverInA2,LOW);
Serial.println("Pulsing Test");
delay(1000);
Serial.println("delay(10)");
analogWrite(MotorDriverPWM,255);
delay(10);
analogWrite(MotorDriverPWM,0);
delay(1000);
Serial.println("delay(20)");
analogWrite(MotorDriverPWM,255);
delay(20);
analogWrite(MotorDriverPWM,0);

*/
}

void EncoderISR()
{
  pulses++;
}

