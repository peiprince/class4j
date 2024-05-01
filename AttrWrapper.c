//
// Created by Administrator on 2024/4/27 0027.
//
#include "AttrWrapper.h"

void init_attr_wrapper(AttrWrapper* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->type = pconst_item->value;
    if (strcmp(pthis->type, CONSTANT_VALUE) == 0 || strcmp(pthis->type, SIGNATURE) == 0)
    {
        ConstantAttr* p_constant = malloc(sizeof(ConstantAttr));
        init_constant_attr(p_constant, pconst_item, fp);
        pthis->p_attr = p_constant;
    }
    else if (strcmp(pthis->type, DEPRECATED) == 0)
    {
        DeprecatedAttr* p_deprecated = malloc(sizeof(DeprecatedAttr));
        init_deprecated_attr(p_deprecated, pconst_item, fp);
        pthis->p_attr = p_deprecated;
    }
    else if (strcmp(pthis->type, "RuntimeVisibleAnnotations") == 0)
    {
        RtVisAnnotationAttr* p_annotation = malloc(sizeof(RtVisAnnotationAttr));
        init_rt_vis_annotation_attr(p_annotation, pconst_item, fp);
        pthis->p_attr = p_annotation;
    }
}

void print_attr_info(AttrWrapper* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    if (strcmp(pthis->type, CONSTANT_VALUE) == 0 || strcmp(pthis->type, SIGNATURE) == 0)
    {
        ConstantAttr* p_constant = (ConstantAttr*) pthis->p_attr;
        print_constant_value_attr(p_constant, p_pool, pool_count);
    }
    else if (strcmp(pthis->type, DEPRECATED) == 0)
    {
        printf(" Deprecated: true\n");
    }
    else if (strcmp(pthis->type, "RuntimeVisibleAnnotations") == 0)
    {
        RtVisAnnotationAttr* p_annotation = (RtVisAnnotationAttr*) pthis->p_attr;
        print_rt_vis_annotation_attr(p_annotation, p_pool, pool_count);
    }
}
