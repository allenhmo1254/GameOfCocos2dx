//
//  ChooseLevelScene.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#include "ChooseLevelScene.h"
#include "../PublicData/GameData.h"

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
    pageNum_ = 3;
    
    initLevelButton();
    initScrollView();
    
    
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



void ChooseLevelScene::levelButtonPressed(CCObject* pSender)
{
    CCMenuItemImage *image = (CCMenuItemImage *)pSender;
    CCLOG("image -> getTag() = %d",image -> getTag());
}



void ChooseLevelScene::initScrollView()
{
    levelScrollView_ = CCScrollView::create(CCSizeMake(SCREEN_WIDTH, SCREEN_HEIGHT), levelButtonLayer_);
    levelScrollView_ -> setContentOffset(CCPointZero);
    levelScrollView_ -> setTouchEnabled(true);
    levelScrollView_ -> setDelegate(this);
    levelScrollView_ -> setDirection(kCCScrollViewDirectionHorizontal);
    
    levelButtonLayer_ -> setContentSize(CCSizeMake(SCREEN_WIDTH * pageNum_, SCREEN_HEIGHT));
    
    addChild(levelScrollView_);
}


void ChooseLevelScene::scrollViewDidScroll(CCScrollView* view)
{
//    CCLOG("scrollViewDidScroll");
}

void ChooseLevelScene::scrollViewDidZoom(CCScrollView* view)
{
//     CCLOG("scrollViewDidZoom");
}

bool ChooseLevelScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    touchBeginPos_ = CCDirector::sharedDirector() -> convertToGL(pTouch -> getLocationInView());
    return true;
}

void ChooseLevelScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("ccTouchMoved");
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
    CCLOG("faceTo = %d",faceTo);
    CCLOG("movePos.x = %f,movePos.y = %f",movePos.x,movePos.y);
    levelScrollView_ -> setContentOffset(movePos, true);
}

