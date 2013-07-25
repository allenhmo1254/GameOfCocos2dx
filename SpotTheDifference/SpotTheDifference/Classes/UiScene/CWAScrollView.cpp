//
//  CWAScrollView.cpp
//  SpotTheDifference
//
//  Created by allenhmo1254 on 13-7-25.
//
//

#include "CWAScrollView.h"
#include "../PublicData/GameData.h"

using namespace cocos2d;


CWAScrollView::CWAScrollView()
:direction_(CWAScrollViewDirectionNone),
isTouchMoved_(false)
{
    
}


CWAScrollView::~CWAScrollView()
{
    
}


bool CWAScrollView::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    setAnchorPoint(CCPointZero);
    
    return true;
}



void CWAScrollView::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
}

void CWAScrollView::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}


bool CWAScrollView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCDirector::sharedDirector() -> convertToGL(pTouch -> getLocation());
    return true;
}

void CWAScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    layerMoveProcess(pTouch);
}

void CWAScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}


void CWAScrollView::layerMoveProcess(CCTouch *pTouch)
{
    if (!isTouchMoved_) {
        return;
    }
    
    CCPoint touchLocation = pTouch -> getLocation();
    CCPoint oldTouchLocation = pTouch -> getPreviousLocation();
    
    //    CGPoint translation = ccp(x, y);//获得之间的差值
    CCPoint translation = ccpSub(touchLocation, oldTouchLocation);//获得之间的差值
    setLayerMove(translation);
}



void CWAScrollView::setLayerMove(CCPoint nextPos)
{
    //自定义方法
    CCPoint newPos = setLayerPosition(nextPos);
    
    newPos = setMoveRange(newPos);
    
    setPosition(newPos);
}


CCPoint CWAScrollView::setMoveRange(CCPoint newPos)
{
    switch (direction_) {
        case CWAScrollViewDirectionNone:
            break;
        case CWAScrollViewDirection_Horizontal:
            newPos.x = MAX(SCREEN_WIDTH - this -> getContentSize().width, newPos.x);
            newPos.x = MIN(0, newPos.x);
            break;
        case CWAScrollViewDirection_Vertical:
            newPos.y = MAX(0, newPos.y);
            newPos.y = MIN(this -> getContentSize().height, newPos.y);
            break;
    }
    
    return newPos;
}


CCPoint CWAScrollView::setLayerPosition(CCPoint nextPos)
{
    switch (direction_) {
        case CWAScrollViewDirectionNone:
            return this -> getPosition();
        case CWAScrollViewDirection_Horizontal:
            return ccp(this -> getPositionX() + nextPos.x, this -> getPositionY());
        case CWAScrollViewDirection_Vertical:
            return ccp(this -> getPositionX(), this -> getPositionY() + nextPos.y);
    }
}
