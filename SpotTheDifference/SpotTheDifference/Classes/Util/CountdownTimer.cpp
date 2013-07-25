//
//  CountdownTimer.cpp
//  SpotTheDifference
//
//  Created by allenhmo1254 on 13-7-25.
//
//

#include "CountdownTimer.h"


CountdownTimer::CountdownTimer():
isFinished_(false),
delay_(0.0f),
dircetor_(NULL),
time_(0)
{
    
}


CountdownTimer* CountdownTimer::create()
{
    CountdownTimer* temp=new CountdownTimer();
    temp->init();
    temp->autorelease();
    return temp;
}


bool CountdownTimer::init()
{
    resetTime();
    dircetor_ = cocos2d::CCDirector::sharedDirector();
    return true;
}


int CountdownTimer::time()
{
    return time_;
}


int CountdownTimer::hour()
{
    return time_ / 3600;
}


int CountdownTimer::minute()
{
    return (time_ % 3600) / 60;
}


int CountdownTimer::second()
{
    return (time_ % 3600) % 60;;
}


bool CountdownTimer::isFinished()
{
    return isFinished_;
}


void CountdownTimer::setTime(int hour,int minute,int second)
{
    time_ = hour * 3600 + minute * 60 + second;
    delay_ = 0;
    isFinished_ = false;
}


void CountdownTimer::setTime(long  time)
{
    time_ = time;
    delay_ = 0;
    isFinished_ = false;
}


void CountdownTimer::resetTime()
{
    time_ = 0;
    delay_ = 0;
    isFinished_ = true;
}

void CountdownTimer::setIsFinished(bool isFinished)
{
    isFinished_ = isFinished;
    if (isFinished_) {
        time_ = 0;
        delay_ = 0;
    }
}


void CountdownTimer::process()
{
    if (!isFinished_) {
        delay_ += dircetor_->dtTime();
        if (delay_ >= 1.0f) {
            delay_ = 0;
            if (--time_ <= 0) {
                resetTime();
            }
        }
    }
}

