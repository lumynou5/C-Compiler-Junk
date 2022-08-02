#ifndef C_COMPILER_PARSER_H
#define C_COMPILER_PARSER_H

#include <map>
#include "ast/binary_op_node.h"
#include "ast/primary_node.h"
#include "ast/state_node.h"
#include "tokenizer.h"

class Parser {
public:
    explicit Parser(Token* token);

    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;

    ~Parser();

    Node* getAST();

private:
    /// \brief Parse tokens to get the syntax tree of a statement.
    ///
    /// EBNF: state = expr ";"
    ///             | "return" expr ";"
    ///
    /// \return The root of the syntax tree.
    StateNode* state();

    /// \brief Parse tokens to get the syntax tree of an expression.
    ///
    /// \return The root of the syntax tree.
    ExprNode* expr();

    /// \brief Parse tokens to get the syntax tree of an assignment subexpression.
    ///
    /// EBNF: assign = var ("=" eq | "+=" eq | "-=" eq | "*=" eq | "/=" eq | "%=" eq)
    ///
    /// \return The root of the syntax tree.
    ExprNode* assign();

    /// \brief Parse tokens to get the syntax tree of an equality subexpression.
    ///
    /// EBNF: eq = rel ("==" rel | "!=" rel)*
    ///
    /// \return The root of the syntax tree.
    ExprNode* eq();

    /// \brief Parse tokens to get the syntax tree of a relation subexpression.
    ///
    /// EBNF: rel = add ("<" add | "<=" add | ">" add | ">=" add)*
    ///
    /// \return The root of the syntax tree.
    ExprNode* rel();

    /// \brief Parse tokens to get the syntax tree of an addition subexpression.
    ///
    /// EBNF: add = mul ("+" mul | "-" mul)*
    ///
    /// \return The root of the syntax tree.
    ExprNode* add();

    /// \brief Parse tokens to get the syntax tree of a multiplication subexpression.
    ///
    /// EBNF: mul = unary ("*" unary | "/" unary | "%" unary)*
    ///
    /// \return The root of the syntax tree.
    ExprNode* mul();

    /// \brief Parse tokens to get the syntax tree of a unary subexpression.
    ///
    /// EBNF: unary = ("+" | "-")? primary
    ///
    /// \return The root of the syntax tree.
    ExprNode* unary();

    /// \brief Parse tokens to get the syntax tree of a primary subexpression.
    ///
    /// EBNF: "(" expr ")" | var | num
    ///
    /// \return The root of the syntax tree.
    ExprNode* primary();

    Token* token;
    Node* ast;
    std::vector<std::string> variables;
};

#endif //C_COMPILER_PARSER_H
