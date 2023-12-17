#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Parser.cpp"
#include "scanner.cpp"

int main() {
    std::string sampleSentence = "(P AND Q) OR NOT Q";
    Scanner scanner(sampleSentence);
    std::vector<Token> tokens = scanner.tokenize();

    std::cout << "Tokens:\n";
    for (const Token& token : tokens) {
        std::cout << "Type: " << static_cast<int>(token.type) << ", Lexeme: " << token.lexeme << "\n";
    }

    Parser parser(tokens);
    Sentence* parsedSentence = parser.parseSentence();

    if (parsedSentence) {
        std::cout << "\nParse Tree:\n";
        printParseTree(parsedSentence, 0);
    } else {
        std::cerr << "Error: Unable to parse the sentence.\n";
    }

    delete parsedSentence;

    return 0;
}
