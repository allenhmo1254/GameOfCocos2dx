#include "CCBValue.h"

using namespace cocos2d;

NS_CC_EXT_BEGIN

// Implementation of ccColor3BWapper

ccColor3BWapper* ccColor3BWapper::create(const ccColor3B& color)
{
    ccColor3BWapper *ret = new ccColor3BWapper();
    if (ret)
    {
        ret->color.r = color.r;
        ret->color.g = color.g;
        ret->color.b = color.b;
        
        ret->autorelease();
    }
    
    return ret;
}

const ccColor3B& ccColor3BWapper::getColor() const
{
    return color;
}

// Implementation of CCBValue

CCBValue* CCBValue::create(int nValue)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->mValue.nValue = nValue;
        ret->mType = kIntValue;
        ret->autorelease();
    }
    
    return ret;
}

CCBValue* CCBValue::create(float fValue)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->mValue.fValue = fValue;
        ret->mType = kFloatValue;
        ret->autorelease();
    }
    
    return ret;
}

CCBValue* CCBValue::create(bool vValue)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->mValue.nValue = vValue ? 1 : 0;
        ret->mType = kBoolValue;
        ret->autorelease();
    }
    
    return ret;
}

CCBValue* CCBValue::create(unsigned char byte)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->mValue.nValue = byte;
        ret->mType = kUnsignedCharValue;
        ret->autorelease();
    }
    
    return ret;
}

CCBValue* CCBValue::create(const char *pStringValue)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->m_strValue = pStringValue;
        ret->mType = kStringValue;
        ret->autorelease();
    }
    
    return ret;
}


CCBValue* CCBValue::create(CCArray *pArrValue)
{
    CCBValue *ret = new CCBValue();
    if (ret)
    {
        ret->m_arrValue = pArrValue;
        ret->mType = kArrayValue;
        ret->autorelease();
    }
    
    return ret;
}


int CCBValue::getIntValue()
{
    assert(mType == kIntValue);
    
    return mValue.nValue;
}

float CCBValue::getFloatValue()
{
    assert(mType == kFloatValue);
    
    return mValue.fValue;
}

bool CCBValue::getBoolValue()
{
    assert(mType == kBoolValue);
    
    return mValue.nValue == 1 ? true : false;
}

unsigned char CCBValue::getByteValue()
{
    assert(mType = kUnsignedCharValue);
    
    return (unsigned char)(mValue.nValue);
}

CCArray* CCBValue::getArrayValue() {
    assert(mType == kArrayValue);
    
    return m_arrValue;
}


const char* CCBValue::getStringValue()
{
    assert(mType == kStringValue);
    
    return m_strValue.c_str();
}

int CCBValue::getType()
{
    return mType;
}


CCBValue * CCBValue::valueWithCCPoint(cocos2d::CCPoint point)
{
    CCBValue *value = new CCBValue();
    if(value)
    {
        value->point_.x=point.x;
        value->point_.y=point.y;
        value->autorelease();
        return value;
    }
    
    CC_SAFE_DELETE(value);
    return NULL;
    
}

CCBValue *CCBValue::valueWithCCRect(cocos2d::CCRect rect)
{
    
    CCBValue *value = new CCBValue();
    if(value)
    {
        value->rect_.setRect(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
        value->autorelease();
        return value;
    }
    CC_SAFE_DELETE(value);
    
    return NULL;
}


CCPoint CCBValue::getCCPointValue()
{
    
    CCPoint point =CCPoint(point_.x, point_.y);
    return point;
}

CCRect CCBValue::getCCRectValue()
{
    CCRect rect= CCRect(rect_.origin.x, rect_.origin.y, rect_.size.width, rect_.size.height);
    return  rect;
}


NS_CC_EXT_END
