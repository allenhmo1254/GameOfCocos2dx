//
//  DataInputStream.cpp
//  MyBox2d
//
//  Created by  陈广文 on 12-12-21.
//
//

#include "DataInputStream.h"
#include "cocos2d.h"
#include "Util.h"
USING_NS_CC;
DataInputStream::DataInputStream(){
}
DataInputStream::~DataInputStream(){
    free(buffer);
    buffer = NULL;
}
DataInputStream*DataInputStream::create(const char *path){
    DataInputStream* temp=new DataInputStream();
    if(temp){
        temp->open(path);
        temp->autorelease();
    }
    return temp;
}
cocos2d::CCString* DataInputStream::stringByReplacingOccurrencesOfString(cocos2d::CCString* str,std::string flag,std::string replace){
    
    std::string temp="";
    int start=0,end=-1;
    while ((end=indexOf(str->getCString(),flag.c_str(),start))!=-1) {
        //         CCLog("end %d --------------------start %d ",end,start);
        temp+=substring(str->getCString(), start, end);
        temp+=replace;
        start=end+flag.length();
    }
    temp+=substring(str->getCString(), start);
    //     CCLog("stringByReplacingOccurrencesOfString temp-------------------- %s ",temp.c_str());
    return CCString::create(temp);
}
unsigned const char* DataInputStream::readUTF(){
    //    if(encode=="GBK"){
    return buffer;
    //    }else{
    //
    //    }
    
}

int DataInputStream::length(){
    return pvrlen;
}
const char* DataInputStream::getPath(const cocos2d::CCString path){
    CCLOG("DataInputStream path =%s",path.getCString());
    std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(path.getCString());
    return fullPath.c_str();
}
unsigned char* DataInputStream::subdataWithRange(int nLen){
    unsigned char* pStr =new unsigned char[nLen];
    if (pStr != NULL)
    {
        if (nLen > 0)
        {
            memcpy(pStr, buffer+position, nLen);
            position+=nLen;
            
        }
    }
    
    
    
    return pStr;
}
//读取文字
cocos2d::CCString* DataInputStream::readUTF(int length)
{
    unsigned char*d   = subdataWithRange(length);
    cocos2d::CCString *str = CCString::createWithData(d,length);
    return str;
}

bool DataInputStream::open(const char *path){
    buffer=NULL;
    pvrlen = 1;
    position = 0;
	CCFileUtils *fUtils=CCFileUtils::sharedFileUtils();
    const char* datapath=getPath(path);
    if(strcmp(datapath, path)==0)
    {
        CCLog(" 获取完全路径失败,  path=%s",path);
        return NULL;
    }
	buffer = fUtils->getFileData(datapath, "rb", (unsigned long *)(&pvrlen));
    
	if(pvrlen == 0)
	{
		return false;
	}
    return true;
}
int DataInputStream::readInt(){
	int temp = 0;
	for(int i = 0;i < 4;i++){
		int shift = (4-1-i)  * 8;
		temp |= (buffer[(position)] & 0x000000ff) << shift;
        
		(position)++;
	}
	return temp;
}

short DataInputStream::readShort(){
	short temp = 0;
	temp = buffer[(position)] << 8;
	(position)++;
	temp |= (buffer[(position)] & 0xff);
	(position)++;
	return temp;
}

char DataInputStream::readByte(){
	char temp = 0;
	temp =(buffer[(position)] & 0xff);
	(position)++;
    return temp;
}
void DataInputStream::close(){
    
}