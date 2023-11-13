#include "chunk.h"

void init_chunk(Chunk* chunk) { chunk->code = g_array_new(FALSE, FALSE, 2); }

void write_chunk(Chunk* chunk, uint8_t byte) {
    chunk->code = g_array_append_val(chunk->code, byte);
}

void free_chunk(Chunk* chunk) {
    g_array_free(chunk->code, TRUE);
    init_chunk(chunk);
}
