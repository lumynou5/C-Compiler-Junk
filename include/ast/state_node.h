#ifndef C_COMPILER_STATE_NODE_H
#define C_COMPILER_STATE_NODE_H

#include "node.hpp"

class NormalStateNode : public StateNode {
public:
    NormalStateNode(ExprNode* content, StateNode* next);

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    ExprNode* content;
    StateNode* next;
};

#endif //C_COMPILER_STATE_NODE_H
