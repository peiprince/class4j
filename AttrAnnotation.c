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
    init_elementValue(pair.value, fp);
    pthis->element_value_pairs[pair_index] = pair;
}

void init_elementValue(ElementValue* pthis, FILE* fp)
{
    pthis->tag = (char) read_n_byte(fp, U1);
}