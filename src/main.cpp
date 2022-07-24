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
    Node* node = parse(token);

    // Generate.
    std::cout << Generator(node).getIR();

    return EXIT_SUCCESS;
}
