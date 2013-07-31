//
//  ChooseLevelScene.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#include "ChooseLevelScene.h"
#include "../../PublicData/GameData.h"
#include "../ChooseGameScene/ChooseGameScene.h"
#include "../../MainMenu/MainMenuScene.h"

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
    
    manager_ = ChooseLevelSceneManager::sharedChooseLevelSceneManager();
    
    pageNum_ = 3;
    
    initLevelButton();
    initScrollView();
    initReturnButton();
    
    
    return true;
}


void ChooseLevelScene::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
}

void ChooseLevelScene::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}


void ChooseLevelScene::initLevelButton()
{
    levelButtonLayer_ = CCMenu::create();
    levelButtonLayer_ -> retain();
    
    for (int i = 0; i < pageNum_; i ++) {
        CCMenuItemImage *itemImage = CCMenuItemImage::create("Icon.png", "Icon.png", this, menu_selector(ChooseLevelScene::levelButtonPressed));
        itemImage -> setPosition(ccp(i * SCREEN_WIDTH + SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2));
        levelButtonLayer_ -> addChild(itemImage, 10, i);
    }
}





void ChooseLevelScene::initScrollView()
{
    levelView_ = CWATableView::create(CWAScrollViewDirection_Horizontal, 3);
    levelView_ -> addChild(levelButtonLayer_);
    levelButtonLayer_ -> setAnchorPoint(CCPointZero);
    levelButtonLayer_ -> setPosition(CCPointZero);
    levelView_ -> setIsTouchMove(true);
    levelView_ -> setTableViewDelegate(this);
    
    addChild(levelView_);
}


void ChooseLevelScene::initReturnButton()
{
    CCMenuItemImage *returnButton = CCMenuItemImage::create("Icon.png", "Icon.png", this, menu_selector(ChooseLevelScene::returnButtonPressed));
    returnButton -> setAnchorPoint(ccp(1.0, 1.0));
    returnButton -> setPosition(ccp(SCREEN_WIDTH - 50, SCREEN_HEIGHT - 50));
    CCMenu *staticButtonLayer = CCMenu::create(returnButton, NULL);
    addChild(staticButtonLayer);
    staticButtonLayer -> setAnchorPoint(CCPointZero);
    staticButtonLayer -> setPosition(CCPointZero);
}



bool ChooseLevelScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    touchBeginPos_ = CCDirector::sharedDirector() -> convertToGL(pTouch -> getLocation());
    return true;
}

void ChooseLevelScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void ChooseLevelScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint endPoint = CCDirector::sharedDirector() -> convertToGL(pTouch -> getLocationInView());
    float distance = endPoint.x - touchBeginPos_.x;
	if(fabs(distance) > LevelSCENEMOVEOFFSET)
	{
		moveScrollView(distance < 0 ? DIR_RIGHT : DIR_LEFT);
	}
}


void ChooseLevelScene::moveScrollView(FaceTo faceTo)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    switch (faceTo) {
        case DIR_LEFT:
            currnetPage_ = currnetPage_ - 1 < 0 ? 0 : currnetPage_ - 1;
            break;
        case DIR_RIGHT:
            currnetPage_ = currnetPage_ + 1 > pageNum_ - 1 ? pageNum_ - 1 : currnetPage_ + 1;
            break;
    }
    
    CCPoint  movePos = ccp(origin.x - visibleSize.width * currnetPage_, 0);
//    levelScrollView_ -> setContentOffset(movePos, true);
}


void ChooseLevelScene::levelButtonPressed(CCObject* pSender)
{
    CCMenuItemImage *image = (CCMenuItemImage *)pSender;
    CCLOG("image -> getTag() = %d",image -> getTag());
    CCDirector::sharedDirector() -> replaceScene(ChooseGameScene::scene());
}



void ChooseLevelScene::tableViewRunFinishProcess(int currentPartOfView)
{
    CCLOG("currentPartOfView = %d",currentPartOfView);
}


void ChooseLevelScene::returnButtonPressed(CCObject* pSender)
{
    CCDirector::sharedDirector() -> replaceScene(MainMenuScene::scene());
}

