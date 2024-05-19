//
// Created by Administrator on 2024/5/5 0005.
//
#include "AttrCode.h"

#define STACK_MAP_TABLE                     "StackMapTable"
#define LINE_NUMBER_TABLE                   "LineNumberTable"
#define LOCAL_VARIABLE_TABLE                "LocalVariableTable"
#define LOCAL_VARIABLE_TYPE_TABLE           "LocalVariableTypeTable"
#define STACK_MAP_TABLE_INDEX               0
#define LINE_NUMBER_TABLE_INDEX             1
#define LOCAL_VARIABLE_TABLE_INDEX          2
#define LOCAL_VARIABLE_TYPE_TABLE_INDEX     3

#define INS_MAX_LEN     16
#define INS_COUNT       205

static void init_exception_item(ExceptionItem*, FILE*);
static void save_code_attr(CodeAttr*, ConstantItem*, FILE*, ConstantItem*, unsigned int);

/**
 * jvm指令
 */
static const char* jvm_instruction[INS_MAX_LEN][INS_COUNT] = {
        "nop",             "aconst_null",   "iconst_m1",      "iconst_0",      "iconst_1",
        "iconst_2",        "iconst_3",      "iconst_3",       "iconst_4",      "iconst_5",
        "lconst_0",        "fconst_0",      "fconst_1",       "fconst_2",      "dconst_0",
        "dconst_1",        "bipush",        "sipush",         "ldc",           "ldc_w",
        "ldc2_w",          "iload",         "lload",          "fload",         "dload",
        "aload",           "iload_0",       "iload_1",        "iload_2",       "iload_3",
        "lload_0",         "lload_1",       "lload_2",        "lload_3",       "fload_0",
        "fload_1",         "fload_2",       "fload_3",        "dload_0",       "dload_1",
        "dload_2",         "dload_3",       "aload_0",        "aload_1",       "aload_2",
        "aload_3",         "iaload",        "laload",         "faload",        "daload",
        "aaload",          "baload",        "caload",         "saload",        "istore",
        "lstore",          "fstore",        "dstore",         "astore",        "istore_0",
        "istore_1",        "istore_2",      "istore_3",       "lstore_0",      "lstore_1",
        "lstore_2",        "lstore_3",      "fstore_0",       "fstore_1",      "fstore_2",
        "fstore_3",        "dstore_0",      "dstore_1",       "dstore_2",      "dstore_3",
        "astore_0",        "astore_1",      "astore_2",       "astore_3",      "iastore",
        "lastore",         "fastore",       "dastore",        "aastore",       "bastore",
        "castore",         "sastore",       "pop",            "pop2",          "dup",
        "dup_x1",          "dup_x2",        "dup2",           "dup2_x1",       "dup2_x2",
        "swap",            "iadd",          "ladd",           "fadd",          "dadd",
        "isub",            "lsub",          "fsub",           "dsub",          "imul",
        "lmul",            "fmul",          "dmul",           "idiv",          "ldiv",
        "fdiv",            "ddiv",          "irem",           "lrem",          "frem",
        "drem",            "ineg",          "lneg",           "fneg",          "dneg",
        "ishl",            "lshl",          "ishr",           "lshr",          "iushr",
        "lushr",           "iand",          "land",           "ior",           "lor",
        "ixor",            "lxor",          "iinc",           "i2l",           "i2f",
        "i2d",             "l2i",           "l2f",            "l2d",           "f2i",
        "f2l",             "f2d",           "d2i",            "d2i",           "d2f",
        "i2b",             "i2c",           "i2s",            "lcmp",          "fcmpl",
        "fcmpg",           "dcmpl",         "dcmpg",          "ifeq",          "ifne",
        "iflt",            "ifge",          "ifgt",           "ifle",          "if_icmpeq",
        "if_icmpne",       "if_icmplt",     "if_icmpge",      "if_icmpgt",     "if_icmple",
        "if_acmpeq",       "if_acmpne",     "goto",           "jsr",           "ret",
        "tableswitch",     "lookupswitch",  "ireturn",        "lreturn",       "freturn",
        "dreturn",         "areturn",       "return",         "getstatic",     "putstatic",
        "getfield",        "putfield",      "invokevirtual",  "invokespecial", "invokestatic",
        "invokeinterface", "invokedynamic", "new",            "newarray",      "anewarray",
        "arraylength",     "athrow",        "checkcast",      "instanceof",    "monitorenter",
        "monitorexit",     "wide",          "multianewarray", "ifnull",        "ifnonnull",
        "goto_w",          "jsr_w",         "breakpoint",     "impdep1",       "impdep2"
};

static const int instruction_param[INS_COUNT] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
};

void init_code_attr(CodeAttr* pthis, ConstantItem* pconst_item, FILE* fp,
                    ConstantItem* p_pool, unsigned int pool_count)
{
    pthis->attribute_name_index = pconst_item->index;
    pthis->attribute_length = read_n_byte(fp, U4);
    pthis->max_stack = read_n_byte(fp, U2);
    pthis->max_locals = read_n_byte(fp, U2);
    pthis->code_length = read_n_byte(fp, U4);
    pthis->code = malloc(pthis->code_length * sizeof(unsigned int));
    for (int i = 0; i < pthis->code_length; i++)
    {
        pthis->code[i] = read_n_byte(fp, U1);
    }
    pthis->exception_table_length = read_n_byte(fp, U2);
    pthis->exception_item = malloc(pthis->exception_table_length * sizeof(ExceptionItem));
    for (int i = 0; i < pthis->exception_table_length; i++)
    {
        init_exception_item(&pthis->exception_item[i], fp);
    }
    for (int i = 0; i < CODE_ATTR_COUNT; i++)
    {
        pthis->attributes[i] = NULL;
    }
    pthis->attributes_count = read_n_byte(fp, U2);
    for (int i = 0; i < pthis->attributes_count; i++)
    {
        save_code_attr(pthis, pconst_item, fp, p_pool, pool_count);
    }
}

/**
 * 保存CodeAttr中的属性
 */
static void save_code_attr(CodeAttr* pthis, ConstantItem* pconst_item, FILE* fp,
                           ConstantItem* p_pool, unsigned int pool_count)
{
    unsigned int index = read_n_byte(fp, U2);
    ConstantItem item = get_constant_item_by_index(p_pool, pool_count, index);
    if (strcmp(item.value, STACK_MAP_TABLE) == 0)
    {

    }
    else if (strcmp(item.value, LINE_NUMBER_TABLE) == 0)
    {
        LineNumberTableAttr* p_table = malloc(sizeof(LineNumberTableAttr));
        init_line_number_table_attr(p_table, &item, fp);
        pthis->attributes[LINE_NUMBER_TABLE_INDEX] = p_table;
    }
    else if (strcmp(item.value, LOCAL_VARIABLE_TABLE) == 0)
    {
        LocalVariableTableAttr* p_table = malloc(sizeof(LocalVariableTableAttr));
        init_local_variable_table_attr(p_table, &item, fp);
        pthis->attributes[LOCAL_VARIABLE_TABLE_INDEX] = p_table;
    }
    else if (strcmp(item.value, LOCAL_VARIABLE_TYPE_TABLE) == 0)
    {
        LocalVariableTableAttr* p_table = malloc(sizeof(LocalVariableTableAttr));
        init_local_variable_table_attr(p_table, pconst_item, fp);
        pthis->attributes[LOCAL_VARIABLE_TYPE_TABLE_INDEX] = p_table;
    }

}

void print_code_attr(CodeAttr* pthis, ConstantItem* p_pool, unsigned int pool_count)
{
    ConstantItem item = get_constant_item_by_index(p_pool, pool_count, pthis->attribute_name_index);
    printf(" %s:\n", item.value);
    printf("   stack=%d, locals=%d, args_size=%d\n", pthis->max_stack, pthis->max_locals, pthis->max_locals);
    if (pthis->attributes[STACK_MAP_TABLE_INDEX] != NULL)
    {

    }
    if (pthis->attributes[LINE_NUMBER_TABLE_INDEX] != NULL)
    {
        print_line_number_table(pthis->attributes[LINE_NUMBER_TABLE_INDEX]);
    }
    if (pthis->attributes[LOCAL_VARIABLE_TABLE_INDEX] != NULL)
    {
        print_local_variable_table_attr(pthis->attributes[LOCAL_VARIABLE_TABLE_INDEX], p_pool, pool_count);
    }
    if (pthis->attributes[LOCAL_VARIABLE_TYPE_TABLE_INDEX] != NULL)
    {
        print_local_variable_type_table_attr(pthis->attributes[LOCAL_VARIABLE_TYPE_TABLE_INDEX], p_pool, pool_count);
    }
}

static void init_exception_item(ExceptionItem* pthis, FILE* fp)
{
    pthis->start_pc = read_n_byte(fp, U2);
    pthis->end_pc = read_n_byte(fp, U2);
    pthis->handler_pc = read_n_byte(fp, U2);
    pthis->catch_type = read_n_byte(fp, U2);
}
