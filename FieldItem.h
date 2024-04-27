//
// Created by Administrator on 2024/4/26 0026.
//
#pragma once
#ifndef CLASS4J_FIELDITEM_H
#define CLASS4J_FIELDITEM_H

#include "AttrWrapper.h"
#include "Common.h"
#include "ConstantItem.h"

/**
 * 字段表&方法表成员完全一致，共用此结构体
 */
typedef struct FieldItem {
    int flags;                          // 访问标识
    unsigned int cons_index;            // 常量池索引
    unsigned int descriptor;            // 描述符

    unsigned int attributes_count;      // 属性表大小
    AttrWrapper* attr_table;            // 属性表

} FieldItem;

/**
 * 读取字段属性
 */
void read_field_attr(FieldItem*, FILE*, unsigned int);

/**
 * 初始化属性表
 */
void init_attr_table(FieldItem*, unsigned int);

/**
 * 打印字段信息
 */
void print_field_item(FieldItem*, ConstantItem*, int);

/**
 * 打印字段访问标识
 */
void printf_field_flag(FieldItem* pthis);

#endif //CLASS4J_FIELDITEM_H
