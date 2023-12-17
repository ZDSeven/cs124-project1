#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Scanner.cpp"
// #include "Parser.cpp"

int main() {
    std::string source = "(P OR Q) AND NOT Q";
    Scanner scanner(source);

    std::vector<Token> tokens = scanner.tokenize();

    for (const Token& token : tokens) {
        std::cout << "Type: ";
        switch (token.type) {
            case TokenType::O_Paren: std::cout << "O_Paren"; break;
            case TokenType::C_Paren: std::cout << "C_Paren"; break;
            case TokenType::Identifier: std::cout << "Identifier"; break;
            case TokenType::Not: std::cout << "Not"; break;
            case TokenType::And: std::cout << "And"; break;
            case TokenType::Or: std::cout << "Or"; break;
            case TokenType::Implies: std::cout << "Implies"; break;
            case TokenType::Equivalent: std::cout << "Equivalent"; break;
            case TokenType::TokenEOF: std::cout << "TokenEOF"; break;
            case TokenType::Unknown: std::cout << "Unknown"; break;
        }

        std::cout << ", Lexeme: " << token.lexeme << std::endl;
    }

    return 0;
}