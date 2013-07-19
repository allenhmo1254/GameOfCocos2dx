//
//  ActionData.h
//  SpotTheDifference
//
//  Created by leitingzu on 13-7-19.
//
//

#ifndef __SpotTheDifference__ActionData__
#define __SpotTheDifference__ActionData__

#include <iostream>
#include "cocos2d.h"
#include "../PublicData/BaseData.h"

class ActionData : public cocos2d::CCObject {
public:
    CC_SYNTHESIZE(cocos2d::CCString*,actionFile_, ActionFile);
    CC_SYNTHESIZE(Short1DArray,module_, Module);
    CC_SYNTHESIZE(Short2DArray,frame_, Frame);
    CC_SYNTHESIZE(Short2DArray,action_, Action);
    CC_SYNTHESIZE(Short2DArray,colRect_, ColRect);
    CC_SYNTHESIZE(Short2DArray,attRect_, AttRect);
public:
    static ActionData* createWithFile(cocos2d::CCString *path);
    
    ActionData();
    ~ActionData();
    
    virtual bool initWithFile(cocos2d::CCString *path);
    
};

#endif /* defined(__SpotTheDifference__ActionData__) */
