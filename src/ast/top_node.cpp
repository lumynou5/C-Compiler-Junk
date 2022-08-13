#include "ast/top_node.h"

FuncNode::FuncNode(std::string_view name, Scope* parent_scope, llvm::Module* module)
        : name(name), state_seq(nullptr), scope(parent_scope), module(module) {}

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
