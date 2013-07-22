//
//  PublicDataManager.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#include "PublicDataManager.h"
#include "PublicDatas.h"


static PublicDataManager* publicDataManager_;

PublicDataManager* PublicDataManager::sharedPublicDataManager()
{
    if (!publicDataManager_) {
        publicDataManager_ = new PublicDataManager();
        publicDataManager_ -> init();
    }
    return publicDataManager_;
}

void PublicDataManager::clearPublicDataManager()
{
    publicDataManager_ -> release();
    publicDataManager_ = NULL;
}



void PublicDataManager::init()
{
    GameConstant::sharedGameConstant();
    CheckPointData::sharedCheckPointData();
}