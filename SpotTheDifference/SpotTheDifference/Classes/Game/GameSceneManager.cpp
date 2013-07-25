//
//  GameSceneManager.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#include "GameSceneManager.h"
#include "../PublicData/PublicDataManager.h"
#include "GameRole/GamePlayer.h"

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
gameTimer_(NULL),
gamePlayer_(NULL)
{
    
}


GameSceneManager::~GameSceneManager()
{
    gameSpriteArray_ -> removeAllObjects();
    gameSpriteArray_ -> release();
    gameSpriteArray_ = NULL;
    
    gameTimer_ -> release();
    gameTimer_ = NULL;
    
    gamePlayer_ -> release();
    gamePlayer_ = NULL;
}


void GameSceneManager::init()
{
    PublicDataManager::sharedPublicDataManager();
    initGameSpriteArray();
    initGameTimer();
    initGamePlayer();
}


void GameSceneManager::initGameSpriteArray()
{
    gameSpriteArray_ = CCArray::createWithCapacity(2);
    gameSpriteArray_ -> retain();
}

void GameSceneManager::initGameTimer()
{
    gameTimer_ = CountdownTimer::create();
    gameTimer_ -> retain();
    gameTimer_ -> setTimerProtocolDelegate(this);
}


void GameSceneManager::initGamePlayer()
{
    gamePlayer_ = GamePlayer::create();
    gamePlayer_ -> retain();
}


void GameSceneManager::resetGameTimer()
{
    gameTimer_ -> setTime(10);
}


void GameSceneManager::resetGameData()
{
    gamePlayer_ -> resetData();
    resetGameTimer();
}


void GameSceneManager::setGameSpriteShowCircle(int index)
{
    for (int i = 0, count = gameSpriteArray_ -> count(); i < count; i ++) {
        GameSprite *sprite = (GameSprite *)gameSpriteArray_ -> objectAtIndex(i);
        sprite -> showCircleWithIndex(index);
    }
    gamePlayer_ -> addCurrentFoundNum();
    if (gamePlayer_ -> isFoundFinish()) {
        CCLOG("已经找到足够数量的不同");
    }
}


void GameSceneManager::mainProcess()
{
    gameTimer_ -> process();
}



void GameSceneManager::gameSpriteTouchPressed(int index)
{
    setGameSpriteShowCircle(index);
}

void GameSceneManager::timeFinishProcess()
{
    CCLOG("到时间了");
}

