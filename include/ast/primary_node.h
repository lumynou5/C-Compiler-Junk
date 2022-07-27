#ifndef C_COMPILER_PRIMARY_NODE_H
#define C_COMPILER_PRIMARY_NODE_H

#include "ast/node.hpp"

class NumNode : public ExprNode {
public:
    explicit NumNode(long val);

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    long val;
};

#endif //C_COMPILER_PRIMARY_NODE_H
