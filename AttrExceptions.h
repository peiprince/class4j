//
// Created by Administrator on 2024/5/19 0019.
//
#pragma once
#ifndef CLASS4J_ATTREXCEPTIONS_H
#define CLASS4J_ATTREXCEPTIONS_H

#include "ConstantItem.h"

/**
 * Exceptions
 */
typedef struct ExceptionsAttr {

    unsigned int attribute_name_index;

    unsigned int attribute_length;

    unsigned int number_of_exceptions;

    unsigned int* exception_index_table;    // 长度为number_of_exceptions

} ExceptionsAttr;

/**
 * 初始化Exceptions
 */
void init_exceptions_attr(ExceptionsAttr*, ConstantItem*, FILE*);

/**
 * 打印Exceptions
 */
void print_exceptions_attr(ExceptionsAttr*, ConstantItem*, unsigned int);

#endif //CLASS4J_ATTREXCEPTIONS_H
