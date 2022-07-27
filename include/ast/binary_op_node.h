#ifndef C_COMPILER_BINARY_OP_NODE_H
#define C_COMPILER_BINARY_OP_NODE_H

#include "ast/node.hpp"

class BinaryOpNode : public ExprNode {
public:
    BinaryOpNode(ExprNode* lhs, ExprNode* rhs);

    ExprNode* lhs;
    ExprNode* rhs;
};

class MulNode : public BinaryOpNode {
public:
    using BinaryOpNode::BinaryOpNode;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;
};

class DivNode : public BinaryOpNode {
public:
    using BinaryOpNode::BinaryOpNode;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;
};

class AddNode : public BinaryOpNode {
public:
    using BinaryOpNode::BinaryOpNode;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;
};

class SubNode : public BinaryOpNode {
public:
    using BinaryOpNode::BinaryOpNode;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;
};

class LessNode : public BinaryOpNode {
public:
    using BinaryOpNode::BinaryOpNode;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;
};

class LessEqNode : public BinaryOpNode {
public:
    using BinaryOpNode::BinaryOpNode;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;
};

class EqNode : public BinaryOpNode {
public:
    using BinaryOpNode::BinaryOpNode;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;
};

class NotEqNode : public BinaryOpNode {
public:
    using BinaryOpNode::BinaryOpNode;

    llvm::Value* generate(llvm::IRBuilder<>* builder) override;
};

#endif //C_COMPILER_BINARY_OP_NODE_H
