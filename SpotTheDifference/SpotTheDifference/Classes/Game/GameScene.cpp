//
//  GameScene.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#include "GameScene.h"
#include "GameSceneManager.h"
#include "../PublicData/PublicDatas.h"
#include "GameSprite.h"
#include "../PublicData/GameData.h"

using namespace cocos2d;


CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    gameSceneManager_ = GameSceneManager::sharedGameSceneManager();
    
    initGameSprite();
    
    return true;
}


void GameScene::initGameSprite()
{
    const int count = 2;
    bool state[count] = {true, false};
    float anchorX[count] = {1, 0};
    
    
    for (int i = 0; i < count - 0; i ++) {
        GameSprite *sprite = GameSprite::createWithSpriteId("1001", state[i]);
        sprite -> setAnchorPoint(ccp(anchorX[i],0.5));
        sprite -> setPosition(ccp(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
        sprite -> setFlipY(state[i]);
        addChild(sprite);
        gameSceneManager_ -> getGameSpriteArray() -> addObject(sprite);
        sprite -> setGameSpriteProtocol(gameSceneManager_);
    }
}


