//
// Created by Administrator on 2024/5/11 0011.
//
#pragma once
#ifndef CLASS4J_ATTRLINENUMBERTABLE_H
#define CLASS4J_ATTRLINENUMBERTABLE_H

#include "ConstantItem.h"

typedef struct LineNumberTableElement LineNumberTableElement;

/**
 * LineNumberTable
 */
typedef struct LineNumberTableAttr {

    unsigned int attribute_name_index;

    unsigned int attribute_length;

    unsigned int line_number_table_length;

    LineNumberTableElement* line_number_table;

} LineNumberTableAttr;

/**
 * 初始化LineNumberTable
 */
void init_line_number_table_attr(LineNumberTableAttr*, ConstantItem*, FILE*);

/**
 * 打印LineNumberTableAttr
 */
void print_line_number_table(LineNumberTableAttr*);

typedef struct LineNumberTableElement {

    unsigned int start_pc;

    unsigned int line_number;

} LineNumberTableElement;

#endif //CLASS4J_ATTRLINENUMBERTABLE_H
