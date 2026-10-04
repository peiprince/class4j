//
// Created by Administrator on 2024/4/30 0030.
//
#pragma once
#ifndef CLASS4J_ATTRDEPRECATED_H
#define CLASS4J_ATTRDEPRECATED_H

#include "ConstantItem.h"

/**
 * Deprecated
 */
typedef struct DeprecatedAttr {

    unsigned int attribute_name_index;

    unsigned int attribute_length;

} DeprecatedAttr;

/**
 * 初始化Deprecated属性
 */
void init_deprecated_attr(DeprecatedAttr*, ConstantItem*, FILE*);

#endif //CLASS4J_ATTRDEPRECATED_H
