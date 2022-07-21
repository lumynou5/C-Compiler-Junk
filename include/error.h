#ifndef C_COMPILER_ERROR_H
#define C_COMPILER_ERROR_H

#include <cstdio>
#include <fmt/format.h>

template<class ...Args>
void compilationError(char* line, char* col, const char* fmt, const Args& ...args) {
    fmt::print(stderr,
               " |\n | {}\n | {: >{}}^ {}\n |\n",
               line,                                     // Source code.
               "", static_cast<std::size_t>(col - line), // Spaces.
               fmt::format(fmt, args...)                 // Error message.
    );
    std::exit(EXIT_FAILURE);
}

#endif //C_COMPILER_ERROR_H
