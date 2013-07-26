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
    float moveDurationTime_;          //移动的延迟时间
    int currentPartOfScrollView_;     //当前部分
    cocos2d::CCSize partOfViewSize_;  //每部分的尺寸
public:
    CC_SYNTHESIZE(bool, isTouchMoved_, IsTouchMove);
    CC_SYNTHESIZE(CWAScrollViewDirection, direction_, Direction);
    CC_SYNTHESIZE(int, partOfScrollView_, PartOfScrollView);//一共有几个部分
public:
    CWAScrollView();
    ~CWAScrollView();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    static CWAScrollView* create(cocos2d::CCSize contentSize, int partOfView);
    
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
    bool crosseProcess();
    //设置当前的part
    void setCurrentPart(int part);
    //移动到part指定的位置
    void layerMoveActionWithPart(int part);
    //设置每部分的尺寸
    void setPartOfViewSize();
    //当触摸松开时，层停在哪个部分的位置
    void partOfViewProcess();
};


#endif /* defined(__SpotTheDifference__CWAScrollView__) */
