//
// Created by Administrator on 2024/4/23 0023.
//
#include "Class.h"

extern char const_type[11][20];
extern unsigned int g_index;
extern unsigned int power;

/*
 * class版本号：	 45	 | 46  | 47  | 48  | 49  | 50  | 51  | 52  | ...
 * JDK版本号：JDK 1.1 | 1.2 | 1.3 | 1.4 | 1.5 | 1.6 | 1.7 | 1.8 | ...
 * class版本号 和 JDK版本号依次+1
 */
void check_class_version(Class* pthis, FILE* fp)
{
    // 魔数
    int magic_num = read_n_byte(fp, U4);
    assert(magic_num == 0xcafebabe);

    pthis->minor_version = read_n_byte(fp, U2);
    pthis->major_version = read_n_byte(fp, U2);
}

void read_constant_pool(Class* pthis, FILE* fp)
{
    // class文件中常量池计数从1开始，需要-1
    int pool_count = read_n_byte(fp, U2);
    init_constant_pool(pthis, --pool_count);

    int pool_index = 0;
    bool skip_flag = false;
    for (int i = 1; i <= pthis->constant_pool_count; i++)
    {
        // Long和Double类型的常量占用8个字节，下次循环要跳过一次，常量总数要-1
        if (skip_flag)
        {
            skip_flag = false;
            pool_count--;
            continue;
        }
        // 读取第一个字节，判断常量类型
        int type = read_n_byte(fp, U1);
        skip_flag = (type == CONSTANT_Long_info || type == CONSTANT_Double_info);
        dispatch_constant_item(&(pthis->constant_pool[pool_index]), fp, type);
        pthis->constant_pool[pool_index].index = i;
        pool_index++;
    }
    // 初始化的pool_count未必准确，要在此处重置为准确值
    pthis->constant_pool_count = pool_count;
}

void init_constant_pool(Class* pthis, int count)
{
    pthis->constant_pool_count = count;
    pthis->constant_pool = (ConstantItem *) malloc(count * sizeof(ConstantItem));
    for (int i = 0; i < count; i++)
    {
        ConstantItem item;
        construct_const_item(&item);
        pthis->constant_pool[i] = item;
    }
}

void read_access_flags(Class* pthis, FILE* fp, FlagType type)
{
    int flags = read_n_byte(fp, U2);
    switch (type) {
        case ClassType:
            pthis->flags = flags;
            break;
        case FieldType:
            break;
    }
}

void read_class_interface_info(Class* pthis, FILE* fp)
{
    pthis->this_class = read_n_byte(fp, U2);
    pthis->super_class  = read_n_byte(fp, U2);
    pthis->interface_count = read_n_byte(fp, U2);
}

void read_field_info(Class* pthis, FILE* fp)
{
    // 初始化常量表
    init_field_table(pthis, read_n_byte(fp, U2));
    // 解析字段信息
    for (int i = 0; i < pthis->field_count; i++)
    {
        pthis->field_table[i].flags = read_n_byte(fp, U2);
        pthis->field_table[i].cons_index = read_n_byte(fp, U2);
        pthis->field_table[i].descriptor = read_n_byte(fp, U2);
        // 读取当前字段的属性数量并初始化属性表
        unsigned int attr_count = read_n_byte(fp, U2);
        if (attr_count <= 0)
        {
            continue;
        }
//        read_field_attr(&(pthis->field_table[i]), fp, attr_count);
        // 读取字段属性表
//        for (int j = 0; j < attr_count; j++)
//        {
            // 当前attribute在常量池中的index
//            int attr_index = read_n_byte(fp, U2);
//            ConstantItem item = pthis.get_constant_item_by_index(attr_index, &class);
//            append_attr(&class.field_table[i], j, &item, p_class);
//        }
    }
}

void init_field_table(Class* pthis, int count)
{
    pthis->field_count = count;
    pthis->field_table = (FieldItem *) malloc(count * sizeof(FieldItem));
    for (int i = 0; i < count; i++)
    {
        FieldItem item = {0};
        pthis->field_table[i] = item;
    }
}

void print_class_info(Class* pthis, char* path)
{
    printf(" minor version: %d, major version: %d, available for JDK %d and above.\n",
           pthis->minor_version, pthis->major_version, pthis->major_version - 44);

    printf_class_flag(pthis);
    // 打印常量池信息
    printf("Constant pool(total - %d):\n", pthis->constant_pool_count);
    for (int i = 0; i < pthis->constant_pool_count; i++)
    {
        ConstantItem item = pthis->constant_pool[i];
        printf(" #%d = %s\t\t%s\n", item.index, const_type[item.type], item.value);
    }
    // 打印字段表信息
    for (int i = 0; i < pthis->field_count; i++)
    {
        print_field_item(&(pthis->field_table[i]), pthis->constant_pool, pthis->constant_pool_count);
    }
}

void printf_class_flag(Class* pthis)
{
    char flags_info[128] = {0};
    int byte1 = 0x000F & pthis->flags;
    int byte2 = 0x00F0 & pthis->flags;
    int byte3 = 0x0F00 & pthis->flags;
    int byte4 = 0xF000 & pthis->flags;
    // byte1
    concat_flag_info(byte1, ACC_PUBLIC, flags_info, "ACC_PUBLIC, ");
    // byte2
    concat_flag_info(byte2, ACC_FINAL, flags_info, "ACC_FINAL, ");
    concat_flag_info(byte2, ACC_SUPER, flags_info, "ACC_SUPER, ");
    concat_flag_info(byte2, ACC_FINAL + ACC_SUPER, flags_info, "ACC_FINAL, ACC_SUPER, ");
    // byte3
    concat_flag_info(byte3, ACC_INTERFACE + ACC_ABSTRACT, flags_info, "ACC_INTERFACE, ACC_ABSTRACT, ");
    concat_flag_info(byte3, ACC_ABSTRACT, flags_info, "ACC_ABSTRACT, ");
    // byte4
    concat_flag_info(byte4, ACC_SYNTHETIC, flags_info, "ACC_SYNTHETIC, ");
    concat_flag_info(byte4, ACC_ANNOTATION, flags_info, "ACC_ANNOTATION, ");
    concat_flag_info(byte4, ACC_ENUM, flags_info, "ACC_ENUM, ");

    size_t length = strlen(flags_info);
    flags_info[length - 2] = '\0';
    printf(" flags: (0x%04x) %s\n", pthis->flags, flags_info);
}