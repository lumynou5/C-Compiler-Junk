#include "ast/translation_unit.h"

TranslationUnit::TranslationUnit() : builder(context), module("from-command-line", context) {}

TranslationUnit::~TranslationUnit() {
    for (auto function : functions) {
        delete function;
    }
}

void TranslationUnit::generate() {
    for (auto function : functions) {
        function->module = &module;
        function->generate(&builder);
    }
}

std::string TranslationUnit::ir() {
    std::string str;
    llvm::raw_string_ostream os(str);
    module.print(os, nullptr);
    return str;
}
