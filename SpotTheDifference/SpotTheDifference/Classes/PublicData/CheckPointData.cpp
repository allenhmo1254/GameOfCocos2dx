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



void CheckPointData::init()
{
    
}

