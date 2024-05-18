//
// Created by Administrator on 2024/4/23 0023.
//
#pragma once
#ifndef CLASS4J_CLASS_H
#define CLASS4J_CLASS_H

#include "Common.h"
#include "ConstantItem.h"
#include "FieldItem.h"

typedef struct Class {

    unsigned short minor_version;				// 次版本号
    unsigned short major_version;				// 主版本号

    unsigned int this_class;                    // 本类类名序号
    unsigned int super_class;                   // 父类类名序号

    unsigned short constant_pool_count;			// 常量池大小
    ConstantItem* constant_pool;                // 常量池

    unsigned short field_count;                 // 字段数量
    FieldItem* field_table;                     // 字段表

    unsigned short method_count;                // 方法数量
    FieldItem* method_table;                    // 方法表

    int flags;                                  // 访问标识
    unsigned int interface_count;               // 接口数量
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
 * 访问标识类型
 */
typedef enum FlagType {
    ClassType,
    FieldType
} FlagType;

/**
 * 读取访问类型
 */
void read_access_flags(Class*, FILE*, FlagType);

/**
 * 读取当前class继承的类和实现的接口信息
 */
void read_class_interface_info(Class*, FILE*);

/**
 * 读取字段表
 */
void read_field_info(Class*, FILE*);

/**
 * 读取方法表
 */
void read_method_info(Class*, FILE*);

/**
 * 打印class文件信息
 */
void print_class_info(Class*, char*);

#endif //CLASS4J_CLASS_H
