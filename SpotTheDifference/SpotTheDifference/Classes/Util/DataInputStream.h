//
//  DataInputStream.h
//  MyBox2d
//
//  Created by  陈广文 on 12-12-21.
//
//

#ifndef __MyBox2d__DataInputStream__
#define __MyBox2d__DataInputStream__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
class DataInputStream:public cocos2d::CCObject{
private:
    unsigned char * buffer;
	int pvrlen ;
	int position ;
    
public:
    DataInputStream();
    ~DataInputStream();
    static DataInputStream* create(const char* path);
    virtual bool open(const char*path);
    virtual int   readInt();
    virtual short readShort();
    virtual char  readByte();
    virtual unsigned const char* readUTF();
    virtual void close();
    virtual  int length();
    unsigned char* subdataWithRange(int nLen);
    cocos2d::CCString* readUTF(int nLen);
    static const char* getPath(const cocos2d::CCString path);
public:
    static int indexOf(std::string str,const char* ch,int fromIndex){
        return str.find(ch, fromIndex);
    }
    static std::string substring(std::string str,int startIndex,int endIndex){
        return str.substr(startIndex,endIndex-startIndex);
    }
    static cocos2d::CCString* stringByReplacingOccurrencesOfString(cocos2d::CCString* str,std::string flag,std::string replace);
    static std::string substring(std::string str,int startIndex){
        
        return str.substr(startIndex,str.length()-startIndex);
        
    }
};
#endif /* defined(__MyBox2d__DataInputStream__) */
