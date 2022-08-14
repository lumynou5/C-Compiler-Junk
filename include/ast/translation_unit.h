#ifndef C_COMPILER_TRANSLATION_UNIT_H
#define C_COMPILER_TRANSLATION_UNIT_H

#include <utility>
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

    FuncNode* addFunction(const std::string& name);

    llvm::Value* getFunction(const std::string& name);

    Scope scope;

private:
    // TODO: Refactor this.
    // Plan: Use a scope instead.
    std::map<std::string, std::pair<FuncNode*, llvm::Value*>> functions;

    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    llvm::Module module;
};

#endif //C_COMPILER_TRANSLATION_UNIT_H
