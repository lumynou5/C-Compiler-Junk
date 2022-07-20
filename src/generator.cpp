#include "generator.h"

#include <fmt/format.h>

std::string generate(Node* node) {
    std::string result;

    // If the root is a number, then the syntax tree consists of the root only.
    if (node->kind == NodeKind::Num) {
        result += fmt::format("    push {}\n", node->val);
        return result;
    }

    result += generate(node->lhs);
    result += generate(node->rhs);

    result += "    pop rdi\n"
              "    pop rax\n";

    switch (node->kind) {
        case NodeKind::Add:
            result += "    add rax, rdi\n";
            break;
        case NodeKind::Sub:
            result += "    sub rax, rdi\n";
            break;
        case NodeKind::Mul:
            result += "    imul rax, rdi\n";
            break;
        case NodeKind::Div:
            result += "    cqo\n"
                      "    idiv rdi\n";
            break;
    }

    result += "    push rax\n";
}
