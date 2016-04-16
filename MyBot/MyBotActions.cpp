
#include "MyBot.h"
#include "Arduino.h"


MyBotAction::MyBotAction()
{
    // drive forward, past mid intersection
    
    // get to wall and line up with center peg
    
    // grab rings
    
    // reverse to mid intersection
    
    // turn 90 deg CCW
    
    // get to center scoring peg
}

/* assuming that we are beginning at the start location of competition */
void MyBotAction::DriveToCenter(int dir)
{

        //Prepares bot class
        MyBotMotors bottyMots;
        //Prepare Line Sensor to be read
        SensorBar FrontSensorBar(LineSensorFrontADD);
        FrontSensorBar.clearBarStrobe();
        //Prepares sonar sensors to be read
        NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
        
        uint8_t state = GO_FORWARD;
        int Check=0;
        int x1;
    
        while(Check==0)
        {
            uint8_t nextState = state;
            
            switch (state) {
                    Serial.println("in switch statement");
                case SENSOR_READ:
                    Serial.println("sensor read");
                    
                    if (FrontSensorBar.getDensity() < 3)
                    {
                        Serial.println("light reading");
                        
                            nextState = GO_FORWARD;
                            if( FrontSensorBar.getPosition() < -35 )
                            {
                                Serial.println("sensor says right");
                                nextState = GO_RIGHT;
                            }
                            if( FrontSensorBar.getPosition() > 35 )
                            {
                                Serial.println("sensor says left");
                                nextState = GO_LEFT;
                            }
                    }
                    else
                    {
                        Serial.println("dense reading");
                        Check = 1;
                        break;
                        
                        if (FrontSensorBar.getDensity()>3 && sonarFront.ping()/US_ROUNDTRIP_CM>20)
                        {
                            
                            Check = 1;
                            
                        }
                    }
                    
                    
                    break;
                case GO_FORWARD:
                    Serial.println("go forward (backwards)");
                    
                    x1=sonarFront.ping()/US_ROUNDTRIP_CM;
                    Serial.println("X1:  " + x1);
                    
                    if (x1<55 && x1!=0)
                    {
                        bottyMots.Drive(dir,140-2*x1);
                    }
                    else if (x1>55 && x1<70)
                    {
                        if (dir == 1)
                        {
                            bottyMots.Drive(0,50);
                        }
                        else
                        {
                            bottyMots.Drive(1,50);
                        }
                    }
                    else
                    {
                
                        bottyMots.Drive(dir,70);
                    }
                    
                    bottyMots.Drive(dir, 100);
                    if (FrontSensorBar.getDensity()>3 && sonarFront.ping()/US_ROUNDTRIP_CM>20)
                    {

                        Check = 1;
                            
                    }
                    nextState = SENSOR_READ;
                    break;
                case GO_LEFT:
                    
                    Serial.println("go left case");
                    
                    bottyMots.Slide(1,SlideSpeed);
                    bottyMots.Stop();
                    nextState = SENSOR_READ;
                    if (FrontSensorBar.getDensity()>3 && sonarFront.ping()/US_ROUNDTRIP_CM>20)
                    {
                        
                        Check = 1;
                        
                    }
                    
                    break;
                case GO_RIGHT:
                    
                    Serial.println("go right case");
                    
                    bottyMots.Slide(0,SlideSpeed);
                    bottyMots.Stop();
                    nextState = SENSOR_READ;
                    if (FrontSensorBar.getDensity()>3 && sonarFront.ping()/US_ROUNDTRIP_CM>20)
                    {
                        
                        Check = 1;
                        
                    }
                    
                    break;
                default:
                    //   motors.stop();       // Stops both motors
                    
                    Serial.println("stop");
                    
                    bottyMots.Stop();
                    break;
            }
            state = nextState;
        }
    bottyMots.Stop();
    
}
    


void MyBotAction::DriveToWall()
{
    //Prepares bot class
    MyBotMotors bottyMots;
    //Prepare Line Sensor to be read
    SensorBar FrontSensorBar(LineSensorFrontADD);
    //Prepares sonar sensors to be read
    NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
    
    uint8_t state = GO_FORWARD;
    int Check=0;
    int x1;
    uint8_t rightCount;
    uint8_t leftCount;
    
    Serial.println("before state machine");
    
    while(Check < 10)
    {
        uint8_t nextState = state;

        switch (state) {

            case SENSOR_READ:

                nextState = GO_FORWARD;
                if( FrontSensorBar.getPosition() < -35 )
                {
                    Serial.println("going right");
                    nextState = GO_RIGHT;
                }
                if( FrontSensorBar.getPosition() > 35 )
                {
                    Serial.println("going left");
                    nextState = GO_LEFT;
                }
                if (sonarFront.ping()/US_ROUNDTRIP_CM<5)
                {
                    Serial.println(sonarFront.ping()/US_ROUNDTRIP_CM);
                    bottyMots.Stop();
                    Check++;
                    nextState = SENSOR_READ;
                    Serial.println("Check");
                }
                if (FrontSensorBar.getDensity()>3)
                {
                    nextState = GO_FORWARD;
                }
                
                break;
            case GO_FORWARD:
                Serial.println("going forward");
                x1=sonarFront.ping_median()/US_ROUNDTRIP_CM;
                if (x1<50)
                {
                bottyMots.Drive(1,2*x1+90);
                }
                else
                {
                bottyMots.Drive(1,150);
                }
                nextState = SENSOR_READ;
                break;
            case GO_LEFT:
                
                bottyMots.Slide(1,SlideSpeed);
                delay(30);
                bottyMots.Stop();
                nextState = SENSOR_READ;
                leftCount++;
                if (leftCount>5)
                {
                    bottyMots.Pivot(0,150);
                }
                
                break;
            case GO_RIGHT:
                
                bottyMots.Slide(0,SlideSpeed);
                delay(30);
                bottyMots.Stop();
                nextState = SENSOR_READ;
                rightCount++;
                if (rightCount>5)
                {
                    bottyMots.Pivot(1,150);
                }
                
                break;
            default:
                //   motors.stop();       // Stops both motors
                Serial.println("stopped");
                bottyMots.Stop();
                Serial.println("Check");
                break;
        }
        Serial.println("getting next state");
        state = nextState;
    }
    Serial.println("after state machine");
}

void MyBotAction::PegCenter()
{
//Prepares bot class
MyBotMotors bottyMots;
//Prepare Line Sensor to be read
SensorBar FrontSensorBar(LineSensorFrontADD);
//Prepares sonar sensors to be read
NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
    
uint8_t state = SENSOR_READ;
int Check = 0;
    unsigned long t1; unsigned long t2;
    t1=millis();
while(Check == 0)
{
    t2=millis()-t1;
    uint8_t nextState = state;
    switch (state) {
            Serial.println("in switch statement");
        case SENSOR_READ:
            if (sonarFront.ping()/US_ROUNDTRIP_CM==5)
            {
                bottyMots.Drive(1,100);
                bottyMots.Stop();
            }
            else if (sonarFront.ping()/US_ROUNDTRIP_CM==3)
            {
                bottyMots.Drive(1,100);
                bottyMots.Stop();
            }
            if( FrontSensorBar.getPosition() < -35 )
            {
                Serial.println("going right");
                nextState = GO_RIGHT;
            }
            else if( FrontSensorBar.getPosition() > 35 )
            {
                Serial.println("going left");
                nextState = GO_LEFT;
            }
            else
            {
                nextState = GO_FORWARD;
            }
            break;
            
        case GO_LEFT:
            
            bottyMots.Slide(1,SlideSpeed);
            bottyMots.Stop();
            nextState = SENSOR_READ;
            if (sonarFront.ping()/US_ROUNDTRIP_CM==5)
            {
                bottyMots.Drive(1,100);
                delay(10);
                bottyMots.Stop();
            }
            else if (sonarFront.ping()/US_ROUNDTRIP_CM==3)
            {
                bottyMots.Drive(1,100);
                delay(10);
                bottyMots.Stop();
            }
            else if (sonarFront.ping()/US_ROUNDTRIP_CM==4)
            {
                Check = 1;
            }
            break;
        case GO_RIGHT:
            
            bottyMots.Slide(0,SlideSpeed);
            bottyMots.Stop();
            nextState = SENSOR_READ;
            if (sonarFront.ping()/US_ROUNDTRIP_CM==5)
            {
                bottyMots.Drive(1,100);
                delay(10);
                bottyMots.Stop();
            }
            else if (sonarFront.ping()/US_ROUNDTRIP_CM==3)
            {
                bottyMots.Drive(1,100);
                delay(10);
                bottyMots.Stop();
            }
            else if (sonarFront.ping()/US_ROUNDTRIP_CM==4)
            {
                Check = 1;
            }
            break;
        case GO_FORWARD:
            if (sonarFront.ping()/US_ROUNDTRIP_CM==5)
            {
                bottyMots.Drive(1,100);
                delay(10);
                bottyMots.Stop();
            }
            else if (sonarFront.ping()/US_ROUNDTRIP_CM==3)
            {
                bottyMots.Drive(1,100);
                delay(10);
                bottyMots.Stop();
            }
            else if (sonarFront.ping()/US_ROUNDTRIP_CM==4)
            {
                Check = 1;
            }
            nextState = SENSOR_READ;
            break;
    }
    state = nextState;
    if(t2>3000)
    {
        break;
    }
}
}

