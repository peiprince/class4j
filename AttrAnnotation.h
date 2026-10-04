//
// Created by Administrator on 2024/5/2 0002.
//
#pragma once
#ifndef CLASS4J_ATTRANNOTATION_H
#define CLASS4J_ATTRANNOTATION_H

typedef struct Annotation Annotation;
typedef struct ElementValuePair ElementValuePair;
typedef struct ElementValue ElementValue;
typedef union EValue EValue;

#include "Common.h"
#include "ConstantItem.h"

/**
 * Runtime注解
 */
typedef struct Annotation {

    unsigned int type_index;                    // 当前注解在常量池中的index

    unsigned int num_element_value_pairs;

    ElementValuePair* element_value_pairs;      // 当前注解下的所有k-v元素，长度为num_element_value_pairs

} Annotation;

/**
 * 初始化Annotation
 */
void init_annotation(Annotation*, FILE*);

/**
 * 添加ElementValuePair
 */
void add_element_value_pair(Annotation*, FILE*, unsigned int);

/**
 * 打印Annotation
 */
void print_annotation(Annotation*, ConstantItem*, unsigned int, unsigned int);

/**
 * 当前注解中key-value对，即注解中的参数
 */
typedef struct ElementValuePair {

    unsigned int element_name_index;

    ElementValue* value;

} ElementValuePair;

/**
 * 拼接注解参数值
 */
char* concat_param_key_value(ElementValuePair*, ConstantItem*, unsigned int, char*, char*);

/**
 * ElementValue，当前注解参数中的value
 */
typedef struct ElementValue {
    char tag;
    EValue* value;
} ElementValue;

/**
 * 初始化ElementValue
 */
void init_element_value(ElementValue*, FILE*);

/**
 * EValue
 */
typedef union EValue {
    unsigned int const_value_index;

    struct {
        unsigned int type_name_index;
        unsigned int const_name_index;
    } enum_const_value;

    unsigned int class_info_index;

    Annotation* annotation_value;

    struct {
        unsigned int num_values;
        ElementValue* values;
    } array_value;
} EValue;

#endif //CLASS4J_ATTRANNOTATION_H
