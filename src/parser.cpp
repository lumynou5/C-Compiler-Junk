#include "parser.h"

#include "error.h"

Node* newNode(NodeKind kind, Node* lhs, Node* rhs) {
    auto* node = new Node;
    node->kind = kind;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

Node* newNumNode(long val) {
    auto* node = newNode(NodeKind::Num, nullptr, nullptr);
    node->val = val;
    return node;
}

Node* parse(Token* token) {
    return expr(token);
}

Node* expr(Token*& token) {
    return eq(token);
}

Node* eq(Token*& token) {
    Node* node = rel(token);

    while (true) {
        if (consume(token, "==")) {
            node = newNode(NodeKind::Eq, node, rel(token));
        } else if (consume(token, "!=")) {
            node = newNode(NodeKind::NotEq, node, rel(token));
        } else {
            return node;
        }
    }
}

Node* rel(Token*& token) {
    Node* node = add(token);

    while (true) {
        if (consume(token, "<=")) {
            node = newNode(NodeKind::LessEq, node, add(token));
        } else if (consume(token, ">=")) {
            node = newNode(NodeKind::LessEq, add(token), node);
        } else if (consume(token, "<")) {
            node = newNode(NodeKind::Less, node, add(token));
        } else if (consume(token, ">")) {
            node = newNode(NodeKind::Less, add(token), node);
        } else {
            return node;
        }
    }
}

Node* add(Token*& token) {
    Node* node = mul(token);

    while (true) {
        if (consume(token, "+")) {
            node = newNode(NodeKind::Add, node, mul(token));
        } else if (consume(token, "-")) {
            node = newNode(NodeKind::Sub, node, mul(token));
        } else {
            return node;
        }
    }
}

Node* mul(Token*& token) {
    Node* node = unary(token);

    while (true) {
        if (consume(token, "*")) {
            node = newNode(NodeKind::Mul, node, unary(token));
        } else if (consume(token, "/")) {
            node = newNode(NodeKind::Div, node, unary(token));
        } else {
            return node;
        }
    }
}

Node* unary(Token*& token) {
    if (consume(token, "+")) {
        return primary(token);
    } else if (consume(token, "-")) {
        return newNode(NodeKind::Sub, newNumNode(0), primary(token));
    }

    return primary(token);
}

Node* primary(Token*& token) {
    if (consume(token, "(")) {
        Node* node = expr(token);
        if (!consume(token, ")")) {
            compilationError(token->line, token->str, "Expected `)`.");
        }
        return node;
    }

    Node* node = newNode(NodeKind::Num, nullptr, nullptr);
    node->val = expectNumber(token);
    return node;
}
