#include "ast/binary_op_node.h"

BinaryOpNode::BinaryOpNode(ExprNode* lhs, ExprNode* rhs)
        : lhs(lhs), rhs(rhs) {}

BinaryOpNode::~BinaryOpNode() {
    delete lhs;
    delete rhs;
}

llvm::Value* MulNode::generate(llvm::IRBuilder<>* builder) {
    return builder->CreateMul(lhs->generate(builder), rhs->generate(builder));
}

llvm::Value* DivNode::generate(llvm::IRBuilder<>* builder) {
    return builder->CreateSDiv(lhs->generate(builder), rhs->generate(builder));
}

llvm::Value* AddNode::generate(llvm::IRBuilder<>* builder) {
    return builder->CreateAdd(lhs->generate(builder), rhs->generate(builder));
}

llvm::Value* SubNode::generate(llvm::IRBuilder<>* builder) {
    return builder->CreateSub(lhs->generate(builder), rhs->generate(builder));
}

llvm::Value* LessNode::generate(llvm::IRBuilder<>* builder) {
    return builder->CreateZExt(
            builder->CreateICmpSLT(lhs->generate(builder), rhs->generate(builder)),
            builder->getInt32Ty());
}

llvm::Value* LessEqNode::generate(llvm::IRBuilder<>* builder) {
    return builder->CreateZExt(
            builder->CreateICmpSLE(lhs->generate(builder), rhs->generate(builder)),
            builder->getInt32Ty());
}

llvm::Value* EqNode::generate(llvm::IRBuilder<>* builder) {
    return builder->CreateZExt(
            builder->CreateICmpEQ(lhs->generate(builder), rhs->generate(builder)),
            builder->getInt32Ty());
}

llvm::Value* NotEqNode::generate(llvm::IRBuilder<>* builder) {
    return builder->CreateZExt(
            builder->CreateICmpNE(lhs->generate(builder), rhs->generate(builder)),
            builder->getInt32Ty());
}

llvm::Value* AssignNode::generate(llvm::IRBuilder<>* builder) {
    // The LHS operand is the variable.
    return builder->CreateStore(rhs->generate(builder), lhs->generate(builder));
}
