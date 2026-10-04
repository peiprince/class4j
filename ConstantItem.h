//
// Created by Administrator on 2024/4/24 0024.
//
#pragma once
#ifndef CLASS4J_CONSTANTITEM_H
#define CLASS4J_CONSTANTITEM_H

#include "Common.h"

typedef struct ConstantItem {

    unsigned int index;             // 常量序号
    unsigned int type;              // 常量类型
    char* value;                    // 常量值
} ConstantItem;

/**
 * 构造函数
 */
void init_const_item(ConstantItem*);

/**
 * 根据常量类型使用不同方法读取
 */
void dispatch_constant_item(ConstantItem*, FILE*, int);

typedef union IntFloatUnion {
    int int_num;
    float float_num;
} IntFloatUnion;

typedef union LongDoubleUnion {
    long long long_num;
    double double_num;
} LongDoubleUnion;

/**
 * 根据index从常量池获取item
 * @param pthis ConstantItem*
 * @param pool_count 常量池大小
 * @param index item下标
 * @return ConstantItem对象
 */
ConstantItem get_constant_item_by_index(ConstantItem*, unsigned int, unsigned int);

/**
 * 根据index从常量池获取utf8的value
 * @param pthis ConstantItem*
 * @param pool_count 常量池大小
 * @param index item下标
 * @return uf8常量的value
 */
char* get_utf8_constant_value(ConstantItem*, unsigned int, unsigned int);

#endif //CLASS4J_CONSTANTITEM_H
