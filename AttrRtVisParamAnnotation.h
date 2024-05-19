//
// Created by Administrator on 2024/5/18 0018.
//
#pragma once
#ifndef CLASS4J_ATTRRTVISPARAMANNOTATION_H
#define CLASS4J_ATTRRTVISPARAMANNOTATION_H

#include "AttrAnnotation.h"

typedef struct ParamAnnotation ParamAnnotation;

/**
 * RuntimeVisibleParameterAnnotation/RuntimeInvisibleParameterAnnotation
 */
typedef struct RtVisParamAnnotationAttr {

    unsigned int attribute_name_index;

    unsigned int attribute_length;

    unsigned int num_parameters;

    ParamAnnotation* parameter_annotations;       // 长度为num_parameters

} RtVisParamAnnotationAttr;

/**
 * 初始化RuntimeVisibleParameterAnnotation
 */
void init_rt_vis_param_annotation_attr(RtVisParamAnnotationAttr*, ConstantItem*, FILE*);

/**
 * 打印RuntimeVisibleParameterAnnotation
 */
void print_rt_vis_param_annotation_attr(RtVisParamAnnotationAttr*, ConstantItem*, unsigned int);

typedef struct ParamAnnotation {

    unsigned int num_annotations;

    Annotation* annotations;        // 长度为num_annotations

} ParamAnnotation;

#endif //CLASS4J_ATTRRTVISPARAMANNOTATION_H
