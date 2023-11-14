#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

VM vm;

void init_vm() { vm.stack = g_queue_new(); }

void free_vm() { g_queue_free(vm.stack); }

static uint8_t read_byte() {
    uint8_t byte = g_array_index(vm.chunk->code, uint8_t, vm.ip);
    vm.ip++;
    return byte;
}

static Value read_constant() {
    uint8_t byte = read_byte();
    Value constant = g_array_index(vm.chunk->constants.values, Value, byte);
    return constant;
}

static void binary_op(BinaryOp op) {
    Value rhs = pop();
    Value lhs = pop();
    switch (op) {
    case ADD:
        push(lhs + rhs);
        break;

    case SUBTRACT:
        push(lhs - rhs);
        break;

    case MULTIPLY:
        push(lhs * rhs);
        break;

    case DIVIDE:
        push(lhs / rhs);
        break;
    }
}

static InterpretResult run() {
    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        disassemble_instruction(vm.chunk, vm.ip);
        g_print(" ");
        for (int i = 0; i < vm.stack->length; i++) {
            Value* slot = g_queue_peek_nth(vm.stack, i);
            g_print("[ ");
            print_value(*slot);
            g_print(" ]");
        }
        g_print("\n");
#endif
        uint8_t instruction;
        switch (instruction = read_byte()) {
        case OP_CONSTANT: {
            Value constant = read_constant();
            push(constant);
            break;
        }

        case OP_ADD: {
            binary_op(ADD);
            break;
        }

        case OP_SUBTRACT: {
            binary_op(SUBTRACT);
            break;
        }

        case OP_MULTIPLY: {
            binary_op(MULTIPLY);
            break;
        }

        case OP_DIVIDE: {
            binary_op(DIVIDE);
            break;
        }

        case OP_NEGATE: {
            push(-pop());
            break;
        }

        case OP_RETURN: {
            print_value(pop());
            g_print("\n");
            return INTERPRET_OK;
        }
        }
    }
}

InterpretResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.ip = 0;
    return run();
}

void push(Value value) {
    Value* val = g_new(Value, 1); /* Allocate mem for 1 'Value' */
    *val = value;
    g_queue_push_head(vm.stack, val);
}

Value pop() {
    Value* val = g_queue_pop_head(vm.stack);
    return *val;
}
