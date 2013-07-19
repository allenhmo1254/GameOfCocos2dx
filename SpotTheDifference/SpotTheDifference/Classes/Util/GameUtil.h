//
//  GameUtil.h
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#ifndef __SpotTheDifference__GameUtil__
#define __SpotTheDifference__GameUtil__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "../PublicData/BaseData.h"

using namespace cocos2d;
using namespace extension;

class IntArray;
class DataInputStream;
class GameUtil : public CCObject {
public:
    //读取mac地址
    static CCString * getMacId();
    
    //动作编辑器的方法
    static CCData * getStream(CCString * path);
    static Short1DArray loadOneShort(DataInputStream *dis);
    static Short2DArray loadTwoShort(DataInputStream *dis);
    static Short2DArray  formatData (Short1DArray data,int size);
    static Short1DArray arrayAppend(Short1DArray src,short add [],int size);
    static IntArray* getCollisionRectAtFrameId(int frameId, Short1DArray data);
    
    
    //读取excel文件的方法
    static Byte2DArray  readXlsByte2D(CCString *path);
    static Short2DArray  readXlsShort2D(CCString *path);
    static Int2DArray  readXlsINT2D(CCString *path);
    static CCArray * readXlsUTF2D(CCString *path);
    
    
    //得到精灵图片路径的数组（0：路径总数组   1：头字母   2：索引）
    static CCArray * getImageFileArray(CCString * file ,CCString *name);
    static CCArray * getStringArrayWithString(CCString * file);
    static CCDictionary * getGestureDictionaryWithFile(CCString * flie);
    static CCString * formatString(CCString * file);
    
    
    static CCDictionary * getDictionaryWithPlistFile(CCString * file);
    static CCArray * getArrayWithPlistFile(CCString * file);
    static CCArray * getPVRStringArrayWithString(CCString * file);
    
    static CCString* substring(CCString *str, int startIndex);
    static CCString* substring(CCString *str, int startIndex, int endIndex);
};

#endif /* defined(__SpotTheDifference__GameUtil__) */
