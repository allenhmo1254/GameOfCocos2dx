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
#include "DifferentSprite.h"

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
    
    DifferentSprite *sp = DifferentSprite::create("Icon.png");
    sp -> setPosition(ccp(100, 100));
    addChild(sp);
    sp -> setOpacity(0);
    sp -> setIsShowCircle(true);
    
    return true;
}


void GameScene::initMainImage()
{
    
}

