//
//  IntArray.h
//  SpotTheDifference
//
//  Created by leitingzu on 13-7-19.
//
//

#ifndef __SpotTheDifference__IntArray__
#define __SpotTheDifference__IntArray__

#include <iostream>
#include "cocos2d.h"
#import "../PublicData/BaseData.h"

class IntArray : public cocos2d::CCObject {
protected:
    Int1DArray data_;
public:
    virtual bool init();
    
    CREATE_FUNC(IntArray);
    
    IntArray();
    ~IntArray();
    
    int count();
    int intAtIndex(int index);
    void addInt(int data);
    void insertIntAtIndex(int index, int value);
    void setIntAtIndex(int index, int value);
    void removeIntAtIndex(int index);
    void removeAllInt();
    void exchangeIntAtIndex(int index1, int index2);
};

#endif /* defined(__SpotTheDifference__IntArray__) */
