#ifndef C_COMPILER_FUNC_NODE_H
#define C_COMPILER_FUNC_NODE_H

#include "ast/node.hpp"
#include "ast/scope.hpp"
#include "ast/state_node.h"

class FuncNode : public Node {
public:
    explicit FuncNode(std::string_view name);

    ~FuncNode() override;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    std::string name;
    StateNode* state_seq;
    Scope scope;
    llvm::Module* module;
};

#endif //C_COMPILER_FUNC_NODE_H
