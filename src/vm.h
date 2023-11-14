#ifndef clox_vm_h
#define clox_vm_h

#include <glib.h>

#include "chunk.h"

typedef struct {
    Chunk* chunk;
    size_t ip;
} VM;

typedef enum { INTERPRET_OK, INTERPRET_COMPILE_ERROR, INTERPRET_RUNTIME_ERROR } InterpretResult;

void init_vm();
void free_vm();
InterpretResult interpret(Chunk* chunk);

#endif
