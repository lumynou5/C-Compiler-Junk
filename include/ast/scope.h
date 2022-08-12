#ifndef C_COMPILER_SCOPE_H
#define C_COMPILER_SCOPE_H

#include <map>
#include <string>
#include <llvm/IR/Value.h>

class Scope {
public:
    explicit Scope(Scope* parent);

    Scope(const Scope&) = delete;
    Scope& operator=(const Scope&) = delete;

    void add(const std::string& name);

    llvm::Value* allocate(const std::string& name, llvm::Value* value);

    llvm::Value* get(const std::string& name);

    bool has(const std::string& name);

    Scope* const parent;

private:
    std::map<std::string, llvm::Value*> variables;
};

#endif //C_COMPILER_SCOPE_H
