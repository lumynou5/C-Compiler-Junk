#include "ast/state_node.h"

NormalStateNode::NormalStateNode(ExprNode* content, StateNode* next)
        : content(content), next(next) {}

llvm::Value* NormalStateNode::generate(llvm::IRBuilder<>* builder) {
    // REG = alloca i32
    // store i32 VAL, i32* REG
    auto reg = builder->CreateAlloca(builder->getInt32Ty());
    builder->CreateStore(content->generate(builder), reg);

    if (next) {
        return next->generate(builder);
    } else {
        return reg;
    }
}
