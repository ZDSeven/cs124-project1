#include <iostream>
#include "parser.cpp"

class Evaluator {
public:
    void setVariableValue(const std::string& name, bool value) {
        AtomicSentence::setBooleanValue(name, value);
    }

    bool getVariableValue(const std::string& name) const {
        return AtomicSentence::getBooleanValue(name);
    }

    bool evaluate(const Sentence* root) const {
        return root->evaluate();
    }
};

void printTruthTable(const std::vector<std::string>& variables, const Sentence* root, const std::string& logicalExpression) {
    // Calculate the number of rows in the truth table
    int numRows = 1 << variables.size(); // 2^n rows for n variables

    // Print header
    for (const std::string& variable : variables) {
        std::cout << variable << "\t";
    }
    std::cout << logicalExpression << "\n"; // Include the logical expression in the header

    // Iterate through all possible truth values
    for (int i = 0; i < numRows; ++i) {
        Evaluator evaluator;

        // Set truth values for variables
        for (int j = 0; j < variables.size(); ++j) {
            bool value = (i >> j) & 1; // Extract j-th bit
            evaluator.setVariableValue(variables[j], value);
            std::cout << std::boolalpha << value << "\t";
        }

        // Evaluate the logical expression for the current truth values
        bool result = evaluator.evaluate(root);
        std::cout << std::boolalpha << result << "\n";
    }
}
