//
//  ChooseLevelScene.h
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#ifndef __SpotTheDifference__ChooseLevelScene__
#define __SpotTheDifference__ChooseLevelScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "../../PublicData/GameData.h"
#include "../BaseView/CWATableView.h"
#include "ChooseLevelSceneManager.h"

USING_NS_CC;
USING_NS_CC_EXT;


class ChooseLevelScene : public cocos2d::CCLayer, public CWATableViewProtocol
{
private:
    CCMenu *levelButtonLayer_;
    CWATableView *levelView_;
    int currnetPage_;
    CCPoint touchBeginPos_;
    ChooseLevelSceneManager *manager_;
public:
    CC_SYNTHESIZE(int, pageNum_, PageNum);
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(ChooseLevelScene);
    //初始化选择等级按钮的数组
    void initLevelButton();
    //加载和退出时调用的函数
    void onEnter();
    void onExit();
    //初始化ScrollView
    void initScrollView();
    void initReturnButton();
    //移动ScrollView
    void moveScrollView(FaceTo faceTo);
    //当前层的触摸
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    //按钮回调函数
    void levelButtonPressed(CCObject* pSender);
    void returnButtonPressed(CCObject* pSender);
    
    virtual void tableViewRunFinishProcess(int currentPartOfView);
    
    
};

#endif /* defined(__SpotTheDifference__ChooseLevelScene__) */
