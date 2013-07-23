//
//  GameSceneManager.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#include "GameSceneManager.h"
#include "../PublicData/PublicDataManager.h"

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


GameSceneManager::GameSceneManager()
:gameSpriteArray_(NULL),
currentFoundNum_(0),
needFoundNum_(0)
{
    
}


GameSceneManager::~GameSceneManager()
{
    gameSpriteArray_ -> removeAllObjects();
    gameSpriteArray_ -> release();
    gameSpriteArray_ = NULL;
}


void GameSceneManager::init()
{
    PublicDataManager::sharedPublicDataManager();
    initGameSpriteArray();
}


void GameSceneManager::initGameSpriteArray()
{
    gameSpriteArray_ = CCArray::createWithCapacity(2);
    gameSpriteArray_ -> retain();
}


void GameSceneManager::setGameSpriteShowCircle(int index)
{
    for (int i = 0, count = gameSpriteArray_ -> count(); i < count; i ++) {
        GameSprite *sprite = (GameSprite *)gameSpriteArray_ -> objectAtIndex(i);
        sprite -> showCircleWithIndex(index);
    }
    currentFoundNum_ ++;
    if (currentFoundNum_ >= needFoundNum_) {
        
    }
}



void GameSceneManager::gameSpriteTouchPressed(int index)
{
    setGameSpriteShowCircle(index);
}

