//
// Created by Administrator on 2024/5/19 0019.
//
#pragma once
#ifndef CLASS4J_ATTRSOURCEFILE_H
#define CLASS4J_ATTRSOURCEFILE_H

#include "ConstantItem.h"

/**
 * SourceFile
 */
typedef struct SourceFileAttr {

    unsigned int attribute_name_index;

    unsigned int attribute_length;

    unsigned int sourcefile_index;

} SourceFileAttr;

/**
 * 初始化SourceFile
 */
void init_source_file_attr(SourceFileAttr*, ConstantItem*, FILE*);

/**
 * 打印SourceFile
 */
void print_source_file_attr(SourceFileAttr*, ConstantItem*, unsigned int);

#endif //CLASS4J_ATTRSOURCEFILE_H
