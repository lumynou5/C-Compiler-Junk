#include "token.h"

extern char* source;

bool consume(Token*& token, char op) {
    if (token->kind != TokenKind::Op || token->str[0] != op) {
        return false;
    }
    token = token->next;
    return true;
}

long expectNumber(Token*& token) {
    if (token->kind != TokenKind::Num) {
        compilationError(source, token->str, "Expect a number.");
    }
    long val = token->val;
    token = token->next;
    return val;
}

Token* newToken(TokenKind kind, Token* parent, char* str) {
    auto* token = new Token;
    token->kind = kind;
    token->str = str;
    token->next = nullptr;
    parent->next = token;
    return token;
}
