//
//  MainMenuScene.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#include "MainMenuScene.h"
#include "../UiScene/ChooseLevelScene.h"
#include "../Game/GameScene.h"

using namespace cocos2d;


CCScene* MainMenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainMenuScene *layer = MainMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize screenSize = CCDirector::sharedDirector() -> getWinSize();
    
    CCLabelTTF *startGameLabel = CCLabelTTF::create("开始游戏", "AppleGothic", 30);
    CCMenuItemLabel *startGameButton = CCMenuItemLabel::create(startGameLabel, this, menu_selector(MainMenuScene::startGame));
    startGameButton -> setPosition(ccp(screenSize.width / 2, screenSize.height * 4 / 5));
    
    CCLabelTTF *setGameLabel = CCLabelTTF::create("设置", "AppleGothic", 30);
    CCMenuItemLabel *setGameButton = CCMenuItemLabel::create(setGameLabel, this, menu_selector(MainMenuScene::setGame));
    setGameButton -> setPosition(ccp(screenSize.width / 2, screenSize.height * 3 / 5));
    
    CCLabelTTF *aboutLabel = CCLabelTTF::create("关于", "AppleGothic", 30);
    CCMenuItemLabel *aboutButton = CCMenuItemLabel::create(aboutLabel, this, menu_selector(MainMenuScene::aboutGame));
    aboutButton -> setPosition(ccp(screenSize.width / 2, screenSize.height * 2 / 5));
    
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(startGameButton, setGameButton, aboutButton, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    return true;
}


void MainMenuScene::startGame(CCObject* pSender)
{
    CCDirector::sharedDirector() -> replaceScene(ChooseLevelScene::scene());
}


void MainMenuScene::setGame(CCObject* pSender)
{
    CCLOG("游戏设置");
}


void MainMenuScene::aboutGame(CCObject* pSender)
{
    CCLOG("游戏关于");
}