#include "ast/primary_node.h"

#include "error.hpp"

NumNode::NumNode(long val) : val(val) {}

llvm::Value* NumNode::generate(llvm::IRBuilder<>* builder) {
    return builder->getInt32(val);
}

VarStoreNode::VarStoreNode(std::string_view name, Scope* current_scope)
        : name(name), current_scope(current_scope) {}

llvm::Value* VarStoreNode::generate(llvm::IRBuilder<>* builder) {
    if (current_scope->variables[name]) {
        return current_scope->variables[name];
    } else {
        return current_scope->variables[name] = builder->CreateAlloca(builder->getInt32Ty());
    }
}

VarLoadNode::VarLoadNode(std::string_view name, Scope* current_scope)
        : name(name), current_scope(current_scope) {}

llvm::Value* VarLoadNode::generate(llvm::IRBuilder<>* builder) {
    return builder->CreateLoad(builder->getInt32Ty(), current_scope->variables[name]);
}
