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
void generateLogicTable(int n) {
    // Print header based on the value of n
    if (n == 1) {
        std::cout << "   P  |  Result" << std::endl;
        std::cout << "----------------" << std::endl;
    } else if (n == 2) {
        std::cout << "   P  |   Q   | Result" << std::endl;
        std::cout << "------------------------" << std::endl;
    } else if (n == 3) {
        std::cout << "   P  |   Q   |   S   | Result" << std::endl;
        std::cout << "-------------------------------" << std::endl;
    } else {
        std::cerr << "Invalid value of n. Supported values are 1, 2, or 3." << std::endl;
        return;
    }

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

int main() {
    // Get user input for n
    int n;
    // std::cout << "Enter the value of n (1, 2, or 3): ";
    // std::cin >> n;

    // Generate and display the logic table
    generateLogicTable(n=2);

    return 0;
}

bool logicalNot(bool value) {
    return !value;
}

// Function to evaluate AND operation
bool logicalAnd(bool p, bool q) {
    return p && q;
}

// Function to evaluate OR operation
bool logicalOr(bool p, bool q) {
    return p || q;
}

// Function to evaluate IMPLIES operation
bool logicalImplies(bool p, bool q) {
    return !p || q;
}

// Function to evaluate EQUIVALENT operation
bool logicalEquivalent(bool p, bool q) {
    return (p && q) || (!p && !q);
}