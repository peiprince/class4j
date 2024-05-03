//
// Created by Administrator on 2024/5/2 0002.
//
#pragma once
#ifndef CLASS4J_ATTRANNOTATION_H
#define CLASS4J_ATTRANNOTATION_H

typedef struct Annotation Annotation;
typedef struct ElementValuePair ElementValuePair;
typedef struct ElementValue ElementValue;

#include "Common.h"

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
 * 当前注解中key-value对
 */
typedef struct ElementValuePair {

    unsigned int element_name_index;

    ElementValue* value;

} ElementValuePair;

typedef struct ElementValue {
    char tag;

    union value {
        unsigned int const_value_index;

        struct enum_const_value {
            unsigned int type_name_index;
            unsigned int const_name_index;
        };

        unsigned int class_info_index;

        Annotation annotation_value;

        struct array_value {
            unsigned int num_values;
            ElementValue* values;
        };
    };
} ElementValue;

void init_elementValue(ElementValue*, FILE*);

#endif //CLASS4J_ATTRANNOTATION_H
