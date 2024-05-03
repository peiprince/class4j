//
// Created by Administrator on 2024/4/30 0030.
//
#include "AttrRtVisAnnotations.h"

void init_rt_vis_annotation_attr(RtVisAnnotationAttr* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->num_annotations = read_n_byte(fp, U2);
    pthis->annotations = malloc(pthis->num_annotations * sizeof(Annotation));
    // 读取annotaions
    for (int i = 0; i < pthis->num_annotations; i++)
    {
        add_annotation(pthis, fp, i);
    }
}

void add_annotation(RtVisAnnotationAttr* pthis, FILE* fp, unsigned int annotation_index)
{
    Annotation annotation = {0};
    init_annotation(&annotation, fp);
    pthis->annotations[annotation_index] = annotation;
}

void print_rt_vis_annotation_attr(RtVisAnnotationAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    ConstantItem item = get_constant_item_by_index(p_pool, pool_count, pthis->attribute_name_index);
    printf(" %s:\n", item.value);
    for (int i = 0; i < pthis->num_annotations; i++)
    {
        unsigned int type_index = pthis->annotations[i].type_index;
        printf("   %d: #%d()\n", i, type_index);
        printf("     %s\n", get_constant_item_by_index(p_pool, pool_count, type_index).value);
    }
}