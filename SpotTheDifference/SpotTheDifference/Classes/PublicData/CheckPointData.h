//
//  CheckPointData.h
//  SpotTheDifference
//
//  Created by allenhmo1254 on 13-7-22.
//
//

#ifndef __SpotTheDifference__CheckPointData__
#define __SpotTheDifference__CheckPointData__

#include <iostream>
#include "cocos2d.h"
#include "IntArray.h"

using namespace cocos2d;

class CheckPointData : public CCObject {
public:
    CC_SYNTHESIZE_READONLY(IntArray *, levelKeyId_, LevelKeyId);
    
public:
    static CheckPointData* sharedCheckPointData();
    static void clearCheckPointData();
    
    void init();
};

#endif /* defined(__SpotTheDifference__CheckPointData__) */
