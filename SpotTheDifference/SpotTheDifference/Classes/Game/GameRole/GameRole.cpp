//
//  GameRole.cpp
//  SpotTheDifference
//
//  Created by allenhmo1254 on 13-7-25.
//
//

#include "GameRole.h"


GameRole::GameRole()
:currentFoundNum_(0),
needFoundNum_(0)
{
    
}


GameRole::~GameRole()
{
    
}


bool GameRole::init()
{
    return true;
}


void GameRole::resetData()
{
    
}


void GameRole::addCurrentFoundNum()
{
    currentFoundNum_ ++;
}


bool GameRole::isFoundFinish()
{
    if (currentFoundNum_ >= needFoundNum_) {
        return true;
    }
    return false;
}