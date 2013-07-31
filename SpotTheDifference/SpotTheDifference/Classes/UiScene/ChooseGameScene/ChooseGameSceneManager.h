//
//  ChooseGameSceneManager.h
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-31.
//
//

#ifndef __SpotTheDifference__ChooseGameSceneManager__
#define __SpotTheDifference__ChooseGameSceneManager__

#include <iostream>
#include "cocos2d.h"

class ChooseGameSceneManager : public cocos2d::CCObject
{
public:
    static ChooseGameSceneManager* sharedChooseGameSceneManager();
    static void clearChooseGameSceneManager();
    
    ChooseGameSceneManager();
    ~ChooseGameSceneManager();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
};

#endif /* defined(__SpotTheDifference__ChooseGameSceneManager__) */
