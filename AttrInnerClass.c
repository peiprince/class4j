//
// Created by Administrator on 2024/5/24 0024.
//
#include "AttrInnerClass.h"

static void init_inner_class(InnerClass*, FILE*);

void init_inner_class_attr(InnerClassAttr* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->number_of_classes = read_n_byte(fp, U2);
    pthis->classes = malloc(pthis->number_of_classes * sizeof(InnerClass));
    for (int i = 0; i < pthis->number_of_classes; i++)
    {
        InnerClass inner_class = {0};
        init_inner_class(&inner_class, fp);
        pthis->classes[i] = inner_class;
    }
}

void print_inner_class_attr(InnerClassAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    printf(" InnerClasses:\n");
    for (int i = 0; i < pthis->number_of_classes; i++)
    {
        // 匿名内部类outer_class_info_index == 0, inner_class_info_index = 0
        if (pthis->classes[i].outer_class_info_index == 0 && pthis->classes[i].inner_name_index == 0)
        {
            printf("   #%d;    // %s\n", pthis->classes[i].inner_class_info_index,
                   get_utf8_constant_value(p_pool, pool_count, pthis->classes[i].inner_class_info_index));
        }
        else
        {
            printf("   #%d = #%d of #%d;    // %s=class %s of %s\n",
                   pthis->classes[i].inner_name_index, pthis->classes[i].inner_class_info_index, pthis->classes[i].outer_class_info_index,
                   get_utf8_constant_value(p_pool, pool_count, pthis->classes[i].inner_name_index),
                   get_utf8_constant_value(p_pool, pool_count, pthis->classes[i].inner_class_info_index),
                   get_utf8_constant_value(p_pool, pool_count, pthis->classes[i].outer_class_info_index));
        }
    }
}

static void init_inner_class(InnerClass* pthis, FILE* fp)
{
    pthis->inner_class_info_index = read_n_byte(fp, U2);
    pthis->outer_class_info_index = read_n_byte(fp, U2);
    pthis->inner_name_index = read_n_byte(fp, U2);
    pthis->inner_class_access_flags = read_n_byte(fp, U2);
}