//
// Created by Administrator on 2024/4/30 0030.
//
#pragma once
#ifndef CLASS4J_ATTRRTVISANNOTATIONS_H
#define CLASS4J_ATTRRTVISANNOTATIONS_H

#include "AttrAnnotation.h"
#include "ConstantItem.h"

/**
 * RuntimeVisibleAnnotation/RuntimeInvisibleAnnotation
 */
typedef struct RtVisAnnotationAttr {

    unsigned int attribute_name_index;  // RuntimeVisibleAnnotation在常量池中的index

    unsigned int attribute_length;

    unsigned int num_annotations;       // RuntimeVisibleAnnotation下注解数量

    Annotation* annotations;            // Runtime注解表，长度为num_annotations

} RtVisAnnotationAttr;

/**
 * 初始化RuntimeVisibleAnnotation
 */
void init_rt_vis_annotation_attr(RtVisAnnotationAttr*, ConstantItem*, FILE*);

/**
 * 打印RuntimeVisibleAnnotation属性
 */
void print_rt_vis_annotation_attr(RtVisAnnotationAttr*, ConstantItem*, unsigned int);

#endif //CLASS4J_ATTRRTVISANNOTATIONS_H
