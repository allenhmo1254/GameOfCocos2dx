//
//  ChooseGameScene.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#include "ChooseGameScene.h"
#include "../../PublicData/GameData.h"
#include "../../Game/GameScene.h"
#include "../ChooseLevelScene/ChooseLevelScene.h"


using namespace cocos2d;


CCScene* ChooseGameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ChooseGameScene *layer = ChooseGameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChooseGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    buttonSize_ = CCSizeMake(4, 3);
    
    buttonDistance_ = CCSizeMake(100, 100);
    
    manager_ = ChooseGameSceneManager::sharedChooseGameSceneManager();
    
    initChooseGameButtonLayer();
    
    initChooseGameView();
    
    initReturnButton();
    
    return true;
}



void ChooseGameScene::initChooseGameView()
{
    chooseGameView_ = CWAScrollView::create(CCSizeMake(SCREEN_WIDTH, SCREEN_HEIGHT));
    chooseGameView_ -> setDirection(CWAScrollViewDirection_Vertical);
    chooseGameView_ -> setIsTouchMove(false);
    addChild(chooseGameView_);
    chooseGameView_ -> addChild(chooseGameButtonLayer_);
    chooseGameButtonLayer_ -> setAnchorPoint(CCPointZero);
    chooseGameButtonLayer_ -> setPosition(CCPointZero);
}


void ChooseGameScene::initChooseGameButtonLayer()
{
    chooseGameButtonLayer_ = CCMenu::create();
    
    CCPoint startPos = ccp(SCREEN_WIDTH / buttonSize_.width, SCREEN_HEIGHT / buttonSize_.height);
    
    for (int i = 0; i < buttonSize_.height; i ++) {
        for (int j = 0; j < buttonSize_.width; j ++) {
            CCMenuItemImage *itemImage = CCMenuItemImage::create("Icon.png", "Icon.png", this, menu_selector(ChooseGameScene::chooseGameButtonPressed));
            itemImage -> setPosition(ccp(startPos.x + j * buttonDistance_.width, SCREEN_HEIGHT - startPos.y - i * buttonDistance_.height));
            chooseGameButtonLayer_ -> addChild(itemImage, 10, i * buttonSize_.width + j);
        }
    }
}



void ChooseGameScene::initReturnButton()
{
    CCMenuItemImage *returnButton = CCMenuItemImage::create("Icon.png", "Icon.png", this, menu_selector(ChooseGameScene::returnButtonPressed));
    returnButton -> setAnchorPoint(ccp(1.0, 1.0));
    returnButton -> setPosition(ccp(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50));
    CCMenu *staticButtonLayer = CCMenu::create(returnButton, NULL);
    addChild(staticButtonLayer);
    staticButtonLayer -> setAnchorPoint(CCPointZero);
    staticButtonLayer -> setPosition(CCPointZero);
}



void ChooseGameScene::chooseGameButtonPressed(CCObject* pSender)
{
    CCMenuItemImage *image = (CCMenuItemImage *)pSender;
    CCLOG("image -> getTag() = %d",image -> getTag());
    CCDirector::sharedDirector() -> replaceScene(GameScene::scene());
}

void ChooseGameScene::returnButtonPressed(CCObject* pSender)
{
    CCDirector::sharedDirector() -> replaceScene(ChooseLevelScene::scene());
}

