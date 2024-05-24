//
// Created by Administrator on 2024/5/19 0019.
//
#include "AttrSourceFile.h"

void init_source_file_attr(SourceFileAttr* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->sourcefile_index = read_n_byte(fp, U2);
}

void print_source_file_attr(SourceFileAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    printf(" SourceFile: %s\n", get_constant_item_by_index(p_pool, pool_count, pthis->sourcefile_index).value);
}
