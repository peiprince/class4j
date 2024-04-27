//
// Created by Administrator on 2024/4/26 0026.
//
#include "FieldItem.h"

void read_field_attr(FieldItem* pthis, FILE* fp, unsigned int count)
{
    init_attr_table(pthis, count);
}

void init_attr_table(FieldItem* pthis, unsigned int count)
{
    pthis->attributes_count = count;
    pthis->attr_table = (AttrWrapper*) malloc(count * sizeof(AttrWrapper));
}

void print_field_item(FieldItem* pthis, ConstantItem* pconst_pool, int pool_count)
{
    char* field_name = NULL;
    char* field_descriptor = NULL;
    for (int i = 0; i < pool_count; i++)
    {
        ConstantItem item = pconst_pool[i];
        if (field_name != NULL && field_descriptor != NULL)
        {
            break;
        }
        if (item.index == pthis->cons_index)    // 读取字段名称
        {
            field_name = (char*) malloc(strlen(item.value) + 1);
            strcpy(field_name, item.value);
        }
        if (item.index == pthis->descriptor)    // 读取字段描述符
        {
            field_descriptor = (char*) malloc(strlen(item.value) + 1);
            strcpy(field_descriptor, item.value);
        }
    }
    printf("%s;\n", field_name);
    printf(" descriptor: %s\n", field_descriptor);
    printf_field_flag(pthis);
//    pthis->printf_field_attr(pthis);
    printf(" Attribute number: %d\n", pthis->attributes_count);
    printf("\n");
    free(field_name);
    free(field_descriptor);
}

void printf_field_flag(FieldItem* pthis)
{
    char flags_info[128] = {0};
    int byte1 = 0x000F & pthis->flags;
    int byte2 = 0x00F0 & pthis->flags;
    int byte4 = 0xF000 & pthis->flags;
    // byte1
    concat_flag_info(byte1, ACC_PUBLIC, flags_info, "ACC_PUBLIC, ");
    concat_flag_info(byte1, ACC_PROTECTED, flags_info, "ACC_PROTECTED, ");
    concat_flag_info(byte1, ACC_PRIVATE, flags_info, "ACC_PRIVATE, ");
    concat_flag_info(byte1, ACC_STATIC, flags_info, "ACC_STATIC, ");
    concat_flag_info(byte1, ACC_PUBLIC + ACC_STATIC, flags_info, "ACC_PUBLIC, ACC_STATIC, ");
    concat_flag_info(byte1, ACC_PROTECTED + ACC_STATIC, flags_info, "ACC_PROTECTED, ACC_STATIC, ");
    concat_flag_info(byte1, ACC_PRIVATE + ACC_STATIC, flags_info, "ACC_PRIVATE, ACC_STATIC, ");
    // byte2
    concat_flag_info(byte2, ACC_FINAL, flags_info, "ACC_FINAL, ");
    concat_flag_info(byte2, ACC_TRANSIENT, flags_info, "ACC_TRANSIENT, ");
    concat_flag_info(byte2, ACC_VOLATILE, flags_info, "ACC_VOLATILE, ");
    concat_flag_info(byte2, ACC_FINAL + ACC_TRANSIENT, flags_info, "ACC_FINAL, ACC_TRANSIENT, ");
    concat_flag_info(byte2, ACC_VOLATILE + ACC_TRANSIENT, flags_info, "ACC_VOLATILE, ACC_TRANSIENT, ");
    // byte4
    concat_flag_info(byte4, ACC_SYNTHETIC, flags_info, "ACC_SYNTHETIC, ");
    concat_flag_info(byte4, ACC_ENUM, flags_info, "ACC_ENUM, ");

    size_t length = strlen(flags_info);
    if (length > 0)
    {
        flags_info[length - 2] = '\0';
    }
    printf(" flags: (0x%04x) %s\n", pthis->flags, flags_info);
}