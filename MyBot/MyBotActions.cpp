
#include "MyBot.h"
#include "Arduino.h"


MyBotAction::MyBotAction()
{
    
}


void MyBotAction::DriveToLocation(int dir, int spee, int Location)
{
    //Prepares bot class
    MyBotMotors bottyMots;
    MyBotMap bottyMap;
    //Prepare Line Sensor to be read
    SensorBar FrontSensorBar(LineSensorFrontADD);// Instantiate the motor control object. This only needs to be
    SensorBar BackSensorBar(LineSensorBackADD);
    //Prepares sonar sensors to be read
    NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
    NewPing sonarRight(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);
    NewPing sonarBack(TRIGGER_PIN_BACK, ECHO_PIN_BACK);
    NewPing sonarLeft(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
    
    uint8_t state = GO_FORWARD;
    int Check=1;
    int speed=spee;
    while(Check==1)
    {
        uint8_t nextState = state;
        speed = spee;
        switch (state) {
            case IDLE_STATE:
                //   motors.stop();       // Stops both motors
                bottyMots.Stop();
                nextState = CHECK_FINAL;
                Serial.println("IDLE");
                
                break;
            case SENSOR_READ:
                if( FrontSensorBar.getDensity() < 3 )
                {
                    nextState = GO_FORWARD;
                    if( FrontSensorBar.getPosition() < -30 )
                    {
                        nextState = GO_LEFT;
                    }
                    if( FrontSensorBar.getPosition() > 30 )
                    {
                        nextState = GO_RIGHT;
                    }
                    Serial.println(FrontSensorBar.getPosition());
                }
                else if(FrontSensorBar.getDensity() == 0)
                {
                    nextState = CHECK_FINAL;
                }
                else
                {
                    nextState = CHECK_FINAL;
                }
                if (sonarFront.ping()/US_ROUNDTRIP_CM<5)
                {
                    bottyMots.Brake();
                    nextState = CHECK_FINAL;
                }
                
                break;
            case GO_FORWARD:
                
                bottyMots.Drive(dir,200);
                nextState = SENSOR_READ;
                
                break;
            case GO_LEFT:
                
                bottyMots.Slide(0,200);
                nextState = SENSOR_READ;
                
                break;
            case GO_RIGHT:
                
                bottyMots.Slide(1,200);
                nextState = SENSOR_READ;
                
                break;
            case CHECK_FINAL:
                bottyMots.Stop();
                Check=bottyMap.CheckLocation(Location);
                if (Check == 1)
                {
                    Check=bottyMap.GoToLocation(Location);
                }
                nextState=IDLE_STATE;
                break;
            default:
                //   motors.stop();       // Stops both motors
                bottyMots.Stop();
                break;
        }
        state = nextState;
    }
    return;
    
}

//Function works best when in the middle of the course.  Use follow lines and other functions to get to the center, then orient.
void MyBotAction::Orient(int dir, int Orientation)
{
    //Prepares bot class
    MyBotMap bottyMap;
    MyBotMotors bottyMots;
    //Prepare Line Sensor to be read
    SensorBar FrontSensorBar(LineSensorFrontADD);// Instantiate the motor control object. This only needs to be
    SensorBar BackSensorBar(LineSensorBackADD);
    //Prepares sonar sensors to be read
    NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
    NewPing sonarRight(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);
    NewPing sonarBack(TRIGGER_PIN_BACK, ECHO_PIN_BACK);
    NewPing sonarLeft(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
    
    
    int Check = 1;
    uint8_t state = ROTATE;
    while (Check == 1)
    {
        // put your main code here, to run repeatedly:
        
        uint8_t nextState = state;
        switch (state) {
            case IDLE_STATE:
                
                bottyMots.Brake();
                nextState = CHECK_FINAL;
                break;
                
            case ROTATE:
                //   driveBot(200);
                bottyMots.Pivot(dir,200);
                nextState = CHECK_FINAL;
                
                break;
            case CHECK_FINAL:
                if (Orientation == RIGHT)
                {
                    if (abs(sonarFront.ping()/US_ROUNDTRIP_CM-RIGHT)<ERROR+5)//Do some analysis to get this number
                    {
                        Check=0;
                    }
                }
                if (Orientation == LEFT)
                {
                    if (abs(sonarFront.ping()/US_ROUNDTRIP_CM-LEFT)<ERROR+5)
                    {
                        Check=0;
                    }
                }
                if (Orientation == FRONT)
                {
                    if (abs(sonarLeft.ping()/US_ROUNDTRIP_CM-FRONT)<ERROR+5)
                    {
                        Check=0;
                    }
                }
                nextState=ROTATE;
                break;
            default:
                //   motors.stop();       // Stops both motors
                bottyMots.Stop();
                break;
        }
        state = nextState;
    }
    return;
}

void MyBotAction::ClawMove(int dir)
{
    //Initialize sonar for grabber
    NewPing sonarBack(TRIGGER_PIN_BACK, ECHO_PIN_BACK);
    //Initiate servo on pin 9
    Servo servo1;
    servo1.attach(9);
    Serial.println("ClawMove");
    
    if (dir == 1) //Down and clamp
    {
        uint8_t state = GO_DOWN;
        
        //Moves the arm down to the correct heigh to 1cm accuracy using sonar
        while (abs(sonarBack.ping()/US_ROUNDTRIP_CM-DOWN)>ERROR1)
        {
            uint8_t nextState = state;
            switch(state)
            {
                case SENSOR_READ: //Reads the sonar distance and decides to move up or down
                    //if closer to the bottom then supposed to be
  //                  delay(50);
                    if(sonarBack.ping()/US_ROUNDTRIP_CM>DOWN)
                    {
                        nextState = GO_UP;
                        Serial.println("GO_UP");
                    }
                    else//Higher from the bottom than supposed to be
                    {
                        nextState = GO_DOWN;
                        Serial.println("GO_DOWN");
                    }
                    
                    break;
                case GO_DOWN: //Moves down
                    digitalWrite(MotorDriverInA1,LOW);
                    digitalWrite(MotorDriverInA2,HIGH);
                    analogWrite(MotorDriverPWM,255);
                    delay(10);
                    analogWrite(MotorDriverPWM,0);
                    nextState = SENSOR_READ;
                    Serial.println("WENT_DOWN");

                    break;
                case GO_UP: //Moves up
                    digitalWrite(MotorDriverInA1,HIGH);
                    digitalWrite(MotorDriverInA2,LOW);
                    analogWrite(MotorDriverPWM,255);
                    delay(10);
                    analogWrite(MotorDriverPWM,0);
                    nextState = SENSOR_READ;
                    Serial.println("WENT_UP");

                    break;
            }
            state=nextState;
        }
        
        servo1.write(90);//Close Grabber
    }
    else
    {
    uint8_t state = GO_UP;
    
    while (abs(sonarBack.ping()/US_ROUNDTRIP_CM-UP)>ERROR1)
    {
        uint8_t nextState = state;
        switch(state)
        {
            case SENSOR_READ:
//                delay(50);
                if(sonarBack.ping()/US_ROUNDTRIP_CM<UP)
                {
                    nextState = GO_UP;
                }
                else
                {
                    nextState = GO_DOWN;
                }
                break;
            case GO_DOWN:
                digitalWrite(MotorDriverInA1,LOW);
                digitalWrite(MotorDriverInA2,HIGH);
                analogWrite(MotorDriverPWM,255);
                delay(10);
                analogWrite(MotorDriverPWM,0);
                nextState = SENSOR_READ;
                Serial.println("WENT_DOWN");

                break;
            case GO_UP:
                digitalWrite(MotorDriverInA1,HIGH);
                digitalWrite(MotorDriverInA2,LOW);
                analogWrite(MotorDriverPWM,255);
                delay(10);
                analogWrite(MotorDriverPWM,0);
                nextState = SENSOR_READ;
                Serial.println("WENT_UP");

                break;
        }
        state=nextState;
    }
        servo1.write(0); // Open Grabber
    }
}

