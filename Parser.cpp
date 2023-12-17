#include <iostream>
#include <vector>
#include <string>
#include "scanner.cpp"

// Enumerations and classes for tokens and scanner (from your scanner.cpp)

// ...

// Abstract base class representing a logical sentence
class Sentence {
public:
    virtual bool evaluate() const = 0;
    virtual void printParseTree(int indent) const = 0;
};

// Concrete class representing a complex sentence with binary connective
class ComplexSentence : public Sentence {
private:
    Sentence* left;
    TokenType connective;
    Sentence* right;

public:
    ComplexSentence(Sentence* left, TokenType connective, Sentence* right)
        : left(left), connective(connective), right(right) {}

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
                return false;
        }
    }

    void printParseTree(int indent) const override {
        std::cout << std::string(indent, ' ') << "ComplexSentence (" << static_cast<int>(connective) << ")\n";
        left->printParseTree(indent + 2);
        right->printParseTree(indent + 2);
    }
};

// Concrete class representing an atomic sentence
class AtomicSentence : public Sentence {
private:
    std::string identifier;

public:
    AtomicSentence(const std::string& identifier) : identifier(identifier) {}

    bool evaluate() const override {
        // To be implemented based on your logic
        return false;
    }

    void printParseTree(int indent) const override {
        std::cout << std::string(indent, ' ') << "AtomicSentence (" << identifier << ")\n";
    }
};

// Concrete class representing a negated sentence
class NegatedSentence : public Sentence {
private:
    Sentence* innerSentence;

public:
    NegatedSentence(Sentence* innerSentence) : innerSentence(innerSentence) {}

    bool evaluate() const override {
        return !innerSentence->evaluate();
    }

    void printParseTree(int indent) const override {
        std::cout << std::string(indent, ' ') << "NegatedSentence\n";
        innerSentence->printParseTree(indent + 2);
    }
};

// Parser class for parsing logical sentences
class Parser {
private:
    const std::vector<Token>& tokens;
    size_t current = 0;

public:
    Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

    bool match(TokenType type) {
        if (tokens[current].type == type) {
            current++;
            return true;
        }
        return false;
    }

    Sentence* parseSentence() {
        return parseComplex();
    }

    Sentence* parseComplex() {
        Sentence* expr = parseEquivalent();

        while (match(TokenType::And) || match(TokenType::Or)) {
            TokenType connective = tokens[current - 1].type;
            Sentence* right = parseEquivalent();
            if (!right) {
                delete expr;
                return nullptr;
            }
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }

    Sentence* parseEquivalent() {
        Sentence* expr = parseImplies();

        while (match(TokenType::Equivalent)) {
            TokenType connective = tokens[current - 1].type;
            Sentence* right = parseImplies();
            if (!right) {
                delete expr;
                return nullptr;
            }
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }

    Sentence* parseImplies() {
        Sentence* expr = parseOr();

        while (match(TokenType::Implies)) {
            TokenType connective = tokens[current - 1].type;
            Sentence* right = parseOr();
            if (!right) {
                delete expr;
                return nullptr;
            }
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }

    Sentence* parseOr() {
        Sentence* expr = parseAnd();

        while (match(TokenType::Or)) {
            TokenType connective = tokens[current - 1].type;
            Sentence* right = parseAnd();
            if (!right) {
                delete expr;
                return nullptr;
            }
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }

    Sentence* parseAnd() {
        Sentence* expr = parsePrimary();

        while (match(TokenType::And)) {
            TokenType connective = tokens[current - 1].type;
            Sentence* right = parsePrimary();
            if (!right) {
                delete expr;
                return nullptr;
            }
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }

    Sentence* parsePrimary() {
        if (match(TokenType::O_Paren)) {
            Sentence* innerSentence = parseComplex();
            if (!match(TokenType::C_Paren)) {
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

        return nullptr;
    }
};

void printParseTree(const Sentence* sentence, int indent) {
    sentence->printParseTree(indent);
}

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
