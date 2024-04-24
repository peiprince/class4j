//
// Created by Administrator on 2024/4/23 0023.
//
#include "Class.h"

void check_class_version(FILE* fp, Class* p_class)
{
    // 魔数
    int magic_num = read_n_byte(fp, U4);
    assert(magic_num == 0xcafebabe);

    p_class->minor_version = read_n_byte(fp, U2);
    p_class->major_version = read_n_byte(fp, U2);
}

void print_class_info(Class* p_class)
{
    printf(" minor version: %d, major version: %d, available for JDK %d and above.\n",
           p_class->minor_version, p_class->major_version, p_class->major_version - 44);
}
