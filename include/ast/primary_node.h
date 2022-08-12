#ifndef C_COMPILER_PRIMARY_NODE_H
#define C_COMPILER_PRIMARY_NODE_H

#include "ast/node.hpp"
#include "ast/scope.h"

class NumNode : public ExprNode {
public:
    explicit NumNode(long val);

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    long val;
};

class VarStoreNode : public ExprNode {
public:
    VarStoreNode(std::string_view name, Scope* current_scope);

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    std::string name;
    Scope* const current_scope;
};

class VarLoadNode : public ExprNode {
public:
    VarLoadNode(std::string_view name, Scope* current_scope);

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    std::string name;
    Scope* const current_scope;
};

#endif //C_COMPILER_PRIMARY_NODE_H
