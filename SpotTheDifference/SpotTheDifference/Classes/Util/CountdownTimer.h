//
//  CountdownTimer.h
//  SpotTheDifference
//
//  Created by allenhmo1254 on 13-7-25.
//
//

#ifndef __SpotTheDifference__CountdownTimer__
#define __SpotTheDifference__CountdownTimer__

#include <iostream>
#include "cocos2d.h"


class TimerProtocol {
public:
    void timeFinishProcess();
};


class CountdownTimer : public cocos2d::CCObject {
protected:
    long int time_;            //时间
    float delay_;         //延迟
    cocos2d::CCDirector *dircetor_;
public:
    CC_SYNTHESIZE_READONLY(bool, isFinished_, IsFinished);
    CC_SYNTHESIZE(TimerProtocol *, timerProtocolDelegate_, TimerProtocolDelegate);
public:
    CountdownTimer();
    static CountdownTimer* create();
    virtual bool init();
    virtual int hour();
    virtual int minute();
    virtual int second();
    virtual int time();
    virtual bool isFinished();
    virtual void setIsFinished(bool isFinished);
    virtual void setTime(long time);
    virtual void setTime(int hour,int minute,int second);
    virtual void process();
    virtual void resetTime();
};

#endif /* defined(__SpotTheDifference__CountdownTimer__) */
