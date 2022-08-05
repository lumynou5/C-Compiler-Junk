#include "ast/state_node.h"

StateNode::~StateNode() {
    delete next;
}

NormalStateNode::NormalStateNode(ExprNode* content) : content(content) {}

llvm::Value* NormalStateNode::generate(llvm::IRBuilder<>* builder) {
    if (content) {
        content->generate(builder);
    }
    if (next) {
        return next->generate(builder);
    }

    return nullptr;
}

NormalStateNode::~NormalStateNode() {
    delete content;
}

RetStateNode::RetStateNode(ExprNode* value) : value(value) {}

RetStateNode::~RetStateNode() {
    delete value;
}

llvm::Value* RetStateNode::generate(llvm::IRBuilder<>* builder) {
    builder->CreateRet(value->generate(builder));

    return nullptr;
}
