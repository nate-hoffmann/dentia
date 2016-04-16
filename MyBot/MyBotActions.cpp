
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
//
//        //Prepares bot class
//        MyBotMotors bottyMots;
//        //Prepare Line Sensor to be read
//        SensorBar FrontSensorBar(LineSensorFrontADD);
//        //Prepares sonar sensors to be read
//        NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
//        
//        uint8_t state = GO_FORWARD;
//        int Check=0;
//        int x1;
//        while(Check<Input)
//        {
//            uint8_t nextState = state;
//            
//            switch (state) {
//                    
//            case SENSOR_READ:
//            
//            if (FrontSensorBar.getDensity()<3)
//            {
//                    nextState = GO_FORWARD;
//                    if( FrontSensorBar.getPosition() < -30 )
//                    {
//                        nextState = GO_LEFT;
//                    }
//                    if( FrontSensorBar.getPosition() > 30 )
//                    {
//                        nextState = GO_RIGHT;
//                    }
//                    
//            }
//            else()
//            {
//                Check++;
//                nextState = GO_FORWARD
//            }
//            
//            break;
//        case GO_FORWARD:
//            x1=sonarFront.ping()/US_ROUNDTRIP_CM;
//            if (x1<50);
//            {
//                bottyMots.Drive(1,255-4*x1);
//            }
//            else();
//            bottyMots.Drive(1,200);
//            nextState = SENSOR_READ;
//            
//            break;
//        case GO_LEFT:
//            
//            bottyMots.Slide(0,200);
//            nextState = SENSOR_READ;
//            
//            break;
//        case GO_RIGHT:
//            
//            bottyMots.Slide(1,200);
//            nextState = SENSOR_READ;
//            
//            break;
//        default:
//            //   motors.stop();       // Stops both motors
//            bottyMots.Stop();
//            break;
//        }
//        state = nextState;
//    }
//    return;
    
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
    while(Check<10)
    {
        uint8_t nextState = state;

        switch (state) {

            case SENSOR_READ:

                nextState = GO_FORWARD;
                if( FrontSensorBar.getPosition() < -30 )
                {
                    nextState = GO_LEFT;
                }
                if( FrontSensorBar.getPosition() > 30 )
                {
                    nextState = GO_RIGHT;
                }
                if (sonarFront.ping()/US_ROUNDTRIP_CM<5)
                {
                    bottyMots.Stop();
                    Check++;
                }
                
                break;
            case GO_FORWARD:
                x1=sonarFront.ping()/US_ROUNDTRIP_CM;
                if (x1<50)
                {
                bottyMots.Drive(1,4*x1+50);
                }
                else
                {
                bottyMots.Drive(1,200);
                }
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
            default:
                //   motors.stop();       // Stops both motors
                bottyMots.Stop();
                break;
        }
        state = nextState;
    }
    
}

