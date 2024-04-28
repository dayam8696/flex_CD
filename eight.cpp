#include <iostream>
using namespace std;

// Define the grammar rules
// S -> AB
// A -> c | aA
// B -> d | bB
bool S(string input);
bool A(string input);
bool B(string input);

// Parse tree construction
bool S(string input) {
    if (input.empty()) return false;
    if (input[0] == 'a') {
        cout << "S -> A B" << endl;
        return A(input.substr(1)) && B(input.substr(2));
    }
    return false;
}

bool A(string input) {
    if (input.empty()) return false;
    if (input[0] == 'c') {
        cout << "A -> c" << endl;
        return true;
    } else if (input[0] == 'a') {
        cout << "A -> a A" << endl;
        return A(input.substr(1));
    }
    return false;
}

bool B(string input) {
    if (input.empty()) return false;
    if (input[0] == 'd') {
        cout << "B -> d" << endl;
        return true;
    } else if (input[0] == 'b') {
        cout << "B -> b B" << endl;
        return B(input.substr(1));
    }
    return false;
}

int main() {
    string input = "acbbd"; // Input string
    bool valid = S(input);

    if (valid) {
        cout << "Parse tree construction successful!" << endl;
    } else {
        cout << "Invalid input string." << endl;
    }

    return 0;
}
