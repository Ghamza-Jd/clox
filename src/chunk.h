#ifndef clox_chunk_h
#define clox_chunk_h

#include <glib.h>

#include "common.h"
#include "value.h"

typedef enum { OP_CONSTANT, OP_NEGATE, OP_RETURN } OpCode;

typedef struct {
    GArray* code;
    GArray* lines;
    ValueArray constants;
} Chunk;

void init_chunk(Chunk* chunk);
void write_chunk(Chunk* chunk, uint8_t byte, int line);
int add_constant(Chunk* chunk, Value value);
void free_chunk(Chunk* chunk);

#endif
