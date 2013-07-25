//
//  GamePlayer.cpp
//  SpotTheDifference
//
//  Created by allenhmo1254 on 13-7-25.
//
//

#include "GamePlayer.h"


bool GamePlayer::init()
{
    if (!GameRole::init()) {
        return false;
    }
    
    return true;
}


void GamePlayer::resetData()
{
    GameRole::init();
    
}