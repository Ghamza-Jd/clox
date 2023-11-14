#include "chunk.h"

void init_chunk(Chunk* chunk) {
    chunk->code = g_array_new(FALSE, FALSE, sizeof(uint8_t));
    chunk->lines = g_array_new(FALSE, FALSE, sizeof(int));
    init_value_array(&chunk->constants);
}

void write_chunk(Chunk* chunk, uint8_t byte, int line) {
    g_array_append_val(chunk->code, byte);
    g_array_append_val(chunk->lines, line);
}

int add_constant(Chunk* chunk, Value value) {
    write_value_array(&chunk->constants, value);
    return chunk->constants.values->len - 1;
}

void free_chunk(Chunk* chunk) {
    g_array_unref(chunk->code);
    g_array_unref(chunk->lines);
    free_value_array(&chunk->constants);
    init_chunk(chunk);
}
