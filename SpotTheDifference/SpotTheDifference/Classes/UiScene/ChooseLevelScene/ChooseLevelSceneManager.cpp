//
//  ChooseLevelSceneManager.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-31.
//
//

#include "ChooseLevelSceneManager.h"

static ChooseLevelSceneManager *chooseLevelSceneManager_;


ChooseLevelSceneManager* ChooseLevelSceneManager::sharedChooseLevelSceneManager()
{
    if (!chooseLevelSceneManager_) {
        chooseLevelSceneManager_ = new ChooseLevelSceneManager();
        chooseLevelSceneManager_ -> init();
    }
    return chooseLevelSceneManager_;
}


void ChooseLevelSceneManager::clearChooseLevelSceneManager()
{
    if (chooseLevelSceneManager_) {
        chooseLevelSceneManager_ -> release();
        chooseLevelSceneManager_ = NULL;
    }
}




ChooseLevelSceneManager::ChooseLevelSceneManager()
{
    
}


ChooseLevelSceneManager::~ChooseLevelSceneManager()
{
    
}



bool ChooseLevelSceneManager::init()
{
    return true;
}