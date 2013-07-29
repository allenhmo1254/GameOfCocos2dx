//
//  CWATableView.h
//  SpotTheDifference
//
//  Created by allenhmo1254 on 13-7-28.
//
//

#ifndef __SpotTheDifference__CWATableView__
#define __SpotTheDifference__CWATableView__

#include <iostream>
#include "CWAScrollView.h"

class CWATableView : public CWAScrollView {
protected:
    int currentPartOfView_;     //当前部分
    cocos2d::CCPoint startPoint_;
    float touchMoveDistance_;
public:
    CC_SYNTHESIZE(cocos2d::CCSize, partOfViewSize_, PartOfViewSize);
    CC_SYNTHESIZE(int, partOfView_, PartOfView);//一共有几个部分
public:
    CWATableView();
    ~CWATableView();
    
    static CWATableView* create(CWAScrollViewDirection direction, int partOfView);
    
    virtual bool init();
    void initOther();
    
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
    
    //设置当前的part
    void setCurrentPart(int part);
    //移动到part指定的位置
    void layerMoveActionWithPart(int part);
    //设置每部分的尺寸
    void setPartOfViewSize();
    //当触摸松开时，层停在哪个部分的位置
    void partOfViewProcess();
    
    void touchEndProcessWithPoint(cocos2d::CCPoint point);
    
    bool checkTouchdistance(cocos2d::CCTouch *touch);
};

#endif /* defined(__SpotTheDifference__CWATableView__) */
