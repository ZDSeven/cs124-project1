#include <iostream>
#include <fstream>
#include <sstream>
#include "evaluator.cpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    const std::string inputFileName = argv[1];
    std::ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file '" << inputFileName << "'" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Create a scanner and tokenize the source code
        Scanner scanner(line);
        std::vector<Token> tokens = scanner.tokenize();

        // Create a parser and parse the logical expression
        Parser parser(tokens);
        Sentence* parsedSentence = parser.parseSentence();

        // Print the truth table with the logical expression in the header
        std::cout << "\nTruth Table for " << line << ":\n";
        std::vector<std::string> variables = parser.getVariables(); // Get the variables used in the expression
        printTruthTable(variables, parsedSentence, line);

        // Clean up
        delete parsedSentence;
    }

    return 0;
}