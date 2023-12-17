#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Parser.cpp"

int main() {
    std::string sampleSentence = "(P AND Q) OR NOT Q";
    Scanner scanner(sampleSentence);
    std::vector<Token> tokens = scanner.tokenize();

    std::cout << "Tokens:\n";
    for (const Token& token : tokens) {
        std::cout << "Type: " << static_cast<int>(token.type) << ", Lexeme: " << token.lexeme << "\n";
    }

    return 0;
}