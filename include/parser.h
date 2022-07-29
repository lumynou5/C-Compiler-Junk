#ifndef C_COMPILER_PARSER_H
#define C_COMPILER_PARSER_H

#include "ast/binary_op_node.h"
#include "ast/primary_node.h"
#include "ast/state_node.h"
#include "tokenizer.h"

/// \brief Parse tokens to get the syntax tree.
///
/// \param token The beginning of the token sequence.
/// \return The root of the syntax tree.
Node* parse(Token* token);

/// \brief Parse tokens to get the syntax tree of a statement sequence.
///
/// EBNF: normal_state = (expr ";")*
///
/// \param token The beginning of a statement sequence.
/// \return The root of the syntax tree.
StateNode* normal_state(Token*& token);

/// \brief Parse tokens to get the syntax tree of an expression.
///
/// \param token The beginning of an expression.
///
/// \return The root of the syntax tree.
ExprNode* expr(Token*& token);

/// \brief Parse tokens to get the syntax tree of an assignment subexpression.
///
/// EBNF: assign = var "=" eq
///
/// \param token The beginning of a subexpression.
/// \return The root of the syntax tree.
ExprNode* assign(Token*& token);

/// \brief Parse tokens to get the syntax tree of an equality subexpression.
///
/// EBNF: eq = rel ("==" rel | "!=" rel)*
///
/// \param token The beginning of a subexpression.
/// \return The root of the syntax tree.
ExprNode* eq(Token*& token);

/// \brief Parse tokens to get the syntax tree of a relation subexpression.
///
/// EBNF: rel = add ("<" add | "<=" add | ">" add | ">=" add)*
///
/// \param token The beginning of a subexpression.
/// \return The root of the syntax tree.
ExprNode* rel(Token*& token);

/// \brief Parse tokens to get the syntax tree of an addition subexpression.
///
/// EBNF: add = mul ("+" mul | "-" mul)*
/// \param token The beginning of a subexpression.
///
/// \return The root of the syntax tree.
ExprNode* add(Token*& token);

/// \brief Parse tokens to get the syntax tree of a multiplication subexpression.
///
/// EBNF: mul = unary ("*" unary | "/" unary)*
///
/// \param token The beginning of a subexpression.
/// \return The root of the syntax tree.
ExprNode* mul(Token*& token);

/// \brief Parse tokens to get the syntax tree of a unary subexpression.
///
/// EBNF: unary = ("+" | "-")? primary
///
/// \param token The beginning of a subexpression.
/// \return The root of the syntax tree.
ExprNode* unary(Token*& token);

/// \brief Parse tokens to get the syntax tree of a primary subexpression.
///
/// EBNF: "(" expr ")" | var | num
///
/// \param token The beginning of a subexpression.
/// \return The root of the syntax tree.
ExprNode* primary(Token*& token);

#endif //C_COMPILER_PARSER_H
