#ifndef C_COMPILER_SCOPE_HPP
#define C_COMPILER_SCOPE_HPP

#include <map>
#include <string>
#include <llvm/IR/Value.h>

class Scope {
public:
    Scope() = default;

    Scope(const Scope&) = delete;
    Scope& operator=(const Scope&) = delete;

    std::map<std::string, llvm::Value*> variables;
};

#endif //C_COMPILER_SCOPE_HPP
