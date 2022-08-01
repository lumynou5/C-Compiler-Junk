#ifndef C_COMPILER_STATE_NODE_H
#define C_COMPILER_STATE_NODE_H

#include "node.hpp"

class NormalStateNode : public StateNode {
public:
    NormalStateNode(ExprNode* content, StateNode* next);

    ~NormalStateNode() override;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    ExprNode* content;
    StateNode* next;
};

class RetStateNode : public StateNode {
public:
    explicit RetStateNode(ExprNode* value);

    ~RetStateNode() override;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    ExprNode* value;
};

#endif //C_COMPILER_STATE_NODE_H
