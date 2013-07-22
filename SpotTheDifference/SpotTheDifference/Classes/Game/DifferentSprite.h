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
public:
    CC_SYNTHESIZE(bool , isShowCircle_, IsShowCircle);
public:
    DifferentSprite();
    ~DifferentSprite();
    
    CREATE_FUNC(DifferentSprite);
    
};

#endif /* defined(__SpotTheDifference__DifferentSprite__) */
