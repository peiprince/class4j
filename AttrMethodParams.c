//
// Created by Administrator on 2024/5/18 0018.
//
#include "AttrMethodParams.h"

static void init_parameter(Parameter*, FILE*);
static char* get_parameter_flag(unsigned int);

void init_method_parameters_attr(MethodParametersAttr* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->parameters_count = read_n_byte(fp, U1);
    pthis->parameters = malloc(pthis->parameters_count * sizeof(Parameter));
    for (int i = 0; i < pthis->parameters_count; i++)
    {
        Parameter parameter = {0};
        init_parameter(&parameter, fp);
        pthis->parameters[i] = parameter;
    }
}

void print_method_parameters_attr(MethodParametersAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    printf(" MethodParameters:\n");
    for (int i = 0; i < pthis->parameters_count; i++)
    {
        printf("   Name: %s, Flags: %s\n",
               get_constant_item_by_index(p_pool, pool_count, pthis->parameters[i].name_index).value,
               get_parameter_flag(pthis->parameters[i].access_flags));
    }
}

static void init_parameter(Parameter* pthis, FILE* fp)
{
    pthis->name_index = read_n_byte(fp, U2);
    pthis->access_flags = read_n_byte(fp, U2);
}

static char* get_parameter_flag(unsigned int flag)
{
    switch (flag) {
        case ACC_FINAL:
            return "ACC_FINAL";
        case ACC_SYNTHETIC:
            return "ACC_SYNTHETIC";
        case ACC_MANDATED:
            return "ACC_MANDATED";
        default:
            return "";
    }
}