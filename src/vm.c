#include "vm.h"
#include "common.h"

VM vm;

void init_vm() {}

void free_vm() {}

static uint8_t read_byte() {
    uint8_t byte = g_array_index(vm.chunk->code, uint8_t, vm.ip);
    vm.ip++;
    return byte;
}

static InterpretResult run() {
    for (;;) {
        uint8_t instruction;
        switch (instruction = read_byte()) {
        case OP_RETURN:
            return INTERPRET_OK;
        }
    }
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = 0;
    return run();
}
