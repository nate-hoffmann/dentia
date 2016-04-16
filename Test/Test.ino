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
      delay(1000);
      FrontSensorBar.begin();//Don't forget to call .begin() to get the bar ready.  This configures HW.
      BackSensorBar.begin();
     
      pinMode(MotorDriverInA1,OUTPUT);
      pinMode(MotorDriverInA2,OUTPUT);
      pinMode(MotorDriverPWM,OUTPUT);
      servo1.attach(9);
      Adafruit_MotorShield AFMS = Adafruit_MotorShield();
      AFMS.begin();
}




void loop() {

      Serial.println("Servo Test Begin");
      servo1.write(90);
      delay(1000);
      servo1.write(0);
      delay(1000);
      Serial.println("Servo Test End");
      
      
      /*Serial.println("Output of sonar.ping/US_ROUNDTRIP_CM");
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
      
      Serial.println("Outpt of Front Sensor Bar getRaw, getPosition, and getDensity");
      uint8_t x = FrontSensorBar.getRaw();
      int8_t y = FrontSensorBar.getPosition();
      Serial.println(x,BIN);
      Serial.println(y);
      x=FrontSensorBar.getDensity();
      Serial.println(x);
      Serial.println("Outpt of Back Sensor Bar getRaw, getPosition, and getDensity");
      
      x = BackSensorBar.getRaw();
      y = BackSensorBar.getPosition();
      
      Serial.println(x,BIN);
      Serial.println(y);
      
      x=BackSensorBar.getDensity();
      
      Serial.println(x);
      Serial.println("Driving routine to test MyBotMotor Class");*/
      
      bottyMots.Drive(1,100);
      delay(4000);
      bottyMots.Brake();
      
      //digitalWrite(MotorDriverSTDBY,HIGH);
      //Serial.println("MotorDriverTestBegin");
      //Serial.println("A1=0 A2=1 PWM = 100");
      
      // CCW
      Serial.println("CCW: A1=1 A2=0 PWM = 100");
      digitalWrite(MotorDriverInA1,LOW);
      digitalWrite(MotorDriverInA2,HIGH);
      analogWrite(MotorDriverPWM,255);
      delay(200);
      
      //CW
      digitalWrite(MotorDriverInA1,HIGH);
      digitalWrite(MotorDriverInA2,LOW);
      analogWrite(MotorDriverPWM,255);
      delay(200);
      //Stop
      analogWrite(MotorDriverPWM,0);
      Serial.println("Test Complete");
      
      
      /*Serial.println("CCW: A1=1 A2=0 PWM = 100");
      digitalWrite(MotorDriverInA1,HIGH);
      digitalWrite(MotorDriverInA2,LOW);
      Serial.println("Pulsing Test");
      delay(1000);
      Serial.println("delay(10)");
      analogWrite(MotorDriverPWM,255);
      delay(20);
      analogWrite(MotorDriverPWM,0);
      delay(1000);
      Serial.println("delay(20)");
      analogWrite(MotorDriverPWM,255);
      delay(20);
      analogWrite(MotorDriverPWM,0);*/


}
