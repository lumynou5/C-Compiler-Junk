#ifndef C_COMPILER_TRANSLATION_UNIT_H
#define C_COMPILER_TRANSLATION_UNIT_H

#include <string>
#include <llvm/IR/IRBuilder.h>
#include "ast/scope.h"
#include "ast/top_node.h"

class TranslationUnit {
public:
    TranslationUnit();

    TranslationUnit(const TranslationUnit&) = delete;
    TranslationUnit& operator=(const TranslationUnit&) = delete;

    ~TranslationUnit();

    void generate();

    std::string ir() const;

    FuncNode* addFunction(std::string_view name);

    Scope scope;

private:
    std::vector<TopNode*> nodes;

    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    llvm::Module module;
};

#endif //C_COMPILER_TRANSLATION_UNIT_H
