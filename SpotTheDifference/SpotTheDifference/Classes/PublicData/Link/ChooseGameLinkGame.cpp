//
//  ChooseGameLinkGame.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-31.
//
//

#include "ChooseGameLinkGame.h"

static ChooseGameLinkGame *chooseGameLinkGame_;

ChooseGameLinkGame* ChooseGameLinkGame::sharedChooseGameLinkGame()
{
    if (!chooseGameLinkGame_) {
        chooseGameLinkGame_ = new ChooseGameLinkGame();
        chooseGameLinkGame_ -> init();
    }
    return chooseGameLinkGame_;
}


void ChooseGameLinkGame::clearChooseGameLinkGame()
{
    chooseGameLinkGame_ -> release();
    chooseGameLinkGame_ = NULL;
}


ChooseGameLinkGame::ChooseGameLinkGame()
{
    
}

ChooseGameLinkGame::~ChooseGameLinkGame()
{
    
}


bool ChooseGameLinkGame::init()
{
    return true;
}