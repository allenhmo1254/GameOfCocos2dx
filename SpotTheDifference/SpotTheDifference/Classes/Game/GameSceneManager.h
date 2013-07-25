//
//  GameSceneManager.h
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#ifndef __SpotTheDifference__GameSceneManager__
#define __SpotTheDifference__GameSceneManager__

#include <iostream>
#include "cocos2d.h"
#include "GameSprite.h"
#include "CountdownTimer.h"



typedef enum{
    GameType_Normal = 0,      //普通
    GameType_Reverse,         //反向
}GameType; //游戏类型


typedef enum{
    GameState_Normal = 0,     //正常状态
    GameState_Finish,         //游戏结束
}GameState;//游戏状态


class GamePlayer;
class GameSceneManager : public cocos2d::CCObject, public GameSpriteProtocol, public TimerProtocol
{
public:
    CC_SYNTHESIZE(cocos2d::CCArray *, gameSpriteArray_, GameSpriteArray);
    CC_SYNTHESIZE(CountdownTimer *, gameTimer_, GameTimer);
    CC_SYNTHESIZE(GamePlayer *, gamePlayer_, GamePlayer);
public:
    static GameSceneManager* sharedGameSceneManager();
    static void clearGameSceneManager();
    
    GameSceneManager();
    ~GameSceneManager();
    
    void init();
    //初始化数据
    void initGameSpriteArray();
    void initGameTimer();
    void initGamePlayer();
    //显示圆圈
    void setGameSpriteShowCircle(int index);
    //游戏触摸碎片以后的回调函数
    virtual void gameSpriteTouchPressed(int index);
    //重置游戏数据
    void resetGameTimer();
    void resetGameData();
    //时间结束逻辑
    virtual void timeFinishProcess();
    //游戏主逻辑
    void mainProcess();
};

#endif /* defined(__SpotTheDifference__GameSceneManager__) */
