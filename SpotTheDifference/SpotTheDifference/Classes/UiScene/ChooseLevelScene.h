//
//  ChooseLevelScene.h
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#ifndef __SpotTheDifference__ChooseLevelScene__
#define __SpotTheDifference__ChooseLevelScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

class ChooseLevelScene : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDelegate, public cocos2d::extension::CCTableViewDataSource
{
public:
    CC_SYNTHESIZE(cocos2d::CCArray *, levelButtonArray_, LevelButtonArray);
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(ChooseLevelScene);
    //初始化选择等级按钮的数组
    void initLevelButton();
};

#endif /* defined(__SpotTheDifference__ChooseLevelScene__) */
