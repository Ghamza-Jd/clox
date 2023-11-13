#ifndef clox_chunk_h
#define clox_chunk_h

#include <glib.h>
#include "common.h"

typedef enum { OP_RETURN } OpCode;

typedef struct {
    GArray* code;
} Chunk;

void init_chunk(Chunk* chunk);
void write_chunk(Chunk* chunk, uint8_t byte);
void free_chunk(Chunk* chunk);

#endif
