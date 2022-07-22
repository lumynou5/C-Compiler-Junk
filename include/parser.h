#ifndef C_COMPILER_PARSER_H
#define C_COMPILER_PARSER_H

#include "tokenizer.h"

enum class NodeKind {
    // Equality.
    Eq,
    NotEq,
    // Relation.
    Less,
    LessEq,
    // Addition.
    Add,
    Sub,
    // Multiplication.
    Mul,
    Div,
    // Primary.
    Num
};

struct Node {
    NodeKind kind;
    Node* lhs;
    Node* rhs;
    long val;
};

Node* newNode(NodeKind kind, Node* lhs, Node* rhs);

Node* newNumNode(long val);

/// @brief Parse tokens to get the syntax tree.
/// @param token The beginning of the token sequence.
/// @return The root of the syntax tree.
Node* parse(Token* token);

/// @brief Parse tokens to get the syntax tree of an expression.
/// @param token The beginning of an expression.
/// @return The root of the syntax tree.
Node* expr(Token*& token);

/// @brief Parse tokens to get the syntax tree of an equality subexpression.
/// EBNF: eq = rel ("==" rel | "!=" rel)*
/// @param token The beginning of a subexpression.
/// @return The root of the syntax tree.
Node* eq(Token*& token);

/// @brief Parse tokens to get the syntax tree of a relation subexpression.
/// EBNF: rel = add ("<" add | "<=" add | ">" add | ">=" add)*
/// @param token The beginning of a subexpression.
/// @return The root of the syntax tree.
Node* rel(Token*& token);

/// @brief Parse tokens to get the syntax tree of an addition subexpression.
/// EBNF: add = mul ("+" mul | "-" mul)*
/// @param token The beginning of a subexpression.
/// @return The root of the syntax tree.
Node* add(Token*& token);

/// @brief Parse tokens to get the syntax tree of a multiplication subexpression.
/// EBNF: mul = unary ("*" unary | "/" unary)*
/// @param token The beginning of a subexpression.
/// @return The root of the syntax tree.
Node* mul(Token*& token);

/// @brief Parse tokens to get the syntax tree of a unary subexpression.
/// EBNF: unary = ("+" | "-")? primary
/// @param token The beginning of a subexpression.
/// @return The root of the syntax tree.
Node* unary(Token*& token);

/// @brief Parse tokens to get the syntax tree of a primary subexpression.
/// EBNF: "(" add ")" | num
/// @param token The beginning of a subexpression.
/// @return The root of the syntax tree.
Node* primary(Token*& token);

#endif //C_COMPILER_PARSER_H
