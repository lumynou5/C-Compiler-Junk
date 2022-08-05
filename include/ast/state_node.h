#ifndef C_COMPILER_STATE_NODE_H
#define C_COMPILER_STATE_NODE_H

#include "ast/node.hpp"

class StateNode : public Node {
public:
    ~StateNode() override;

    StateNode* next;
};

class NormalStateNode : public StateNode {
public:
    NormalStateNode(ExprNode* content);

    ~NormalStateNode() override;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    ExprNode* content;
};

class RetStateNode : public StateNode {
public:
    explicit RetStateNode(ExprNode* value);

    ~RetStateNode() override;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    ExprNode* value;
};

#endif //C_COMPILER_STATE_NODE_H
