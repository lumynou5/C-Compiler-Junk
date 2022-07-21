#include "tokenizer.h"

#include "error.h"

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
        } else if (!(strncmp(ptr, "==", 2) && strncmp(ptr, "!=", 2) && strncmp(ptr, "<=", 2) && strncmp(ptr, ">=", 2))) {
            curr = newToken(TokenKind::Op, curr, line, ptr, 2);
            ptr += 2;
        } else if (*ptr == '+' || *ptr == '-' || *ptr == '*' || *ptr == '/' || *ptr == '(' || *ptr == ')' ||
                   *ptr == '<' || *ptr == '>') {
            curr = newToken(TokenKind::Op, curr, line, ptr++, 1);
        } else if (std::isdigit(*ptr)) {
            curr = newToken(TokenKind::Num, curr, line, ptr, 0);
            curr->val = strtol(ptr, &ptr, 10);
        } else {
            compilationError(line, ptr, "Unexpected character.");
        }
    }
    newToken(TokenKind::Eof, curr, line, ptr, 0);
    return head.next;
}

bool consume(Token*& token, const char* op) {
    if (token->kind != TokenKind::Op ||
        token->len != strlen(op) ||
        strncmp(token->str, op, token->len) != 0) {
        return false;
    }
    token = token->next;
    return true;
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
