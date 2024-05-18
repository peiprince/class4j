//
// Created by Administrator on 2024/5/11 0011.
//
#include "AttrLineNumberTable.h"

static void init_table_element(LineNumberTableElement*, FILE*);

void init_line_number_table_attr(LineNumberTableAttr* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->line_number_table_length = read_n_byte(fp, U2);
    pthis->line_number_table = malloc(pthis->line_number_table_length * sizeof(LineNumberTableElement));
    for (int i = 0; i < pthis->line_number_table_length; i++)
    {
        LineNumberTableElement element = {0};
        init_table_element(&element, fp);
        pthis->line_number_table[i] = element;
    }
}

/**
 * 初始化TableElement
 */
static void init_table_element(LineNumberTableElement* pthis, FILE* fp)
{
    pthis->start_pc = read_n_byte(fp, U2);
    pthis->line_number = read_n_byte(fp, U2);
}

void print_line_number_table(LineNumberTableAttr* pthis)
{
    printf("   LineNumberTable:\n");
    for (int i = 0; i < pthis->line_number_table_length; i++)
    {
        printf("     line %u: %u\n", pthis->line_number_table[i].line_number, pthis->line_number_table[i].start_pc);
    }
}