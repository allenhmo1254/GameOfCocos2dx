//
//  IntArray.cpp
//  SpotTheDifference
//
//  Created by leitingzu on 13-7-19.
//
//

#include "IntArray.h"


IntArray::IntArray()
:data_(NULL)
{
    
}

IntArray::~IntArray()
{
    clearInt1DArray(&data_);
}


int IntArray::count()
{
    if (!data_) {
        return 0;
    }
    return data_ -> length;
}

int IntArray::intAtIndex(int index)
{
    if(index >= data_ -> length){
        return -1;
    }else{
        return data_ -> value[index];
    }
}

void IntArray::addInt(int data)
{
    int length = data_ == nil ? 0 : data_ -> length;
    int i;
    length ++;
    
    Int1DArray tempdata = (Int1DArray)malloc(sizeof(Int1ArrayStruct));
    initInt1DArray(&tempdata, length);
    
    if (length > 1) {
        for (i = 0; i < length - 1; i ++) {
            tempdata -> value[i] = data_ -> value[i];
        }
    }
    tempdata -> value[length - 1] = data;
    clearInt1DArray(&data_);
    data_ = tempdata;
}

void IntArray::insertIntAtIndex(int index, int value)
{
    int length = data_ == nil ? 0 : data_ -> length;
    int i;
    length ++;
    
    Int1DArray tempdata = (Int1DArray)malloc(sizeof(Int1ArrayStruct));
    initInt1DArray(&tempdata, length);
    
    if (length > 1) {
        for (i = 0; i < length - 1; i ++) {
            tempdata -> value[i] = data_ -> value[i];
        }
    }
    
    for(i = length - 1; i > index; i --){
        tempdata -> value[i] = tempdata -> value[i - 1];
    }
    
    tempdata -> value[index] = value;
    clearInt1DArray(&data_);
    data_ = tempdata;
}



void IntArray::setIntAtIndex(int index, int value)
{
    int length = data_ == nil ? 0 : data_ -> length;
    int i;
    if(index < length){
        data_ ->value[index] = value;
    } else {
        if (index == length) {
            length ++;
            
            Int1DArray tempdata = (Int1DArray)malloc(sizeof(Int1ArrayStruct));
            initInt1DArray(&tempdata, length);
            
            if (length > 1) {
                for (i = 0; i < length - 1; i ++) {
                    tempdata -> value[i] = data_ -> value[i];
                }
            }
            tempdata -> value[length - 1] = value;
            clearInt1DArray(&data_);
            data_ = tempdata;
        } else if (index > length){
            return;
        }
    }
}

void IntArray::removeIntAtIndex(int index)
{
    int length = data_ == nil ? 0 : data_ -> length;
    int i;
    for (i = index + 1; i < length; i ++) {
        data_ -> value[i - 1] = data_ -> value[i];
    }
    length --;
    Int1DArray tempdata = (Int1DArray)malloc(sizeof(Int1ArrayStruct));
    initInt1DArray(&tempdata, length);
    
    for (i = 0; i < length; i ++) {
        tempdata -> value[i] = data_ -> value[i];
    }
    clearInt1DArray(&data_);
    data_ = tempdata;
}

void IntArray::removeAllInt()
{
    clearInt1DArray(&data_);
}

void IntArray::exchangeIntAtIndex(int index1, int index2)
{
    int length = data_ == nil ? 0 : data_ -> length;
    if (index1 >= length || index2 >= length) {
        return;
    }
    int temp = data_ -> value[index1];
    data_ -> value[index1] = data_ -> value[index2];
    data_ -> value[index2] = temp;
}

