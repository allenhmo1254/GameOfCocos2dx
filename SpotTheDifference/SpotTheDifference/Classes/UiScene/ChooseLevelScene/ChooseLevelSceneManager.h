//
//  ChooseLevelSceneManager.h
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-31.
//
//

#ifndef __SpotTheDifference__ChooseLevelSceneManager__
#define __SpotTheDifference__ChooseLevelSceneManager__

#include <iostream>
#include "cocos2d.h"

class ChooseLevelSceneManager : public cocos2d::CCObject
{
public:
    ChooseLevelSceneManager();
    ~ChooseLevelSceneManager();
    
    static ChooseLevelSceneManager* sharedChooseLevelSceneManager();
    static void clearChooseLevelSceneManager();
    
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
};

#endif /* defined(__SpotTheDifference__ChooseLevelSceneManager__) */
