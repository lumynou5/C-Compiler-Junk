#ifndef C_COMPILER_TOKENIZER_H
#define C_COMPILER_TOKENIZER_H

#include <stdexcept>
#include <fmt/format.h>

enum class TokenKind {
    Op,
    Num,
    Eof
};

struct Token {
    TokenKind kind;
    long val;
    char* line;
    char* str;
    Token* next;
};

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

Token* tokenize(char* source);

bool consume(Token*& token, char op);

long expectNumber(Token*& token);

Token* newToken(TokenKind kind, Token* parent, char* line, char* str);

#endif //C_COMPILER_TOKENIZER_H
