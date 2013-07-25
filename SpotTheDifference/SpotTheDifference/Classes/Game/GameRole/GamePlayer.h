//
//  GamePlayer.h
//  SpotTheDifference
//
//  Created by allenhmo1254 on 13-7-25.
//
//

#ifndef __SpotTheDifference__GamePlayer__
#define __SpotTheDifference__GamePlayer__

#include <iostream>
#include "GameRole.h"

class GamePlayer : public GameRole {
public:
    CREATE_FUNC(GamePlayer);
    
    virtual bool init();
    
    virtual void resetData();
};

#endif /* defined(__SpotTheDifference__GamePlayer__) */
