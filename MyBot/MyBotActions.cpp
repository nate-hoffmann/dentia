
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
                    bottyMap.GoToLocation(Location);
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
                    if (abs(sonarFront.ping_median(10)/US_ROUNDTRIP_CM-RIGHT)<ERROR+5)
                    {
                        Check=0;
                    }
                }
                if (Orientation == LEFT)
                {
                    if (abs(sonarFront.ping_median(10)/US_ROUNDTRIP_CM-LEFT)<ERROR+5)
                    {
                        Check=0;
                    }
                }
                if (Orientation == FRONT)
                {
                    if (abs(sonarLeft.ping_median(10)/US_ROUNDTRIP_CM-FRONT)<ERROR+5)
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

