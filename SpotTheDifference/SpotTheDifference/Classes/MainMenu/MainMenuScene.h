//
//  MainMenuScene.h
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#ifndef __SpotTheDifference__MainMenuScene__
#define __SpotTheDifference__MainMenuScene__

#include <iostream>
#include "cocos2d.h"

class MainMenuScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(MainMenuScene);
    
    void startGame(CCObject* pSender);
    void setGame(CCObject* pSender);
    void aboutGame(CCObject* pSender);
};

#endif /* defined(__SpotTheDifference__MainMenuScene__) */
