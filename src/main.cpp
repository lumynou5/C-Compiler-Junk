#include <iostream>
#include <fmt/format.h>
#include "token.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Couldn't recognize the arguments." << std::endl;
        return EXIT_FAILURE;
    }

    // Tokenize.
    char* ptr = argv[1];
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

        fmt::print(stderr, "Unexpected character `{}` found.", *ptr);
        return EXIT_FAILURE;
    }
    newToken(TokenKind::Eof, curr, ptr);
    curr = head.next;

    // Generate.
    try {
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

            throw std::invalid_argument(
                    fmt::format("Expected operator but found {}.", getTokenKindName(curr->kind))
            );
        }
        fmt::print("    ret\n");
    } catch (std::exception& e) {
        fmt::print(stderr, e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
