#include <glib.h>
#include <stdio.h>

#include "value.h"

void init_value_array(ValueArray* array) { array->values = g_array_new(FALSE, FALSE, sizeof(Value)); }

void write_value_array(ValueArray* array, Value value) { g_array_append_val(array->values, value); }

void free_value_array(ValueArray* array) {
    g_array_unref(array->values);
    init_value_array(array);
}

void print_value(Value value) { g_print("%g", value); }
