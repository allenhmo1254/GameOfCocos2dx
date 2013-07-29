//
//  CWAScrollView.h
//  SpotTheDifference
//
//  Created by allenhmo1254 on 13-7-25.
//
//

#ifndef __SpotTheDifference__CWAScrollView__
#define __SpotTheDifference__CWAScrollView__

#include <iostream>
#include "cocos2d.h"

typedef enum {
    CWAScrollViewDirectionNone = -1,
    CWAScrollViewDirection_Horizontal = 0,
    CWAScrollViewDirection_Vertical,
} CWAScrollViewDirection;


class CWAScrollView : public cocos2d::CCLayer
{
protected:
    cocos2d::CCPoint moveLayerStartPos_,
    moveLayerEndPos_,
    moveLayerDifferencePos_,
    moveLayerSpeed,
    moveLayeraSpeed;
    int moveHdirection_,
    moveVdirection_;
    bool isMoveLayer_;
public:
    CC_SYNTHESIZE(bool, isTouchMoved_, IsTouchMove);
    CC_SYNTHESIZE(CWAScrollViewDirection, direction_, Direction);
public:
    CWAScrollView();
    ~CWAScrollView();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    static CWAScrollView* create(cocos2d::CCSize contentSize);
    
    virtual void touchBeginProcess(cocos2d::CCTouch *touch);
    virtual void touchMoveProcess(cocos2d::CCTouch *touch);
    virtual void touchEndProcess(cocos2d::CCTouch *touch);
    
    virtual void mainUpdate(float time);
    virtual void mainProcess();
    
    virtual void onEnter();
    virtual void onExit();
    
    // default implements are used to call script callback if exist
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    void layerMoveProcess(cocos2d::CCTouch *pTouch);
    void setLayerMove(cocos2d::CCPoint nextPos);
    cocos2d::CCPoint setLayerPosition(cocos2d::CCPoint nextPos);
    cocos2d::CCPoint setMoveRange(cocos2d::CCPoint newPos);
    int isCrosse(cocos2d::CCPoint point);
    void touchEndProcess();
    bool crosseProcess();
   
    void layerMoveActionWithFaceTo(int faceTo);
    //平滑移动层的逻辑
    void moveLayerDiferencePosProcess();
    void moveLayerDiferencePosWithTouchEnd();
    void moveLayerDiferencePosWithTouchMove(cocos2d::CCTouch *touch);
    void moveLayerDiferencePosWithTouchBegin();
};


#endif /* defined(__SpotTheDifference__CWAScrollView__) */
