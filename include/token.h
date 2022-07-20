#ifndef C_COMPILER_TOKEN_H
#define C_COMPILER_TOKEN_H

#include <stdexcept>
#include <fmt/format.h>

enum class TokenKind {
    Op,
    Num,
    Eof
};

struct Token {
    TokenKind kind;
    union {
        long val;
        char* str;
    };
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

inline const char* getTokenKindName(TokenKind kind) {
    switch (kind) {
        case TokenKind::Op:
            return "operator";
        case TokenKind::Num:
            return "number";
        case TokenKind::Eof:
            return "EOF";
        default:
            return "";
    }
}

bool consume(Token*& token, char op);

long expectNumber(Token*& token);

Token* newToken(TokenKind kind, Token* parent, char* str);

#endif //C_COMPILER_TOKEN_H
