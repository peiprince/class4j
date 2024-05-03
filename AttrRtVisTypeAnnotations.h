//
// Created by Administrator on 2024/5/1 0001.
//
#pragma once
#ifndef CLASS4J_ATTRRTVISTYPEANNOTATIONS_H
#define CLASS4J_ATTRRTVISTYPEANNOTATIONS_H

#include "AttrAnnotation.h"
#include "ConstantItem.h"

typedef struct TypeAnnotation TypeAnnotation;
typedef union TargetInfo TargetInfo;
typedef struct LocalVar LocalVar;
typedef struct TPath TPath;

/**
 * RuntimeVisibleTypeAnnotations
 */
typedef struct RtVisTypeAnnotationAttr {

    unsigned int attribute_name_index;  // RuntimeVisibleTypeAnnotations在常量池中的index

    unsigned int attribute_length;

    unsigned int num_annotations;       // RuntimeVisibleTypeAnnotations中注解数量

    TypeAnnotation* annotations;        // 长度为num_annotations

} RtVisTypeAnnotationAttr;

/**
 * 初始化RuntimeVisibleTypeAnnotations
 */
void init_rt_vis_type_annotation_attr(RtVisTypeAnnotationAttr*, ConstantItem*, FILE*);

/**
 * 添加RuntimeVisibleTypeAnnotations
 */
void add_type_annotation(RtVisTypeAnnotationAttr*,  FILE*, unsigned int);

/**
 * 打印RuntimeVisibleTypeAnnotations
 */
void print_rt_vis_type_annotation_attr(RtVisTypeAnnotationAttr*, ConstantItem*, unsigned int);

/**
 * TypeAnnotation
 */
typedef struct TypeAnnotation {

    unsigned int target_type;   // 注解修饰的数据类型

    TargetInfo* target_info;

    struct {
        unsigned int path_length;
        TPath* path;    // 长度为path_length
    } target_path;

    Annotation* annotation;

} TypeAnnotation;

/**
 * 初始化TypeAnnotation
 */
void init_type_annotation(TypeAnnotation*, FILE*);

/**
 * 打印TypeAnnotation
 */
void print_type_annotation(TypeAnnotation*, ConstantItem*, unsigned int, unsigned int);

/**
 * TargetInfo
 */
typedef union TargetInfo {

    struct {
        unsigned int type_parameter_index;
    } type_parameter_target;

    struct {
        unsigned int supertype_index;
    } supertype_target;

    struct {
        unsigned int type_parameter_bound_index;
        unsigned int bound_index;
    } type_parameter_bound_target;

    struct  {

    } empty_target;

    struct {
        unsigned int formal_parameter_index;
    } method_formal_parameter_target;

    struct {
        unsigned int throws_type_index;
    } throws_target;

    struct {
        unsigned int table_length;
        LocalVar* table;    // 长度为table_length
    } localvar_target;

    struct {
        unsigned int exception_table_index;
    } catch_target;

    struct {
        unsigned int offset;
    } offset_target;

    struct {
        unsigned int argument_offset;
        unsigned int type_argument_index;
    } type_argument_target;

} TargetInfo;

/**
 * 初始化TargetInfo
 */
void init_target_info(TargetInfo*, FILE*, unsigned int);

/**
 * 添加LocalVar至TargetInfo.localvar_target.table
 */
void add_local_var(TargetInfo*, FILE*, unsigned int);

/**
 * 根据type_index获取当前注解的位置
 */
char* locate_annotation(char*, unsigned int);

/**
 * LocalVar table成员
 */
typedef struct LocalVar {

    unsigned int start_pc;
    unsigned int length;
    unsigned int index;

} LocalVar;

/**
 * 初始化LocalVar
 */
void init_local_var(LocalVar*, FILE*);

/**
 * TPath
 */
typedef struct TPath {
    unsigned int type_path_kind;
    unsigned int type_argument_index;
} TPath;

/**
 * 初始化TPath
 */
void init_t_path(TPath*, FILE*);

#endif //CLASS4J_ATTRRTVISTYPEANNOTATIONS_H
