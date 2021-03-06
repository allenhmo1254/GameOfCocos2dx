//
//  DifferentSprite.h
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-22.
//
//

#ifndef __SpotTheDifference__DifferentSprite__
#define __SpotTheDifference__DifferentSprite__

#include <iostream>
#include "cocos2d.h"

class DifferentSprite : public cocos2d::CCSprite {
protected:
    bool isShowCircle_;
public:
    static DifferentSprite *create(const char *name);
    
    void setIsShowCircle(bool state);
    bool getIsShowCircle();
};

#endif /* defined(__SpotTheDifference__DifferentSprite__) */
