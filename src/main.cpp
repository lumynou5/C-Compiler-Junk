#include <iostream>
#include <fmt/format.h>
#include "token.h"

char* source;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Couldn't recognize the arguments.";
        return EXIT_FAILURE;
    }

    source = argv[1];

    // Tokenize.
    char* ptr = source;
    Token head;
    Token* curr = &head;
    while (*ptr) {
        if (std::isspace(*ptr)) {
            ++ptr;
            continue;
        }

        if (*ptr == '+' || *ptr == '-') {
            curr = newToken(TokenKind::Op, curr, ptr++);
            continue;
        }

        if (std::isdigit(*ptr)) {
            curr = newToken(TokenKind::Num, curr, ptr);
            curr->val = strtol(ptr, &ptr, 10);
            continue;
        }

        compilationError(source, ptr, "Unexpected character.");
    }
    newToken(TokenKind::Eof, curr, ptr);
    curr = head.next;

    // Generate.
    fmt::print(".intel_syntax noprefix\n");
    fmt::print(".globl main\n");
    fmt::print("main:\n");
    fmt::print("    mov rax, {}\n", expectNumber(curr));
    while (curr->kind != TokenKind::Eof) {
        if (consume(curr, '+')) {
            fmt::print("    add rax, {}\n", expectNumber(curr));
            continue;
        }
        if (consume(curr, '-')) {
            fmt::print("    sub rax, {}\n", expectNumber(curr));
            continue;
        }

        compilationError(source, ptr, "");
    }
    fmt::print("    ret\n");

    return EXIT_SUCCESS;
}
