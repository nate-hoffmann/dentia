
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
            nextState = SENSOR_READ;
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
            //Speed Change
                if (sonarFront.ping()/US_ROUNDTRIP_CM<60)
                {
                    speed = 190;
                    if (sonarFront.ping()/US_ROUNDTRIP_CM<50)
                    {
                        speed = 180;
                        if (sonarFront.ping()/US_ROUNDTRIP_CM<40)
                        {
                            speed = 170;
                            if (sonarFront.ping()/US_ROUNDTRIP_CM<30)
                            {
                                speed = 160;
                                if (sonarFront.ping()/US_ROUNDTRIP_CM<30)
                                {
                                    speed = 150;
                                    if (sonarFront.ping()/US_ROUNDTRIP_CM<20)
                                    {
                                        speed = 140;
                                        if (sonarFront.ping()/US_ROUNDTRIP_CM<10)
                                        {
                                            speed = 100;
                                        }
                                    }
                                }
                            }
                        }
                    }
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
            nextState=GO_FORWARD;
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

void MyBotAction::Rotate(int dir, int Location)
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
                Check=bottyMap.CheckLocation(Location);
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

