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
    CC_SYNTHESIZE_READONLY(CCDictionary *, mainImageFile_, MainImageFile);
    CC_SYNTHESIZE_READONLY(CCDictionary *, differentImageFile_, DifferentImageFile);
public:
    static CheckPointData* sharedCheckPointData();
    static void clearCheckPointData();
    
    CheckPointData();
    ~CheckPointData();
    
    void init();
    
    void initMainImageFile();
    void initDifferentImageFile();
};

#endif /* defined(__SpotTheDifference__CheckPointData__) */
