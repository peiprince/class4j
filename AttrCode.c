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

#define INS_COUNT       205

static void init_exception_item(ExceptionItem*, FILE*);
static void save_code_attr(CodeAttr*, ConstantItem*, FILE*, ConstantItem*, unsigned int);

/**
 * jvm指令
 */
static const char* jvm_instruction[INS_COUNT] = {
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
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,     // 0-9: nop~iconst_5
        0, 0, 0, 0, 0, 0, 1, 2, 1, 2,      // 10-19: lconst_0~ldc_w
        2, 1, 1, 1, 1, 1, 0, 0, 0, 0,      // 20-29: ldc2_w~iload
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,      // 30-39: lload~iload_3
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,      // 40-49: lload_0~aaload
        0, 0, 0, 1, 1, 1, 1, 1, 0, 0,      // 50-59: baload~istore
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,      // 60-69: lstore~istore_3
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,      // 70-79: lstore_0~fstore_3
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,      // 80-89: dstore_0~iastore
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,      // 90-99: lastore~sastore
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,      // 100-109: pop~dup2_x2
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,      // 110-119: swap~ddiv
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,      // 120-129: irem~dneg
        0, 0, 0, 0, 0, 0, 2, 0, 0, 0,      // 130-139: ishl~i2d
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,      // 140-149: l2i~dcmpg
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,      // 150-159: ifeq~if_icmple
        2, 2, 2, 2, 1, -1, -1, 0, 0, 0,    // 160-169: if_acmpeq~return
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,      // 170-179: getstatic~anewarray
        0, 0, 2, 2, 1, 4, 2, 3, 2, 2,      // 180-189: arraylength~ifnonnull
        4, 4, 0, 0, 0                       // 190-194: goto_w~breakpoint
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
        StackMapTableAttr* p_table = malloc(sizeof(StackMapTableAttr));
        init_stack_map_table_attr(p_table, &item, fp);
        pthis->attributes[STACK_MAP_TABLE_INDEX] = p_table;
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
    if (pthis->exception_table_length > 0)
    {
        printf("   Exception table:\n");
        printf("      from    to  target type\n");
        for (int i = 0; i < pthis->exception_table_length; i++)
        {
            ExceptionItem ei = pthis->exception_item[i];
            if (ei.catch_type == 0)
            {
                printf("       %4d  %4d  %4d   any\n", ei.start_pc, ei.end_pc, ei.handler_pc);
            }
            else
            {
                char* catch_class = get_utf8_constant_value(p_pool, pool_count, ei.catch_type);
                char dest[256] = {0};
                printf("       %4d  %4d  %4d   Class %s\n", ei.start_pc, ei.end_pc, ei.handler_pc,
                       str_slash2dot(dest, catch_class, 0, 0));
            }
        }
    }
    printf("   Code:\n");
    int pc = 0;
    while (pc < pthis->code_length)
    {
        int opcode = pthis->code[pc];
        if (opcode >= INS_COUNT)
        {
            printf("     %d: unknown opcode(%d)\n", pc, opcode);
            pc++;
            continue;
        }
        int param_bytes = instruction_param[opcode];
        if (param_bytes == -1)
        {
            // tableswitch / lookupswitch，需要特殊处理
            int padding = (4 - ((pc + 1) % 4)) % 4;
            int base = pc + 1 + padding;
            if (opcode == 170) // tableswitch
            {
                int default_offset = (pthis->code[base] << 24) | (pthis->code[base+1] << 16) |
                                     (pthis->code[base+2] << 8) | pthis->code[base+3];
                int low = (pthis->code[base+4] << 24) | (pthis->code[base+5] << 16) |
                          (pthis->code[base+6] << 8) | pthis->code[base+7];
                int high = (pthis->code[base+8] << 24) | (pthis->code[base+9] << 16) |
                           (pthis->code[base+10] << 8) | pthis->code[base+11];
                printf("     %d: tableswitch   { %d to %d }\n", pc, low, high);
                pc = base + 12 + (high - low + 1) * 4;
            }
            else // lookupswitch (171)
            {
                int default_offset = (pthis->code[base] << 24) | (pthis->code[base+1] << 16) |
                                     (pthis->code[base+2] << 8) | pthis->code[base+3];
                int npairs = (pthis->code[base+4] << 24) | (pthis->code[base+5] << 16) |
                             (pthis->code[base+6] << 8) | pthis->code[base+7];
                printf("     %d: lookupswitch   { %d pairs }\n", pc, npairs);
                pc = base + 8 + npairs * 8;
            }
            continue;
        }
        printf("     %d: %s", pc, jvm_instruction[opcode]);
        if (param_bytes == 1)
        {
            printf("  #%d", pthis->code[pc + 1]);
        }
        else if (param_bytes == 2)
        {
            int operand = (pthis->code[pc + 1] << 8) | pthis->code[pc + 2];
            if (opcode >= 178 && opcode <= 185)
            {
                char* ref = get_utf8_constant_value(p_pool, pool_count, operand);
                printf("  // %s", ref);
            }
            else if (opcode >= 150 && opcode <= 167)
            {
                int offset = (short) operand;
                printf("  %d", pc + offset);
            }
            else
            {
                printf("  #%d", operand);
            }
        }
        else if (param_bytes == 3)
        {
            int operand = (pthis->code[pc + 1] << 16) | (pthis->code[pc + 2] << 8) | pthis->code[pc + 3];
            printf("  #%d", operand);
        }
        else if (param_bytes == 4)
        {
            int operand = (pthis->code[pc + 1] << 24) | (pthis->code[pc + 2] << 16) |
                          (pthis->code[pc + 3] << 8) | pthis->code[pc + 4];
            printf("  #%d", operand);
        }
        printf("\n");
        pc += 1 + param_bytes;
    }
    if (pthis->attributes[STACK_MAP_TABLE_INDEX] != NULL)
    {
        print_stack_map_table_attr(pthis->attributes[STACK_MAP_TABLE_INDEX], p_pool, pool_count);
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
