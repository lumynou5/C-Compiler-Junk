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
