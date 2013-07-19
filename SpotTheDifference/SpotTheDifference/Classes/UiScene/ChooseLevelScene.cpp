//
//  ChooseLevelScene.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#include "ChooseLevelScene.h"


using namespace cocos2d;
using namespace extension;


CCScene* ChooseLevelScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ChooseLevelScene *layer = ChooseLevelScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool ChooseLevelScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize screenSize = CCDirector::sharedDirector() -> getWinSize();
    
    cocos2d::extension::CCTableView *table = cocos2d::extension::CCTableView::create(this, screenSize);
    
    return true;
}


void ChooseLevelScene::initLevelButton()
{
    levelButtonArray_ = CCArray::create();
    levelButtonArray_ -> retain();
}

