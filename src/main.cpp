#include <iostream>
#include <fmt/format.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Couldn't recognize the arguments." << std::endl;
        return EXIT_FAILURE;
    }

    char* ptr = argv[1];

    fmt::print(".intel_syntax noprefix\n");
    fmt::print(".globl main\n");
    fmt::print("main:\n");
    fmt::print("    mov rax, {}\n", strtol(ptr, &ptr, 10));

    while (*ptr) {
        if (*ptr == '+') {
            ++ptr;
            fmt::print("    add rax, {}\n", strtol(ptr, &ptr, 10));
            continue;
        }
        if (*ptr == '-') {
            ++ptr;
            fmt::print("    sub rax, {}\n", strtol(ptr, &ptr, 10));
            continue;
        }

        fmt::print(stderr, "Unexpected character `{}` found.", *ptr);
        return EXIT_FAILURE;
    }

    fmt::print("    ret\n");

    return EXIT_SUCCESS;
}
