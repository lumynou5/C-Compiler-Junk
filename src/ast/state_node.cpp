#include "ast/state_node.h"

NormalStateNode::NormalStateNode(ExprNode* content, StateNode* next)
        : content(content), next(next) {}

llvm::Value* NormalStateNode::generate(llvm::IRBuilder<>* builder) {
    auto val = content->generate(builder);
    if (next) {
        return next->generate(builder);
    } else {
        return val;
    }
}

NormalStateNode::~NormalStateNode() {
    delete content;
    delete next;
}

RetStateNode::RetStateNode(ExprNode* value) : value(value) {}

RetStateNode::~RetStateNode() {
    delete value;
}

llvm::Value* RetStateNode::generate(llvm::IRBuilder<>* builder) {
    return builder->CreateRet(value->generate(builder));
}
