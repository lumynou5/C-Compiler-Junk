#include "generator.h"

Generator::Generator(Node* node)
        : builder(new llvm::IRBuilder<>(context)) {
    llvm::Module module("module", context);
    auto main = llvm::Function::Create(
            llvm::FunctionType::get(builder->getInt32Ty(), false),
            llvm::Function::ExternalLinkage,
            "main",
            module);
    auto entry = llvm::BasicBlock::Create(context, "entry", main);
    builder->SetInsertPoint(entry);

    auto ret = builder->CreateLoad(builder->getInt32Ty(), node->generate(builder));
    builder->CreateRet(ret);

    llvm::raw_string_ostream out(ir);
    main->print(out);
}

std::string_view Generator::getIR() {
    return ir;
}

Generator::~Generator() {
    delete builder;
}
