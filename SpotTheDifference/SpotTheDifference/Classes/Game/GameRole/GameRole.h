//
//  GameRole.h
//  SpotTheDifference
//
//  Created by allenhmo1254 on 13-7-25.
//
//

#ifndef __SpotTheDifference__GameRole__
#define __SpotTheDifference__GameRole__

#include <iostream>
#include "cocos2d.h"

typedef enum{
    RoleType_Player = 0,     //玩家
    RoleType_Antagonist,     //对手
}RoleType;//玩家类型

class GameRole : public cocos2d::CCObject {
    CC_SYNTHESIZE(int, currentFoundNum_, CurrentFoundNum);
    CC_SYNTHESIZE(int, needFoundNum_, NeedFoundNum);
public:
    GameRole();
    ~GameRole();
    
    CREATE_FUNC(GameRole);
    
    virtual bool init();
    
    virtual void resetData();
    
    void addCurrentFoundNum();
    
    bool isFoundFinish();
};

#endif /* defined(__SpotTheDifference__GameRole__) */
