#include <iostream>
#include "tokenizer.h"
#include "parser.h"
#include "generator.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Couldn't recognize the arguments.";
        return EXIT_FAILURE;
    }

    // Tokenize.
    Token* token = tokenize(argv[1]);

    // Parse.
    Parser parser(token);

    // Generate.
    Generator generator(parser.getAST());

    // Output.
    std::cout << generator.getIR();

    return EXIT_SUCCESS;
}
