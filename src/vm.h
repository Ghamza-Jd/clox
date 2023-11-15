#ifndef clox_vm_h
#define clox_vm_h

#include <glib.h>

#include "chunk.h"
#include "value.h"

typedef struct {
    Chunk* chunk;
    size_t ip;
    GQueue* stack;
} VM;

typedef enum { INTERPRET_OK, INTERPRET_COMPILE_ERROR, INTERPRET_RUNTIME_ERROR } InterpretResult;

void init_vm();
void free_vm();
InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

#endif
