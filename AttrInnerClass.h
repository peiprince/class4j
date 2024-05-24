//
// Created by Administrator on 2024/5/24 0024.
//
#pragma once
#ifndef CLASS4J_ATTRINNERCLASS_H
#define CLASS4J_ATTRINNERCLASS_H

#include "ConstantItem.h"

typedef struct InnerClass InnerClass;

/**
 * InnerClass
 */
typedef struct InnerClassAttr {

    unsigned int attribute_name_index;

    unsigned int attribute_length;

    unsigned int number_of_classes;

    InnerClass* classes;

} InnerClassAttr;

/**
 * 初始化InnerClass
 */
void init_inner_class_attr(InnerClassAttr*, ConstantItem*, FILE*);

/**
 * 打印InnerClass
 */
void print_inner_class_attr(InnerClassAttr*, ConstantItem*, unsigned int);

typedef struct InnerClass {

    unsigned int inner_class_info_index;

    unsigned int outer_class_info_index;

    unsigned int inner_name_index;

    unsigned int inner_class_access_flags;

} InnerClass;

#endif //CLASS4J_ATTRINNERCLASS_H
