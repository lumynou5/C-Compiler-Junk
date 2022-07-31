#include "parser.h"

#include "error.hpp"

Parser::Parser(Token* token) : token(token) {
    ast = normal_state();
}

Parser::~Parser() {
    delete ast;
}

Node* Parser::getAST() {
    return ast;
}

StateNode* Parser::normal_state() {
    if (token->kind == TokenKind::Eof) {
        return nullptr;
    }

    auto node = expr();
    if (!consume(token, ";")) {
        compilationError(token->line, token->str, "Expected `;`.");
    }
    return new NormalStateNode(node, normal_state());
}

ExprNode* Parser::expr() {
    return assign();
}

ExprNode* Parser::assign() {
    Token* previous = token;

    if (auto id = consumeId(token); !id.empty()) {
        if (consume(token, "=")) {
            variables.push_back(id);
            return new AssignNode(new VarStoreNode(id), eq());
        }
    }

    token = previous;
    return eq();
}

ExprNode* Parser::eq() {
    auto node = rel();

    while (true) {
        if (consume(token, "==")) {
            node = new EqNode(node, rel());
        } else if (consume(token, "!=")) {
            node = new NotEqNode(node, rel());
        } else {
            return node;
        }
    }
}

ExprNode* Parser::rel() {
    auto node = add();

    while (true) {
        if (consume(token, "<=")) {
            node = new LessEqNode(node, add());
        } else if (consume(token, ">=")) {
            node = new LessEqNode(add(), node);
        } else if (consume(token, "<")) {
            node = new LessNode(node, add());
        } else if (consume(token, ">")) {
            node = new LessNode(add(), node);
        } else {
            return node;
        }
    }
}

ExprNode* Parser::add() {
    auto node = mul();

    while (true) {
        if (consume(token, "+")) {
            node = new AddNode(node, mul());
        } else if (consume(token, "-")) {
            node = new SubNode(node, mul());
        } else {
            return node;
        }
    }
}

ExprNode* Parser::mul() {
    auto node = unary();

    while (true) {
        if (consume(token, "*")) {
            node = new MulNode(node, unary());
        } else if (consume(token, "/")) {
            node = new DivNode(node, unary());
        } else if (consume(token, "%")) {
            node = new RemNode(node, unary());
        } else {
            return node;
        }
    }
}

ExprNode* Parser::unary() {
    if (consume(token, "+")) {
        return primary();
    } else if (consume(token, "-")) {
        return new SubNode(new NumNode(0), primary());
    }

    return primary();
}

ExprNode* Parser::primary() {
    if (consume(token, "(")) {
        auto node = expr();
        if (!consume(token, ")")) {
            compilationError(token->line, token->str, "Expected `)`.");
        }
        return node;
    }

    Token* variable = token;
    if (auto id = consumeId(token); !id.empty()) {
        if (std::find(variables.begin(), variables.end(), id) == variables.end()) {
            compilationError(variable->line, variable->str, "Undefined variable.");
        }

        return new VarLoadNode(id);
    }

    return new NumNode(expectNumber(token));
}
