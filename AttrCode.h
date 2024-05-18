//
// Created by Administrator on 2024/5/5 0005.
//
#pragma once
#ifndef CLASS4J_ATTRCODE_H
#define CLASS4J_ATTRCODE_H

#include "AttrLineNumberTable.h"
#include "AttrLocalVariableTable.h"
#include "Common.h"
#include "ConstantItem.h"

#define CODE_ATTR_COUNT                     4

typedef struct ExceptionItem ExceptionItem;
typedef struct CodeAttrWrapper CodeAttrWrapper;

/**
 * Code
 */
typedef struct CodeAttr {

    unsigned int attribute_name_index;

    unsigned int attribute_length;

    unsigned int max_stack;         // 操作数栈最大深度

    unsigned int max_locals;        // 局部变量表最大个数

    unsigned int code_length;

    unsigned int* code;                     //　字节码指令

    unsigned int exception_table_length;

    ExceptionItem* exception_item;          // 长度为exception_table_length

    unsigned int attributes_count;

    void* attributes[CODE_ATTR_COUNT];      // 长度为attributes_count

} CodeAttr;

/**
 * 初始化CodeAttr
 */
void init_code_attr(CodeAttr*, ConstantItem*, FILE*, ConstantItem*, unsigned int);

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

static void init_exception_item(ExceptionItem*, FILE*);

/**
 * 完全等同于AttrWrapper，避免头文件循环依赖，仅用于包装下列四种属性：
 * StackMapTable, LineNumberTable, LocalVariableTable, LocalVariableTypeTable
 */
typedef struct CodeAttrWrapper {

    char* type;         // 标记当前属性的类型
    void* p_attr;       // 存储属性信息

} CodeAttrWrapper;

#endif //CLASS4J_ATTRCODE_H
