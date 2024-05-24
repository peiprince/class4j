//
// Created by Administrator on 2024/4/26 0026.
//
#pragma once
#ifndef CLASS4J_ATTRWRAPPER_H
#define CLASS4J_ATTRWRAPPER_H

#include "AttrCode.h"
#include "AttrConstantValue.h"
#include "AttrExceptions.h"
#include "AttrInnerClass.h"
#include "AttrSourceFile.h"
#include "AttrDeprecated.h"
#include "AttrRtVisAnnotations.h"
#include "AttrRtVisParamAnnotation.h"
#include "AttrRtVisTypeAnnotations.h"
#include "AttrMethodParams.h"
#include "Common.h"
#include "ConstantItem.h"

/**
 * 属性包装类，不包含以下四种属性：
 * StackMapTable, LineNumberTable, LocalVariableTable, LocalVariableTypeTable
 */
typedef struct AttrWrapper {

    char* type;         // 标记当前属性的类型

    void* p_attr;       // 存储属性信息

} AttrWrapper;

/**
* 初始化AttrWrapper，根据ConstantItem中的value构造不同类型的p_attr
* @param pthis AttrWrapper*
* @param pconst_item ConstantItem对象
* @param fp FILE*指针
* @param p_pool 常量池首地址
* @param pool_count 常量池大小
*/
void init_attr_wrapper(AttrWrapper*, ConstantItem*, FILE*, ConstantItem*, unsigned int);

/**
 * 打印当前属性信息
 */
void print_attr_info(AttrWrapper*, ConstantItem*, unsigned int);

#endif //CLASS4J_ATTRWRAPPER_H
