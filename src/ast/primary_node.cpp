#include "ast/primary_node.h"

#include <map>
#include "error.hpp"

namespace {

std::map<std::string, llvm::AllocaInst*> variables;

}

NumNode::NumNode(long val) : val(val) {}

llvm::Value* NumNode::generate(llvm::IRBuilder<>* builder) {
    return builder->getInt32(val);
}

VarStoreNode::VarStoreNode(std::string_view name) : name(name) {}

llvm::Value* VarStoreNode::generate(llvm::IRBuilder<>* builder) {
    if (auto it = variables.find(name); it != variables.end()) {
        return it->second;
    } else {
        return variables[name] = builder->CreateAlloca(builder->getInt32Ty());
    }
}

VarLoadNode::VarLoadNode(std::string_view name) : name(name) {}

llvm::Value* VarLoadNode::generate(llvm::IRBuilder<>* builder) {
    return builder->CreateLoad(builder->getInt32Ty(), variables[name]);
}
