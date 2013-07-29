//
//  CWAScrollView.cpp
//  SpotTheDifference
//
//  Created by allenhmo1254 on 13-7-25.
//
//

#include "CWAScrollView.h"
#include "../../PublicData/GameData.h"

#define MOVESPEED             20
#define MOVEASPEED           0.2


using namespace cocos2d;


CWAScrollView::CWAScrollView()
:direction_(CWAScrollViewDirectionNone),
isTouchMoved_(false),
moveLayerStartPos_(CCPointZero),
moveLayerEndPos_(CCPointZero),
moveLayerDifferencePos_(CCPointZero),
moveLayerSpeed(CCPointZero),
moveLayeraSpeed(CCPointZero),
moveHdirection_(0),
moveVdirection_(0)
{
    
}


CWAScrollView::~CWAScrollView()
{
    
}


CWAScrollView* CWAScrollView::create(cocos2d::CCSize contentSize)
{
    CWAScrollView *view = new CWAScrollView();
    if (view && view -> init()) {
        view -> autorelease();
        view -> setContentSize(contentSize);
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
    schedule(schedule_selector(CWAScrollView::mainUpdate));
    
    return true;
}



void CWAScrollView::mainUpdate(float time)
{
    mainProcess();
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
    touchBeginProcess(pTouch);
    return true;
}

void CWAScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    touchMoveProcess(pTouch);
}

void CWAScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    touchEndProcess(pTouch);
}



void CWAScrollView::touchBeginProcess(CCTouch *touch)
{
    moveLayerDiferencePosWithTouchBegin();
}


void CWAScrollView::touchMoveProcess(CCTouch *touch)
{
    layerMoveProcess(touch);
    moveLayerDiferencePosWithTouchMove(touch);
}


void CWAScrollView::touchEndProcess(CCTouch *touch)
{
    touchEndProcess();
}

void CWAScrollView::mainProcess()
{
    moveLayerDiferencePosProcess();
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
        moveLayerDiferencePosWithTouchEnd();
    }
}




bool CWAScrollView::crosseProcess()
{
    switch (direction_) {
        case CWAScrollViewDirectionNone:
            return false;
        case CWAScrollViewDirection_Vertical:
        case CWAScrollViewDirection_Horizontal:
        {
            int faceTo = isCrosse(this -> getPosition());
            if (faceTo == DIR_NOMOVE) {
                return false;
            } else {
                layerMoveActionWithFaceTo(faceTo);
                return true;
            }
        }
            break;
    }
    return false;
}



int CWAScrollView::isCrosse(CCPoint point)
{
    switch (direction_) {
        case CWAScrollViewDirectionNone:
            return DIR_NOMOVE;
        case CWAScrollViewDirection_Horizontal:
            if (point.x < SCREEN_WIDTH - this -> getContentSize().width) {
                return DIR_LEFT;
            } else if(point.x > 0){
                return DIR_RIGHT;
            }
            return DIR_NOMOVE;
        case CWAScrollViewDirection_Vertical:
            if (point.y < 0) {
                return DIR_DOWN;
            } else if (point.y > SCREEN_HEIGHT - this -> getContentSize().height){
                return DIR_UP;
            }
            return DIR_NOMOVE;
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



void CWAScrollView::layerMoveActionWithFaceTo(int faceTo)
{
    if (faceTo == DIR_NOMOVE) {
        return;
    }
    
    switch (direction_) {
        case CWAScrollViewDirectionNone:
            return;
        case CWAScrollViewDirection_Horizontal:
        {
            switch (faceTo) {
                case DIR_LEFT:
                {
                    CCPoint point = ccp(SCREEN_WIDTH - this -> getContentSize().width, this -> getPositionY());
                    CCMoveTo *move = CCMoveTo::create(MOVEDURATIONTIME, point);
                    runAction(move);
                }
                    break;
                case DIR_RIGHT:
                {
                    CCPoint point = ccp(0, this -> getPositionY());
                    CCMoveTo *move = CCMoveTo::create(MOVEDURATIONTIME, point);
                    runAction(move);
                }
                    break;
            }
        }
            break;
        case CWAScrollViewDirection_Vertical:
        {
            switch (faceTo) {
                case DIR_UP:
                {
                    CCPoint point = ccp(this -> getPositionX(), 0);
                    CCMoveTo *move = CCMoveTo::create(MOVEDURATIONTIME, point);
                    runAction(move);
                }
                    break;
                case DIR_DOWN:
                {
                    CCPoint point = ccp(this -> getPositionX(), SCREEN_HEIGHT - this -> getContentSize().height);
                    CCMoveTo *move = CCMoveTo::create(MOVEDURATIONTIME, point);
                    runAction(move);
                }
                    break;
            }
        }
            break;
    }
}




void CWAScrollView::moveLayerDiferencePosWithTouchBegin()
{
    moveLayerDifferencePos_ = CCPointZero;
    isMoveLayer_ = false;
}


void CWAScrollView::moveLayerDiferencePosWithTouchMove(CCTouch *touch)
{
    moveLayerEndPos_ = moveLayerStartPos_;
    moveLayerStartPos_ = touch -> getLocation();
}



void CWAScrollView::moveLayerDiferencePosWithTouchEnd()
{
    if (!isTouchMoved_) {
        return;
    }
        moveLayerDifferencePos_ = ccpSub(moveLayerStartPos_, moveLayerEndPos_);
        if (moveLayerDifferencePos_.x > 0) {
            moveHdirection_ = DIR_RIGHT;
        } else if (moveLayerDifferencePos_.x < 0) {
            moveHdirection_ = DIR_LEFT;
        } else {
            moveHdirection_ = DIR_NOMOVE;
        }
        if (moveLayerDifferencePos_.y > 0) {
            moveVdirection_ = DIR_DOWN;
        } else if (moveLayerDifferencePos_.y < 0) {
            moveVdirection_ = DIR_UP;
        } else {
            moveVdirection_ = DIR_NOMOVE;
        }
        moveLayerSpeed = ccp(abs(moveLayerDifferencePos_.x), abs(moveLayerDifferencePos_.y));
        moveLayerSpeed.x = moveLayerSpeed.x > MOVESPEED ? MOVESPEED : moveLayerSpeed.x;
        moveLayerSpeed.y = moveLayerSpeed.y > MOVESPEED ? MOVESPEED : moveLayerSpeed.y;
        moveLayeraSpeed = ccp(MOVEASPEED, MOVEASPEED);
        isMoveLayer_ = true;
}

int direction[5] = {0, 1, -1, -1, 1};

void CWAScrollView::moveLayerDiferencePosProcess()
{
    if (!isMoveLayer_) {
        return;
    }
    
    switch (direction_) {
        case CWAScrollViewDirectionNone:
            break;
        case CWAScrollViewDirection_Horizontal:
            if (moveHdirection_ != DIR_NOMOVE) {
                setPosition(ccp(this -> getPositionX() + direction[moveHdirection_] * moveLayerSpeed.x, this -> getPositionY()));
                moveLayerSpeed = ccp(moveLayerSpeed.x - moveLayeraSpeed.x, moveLayerSpeed.y);
                moveLayerSpeed.x = moveLayerSpeed.x < 0 ? 0 : moveLayerSpeed.x;
                int faceTo = isCrosse(this -> getPosition());
                if (faceTo != DIR_NOMOVE) {
                    isMoveLayer_ = false;
                    layerMoveActionWithFaceTo(faceTo);
                } else {
                    if (moveLayerSpeed.x == 0) {
                        isMoveLayer_ = false;
                    }
                }
            }
            break;
        case CWAScrollViewDirection_Vertical:
            if (moveVdirection_ != DIR_NOMOVE) {
                setPosition(ccp(this -> getPositionX(), this -> getPositionY() + direction[moveVdirection_] * moveLayerSpeed.y));
                moveLayerSpeed = ccp(moveLayerSpeed.x, moveLayerSpeed.y - moveLayeraSpeed.y);
                moveLayerSpeed.y = moveLayerSpeed.y < 0 ? 0 : moveLayerSpeed.y;
                int faceTo = isCrosse(this -> getPosition());
                if (faceTo != DIR_NOMOVE) {
                    isMoveLayer_ = false;
                    layerMoveActionWithFaceTo(faceTo);
                } else {
                    if (moveLayerSpeed.y == 0) {
                        isMoveLayer_ = false;
                    }
                }
            }
            break;
    }
}



