#include "token.h"

#include <stdexcept>
#include <fmt/format.h>

bool consume(Token*& token, char op) {
    if (token->kind != TokenKind::Op || token->str[0] != op) {
        return false;
    }
    token = token->next;
    return true;
}

void expect(Token*& token, char op) {
    if (!consume(token, op)) {
        throw std::invalid_argument(fmt::format("Expected `{}` but found `{}`.", op, token->str));
    }
}

long expectNumber(Token*& token) {
    if (token->kind != TokenKind::Num) {
        throw std::invalid_argument(
                fmt::format("Expected a number but found {}.", getTokenKindName(token->kind))
        );
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
