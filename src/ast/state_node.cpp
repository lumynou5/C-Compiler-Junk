#include "ast/state_node.h"

StateNode::~StateNode() {
    delete next;
}

NormalStateNode::NormalStateNode(ExprNode* content) : content(content) {}

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
}

RetStateNode::RetStateNode(ExprNode* value) : value(value) {}

RetStateNode::~RetStateNode() {
    delete value;
}

llvm::Value* RetStateNode::generate(llvm::IRBuilder<>* builder) {
    return builder->CreateRet(value->generate(builder));
}
