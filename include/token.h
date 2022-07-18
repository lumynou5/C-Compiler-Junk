#ifndef C_COMPILER_TOKEN_H
#define C_COMPILER_TOKEN_H

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

inline const char* getTokenKindName(TokenKind kind) {
    switch (kind) {
        case TokenKind::Op:
            return "operator";
        case TokenKind::Num:
            return "number";
        case TokenKind::Eof:
            return "EOF";
    }
}

bool consume(Token*& token, char op);

void expect(Token*& token, char op);

long expectNumber(Token*& token);

Token* newToken(TokenKind kind, Token* parent, char* str);

#endif //C_COMPILER_TOKEN_H
