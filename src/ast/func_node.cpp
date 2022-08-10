#include "ast/func_node.h"

FuncNode::FuncNode(std::string_view name)
        : name(name), state_seq(nullptr), module(nullptr) {}

FuncNode::~FuncNode() {
    delete state_seq;
}

llvm::Value* FuncNode::generate(llvm::IRBuilder<>* builder) {
    auto func = llvm::Function::Create(
            llvm::FunctionType::get(builder->getInt32Ty(), false),
            llvm::Function::LinkageTypes::ExternalLinkage,
            name,
            module);
    auto entry = llvm::BasicBlock::Create(builder->getContext(), "", func);
    builder->SetInsertPoint(entry);

    if (state_seq) {
        state_seq->generate(builder);
    }

    return nullptr;
}
