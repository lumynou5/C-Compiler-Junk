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
        case NodeKind::Eq:
            result += "    cmp rax, rdi\n"
                      "    sete al\n"
                      "    movzb rax, al\n";
            break;
        case NodeKind::NotEq:
            result += "    cmp rax, rdi\n"
                      "    setne al\n"
                      "    movzb rax, al\n";
            break;
        case NodeKind::Less:
            result += "    cmp rax, rdi\n"
                      "    setl al\n"
                      "    movzb rax, al\n";
            break;
        case NodeKind::LessEq:
            result += "    cmp rax, rdi\n"
                      "    setle al\n"
                      "    movzb rax, al\n";
            break;
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
