#include <iostream>
#include <string>
#include <vector>

/**
 * Enumeration representing different token types in the language.
 */
enum class TokenType {
    // Single-character tokens
    OParen, CParen,
    // Literals
    Ident, P, Q,
    // Keywords
    True, False, Not, And, Or, Implies, Equivalent,

    TokenEOF
};
/**
 * Class representing a token with its type, lexeme, and line number.
 */
class Token {
public:
    const TokenType type; /**< Type of the token. */
    const std::string lexeme; /**< Lexeme of the token. */
    const int line; /**< Line number where the token appears in the source code. */

    /**
     * Constructor for Token class.
     * @param type Type of the token.
     * @param lexeme Lexeme of the token.
     * @param line Line number where the token appears in the source code.
     */
    Token(TokenType type, const std::string lexeme, int line)
        : type(type), lexeme(lexeme), line(line) {};
};

/**
 * Class responsible for scanning the source code and generating a sequence of tokens.
 */
class Scanner {
private:
    const std::string source; /**< Source code to be scanned. */
    std::vector<Token> tokens; /**< Vector to store the generated tokens. */
    size_t current = 0; /**< Current position in the source code. */
    size_t start = 0; /**< Starting position of the current token being scanned. */
    int line = 1; /**< Current line number in the source code. */


public:
    /**
     * Scans the next token from the source code and adds it to the list of tokens.
     */
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
            throw std::runtime_error("Error: Unrecognized token at line " + std::to_string(line));
        }
    }  
    /**
     * Scans an identifier token from the source code, including keywords and literals.
     */
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
    /**
     * Checks if the given character is an alphabetical character.
     * @param c The character to be checked.
     * @return True if the character is an alphabetical character, false otherwise.
     */
    bool isAlpha(char c) {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
    }
    /**
     * Peeks at the next character in the source code without advancing the position.
     * @return The next character in the source code.
     */
    char peek() {
        if (isAtEnd()) return '\0';
        return source.at(current);
    }
    /**
     * Constructor for the Scanner class.
     * @param source The source code to be scanned.
     */
    Scanner(const std::string& source) : source(source) {}
    /**
     * Scans the entire source code and returns the list of tokens.
     * @return Vector containing the generated tokens.
     */
    std::vector<Token> scanTokens() {
        while (!isAtEnd()) {
            start = current;
            scanToken();
        }

        tokens.emplace_back(TokenType::TokenEOF, "", line);
        return tokens;
    }
    /**
     * Checks if the end of the source code has been reached.
     * @return True if the end is reached, false otherwise.
     */
    bool isAtEnd() {
        return current >= source.length();
    }
    /**
     * Advances to the next character in the source code and returns the current character.
     * @return The current character in the source code.
     */
    char advance() {
        return source.at(current++);
    }
    /**
     * Adds a token to the list of tokens with the given type.
     * @param type Type of the token to be added.
     */
    void addToken(TokenType type) {
        std::string text = source.substr(start, current - start);
        tokens.emplace_back(type, text, line);
    }
    /**
     * Adds a token to the list of tokens with the given type and literal character.
     * @param type Type of the token to be added.
     * @param literal Literal character associated with the token.
     */
    void addToken(TokenType type, const char literal) {
        std::string text = source.substr(start, current - start);
        tokens.emplace_back(type, text, line);
    }   
};

int main() {
    std::string sourceCode = "(P AND Q) OR NOoT (P IMPLIES Q)";

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