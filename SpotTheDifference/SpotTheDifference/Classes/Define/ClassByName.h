#ifndef _CLASSBY_NAME_H
#define _CLASSBY_NAME_H

#include <string>
#include <map>
#include <iostream>
using namespace std;
// 用于声明具有动态创建功能的基类
#define DECLARE_DYNCRT_BASE(base) \
public: \
typedef base* (*ClassGen)(); \
static void Register(string class_name, ClassGen class_gen) \
{ \
    class_set.insert(map<string, ClassGen>::value_type(class_name, class_gen)); \
} \
public: \
static base* Create(string class_name) \
{ \
    map<string, ClassGen>::iterator iter; \
    if((iter = class_set.find(class_name)) != class_set.end()) \
    { \
        return ((*iter).second)(); \
    } \
    return NULL; \
} \
protected: \
static map<string, ClassGen> class_set;

// 用于实现基类
#define IMPLEMENT_DYNCRT_BASE(base) \
map<string, base::ClassGen> base::class_set;

// 用于声明一个能够被动态创建的类
#define DECLARE_DYNCRT_CLASS(derived, base) \
public: \
struct derived##Register \
{ \
    derived##Register() \
    { \
        static bool bRegistered = false; \
        if(!bRegistered) \
        { \
            base::Register(#derived, Create); \
            bRegistered = true; \
        } \
    } \
}; \
static base* Create() \
{ \
    return new derived; \
}

// 用于实现一个能够被动态创建的类
#define IMPLEMENT_DYNCRT_CLASS(derived) \
static derived::derived##Register derived##_for_registering;


#endif