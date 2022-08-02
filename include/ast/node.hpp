#ifndef C_COMPILER_NODE_HPP
#define C_COMPILER_NODE_HPP

#include <llvm/IR/IRBuilder.h>

class Node {
public:
    Node() = default;

    Node(const Node*) = delete;
    Node& operator=(const Node*) = delete;

    virtual ~Node() = default;

    virtual llvm::Value* generate(llvm::IRBuilder<>* builder) = 0;
};

class ExprNode : public Node {};

#endif //C_COMPILER_NODE_HPP
