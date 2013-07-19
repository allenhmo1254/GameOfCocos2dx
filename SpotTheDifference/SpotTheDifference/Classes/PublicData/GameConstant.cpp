//
//  GameConstant.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#include "GameConstant.h"


static GameConstant* gameConstant_;

GameConstant* GameConstant::sharedGameConstant()
{
    if (!gameConstant_) {
        gameConstant_ = new GameConstant();
        gameConstant_ -> init();
    }
    return gameConstant_;
}

void GameConstant::clearGameConstant()
{
    gameConstant_ -> release();
    gameConstant_ = NULL;
}



void GameConstant::init()
{
    
}