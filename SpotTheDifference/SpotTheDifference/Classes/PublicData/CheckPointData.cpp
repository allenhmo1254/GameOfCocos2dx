//
//  CheckPointData.cpp
//  SpotTheDifference
//
//  Created by allenhmo1254 on 13-7-22.
//
//

#include "CheckPointData.h"


static CheckPointData* checkPointData_;

CheckPointData* CheckPointData::sharedCheckPointData()
{
    if (!checkPointData_) {
        checkPointData_ = new CheckPointData();
        checkPointData_ -> init();
    }
    return checkPointData_;
}

void CheckPointData::clearCheckPointData()
{
    checkPointData_ -> release();
    checkPointData_ = NULL;
}



CheckPointData::CheckPointData()
:mainImageFile_(NULL),
differentImageFile_(NULL),
levelKeyId_(NULL)
{
    
}


CheckPointData::~CheckPointData()
{
    mainImageFile_ -> removeAllObjects();
    mainImageFile_ -> release();
    mainImageFile_ = NULL;
    
    differentImageFile_ -> removeAllObjects();
    differentImageFile_ -> release();
    differentImageFile_ = NULL;
}



void CheckPointData::init()
{
    initMainImageFile();
    initDifferentImageFile();
    
}


void CheckPointData::initMainImageFile()
{
    mainImageFile_ = CCDictionary::create();
    mainImageFile_ -> retain();
    
    CCString *string = CCString::create("pic1001.png");
    mainImageFile_ -> setObject(string, "1001");
}



void CheckPointData::initDifferentImageFile()
{
    differentImageFile_ = CCDictionary::create();
    differentImageFile_ -> retain();
    
    CCArray *tempArray = CCArray::createWithCapacity(7);
    for (int i = 0; i < 7; i ++) {
        CCString *string = CCString::createWithFormat("frag1001-%d.png",i);
        tempArray -> addObject(string);
    }
    differentImageFile_ -> setObject(tempArray, "1001");
}

