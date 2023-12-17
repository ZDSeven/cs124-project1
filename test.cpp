#include <iostream>

// Base case for recursion (prints newline)
void printVars() {
    std::cout << std::endl;
}

// Recursive template function to print variables
template <typename T, typename... Args>
void printVars(T first, Args... args) {
    std::cout << first << ", ";
    printVars(args...);
}

int main() {
    int P = 10;
    double Q = 3.14;

    // Print one variable
    printVars(Q);

    // Print multiple variables
    printVars(P, Q);

    return 0;
}
