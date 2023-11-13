#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassemble_chunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);
    for (int offset = 0; offset < chunk->code->len;) {
        offset = disassemble_instruction(chunk, offset);
    }
}

static int constant_instruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = g_array_index(chunk->code, uint8_t, offset + 1);
    printf("%-16s %4d '", name, constant);
    print_value(g_array_index(chunk->constants.values, Value, constant));
    printf("'\n");
    return offset + 2;
}

static int simple_instruction(const char* name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

int disassemble_instruction(Chunk* chunk, int offset) {
    printf("%04d ", offset);

    int current_line = g_array_index(chunk->lines, int, offset);

    if (offset > 0 && current_line == g_array_index(chunk->lines, int, offset - 1)) {
        printf("   | ");
    } else {
        printf("%4d ", current_line);
    }

    uint8_t instruction = g_array_index(chunk->code, uint8_t, offset);
    switch (instruction) {
    case OP_RETURN:
        return simple_instruction("OP_RETURN", offset);

    case OP_CONSTANT:
        return constant_instruction("OP_CONSTANT", chunk, offset);

    default:
        printf("Unknown opcode %d\n", instruction);
        return offset + 1;
    }
}
