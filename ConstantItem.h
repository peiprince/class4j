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
void construct_const_item(ConstantItem*);

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

void read_utf8_info(FILE*, char*);

void read_integer_info(FILE*, char*);

void read_float_info(FILE*, char*);

void read_long_info(FILE*, char*);

void read_double_info(FILE*, char*);

void read_class_info(FILE*, char*);

void read_fieldref_info(FILE*, char*);

/**
 * 根据下标从常量池取值
 * @return 常量对象
 */
ConstantItem get_constant_item_by_index(ConstantItem*, unsigned int, unsigned int);

#endif //CLASS4J_CONSTANTITEM_H
