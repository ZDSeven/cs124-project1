#include <iostream>
#include <vector>
#include <string>
#include "scanner.cpp"

class Sentence {
public:
    virtual bool evaluate() const = 0;
};

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
                //Unknown Connective
                return false;
        }
    }
};

class AtomicSentence : public Sentence {
private:
    std::string identifier;

public:
    AtomicSentence(const std::string& identifier) : identifier(identifier) {}

    bool evaluate() const override {
        // Return identifier value
    }
};

class NegatedSentence : public Sentence {
private:
    Sentence* innerSentence;

public:
    NegatedSentence(Sentence* innerSentence) : innerSentence(innerSentence) {}

    bool evaluate() const override {
        return !innerSentence->evaluate();
    }
};

class Parser {
private:
    const std::vector<Token>& tokens;
    size_t current = 0;

public:
    Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

    bool match(TokenType type) {
        if (tokens[current].type == type) {
            current ++;
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
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }

    Sentence* parseEquivalent() {
        Sentence* expr = parseImplies();

        while (match(TokenType::Equivalent)) {
            TokenType connective = tokens[current - 1].type;
            Sentence* right = parseImplies();
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }

    Sentence* parseImplies() {
        Sentence* expr = parseOr();

        while (match(TokenType::Implies)) {
            TokenType connective = tokens[current - 1].type;
            Sentence* right = parseOr();
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }

    Sentence* parseOr() {
        Sentence* expr = parseAnd();

        while (match(TokenType::Or)) {
            TokenType connective = tokens[current - 1].type;
            Sentence* right = parseAnd();
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }

    Sentence* parseAnd() {
        Sentence* expr = parsePrimary();

        while (match(TokenType::And)) {
            TokenType connective = tokens[current - 1].type;
            Sentence* right = parsePrimary();
            expr = new ComplexSentence(expr, connective, right);
        }

        return expr;
    }

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