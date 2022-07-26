#ifndef C_COMPILER_GENERATOR_H
#define C_COMPILER_GENERATOR_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include "parser.h"

class Generator {
public:
    explicit Generator(Node* node);

    Generator(const Node&) = delete;
    Generator& operator =(const Node&) = delete;

    std::string_view getIR();

private:
    llvm::Value* generate(Node* node);

    std::string ir;
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
};

#endif //C_COMPILER_GENERATOR_H
