//
// Created by Administrator on 2024/4/23 0023.
//
#pragma once
#ifndef CLASS4J_CLASS_H
#define CLASS4J_CLASS_H

#include "Common.h"

typedef struct Class {

    unsigned short minor_version;				// 次版本号
    unsigned short major_version;				// 主版本号

    unsigned int this_class;                    // 本类类名序号
    unsigned int super_class;                   // 父类类名序号

} Class;

/**
 * 获取class文件版本号
 */
void check_class_version(FILE*, Class*);

/**
 * 打印class文件信息
 */
void print_class_info(Class*);

#endif //CLASS4J_CLASS_H
