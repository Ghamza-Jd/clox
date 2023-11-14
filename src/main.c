#include <glib.h>
#include <stdio.h>

#include "chunk.h"
#include "debug.h"
#include "vm.h"

static gchar* arg_path;

static GOptionEntry entries[] = {{"path", 'p', 0, G_OPTION_ARG_FILENAME, &arg_path, "Path to .clx file", NULL}, {NULL}};

static void repl();
static void run_file(const char* path);

int main(int argc, char** argv) {
    GError* error = NULL;
    GOptionContext* ctx;

    ctx = g_option_context_new("");
    g_option_context_add_main_entries(ctx, entries, NULL);

    gboolean did_succeed = g_option_context_parse(ctx, &argc, &argv, &error);

    if (!did_succeed) {
        g_printerr("Failed to parse args\n");
        exit(1);
    }

    init_vm();

    if (arg_path != NULL) {
        run_file(arg_path);
    } else {
        repl();
    }

    free_vm();
    return 0;
}

static void repl() {
    char line[1024];
    for (;;) {
        g_print("> ");

        if (!fgets(line, sizeof(line), stdin)) {
            g_print("\n");
            break;
        }

        // interpret(line);
    }
}

static void run_file(const char* path) {
    GError* err = NULL;
    char* source_code;
    gsize length;
    gboolean did_succeed = g_file_get_contents(path, &source_code, &length, &err);

    if (did_succeed) {
        // InterpretResult result = interpret(source_code);
        // free(source_code);

        // if (result == INTERPRET_COMPILE_ERROR) exit(65);
        // if (result == INTERPRET_RUNTIME_ERROR) exit(70);
    } else {
        /* handle error with `err` */
    }

    g_free(source_code);
}
