#ifndef C_COMPILER_TOP_NODE_H
#define C_COMPILER_TOP_NODE_H

#include "ast/node.hpp"
#include "ast/scope.h"
#include "ast/state_node.h"

class TopNode : public Node {};

class FuncNode : public TopNode {
public:
    FuncNode(std::string_view name, Scope* parent_scope, llvm::Module* module);

    ~FuncNode() override;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;
    const std::string name;
    StateNode* state_seq;

    Scope scope;

private:
    llvm::Module* module;
};

#endif //C_COMPILER_TOP_NODE_H
