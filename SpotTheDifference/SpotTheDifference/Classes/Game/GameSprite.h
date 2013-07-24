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

class GameSpriteProtocol
{
public:
    virtual void gameSpriteTouchPressed(int index) = 0;
};


class GameSceneManager;
class DifferentSprite;
class GameSprite : public cocos2d::CCLayer {
protected:
    cocos2d::CCString *spriteName_;;
    bool flipX_;
    bool flipY_;
    cocos2d::CCSprite *mainSprite_;
    cocos2d::CCSize mainSpriteSize_;
    cocos2d::CCPoint startPos_;
//    GameSpriteTouch *gameSpriteTouch_;
public:
    CC_SYNTHESIZE(GameSpriteProtocol *, gameSpriteProtocol_, GameSpriteProtocol);
    CC_SYNTHESIZE_READONLY(cocos2d::CCArray *, differentSpriteArray_, DifferentSpriteArray);
    CC_SYNTHESIZE(bool , isShowDifferent_, IsShowDifferent);
    CC_SYNTHESIZE_READONLY(int , differentSpriteNum_, DifferentSpriteNum);
public:
    GameSprite();
    ~GameSprite();
    
    static GameSprite *createWithSpriteId(const char *name, bool isShowDifferent);
    
    bool initWithFile(const char *name, bool isShowDifferent);
    //初始化不同的精灵数组
    void initDifferentSpriteArray();
    //初始化游戏精灵
    void initGameSprite();
    bool initMainSprite();
    void initDifferentSprite();
    //当前层的触摸
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    //检测不用的精灵
    void checkDifferentSprite(cocos2d::CCPoint pos);
    //按照索引显示不同精灵的圆圈
    void showCircleWithIndex(int index);
    //加载和退出时调用的函数
    void onEnter();
    void onExit();
    //设置水平和垂直翻转
    bool getFlipX();
    void setFlipX(bool state);
    bool getFlipY();
    void setFlipY(bool state);
    //得到精灵的Rect
    cocos2d::CCRect getGameSpriteRect(cocos2d::CCSprite *sprite);
    //设置锚点
    virtual void setAnchorPoint(const cocos2d::CCPoint& anchor);
    //重置精灵的坐标
    void resetSpritePos();
    //重写draw方法
    virtual void draw(void);
    //绘制精灵的碰撞框
    void drawSpriteRect();
    
    cocos2d::CCPoint getDifferentSpritePos(DifferentSprite *differentSprite, cocos2d::CCPoint pos);

};

#endif /* defined(__SpotTheDifference__GameSprite__) */
