//
//  GameScene.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#include "GameScene.h"


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
    
    CCSize screenSize = CCDirector::sharedDirector() -> getWinSize();
    
    CCLabelTTF *sceneLabel = CCLabelTTF::create("游戏界面", "AppleGothic", 30);
    
    addChild(sceneLabel);
    
    sceneLabel -> setPosition(ccp(screenSize.width / 2,screenSize.height / 2));
    
    
    return true;
}