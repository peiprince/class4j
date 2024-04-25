//
// Created by Administrator on 2024/4/23 0023.
//
#pragma once
#ifndef CLASS4J_CLASS_H
#define CLASS4J_CLASS_H

#include "Common.h"
#include "ConstantItem.h"

typedef struct Class {

    unsigned short minor_version;				// 次版本号
    unsigned short major_version;				// 主版本号

    unsigned int this_class;                    // 本类类名序号
    unsigned int super_class;                   // 父类类名序号

    unsigned short constant_pool_count;			// 常量池大小
    ConstantItem* constant_pool;                // 常量池
} Class;

/**
 * 获取class文件版本号
 */
void check_class_version(Class*, FILE*);

/**
 * 读取常量池信息
 */
void read_constant_pool(Class*, FILE*);

/**
 * 初始化常量池
 */
void init_constant_pool(Class*, int);

/**
 * 打印class文件信息
 */
void print_class_info(Class*);

#endif //CLASS4J_CLASS_H
