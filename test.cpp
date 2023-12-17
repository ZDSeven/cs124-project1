// #include <iostream>

// // Base case for recursion (prints newline)
// void printVars() {
//     std::cout << std::endl;
// }

// // Recursive template function to print variables
// template <typename T, typename... Args>
// void printVars(T first, Args... args) {
//     std::cout << first << ", ";
//     printVars(args...);
// }

// int main() {
//     int P = 10;
//     double Q = 3.14;

//     // Print one variable
//     printVars(Q);

//     // Print multiple variables
//     printVars(P, Q);

//     return 0;
// }
#include <iostream>
#include <string>
#include <map>

bool evaluateExpression(const std::string& expression, const std::map<char, bool>& variableValues) {
    std::string evaluatedExpression = expression;

    // Replace variable names with their corresponding values in the expression
    for (const auto& pair : variableValues) {
        char variable = pair.first;
        bool value = pair.second;

        // Replace occurrences of the variable with its boolean value
        size_t pos = 0;
        while ((pos = evaluatedExpression.find(variable, pos)) != std::string::npos) {
            evaluatedExpression.replace(pos, 1, value ? "true" : "false");
            pos += value ? 4 : 5; // Length of "true" or "false"
        }
    }

    // Evaluate the expression
    std::string command = "echo \"(" + evaluatedExpression + ")\" | bc";
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Error in evaluating the expression." << std::endl;
        return false;
    }

    char buffer[128];
    std::string result = "";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    int exitCode = pclose(pipe);
    return (exitCode == 0) && (result.find("1") != std::string::npos);
}

int main() {
    std::map<char, bool> variableValues;

    // Input values for variables P, Q, and S
    variableValues['P'] = true;  // Example value for P
    variableValues['Q'] = false; // Example value for Q
    variableValues['S'] = true;  // Example value for S

    std::string expression = "P && (!(Q && !S)) || Q";

    // Evaluate the expression
    bool result = evaluateExpression(expression, variableValues);

    // Output the result
    std::cout << "Result: " << (result ? "true" : "false") << std::endl;

    return 0;
}
