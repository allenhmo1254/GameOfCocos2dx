//
//  CWATableView.cpp
//  SpotTheDifference
//
//  Created by allenhmo1254 on 13-7-28.
//
//

#include "CWATableView.h"
#include "../../PublicData/GameData.h"

using namespace cocos2d;


CWATableView::CWATableView()
:currentPartOfView_(0),
partOfView_(0),
partOfViewSize_(CCSizeZero),
startPoint_(CCPointZero),
touchMoveDistance_(0)
{
    
}


CWATableView::~CWATableView()
{
    
}



CWATableView* CWATableView::create(CWAScrollViewDirection direction, int partOfView)
{
    CWATableView *view = new CWATableView();
    if (view && view -> init()) {
        view -> autorelease();
        view -> setDirection(direction);
        view -> setPartOfView(partOfView);
        view -> setPartOfViewSize();
        view -> initOther();
        cocos2d::CCSize size = cocos2d::CCSizeZero;
        switch (direction) {
            case CWAScrollViewDirectionNone:
                size = view -> getPartOfViewSize();
                break;
            case CWAScrollViewDirection_Horizontal:
                size = CCSizeMake(view -> getPartOfViewSize().width * partOfView, view -> getPartOfViewSize().height);
                break;
            case CWAScrollViewDirection_Vertical:
                size = CCSizeMake(view -> getPartOfViewSize().width, partOfView * view -> getPartOfViewSize().height);
                break;
        }
        view -> setContentSize(size);
        return view;
    } else {
        delete view;
        view = NULL;
        return NULL;
    }
}

bool CWATableView::init()
{
    if (!CWAScrollView::init()) {
        return false;
    }
    
    
    return true;
}

void CWATableView::touchBeginProcess(cocos2d::CCTouch *touch)
{
    startPoint_ = touch -> getLocation();
}


void CWATableView::touchMoveProcess(cocos2d::CCTouch *touch)
{
    CWAScrollView::touchMoveProcess(touch);
}


void CWATableView::touchEndProcess(cocos2d::CCTouch *touch)
{
    if (!crosseProcess()) {
//        if (!checkTouchdistance(touch)) {
            touchEndProcessWithPoint(touch -> getLocation());
//        }
    }
}

void CWATableView::mainUpdate(float time)
{
    
}


void CWATableView::mainProcess()
{
    
}

void CWATableView::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
}

void CWATableView::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

// default implements are used to call script callback if exist
bool CWATableView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    touchBeginProcess(pTouch);
    return true;
}


void CWATableView::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    touchMoveProcess(pTouch);
}


void CWATableView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    touchEndProcess(pTouch);
}



void CWATableView::setCurrentPart(int part)
{
    if (part < 0 || part >= partOfView_) {
        return;
    }
    if (currentPartOfView_ != part) {
        currentPartOfView_ = part;
        layerMoveActionWithPart(part);
    }
}

//移动到part指定的位置
void CWATableView::layerMoveActionWithPart(int part)
{
    if (part < 0 || part >= partOfView_) {
        return;
    }
    
    switch (direction_) {
        case CWAScrollViewDirectionNone:
            break;
        case CWAScrollViewDirection_Horizontal:
        {
            moveActionWithPos(ccp(-part * partOfViewSize_.width, 0));
        }
            break;
        case CWAScrollViewDirection_Vertical:
        {
            moveActionWithPos(ccp(0, part * partOfViewSize_.height));
        }
            break;
    }
}



void CWATableView::moveActionWithPos(CCPoint point)
{
    CCMoveTo *move = CCMoveTo::create(MOVEDURATIONTIME, point);
    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(CWATableView::actionFinishProcess));
    CCSequence *seq = CCSequence::create(move, call, NULL);
    runAction(seq);
}


void CWATableView::actionFinishProcess()
{
    if (tableViewDelegate_) {
        tableViewDelegate_ -> tableViewRunFinishProcess(currentPartOfView_);
    }
}



//设置每部分的尺寸
void CWATableView::setPartOfViewSize()
{
    partOfViewSize_ = CCSizeMake(SCREEN_WIDTH, SCREEN_HEIGHT);
}

//当触摸松开时，层停在哪个部分的位置
void CWATableView::partOfViewProcess()
{
    
}

void CWATableView::initOther()
{
    touchMoveDistance_ = 10;
}


void CWATableView::touchEndProcessWithPoint(CCPoint point)
{
    CCPoint distance = ccpSub(point, startPoint_);
    switch (direction_) {
        case CWAScrollViewDirectionNone:
            
            break;
        case CWAScrollViewDirection_Horizontal:
            if (distance.x > touchMoveDistance_) {
                setCurrentPart(currentPartOfView_ - 1);
            } else if (distance.x < -touchMoveDistance_) {
                setCurrentPart(currentPartOfView_ + 1);
            } else {
                layerMoveActionWithPart(currentPartOfView_);
            }
            break;
        case CWAScrollViewDirection_Vertical:
            if (distance.y < touchMoveDistance_) {
                setCurrentPart(currentPartOfView_ - 1);
            } else if (distance.y > -touchMoveDistance_) {
                setCurrentPart(currentPartOfView_ + 1);
            } else {
                layerMoveActionWithPart(currentPartOfView_);
            }
            break;
    }
}


bool CWATableView::checkTouchdistance(CCTouch *touch)
{
    CCPoint touchLocation = touch -> getLocation();
    CCPoint oldTouchLocation = touch -> getPreviousLocation();
    
    CCPoint translation = ccpSub(touchLocation, oldTouchLocation);//获得之间的差值
    
    float temp = 2;
    switch (direction_) {
        case CWAScrollViewDirectionNone:
            return false;
        case CWAScrollViewDirection_Horizontal:
            if (translation.x > temp) {
                setCurrentPart(currentPartOfView_ - 1);
                return true;
            } else if (translation.x < -temp) {
                setCurrentPart(currentPartOfView_ + 1);
                return true;
            }
            return false;
        case CWAScrollViewDirection_Vertical:
            if (translation.y < temp) {
                setCurrentPart(currentPartOfView_ - 1);
                return true;
            } else if (translation.y > -temp) {
                setCurrentPart(currentPartOfView_ + 1);
                return true;
            }
            return false;
    }
    
    return false;
}


