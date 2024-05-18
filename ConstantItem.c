//
// Created by Administrator on 2024/4/24 0024.
//
#include "ConstantItem.h"

static void read_utf8_info(FILE*, char*);
static void read_integer_info(FILE*, char*);
static void read_float_info(FILE*, char*);
static void read_long_info(FILE*, char*);
static void read_double_info(FILE*, char*);
static void read_class_info(FILE*, char*);
static void read_fieldref_info(FILE*, char*);

extern unsigned int g_index;

// 下标对应tag
const char const_type[13][20] = {
        "", "Utf8", "", "Integer","Float","Long","Double","Class","String",
        "Fieldref","Methodref","InterfaceMethodref","NameAndType"
};

void init_const_item(ConstantItem* pthis)
{
    pthis->index = 0;
    pthis->type = 0;
    // Utf8最长是65535 byte，附加64 byte冗余
    pthis->value = (char*) malloc(64 + (1 << 16));
}

void dispatch_constant_item(ConstantItem* pthis, FILE* fp, int type)
{
    pthis->type = type;
    switch (type)
    {
        case CONSTANT_Utf8_info:
            read_utf8_info(fp, pthis->value);
            break;
        case CONSTANT_Integer_info:
            read_integer_info(fp, pthis->value);
            break;
        case CONSTANT_Float_info:
            read_float_info(fp, pthis->value);
            break;
        case CONSTANT_Long_info:
            read_long_info(fp, pthis->value);
            break;
        case CONSTANT_Double_info:
            read_double_info(fp, pthis->value);
            break;
        // Class,String常量结构一致
        case CONSTANT_Class_info:
        case CONSTANT_String_info:
            read_class_info(fp, pthis->value);
            break;
        // Field,Method,Interface,NameAndType常量结构一致
        case CONSTANT_Fieldref_info:
        case CONSTANT_Methodref_info:
        case CONSTANT_InterfaceMethodref_info:
        case CONSTANT_NameAndType_info:
            read_fieldref_info(fp, pthis->value);
            break;
        default:
            break;
    }
}

static void read_utf8_info(FILE* fp, char* constant_value)
{
    int utf8_length = read_n_byte(fp, U2);
    int end_index = (int)g_index + utf8_length;
    char* utf8_bytes = (char*)malloc(utf8_length + 1);
    int utf8_index = 0;
    while (g_index < end_index)
    {
        utf8_bytes[utf8_index] = (char)fgetc(fp);
        g_index++;
        utf8_index++;
    }
    utf8_bytes[utf8_index] = '\0';
    strcpy(constant_value, utf8_bytes);
    free(utf8_bytes);
}

static void read_integer_info(FILE* fp, char* constant_value)
{
    int number = read_n_byte(fp, U4);
    sprintf(constant_value, "%d", number);
}

static void read_float_info(FILE* fp, char* constant_value)
{
    IntFloatUnion un;
    int number = read_n_byte(fp, U4);
    un.int_num = number;
    sprintf(constant_value, "%gf", un.float_num);
}

static void read_long_info(FILE* fp, char* constant_value)
{
    long long number = read_long_byte(fp);
    sprintf(constant_value, "%lldl", number);
}

static void read_double_info(FILE* fp, char* constant_value)
{
    LongDoubleUnion un;
    long long number = read_long_byte(fp);
    un.long_num = number;
    sprintf(constant_value, "%.15fd", un.double_num);
}

static void read_class_info(FILE* fp, char* constant_value)
{
    int class_index = read_n_byte(fp, U2);	// 读取class_info中的name_index
    sprintf(constant_value, "#%d", class_index);
}

static void read_fieldref_info(FILE* fp, char* constant_value)
{
    int index1 = read_n_byte(fp, U2);
    int index2 = read_n_byte(fp, U2);
    sprintf(constant_value, "#%d.#%d", index1, index2);
}

inline ConstantItem get_constant_item_by_index(ConstantItem* pthis, unsigned int pool_count, unsigned int index)
{
    ConstantItem result = pthis[0];
    for (int i = 0; i < pool_count; i++)
    {
        if (pthis[i].index == index)
        {
            result = pthis[i];
            break;
        }
    }
    return result;
}