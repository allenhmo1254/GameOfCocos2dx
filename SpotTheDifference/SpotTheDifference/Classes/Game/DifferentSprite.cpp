//
//  DifferentSprite.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-22.
//
//

#include "DifferentSprite.h"


DifferentSprite* DifferentSprite::create(const char *pszFileName)
{
    DifferentSprite *pobSprite = new DifferentSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}


void DifferentSprite::setIsShowCircle(bool state)
{
    isShowCircle_ = state;
    if (isShowCircle_) {
        CCSprite *mainSprite = CCSprite::create("Icon-72.png");
        addChild(mainSprite);
    }
}


bool DifferentSprite::getIsShowCircle()
{
    return isShowCircle_;
}


