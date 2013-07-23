//
//  GameScene.h
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#ifndef __SpotTheDifference__GameScene__
#define __SpotTheDifference__GameScene__

#include <iostream>
#include "cocos2d.h"

class GameSceneManager;
class GameScene : public cocos2d::CCLayer
{
protected:
    GameSceneManager *gameSceneManager_;
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameScene);
    
    void initGameSprite();
};

#endif /* defined(__SpotTheDifference__GameScene__) */
