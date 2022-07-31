#include "tokenizer.h"

#include "error.hpp"

Token* tokenize(char* source) {
    char* line = source;
    char* ptr = source;
    Token head;
    Token* curr = &head;
    while (*ptr) {
        if (*ptr == '\n') {
            line = ptr;
        }

        if (std::isspace(*ptr)) {
            // Ignore if it's space.
            ++ptr;
        } else if (std::isdigit(*ptr)) {
            // If the first character is a digit, it's a number.
            curr = newToken(TokenKind::Num, curr, line, ptr, 0);
            curr->val = std::strtol(ptr, &ptr, 10);
        } else if (!std::strncmp(ptr, "==", 2) || !std::strncmp(ptr, "!=", 2) ||
                   !std::strncmp(ptr, "<=", 2) || !std::strncmp(ptr, ">=", 2)) {
            curr = newToken(TokenKind::Res, curr, line, ptr, 2);
            ptr += 2;
        } else if (std::strchr("+-*/%<>()=;", *ptr)) {
            curr = newToken(TokenKind::Res, curr, line, ptr++, 1);
        } else if (std::isalpha(*ptr) || *ptr == '_') {
            char* last = ptr;
            for (; std::isalnum(*last) || *last == '_'; ++last);
            curr = newToken(TokenKind::Id, curr, line, ptr, static_cast<std::size_t>(last - ptr));
            ptr = last;
        } else {
            compilationError(line, ptr, "Unexpected character.");
        }
    }
    newToken(TokenKind::Eof, curr, line, ptr, 0);
    return head.next;
}

bool consume(Token*& token, const char* op) {
    if (token->kind != TokenKind::Res ||
        token->len != std::strlen(op) ||
        std::strncmp(token->str, op, token->len)) {
        return false;
    }

    token = token->next;
    return true;
}

std::string consumeId(Token*& token) {
    if (token->kind != TokenKind::Id) {
        return {};
    }
    std::string id(token->str, token->len);

    token = token->next;
    return id;
}

long expectNumber(Token*& token) {
    if (token->kind != TokenKind::Num) {
        compilationError(token->line, token->str, "Expected a number.");
    }
    long val = token->val;

    token = token->next;
    return val;
}

Token* newToken(TokenKind kind, Token* parent, char* line, char* str, std::size_t len) {
    auto* token = new Token;
    token->kind = kind;
    token->line = line;
    token->str = str;
    token->len = len;
    token->next = nullptr;

    parent->next = token;
    return token;
}
