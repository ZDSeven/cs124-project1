#include <iostream>
#include <string>
#include <vector>

enum class TokenType {
    O_Paren, C_Paren,
    Identifier,
    Not, And, Or, Implies, Equivalent,
    TokenEOF,
    Unknown
};

class Token {
public:
    const TokenType type;
    const std::string lexeme;

    Token(TokenType type, const std::string lexeme)
        : type(type), lexeme(lexeme) {};
};

class Scanner {
private:
    const std::string source;
    std::vector<Token> tokens;
    size_t current = 0;
    size_t start = 0;

public:
    void scanToken(){}

    void scanIdentifier(){}

    void nextToken() {}

    void addToken(TokenType type, const std::string& lexeme){}

    void skipWhiteSpace(){}

    std::vector<Token> tokenize() {
        while (current < source.length()) {
            start = current;
            scanToken();
        }

        addToken(TokenType::TokenEOF, "");
        
        return tokens;
    }

};