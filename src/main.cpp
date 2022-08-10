#include <iostream>
#include "tokenizer.h"
#include "parser.h"

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
    parser.getTU()->generate();

    // Output.
    std::cout << parser.getTU()->ir();

    return EXIT_SUCCESS;
}
