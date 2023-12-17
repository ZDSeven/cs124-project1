#include <iostream>
#include <vector>
#include <string>
#include "scanner.cpp"

/**
 * @brief Abstract base class representing a logical sentence
 */
class Sentence {
public:
    virtual bool evaluate() const = 0;
};

/**
 * @brief Concrete class representing a complex sentence with binary connective
 */
class ComplexSentence : public Sentence {
private:
    Sentence* left;
    TokenType connective;
    Sentence* right;
    /**
     * @brief Constructor for ComplexSentence
     * @param left Left operand
     * @param connective Binary connective type
     * @param right Right operand
     */
public:
    ComplexSentence(Sentence* left, TokenType connective, Sentence* right)
        : left(left), connective(connective), right(right) {}
    /**
     * @brief Evaluates the complex sentence based on the binary connective
     * @return Result of the evaluation
     */
    bool evaluate() const override {
        switch (connective) {
            case TokenType::And:
                return left->evaluate() && right->evaluate();
            case TokenType::Or:
                return left->evaluate() || right->evaluate();
            case TokenType::Implies:
                return !left->evaluate() || right->evaluate();
            case TokenType::Equivalent:
                return (left->evaluate() && right->evaluate()) || (!left->evaluate() && !right->evaluate());
            default:
                //Unknown Connective
                return false;
        }
    }
};
/**
 * @brief Concrete class representing an atomic sentence
 */
class AtomicSentence : public Sentence {
private:
    std::string identifier;

public:
    /**
     * @brief Constructor for AtomicSentence
     * @param identifier Identifier for the atomic sentence
     */
    AtomicSentence(const std::string& identifier) : identifier(identifier) {}

    /**
     * @brief Evaluates the atomic sentence (to be implemented)
     * @return Result of the evaluation
     */
    bool evaluate() const override {
        // Return identifier value
        if (identifier == "TRUE"){
            return true;
        } else if (identifier == "FALSE"){
            return false;
        } else{
            return false;
        }
    }
};

class NegatedSentence : public Sentence {
private:
    Sentence* innerSentence;
/**
 * @brief Concrete class representing a negated sentence
 */
public:
/**
     * @brief Constructor for NegatedSentence
     * @param innerSentence Inner sentence to be negated
     */
    NegatedSentence(Sentence* innerSentence) : innerSentence(innerSentence) {}

    /**
     * @brief Evaluates the negated sentence
     * @return Result of the evaluation
     */
    bool evaluate() const override {
        return !innerSentence->evaluate();
    }
};
/**
 * @brief Parser class for parsing logical sentences
 */
class Parser {
private:
    const std::vector<Token>& tokens;
    size_t current = 0;

public:
    /**
     * @brief Constructor for Parser
     * @param tokens Vector of tokens to be parsed
     */
    Parser(const std::vector<Token>& tokens) : tokens(tokens) {}
    /**
     * @brief Helper function to match the current token with a given type
     * @param type TokenType to match
     * @return True if the match is successful, false otherwise
     */
    bool match(TokenType type) {
        if (tokens[current].type == type) {
            current ++;
            return true;
        }
        return false;
    }

    /**
     * @brief Parses a logical sentence
     * @return Parsed sentence
     */
    Sentence* parseSentence() {
        return parseComplex();
    }

    /**
     * @brief Parses a complex sentence with binary connective
     * @return Parsed complex sentence
     */
    Sentence* parseComplex() {
        Sentence* expr = parseEquivalent();

        while (match(TokenType::And) || match(TokenType::Or)) {
            TokenType connective = tokens[current - 1].type;
            Sentence* right = parseEquivalent();
            if (!right) { /*missing right operand*/
                delete expr;
                return nullptr;
            }
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }

    /**
     * @brief Parses an equivalent sentence
     * @return Parsed equivalent sentence
     */
    Sentence* parseEquivalent() {
        Sentence* expr = parseImplies();

        while (match(TokenType::Equivalent)) {
            TokenType connective = tokens[current - 1].type;
            Sentence* right = parseImplies();
            if (!right) { /*missing right operand*/
                delete expr;
                return nullptr;
            }
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }

    /**
     * @brief Parses an implies sentence
     * @return Parsed implies sentence
     */
    Sentence* parseImplies() {
        Sentence* expr = parseOr();

        while (match(TokenType::Implies)) {
            TokenType connective = tokens[current - 1].type;
            Sentence* right = parseOr();
            if (!right) { /*missing right operand*/
                delete expr;
                return nullptr;
            }
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }

    /**
     * @brief Parses an OR sentence
     * @return Parsed OR sentence
     */
    Sentence* parseOr() {
        Sentence* expr = parseAnd();

        while (match(TokenType::Or)) {
            TokenType connective = tokens[current - 1].type;
            Sentence* right = parseAnd();
            if (!right) { /*missing right operand*/
                delete expr;
                return nullptr;
            }
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }

    /**
     * @brief Parses an AND sentence
     * @return Parsed AND sentence
     */
    Sentence* parseAnd() {
        Sentence* expr = parsePrimary();

        while (match(TokenType::And)) {
            TokenType connective = tokens[current - 1].type;
            Sentence* right = parsePrimary();
            if (!right) { /*missing right operand*/
                delete expr;
                return nullptr;
            }
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }
    /**
     * @brief Parses a primary sentence
     * @return Parsed primary sentence
     */
    Sentence* parsePrimary() {
        if (match(TokenType::O_Paren)) {
            Sentence* innerSentence = parseComplex();
            if (!match(TokenType::C_Paren)) {
                // Error no closing parenthesis
                return nullptr;
            }
            return innerSentence;
        }

        if (match(TokenType::Not)) {
            Sentence* innerSentence = parsePrimary();
            return new NegatedSentence(innerSentence);
        }

        if (match(TokenType::Identifier)) {
            return new AtomicSentence(tokens[current - 1].lexeme);
        }

        // Unknown token
        return nullptr;
    }
};

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