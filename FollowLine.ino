//Include Motor Library
#include <AFMotor.h>

//Define some tunable constants
#define Threshold 800
#define StartSpeed 150
#define SlideSpeed 200
#define RotateSpeed 100
#define Gain 2
#define Sensor1 8
#define Sensor2 9
#define Sensor3 10
#define Sensor4 11
#define Sensor5 12
#define Sensor6 13
#define Sensor7 14
#define Sensor8 15

int SpeedFL = StartSpeed;
int SpeedFR = StartSpeed; 
int SpeedBL = StartSpeed;
int SpeedBR = StartSpeed;

//Setup the Motor(s)
AF_DCMotor motorFL(1,MOTOR12_64KHZ);
AF_DCMotor motorFR(2,MOTOR12_64KHZ);
AF_DCMotor motorBL(3,MOTOR12_64KHZ);
AF_DCMotor motorBR(4,MOTOR12_64KHZ);

void setup() {

  Serial.begin(9600);
  //Parameters that would be passed into this function
  int NumberOfPluses=2;
  int PlusCount=0;
  motorFL.run(FORWARD);
  motorFR.run(FORWARD);
  motorBL.run(FORWARD);
  motorBR.run(FORWARD);

  motorFL.setSpeed(SpeedFL);
  motorFR.setSpeed(SpeedFR);
  motorBL.setSpeed(SpeedBL);
  motorBR.setSpeed(SpeedBR);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (analogRead(Sensor6) > Threshold){
    //Increase Right Side Wheels Speed
    SpeedFR+=1*Gain;
    SpeedBR+=1*Gain;
    //Activate that increase in the wheels
    motorFR.setSpeed(SpeedFR);  
    motorBR.setSpeed(SpeedBR);
  }

  //If having issues with this routine, consider some other scearios with more sever cockey using sensors 2 and 3
  if (analogRead(Sensor5) > Threshold){
    //Stop!
    motorFL.run(BRAKE);
    motorFR.run(BRAKE);
    motorBL.run(BRAKE);
    motorBR.run(BRAKE);
    while(analogRead(Sensor1) < Threshold && analogRead(Sensor2) < Threshold && analogRead(Sensor3) < Threshold && analogRead(Sensor4) < Threshold){
      //Slide Left
      motorFL.run(BACKWARD);
      motorFR.run(FORWARD);
      motorBL.run(FORWARD);
      motorBR.run(BACKWARD);
      motorFL.setSpeed(SlideSpeed);
      motorFR.setSpeed(SlideSpeed);
      motorBL.setSpeed(SlideSpeed);
      motorBR.setSpeed(SlideSpeed);

      //While the vehicle is cockeyed with the front to the left...
      while(analogRead(Sensor4) > Threshold && analogRead(Sensor1) < Threshold){
        /* Could add this as a one time thing w/ a counter if its an issue
        motorFL.run(BRAKE);
        motorFR.run(BRAKE);
        motorBL.run(BRAKE);
        motorBR.run(BRAKE);
        */
        //Rotate Counter Clockwise
        motorFL.run(BACKWARD);
        motorFR.run(FORWARD);
        motorBL.run(BACKWARD);
        motorBR.run(FORWARD);
        motorFL.setSpeed(RotateSpeed);
        motorFR.setSpeed(RotateSpeed);
        motorBL.setSpeed(RotateSpeed);
        motorBR.setSpeed(RotateSpeed);
      }
      //While the vehicle is cockeyed with the front to the Right...
      while(analogRead(Sensor4) < Threshold && analogRead(Sensor1) > Threshold){
        /*
        motorFL.run(BRAKE);
        motorFR.run(BRAKE);
        motorBL.run(BRAKE);
        motorBR.run(BRAKE);
        */
        //Rotate Clockwise
        motorFL.run(FORWARD);
        motorFR.run(BACKWARD);
        motorBL.run(FORWARD);
        motorBR.run(BACKWARD);
        motorFL.setSpeed(RotateSpeed);
        motorFR.setSpeed(RotateSpeed);
        motorBL.setSpeed(RotateSpeed);
        motorBR.setSpeed(RotateSpeed);
      }
    }
    //Continue Forward Motion
    motorFL.run(FORWARD);
    motorFR.run(FORWARD);
    motorBL.run(FORWARD);
    motorBR.run(FORWARD);
    //Consider Resetting Speed somehow b/c this way the speed will keep increasing
    //There should be a way to slow down as you approach (potentially with time or encoder.)
    motorFL.setSpeed(SpeedFL);
    motorFR.setSpeed(SpeedFR);
    motorBL.setSpeed(SpeedBL);
    motorBR.setSpeed(SpeedBR);
  }
  
  if (analogRead(Sensor7)>Threshold){
    //Increase Left Side Wheels Speed
    SpeedFL+=1*Gain;
    SpeedBL+=1*Gain;
    //Activate that increase in the wheels
    motorFL.setSpeed(SpeedFL);  
    motorBL.setSpeed(SpeedBL);
  
  }

  if (analogRead(Sensor8)>Threshold){
    //Stop!
    motorFL.run(BRAKE);
    motorFR.run(BRAKE);
    motorBL.run(BRAKE);
    motorBR.run(BRAKE);
    while(analogRead(Sensor1) < Threshold && analogRead(Sensor2) < Threshold && analogRead(Sensor3) < Threshold && analogRead(Sensor4) < Threshold){
      //Slide Right
      motorFL.run(FORWARD);
      motorFR.run(BACKWARD);
      motorBL.run(BACKWARD);
      motorBR.run(FORWARD);
      motorFL.setSpeed(SlideSpeed);
      motorFR.setSpeed(SlideSpeed);
      motorBL.setSpeed(SlideSpeed);
      motorBR.setSpeed(SlideSpeed);

      //While the vehicle is cockeyed with the front to the left...
      while(analogRead(Sensor4) > Threshold && analogRead(Sensor1) < Threshold){
        /*
        motorFL.run(BRAKE);
        motorFR.run(BRAKE);
        motorBL.run(BRAKE);
        motorBR.run(BRAKE);
        */
        //Rotate Clockwise
        motorFL.run(FORWARD);
        motorFR.run(BACKWARD);
        motorBL.run(FORWARD);
        motorBR.run(BACKWARD);
        motorFL.setSpeed(RotateSpeed);
        motorFR.setSpeed(RotateSpeed);
        motorBL.setSpeed(RotateSpeed);
        motorBR.setSpeed(RotateSpeed);
      }
      //While the vehicle is cockeyed with the front to the Right...
      while(analogRead(Sensor4) < Threshold && analogRead(Sensor1) > Threshold){
        /*
        motorFL.run(BRAKE);
        motorFR.run(BRAKE);
        motorBL.run(BRAKE);
        motorBR.run(BRAKE);
        */
        //Rotate Counter Clockwise
        motorFL.run(BACKWARD);
        motorFR.run(FORWARD);
        motorBL.run(BACKWARD);
        motorBR.run(FORWARD);
        motorFL.setSpeed(RotateSpeed);
        motorFR.setSpeed(RotateSpeed);
        motorBL.setSpeed(RotateSpeed);
        motorBR.setSpeed(RotateSpeed);
      }
    }
    //Continue Forward Motion
    motorFL.run(FORWARD);
    motorFR.run(FORWARD);
    motorBL.run(FORWARD);
    motorBR.run(FORWARD);
    //Consider Resetting Speed somehow b/c this way the speed will keep increasing
    //There should be a way to slow down as you approach (potentially with time or encoder.)
    motorFL.setSpeed(SpeedFL);
    motorFR.setSpeed(SpeedFR);
    motorBL.setSpeed(SpeedBL);
    motorBR.setSpeed(SpeedBR);
  }
  
}
