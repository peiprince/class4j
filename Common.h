//
// Created by Administrator on 2024/4/23 0023.
//
#pragma once
#ifndef CLASS4J_COMMON_H
#define CLASS4J_COMMON_H

#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define HEX_BASE 16
/* Class类型 */
#define U1 1
#define U2 2
#define U4 4
#define U8 8

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
