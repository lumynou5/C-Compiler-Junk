#ifndef C_COMPILER_FUNC_NODE_H
#define C_COMPILER_FUNC_NODE_H

#include "ast/node.hpp"
#include "ast/state_node.h"

class FuncNode : public Node {
public:
    FuncNode(std::string_view name, StateNode* state_seq);

    ~FuncNode() override;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    std::string name;
    StateNode* state_seq;
    FuncNode* next;
};

#endif //C_COMPILER_FUNC_NODE_H
