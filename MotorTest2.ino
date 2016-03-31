#include <AFMotor.h>

#define SlideSpeed 200
//Constants for Encoder
volatile int FL_sig=0;
volatile int FR_sig=0;
volatile int BL_sig=0;
volatile int BR_sig=0;

volatile int FLpulses=0;
volatile int FRpulses=0;
volatile int BLpulses=0;
volatile int BRpulses=0;

//Setup the Motor(s)
AF_DCMotor motorFL(1,MOTOR12_64KHZ);
AF_DCMotor motorFR(2,MOTOR12_64KHZ);
AF_DCMotor motorBL(3,MOTOR12_64KHZ);
AF_DCMotor motorBR(4,MOTOR12_64KHZ);

//Initialize interrupt service routines
void FL_Change();
void FR_Change();
void BL_Change();
void BR_Change();

void setup() {
  //Sets up interrupt pins as inputs
  pinMode(18,INPUT);
  pinMode(19,INPUT);
  pinMode(20,INPUT);
  pinMode(21,INPUT);

/*  //Outputs 5v to the encoder
  pinMode(31,OUTPUT);
  pinMode(33,OUTPUT);
  pinMode(35,OUTPUT);
  pinMode(37,OUTPUT);
  digitalWrite(31,HIGH);
  digitalWrite(33,HIGH);
  digitalWrite(35,HIGH);
  digitalWrite(37,HIGH);
*/ 
  Serial.begin(250000); //Really fast to catch every encoder edge
 
  //Sketch title
  Serial.println("Drive In a Square");
  delay(10000);

}

void loop() {

  //All four wheels running forard (Vehicle in Drive)
  Serial.println("Forward Command");
  motorFL.run(FORWARD);
  motorFR.run(FORWARD);
  motorBL.run(FORWARD);
  motorBR.run(FORWARD);
  for (int i=0; i<255;i++){
  motorFL.setSpeed(i);
  motorFR.setSpeed(i);
  motorBL.setSpeed(i);
  motorBR.setSpeed(i);
  delay(10);
  }
  for (int i=255;i>0;i--){
  motorFL.setSpeed(i);
  motorFR.setSpeed(i);
  motorBL.setSpeed(i);
  motorBR.setSpeed(i);
  delay(10);
  }
/*
  while (FLpulses<1000){
  //Starts counting
  attachInterrupt(digitalPinToInterrupt(18),FL_Change,CHANGE); 
//  attachInterrupt(digitalPinToInterrupt(19),FR_Change,CHANGE);
//  attachInterrupt(digitalPinToInterrupt(20),BL_Change,CHANGE);
//  attachInterrupt(digitalPinToInterrupt(21),BR_Change,CHANGE);
  Serial.println(FLpulses);

  }
*/
  motorFL.run(BRAKE);
  motorFR.run(BRAKE);
  motorBL.run(BRAKE);
  motorBR.run(BRAKE);
  //Detaches the Interrupts
//  detachInterrupt(digitalPinToInterrupt(18));
//  detachInterrupt(digitalPinToInterrupt(19));
//  detachInterrupt(digitalPinToInterrupt(20));
//  detachInterrupt(digitalPinToInterrupt(21));


  FLpulses=0;
  FRpulses=0;
  BLpulses=0;
  BRpulses=0;
  
  //Wait three seconds to Strafe Right
/*  delay(3000);

  motorFL.run(BACKWARD);
  motorFR.run(FORWARD);
  motorBL.run(FORWARD);
  motorBR.run(BACKWARD);
  motorFL.setSpeed(100);
  motorFR.setSpeed(100);
  motorBL.setSpeed(100);
  motorBR.setSpeed(100);

  while(FLpulses<1000){
  attachInterrupt(digitalPinToInterrupt(18),FL_Change,CHANGE); 
//  attachInterrupt(digitalPinToInterrupt(19),FR_Change,CHANGE);
//  attachInterrupt(digitalPinToInterrupt(20),BL_Change,CHANGE);
//  attachInterrupt(digitalPinToInterrupt(21),BR_Change,CHANGE);
  }
  motorFL.run(BRAKE);
  motorFR.run(BRAKE);
  motorBL.run(BRAKE);
  motorBR.run(BRAKE);
  detachInterrupt(digitalPinToInterrupt(18));
//  detachInterrupt(digitalPinToInterrupt(19));
//  detachInterrupt(digitalPinToInterrupt(20));
//  detachInterrupt(digitalPinToInterrupt(21));

  FLpulses=0;
  FRpulses=0;
  BLpulses=0;
  BRpulses=0;
*/
  //Wait three seconds to slide right
  delay(3000);

 Serial.println("Slide Right Command");
  motorFL.run(FORWARD);
  motorFR.run(BACKWARD);
  motorBL.run(BACKWARD);
  motorBR.run(FORWARD);
  motorFL.setSpeed(SlideSpeed);
  motorFR.setSpeed(SlideSpeed);
  motorBL.setSpeed(SlideSpeed);
  motorBR.setSpeed(SlideSpeed);

  while(FLpulses<6000){
  attachInterrupt(digitalPinToInterrupt(18),FL_Change,CHANGE); 
//  attachInterrupt(digitalPinToInterrupt(19),FR_Change,CHANGE);
//  attachInterrupt(digitalPinToInterrupt(20),BL_Change,CHANGE);
//  attachInterrupt(digitalPinToInterrupt(21),BR_Change,CHANGE);
  }
  motorFL.run(BRAKE);
  motorFR.run(BRAKE);
  motorBL.run(BRAKE);
  motorBR.run(BRAKE);
  detachInterrupt(digitalPinToInterrupt(18));
/*
//  detachInterrupt(digitalPinToInterrupt(19));
//  detachInterrupt(digitalPinToInterrupt(20));
//  detachInterrupt(digitalPinToInterrupt(21));
*/

  FLpulses=0;
  FRpulses=0;
  BLpulses=0;
  BRpulses=0;

delay(3000);
  Serial.println("Backward Command");
  motorFL.run(BACKWARD);
  motorFR.run(BACKWARD);
  motorBL.run(BACKWARD);
  motorBR.run(BACKWARD);
  for (int i=0; i<255;i++){
  motorFL.setSpeed(i);
  motorFR.setSpeed(i);
  motorBL.setSpeed(i);
  motorBR.setSpeed(i);
  delay(10);
  }
  for (int i=255;i>0;i--){
  motorFL.setSpeed(i);
  motorFR.setSpeed(i);
  motorBL.setSpeed(i);
  motorBR.setSpeed(i);
  delay(10);
  }
  //Wait three seconds strafe left
  delay(3000);

  FLpulses=0;
  FRpulses=0;
  BLpulses=0;
  BRpulses=0;

  Serial.println("Slide Left");
  motorFL.run(BACKWARD);
  motorFR.run(FORWARD);
  motorBL.run(FORWARD);
  motorBR.run(BACKWARD);
  motorFL.setSpeed(SlideSpeed);
  motorFR.setSpeed(SlideSpeed);
  motorBL.setSpeed(SlideSpeed);
  motorBR.setSpeed(SlideSpeed);

  while(FLpulses<6000){
  attachInterrupt(digitalPinToInterrupt(18),FL_Change,CHANGE); 
//  attachInterrupt(digitalPinToInterrupt(19),FR_Change,CHANGE);
//  attachInterrupt(digitalPinToInterrupt(20),BL_Change,CHANGE);
//  attachInterrupt(digitalPinToInterrupt(21),BR_Change,CHANGE);
  }
  motorFL.run(BRAKE);
  motorFR.run(BRAKE);
  motorBL.run(BRAKE);
  motorBR.run(BRAKE);
  detachInterrupt(digitalPinToInterrupt(18));
//  detachInterrupt(digitalPinToInterrupt(19));
//  detachInterrupt(digitalPinToInterrupt(20));
//  detachInterrupt(digitalPinToInterrupt(21));

  delay(100);

}


//FUNCTION DEFENITIONS
//-----------------------------------------------------------
void FL_Change(){
  detachInterrupt(digitalPinToInterrupt(18));
  FLpulses++;
  attachInterrupt(digitalPinToInterrupt(18),FL_Change,CHANGE);
}

void FR_Change(){
  detachInterrupt(digitalPinToInterrupt(19));
  FRpulses++;
  attachInterrupt(digitalPinToInterrupt(19),FR_Change,CHANGE);
}

void BL_Change(){
  detachInterrupt(digitalPinToInterrupt(20));
  BLpulses++;
  attachInterrupt(digitalPinToInterrupt(20),BL_Change,CHANGE);
  
}

void BR_Change(){
  detachInterrupt(digitalPinToInterrupt(21));
  BRpulses++;
  attachInterrupt(digitalPinToInterrupt(21),BR_Change,CHANGE);
  
}


