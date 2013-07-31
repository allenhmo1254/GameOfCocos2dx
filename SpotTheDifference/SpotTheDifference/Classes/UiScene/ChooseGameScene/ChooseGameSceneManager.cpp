//
//  ChooseGameSceneManager.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-31.
//
//

#include "ChooseGameSceneManager.h"


static ChooseGameSceneManager *chooseGameSceneManager_;


ChooseGameSceneManager* ChooseGameSceneManager::sharedChooseGameSceneManager()
{
    if (!chooseGameSceneManager_) {
        chooseGameSceneManager_ = new ChooseGameSceneManager();
        chooseGameSceneManager_ -> init();
    }
    return chooseGameSceneManager_;
}


void ChooseGameSceneManager::clearChooseGameSceneManager()
{
    if (chooseGameSceneManager_) {
        chooseGameSceneManager_ -> release();
        chooseGameSceneManager_ = NULL;
    }
}


ChooseGameSceneManager::ChooseGameSceneManager()
{
    
}


ChooseGameSceneManager::~ChooseGameSceneManager()
{
    
}


// Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
bool ChooseGameSceneManager::init()
{
    return true;
}