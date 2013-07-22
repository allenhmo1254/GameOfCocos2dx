//
//  GameSprite.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-22.
//
//

#include "GameSprite.h"
#include "../PublicData/PublicDatas.h"
#include "extension.h"

using namespace extension;


GameSprite::GameSprite()
:differentSpriteArray_(NULL),
isShowDifferent_(false)
{
    
}


GameSprite::~GameSprite()
{
    differentSpriteArray_ -> removeAllObjects();
    differentSpriteArray_ -> release();
    differentSpriteArray_ = NULL;
}


GameSprite* GameSprite::createWithSpriteId(const char *name, bool isShowDifferent)
{
    GameSprite *pobSprite = new GameSprite();
    if (pobSprite && pobSprite->initWithFile(name, isShowDifferent))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
    
}


bool GameSprite::initWithFile(const char *name, bool isShowDifferent)
{
    if (!CCLayer::init()) {
        return false;
    }
    
    initDifferentSpriteArray();
    initGameSprite(name, isShowDifferent);
    
    return true;
}


void GameSprite::initDifferentSpriteArray()
{
    differentSpriteNum_ = ((CCArray *)CheckPointData::sharedCheckPointData() -> getDifferentImageFile()) -> count();
    differentSpriteArray_ = CCArray::createWithCapacity(differentSpriteNum_);
    differentSpriteArray_ -> retain();
    
}

void GameSprite::initGameSprite(const char *name, bool isShowDifferent)
{
    CCString *mainSpriteFile = (CCString *)CheckPointData::sharedCheckPointData() -> getMainImageFile() -> objectForKey(name);
    isShowDifferent_ = isShowDifferent;
    if (mainSpriteFile) {
        CCSprite *mainSprite = CCSprite::create(mainSpriteFile -> getCString());
        addChild(mainSprite);
        CCArray *differentSpriteFileArray = (CCArray *)CheckPointData::sharedCheckPointData() -> getDifferentImageFile() -> objectForKey(name);
        CCArray *differentSpritePosArray = (CCArray *)CheckPointData::sharedCheckPointData() -> getDifferentImagePos() -> objectForKey(name);
        for (int i = 0, count = differentSpriteFileArray -> count(); i < count; i ++) {
            CCString *differentSpriteFile = (CCString *)differentSpriteFileArray -> objectAtIndex(i);
            CCPoint differentSpritePos = ((CCBValue *)differentSpritePosArray -> objectAtIndex(i)) -> getCCPointValue();
            CCSprite *differentSprite = CCSprite::create(differentSpriteFile -> getCString());
            addChild(differentSprite);
            differentSprite -> setPosition(differentSpritePos);
            differentSprite -> setVisible(isShowDifferent_);
            differentSpriteArray_ -> addObject(differentSprite);
        }
    }
}


bool GameSprite::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint point = CCDirector::sharedDirector() -> convertToGL(pTouch -> getLocationInView());
    
    return true;
}

void GameSprite::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("ccTouchMoved");
}

void GameSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint endPoint = CCDirector::sharedDirector() -> convertToGL(pTouch -> getLocationInView());
    
}


void GameSprite::checkDifferentSprite(CCPoint pos)
{
    for (int i = 0; i < differentSpriteNum_; i ++) {
        CCSprite *sprite = (CCSprite *)differentSpriteArray_ -> objectAtIndex(i);
        CCRect rect = CCRectMake(sprite -> getPosition().x, sprite -> getPosition().y, sprite -> getContentSize().width, sprite -> getContentSize().height);
        
    }
}


