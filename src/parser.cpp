#include "parser.h"

#include "error.hpp"

Node* parse(Token* token) {
    return normal_state(token);
}

StateNode* normal_state(Token*& token) {
    if (token->kind == TokenKind::Eof) {
        return nullptr;
    }

    auto node = expr(token);
    if (!consume(token, ";")) {
        compilationError(token->line, token->str, "Expected `;`.");
    }
    return new NormalStateNode(node, normal_state(token));
}

ExprNode* expr(Token*& token) {
    return assign(token);
}

ExprNode* assign(Token*& token) {
    Token* previous = token;

    if (auto id = consumeId(token); !id.empty()) {
        if (consume(token, "=")) {
            return new AssignNode(new VarStoreNode(id), eq(token));
        }
    }

    token = previous;
    return eq(token);
}

ExprNode* eq(Token*& token) {
    auto node = rel(token);

    while (true) {
        if (consume(token, "==")) {
            node = new EqNode(node, rel(token));
        } else if (consume(token, "!=")) {
            node = new NotEqNode(node, rel(token));
        } else {
            return node;
        }
    }
}

ExprNode* rel(Token*& token) {
    auto node = add(token);

    while (true) {
        if (consume(token, "<=")) {
            node = new LessEqNode(node, add(token));
        } else if (consume(token, ">=")) {
            node = new LessEqNode(add(token), node);
        } else if (consume(token, "<")) {
            node = new LessNode(node, add(token));
        } else if (consume(token, ">")) {
            node = new LessNode(add(token), node);
        } else {
            return node;
        }
    }
}

ExprNode* add(Token*& token) {
    auto node = mul(token);

    while (true) {
        if (consume(token, "+")) {
            node = new AddNode(node, mul(token));
        } else if (consume(token, "-")) {
            node = new SubNode(node, mul(token));
        } else {
            return node;
        }
    }
}

ExprNode* mul(Token*& token) {
    auto node = unary(token);

    while (true) {
        if (consume(token, "*")) {
            node = new MulNode(node, unary(token));
        } else if (consume(token, "/")) {
            node = new DivNode(node, unary(token));
        } else {
            return node;
        }
    }
}

ExprNode* unary(Token*& token) {
    if (consume(token, "+")) {
        return primary(token);
    } else if (consume(token, "-")) {
        return new SubNode(new NumNode(0), primary(token));
    }

    return primary(token);
}

ExprNode* primary(Token*& token) {
    if (consume(token, "(")) {
        auto node = expr(token);
        if (!consume(token, ")")) {
            compilationError(token->line, token->str, "Expected `)`.");
        }
        return node;
    }

    if (auto id = consumeId(token); !id.empty()) {
        return new VarLoadNode(id);
    }

    return new NumNode(expectNumber(token));
}
