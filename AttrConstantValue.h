//
// Created by Administrator on 2024/4/29 0029.
//
#pragma once
#ifndef CLASS4J_ATTRCONSTANTVALUE_H
#define CLASS4J_ATTRCONSTANTVALUE_H

#include "ConstantItem.h"


/**
 * ConstantValue
 */
typedef struct ConstantAttr {

    unsigned int attribute_name_index;

    unsigned int attribute_length;

    unsigned int constant_value_index;

} ConstantAttr;

/**
 * 初始化ConstantValue属性
 */
void init_constant_attr(ConstantAttr*, ConstantItem*, FILE*);

/**
 * 打印ConstantValue属性
 */
void print_constant_value_attr(ConstantAttr*, ConstantItem*, unsigned int);

#endif //CLASS4J_ATTRCONSTANTVALUE_H
