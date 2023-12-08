#include <iostream>
#include <string>
#include <vector>

enum class TokenType {
    // Single-character tokens
    OParen, CParen,
    // Literals
    Ident, P, Q,
    // Keywords
    True, False, Not, And, Or, Implies, Equivalent,

    TokenEOF
};

class Token {
public:
    const TokenType type;
    const std::string lexeme;
    const int line;

    Token(TokenType type, const std::string lexeme, int line)
        : type(type), lexeme(lexeme), line(line) {};
};

class Scanner {
private:
    const std::string source;
    std::vector<Token> tokens;
    size_t current = 0;
    size_t start = 0;
    int line = 1;

public:
    void scanToken() {
    char c = advance();
    switch (c) {
        case '(': addToken(TokenType::OParen); break;
        case ')': addToken(TokenType::CParen); break;
        case ' ':
        case '\r':
        case '\t': break;
        case '\n': line++; break;
        case 'P':
        case 'Q': addToken(TokenType::Ident); break;
        case 'A': case 'O': case 'N': case 'I': case 'E':
            scanIdentifier(); break;
        default:
            break;
        }
    }  

    void scanIdentifier() {
        while (isAlpha(peek())) advance();

        std::string identifier = source.substr(start, current - start);
        TokenType type = TokenType::Ident;

        if (identifier == "AND") type = TokenType::And;
        else if (identifier == "OR") type = TokenType::Or;
        else if (identifier == "NOT") type = TokenType::Not;
        else if (identifier == "IMPLIES") type = TokenType::Implies;
        else if (identifier == "EQUIVALENT") type = TokenType::Equivalent;
        else if (identifier == "P") type = TokenType::P;
        else if (identifier == "Q") type = TokenType::Q;

        addToken(type);
    }

    bool isAlpha(char c) {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
    }

    char peek() {
        if (isAtEnd()) return '\0';
        return source.at(current);
    }

    Scanner(const std::string& source) : source(source) {}

    std::vector<Token> scanTokens() {
        while (!isAtEnd()) {
            start = current;
            scanToken();
        }

        tokens.emplace_back(TokenType::TokenEOF, "", line);
        return tokens;
    }

    bool isAtEnd() {
        return current >= source.length();
    }

    char advance() {
        return source.at(current++);
    }

    void addToken(TokenType type) {
        std::string text = source.substr(start, current - start);
        tokens.emplace_back(type, text, line);
    }

    void addToken(TokenType type, const char literal) {
        std::string text = source.substr(start, current - start);
        tokens.emplace_back(type, text, line);
    }   
};

int main() {
    std::string sourceCode = "(P AND Q) OR NOT (P IMPLIES Q)";

    Scanner scanner(sourceCode);
    std::vector<Token> tokens = scanner.scanTokens();

    for (const Token& token : tokens) {
        std::cout << "Type: ";
        switch (token.type) {
            case TokenType::OParen: std::cout << "OParen"; break;
            case TokenType::CParen: std::cout << "CParen"; break;
            case TokenType::Ident: std::cout << "Ident"; break;
            case TokenType::True: std::cout << "True"; break;
            case TokenType::False: std::cout << "False"; break;
            case TokenType::Not: std::cout << "Not"; break;
            case TokenType::And: std::cout << "Add"; break;
            case TokenType::Or: std::cout << "Or"; break;
            case TokenType::Implies: std::cout << "Implies"; break;
            case TokenType::Equivalent: std::cout << "Equivalent"; break;
            case TokenType::TokenEOF: std::cout << "TokenEOF"; break;
        }

        std::cout << ", Lexeme: " << token.lexeme << ", Line: " << token.line << std::endl;
    }

    return 0;
}