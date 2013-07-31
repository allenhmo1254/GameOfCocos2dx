//
//  ChooseGameLinkGame.h
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-31.
//
//

#ifndef __SpotTheDifference__ChooseGameLinkGame__
#define __SpotTheDifference__ChooseGameLinkGame__

#include <iostream>
#include "cocos2d.h"

class ChooseGameLinkGame : public cocos2d::CCObject
{
public:
    CC_SYNTHESIZE(int, gameLevel_, GameLevel);
    CC_SYNTHESIZE(int, gameIndex, GameIndex);
public:
    static ChooseGameLinkGame* sharedChooseGameLinkGame();
    static void clearChooseGameLinkGame();
    
    ChooseGameLinkGame();
    ~ChooseGameLinkGame();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
};

#endif /* defined(__SpotTheDifference__ChooseGameLinkGame__) */
