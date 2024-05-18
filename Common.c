//
// Created by Administrator on 2024/4/23 0023.
//
#include "Common.h"

unsigned int power = 0;
unsigned int g_index = 0;	// 文件指针

inline int read_n_byte(FILE* fp, int n)
{
    int result = 0;
    power = 2 * n - 1;  // 一个字节对应两个16进制数
    unsigned int end_index = g_index + n;
    while (g_index < end_index)
    {
        int temp = fgetc(fp);
        int h = (0xF0 & temp) / HEX_BASE;     // 高位需要除掉16
        int l = 0x0F & temp;                  // 低位
        result += h * (int)pow(HEX_BASE, power--);
        result += l * (int)pow(HEX_BASE, power--);
        g_index++;
    }
    return result;
}

long long read_long_byte(FILE* fp)
{
    long long result = 0;
    power = 2 * U8 - 1;  // 一个字节对应两个16进制数
    unsigned int end_index = g_index + U8;
    while (g_index < end_index)
    {
        int temp = fgetc(fp);
        int h = (0xF0 & temp) / HEX_BASE;     // 高位需要除掉16
        int l = 0x0F & temp;                  // 低位
        result += h * (long long)pow(HEX_BASE, power--);
        result += l * (long long)pow(HEX_BASE, power--);
        g_index++;
    }
    return result;
}

void concat_flag_info(int byte, int target, char* result, char* info)
{
    if (byte == target)
    {
        strcat(result, info);
    }
}

char* str_slash2dot(char* dest, char* source, unsigned int source_index, int source_end_index)
{
    unsigned int dest_index = 0;
    for (int i = 0; i < strlen(source) + source_end_index; i++)
    {
        // 从source的第source_index位开始复制
        if (i < source_index)
        {
            continue;
        }
        if ('/' == source[i])
        {
            dest[dest_index] = '.';
        }
        else
        {
            dest[dest_index] = source[i];
        }
        dest_index++;
    }
    dest[dest_index] = '\0';
    return dest;
}
