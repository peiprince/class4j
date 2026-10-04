//
// Created by Administrator on 2024/5/18 0018.
//
#pragma once
#ifndef CLASS4J_ATTRMETHODPARAMS_H
#define CLASS4J_ATTRMETHODPARAMS_H

#include "ConstantItem.h"

typedef struct Parameter Parameter;

/**
 * MethodParameters
 */
typedef struct MethodParametersAttr {

    unsigned int attribute_name_index;

    unsigned int attribute_length;

    unsigned int parameters_count;

    Parameter* parameters;      // 长度为parameters_count

} MethodParametersAttr;

/**
 * 初始化MethodParameters
 */
void init_method_parameters_attr(MethodParametersAttr*, ConstantItem*, FILE*);

/**
 * 打印MethodParameters
 */
void print_method_parameters_attr(MethodParametersAttr*, ConstantItem*, unsigned int);

typedef struct Parameter {

    unsigned int name_index;

    unsigned int access_flags;

} Parameter;

#endif //CLASS4J_ATTRMETHODPARAMS_H
