//
// Created by Administrator on 2024/5/12 0012.
//
#include "AttrLocalVariableTable.h"

static void init_table_element(LocalVariableTableElement*, FILE*);
static void print_table_element(LocalVariableTableAttr*, ConstantItem*, unsigned int);


void init_local_variable_table_attr(LocalVariableTableAttr* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->local_variable_table_length = read_n_byte(fp, U2);
    pthis->local_variable_table = malloc(pthis->local_variable_table_length * sizeof(LocalVariableTableElement));
    for (int i = 0; i < pthis->local_variable_table_length; i++)
    {
        LocalVariableTableElement element = {0};
        init_table_element(&element, fp);
        pthis->local_variable_table[i] = element;
    }
}

/**
 * 初始化LocalVariableTableElement
 */
static void init_table_element(LocalVariableTableElement* pthis, FILE* fp)
{
    pthis->start_pc = read_n_byte(fp, U2);
    pthis->length = read_n_byte(fp, U2);
    pthis->name_index = read_n_byte(fp, U2);
    pthis->descriptor_index = read_n_byte(fp, U2);
    pthis->index = read_n_byte(fp, U2);
}

void print_local_variable_table_attr(LocalVariableTableAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    printf("   LocalVariableTable:\n");
    print_table_element(pthis, p_pool, pool_count);
}

void print_local_variable_type_table_attr(LocalVariableTableAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    printf("   LocalVariableTypeTable:\n");
    print_table_element(pthis, p_pool, pool_count);
}

static void print_table_element(LocalVariableTableAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    for (int i = 0; i < pthis->local_variable_table_length; i++)
    {
        LocalVariableTableElement element = pthis->local_variable_table[i];
        printf("     Start: %u, Length: %u, Slot: %u, Name: %s, Signature: %s\n", element.start_pc, element.length, element.index,
               get_constant_item_by_index(p_pool, pool_count, pthis->local_variable_table[i].name_index).value,
               get_constant_item_by_index(p_pool, pool_count, pthis->local_variable_table[i].descriptor_index).value);
    }
}