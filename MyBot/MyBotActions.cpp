
#include "MyBot.h"
#include "Arduino.h"


MyBotAction::MyBotAction()
{
    
}


void MyBotAction::DriveToLine(int dir, int spee, uint8_t input)
{
    //Prepares bot class
    MyBotMotors bottyMots;
    //Prepare Line Sensor to be read
    SensorBar mySensorBar(LineSensorADD);// Instantiate the motor control object. This only needs to be done once.
    //Prepares sonar sensors to be read
    NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
    NewPing sonarRight(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);
    NewPing sonarBack(TRIGGER_PIN_BACK, ECHO_PIN_BACK);
    NewPing sonarLeft(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
    
    uint8_t stopper = 0;
    uint8_t state = GO_FORWARD;
    while(stopper<input)
    {
    uint8_t nextState = state;
    switch (state) {
        case IDLE_STATE:
            //   motors.stop();       // Stops both motors
            bottyMots.Stop();
            nextState = SENSOR_READ;
            Serial.println("IDLE");
            stopper ++;
            break;
        case SENSOR_READ:
            if (stopper < input)
            {
                if( mySensorBar.getDensity() < 3 )
                {
                    nextState = GO_FORWARD;
                    if( mySensorBar.getPosition() < -20 )
                    {
                        nextState = GO_LEFT;
                    }
                    if( mySensorBar.getPosition() > 20 )
                    {
                        nextState = GO_RIGHT;
                    }
                    Serial.println(mySensorBar.getPosition());
                }
                else
                {
                    nextState = IDLE_STATE;
                }
            }
            else
            {
                nextState = IDLE_STATE;
            }
            Serial.println("READ");
            break;
        case GO_FORWARD:
            //   driveBot(200);
            if (stopper < input)
            {
                bottyMots.Drive(1,200);
                nextState = SENSOR_READ;
            }
            else
            {
                nextState = IDLE_STATE;
            }
            break;
        case GO_LEFT:
            if (stopper < input)
            {
                //    turnBot(-.75);
                bottyMots.Turn(0);
                nextState = SENSOR_READ;
            }
            else
            {
                nextState = IDLE_STATE;
            }
            break;
        case GO_RIGHT:
            //    turnBot(.75);
            if (stopper < input)
            {
                bottyMots.Turn(1);
                nextState = SENSOR_READ;
            }
            else
            {
                nextState = IDLE_STATE;
            }
            Serial.println("RIGHT");
            break;
        default:
            //   motors.stop();       // Stops both motors
            bottyMots.Stop();
            break;
    }
    state = nextState;
    }
    
}

void MyBotAction::Rotate(int dir, int input)
{
    //Prepares bot class
    MyBotMotors bottyMots;
    //Prepare Line Sensor to be read
    SensorBar mySensorBar(LineSensorADD);// Instantiate the motor control object. This only needs to be done once.
    //Prepares sonar sensors to be read
    NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
    NewPing sonarRight(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);
    NewPing sonarBack(TRIGGER_PIN_BACK, ECHO_PIN_BACK);
    NewPing sonarLeft(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
    
    int count;
    uint8_t stopper = 0;
    uint8_t state = ROTATE;
    while (stopper < input)
    {
        // put your main code here, to run repeatedly:
        
        uint8_t nextState = state;
        switch (state) {
            case IDLE_STATE:
                if (count < 2){
                    bottyMots.Pivot(dir,200);
                    nextState = SENSOR_READ;
                }
                else{
                    bottyMots.Brake();
                    nextState = SENSOR_READ;
                    stopper++;
                }
                break;
            case SENSOR_READ:
                if( mySensorBar.getDensity() < 4 || count > 10 )
                {
                    nextState = ROTATE;
                }
                else
                {
                    nextState=IDLE_STATE;
                }
                break;
            case ROTATE:
                //   driveBot(200);
                bottyMots.Pivot(dir,200);
                nextState = SENSOR_READ;
                break;
            default:
                //   motors.stop();       // Stops both motors
                bottyMots.Stop();
                break;
        }
        count++;
        state = nextState;
        delay(100);
    }
    
}

