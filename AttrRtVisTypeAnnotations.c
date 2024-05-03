//
// Created by Administrator on 2024/5/1 0001.
//
#include "AttrRtVisTypeAnnotations.h"

void init_rt_vis_type_annotation_attr(RtVisTypeAnnotationAttr* pthis, ConstantItem* p_const, FILE* fp)
{
    pthis->attribute_name_index = p_const->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->num_annotations = read_n_byte(fp, U2);
    pthis->annotations = malloc(pthis->num_annotations * sizeof(TypeAnnotation));
    for (int i = 0; i < pthis->num_annotations; i++)
    {
        add_type_annotation(pthis, fp, i);
    }
}

void print_rt_vis_type_annotation_attr(RtVisTypeAnnotationAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    ConstantItem item = get_constant_item_by_index(p_pool, pool_count, pthis->attribute_name_index);
    printf(" %s:\n", item.value);
    for (int i = 0; i < pthis->num_annotations; i++)
    {
        print_type_annotation(&pthis->annotations[i], p_pool, pool_count, i);
    }
}

void add_type_annotation(RtVisTypeAnnotationAttr* pthis, FILE* fp, unsigned int annotation_index)
{
    TypeAnnotation typeAnnotation = {0};
    init_type_annotation(&typeAnnotation, fp);
    pthis->annotations[annotation_index] = typeAnnotation;
}

void init_type_annotation(TypeAnnotation* pthis, FILE* fp)
{
    pthis->target_type = read_n_byte(fp, U1);

    // 初始化target_info
    TargetInfo target_info = {0};
    init_target_info(&target_info, fp, pthis->target_type);
    pthis->target_info = &target_info;

    // 初始化target_path
    int path_length = read_n_byte(fp, U1);
    pthis->target_path.path_length = path_length;
    for (int i = 0; i < path_length; i++)
    {
        TPath path = {0};
        init_t_path(&path, fp);
        pthis->target_path.path[i] = path;
    }

    Annotation* p_annotation = malloc(sizeof(Annotation));
    init_annotation(p_annotation, fp);
    pthis->annotation = p_annotation;
}

void print_type_annotation(TypeAnnotation* pthis, ConstantItem* p_pool, unsigned int pool_count, unsigned int annotation_index)
{
    // 打印target_info
    char* location = "";
    unsigned int type_index = pthis->annotation->type_index;
    printf("   %d: #%d(): %s\n", annotation_index, type_index, locate_annotation(location, pthis->target_type));
    ConstantItem item = get_constant_item_by_index(p_pool, pool_count, type_index);
    printf("     %s\n", item.value);
}

void init_target_info(TargetInfo* pthis, FILE* fp, unsigned int type_index)
{
    int table_length = 0;
    switch (type_index) {
        case 0x00:
        case 0x01:
            pthis->type_parameter_target.type_parameter_index = read_n_byte(fp, U1);
            break;
        case 0x10:
            pthis->supertype_target.supertype_index = read_n_byte(fp, U2);
            break;
        case 0x11:
        case 0x12:
            pthis->type_parameter_bound_target.type_parameter_bound_index = read_n_byte(fp, U1);
            pthis->type_parameter_bound_target.bound_index = read_n_byte(fp, U1);
            break;
        case 0x13:
        case 0x14:
        case 0x15:
            break;
        case 0x16:
            pthis->method_formal_parameter_target.formal_parameter_index = read_n_byte(fp, U1);
            break;
        case 0x17:
            pthis->throws_target.throws_type_index = read_n_byte(fp, U2);
            break;
        case 0x40:
        case 0x41:
            table_length = read_n_byte(fp, U2);
            pthis->localvar_target.table_length = table_length;
            pthis->localvar_target.table = malloc(table_length * sizeof(LocalVar));
            for (int i = 0; i < table_length; i++)
            {
                add_local_var(pthis, fp, i);
            }
            break;
        case 0x42:
            pthis->catch_target.exception_table_index = read_n_byte(fp, U2);
            break;
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
            pthis->offset_target.offset = read_n_byte(fp, U2);
            break;
        case 0x47:
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x4B:
            pthis->type_argument_target.argument_offset = read_n_byte(fp, U2);
            pthis->type_argument_target.type_argument_index = read_n_byte(fp, U1);
            break;
        default:
            break;
    }
}

void add_local_var(TargetInfo* pthis, FILE* fp, unsigned int var_index)
{
    LocalVar local_var = {0};
    init_local_var(&local_var, fp);
    pthis->localvar_target.table[var_index] = local_var;
}

char* locate_annotation(char* location, unsigned int target_type)
{
    switch (target_type) {
        case 0x00:
        case 0x10:
        case 0x11:
            // ClassFile
            break;
        case 0x01:
        case 0x12:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
            // method_file
            break;
        case 0x13:
            location = "FIELD";
            break;
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
        case 0x47:
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x4B:
            // Code
            break;
        default:
            break;
    }
    return location;
}

void init_local_var(LocalVar* pthis, FILE* fp)
{
    pthis->start_pc = read_n_byte(fp, U2);
    pthis->length = read_n_byte(fp, U2);
    pthis->index = read_n_byte(fp, U2);
}

void init_t_path(TPath* pthis, FILE* fp)
{
    pthis->type_path_kind = read_n_byte(fp, U1);
    pthis->type_argument_index = read_n_byte(fp, U1);
}