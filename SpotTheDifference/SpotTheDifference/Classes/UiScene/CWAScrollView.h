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
    float moveDurationTime_;
public:
    CC_SYNTHESIZE(bool, isTouchMoved_, IsTouchMove);
    CC_SYNTHESIZE(CWAScrollViewDirection, direction_, Direction);
public:
    CWAScrollView();
    ~CWAScrollView();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(CWAScrollView);
    
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
};


#endif /* defined(__SpotTheDifference__CWAScrollView__) */
