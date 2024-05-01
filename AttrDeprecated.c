//
// Created by Administrator on 2024/4/30 0030.
//
#include "AttrDeprecated.h"

void init_deprecated_attr(DeprecatedAttr* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
}