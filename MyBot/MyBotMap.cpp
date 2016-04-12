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
    int LRF[3];
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
    uint8_t LeftCount;
    uint8_t RightCount;
    uint8_t FrontCount;
    int i;
    
    //Take 10 Data Points from all 4 Sonar Sensors
    for (i=0;i<10;i++)
    {
        
        //Check for any zero values
        if (LRF[0]>0)
        {
            CurLeft=sonarLeft.ping()/US_ROUNDTRIP_CM;
            if(abs(CurLeft-LRF[0])<ERROR)
            {
                LeftCount++;
            }
        }
        if (LRF[1]>0)
        {
            CurRight=sonarRight.ping()/US_ROUNDTRIP_CM;
            if(abs(CurRight-LRF[1])<ERROR)
            {
                RightCount++;
            }
        }
        if (LRF[2]>0)
        {
            CurFront=sonarFront.ping()/US_ROUNDTRIP_CM;
            if(abs(CurFront-LRF[2])<ERROR)
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

void MyBotMap::GoToLocation(int Location)
{
/*
    NewPing sonarFront(TRIGGER_PIN_FRONT, ECHO_PIN_FRONT);
    NewPing sonarRight(TRIGGER_PIN_RIGHT, ECHO_PIN_RIGHT);
    NewPing sonarBack(TRIGGER_PIN_BACK, ECHO_PIN_BACK);
    NewPing sonarLeft(TRIGGER_PIN_LEFT, ECHO_PIN_LEFT);
    for (int i=0;i<10;i++)
    {
        x1=SonarFront.ping()/US_CM_CONST;
        x2=SonarLeft.ping()/US_CM_CONST;
        x3=SonarRight.ping()/US_CM_CONST;
        
        
    }
 */
}