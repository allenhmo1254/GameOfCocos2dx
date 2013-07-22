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


typedef enum{
    GameType_Normal = 0,      //普通
    GameType_Reverse,         //反向
}GameType; //游戏类型


typedef enum{
    GameState_Normal = 0,     //正常状态
    GameState_Finish,         //游戏结束
}GameState;//游戏状态


class GameSceneManager : public cocos2d::CCObject
{
public:
    CC_SYNTHESIZE(cocos2d::CCArray *, gameSpriteArray_, GameSpriteArray);
    CC_SYNTHESIZE(int, currentFoundNum_, CurrentFoundNum);
    CC_SYNTHESIZE(int, needFoundNum_, NeedFoundNum);
public:
    static GameSceneManager* sharedGameSceneManager();
    static void clearGameSceneManager();
    
    GameSceneManager();
    ~GameSceneManager();
    
    void init();
    
    void initGameSpriteArray();
    
    void setGameSpriteShowCircle(int index);
};

#endif /* defined(__SpotTheDifference__GameSceneManager__) */
