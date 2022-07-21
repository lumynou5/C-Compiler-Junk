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
    std::size_t len;
    Token* next;
};

Token* tokenize(char* source);

bool consume(Token*& token, const char* op);

long expectNumber(Token*& token);

Token* newToken(TokenKind kind, Token* parent, char* line, char* str, std::size_t len);

#endif //C_COMPILER_TOKENIZER_H
