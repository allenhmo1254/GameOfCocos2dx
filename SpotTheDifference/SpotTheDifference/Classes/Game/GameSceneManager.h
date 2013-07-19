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

class GameSceneManager : public cocos2d::CCObject
{
public:
    static GameSceneManager* sharedGameSceneManager();
    static void clearGameSceneManager();
    
    void init();
};

#endif /* defined(__SpotTheDifference__GameSceneManager__) */
