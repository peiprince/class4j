//
// Created by Administrator on 2024/5/5 0005.
//
#include "AttrCode.h"

void init_code_attr(CodeAttr* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->max_stack = read_n_byte(fp, U2);
    pthis->max_locals = read_n_byte(fp, U2);
    pthis->code_length = read_n_byte(fp, U4);
    pthis->code = read_n_byte(fp, U1);  // TODO
    pthis->exception_table_length = read_n_byte(fp, U2);
    pthis->exception_item = malloc(pthis->exception_table_length * sizeof(ExceptionItem));
    for (int i = 0; i < pthis->exception_table_length; i++)
    {
        init_exception_item(&pthis->exception_item[i], fp);
    }
    pthis->attributes_count = read_n_byte(fp, U2);
}

void print_code_attr(CodeAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    ConstantItem item = get_constant_item_by_index(p_pool, pool_count, pthis->attribute_name_index);
    printf(" %s:\n", item.value);
    printf("   stack=%d, locals=%d, args_size=%d\n", pthis->max_stack, pthis->max_locals, pthis->max_locals);
}

void init_exception_item(ExceptionItem* pthis, FILE* fp)
{
    pthis->start_pc = read_n_byte(fp, U2);
    pthis->end_pc = read_n_byte(fp, U2);
    pthis->handler_pc = read_n_byte(fp, U2);
    pthis->catch_type = read_n_byte(fp, U2);
}