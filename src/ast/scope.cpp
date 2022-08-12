#include "ast/scope.h"

Scope::Scope(Scope* parent) : parent(parent) {}

void Scope::add(const std::string& name) {
    variables[name] = nullptr;
}

llvm::Value* Scope::allocate(const std::string& name, llvm::Value* value) {
    return variables[name] = value;
}

llvm::Value* Scope::get(const std::string& name) {
    for (Scope* curr = this; curr; curr = curr->parent) {
        if (curr->variables.find(name) != curr->variables.end()) {
            return curr->variables[name];
        }
    }
    return nullptr;
}

bool Scope::has(const std::string& name) {
    for (Scope* curr = this; curr; curr = curr->parent) {
        if (curr->variables.find(name) != curr->variables.end()) {
            return true;
        }
    }
    return false;
}
