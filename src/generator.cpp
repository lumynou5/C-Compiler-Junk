#include "generator.h"

Generator::Generator(Node* node) : builder(context) {
    llvm::Module module("module", context);
    auto main = llvm::Function::Create(
            llvm::FunctionType::get(builder.getInt32Ty(), false),
            llvm::Function::ExternalLinkage,
            "main",
            module);
    auto entry = llvm::BasicBlock::Create(context, "entry", main);
    builder.SetInsertPoint(entry);

    auto ret = builder.CreateLoad(builder.getInt32Ty(), generate(node));
    builder.CreateRet(ret);

    llvm::raw_string_ostream out(ir);
    main->print(out);
}

std::string_view Generator::getIR() {
    return ir;
}

llvm::Value* Generator::generate(Node* node) {
    if (node->kind == NodeKind::State) {
        llvm::Value* reg = builder.CreateAlloca(builder.getInt32Ty());
        builder.CreateStore(generate(node->lhs), reg);
        if (node->rhs != nullptr) {
            reg = generate(node->rhs);
        }
        return reg;
    }

    if (node->kind == NodeKind::Num) {
        return builder.getInt32(node->val);
    }

    auto lhs = generate(node->lhs);
    auto rhs = generate(node->rhs);

    switch (node->kind) {
        case NodeKind::Eq:
            return builder.CreateZExt(
                    builder.CreateICmpEQ(lhs, rhs),
                    builder.getInt32Ty()
            );
        case NodeKind::NotEq:
            return builder.CreateZExt(
                    builder.CreateICmpNE(lhs, rhs),
                    builder.getInt32Ty()
            );
        case NodeKind::Less:
            return builder.CreateZExt(
                    builder.CreateICmpSLT(lhs, rhs),
                    builder.getInt32Ty()
            );
        case NodeKind::LessEq:
            return builder.CreateZExt(
                    builder.CreateICmpSLE(lhs, rhs),
                    builder.getInt32Ty()
            );
        case NodeKind::Add:
            return builder.CreateAdd(lhs, rhs);
        case NodeKind::Sub:
            return builder.CreateSub(lhs, rhs);
        case NodeKind::Mul:
            return builder.CreateMul(lhs, rhs);
        case NodeKind::Div:
            return builder.CreateSDiv(lhs, rhs);
        default:
            break;
    }
}
