#include "ast/translation_unit.h"

TranslationUnit::TranslationUnit()
        : scope(nullptr), builder(context), module("from-command-line", context) {}

TranslationUnit::~TranslationUnit() {
    std::destroy(functions.begin(), functions.end());
}

void TranslationUnit::generate() {
    for (auto function : functions) {
        function.second.second = function.second.first->generate(&builder);
    }
}

std::string TranslationUnit::ir() const {
    std::string str;
    llvm::raw_string_ostream os(str);
    module.print(os, nullptr);
    return str;
}

FuncNode* TranslationUnit::addFunction(const std::string& name) {
    auto node = new FuncNode(name, &scope, &module);
    functions[name] = std::make_pair(node, nullptr);
    return node;
}

llvm::Value* TranslationUnit::getFunction(const std::string& name) {
    return functions[name].second;
}
