//
//  Define.h
//  SMSDX
//
//  Created by cwa leiting on 13-2-21.
//
//

#ifndef __SMSDX__Define__
#define __SMSDX__Define__
#include <string>
#define NO false
#define YES true

#define nil NULL
#define BOOL bool
typedef unsigned int ALuint;
typedef float CGFloat;
typedef int NSInteger;
typedef unsigned int NSUInteger;
typedef unsigned int uint32_t;
typedef unsigned char  Byte;
typedef double CFTimeInterval;

#define CCLocalizedStringFromTable(key, tbl, comment) \
CCBundle::mainBundle()->localizedStringForKey(key,"",tbl)

#define LEN 21

const std::string FILE_NAME[LEN]={
   "achievement","buff","build","ButtonTitle","dailyMissionDescription",
    "dailyMissionName","decoration","decorationEffect","FarmEventTalkWord","help",
    "horse","item","jewel","LocalNotification","mainMissionDescription",
    "mainMissionName","match","playerLevel","skill","upGradeTishiInfo","UIStrings"};

#define CCStringCreate(string) \
CCString::create(string)


//动态创建对象
#define CCClassFromString(class_name)\
createClass(class_name);

//对象与类名字符比较判断
#define CCObjectIsKindofClass(objectName,className)\
sameClass(objectName,className)
#endif /* defined(__SMSDX__Define__) */
