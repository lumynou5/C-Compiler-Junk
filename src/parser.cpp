#include "parser.h"

#include "error.h"

Node* parse(Token* token) {
    return state(token);
}

StateNode* state(Token*& token) {
    if (token->kind == TokenKind::Eof) {
        return nullptr;
    }

    auto node = expr(token);
    if (!consume(token, ";")) {
        compilationError(token->line, token->str, "Expected `;`.");
    }
    return new StateNode(node, state(token));
}

ExprNode* expr(Token*& token) {
    return eq(token);
}

ExprNode* eq(Token*& token) {
    auto node = rel(token);

    while (true) {
        if (consume(token, "==")) {
            node = new BinaryOpNode(BinaryOpNode::Eq, node, rel(token));
        } else if (consume(token, "!=")) {
            node = new BinaryOpNode(BinaryOpNode::NotEq, node, rel(token));
        } else {
            return node;
        }
    }
}

ExprNode* rel(Token*& token) {
    auto node = add(token);

    while (true) {
        if (consume(token, "<=")) {
            node = new BinaryOpNode(BinaryOpNode::LessEq, node, add(token));
        } else if (consume(token, ">=")) {
            node = new BinaryOpNode(BinaryOpNode::LessEq, add(token), node);
        } else if (consume(token, "<")) {
            node = new BinaryOpNode(BinaryOpNode::Less, node, add(token));
        } else if (consume(token, ">")) {
            node = new BinaryOpNode(BinaryOpNode::Less, add(token), node);
        } else {
            return node;
        }
    }
}

ExprNode* add(Token*& token) {
    auto node = mul(token);

    while (true) {
        if (consume(token, "+")) {
            node = new BinaryOpNode(BinaryOpNode::Add, node, mul(token));
        } else if (consume(token, "-")) {
            node = new BinaryOpNode(BinaryOpNode::Sub, node, mul(token));
        } else {
            return node;
        }
    }
}

ExprNode* mul(Token*& token) {
    auto node = unary(token);

    while (true) {
        if (consume(token, "*")) {
            node = new BinaryOpNode(BinaryOpNode::Mul, node, unary(token));
        } else if (consume(token, "/")) {
            node = new BinaryOpNode(BinaryOpNode::Div, node, unary(token));
        } else {
            return node;
        }
    }
}

ExprNode* unary(Token*& token) {
    if (consume(token, "+")) {
        return primary(token);
    } else if (consume(token, "-")) {
        return new BinaryOpNode(BinaryOpNode::Sub, new NumberNode(0), primary(token));
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

    return new NumberNode(expectNumber(token));
}
