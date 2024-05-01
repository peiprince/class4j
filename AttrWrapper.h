//
// Created by Administrator on 2024/4/26 0026.
//
#pragma once
#ifndef CLASS4J_ATTRWRAPPER_H
#define CLASS4J_ATTRWRAPPER_H

#include "AttrConstantValue.h"
#include "AttrDeprecated.h"
#include "AttrRtVisAnnotations.h"
#include "Common.h"
#include "ConstantItem.h"

#define CONSTANT_VALUE  "ConstantValue"
#define SIGNATURE       "Signature"
#define DEPRECATED      "Deprecated"

/**
 * 属性包装类
 */
typedef struct AttrWrapper {

    char* type;         // 标记当前属性的类型

    void* p_attr;       // 存储属性信息

} AttrWrapper;

/**
 * 初始化方法，根据ConstantItem中的value构造不同类型的p_attr
 */
void init_attr_wrapper(AttrWrapper*, ConstantItem*, FILE*);

/**
 * 打印当前属性信息
 */
void print_attr_info(AttrWrapper*, ConstantItem*, unsigned int);

#endif //CLASS4J_ATTRWRAPPER_H
