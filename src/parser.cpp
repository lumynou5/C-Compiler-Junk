#include "parser.h"

#include "error.hpp"

Parser::Parser(Token* token) : token(token) {
    tu = new TranslationUnit();

    while (this->token->kind != TokenKind::Eof) {
        func();
    }
}

Parser::~Parser() {
    delete tu;
}

TranslationUnit* Parser::getTU() {
    return tu;
}

FuncNode* Parser::func() {
    for (auto id = consumeId(token); !id.empty();) {
        if (!consume(token, "(")) break;
        if (!consume(token, ")")) break;
        if (!consume(token, "{")) break;

        auto node = tu->addFunction(id);

        current_scope = &node->scope;

        StateNode* state_seq = nullptr;
        auto curr = state_seq;
        while (!consume(token, "}")) {
            if (token->kind == TokenKind::Eof) {
                compilationError(token->line, token->str, "Expected `}}`.");
            }

            if (curr) {
                curr->next = state();
                curr = curr->next;
            } else {
                curr = state();
                state_seq = curr;
            }
        }

        current_scope = current_scope->parent;

        node->state_seq = state_seq;
        return node;
    }

    compilationError(token->line, token->str, "Unexpected token.");
}

StateNode* Parser::state() {
    if (auto node = retState(); node) {
        return node;
    }

    return normalState();
}

NormalStateNode* Parser::normalState() {
    // Empty statement.
    if (consume(token, ";")) {
        return new NormalStateNode(nullptr);
    }

    auto node = expr();
    if (!consume(token, ";")) {
        compilationError(token->line, token->str, "Expected `;`.");
    }
    return new NormalStateNode(node);
}

RetStateNode* Parser::retState() {
    if (consume(token, "return")) {
        auto node = expr();
        if (!consume(token, ";")) {
            compilationError(token->line, token->str, "Expected `;`.");
        }
        return new RetStateNode(node);
    }
    return nullptr;
}

ExprNode* Parser::expr() {
    return assign();
}

ExprNode* Parser::assign() {
    Token* previous = token;

    if (auto id = consumeId(token); !id.empty()) {
        if (consume(token, "=")) {
            current_scope->add(id);
            return new AssignNode(new VarStoreNode(id, current_scope), eq());
        }

        if (!current_scope->has(id)) {
            compilationError(token->line, token->str, "Undefined variable.");
        }
        if (consume(token, "+=")) {
            return new AssignNode(new VarStoreNode(id, current_scope),
                                  new AddNode(new VarLoadNode(id, current_scope), eq()));
        } else if (consume(token, "-=")) {
            return new AssignNode(new VarStoreNode(id, current_scope),
                                  new SubNode(new VarLoadNode(id, current_scope), eq()));
        } else if (consume(token, "*=")) {
            return new AssignNode(new VarStoreNode(id, current_scope),
                                  new MulNode(new VarLoadNode(id, current_scope), eq()));
        } else if (consume(token, "/=")) {
            return new AssignNode(new VarStoreNode(id, current_scope),
                                  new DivNode(new VarLoadNode(id, current_scope), eq()));
        } else if (consume(token, "%=")) {
            return new AssignNode(new VarStoreNode(id, current_scope),
                                  new RemNode(new VarLoadNode(id, current_scope), eq()));
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
        if (!current_scope->has(id)) {
            compilationError(variable->line, variable->str, "Undefined variable.");
        }

        return new VarLoadNode(id, current_scope);
    }

    return new NumNode(expectNumber(token));
}
