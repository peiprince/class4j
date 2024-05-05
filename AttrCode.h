//
// Created by Administrator on 2024/5/5 0005.
//
#pragma once
#ifndef CLASS4J_ATTRCODE_H
#define CLASS4J_ATTRCODE_H

#include "Common.h"
#include "ConstantItem.h"

typedef struct ExceptionItem ExceptionItem;

/**
 * Code
 */
typedef struct CodeAttr {

    unsigned int attribute_name_index;

    unsigned int attribute_length;

    unsigned int max_stack;         // 操作数栈最大深度

    unsigned int max_locals;        // 局部变量表最大个数

    unsigned int code_length;

    unsigned int code;                    // TODO string数组，长度为code_length

    unsigned int exception_table_length;

    ExceptionItem* exception_item;  // 长度为exception_table_length

    unsigned int attributes_count;

    // TODO

} CodeAttr;

/**
 * 初始化CodeAttr
 */
void init_code_attr(CodeAttr*, ConstantItem*, FILE*);

/**
 * 打印CodeAttr
 */
void print_code_attr(CodeAttr*, ConstantItem*, unsigned int);

/**
 * ExceptionItem
 */
typedef struct ExceptionItem {

    unsigned int start_pc;

    unsigned int end_pc;

    unsigned int handler_pc;

    unsigned int catch_type;

} ExceptionItem;

void init_exception_item(ExceptionItem*, FILE*);

#endif //CLASS4J_ATTRCODE_H
