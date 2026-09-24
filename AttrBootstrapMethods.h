//
// Created by Administrator on 2024/5/26 0026.
//
#pragma once
#ifndef CLASS4J_ATTRBOOTSTRAPMETHODS_H
#define CLASS4J_ATTRBOOTSTRAPMETHODS_H

#include "ConstantItem.h"

typedef struct BootstrapMethods BootstrapMethods;

/**
 * BootstrapMethods
 */
typedef struct BootstrapMethodsAttr {

    unsigned int attribute_name_index;

    unsigned int attribute_length;

    unsigned int num_bootstrap_methods;

    BootstrapMethods* bootstrap_methods;

} BootstrapMethodsAttr;

/**
 * 初始化BootstrapMethods
 */
void init_bootstrap_methods_attr(BootstrapMethodsAttr*, ConstantItem*, FILE*);

/**
 * 打印BootstrapMethods
 */
void print_bootstrap_methods_attr(BootstrapMethodsAttr*, ConstantItem*, unsigned int);

typedef struct BootstrapMethods {

    unsigned int bootstrap_method_ref;

    unsigned int num_bootstrap_arguments;

    unsigned int* bootstrap_arguments;

} BootstrapMethods;

#endif //CLASS4J_ATTRBOOTSTRAPMETHODS_H
