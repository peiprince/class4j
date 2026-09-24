//
// Created by Administrator on 2024/5/25 0025.
//
#pragma once
#ifndef CLASS4J_ATTRENCLOSINGMETHOD_H
#define CLASS4J_ATTRENCLOSINGMETHOD_H

#include "ConstantItem.h"

/**
 * EnclosingMethod
 */
typedef struct EnclosingMethodAttr {

    unsigned int attribute_name_index;

    unsigned int attribute_length;

    unsigned int class_index;

    unsigned int method_index;

} EnclosingMethodAttr;

/**
 * 初始化EnclosingMethod
 */
void init_enclosing_method_attr(EnclosingMethodAttr*, ConstantItem*, FILE*);

/**
 * 打印EnclosingMethod
 */
void print_enclosing_method_attr(EnclosingMethodAttr*, ConstantItem*, unsigned int);

#endif //CLASS4J_ATTRENCLOSINGMETHOD_H
