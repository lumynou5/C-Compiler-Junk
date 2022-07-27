#include "ast/primary_node.h"

NumNode::NumNode(long val) : val(val) {}

llvm::Value* NumNode::generate(llvm::IRBuilder<>* builder) {
    return builder->getInt32(val);
}
