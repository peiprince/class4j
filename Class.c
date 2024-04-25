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

void print_class_info(Class* pthis)
{
    printf(" minor version: %d, major version: %d, available for JDK %d and above.\n",
           pthis->minor_version, pthis->major_version, pthis->major_version - 44);

    // 打印常量池信息
    printf("Constant pool(total - %d):\n", pthis->constant_pool_count);
    for (int i = 0; i < pthis->constant_pool_count; i++)
    {
        ConstantItem item = pthis->constant_pool[i];
        printf(" #%d = %s\t\t%s\n", item.index, const_type[item.type], item.value);
    }
}
