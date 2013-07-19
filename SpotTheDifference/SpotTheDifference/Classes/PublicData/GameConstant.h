//
//  GameConstant.h
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#ifndef __SpotTheDifference__GameConstant__
#define __SpotTheDifference__GameConstant__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class GameConstant : public CCObject {
public:
    static GameConstant* sharedGameConstant();
    static void clearGameConstant();
    
    void init();
};


#endif /* defined(__SpotTheDifference__GameConstant__) */
