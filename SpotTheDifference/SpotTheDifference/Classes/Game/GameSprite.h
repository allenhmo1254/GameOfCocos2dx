//
//  GameSprite.h
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-22.
//
//

#ifndef __SpotTheDifference__GameSprite__
#define __SpotTheDifference__GameSprite__

#include <iostream>
#include "cocos2d.h"

class GameSprite : public cocos2d::CCLayer {
public:
    CC_SYNTHESIZE(cocos2d::CCArray *, differentSpriteArray_, DifferentSpriteArray);
    CC_SYNTHESIZE(bool , isShowDifferent_, IsShowDifferent);
    CC_SYNTHESIZE(int , differentSpriteNum_, DifferentSpriteNum);
public:
    GameSprite();
    ~GameSprite();
    
    static GameSprite *createWithSpriteId(const char *name, bool isShowDifferent);
    
    bool initWithFile(const char *name, bool isShowDifferent);
    //初始化不同的精灵数组
    void initDifferentSpriteArray();
    //初始化游戏精灵
    void initGameSprite(const char *name, bool isShowDifferent);
    //当前层的触摸
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    //检测不用的精灵
    void checkDifferentSprite(cocos2d::CCPoint pos);
};

#endif /* defined(__SpotTheDifference__GameSprite__) */
