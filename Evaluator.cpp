#include <iostream>
#include "parser.cpp"

class Evaluator {
    /**
     * @brief Sets the truth value for a variable.
     * @param name The name of the variable.
     * @param value The truth value to set.
     */
public:
    void setVariableValue(const std::string& name, bool value) {
        AtomicSentence::setBooleanValue(name, value);
    }
    /**
     * @brief Gets the truth value of a variable.
     * @param name The name of the variable.
     * @return The truth value of the variable.
     */
    bool getVariableValue(const std::string& name) const {
        return AtomicSentence::getBooleanValue(name);
    }
    /**
     * @brief Evaluates a logical expression rooted at the given Sentence.
     * @param root The root of the logical expression.
     * @return The result of the logical expression evaluation.
     */
    bool evaluate(const Sentence* root) const {
        return root->evaluate();
    }
};
/**
 * @brief Prints the truth table for a logical expression.
 * @param variables The list of variable names.
 * @param root The root of the logical expression.
 * @param logicalExpression The logical expression as a string.
 */
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
