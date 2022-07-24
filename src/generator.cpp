#include "generator.h"

Generator::Generator(Node* node) : node(node), builder(context) {
    auto main = llvm::Function::Create(
            llvm::FunctionType::get(builder.getInt32Ty(), false),
            llvm::GlobalValue::ExternalLinkage,
            "main");
    auto entry = llvm::BasicBlock::Create(context, "entry", main);
    builder.SetInsertPoint(entry);

    auto ret = generate(node);

    builder.CreateRet(ret);

    llvm::raw_string_ostream out(ir);
    main->print(out);
}

std::string_view Generator::getIR() {
    return ir;
}

llvm::Value* Generator::generate(Node* node) {
    if (node->kind == NodeKind::Num) {
        return builder.getInt32(node->val);
    }

    auto lhs = generate(node->lhs);
    auto rhs = generate(node->rhs);

    switch (node->kind) {
        case NodeKind::Eq:
            builder.CreateZExt(
                    builder.CreateCmp(llvm::CmpInst::Predicate::ICMP_EQ, lhs, rhs),
                    builder.getInt32Ty()
                    );
            break;
        case NodeKind::NotEq:
            builder.CreateZExt(
                    builder.CreateCmp(llvm::CmpInst::Predicate::ICMP_NE, lhs, rhs),
                    builder.getInt32Ty()
            );
            break;
        case NodeKind::Less:
            builder.CreateZExt(
                    builder.CreateCmp(llvm::CmpInst::Predicate::ICMP_SLT, lhs, rhs),
                    builder.getInt32Ty()
            );
            break;
        case NodeKind::LessEq:
            builder.CreateZExt(
                    builder.CreateCmp(llvm::CmpInst::Predicate::ICMP_SLE, lhs, rhs),
                    builder.getInt32Ty()
            );
            break;
        case NodeKind::Add:
            builder.CreateAdd(lhs, rhs);
            break;
        case NodeKind::Sub:
            builder.CreateSub(lhs, rhs);
            break;
        case NodeKind::Mul:
            builder.CreateMul(lhs, rhs);
            break;
        case NodeKind::Div:
            builder.CreateSDiv(lhs, rhs);
            break;
        default:
            break;
    }
}
