//
// Created by Administrator on 2024/5/25 0025.
//
#include "AttrEnclosingMethod.h"

void init_enclosing_method_attr(EnclosingMethodAttr* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->class_index = read_n_byte(fp, U2);
    pthis->method_index = read_n_byte(fp, U2);
}

void print_enclosing_method_attr(EnclosingMethodAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    char* class_str = get_utf8_constant_value(p_pool, pool_count, pthis->class_index);
    char* temp_str = malloc(strlen(class_str));
    printf(" EnclosingMethod: #%d.#%d   // %s\n", pthis->class_index, pthis->method_index, str_slash2dot(temp_str, class_str, 0, 0));
    free(temp_str);
}