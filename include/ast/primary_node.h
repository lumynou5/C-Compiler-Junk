#ifndef C_COMPILER_PRIMARY_NODE_H
#define C_COMPILER_PRIMARY_NODE_H

#include "ast/node.hpp"
#include "ast/scope.h"
#include "ast/translation_unit.h"

class NumNode : public ExprNode {
public:
    explicit NumNode(long val);

    ~NumNode() override = default;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    long val;
};

class VarStoreNode : public ExprNode {
public:
    VarStoreNode(std::string_view name, Scope* current_scope);

    ~VarStoreNode() override = default;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    std::string name;
    Scope* const current_scope;
};

class VarLoadNode : public ExprNode {
public:
    VarLoadNode(std::string_view name, Scope* current_scope);

    ~VarLoadNode() override = default;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    std::string name;
    Scope* const current_scope;
};

class FuncCallNode : public ExprNode {
public:
    FuncCallNode(std::string_view name, TranslationUnit* tu);

    ~FuncCallNode() override = default;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    std::string name;
    TranslationUnit* const tu;
};

#endif //C_COMPILER_PRIMARY_NODE_H
