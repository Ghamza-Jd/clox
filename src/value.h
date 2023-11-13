#ifndef clox_value_h
#define clox_value_h

#include <glib.h>

#include "common.h"

typedef double Value;

typedef struct {
    GArray* values;
} ValueArray;

void init_value_array(ValueArray* array);
void write_value_array(ValueArray* array, Value value);
void free_value_array(ValueArray* array);
void print_value(Value value);

#endif
