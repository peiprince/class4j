//
// Created by Administrator on 2024/5/26 0026.
//
#include "AttrBootstrapMethods.h"

static void init_bootstrap_methods(BootstrapMethods*, FILE*);

void init_bootstrap_methods_attr(BootstrapMethodsAttr* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->num_bootstrap_methods = read_n_byte(fp, U2);
    pthis->bootstrap_methods = malloc(pthis->num_bootstrap_methods * sizeof(BootstrapMethods));
    for (int i = 0; i < pthis->num_bootstrap_methods; i++)
    {
        BootstrapMethods methods = {0};
        init_bootstrap_methods(&methods, fp);
        pthis->bootstrap_methods[i] = methods;
    }
}

/**
 * 打印BootstrapMethods
 */
void print_bootstrap_methods_attr(BootstrapMethodsAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    printf(" BootstrapMethods:\n");
    for (int i = 0; i < pthis->num_bootstrap_methods; i++)
    {
        unsigned int method_ref = pthis->bootstrap_methods[i].bootstrap_method_ref;
        printf("   %d: #%d %s\n", i, method_ref, get_utf8_constant_value(p_pool, pool_count, method_ref));
        printf("      Method arguments:\n");
        for (int j = 0; j < pthis->bootstrap_methods[i].num_bootstrap_arguments; j++)
        {
            printf("      #%d %s\n", pthis->bootstrap_methods[i].bootstrap_arguments[j],
                   get_utf8_constant_value(p_pool, pool_count, (unsigned int) pthis->bootstrap_methods[i].bootstrap_arguments[j]));
        }
    }
}

static void init_bootstrap_methods(BootstrapMethods* pthis, FILE* fp)
{
    pthis->bootstrap_method_ref = read_n_byte(fp, U2);
    pthis->num_bootstrap_arguments = read_n_byte(fp, U2);
    pthis->bootstrap_arguments = malloc(pthis->num_bootstrap_arguments * sizeof(unsigned int));
    for (int i = 0; i < pthis->num_bootstrap_arguments; i++)
    {
        pthis->bootstrap_arguments[i] = read_n_byte(fp, U2);
    }
}