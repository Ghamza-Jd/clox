#include <stdio.h>
#include <string.h>

#include "common.h"
#include "scanner.h"

typedef struct {
    const char* start;
    const char* current;
    int line;
} Scanner;

Scanner scanner;

GHashTable* keywords;

static void init_keywords() {
    keywords = g_hash_table_new(g_str_hash, g_str_equal);

#define INSERT_TOKEN(lexeme, token) g_hash_table_insert(keywords, lexeme, GINT_TO_POINTER(token))
    INSERT_TOKEN("and", TOKEN_AND);
    INSERT_TOKEN("class", TOKEN_CLASS);
    INSERT_TOKEN("else", TOKEN_ELSE);
    INSERT_TOKEN("if", TOKEN_IF);
    INSERT_TOKEN("nil", TOKEN_NIL);
    INSERT_TOKEN("or", TOKEN_OR);
    INSERT_TOKEN("print", TOKEN_PRINT);
    INSERT_TOKEN("return", TOKEN_RETURN);
    INSERT_TOKEN("super", TOKEN_SUPER);
    INSERT_TOKEN("let", TOKEN_VAR);
    INSERT_TOKEN("while", TOKEN_WHILE);
    INSERT_TOKEN("false", TOKEN_FALSE);
    INSERT_TOKEN("for", TOKEN_FOR);
    INSERT_TOKEN("fn", TOKEN_FUN);
    INSERT_TOKEN("this", TOKEN_THIS);
    INSERT_TOKEN("true", TOKEN_TRUE);
#undef INSERT_TOKEN
}

void init_scanner(const char* source) {
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
    init_keywords();
}

static bool is_at_end() { return *scanner.current == '\0'; }
static bool is_digit(char c) { return c >= '0' && c <= '9'; }
static bool is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'; }

static Token make_token(TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

static Token make_err_token(const char* msg) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = msg;
    token.length = (int)strlen(msg);
    token.line = scanner.line;
    return token;
}

static char advance() {
    scanner.current++;
    return scanner.current[-1];
}

static char peek() { return *scanner.current; }

static char peek_next() {
    if (is_at_end()) return '\0';
    return scanner.current[1];
}

static void skip_whitespace() {
    for (;;) {
        char c = peek();
        switch (c) {
        case ' ':
        case '\r':
        case '\t': advance(); break;
        case '\n':
            scanner.line++;
            advance();
            break;
        case '/':
            if (peek_next() == '/') {
                while (peek() != '\n' && !is_at_end()) advance();
            } else {
                return;
            }
            break;
        default: return;
        }
    }
}

static TokenType identifier_type() {
    while (is_alpha(peek())) advance();

    gchar* word = g_strndup(scanner.start, scanner.current - scanner.start);
    gboolean is_keyword = g_hash_table_contains(keywords, word);

    if (is_keyword) {
        gpointer ptr = g_hash_table_lookup(keywords, word);
        TokenType type = GPOINTER_TO_INT(ptr);
        return type;
    }

    return TOKEN_IDENTIFIER;
}

static Token make_string_token() {
    while (peek() != '"' && !is_at_end()) {
        if (peek() == '\n') scanner.line++;
        advance();
    }

    if (is_at_end()) return make_err_token("Unterminated string.");

    advance();
    return make_token(TOKEN_STRING);
}

static Token make_number_token() {
    while (is_digit(peek())) advance();

    if (peek() == '.' && is_digit(peek_next())) {
        advance();

        while (is_digit(peek())) advance();
    }

    return make_token(TOKEN_NUMBER);
}

static Token make_identifier_token() {
    while (is_alpha(peek()) || is_digit(peek())) advance();
    return make_token(identifier_type());
}

static bool match(char expected) {
    if (is_at_end()) return false;
    if (*scanner.current != expected) return false;
    scanner.current++;
    return true;
}

Token scan_token() {
    skip_whitespace();
    scanner.start = scanner.current;
    if (is_at_end()) return make_token(TOKEN_EOF);

    char c = advance();

    if (is_digit(c)) return make_number_token();
    if (is_alpha(c)) return make_identifier_token();

    switch (c) {
    case '(': return make_token(TOKEN_LEFT_PAREN);
    case ')': return make_token(TOKEN_RIGHT_PAREN);
    case '{': return make_token(TOKEN_LEFT_BRACE);
    case '}': return make_token(TOKEN_RIGHT_BRACE);
    case ';': return make_token(TOKEN_SEMICOLON);
    case ',': return make_token(TOKEN_COMMA);
    case '.': return make_token(TOKEN_DOT);
    case '-': return make_token(TOKEN_MINUS);
    case '+': return make_token(TOKEN_PLUS);
    case '/': return make_token(TOKEN_SLASH);
    case '*': return make_token(TOKEN_STAR);
    case '!': return make_token(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
    case '=': return make_token(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
    case '<': return make_token(match('=') ? TOKEN_LESS_EQUAL : TOKEN_EQUAL);
    case '>': return make_token(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_EQUAL);
    case '"': return make_string_token();
    }

    return make_err_token("Unexpected character.");
}
