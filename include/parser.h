#ifndef C_COMPILER_PARSER_H
#define C_COMPILER_PARSER_H

#include "tokenizer.h"

enum class NodeKind {
    Add,
    Sub,
    Mul,
    Div,
    Num
};

struct Node {
    NodeKind kind;
    Node* lhs;
    Node* rhs;
    long val;
};

Node* newNode(NodeKind kind, Node* lhs, Node* rhs);

/// @brief Parse tokens to get the syntax tree.
/// @param token The beginning of the token sequence.
/// @return The root of the syntax tree.
Node* parse(Token* token);

/// @brief Parse tokens to get the syntax tree of an expression.
/// EBNF: expr = mul ("+" mul | "-" mul)*
/// @param token The beginning of an expression.
/// @return The root of the syntax tree.
Node* expr(Token*& token);

/// @brief Parse tokens to get the syntax tree of a multiplication subexpression.
/// EBNF: mul = primary ("*" primary | "/" primary)*
/// @param token The beginning of a subexpression.
/// @return The root of the syntax tree.
Node* mul(Token*& token);

/// @brief Parse tokens to get the syntax tree of a primary subexpression.
/// EBNF: "(" expr ")" | num
/// @param token The beginning of a subexpression.
/// @return The root of the syntax tree.
Node* primary(Token*& token);

#endif //C_COMPILER_PARSER_H
