//
//  ActionData.cpp
//  SpotTheDifference
//
//  Created by leitingzu on 13-7-19.
//
//

#include "ActionData.h"
#include "GameUtil.h"
#include "DataInputStream.h"

using namespace cocos2d;
using namespace extension;

ActionData::ActionData()
:actionFile_(NULL),
module_(NULL),
frame_(NULL),
action_(NULL),
colRect_(NULL),
attRect_(NULL)
{
    
}


ActionData::~ActionData(){
    clearShort1DArray(&module_);
    clearShort2DArray(&frame_);
    clearShort2DArray(&action_);
    clearShort2DArray(&colRect_);
    clearShort2DArray(&attRect_);
}


bool ActionData::initWithFile(cocos2d::CCString *path)
{
    DataInputStream *dis = DataInputStream::create(path -> getCString());
    if (!dis) {
        return false;
    }
    module_ = GameUtil::loadOneShort(dis);
    frame_ = GameUtil::loadTwoShort(dis); //frame
    action_ =  GameUtil::loadTwoShort(dis); //action
    
    Short1DArray tempColRect = GameUtil::loadOneShort(dis);
    if (tempColRect) {
        colRect_ = GameUtil::formatData(tempColRect, frame_ -> length);
    }
    Short1DArray tempAttRect = GameUtil::loadOneShort(dis);
    if (tempAttRect) {
        attRect_ = GameUtil::formatData(tempAttRect, frame_ -> length);
    }
    
    return true;
}



ActionData* ActionData::createWithFile(cocos2d::CCString *path)
{
    ActionData* data = new ActionData();
    if (data && data -> initWithFile(path)) {
        data -> autorelease();
        return data;
    } else {
        delete data;
        data = NULL;
        return NULL;
    }
}
