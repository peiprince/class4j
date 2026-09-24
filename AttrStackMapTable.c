//
// Created by Administrator on 2024/5/26 0026.
//
#include "AttrStackMapTable.h"

static void init_stack_map_frame(StackMapFrame*, FILE*);
static void init_verification_type_info(VerificationTypeInfo*, FILE*);
static void print_verification_type_info(VerificationTypeInfo* pthis, ConstantItem* p_pool, unsigned int pool_count);

void init_stack_map_table_attr(StackMapTableAttr* pthis, ConstantItem* pconst_item, FILE* fp)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->number_of_entries = read_n_byte(fp, U2);
    pthis->entries = malloc(pthis->number_of_entries * sizeof(StackMapFrame));
    for (int i = 0; i < pthis->number_of_entries; i++)
    {
        StackMapFrame frame = {0};
        init_stack_map_frame(&frame, fp);
        pthis->entries[i] = frame;
    }
}

void print_stack_map_table_attr(StackMapTableAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    printf("  StackMapTable: number of entries = %d\n", pthis->number_of_entries);
    for (int i = 0; i < pthis->number_of_entries; i++)
    {
        unsigned int frame_type = pthis->entries[i].same_frame.frame_type;
        if (frame_type <= 63)
        {
            printf("     frame_type = %d /* same */\n", frame_type);
        }
        else if (frame_type <= 127)
        {
            printf("     frame_type = %d /* same_locals_1_stack_item */\n", frame_type);
            printf("     stack: ");
            print_verification_type_info(pthis->entries[i].same_locals_1_stack_item_frame.stack, p_pool, pool_count);
        }
        else if (frame_type == 247)
        {
            printf("     frame_type = %d /* same_locals_1_stack_item_extended */\n", frame_type);
            printf("     offset_delta = %d\n", pthis->entries[i].same_locals_1_stack_item_frame_extended.offset_delta);
            printf("     stack: ");
            print_verification_type_info(pthis->entries[i].same_locals_1_stack_item_frame_extended.stack, p_pool, pool_count);
        }
        else if (frame_type >= 248 && frame_type <= 250)
        {
            printf("     frame_type = %d /* chop */\n", frame_type);
            printf("     offset_delta = %d\n", pthis->entries[i].chop_frame.offset_delta);
        }
        else if (frame_type == 251)
        {
            printf("     frame_type = %d /* same_frame_extended */\n", frame_type);
            printf("     offset_delta = %d\n", pthis->entries[i].same_frame_extended.offset_delta);
        }
        else if (frame_type >= 252 && frame_type <= 254)
        {
            printf("     frame_type = %d /* append */\n", frame_type);
            printf("     offset_delta = %d\n", pthis->entries[i].append_frame.offset_delta);
            unsigned int length = frame_type - 251;
            for (int j = 0; j < length; j++)
            {
                printf("     local: ");
                print_verification_type_info(&pthis->entries[i].append_frame.locals[j], p_pool, pool_count);
            }
        }
        else if (frame_type == 255)
        {
            printf("     frame_type = %d /* full_frame */\n", frame_type);
            printf("     offset_delta = %d\n", pthis->entries[i].full_frame.offset_delta);
            printf("     number_of_locals = %d\n", pthis->entries[i].full_frame.number_of_locals);
            for (int j = 0; j < pthis->entries[i].full_frame.number_of_locals; j++)
            {
                printf("     local: ");
                print_verification_type_info(&pthis->entries[i].full_frame.locals[j], p_pool, pool_count);
            }
            printf("     number_of_stack_items = %d\n", pthis->entries[i].full_frame.number_of_stack_items);
            for (int j = 0; j < pthis->entries[i].full_frame.number_of_stack_items; j++)
            {
                printf("     stack: ");
                print_verification_type_info(&pthis->entries[i].full_frame.stack[j], p_pool, pool_count);
            }
        }
    }
}

static void init_stack_map_frame(StackMapFrame* pthis, FILE* fp)
{
    unsigned int frame_type = read_n_byte(fp, U1);
    if (frame_type <= 63)
    {
        pthis->same_frame.frame_type = frame_type;
    }
    else if (frame_type <= 127)
    {
        pthis->same_locals_1_stack_item_frame.frame_type = frame_type;
        VerificationTypeInfo info = {0};
        init_verification_type_info(&info, fp);
        pthis->same_locals_1_stack_item_frame.stack = &info;
    }
    else if (frame_type == 247)
    {
        pthis->same_locals_1_stack_item_frame_extended.frame_type = frame_type;
        pthis->same_locals_1_stack_item_frame_extended.offset_delta = read_n_byte(fp, U2);
        VerificationTypeInfo info = {0};
        init_verification_type_info(&info, fp);
        pthis->same_locals_1_stack_item_frame_extended.stack = &info;
    }
    else if (frame_type >= 248 && frame_type <= 250)
    {
        pthis->chop_frame.frame_type = frame_type;
        pthis->chop_frame.offset_delta = read_n_byte(fp, U2);
    }
    else if (frame_type == 251)
    {
        pthis->same_frame_extended.frame_type = frame_type;
        pthis->same_frame_extended.offset_delta = read_n_byte(fp, U2);
    }
    else if (frame_type >= 252 && frame_type <= 254)
    {
        pthis->append_frame.frame_type = frame_type;
        pthis->append_frame.offset_delta = read_n_byte(fp ,U2);
        unsigned int length = frame_type - 251;
        pthis->append_frame.locals = malloc(length * sizeof(VerificationTypeInfo));
        for (int i = 0; i < length; i++)
        {
            VerificationTypeInfo info = {0};
            init_verification_type_info(&info, fp);
            pthis->append_frame.locals[i] = info;
        }
    }
    else if (frame_type == 255)
    {
        pthis->full_frame.frame_type = frame_type;
        pthis->full_frame.offset_delta = read_n_byte(fp ,U2);
        pthis->full_frame.number_of_locals = read_n_byte(fp ,U2);
        pthis->full_frame.locals = malloc(pthis->full_frame.number_of_locals * sizeof(VerificationTypeInfo));
        for (int i = 0; i < pthis->full_frame.number_of_locals; i++)
        {
            VerificationTypeInfo info = {0};
            init_verification_type_info(&info, fp);
            pthis->full_frame.locals[i] = info;
        }
        pthis->full_frame.number_of_stack_items = read_n_byte(fp ,U2);
        pthis->full_frame.stack = malloc(pthis->full_frame.number_of_stack_items * sizeof(VerificationTypeInfo));
        for (int i = 0; i < pthis->full_frame.number_of_stack_items; i++)
        {
            VerificationTypeInfo info = {0};
            init_verification_type_info(&info, fp);
            pthis->full_frame.stack[i] = info;
        }
    }
}

static void init_verification_type_info(VerificationTypeInfo* pthis, FILE* fp)
{
    pthis->tag = read_n_byte(fp, U1);
    switch (pthis->tag) {
        case 0:
            pthis->top_variable_info.tag = pthis->tag;
            break;
        case 1:
            pthis->integer_variable_info.tag = pthis->tag;
            break;
        case 2:
            pthis->float_variable_info.tag = pthis->tag;
            break;
        case 3:
            pthis->double_variable_info.tag = pthis->tag;
            break;
        case 4:
            pthis->long_variable_info.tag = pthis->tag;
            break;
        case 5:
            pthis->null_variable_info.tag = pthis->tag;
            break;
        case 6:
            pthis->uninitializedthis_variable_info.tag = pthis->tag;
            break;
        case 7:
            pthis->object_variable_info.tag = pthis->tag;
            pthis->object_variable_info.cpool_index = read_n_byte(fp, U2);
            break;
        case 8:
            pthis->uninitialized_variable_info.tag = pthis->tag;
            pthis->uninitialized_variable_info.offset = read_n_byte(fp, U2);
            break;
        default:
            break;
    }
}

static void print_verification_type_info(VerificationTypeInfo* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    switch (pthis->tag) {
        case 0:
            printf("top\n");
            break;
        case 1:
            printf("integer\n");
            break;
        case 2:
            printf("float\n");
            break;
        case 3:
            printf("double\n");
            break;
        case 4:
            printf("long\n");
            break;
        case 5:
            printf("null\n");
            break;
        case 6:
            printf("uninitializedThis\n");
            break;
        case 7:
            printf("object (#%d)\n", pthis->object_variable_info.cpool_index);
            break;
        case 8:
            printf("uninitialized(%d)\n", pthis->uninitialized_variable_info.offset);
            break;
        default:
            printf("unknown\n");
            break;
    }
}