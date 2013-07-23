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
#include "DifferentSprite.h"
#include "GameSceneManager.h"

using namespace extension;


GameSprite::GameSprite()
:differentSpriteArray_(NULL),
isShowDifferent_(false),
gameSpriteProtocol_(NULL),
differentSpriteNum_(0)
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
    name_ = name;
    initDifferentSpriteArray();
    initGameSprite(name, isShowDifferent);
    
    return true;
}


void GameSprite::initDifferentSpriteArray()
{
    
    CCArray *differentSpriteFileArray = (CCArray *)CheckPointData::sharedCheckPointData() -> getDifferentImageFile() -> objectForKey(name_);
    differentSpriteNum_ = differentSpriteFileArray -> count();
    CCLOG("differentSpriteNum_ = %d",differentSpriteNum_);
    differentSpriteArray_ = CCArray::createWithCapacity(differentSpriteNum_);
    differentSpriteArray_ -> retain();
    
}

void GameSprite::initGameSprite(const char *name, bool isShowDifferent)
{
    CCString *mainSpriteFile = (CCString *)CheckPointData::sharedCheckPointData() -> getMainImageFile() -> objectForKey(name);
    isShowDifferent_ = isShowDifferent;
    if (mainSpriteFile) {
        mainSprite_ = CCSprite::create(mainSpriteFile -> getCString());
        addChild(mainSprite_, -2);
        mainSprite_ -> setAnchorPoint(CCPointZero);
        mainSprite_ -> setPosition(CCPointZero);
        CCArray *differentSpriteFileArray = (CCArray *)CheckPointData::sharedCheckPointData() -> getDifferentImageFile() -> objectForKey(name);
        CCArray *differentSpritePosArray = (CCArray *)CheckPointData::sharedCheckPointData() -> getDifferentImagePos() -> objectForKey(name);
        mainSpriteSize_ = mainSprite_ -> getContentSize();
        for (int i = 0, count = differentSpriteFileArray -> count(); i < count; i ++) {
            CCString *differentSpriteFile = (CCString *)differentSpriteFileArray -> objectAtIndex(i);
            CCPoint differentSpritePos = ((CCBValue *)differentSpritePosArray -> objectAtIndex(i)) -> getCCPointValue();
            DifferentSprite *differentSprite = DifferentSprite::create(differentSpriteFile -> getCString());
            differentSpriteArray_ -> addObject(differentSprite);
            addChild(differentSprite, -1);
            differentSprite -> setAnchorPoint(ccp(0,1));
            differentSprite -> setPosition(ccp(differentSpritePos.x / CC_CONTENT_SCALE_FACTOR(),mainSpriteSize_.height - differentSpritePos.y / CC_CONTENT_SCALE_FACTOR()));
            if (!isShowDifferent_) {
                differentSprite -> setOpacity(0);
            }
        }
    }
}


bool GameSprite::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint point = pTouch -> getLocation();
    checkDifferentSprite(point);
    return true;
}

void GameSprite::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
//    CCLOG("ccTouchMoved");
}

void GameSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
//    CCPoint endPoint = CCDirector::sharedDirector() -> convertToGL(pTouch -> getLocationInView());
    
}


void GameSprite::draw()
{
    for (int i = 0; i < differentSpriteNum_; i ++) {
        DifferentSprite *sprite = (DifferentSprite *)differentSpriteArray_ -> objectAtIndex(i);
        CCRect rect = getGameSpriteRect(sprite);
        ccDrawRect(rect.origin, ccp(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height));
    }
}


void GameSprite::checkDifferentSprite(CCPoint pos)
{
    CCLOG("pos.x = %f,pos.y = %f",pos.x,pos.y);
    CCLOG("getPositionX() = %f, getPositionY() = %f",getPositionX(), getPositionY());
    for (int i = 0; i < differentSpriteNum_; i ++) {
        DifferentSprite *sprite = (DifferentSprite *)differentSpriteArray_ -> objectAtIndex(i);
        CCRect rect = getGameSpriteRect(sprite);
        CCLOG("rect.origin.x = %f,rect.origin.y = %f,rect.size.width = %f,rect.size.height = %f",rect.origin.x,rect.origin.y,rect.size.width,rect.size.height);
        if (rect.containsPoint(pos) && !sprite -> getIsShowCircle()) {
            if (gameSpriteProtocol_) {
                gameSpriteProtocol_ -> gameSpriteTouchPressed(i);
            }
            break;
        }
    }
}


void GameSprite::showCircleWithIndex(int index)
{
    DifferentSprite *sprite = (DifferentSprite *)differentSpriteArray_ -> objectAtIndex(index);
    sprite -> setIsShowCircle(true);
}


void GameSprite::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
}

void GameSprite::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}



bool GameSprite::getFlipX()
{
    return flipX_;
}


void GameSprite::setFlipX(bool state)
{
    if (flipX_ != state) {
        flipX_ = state;
        mainSprite_ -> setFlipX(flipX_);
        for (int i = 0, count = differentSpriteArray_ -> count(); i < count; i ++) {
            DifferentSprite *sprite = (DifferentSprite *)differentSpriteArray_ -> objectAtIndex(i);
            CCPoint tempAnchor = sprite -> getAnchorPoint();
            CCPoint tempPos = sprite -> getPosition();
            sprite -> setAnchorPoint(ccp(1 - tempAnchor.x, tempAnchor.y));
            sprite -> setPosition(ccp(mainSpriteSize_.width - tempPos.x, tempPos.y));
            sprite -> setFlipX(flipX_);
        }
    }
}

bool GameSprite::getFlipY()
{
    return flipY_;
}


void GameSprite::setFlipY(bool state)
{
    if (flipY_ != state) {
        flipY_ = state;
        mainSprite_ -> setFlipY(flipY_);
        for (int i = 0, count = differentSpriteArray_ -> count(); i < count; i ++) {
            DifferentSprite *sprite = (DifferentSprite *)differentSpriteArray_ -> objectAtIndex(i);
            CCPoint tempAnchor = sprite -> getAnchorPoint();
            CCPoint tempPos = sprite -> getPosition();
            sprite -> setAnchorPoint(ccp(tempAnchor.x, 1 - tempAnchor.y));
            sprite -> setPosition(ccp(tempPos.x, mainSpriteSize_.height - tempPos.y));
            sprite -> setFlipY(flipY_);
        }
    }
}


CCRect GameSprite::getGameSpriteRect(CCSprite *sprite)
{
    float x = flipX_ == true ? sprite -> getPosition().x - sprite -> getContentSize().width : sprite -> getPosition().x;
    float y = flipY_ == true ? sprite -> getPosition().y : sprite -> getPosition().y - sprite -> getContentSize().height;
    float width = sprite -> getContentSize().width;
    float height = sprite -> getContentSize().height;
    return CCRectMake(x + getPositionX(), y + getPositionY(), width, height);
}



void GameSprite::setAnchorPoint(const CCPoint& anchor)
{
    CCNode::setAnchorPoint(anchor);
    startPos_ = ccp(-anchor.x * mainSpriteSize_.width, -anchor.y * mainSpriteSize_.height);
    resetSpritePos();
}


void GameSprite::resetSpritePos()
{
    mainSprite_ -> setPosition(ccpAdd(startPos_, mainSprite_ -> getPosition()));
    for (int i = 0; i < differentSpriteNum_; i ++) {
        DifferentSprite *sprite = (DifferentSprite *)differentSpriteArray_ -> objectAtIndex(i);
        sprite -> setPosition(ccpAdd(startPos_, sprite -> getPosition()));
    }
}

