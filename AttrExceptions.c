//
// Created by Administrator on 2024/5/19 0019.
//
#include "AttrExceptions.h"

void init_exceptions_attr(ExceptionsAttr* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->number_of_exceptions = read_n_byte(fp, U2);
    pthis->exception_index_table = malloc(pthis->number_of_exceptions * sizeof(unsigned int));
    for (int i = 0; i < pthis->number_of_exceptions; i++)
    {
        pthis->exception_index_table[i] = read_n_byte(fp, U2);
    }
}

void print_exceptions_attr(ExceptionsAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    printf(" Exceptions:\n");
    for (int i = 0; i < pthis->number_of_exceptions; i++)
    {
        char* exception = get_utf8_constant_value(p_pool, pool_count, pthis->exception_index_table[i]);
        char dest[1 << 8] = {0};
        printf("   throws %s\n", str_slash2dot(dest, exception, 0, 0));
    }
}