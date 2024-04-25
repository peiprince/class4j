//
// Created by Administrator on 2024/4/23 0023.
//
#pragma once
#ifndef CLASS4J_COMMON_H
#define CLASS4J_COMMON_H

#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define HEX_BASE 16
/* Class类型 */
#define U1 1
#define U2 2
#define U4 4
#define U8 8

#pragma region 常量类型
#define CONSTANT_Utf8_info					1
#define CONSTANT_Integer_info				3
#define CONSTANT_Float_info					4
#define CONSTANT_Long_info					5
#define CONSTANT_Double_info				6
#define CONSTANT_Class_info					7
#define CONSTANT_String_info				8
#define CONSTANT_Fieldref_info				9
#define CONSTANT_Methodref_info				10
#define CONSTANT_InterfaceMethodref_info	11
#define CONSTANT_NameAndType_info			12
#pragma endregion

/**
 * 读取指定的n个字节
 * @return 读取结果
 */
int read_n_byte(FILE*, int);

/**
 * 读取8个字节，long和double专用
 * @return 读取结果
 */
long long read_long_byte(FILE*);

#endif //CLASS4J_COMMON_H
