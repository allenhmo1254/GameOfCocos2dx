//
//  BaseData.h
//  SpotTheDifference
//
//  Created by leitingzu on 13-7-19.
//
//

#ifndef SpotTheDifference_BaseData_h
#define SpotTheDifference_BaseData_h

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;


#define getLength(x) (sizeof(x)/sizeof(__typeof__(x)))
//#define charToNSStr(str) [[[NSString alloc]initWithCString:str] autorelease]
#define charToNSStr(str) CCString::create(str)

//#define intToNSStr(v) [[[NSString alloc]initWithString:[NSString stringWithFormat:@"%d",v]] autorelease]
#define intToNSStr(v) CCString::create(CCString::createWithFormat("%d",v)->getCString())

//#define addHashTableValue(_hash_,_value_,_key_) [_hash_ setObject:_value_ forKey:charToNSStr(_key_)]
#define addHashTableValue(_hash_,_value_,_key_) _hash_->setObject(_value_,charToNSStr(_key_))

//#define getHashTableValue(_hash_,_key_) [_hash_ objectForKey:charToNSStr(_key_)]
#define getHashTableValue(_hash_,_key_) _hash_->objectForKey(charToNSStr(_key_))

/** @def tmSWAP
 交换两变量
 */
#define tmSWAP( x, y )			\
({ __typeof__(x) temp  = (x);		\
x = y; y = temp;		\
})

/** @def tmRANDOM_MINUS1_1
 随机－1到1的数
 */
#define tmRANDOM_MINUS1_1() ((random() / (float)0x3fffffff )-1.0f)

/** @def tmRANDOM_0_1
 随机0－1的数
 */
#define tmRANDOM_0_1() ((random() / (float)0x7fffffff ))

/** @def tmDegreesToRadians
 角度转弧度
 */
#define tmDEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) * 0.01745329252f) // PI / 180

/** @def tmRADIANS_TO_DEGREES
 弧度转角度
 */
#define tmRADIANS_TO_DEGREES(__ANGLE__) ((__ANGLE__) * 57.29577951f) // PI * 180

//#pragma mark - --> 绘图

//#define getImage(str) [UIImage imageNamed:@str]
#define getImage(str) CCImage::create(str)

//#define tmRGB(r,g,b) [UIColor colorWithRed:r/255 green:g/255 blue:b/255 alpha:1]
#define tmRGB(r,g,b) ccc4(r/255,g/255,b/255,1)

//#define tmRGBA(r,g,b,a) [UIColor colorWithRed:r/255 green:g/255 blue:b/255 alpha:a/255]
#define tmRGBA(r,g,b,a) ccc4(r/255,g/255,b/255,a/255)

//#define tmlog(...) NSLog(@__VA_ARGS__)
#define tmlog(...) CCLog(__VA_ARGS__)

#define tmMalloc(_type_,_len_) (_type_*)malloc(sizeof(_type_) * (_len_))
#define tmMalloc2(_v_,_type_,_len_,_len2_) {\
_v_ = (_type_**)malloc(sizeof(_type_*) * _len_);\
for(int i=0;i<_len_;i++){\
_v_[i] = (_type_*)malloc(sizeof(_type_) * _len2_);\
}\
}

#define tmFree(_v_) free(_v_);_v_=NULL;

//#define charToNSStr(str) [[[NSString alloc]initWithCString:str] autorelease]


#define byteArrayToShort(data) ((data[0]&0xff)<<8 | (data[1]&0xff))

//定义byte型, 因为Byte是无符号类型,取值范围是0~255
typedef signed char byte;


#pragma mark -
#pragma mark 其他基本函数
/*
 * 函数名: randomInt
 * 参数: i_base作为一个基数, i_rangel是一个范围
 * 作用: 取值i_base~i_rangel的一个随机数
 */
static inline int randomIntAB(int i_base, int i_rangel)
{
	int i_back = i_base + arc4random() %(i_rangel - i_base); //这里用random的话, 每一次开始随机数的值都是一样的.
	return i_back;
}


/*
 * 函数名: randomInt
 * 参数: i_base作为一个基数, i_rangel是一个范围
 * 作用: 取值i_base~i_rangel的一个随机数
 */
static inline int randomIntAC(int i_base, int i_rangel)
{
	int i_back = i_base + arc4random() % i_rangel; //这里用random的话, 每一次开始随机数的值都是一样的.
	return i_back;
}




/*
 * 函数名: randomInt
 * 参数: i_base作为一个基数, i_rangel是一个范围
 * 作用: 取值i_base~i_rangel的一个随机数
 */
static inline int randomInt(int i_rangel)
{
	int i_back = arc4random()%i_rangel; //这里用random的话, 每一次开始随机数的值都是一样的.
	return i_back;
}


/*
 * 函数名: intersectRect
 * 参数: l0,t0,r0,b0分别是一个矩形的左上角和右下角的坐标, l左t上r右b下
 * 作用: 判断两个矩形是否相交
 */
static inline bool intersectRect(int l0, int t0, int r0, int b0, int l1, int t1, int r1, int b1)
{
	if(l0 < r1 && r0 > l1 && t0 < b1 && b0 > t1)
		return true;
	else
		return false;
}

/*
 * 函数名: pointerInRect
 * 参数: x, y表示角色的当前坐标, l,t,r,b矩形的范围(左上右下)
 * 作用: 判断当前的点是否在矩形框内
 */
static inline bool pointerInRect(int x, int y, int l, int t, int r, int b)
{
	return x >= l && x <= r && y >= t && y <= b;
}



//一维Float数组结构体及其方法----------------------------------------------------------------------------
typedef struct
{
    float *value;
    int length;
}*Float1DArray, Float1ArrayStruct;

static inline void initFloat1DArray(Float1DArray *array, short length){
    (*array) -> value = (float *)malloc(sizeof(float) * length);
    (*array) -> length = length;
    for (int i = 0; i < length; i ++) {
        (*array) -> value[i] = 0;
    }
}

static inline int getFloat1DArrayLength(Float1DArray *array){
    return (*array) -> length;
}

static inline void setFloat1DArrayValue(Float1DArray *array, float value, short index){
    if(index >= getFloat1DArrayLength(array)){
        return;
    }
    (*array) -> value[index] = value;
}

static inline float getFloat1DArrayValue(Float1DArray *array,short index){
    if(index >= getFloat1DArrayLength(array)){
        return -1;
    }
    return (*array) -> value[index];
}

static inline void clearFloat1DArray(Float1DArray *array){
    if(*array != NULL){
        free((*array)->value);
        (*array)->value = NULL;
        free(*array);
        *array = NULL;
    }
}




//二维float数组结构体及其方法----------------------------------------------------------------------------
typedef struct
{
	Float1DArray *value; //二维byte数组
    int length;//第一维的长度
}*Float2DArray, Float2ArrayStruct;


static inline void initFloat2DArray(Float2DArray *array,int type,short length,int index){
    switch (type) {
        case 1:
            (*array) -> value = (Float1DArray *)malloc(sizeof(Float1DArray) * length);
            (*array) -> length = length;
            break;
        case 2:
            (*array) -> value[index] = (Float1DArray)malloc(sizeof(Float1ArrayStruct));
            initFloat1DArray(&((*array)->value[index]), length);
            break;
    }
}

static inline int getFloat2DArrayLength(Float2DArray *array, int type, short index){
    switch (type) {
        case 1:
            return (*array) -> length;
        case 2:
            return getFloat1DArrayLength(&((*array)->value[index]));
        default:
            return -1;
    }
}


static inline void setFloat2DArrayValue(Float2DArray *array, float value, short index1, short index2){
    if(index1 >= getFloat2DArrayLength(array, 1, 0) || index2 >= getFloat2DArrayLength(array, 2, index1)){
        return;
    }
    setFloat1DArrayValue(&((*array)->value[index1]), value, index2);
}


static inline float getFloat2DArrayValue(Float2DArray *array, short index1, short index2){
    if(index1 >= getFloat2DArrayLength(array, 1, 0) || index2 >= getFloat2DArrayLength(array, 2, index1)){
        return -1;
    }
    return getFloat1DArrayValue(&((*array)->value[index1]),index2);
}

static inline void clearFloat2DArray(Float2DArray *array){
    int i = 0;
    if(*array != NULL){
        for(i = 0; i < (*array)->length; i++){
            clearFloat1DArray(&((*array)->value[i]));
        }
        free((*array) -> value);
        (*array) -> value = NULL;
        free(*array);
        *array = NULL;
    }
}






//一维Byte数组结构体及其方法----------------------------------------------------------------------------
typedef struct
{
    byte *value;
    int length;
}*Byte1DArray, Byte1ArrayStruct;

static inline void initByte1DArray(Byte1DArray *array, short length){
    (*array) -> value = (byte *)malloc(sizeof(byte) * length);
    (*array) -> length = length;
    for (int i = 0; i < length; i ++) {
        (*array) -> value[i] = 0;
    }
}

static inline int getByte1DArrayLength(Byte1DArray *array){
    return (*array) -> length;
}

static inline void setByte1DArrayValue(Byte1DArray *array, byte value, short index){
    if(index >= getByte1DArrayLength(array)){
        return;
    }
    (*array) -> value[index] = value;
}

static inline short getByte1DArrayValue(Byte1DArray *array,short index){
    if(index >= getByte1DArrayLength(array)){
        return -1;
    }
    return (*array) -> value[index];
}

static inline void clearByte1DArray(Byte1DArray *array){
    if(*array != NULL){
        free((*array)->value);
        (*array)->value = NULL;
        free(*array);
        *array = NULL;
    }
}


static inline Byte1DArray copyByte1DArray(Byte1DArray data)
{
    Byte1DArray tempdata = (Byte1DArray)malloc(sizeof(Byte1ArrayStruct));
    initByte1DArray(&tempdata, data -> length);
    for (byte i = 0, length = tempdata -> length; i < length; i++) {
        setByte1DArrayValue(&tempdata, data -> value[i], i);
    }
    return tempdata;
}




//二维byte数组结构体及其方法----------------------------------------------------------------------------
typedef struct
{
	Byte1DArray *value; //二维byte数组
    int length;//第一维的长度
}*Byte2DArray, Byte2ArrayStruct;


static inline void initByte2DArray(Byte2DArray *array,int type,short length,int index){
    switch (type) {
        case 1:
            (*array) -> value = (Byte1DArray *)malloc(sizeof(Byte1DArray) * length);
            (*array) -> length = length;
            break;
        case 2:
            (*array) -> value[index] = (Byte1DArray)malloc(sizeof(Byte1ArrayStruct));
            initByte1DArray(&((*array)->value[index]), length);
            break;
    }
}

static inline int getByte2DArrayLength(Byte2DArray *array, int type, short index){
    switch (type) {
        case 1:
            return (*array) -> length;
        case 2:
            return getByte1DArrayLength(&((*array)->value[index]));
        default:
            return -1;
    }
}


static inline void setByte2DArrayValue(Byte2DArray *array, byte value, short index1, short index2){
    if(index1 >= getByte2DArrayLength(array, 1, 0) || index2 >= getByte2DArrayLength(array, 2, index1)){
        return;
    }
    setByte1DArrayValue(&((*array)->value[index1]), value, index2);
}


static inline byte getByte2DArrayValue(Byte2DArray *array, short index1, short index2){
    if(index1 >= getByte2DArrayLength(array, 1, 0) || index2 >= getByte2DArrayLength(array, 2, index1)){
        return -1;
    }
    return getByte1DArrayValue(&((*array)->value[index1]),index2);
}

static inline void clearByte2DArray(Byte2DArray *array){
    int i = 0;
    if(*array != NULL){
        for(i = 0; i < (*array)->length; i++){
            clearByte1DArray(&((*array)->value[i]));
        }
        free((*array) -> value);
        (*array) -> value = NULL;
        free(*array);
        *array = NULL;
    }
}


static inline Byte2DArray copyByte2DArray(Byte2DArray data)
{
    Byte2DArray tempdata = (Byte2DArray)malloc(sizeof(Byte2ArrayStruct));
    initByte2DArray(&tempdata, 1, data -> length, 0);
    for (byte i = 0, length = tempdata -> length; i < length; i++) {
        initByte2DArray(&tempdata, 2, getByte2DArrayLength(&data, 2, i), i);
        for (int j = 0, length = getByte2DArrayLength(&tempdata, 2, i); j < length; j++) {
            setByte2DArrayValue(&tempdata, getByte2DArrayValue(&data, i, j), i, j);
        }
    }
    return tempdata;
}




//三维Byte数组结构体及其方法----------------------------------------------------------------------------
typedef struct
{
    Byte2DArray *value;
    int length;
}*Byte3DArray, Byte3ArrayStruct;

static inline void initByte3DArray(Byte3DArray *array, int type, short length, int index1, int index2){
    switch (type) {
        case 1:
            (*array) -> value = (Byte2DArray *)malloc(sizeof(Byte2DArray) * length);
            (*array) -> length = length;
            break;
        case 2:
            (*array) -> value[index1] = (Byte2DArray)malloc(sizeof(Byte2ArrayStruct));
            initByte2DArray(&((*array)->value[index1]), 1, length, index2);
            break;
        case 3:
            initByte2DArray(&((*array)->value[index1]), 2, length, index2);
            break;
    }
}

static inline int getByte3DArrayLength(Byte3DArray *array, int type, short index1, short index2){
    switch (type) {
        case 1:
            return (*array) -> length;
        case 2:
            return getByte2DArrayLength(&((*array)->value[index1]), 1, index2);
            break;
        case 3:
            return getByte2DArrayLength(&((*array)->value[index1]), 2, index2);
        default:
            return -1;
            break;
    }
}


static inline void setByte3DArrayValue(Byte3DArray *array, short value, short index1, short index2, short index3){
    if(index1 >= getByte3DArrayLength(array, 1, index1, index2)
       ||index2 >= getByte3DArrayLength(array, 2, index1, index2)
       ||index3 >= getByte3DArrayLength(array, 3, index1, index2)){
        return;
    }
    setByte2DArrayValue(&((*array)->value[index1]), value, index2, index3);
}

static inline short getByte3DArrayValue(Byte3DArray *array, short index1, short index2, short index3){
    if(index1 >= getByte3DArrayLength(array, 1, index1, index2)
       ||index2 >= getByte3DArrayLength(array, 2, index1, index2)
       ||index3 >= getByte3DArrayLength(array, 3, index1, index2)){
        return -1;
    }
    return getByte2DArrayValue(&((*array)->value[index1]), index2, index3);
}


static inline void clearByte3DArray(Byte3DArray *array){
    int i = 0;
    if(*array != NULL){
        for(i = 0; i < (*array)->length; i++){
            clearByte2DArray(&((*array)->value[i]));
        }
        free((*array) -> value);
        (*array) -> value = NULL;
        free(*array);
        *array = NULL;
    }
}


//一维Short数组结构体及其方法----------------------------------------------------------------------------


typedef struct
{
    short *value;
    int length;
}*Short1DArray, Short1ArrayStruct;


static inline void initShort1DArray(Short1DArray *array,short length){
    (*array) -> value = (short *)malloc(sizeof(short) * length);
    (*array) -> length = length;
    for (int i = 0; i < length; i ++) {
        (*array) -> value[i] = 0;
    }
}

static inline int getShort1DArrayLength(Short1DArray *array){
    return (*array) -> length;
}

static inline void setShort1DArrayValue(Short1DArray *array, short value, short index){
    if(index >= getShort1DArrayLength(array)){
        return;
    }
    (*array) -> value[index] = value;
}

static inline short getShort1DArrayValue(Short1DArray *array, short index){
    if(index >= getShort1DArrayLength(array)){
        return -1;
    }
    return (*array) -> value[index];
}

static inline void clearShort1DArray(Short1DArray * array){
    if(*array != NULL){
        free((*array)->value);
        (*array)->value = NULL;
        free(*array);
        *array = NULL;
    }
}


static inline Short1DArray copyShort1DArray(Short1DArray data)
{
    Short1DArray tempdata = (Short1DArray)malloc(sizeof(Short1ArrayStruct));
    initShort1DArray(&tempdata, data -> length);
    for (byte i = 0, length = tempdata -> length; i < length; i++) {
        setShort1DArrayValue(&tempdata, data -> value[i], i);
    }
    return tempdata;
}


//二维Short数组结构体及其方法----------------------------------------------------------------------------
typedef struct
{
	Short1DArray *value; //二维short数组
    int length;//第一维的长度
}*Short2DArray, Short2ArrayStruct;


static inline void initShort2DArray(Short2DArray *array, int type, short length, int index){
    switch (type) {
        case 1:
            (*array) -> value = (Short1DArray*)malloc(sizeof(Short1DArray) * length);
            (*array) -> length = length;
            break;
        case 2:
            (*array) -> value[index] = (Short1DArray)malloc(sizeof(Short1ArrayStruct));
            initShort1DArray(&((*array)->value[index]), length);
            break;
    }
}


static inline int getShort2DArrayLength(Short2DArray *array, int type, short index){
    switch (type) {
        case 1:
            return (*array) -> length;
        case 2:
            return getShort1DArrayLength(&((*array)->value[index]));
        default:
            return -1;
    }
    
}

static inline void setShort2DArrayValue(Short2DArray *array, short value, short index1, short index2){
    if(index1 >= getShort2DArrayLength(array, 1, 0) || index2 >= getShort2DArrayLength(array, 2, index1)){
        return;
    }
    setShort1DArrayValue(&((*array)->value[index1]), value, index2);
}

static inline short getShort2DArrayValue(Short2DArray *array, short index1, short index2){
    if(index1 >= getShort2DArrayLength(array, 1, 0) || index2 >= getShort2DArrayLength(array, 2, index1)){
        return -1;
    }
    return getShort1DArrayValue(&((*array)->value[index1]), index2);
}

static inline void clearShort2DArray(Short2DArray *array){
    int i = 0;
    if(*array != NULL){
        for(i = 0; i < (*array)->length; i++){
            clearShort1DArray(&((*array)->value[i]));
        }
        free((*array) -> value);
        (*array) -> value = NULL;
        free(*array);
        *array = NULL;
    }
}



static inline Short2DArray copyShort2DArray(Short2DArray data)
{
    Short2DArray tempdata = (Short2DArray)malloc(sizeof(Short2ArrayStruct));
    initShort2DArray(&tempdata, 1, data -> length, 0);
    for (byte i = 0, length = tempdata -> length; i < length; i++) {
        initShort2DArray(&tempdata, 2, getShort2DArrayLength(&data, 2, i), i);
        for (int j = 0, length = getShort2DArrayLength(&tempdata, 2, i); j < length; j++) {
            setShort2DArrayValue(&tempdata, getShort2DArrayValue(&data, i, j), i, j);
        }
    }
    return tempdata;
}


//三维Short数组结构体及其方法----------------------------------------------------------------------------
typedef struct
{
    Short2DArray *value;
    int length;
}*Short3DArray, Short3ArrayStruct;

static inline void initShort3DArray(Short3DArray *array, int type, short length, int index1, int index2){
    switch (type) {
        case 1:
            (*array) -> value = (Short2DArray *)malloc(sizeof(Short2DArray) * length);
            (*array) -> length = length;
            break;
        case 2:
            (*array) -> value[index1] = (Short2DArray)malloc(sizeof(Short2ArrayStruct));
            initShort2DArray(&((*array)->value[index1]), 1, length, index2);
            break;
        case 3:
            initShort2DArray(&((*array)->value[index1]), 2, length, index2);
            break;
    }
}

static inline int getShort3DArrayLength(Short3DArray *array, int type, short index1, short index2){
    switch (type) {
        case 1:
            return (*array) -> length;
        case 2:
            return getShort2DArrayLength(&((*array)->value[index1]), 1, index2);
            break;
        case 3:
            return getShort2DArrayLength(&((*array)->value[index1]), 2, index2);
        default:
            return -1;
            break;
    }
}


static inline void setShort3DArrayValue(Short3DArray *array, short value, short index1, short index2, short index3){
    if(index1 >= getShort3DArrayLength(array, 1, index1, index2)
       ||index2 >= getShort3DArrayLength(array, 2, index1, index2)
       ||index3 >= getShort3DArrayLength(array, 3, index1, index2)){
        return;
    }
    setShort2DArrayValue(&((*array)->value[index1]), value, index2, index3);
}

static inline short getShort3DArrayValue(Short3DArray *array, short index1, short index2, short index3){
    if(index1 >= getShort3DArrayLength(array, 1, index1, index2)
       ||index2 >= getShort3DArrayLength(array, 2, index1, index2)
       ||index3 >= getShort3DArrayLength(array, 3, index1, index2)){
        return -1;
    }
    return getShort2DArrayValue(&((*array)->value[index1]), index2, index3);
}


static inline void clearShort3DArray(Short3DArray *array){
    int i = 0;
    if(*array != NULL){
        for(i = 0; i < (*array)->length; i++){
            clearShort2DArray(&((*array)->value[i]));
        }
        free((*array) -> value);
        (*array) -> value = NULL;
        free(*array);
        *array = NULL;
    }
}


//四维Short数组结构体及其方法----------------------------------------------------------------------------
typedef struct
{
    Short3DArray *value;
    int length;
}*Short4DArray, Short4ArrayStruct;


static inline void initShort4DArray(Short4DArray *array, int type, short length, int index1, int index2, int index3){
    switch (type) {
        case 1:
            (*array) -> value = (Short3DArray*)malloc(sizeof(Short3DArray) * length);
            (*array) -> length = length;
            break;
        case 2:
            (*array) -> value[index1] = (Short3DArray)malloc(sizeof(Short3ArrayStruct));
            initShort3DArray(&((*array)->value[index1]), 1, length, index2, index3);
            break;
        case 3:
            initShort3DArray(&((*array)->value[index1]), 2, length, index2, index3);
            break;
        case 4:
            initShort3DArray(&((*array)->value[index1]), 3, length, index2, index3);
            break;
    }
}

static inline int getShort4DArrayLength(Short4DArray *array, int type, short index1, short index2, short index3){
    switch (type) {
        case 1:
            return (*array) -> length;
        case 2:
            return getShort3DArrayLength(&((*array)->value[index1]), 1, index2, index3);
        case 3:
            return getShort3DArrayLength(&((*array)->value[index1]), 2, index2, index3);
        case 4:
            return getShort3DArrayLength(&((*array)->value[index1]), 3, index2, index3);
        default:
            return -1;
    }
}


static inline void setShort4DArrayValue(Short4DArray *array, short value, short index1,
                                        short index2, short index3, short index4){
    if(index1 >= getShort4DArrayLength(array, 1, index1, index2, index3)
       ||index2 >= getShort4DArrayLength(array, 2, index1, index2, index3)
       ||index3 >= getShort4DArrayLength(array, 3, index1, index2, index3)
       ||index4 >= getShort4DArrayLength(array, 4, index1, index2, index3)){
        return;
    }
    setShort3DArrayValue(&((*array)->value[index1]), value, index2, index3, index4);
}
static inline short getShort4DArrayValue(Short4DArray *array, short index1, short index2, short index3, short index4){
    if(index1 >= getShort4DArrayLength(array, 1, index1, index2, index3)
       ||index2 >= getShort4DArrayLength(array, 2, index1, index2, index3)
       ||index3 >= getShort4DArrayLength(array, 3, index1, index2, index3)
       ||index4 >= getShort4DArrayLength(array, 4, index1, index2, index3)){
        return -1;
    }
    return getShort3DArrayValue(&((*array)->value[index1]), index2, index3, index4);
}


static inline void clearShort4DArray(Short4DArray *array){
    int i = 0;
    if(*array != NULL){
        for(i = 0; i < (*array)->length; i++){
            clearShort3DArray(&((*array)->value[i]));
        }
        free((*array) -> value);
        (*array) -> value = NULL;
        free(*array);
        *array = NULL;
    }
}






//一维Int数组结构体及其方法----------------------------------------------------------------------------
typedef struct
{
    int *value;
    int length;
}*Int1DArray, Int1ArrayStruct;

static inline void initInt1DArray(Int1DArray *array, short length){
    (*array) -> value = (int *)malloc(sizeof(int) * length);
    (*array) -> length = length;
    for (int i = 0; i < length; i ++) {
        (*array) -> value[i] = 0;
    }
}

static inline int getInt1DArrayLength(Int1DArray *array){
    return (*array) -> length;
}

static inline void setInt1DArrayValue(Int1DArray *array, int value, short index){
    if(index >= getInt1DArrayLength(array)){
        return;
    }
    (*array) -> value[index] = value;
}

static inline int getInt1DArrayValue(Int1DArray *array,short index){
    if(index >= getInt1DArrayLength(array)){
        return -1;
    }
    return (*array) -> value[index];
}

static inline void clearInt1DArray(Int1DArray *array){
    if(*array != NULL){
        free((*array)->value);
        (*array)->value = NULL;
        free(*array);
        *array = NULL;
    }
}



static inline Int1DArray copyInt1DArray(Int1DArray data)
{
    Int1DArray tempdata = (Int1DArray)malloc(sizeof(Int1ArrayStruct));
    initInt1DArray(&tempdata, data -> length);
    for (byte i = 0, length = tempdata -> length; i < length; i++) {
        setInt1DArrayValue(&tempdata, data -> value[i], i);
    }
    return tempdata;
}



//二维byte数组结构体及其方法----------------------------------------------------------------------------
typedef struct
{
	Int1DArray *value; //二维byte数组
    int length;//第一维的长度
}*Int2DArray, Int2ArrayStruct;


static inline void initInt2DArray(Int2DArray *array,int type,short length,int index){
    switch (type) {
        case 1:
            (*array) -> value = (Int1DArray *)malloc(sizeof(Int1DArray) * length);
            (*array) -> length = length;
            break;
        case 2:
            (*array) -> value[index] = (Int1DArray)malloc(sizeof(Int1ArrayStruct));
            initInt1DArray(&((*array)->value[index]), length);
            break;
    }
}

static inline int getInt2DArrayLength(Int2DArray *array, int type, short index){
    switch (type) {
        case 1:
            return (*array) -> length;
        case 2:
            return getInt1DArrayLength(&((*array)->value[index]));
        default:
            return -1;
    }
}


static inline void setInt2DArrayValue(Int2DArray *array, int value, short index1, short index2){
    if(index1 >= getInt2DArrayLength(array, 1, 0) || index2 >= getInt2DArrayLength(array, 2, index1)){
        return;
    }
    setInt1DArrayValue(&((*array)->value[index1]), value, index2);
}


static inline int getInt2DArrayValue(Int2DArray *array, short index1, short index2){
    if(index1 >= getInt2DArrayLength(array, 1, 0) || index2 >= getInt2DArrayLength(array, 2, index1)){
        return -1;
    }
    return getInt1DArrayValue(&((*array)->value[index1]),index2);
}

static inline void clearInt2DArray(Int2DArray *array){
    int i = 0;
    if(*array != NULL){
        for(i = 0; i < (*array)->length; i++){
            clearInt1DArray(&((*array)->value[i]));
        }
        free((*array) -> value);
        (*array) -> value = NULL;
        free(*array);
        *array = NULL;
    }
}



static inline Int2DArray copyInt2DArray(Int2DArray data)
{
    Int2DArray tempdata = (Int2DArray)malloc(sizeof(Int2ArrayStruct));
    initInt2DArray(&tempdata, 1, data -> length, 0);
    for (byte i = 0, length = tempdata -> length; i < length; i++) {
        initInt2DArray(&tempdata, 2, getInt2DArrayLength(&data, 2, i), i);
        for (int j = 0, length = getInt2DArrayLength(&tempdata, 2, i); j < length; j++) {
            setInt2DArrayValue(&tempdata, getInt2DArrayValue(&data, i, j), i, j);
        }
    }
    return tempdata;
}



//static inline NSMutableArray * copyUTF2DArray(NSMutableArray* data)
//{
//    NSMutableArray *tempdata = [[NSMutableArray alloc] init];
//    for (int i = 0, length = data.count; i < length; i++) {
//        NSMutableArray *tempdata1 = [data objectAtIndex:i];
//        NSMutableArray *array = [NSMutableArray array];
//        for (int j = 0, length = tempdata1.count; j < length; j++) {
//            NSString *str = [tempdata1 objectAtIndex:j];
//            [array addObject:str];
//        }
//        [tempdata addObject:array];
//    }
//    return tempdata;
//}
static inline CCArray * copyUTF2DArray(CCArray* data)
{
    CCArray *tempdata =CCArray::create();
    for (int i = 0, length = data->count(); i < length; i++) {
        //CCArray *tempdata1=（CCArray*)data->objectAtIndex(i);
        CCArray* tempdata1=(CCArray*)data->objectAtIndex(i);
        CCArray *array = CCArray::create();
        for (int j = 0, length = tempdata1->count(); j < length; j++) {
            CCString *str =(CCString*)tempdata1->objectAtIndex(j);
            array->addObject(str);
        }
        tempdata->addObject(array);
    }
    return tempdata;
}



//三维Int数组结构体及其方法----------------------------------------------------------------------------
typedef struct
{
    Int2DArray *value;
    int length;
}*Int3DArray, Int3ArrayStruct;

static inline void initInt3DArray(Int3DArray *array, int type, short length, int index1, int index2){
    switch (type) {
        case 1:
            (*array) -> value = (Int2DArray *)malloc(sizeof(Int2DArray) * length);
            (*array) -> length = length;
            break;
        case 2:
            (*array) -> value[index1] = (Int2DArray)malloc(sizeof(Int2ArrayStruct));
            initInt2DArray(&((*array)->value[index1]), 1, length, index2);
            break;
        case 3:
            initInt2DArray(&((*array)->value[index1]), 2, length, index2);
            break;
    }
}

static inline int getInt3DArrayLength(Int3DArray *array, int type, short index1, short index2){
    switch (type) {
        case 1:
            return (*array) -> length;
        case 2:
            return getInt2DArrayLength(&((*array)->value[index1]), 1, index2);
            break;
        case 3:
            return getInt2DArrayLength(&((*array)->value[index1]), 2, index2);
        default:
            return -1;
            break;
    }
}


static inline void setInt3DArrayValue(Int3DArray *array, int value, short index1, short index2, short index3){
    if(index1 >= getInt3DArrayLength(array, 1, index1, index2)
       ||index2 >= getInt3DArrayLength(array, 2, index1, index2)
       ||index3 >= getInt3DArrayLength(array, 3, index1, index2)){
        return;
    }
    setInt2DArrayValue(&((*array)->value[index1]), value, index2, index3);
}

static inline int getInt3DArrayValue(Int3DArray *array, short index1, short index2, short index3){
    if(index1 >= getInt3DArrayLength(array, 1, index1, index2)
       ||index2 >= getInt3DArrayLength(array, 2, index1, index2)
       ||index3 >= getInt3DArrayLength(array, 3, index1, index2)){
        return -1;
    }
    return getInt2DArrayValue(&((*array)->value[index1]), index2, index3);
}


static inline void clearInt3DArray(Int3DArray *array){
    int i = 0;
    if(*array != NULL){
        for(i = 0; i < (*array)->length; i++){
            clearInt2DArray(&((*array)->value[i]));
        }
        free((*array) -> value);
        (*array) -> value = NULL;
        free(*array);
        *array = NULL;
    }
}



//一维NSString数组结构体及其方法----------------------------------------------------------------------------
typedef struct{
    CCString **value;
    int length;
}*NSString1DArray,NSString1DArrayStruct;


static inline void initNSString1DArray(NSString1DArray *array, short length){
    (*array) -> value = (CCString **)malloc(sizeof(CCString *) * length);
    (*array) -> length = length;
}

static inline int getNSString1DArrayLength(NSString1DArray *array){
    return (*array) -> length;
}

static inline void setNSString1DArrayValue(NSString1DArray *array, CCString* value, short index){
    if(index >= getNSString1DArrayLength(array)){
        return;
    }
    (*array) -> value[index] =value;
}

static inline CCString* getNSString1DArrayValue(NSString1DArray *array, short index){
    if(index >= getNSString1DArrayLength(array)){
        return NULL;
    }
    return (*array) -> value[index];
}


static inline void clearNSString1DArray(NSString1DArray *array){
    if(*array != NULL){
        for (int i = 0; i < (*array)->length; i ++) {
            (*array)->value[i]->release();
        }
        free((*array)->value);
        (*array)->value = NULL;
        free(*array);
        *array = NULL;
    }
}


//一维String数组结构体及方法----------------------------------------------------
typedef struct{
    const char **value;
    int length;
}*String1DArray,String1DArrayStruct;

static inline void initString1DArray(String1DArray *array, short length){
    (*array) -> value = (const char **)malloc(sizeof(char *) * length);
    (*array) -> length = length;
}

static inline int getString1DArrayLength(String1DArray *array){
    return (*array) -> length;
}

static inline void setString1DArrayValue(String1DArray *array, char* value, short index){
    if(index >= getString1DArrayLength(array)){
        return;
    }
    (*array) -> value[index] = value;
}

static inline const char* getString1DArrayValue(String1DArray *array, short index){
    if(index >= getString1DArrayLength(array)){
        return NULL;
    }
    return (*array) -> value[index];
}


static inline void clearString1DArray(String1DArray *array){
    if(*array != NULL){
        free((*array)->value);
        (*array)->value = NULL;
        free(*array);
        *array = NULL;
    }
}
typedef	unsigned int		uint;

/*只支持>-1的值转换*/
static inline char* intTochar(int value)
{
    uint i,len = 0,temp = value;
    char* c;
    char index[]="0123456789";
    do{
        temp/=10;
        len++;
    }while(temp);
    c =(char*) malloc(len+1);
    memset(c, 0, len);
    for(i=len-1,temp=value;temp;i--){
        *(c+i) = index[temp%10];
        temp/=10;
    }
    return c;
}


#endif
