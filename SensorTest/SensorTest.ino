#include <Servo.h>
#include <MyBot.h>

//Prepare servo
Servo servo1;
//Prepares bot class
MyBotMotors bottyMots;
MyBotMap  bottyMap;

//Prepare Line Sensor to be read
SensorBar FrontSensorBar(LineSensorFrontADD);// Instantiate the motor control object. This only needs to be done once.
SensorBar BackSensorBar(LineSensorBackADD);
//Prepares sonar sensors to be read
NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
NewPing sonarRight(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);
NewPing sonarBack(TRIGGER_PIN_BACK, ECHO_PIN_BACK);
NewPing sonarLeft(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
FrontSensorBar.begin();//Don't forget to call .begin() to get the bar ready.  This configures HW.
BackSensorBar.begin();
boolean Truth = true;
Serial.println("Servo Attachment Test");
for (int i = 1;i<30;i++)
{
servo1.attach(i);
  if (servo1.attached()==Truth)
  {
    Serial.print("Servo ");
    Serial.print(i);
    int j=i;
    Serial.println(" is attached");
  }
}
pinMode(MotorDriverInA1,OUTPUT);
pinMode(MotorDriverInA2,OUTPUT);
pinMode(MotorDriverPWM,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println("Servo Test Begin");
for (int i=544;i<1000;i++){
  servo1.write(9);
  delay(10);
}
Serial.println("Servo Test End");
delay(3000);

Serial.println("Output of sonar.ping/US_ROUNDTRIP_CM");
int uS = sonarFront.ping();
Serial.print("Front: ");
Serial.println(uS / US_ROUNDTRIP_CM);
uS = sonarRight.ping();
Serial.print("Right: ");
Serial.println(uS / US_ROUNDTRIP_CM);

uS = sonarLeft.ping();
Serial.print("Left: ");
Serial.println(uS / US_ROUNDTRIP_CM);

uS = sonarBack.ping();
Serial.print("Back: ");
Serial.println(uS / US_ROUNDTRIP_CM);
delay(3000);
/*Serial.println("Outpt of Front Sensor Bar getRaw, getPosition, and getDensity");
uint8_t x = FrontSensorBar.getRaw();
int8_t y = FrontSensorBar.getPosition();
Serial.println(x,BIN);
Serial.println(y);
x=FrontSensorBar.getDensity();
Serial.println(x);
delay(1000);
Serial.println("Outpt of Back Sensor Bar getRaw, getPosition, and getDensity");
x = BackSensorBar.getRaw();
y = BackSensorBar.getPosition();
Serial.println(x,BIN);
Serial.println(y);
x=BackSensorBar.getDensity();
Serial.println(x);
delay(3000);
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
bottyMots.Turn(1);
delay(1000);
bottyMots.Turn(0);
delay(1000);
bottyMots.Stop();
delay(1000);
bottyMots.Drive(1,200);
delay(1000);
bottyMots.Brake();
delay(1000);
*/

delay(3000);
digitalWrite(MotorDriverSTDBY,HIGH);
Serial.println("MotorDriverTestBegin");
Serial.println("A1=0 A2=1 PWM = 100");

// CCW
digitalWrite(MotorDriverInA1,LOW);
digitalWrite(MotorDriverInA2,HIGH);
analogWrite(MotorDriverPWM,100);
delay(1000);
Serial.println("CCW: A1=1 A2=0 PWM = 100");

//CW
digitalWrite(MotorDriverInA1,HIGH);
digitalWrite(MotorDriverInA2,LOW);
analogWrite(MotorDriverPWM,100);
delay(1000);
Serial.println("CW: A1=0 A2=1 PWM = 0");
digitalWrite(MotorDriverInA1,LOW);
digitalWrite(MotorDriverInA2,HIGH);
analogWrite(MotorDriverPWM,0);

Serial.println("Test Complete");
digitalWrite(MotorDriverSTDBY,LOW);
delay(3000);

}
