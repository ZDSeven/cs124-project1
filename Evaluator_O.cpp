#include <iostream>
#include <vector>

// Function to evaluate the logical expression with one proposition
bool evaluateLogicalExpression(bool P) {
    return P;
}

// Function to evaluate the logical expression with two propositions
bool evaluateLogicalExpression(bool P, bool Q) {
    return P && Q;
}

// Function to evaluate the logical expression with three propositions
bool evaluateLogicalExpression(bool P, bool Q, bool S) {
    return P && (!(Q && !S)) || Q;
}

// Function to generate and display the logic table
void evaluate(int n) {
    // Print header based on the value of n
    // TODO DETECT THE NUMBER OF N
    // TODO DETECT WHAT TO PRINT IN THE TITLE
    if (n == 1) {
        std::cout << "   P  |  Result" << std::endl;
        std::cout << "----------------" << std::endl;
    } else if (n == 2) {
        std::cout << "   P  |   Q   | Result" << std::endl;
        std::cout << "------------------------" << std::endl;
    } else if (n == 3) {
        std::cout << "   P  |   Q   |   S   | Result" << std::endl;
        std::cout << "-------------------------------" << std::endl;
    } 
    // TODO! EVALUATION OF LOGICAL PROPOSITION
    // Print logic table based on the value of n
    if (n == 1) {
        for (bool p : {true, false}) {
            bool result = evaluateLogicalExpression(p);
            std::cout << (p ? "True " : "False") << " | "
                      << (result ? "True " : "False") << std::endl;
        }
    } else if (n == 2) {
        for (bool p : {true, false}) {
            for (bool q : {true, false}) {
                bool result = evaluateLogicalExpression(p, q);
                std::cout << (p ? "True " : "False") << " | "
                          << (q ? "True " : "False") << " | "
                          << (result ? "True" : "False") << std::endl;
            }
        }
    } else if (n == 3) {
        for (bool p : {true, false}) {
            for (bool q : {true, false}) {
                for (bool s : {true, false}) {
                    bool result = evaluateLogicalExpression(p, q, s);
                    std::cout << (p ? "True " : "False") << " | "
                              << (q ? "True " : "False") << " | "
                              << (s ? "True " : "False") << " | "
                              << (result ? "True" : "False") << std::endl;
                }
            }
        }
    }
}


bool logicalNot(bool value) {
    return !value;
}

bool logicalAnd(bool p, bool q) {
    return p && q;
}

bool logicalOr(bool p, bool q) {
    return p || q;
}

bool logicalImplies(bool p, bool q) {
    return !p || q;
}

bool logicalEquivalent(bool p, bool q) {
    return (p && q) || (!p && !q);
}