//
//  MyBotMap.cpp
//
//
//  Created by Tyler White on 4/11/16.
//
//

#include "MyBot.h"
#include "Arduino.h"


int* MyBotMap::WhatLocation(int Location)
{
    int* LRF[3];
    switch(Location)
    {
        case PrimaryRight:
            LRF[0]=0;
            LRF[1]=PrimaryRightPeg;
            LRF[2]=4;
            break;
        case PrimaryLeft:
            LRF[0]=PrimaryLeftPeg;
            LRF[1]=0;
            LRF[2]=4;
            break;
        case PrimaryCenter:
            LRF[0]=PrimaryMiddlePegLeft;
            LRF[1]=PrimaryMiddlePegRight;
            LRF[2]=4;
            break;
        case CenterLeft:
            LRF[0]=0;
            LRF[1]=0;
            LRF[2]=CenterLEFTFront;
            break;
        case CenterRight:
            LRF[0]=0;
            LRF[1]=0;
            LRF[2]=CenterRIGHTFront;
            break;
        case CenterForward:
            LRF[0]=CenterFWDLeft;
            LRF[1]=CenterFWDRight;
            LRF[2]=0;
            break;
        case SecondaryRight:
            LRF[0]=0;;
            LRF[1]=SecondaryRightPeg;
            LRF[2]=4;
            break;
        case SecondaryLeft:
            LRF[0]=SecondaryLeftPeg;
            LRF[1]=0;
            LRF[2]=4;
            break;
        case SecondaryCenter:
            LRF[0]=SecondaryMiddlePegLeft;
            LRF[1]=SecondaryMiddlePegRight;
            LRF[2]=4;
            break;
        case ScoringCenter:
            LRF[0]=ScoringPegCenterLeft;
            LRF[1]=ScoringPegCenterRight;
            LRF[2]=4;
            break;
        case ScoringRight:
            LRF[0]=0;
            LRF[1]=ScoringPegRight;
            LRF[2]=4;
            break;
        case ScoringLeft:
            LRF[0]=ScoringPegLeft;
            LRF[1]=0;
            LRF[2]=4;
            break;
    }
    return LRF;
    
}
int MyBotMap::CheckLocation(int Location)
{
    MyBotMap bottyMap;
    //Get Coordinates of Locatio of interest
    int* LRF = bottyMap.WhatLocation(Location);
    //Initialize all Sonar Sensors
    NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
    NewPing sonarRight(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);
    NewPing sonarBack(TRIGGER_PIN_BACK, ECHO_PIN_BACK);
    NewPing sonarLeft(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
    
    int CurLeft;
    int CurRight;
    int CurFront;
    uint8_t LeftCount = 0;
    uint8_t RightCount = 0;
    uint8_t FrontCount = 0;
    int i;
    
    //Pole all sonar sensor of interest
    for (i=0;i<10;i++)
    {
        
        //Check for any zero values
        if (LRF[0]>0)
        {
            if(abs((sonarLeft.ping()/US_ROUNDTRIP_CM)-LRF[0])<ERROR)
            {
                LeftCount++;
            }
        }
        if (LRF[1]>0)
        {
            if(abs((sonarRight.ping()/US_ROUNDTRIP_CM)-LRF[1])<ERROR)
            {
                RightCount++;
            }
        }
        if (LRF[2]>0)
        {
            if(abs((sonarFront.ping()/US_ROUNDTRIP_CM)-LRF[2])<ERROR)
            {
                FrontCount++;
            }
        }
        
    }
    
    if (FrontCount>5||LRF[2]==0)
    {
        if (RightCount>5||LRF[1]==0)
        {
            if (LeftCount>5|LRF[0]==0)
            {
                return 0;
            }
        }
    }
    else
    {
        return 1;
    }
    
}

int MyBotMap::GoToLocation(int Location)
{
    //Initialize sensor ints
    int x1=0; int x2=0; int x3=0;
    
    
    // Get coordinates from location
    MyBotMap bottyMap;
    int* LRF = bottyMap.WhatLocation(Location);
    
    MyBotMotors bottyMots;
    //Initialize sonar sensors
    NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
    NewPing sonarRight(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);
    NewPing sonarBack(TRIGGER_PIN_BACK, ECHO_PIN_BACK);
    NewPing sonarLeft(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
    
    uint8_t state = SENSOR_READ;
    
    //Drve the sonar sensor readings to the coordinates of the desired location
    while (abs(x1)>ERROR && abs(x2)>ERROR && abs(x3)>ERROR)
    {
        uint8_t nextState=state;
        switch (state)
        {
                
            case SENSOR_READ:
                //Check for any zero values and get coordinate difference from sensors of interest (non zero coordinates)
                if (LRF[0]>0)
                {
                    x1=sonarLeft.ping_median(20)-LRF[0];
                }
                else
                {
                    x1=0;
                }
                
                if (LRF[1]>0)
                {
                    x2=sonarRight.ping_median(20)-LRF[1];
                }
                else
                {
                    x2=0;
                }
                if (LRF[2]>0)
                {
                    x3=sonarFront.ping_median(20)-LRF[2];
                }
                else
                {
                    x3=0;
                }
                nextState=MANEUVER;
                break;
            case MANEUVER:
                //Based on the difference make some maneuvers to bring the two values closer together.
                
                //Which is the furthest off of the sensors of interest?
                if (abs(x1)>abs(x2)&&abs(x1)>abs(x3))
                {
                    //Positive or Negative
                    if (x1>0)
                    {
                        //Speed Check
                        if (abs(x1)<70)
                        {
                            bottyMots.Slide(0,200);
                            if (abs(x1)<60)
                            {
                                bottyMots.Slide(0,180);
                                if (abs(x1)<40)
                                {
                                    bottyMots.Slide(0,160);
                                    if (abs(x1)<ERROR)
                                    {
                                        bottyMots.Stop();
                                    }
                                }
                            }
                            
                        }
                    }
                    else
                    {
                        if (abs(x1)<70)
                        {
                            bottyMots.Slide(1,200);
                            if (abs(x1)<60)
                            {
                                bottyMots.Slide(1,180);
                                if (abs(x1)<40)
                                {
                                    bottyMots.Slide(1,160);
                                    if (abs(x1)<ERROR)
                                    {
                                        bottyMots.Stop();
                                    }
                                }
                            }
                            
                        }
                    }
                }
                else if(abs(x2)>abs(x1)&&abs(x2)>abs(x3))
                {
                    if (x2>0)
                    {
                        if (abs(x2)<70)
                        {
                            bottyMots.Slide(1,200);
                            if (abs(x2)<60)
                            {
                                bottyMots.Slide(1,180);
                                if (abs(x2)<40)
                                {
                                    bottyMots.Slide(1,160);
                                    if (abs(x2)<ERROR)
                                    {
                                        bottyMots.Stop();
                                    }
                                }
                            }
                            
                        }
                    }
                    else
                    {
                        if (abs(x2)<70)
                        {
                            bottyMots.Slide(0,200);
                            if (abs(x2)<60)
                            {
                                bottyMots.Slide(0,180);
                                if (abs(x2)<40)
                                {
                                    bottyMots.Slide(0,160);
                                    if (abs(x2)<ERROR)
                                    {
                                        bottyMots.Stop();
                                    }
                                }
                            }
                            
                        }
                    }
                }
                else
                {
                    if (abs(x3)>0)
                    {
                        if (abs(x3)<30)
                        {
                            bottyMots.Drive(1,200);
                            if (abs(x3)<20)
                            {
                                bottyMots.Drive(1,180);
                                if (abs(x3)<10)
                                {
                                    bottyMots.Drive(1,160);
                                    if (abs(x3)<ERROR)
                                    {
                                        bottyMots.Stop();
                                    }
                                }
                            }
                            
                        }
                    }
                    else
                    {
                        if (abs(x3)<30)
                        {
                            bottyMots.Drive(0,200);
                            if (abs(x3)<20)
                            {
                                bottyMots.Drive(0,180);
                                if (abs(x3)<10)
                                {
                                    bottyMots.Drive(0,160);
                                    if (abs(x3)<ERROR)
                                    {
                                        bottyMots.Stop();
                                    }
                                }
                            }
                            
                        }
                    }
                }
                nextState = SENSOR_READ;
                break;
                
        }
        
    }
}