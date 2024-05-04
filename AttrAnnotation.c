//
// Created by Administrator on 2024/5/2 0002.
//
#include "AttrAnnotation.h"

void init_annotation(Annotation* pthis, FILE* fp)
{
    pthis->type_index = read_n_byte(fp, U2);
    pthis->num_element_value_pairs = read_n_byte(fp, U2);
    pthis->element_value_pairs = malloc(pthis->num_element_value_pairs * sizeof(ElementValuePair));
    // 读取element_value_pairs
    for (int j = 0; j < pthis->num_element_value_pairs; j++)
    {
        add_element_value_pair(pthis, fp, j);
    }
}

void add_element_value_pair(Annotation* pthis, FILE* fp, unsigned int pair_index)
{
    ElementValuePair pair = {0};
    pair.element_name_index = read_n_byte(fp, U2);
    pair.value = malloc(sizeof(ElementValue));
    init_element_value(pair.value, fp);
    pthis->element_value_pairs[pair_index] = pair;
}

void print_annotation(Annotation* pthis, ConstantItem* p_pool, unsigned int pool_count, unsigned int annotation_index)
{
    unsigned int type_index = pthis->type_index;
    // 拼接注解参数
    char param_info[1 << 8] = {0};
    char param_value_info[1 << 8] = {0};
    for (int i = 0; i < pthis->num_element_value_pairs; i++)
    {
        char* index_str = malloc(1 << 8);   // (#10=J#11,#13=s#14)
        char* value_str = malloc(1 << 8);   // (value=1000l message="haha")
        concat_param_key_value(&pthis->element_value_pairs[i], p_pool, pool_count, index_str, value_str);
        concat_flag_info(U1, U1, param_info, index_str);
        concat_flag_info(U1, U1, param_value_info, value_str);
        free(index_str);
        free(value_str);
    }
    param_info[strlen(param_info) - 1] = '\0';

    printf("   %d: #%d(%s)\n", annotation_index, type_index, param_info);
    char* source = get_constant_item_by_index(p_pool, pool_count, type_index).value;
    char dest[1 << 8] = {0};
    if (strlen(param_value_info) != 0)
    {
        param_value_info[strlen(param_value_info) - 1] = '\0';
        printf("     %s(%s)\n", str_slash2dot(dest, source, 1, -1), param_value_info);
    }
    else
    {
        printf("     %s\n", str_slash2dot(dest, source, 1, -1));
    }
}

char* concat_param_key_value(ElementValuePair* pthis, ConstantItem* p_pool, unsigned int pool_count, char* index_str, char* value_str)
{
    char* value;
    unsigned int value_index = 0;
    switch (pthis->value->tag) {
        case 'B':
        case 'C':
        case 'D':
        case 'F':
        case 'I':
        case 'J':
        case 'S':
        case 'Z':
        case 's':
            value_index = pthis->value->value->const_value_index;
            value = get_constant_item_by_index(p_pool, pool_count, pthis->value->value->const_value_index).value;
            break;
        default:
            value = "";
            break;
    };
    sprintf(index_str, "#%u=%c#%u,", pthis->element_name_index, pthis->value->tag, value_index);
    char* index = get_constant_item_by_index(p_pool, pool_count, pthis->element_name_index).value;
    sprintf(value_str, "%s=%s ", index, value);
    return value_str;
}

void init_element_value(ElementValue* pthis, FILE* fp)
{
    pthis->tag = (char) read_n_byte(fp, U1);
    EValue* value = malloc(sizeof(EValue));
    switch (pthis->tag) {
        case 'B':
        case 'C':
        case 'D':
        case 'F':
        case 'I':
        case 'J':
        case 'S':
        case 'Z':
        case 's':
            value->const_value_index = read_n_byte(fp, U2);
            break;
        case 'e':
            value->enum_const_value.type_name_index = read_n_byte(fp, U2);
            value->enum_const_value.const_name_index = read_n_byte(fp, U2);
            break;
        case 'c':
            value->class_info_index = read_n_byte(fp, U2);
            break;
        case '@':
            value->annotation_value = malloc(sizeof(Annotation));
            init_annotation(value->annotation_value, fp);
            break;
        case '[':
            value->array_value.num_values = read_n_byte(fp, U2);
            value->array_value.values = malloc(value->array_value.num_values * sizeof(ElementValue));
            for (int i = 0; i < value->array_value.num_values; i++)
            {
                init_element_value(&value->array_value.values[i], fp);
            }
            break;
        default:
            break;
    }
    pthis->value = value;
}
