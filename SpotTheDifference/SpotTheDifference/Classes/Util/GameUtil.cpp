//
//  GameUtil.cpp
//  SpotTheDifference
//
//  Created by 景 中杰 on 13-7-18.
//
//

#include "GameUtil.h"
#include <sys/socket.h>
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>
#include <cctype>
#include <algorithm>
#include <string>
#include "IntArray.h"
#include "DataInputStream.h"
#include "../PublicData/CCRange.h"


CCString * GameUtil::getMacId()
{
    
    int                    mib[6];
    
    size_t                len;
    
    char                *buf;
    
    unsigned char        *ptr;
    
    struct if_msghdr    *ifm;
    
    struct sockaddr_dl    *sdl;
    
    
    mib[0] = CTL_NET;
    
    mib[1] = AF_ROUTE;
    
    mib[2] = 0;
    
    mib[3] = AF_LINK;
    
    mib[4] = NET_RT_IFLIST;
    
    
    if ((mib[5] = if_nametoindex("en0")) == 0) {
        
        printf("Error: if_nametoindex error/n");
        
        return NULL;
        
    }
    
    
    if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
        
        printf("Error: sysctl, take 1/n");
        
        return NULL;
        
    }
    
    
    
    
    if ((buf = (char *)malloc(len)) == NULL) {
        
        printf("Could not allocate memory. error!/n");
        
        return NULL;
        
    }
    
    
    if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
        
        printf("Error: sysctl, take 2");
        
        return NULL;
        
    }
    
    
    ifm = (struct if_msghdr *)buf;
    
    sdl = (struct sockaddr_dl *)(ifm + 1);
    
    ptr = (unsigned char *)LLADDR(sdl);
    
    CCString *outstring=CCString::createWithFormat("%02x%02x%02x%02x%02x%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5) );
    
    free(buf);
    
    //转换成大写
    std::transform(outstring->m_sString.begin(), outstring->m_sString.end(), outstring->m_sString.begin(), toupper);
    
    return outstring;
    
    
}



CCData * GameUtil::getStream(CCString *path)
{
    
    CCFileUtils *fUtil=CCFileUtils::sharedFileUtils();
    std::string datapath=fUtil->fullPathForFilename(path->m_sString.c_str() );
    
    if(path == NULL){
        CCLog("data is Empty");
        return NULL;
    }
    
    if(strcmp(datapath.c_str(), path->getCString())==0)
    {
        CCLog(" 获取完全路径失败,  path=%s",path->getCString());
        return NULL;
    }
    
    unsigned long flag=0;
    unsigned char *buffer=fUtil->getFileData(datapath.c_str(), "rb", &flag);
    
    
    
    CCData *tempdata=new CCData(buffer,flag);
    CC_SAFE_DELETE_ARRAY(buffer);
    
    return tempdata;
}


Short1DArray GameUtil::loadOneShort(DataInputStream *dis)
{
    short firstlength = dis -> readShort();// 第1维数据数量
    
    short singleDataLength = dis -> readShort();// 每组数据长度
    
    int totalLength = firstlength * singleDataLength;//获得总长度
    
    Short1DArray des = (Short1DArray)malloc(sizeof(Short1ArrayStruct));
    des -> value = (short *)malloc(sizeof(short) * totalLength);
    des -> length = totalLength;
    
    for (int i = 0; i < totalLength; i++) {
        des -> value[i] = dis -> readShort();
    }
    return des;
}



Short2DArray GameUtil::loadTwoShort(DataInputStream *dis)
{
    short firstlength = dis -> readShort();// 第1维数据数量
    
    short singleDataLength = dis -> readShort();// 每组数据长度
    
    Short2DArray des = (Short2DArray)malloc(sizeof(Short2ArrayStruct));
    des -> value = (Short1DArray*)malloc(sizeof(Short1DArray) * firstlength);
    des -> length = firstlength;
    
    for (int i = 0; i < firstlength; i++) {
        short secondlength = dis -> readShort();// 第2维数据数量
        short totalLength = secondlength * singleDataLength;
        des -> value[i] = (Short1DArray)malloc(sizeof(Short1ArrayStruct));
        des -> value[i] -> value = (short *)malloc(sizeof(short) * totalLength);
        des -> value[i] -> length = totalLength;
        
        for (int j = 0; j < totalLength; j++) {
            des -> value[i] -> value[j] = dis -> readShort();
        }
    }
    return des;
}


IntArray* GameUtil::getCollisionRectAtFrameId(int frameId, Short1DArray data)
{
    IntArray *array = IntArray::create();
    for (int i = 0, count = data -> length / 5; i < count; i ++) {
        if (data -> value[i * 5] == frameId) {
            array -> addInt(data -> value[i * 5 + 1]);
            array -> addInt(data -> value[i * 5 + 2]);
            array -> addInt(data -> value[i * 5 + 3]);
            array -> addInt(data -> value[i * 5 + 4]);
        }
    }
    return array;
}



Short2DArray GameUtil::formatData(Short1DArray data,int size)
{
    if (data == NULL) {
        return NULL;
    }
    int i, j, count;
    
    Short2DArray des = (Short2DArray)malloc(sizeof(Short2ArrayStruct));
    initShort2DArray(&des, 1, size, 0);
    for (i = 0; i < size; i ++) {
        IntArray *array = getCollisionRectAtFrameId(i, data);
        initShort2DArray(&des, 2, array -> count(), i);
        for (j = 0, count = getShort2DArrayLength(&des, 2, i); j < count; j ++) {
            setShort2DArrayValue(&des, array -> intAtIndex(j), i, j);
        }
    }
    
    clearShort1DArray(&data);
    return des;
}


Short1DArray GameUtil::arrayAppend(Short1DArray src ,short add[],int size)
{
    int pos = 0;
    int len = 0;
    Short1DArray temp;
    if (src != NULL)
    {
        pos = src -> length;
    }
    len = pos + size;
    temp = (Short1DArray)malloc(sizeof(Short1ArrayStruct));
    initShort1DArray(&temp, len);
    if (src != NULL)
    {
        for (int i = 0; i < src -> length; i ++) {
            temp -> value[i] = src -> value[i];
        }
    }
    for (int i = 0; i < size; i ++) {
        temp -> value[i + pos] = add[i];
    }
    return temp;
    
}



Byte2DArray GameUtil::readXlsByte2D(CCString *path)
{
    DataInputStream* dis=DataInputStream::create(path->getCString());
    Byte2DArray xls2DByteData_ = (Byte2DArray)malloc(sizeof(Byte2ArrayStruct));
    int firstlength = dis -> readInt();
    int secondlength = dis -> readInt();
    initByte2DArray(&xls2DByteData_, 1, firstlength, 0);
    for (int i = 0; i < firstlength; i ++) {
        initByte2DArray(&xls2DByteData_, 2, secondlength, i);
        for (int j = 0; j < secondlength; j ++) {
            xls2DByteData_ -> value[i] -> value[j] = dis -> readShort();
        }
    }
    
    return xls2DByteData_;
}




Short2DArray GameUtil::readXlsShort2D(CCString *path)
{
    DataInputStream* dis=DataInputStream::create(path->getCString());
    Short2DArray xls2DShortData_ = (Short2DArray)malloc(sizeof(Short2ArrayStruct));
    int firstlength = dis -> readInt();
    int secondlength = dis -> readInt();
    initShort2DArray(&xls2DShortData_, 1, firstlength, 0);
    for (int i = 0; i < firstlength; i ++) {
        initShort2DArray(&xls2DShortData_, 2, secondlength, i);
        for (int j = 0; j < secondlength; j ++) {
            xls2DShortData_ -> value[i] -> value[j] = dis -> readShort();
        }
    }
    
    return xls2DShortData_;
}




Int2DArray GameUtil::readXlsINT2D(CCString *path)
{
    DataInputStream* dis=DataInputStream::create(path->getCString());
    Int2DArray xls2DIntData_ = (Int2DArray)malloc(sizeof(Int2ArrayStruct));
    int firstlength = dis -> readInt();
    int secondlength = dis -> readInt();
    initInt2DArray(&xls2DIntData_, 1, firstlength, 0);
    for (int i = 0; i < firstlength; i ++) {
        initInt2DArray(&xls2DIntData_, 2, secondlength, i);
        for (int j = 0; j < secondlength; j ++) {
            xls2DIntData_ -> value[i] -> value[j] = dis -> readInt();
        }
    }
    return xls2DIntData_;
}



CCArray * GameUtil::readXlsUTF2D(CCString *path)
{
    DataInputStream* dis=DataInputStream::create(path->getCString());
    CCArray *xls2DUTFData_= CCArray::create();
    xls2DUTFData_ -> retain();
    
    int firstlength = dis->readInt();
    int secondlength = dis->readInt();
    
    for (int i = 0; i < firstlength; i ++) {
        CCArray *tempArray1_ = CCArray::create();
        
        for (int j = 0; j < secondlength; j ++) {
            CCString *str = dis->readUTF(dis->readShort());
            tempArray1_->addObject( str);
        }
        
        xls2DUTFData_->addObject(tempArray1_);
        
    }
    return xls2DUTFData_;
}



CCArray * GameUtil::getImageFileArray(CCString * file,CCString *name)
{
    CCString *source = file;
    CCArray *tempArray_ = CCArray::create();
    
    int index0 = 0; // 两个指向字符串中字符的索引。
    int index1 = -1;
    CCString *tempstr;
    
    while (index0 < source->length()) {
        index1 ++;
        if (index1 > source->length() - 1) {
            tempstr=CCString::createWithFormat("%s%s.png",name->getCString(), (source->m_sString.substr(index0,source->length()-index0) ).c_str() );
            tempArray_->addObject(tempstr);
            break;
        }
        if(source->m_sString.at(index1)==',')
        {
            tempstr=CCString::createWithFormat("%s%s.png", name->getCString(), (source->m_sString.substr(index0,index1-index0)).c_str() );
            tempArray_->addObject(tempstr);
            index0 = index1 + 1;
        }
    }
    
    return tempArray_;
}


CCArray * GameUtil::getStringArrayWithString(CCString * file)
{
    CCString *s = file;
    CCArray *tempArray_ = CCArray::create();
    
    int  index0=0;
    int index1=-1;
    CCRange temprange;
    
    while (index0 < s->length()) {
        index1 ++;
        if (index1 > s->length() - 1 ) {
            CCString *temp=CCString::create(s->m_sString.substr(index0));
            tempArray_->addObject(temp);
            
            break;
        }
        if(s->m_sString.at(index1) == ','){
            temprange.location = index0;
            temprange.length = index1 - index0;
            tempArray_->addObject(CCString::create(s->m_sString.substr(temprange.location,temprange.length)));
            index0=index1+1;
        }
    }
    
    
    return tempArray_;
}


CCDictionary * GameUtil::getGestureDictionaryWithFile(CCString *flie)
{
    CCDictionary *output = CCDictionary::create();
    CCString * file_ = CCString::createWithFormat("%s.plist",flie->getCString());
    
    CCDictionary *dic = CCDictionary::createWithContentsOfFile(file_->getCString());
    
    for (int i = 0; i < dic->allKeys()->count(); i ++) {
        
        CCString *key= ( CCString *)dic->allKeys()->objectAtIndex(i);
        CCString *temp=(CCString *)dic->objectForKey(key->m_sString);
        
        CCString *value=formatString(temp);
        CCArray *tempArray=getStringArrayWithString(value);
        
        CCArray *points=CCArray::create();
        
        
        for (int j = 0, length1 = tempArray->count(); j < length1 - 1; j += 2) {
            CCPoint tempPoint=ccp( ((CCString *)tempArray->objectAtIndex(j))->floatValue(), ((CCString *)tempArray->objectAtIndex(j+1))->floatValue() );
            points->addObject(CCBValue::valueWithCCPoint(tempPoint));
            
        }
        
        output->setObject(points, key->m_sString);
        
    }
    
    return output;
}


CCString * GameUtil::formatString(CCString *file)
{
    CCString *s = file;
    CCString *mutableString=CCString::create("");
    
    int index0 = 0; // 两个指向字符串中字符的索引。
    int index1 = -1;
    CCRange temprange;
    std::string tempstr;
    
    while (index0 < s->length()) {
        index1 ++;
        
        if(s->m_sString.at(index1) == '['){
            index1 ++;
            index0 = index1;
        } else if (s->m_sString.at(index1) == ']'){
            temprange.location = index0;
            temprange.length = 1;
            tempstr=s->m_sString.substr(temprange.location,temprange.length);
            
            mutableString->m_sString.append(tempstr);
            index1++;
            index0=index1;
            
        } else {
            temprange.location=index0;
            temprange.length=1;
            tempstr=s->m_sString.substr(temprange.location,temprange.length);
            mutableString->m_sString.append(tempstr);
            index0=index1;
        }
    }
    return mutableString;
}


CCDictionary * GameUtil::getDictionaryWithPlistFile(CCString * file)
{
    CCString *file_ = CCString::createWithFormat("%s.plist",file->getCString());
    
    CCDictionary *output = CCDictionary::createWithContentsOfFile(file_->getCString());
    
    return output;
}


CCArray * GameUtil::getArrayWithPlistFile(CCString * file)
{
    
    CCString * file_ = CCString::createWithFormat("%s.plist",file->getCString() );
    
    CCArray *output = CCArray::createWithContentsOfFile(file_->getCString());
    
    return output;
}


CCString* GameUtil::substring(CCString *str, int startIndex)
{
    std::string string = str -> m_sString;
    
    return cocos2d::CCString::create(string.substr(startIndex,string.length()-startIndex));
}

CCString* GameUtil::substring(CCString *str, int startIndex, int endIndex)
{
    std::string string = str -> m_sString;
    
    return cocos2d::CCString::create(string.substr(startIndex,endIndex-startIndex));
}


CCArray * GameUtil::getPVRStringArrayWithString(CCString * file)
{
    CCString *s = file;
    CCArray *tempArray_ = CCArray::create();
    
    int index0 = 0; // 两个指向字符串中字符的索引。
    int index1 = -1;
    CCRange temprange;
    
    while (index0 < s->length() ) {
        index1 ++;
        if (index1 > s->length() - 1) {
            CCString *string = substring(s, index0);
            string = DataInputStream::stringByReplacingOccurrencesOfString(string, "png", "pvr.ccz");
            tempArray_->addObject(string);
            break;
        }
        if( s->m_sString.at(index1) == ','){
            temprange.location = index0;
            temprange.length = index1 - index0;
            CCString *string = substring(s, index0, index1 - index0);
            string = DataInputStream::stringByReplacingOccurrencesOfString(string, "png" , "pvr.ccz");
            tempArray_->addObject(string);
            index0 = index1 + 1;
        }
    }
    
    return tempArray_;
}



