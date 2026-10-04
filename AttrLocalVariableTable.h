//
// Created by Administrator on 2024/5/11 0011.
//
#pragma once
#ifndef CLASS4J_ATTRLOCALVARIABLETABLE_H
#define CLASS4J_ATTRLOCALVARIABLETABLE_H

#include "ConstantItem.h"

typedef struct LocalVariableTableElement LocalVariableTableElement;

/**
 * LocalVariableTable/LocalVariableTypeTable
 */
typedef struct LocalVariableTableAttr {

    unsigned int attribute_name_index;

    unsigned int attribute_length;

    unsigned int local_variable_table_length;

    // 对LocalVariableTypeTable属性该字段表示local_variable_type_table
    LocalVariableTableElement* local_variable_table;

} LocalVariableTableAttr;

/**
 * 初始化LocalVariableTable
 */
void init_local_variable_table_attr(LocalVariableTableAttr*, ConstantItem*, FILE*);

/**
 * 打印LocalVariableTable
 */
void print_local_variable_table_attr(LocalVariableTableAttr*, ConstantItem*, unsigned int);

/**
 * 打印LocalVariableTypeTable
 */
void print_local_variable_type_table_attr(LocalVariableTableAttr*, ConstantItem*, unsigned int);

typedef struct LocalVariableTableElement {

    unsigned int start_pc;

    unsigned int length;

    unsigned int name_index;

    // 对LocalVariableTypeTable属性该字段表示signature_index
    unsigned int descriptor_index;

    unsigned int index;

} LocalVariableTableElement;

#endif //CLASS4J_ATTRLOCALVARIABLETABLE_H
