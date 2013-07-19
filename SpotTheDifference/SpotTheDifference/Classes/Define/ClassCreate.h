//
//  ClassCreate.h
//  TestDemo
//
//  Created by zhengkaiyuan on 13-4-25.
//
//

#ifndef __TestDemo__ClassCreate__
#define __TestDemo__ClassCreate__

#include <string>
#include <map>
#include <iostream>
#include "cocos2d.h"
#include "ClassInclude.h"

USING_NS_CC;
using namespace std;

static bool sameClass(const char* object_name,const char* className)
{
    string objectname = object_name;
    int index = objectname.find(className);
    if(index==-1)
        return false;
    else
        return true;
}

static string class_type[] ={"GameContent"};
enum Class_Type
{
    class_Null=-1,
    class_GameContent,
};
static CCObject* createClass(const char* className)
{
    CCObject* obj = NULL;
    string cName = className;
    int typeLen = sizeof(class_type)/sizeof(class_type[0]);
    Class_Type typeId = class_Null;
    for(int i = 0 ;i< typeLen;++i)
    {
        if(cName.find(class_type[i])!=-1)
        {
            typeId = (Class_Type)i;
            
            break;
        }
        if(i == typeLen-1)
        {           
            CCLog("类%s没有预定义",className);
            return NULL;
        }      
    
    }
    switch (typeId) {
        case class_GameContent:
//            obj =  GameContent::Create(className);//Teach::Create(className);
            break;
        default:
            CCLOG("无效返回 typeId = %d",typeId);
            break;
    }
return obj;

}



//****************************************************
//#include <iostream>
//
//#include <string>
//#include <map>
//#include <iostream>
//
//using namespace std;
//
//typedef void*  (*CreateClass)(void);
//
//class ClassFactory {
//    
//    
//public:
//    static void* GetClassByName(string className)
//    {
//        map<string,CreateClass>::const_iterator iter;
//		iter = m_classMap.find(className);
//		if(iter==m_classMap.end())
//			return NULL;
//		else
//			return iter->second();
//    };
//     static void RegistClass(string sName,CreateClass csMethod)
//    {
//        m_classMap.insert(pair<string,CreateClass>(sName, csMethod));
//    };
//    
//private:
//    static map<string, CreateClass> m_classMap;
//};
//
//
//map<string, CreateClass> ClassFactory::m_classMap;
//
///*@动态创建类,动态创建的类通过包含该类的一个静态对象
// *向类工厂里注册自己的创建对象函数
// */
//class GenDynamic
//{
//public:
//	GenDynamic(string sName,CreateClass csMethod)
//	{
//		ClassFactory::RegistClass(sName, csMethod);
//	}
//};
//static void* createClass(const char* className)
//{
//    return  ClassFactory::GetClassByName(className);
//}
//
//static bool sameClass(const char* object_name,const char* className)
//{
//    string objectname = object_name;
//    int index = objectname.find(className);
//    if(index==-1)
//        return false;
//    else
//        return true;
//}
//
///*@定义宏,类通过包含该宏,实现动态创建*/
//#define DECLARE_RUNTIME(class_name)\
//public :static void * CreateInstance();\
//public :static GenDynamic* class_name##gd
//
////string class_name##Name;\
//
///*@宏实现,类通过实现该宏,实现动态创建*/
//#define IMPLEMENT_RUNTIME(class_name)\
//void * class_name::CreateInstance(){return new class_name;}\
//GenDynamic* class_name::class_name##gd = new GenDynamic(#class_name,class_name::CreateInstance);

#endif /* defined(__TestDemo__ClassCreate__) */


