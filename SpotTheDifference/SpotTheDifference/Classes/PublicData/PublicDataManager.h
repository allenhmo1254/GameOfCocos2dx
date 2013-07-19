//
//  PublicDataManager.h
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#ifndef __SpotTheDifference__PublicDataManager__
#define __SpotTheDifference__PublicDataManager__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class PublicDataManager : public CCObject {
public:
    static PublicDataManager* sharedPublicDataManager();
    static void clearPublicDataManager();
    
    void init();
};


#endif /* defined(__SpotTheDifference__PublicDataManager__) */
