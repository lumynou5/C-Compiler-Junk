#ifndef C_COMPILER_TRANSLATION_UNIT_H
#define C_COMPILER_TRANSLATION_UNIT_H

#include "ast/func_node.h"

class TranslationUnit {
public:
    TranslationUnit();

    TranslationUnit(const TranslationUnit&) = delete;
    TranslationUnit& operator=(const TranslationUnit&) = delete;

    ~TranslationUnit();

    void generate();

    std::string ir();

    std::vector<FuncNode*> functions;

private:
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    llvm::Module module;
};

#endif //C_COMPILER_TRANSLATION_UNIT_H
