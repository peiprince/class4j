//
// Created by Administrator on 2024/5/26 0026.
//
#pragma once
#ifndef CLASS4J_ATTRSTACKMAPTABLE_H
#define CLASS4J_ATTRSTACKMAPTABLE_H

#include "ConstantItem.h"

typedef union StackMapFrame StackMapFrame;
typedef union VerificationTypeInfo VerificationTypeInfo;

/**
 * StackMapTable
 */
typedef struct StackMapTableAttr {

    unsigned int attribute_name_index;

    unsigned int attribute_length;

    unsigned int number_of_entries;

    StackMapFrame* entries;

} StackMapTableAttr;

/**
 * 初始化StackMapTable
 */
void init_stack_map_table_attr(StackMapTableAttr*, ConstantItem*, FILE*);

/**
 * 打印StackMapTable
 */
void print_stack_map_table_attr(StackMapTableAttr*, ConstantItem*, unsigned int);

typedef union StackMapFrame {

    struct {
        unsigned int frame_type;    // 0~63
    } same_frame;

    struct {
        unsigned int frame_type;    // 64~127
        VerificationTypeInfo* stack;
    } same_locals_1_stack_item_frame;

    struct {
        unsigned int frame_type;    // 247
        unsigned int offset_delta;
        VerificationTypeInfo* stack;
    } same_locals_1_stack_item_frame_extended;

    struct {
        unsigned int frame_type;    // 248~250
        unsigned int offset_delta;
    } chop_frame;

    struct {
        unsigned int frame_type;    // 251
        unsigned int offset_delta;
    } same_frame_extended;

    struct {
        unsigned int frame_type;    // 252~254
        unsigned int offset_delta;
        VerificationTypeInfo* locals;    // 长度为frame_type-251
    } append_frame;

    struct {
        unsigned int frame_type;    // 255
        unsigned int offset_delta;
        unsigned int number_of_locals;
        VerificationTypeInfo* locals;   // 长度为number_of_locals
        unsigned int number_of_stack_items;
        VerificationTypeInfo* stack;   // 长度为number_of_stack_items
    } full_frame;

} StackMapFrame;

typedef union VerificationTypeInfo {

    unsigned int tag;

    struct {
        unsigned int tag;
    } top_variable_info;

    struct {
        unsigned int tag;
    } integer_variable_info;

    struct {
        unsigned int tag;
    } float_variable_info;

    struct {
        unsigned int tag;
    } null_variable_info;

    struct {
        unsigned int tag;
    } uninitializedthis_variable_info;

    struct {
        unsigned int tag;
        unsigned int cpool_index;
    } object_variable_info;

    struct {
        unsigned int tag;
        unsigned int offset;
    } uninitialized_variable_info;

    struct {
        unsigned int tag;
    } long_variable_info;

    struct {
        unsigned int tag;
    } double_variable_info;

} VerificationTypeInfo;

#endif //CLASS4J_ATTRSTACKMAPTABLE_H
