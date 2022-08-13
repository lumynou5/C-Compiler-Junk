#include "ast/translation_unit.h"

TranslationUnit::TranslationUnit()
        : scope(nullptr), builder(context), module("from-command-line", context) {}

TranslationUnit::~TranslationUnit() {
    std::destroy(nodes.begin(), nodes.end());
}

void TranslationUnit::generate() {
    for (auto node : nodes) {
        node->generate(&builder);
    }
}

std::string TranslationUnit::ir() const {
    std::string str;
    llvm::raw_string_ostream os(str);
    module.print(os, nullptr);
    return str;
}

FuncNode* TranslationUnit::addFunction(std::string_view name) {
    auto node = new FuncNode(name, &scope, &module);
    nodes.push_back(node);
    return node;
}
