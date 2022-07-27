#include "generator.h"

Generator::Generator(Node* node)
        : builder(context) {
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
    if (node->NODE_KIND() == NodeKind::State) {
        auto state_node = static_cast<StateNode*>(node);

        // `REG = alloca i32`
        auto reg = builder.CreateAlloca(builder.getInt32Ty());

        // `store i32 VALUE, i32* REG`
        builder.CreateStore(generate(state_node->content), reg);

        // Generate the next statement.
        if (state_node->next == nullptr) {
            return reg;
        } else {
            return generate(state_node->next);
        }
    } else if (node->NODE_KIND() == NodeKind::Number) {
        auto number_node = static_cast<NumberNode*>(node);
        return builder.getInt32(number_node->val);
    } else if (node->NODE_KIND() == NodeKind::BinaryOp) {
        auto binary_op_node = static_cast<BinaryOpNode*>(node);

        auto lhs = generate(binary_op_node->lhs);
        auto rhs = generate(binary_op_node->rhs);

        switch (binary_op_node->kind) {
            case BinaryOpNode::Mul:
                return builder.CreateMul(lhs, rhs);
            case BinaryOpNode::Div:
                return builder.CreateSDiv(lhs, rhs);
            case BinaryOpNode::Add:
                return builder.CreateAdd(lhs, rhs);
            case BinaryOpNode::Sub:
                return builder.CreateSub(lhs, rhs);
            case BinaryOpNode::Less:
                return builder.CreateZExt(builder.CreateICmpSLT(lhs, rhs),
                                          builder.getInt32Ty());
            case BinaryOpNode::LessEq:
                return builder.CreateZExt(builder.CreateICmpSLE(lhs, rhs),
                                          builder.getInt32Ty());
            case BinaryOpNode::Eq:
                return builder.CreateZExt(builder.CreateICmpEQ(lhs, rhs),
                                          builder.getInt32Ty());
            case BinaryOpNode::NotEq:
                return builder.CreateZExt(builder.CreateICmpNE(lhs, rhs),
                                          builder.getInt32Ty());
        }
    }
}
