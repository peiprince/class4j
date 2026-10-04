//
// Created by Administrator on 2024/5/18 0018.
//
#include "AttrRtVisParamAnnotation.h"

static void init_param_annotation(ParamAnnotation*, FILE*);

void init_rt_vis_param_annotation_attr(RtVisParamAnnotationAttr* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->num_parameters = read_n_byte(fp, U1);
    pthis->parameter_annotations = malloc(pthis->num_parameters * sizeof(ParamAnnotation));
    for (int i = 0; i < pthis->num_parameters; i++)
    {
        ParamAnnotation annotation = {0};
        init_param_annotation(&annotation, fp);
        pthis->parameter_annotations[i] = annotation;
    }
}

void print_rt_vis_param_annotation_attr(RtVisParamAnnotationAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    printf(" RuntimeVisibleParameterAnnotation:\n");
    for (int i = 0; i < pthis->num_parameters; i++)
    {
        printf("   parameter %d:\n", i);
        for (int j = 0; j < pthis->parameter_annotations[i].num_annotations; j++)
        {
            print_annotation(&(pthis->parameter_annotations[i].annotations[j]), p_pool, pool_count, j);
        }
    }
}

static void init_param_annotation(ParamAnnotation* pthis, FILE* fp)
{
    pthis->num_annotations = read_n_byte(fp, U2);
    pthis->annotations = malloc(pthis->num_annotations * sizeof(Annotation));
    for (int i = 0; i < pthis->num_annotations; i++)
    {
        Annotation annotation = {0};
        init_annotation(&annotation, fp);
        pthis->annotations[i] = annotation;
    }
}