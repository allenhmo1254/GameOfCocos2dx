//
//  GameSceneManager.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#include "GameSceneManager.h"


static GameSceneManager* gameSceneManager_;

GameSceneManager* GameSceneManager::sharedGameSceneManager()
{
    if (!gameSceneManager_) {
        gameSceneManager_ = new GameSceneManager();
        gameSceneManager_ -> init();
    }
    return gameSceneManager_;
}

void GameSceneManager::clearGameSceneManager()
{
    gameSceneManager_ -> release();
    gameSceneManager_ = NULL;
}


void GameSceneManager::init()
{
    
}