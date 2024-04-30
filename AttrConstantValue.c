//
// Created by Administrator on 2024/4/29 0029.
//

#include "AttrConstantValue.h"

extern char const_type[13][20];

void init_constant_attr(ConstantAttr* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->constant_value_index = read_n_byte(fp, pthis->attribute_length);
}

void print_constant_value_attr(ConstantAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    char* attr_type = get_constant_item_by_index(p_pool, pool_count, pthis->attribute_name_index).value;
    ConstantItem item = get_constant_item_by_index(p_pool, pool_count, pthis->constant_value_index);
    printf(" %s: %s %s\n", attr_type, const_type[item.type], item.value);
}