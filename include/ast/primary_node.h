#ifndef C_COMPILER_PRIMARY_NODE_H
#define C_COMPILER_PRIMARY_NODE_H

#include "ast/node.hpp"

class NumNode : public ExprNode {
public:
    explicit NumNode(long val);

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    long val;
};

class VarStoreNode : public ExprNode {
public:
    explicit VarStoreNode(std::string_view name);

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    std::string name;
};

class VarLoadNode : public ExprNode {
public:
    explicit VarLoadNode(std::string_view name);

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;

    std::string name;
};

#endif //C_COMPILER_PRIMARY_NODE_H
