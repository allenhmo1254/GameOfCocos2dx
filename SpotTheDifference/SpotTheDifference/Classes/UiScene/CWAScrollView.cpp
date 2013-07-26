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
isTouchMoved_(false),
moveDurationTime_(0),
partOfScrollView_(0),
currentPartOfScrollView_(0)
{
    
}


CWAScrollView::~CWAScrollView()
{
    
}


CWAScrollView* CWAScrollView::create(cocos2d::CCSize contentSize, int partOfView)
{
    CWAScrollView *view = new CWAScrollView();
    if (view && view -> init()) {
        view -> autorelease();
        view -> setContentSize(contentSize);
        view -> setPartOfScrollView(partOfView);
        return view;
    } else {
        delete view;
        view = NULL;
        return NULL;
    }
}


bool CWAScrollView::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    setAnchorPoint(CCPointZero);
    moveDurationTime_ = 0.2;
    
    return true;
}


void CWAScrollView::setPartOfViewSize()
{
    
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
    touchEndProcess();
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
    
//    newPos = setMoveRange(newPos);
    
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
            newPos.y = MIN(SCREEN_HEIGHT - this -> getContentSize().height, newPos.y);
            break;
    }
    
    return newPos;
}



void CWAScrollView::touchEndProcess()
{
    if (!crosseProcess()) {
        partOfViewProcess();
    }
}



void CWAScrollView::partOfViewProcess()
{
    switch (direction_) {
        case CWAScrollViewDirectionNone:
            break;
        case CWAScrollViewDirection_Horizontal:
        {
            float partOfViewWidth = this -> getContentSize().width / partOfScrollView_;
            float temp = abs(this -> getPositionX()) - ((currentPartOfScrollView_ + 1) * partOfViewWidth - partOfViewWidth * 2);
            if (temp > 0) {
                setCurrentPart(currentPartOfScrollView_ - 1);
            } else if (temp < 0){
                setCurrentPart(currentPartOfScrollView_ + 1);
            }
        }
            break;
        case CWAScrollViewDirection_Vertical:
        {
            float partOfViewHeight = this -> getContentSize().height / partOfScrollView_;
            int tempPart = this -> getPositionY() / partOfViewHeight;
            setCurrentPart(abs(tempPart));
        }
            break;
    }
}



bool CWAScrollView::crosseProcess()
{
    switch (direction_) {
        case CWAScrollViewDirectionNone:
            return false;
        case CWAScrollViewDirection_Horizontal:
            switch (isCrosse(this -> getPosition())) {
                case -1:
                    layerMoveActionWithPart(partOfScrollView_ - 1);
                    return true;
                case 1:
                    layerMoveActionWithPart(0);
                    return true;
            }
            break;
        case CWAScrollViewDirection_Vertical:
            switch (isCrosse(this -> getPosition())) {
                case -1:
                    layerMoveActionWithPart(0);
                    return true;
                case 1:
                    layerMoveActionWithPart(partOfScrollView_ - 1);
                    return true;
            }
            break;
    }
    return false;
}



int CWAScrollView::isCrosse(CCPoint point)
{
    switch (direction_) {
        case CWAScrollViewDirectionNone:
            return 0;
        case CWAScrollViewDirection_Horizontal:
            if (point.x < SCREEN_WIDTH - this -> getContentSize().width) {
                return -1;
            } else if(point.x > 0){
                return 1;
            }
            return 0;
        case CWAScrollViewDirection_Vertical:
            if (point.y < 0) {
                return -1;
            } else if (point.y > SCREEN_HEIGHT - this -> getContentSize().height){
                return 1;
            }
            return 0;
    }
}



CCPoint CWAScrollView::setLayerPosition(CCPoint nextPos)
{
    switch (direction_) {
        case CWAScrollViewDirectionNone:
            return this -> getPosition();
        case CWAScrollViewDirection_Horizontal:
        {
            CCPoint tempPos = ccp(this -> getPositionX() + nextPos.x, this -> getPositionY());
            if (isCrosse(tempPos) != 0) {
                return ccp(this -> getPositionX() + nextPos.x / 3, this -> getPositionY());
            } else {
                return tempPos;
            }
        }
        case CWAScrollViewDirection_Vertical:
        {
            CCPoint tempPos = ccp(this -> getPositionX(), this -> getPositionY() + nextPos.y);
            if (isCrosse(tempPos) != 0) {
                return ccp(this -> getPositionX(), this -> getPositionY() + nextPos.y / 3);
            } else {
                return tempPos;
            }
        }
    }
}



void CWAScrollView::layerMoveActionWithPart(int part)
{
    switch (direction_) {
        case CWAScrollViewDirectionNone:
            return;
        case CWAScrollViewDirection_Horizontal:
        {
            CCPoint point = ccp(this -> getContentSize().width / partOfScrollView_ * part, this -> getPositionY());
            CCMoveTo *move = CCMoveTo::create(moveDurationTime_, point);
            runAction(move);
        }
            break;
        case CWAScrollViewDirection_Vertical:
        {
            CCPoint point = ccp(this -> getPositionX(), this -> getContentSize().height / partOfScrollView_ * part);
            CCMoveTo *move = CCMoveTo::create(moveDurationTime_, point);
            runAction(move);
        }
            break;
    }
}



void CWAScrollView::setCurrentPart(int part)
{
    if (part < 0 || part >= partOfScrollView_) {
        return;
    }
    currentPartOfScrollView_ = part;
    layerMoveActionWithPart(currentPartOfScrollView_);
}

