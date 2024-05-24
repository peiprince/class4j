//
// Created by Administrator on 2024/4/27 0027.
//
#include "AttrWrapper.h"

#define CONSTANT_VALUE                      "ConstantValue"
#define CODE                                "Code"
#define EXCEPTIONS                          "Exceptions"
#define INNER_CLASSES                       "InnerClasses"
#define SOURCE_FILE                         "SourceFile"
#define SIGNATURE                           "Signature"
#define DEPRECATED                          "Deprecated"
#define RUNTIME_VISIBLE_ANNOTATIONS         "RuntimeVisibleAnnotations"
#define RUNTIME_VISIBLE_PARAM_ANNOTATIONS   "RuntimeVisibleParameterAnnotations"
#define RUNTIME_VISIBLE_TYPE_ANNOTATIONS    "RuntimeVisibleTypeAnnotations"
#define METHOD_PARAMETERS                   "MethodParameters"


void init_attr_wrapper(AttrWrapper* pthis, ConstantItem* pconst_item, FILE* fp,
                       ConstantItem* p_pool, unsigned int pool_count)
{
    pthis->type = pconst_item->value;
    if (strcmp(pthis->type, CONSTANT_VALUE) == 0 || strcmp(pthis->type, SIGNATURE) == 0)
    {
        ConstantAttr* p_constant = malloc(sizeof(ConstantAttr));
        init_constant_attr(p_constant, pconst_item, fp);
        pthis->p_attr = p_constant;
    }
    else if (strcmp(pthis->type, CODE) == 0)
    {
        CodeAttr* p_code = malloc(sizeof(CodeAttr));
        init_code_attr(p_code, pconst_item, fp, p_pool, pool_count);
        pthis->p_attr = p_code;
    }
    else if (strcmp(pthis->type, EXCEPTIONS) == 0)
    {
        ExceptionsAttr* p_exception = malloc(sizeof(ExceptionsAttr));
        init_exceptions_attr(p_exception, pconst_item, fp);
        pthis->p_attr = p_exception;
    }
    else if (strcmp(pthis->type, INNER_CLASSES) == 0)
    {
        InnerClassAttr* p_inner_class = malloc(sizeof(InnerClass));
        init_inner_class_attr(p_inner_class, pconst_item, fp);
        pthis->p_attr = p_inner_class;
    }
    else if (strcmp(pthis->type, SOURCE_FILE) == 0)
    {
        SourceFileAttr* p_file = malloc(sizeof(SourceFileAttr));
        init_source_file_attr(p_file, pconst_item, fp);
        pthis->p_attr = p_file;
    }
    else if (strcmp(pthis->type, DEPRECATED) == 0)
    {
        DeprecatedAttr* p_deprecated = malloc(sizeof(DeprecatedAttr));
        init_deprecated_attr(p_deprecated, pconst_item, fp);
        pthis->p_attr = p_deprecated;
    }
    else if (strcmp(pthis->type, RUNTIME_VISIBLE_ANNOTATIONS) == 0)
    {
        RtVisAnnotationAttr* p_annotation = malloc(sizeof(RtVisAnnotationAttr));
        init_rt_vis_annotation_attr(p_annotation, pconst_item, fp);
        pthis->p_attr = p_annotation;
    }
    else if (strcmp(pthis->type, RUNTIME_VISIBLE_PARAM_ANNOTATIONS) == 0)
    {
        RtVisParamAnnotationAttr* p_annotation = malloc(sizeof(RtVisParamAnnotationAttr));
        init_rt_vis_param_annotation_attr(p_annotation, pconst_item, fp);
        pthis->p_attr = p_annotation;
    }
    else if (strcmp(pthis->type, RUNTIME_VISIBLE_TYPE_ANNOTATIONS) == 0)
    {
        RtVisTypeAnnotationAttr* p_annotation = malloc(sizeof(RtVisTypeAnnotationAttr));
        init_rt_vis_type_annotation_attr(p_annotation, pconst_item, fp);
        pthis->p_attr = p_annotation;
    }
    else if (strcmp(pthis->type, METHOD_PARAMETERS) == 0)
    {
        MethodParametersAttr* p_params = malloc(sizeof(MethodParametersAttr));
        init_method_parameters_attr(p_params, pconst_item, fp);
        pthis->p_attr = p_params;
    }
}

void print_attr_info(AttrWrapper* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    if (strcmp(pthis->type, CONSTANT_VALUE) == 0 || strcmp(pthis->type, SIGNATURE) == 0)
    {
        print_constant_value_attr(pthis->p_attr, p_pool, pool_count);
    }
    else if (strcmp(pthis->type, CODE) == 0)
    {
        print_code_attr(pthis->p_attr, p_pool, pool_count);
    }
    else if (strcmp(pthis->type, EXCEPTIONS) == 0)
    {
        print_exceptions_attr(pthis->p_attr, p_pool, pool_count);
    }
    else if (strcmp(pthis->type, INNER_CLASSES) == 0)
    {
        print_inner_class_attr(pthis->p_attr, p_pool, pool_count);
    }
    else if (strcmp(pthis->type, SOURCE_FILE) == 0)
    {
        print_source_file_attr(pthis->p_attr, p_pool, pool_count);
    }
    else if (strcmp(pthis->type, DEPRECATED) == 0)
    {
        printf(" Deprecated: true\n");
    }
    else if (strcmp(pthis->type, RUNTIME_VISIBLE_ANNOTATIONS) == 0)
    {
        print_rt_vis_annotation_attr(pthis->p_attr, p_pool, pool_count);
    }
    else if (strcmp(pthis->type, RUNTIME_VISIBLE_PARAM_ANNOTATIONS) == 0)
    {
        print_rt_vis_param_annotation_attr(pthis->p_attr, p_pool, pool_count);
    }
    else if (strcmp(pthis->type, RUNTIME_VISIBLE_TYPE_ANNOTATIONS) == 0)
    {
        print_rt_vis_type_annotation_attr(pthis->p_attr, p_pool, pool_count);
    }
    else if (strcmp(pthis->type, METHOD_PARAMETERS) == 0)
    {
        print_method_parameters_attr(pthis->p_attr, p_pool, pool_count);
    }
}
