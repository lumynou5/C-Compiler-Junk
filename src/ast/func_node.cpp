#include "ast/func_node.h"

FuncNode::FuncNode(std::string_view name, StateNode* state_seq)
        : name(name), state_seq(state_seq), next(nullptr) {}

FuncNode::~FuncNode() {
    delete state_seq;
}

llvm::Value* FuncNode::generate(llvm::IRBuilder<>* builder) {
    auto func = llvm::Function::Create(
            llvm::FunctionType::get(builder->getInt32Ty(), false),
            llvm::Function::LinkageTypes::ExternalLinkage,
            name);
    auto entry = llvm::BasicBlock::Create(builder->getContext(), "", func);
    builder->SetInsertPoint(entry);

    if (state_seq) {
        state_seq->generate(builder);
    }

    if (next) {
        next->generate(builder);
    }

    return nullptr;
}
