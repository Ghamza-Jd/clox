#include <glib.h>
#include <stdio.h>

#include "debug.h"
#include "value.h"

void disassemble_chunk(Chunk* chunk, const char* name) {
    g_print("== %s ==\n", name);
    for (int offset = 0; offset < chunk->code->len;) {
        offset = disassemble_instruction(chunk, offset);
    }
}

static int constant_instruction(const char* name, Chunk* chunk, int offset) {
    uint8_t constant = g_array_index(chunk->code, uint8_t, offset + 1);
    g_print("%-16s %4d '", name, constant);
    print_value(g_array_index(chunk->constants.values, Value, constant));
    g_print("'\n");
    return offset + 2;
}

static int simple_instruction(const char* name, int offset) {
    g_print("%s\n", name);
    return offset + 1;
}

int disassemble_instruction(Chunk* chunk, int offset) {
    g_print("%04d ", offset);

    int current_line = g_array_index(chunk->lines, int, offset);

    if (offset > 0 && current_line == g_array_index(chunk->lines, int, offset - 1)) {
        g_print("   | ");
    } else {
        g_print("%4d ", current_line);
    }

    uint8_t instruction = g_array_index(chunk->code, uint8_t, offset);
    switch (instruction) {
    case OP_CONSTANT:
        return constant_instruction("OP_CONSTANT", chunk, offset);

    case OP_ADD:
        return simple_instruction("OP_ADD", offset);

    case OP_SUBTRACT:
        return simple_instruction("OP_SUBTRACT", offset);

    case OP_MULTIPLY:
        return simple_instruction("OP_MULTIPLY", offset);

    case OP_DIVIDE:
        return simple_instruction("OP_DIVIDE", offset);

    case OP_NEGATE:
        return simple_instruction("OP_NEGATE", offset);

    case OP_RETURN:
        return simple_instruction("OP_RETURN", offset);

    default:
        g_print("Unknown opcode %d\n", instruction);
        return offset + 1;
    }
}
