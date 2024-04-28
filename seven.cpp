#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<char, vector<string>> productions;
unordered_map<char, unordered_set<char>> first;
unordered_map<char, unordered_set<char>> follow;

void addProduction(char nonTerminal, string production) {
    productions[nonTerminal].push_back(production);
}

void calculateFirst(char nonTerminal) {
    if (first.find(nonTerminal) != first.end()) // First set already calculated
        return;

    for (string production : productions[nonTerminal]) {
        if (isupper(production[0])) { // Non-terminal symbol
            calculateFirst(production[0]);
            for (char ch : first[production[0]]) {
                first[nonTerminal].insert(ch);
            }
        } else { // Terminal symbol
            first[nonTerminal].insert(production[0]);
        }
    }
}

void calculateFollow(char nonTerminal) {
    if (follow.find(nonTerminal) != follow.end()) // Follow set already calculated
        return;

    if (nonTerminal == 'S') // S is the start symbol
        follow[nonTerminal].insert('$');

    for (auto prod : productions) {
        char nt = prod.first;
        for (string production : prod.second) {
            size_t pos = production.find(nonTerminal);
            while (pos != string::npos) {
                if (pos == production.size() - 1) { // Non-terminal at the end of production
                    if (nt != nonTerminal) { // Avoid left recursion
                        calculateFollow(nt);
                        for (char ch : follow[nt]) {
                            follow[nonTerminal].insert(ch);
                        }
                    }
                } else {
                    char nextChar = production[pos + 1];
                    if (isupper(nextChar)) { // Next symbol is non-terminal
                        calculateFirst(nextChar);
                        for (char ch : first[nextChar]) {
                            if (ch != '#')
                                follow[nonTerminal].insert(ch);
                            else { // epsilon production
                                if (nt != nonTerminal) { // Avoid left recursion
                                    calculateFollow(nt);
                                    for (char ch : follow[nt]) {
                                        follow[nonTerminal].insert(ch);
                                    }
                                }
                            }
                        }
                        if (first[nextChar].find('#') != first[nextChar].end()) { // If epsilon is in First set
                            if (nt != nonTerminal) { // Avoid left recursion
                                calculateFollow(nt);
                                for (char ch : follow[nt]) {
                                    follow[nonTerminal].insert(ch);
                                }
                            }
                        }
                    } else { // Next symbol is terminal
                        follow[nonTerminal].insert(nextChar);
                    }
                }
                pos = production.find(nonTerminal, pos + 1);
            }
        }
    }
}

int main() {
    // Example grammar
    addProduction('S', "AB");
    addProduction('A', "aA");
    addProduction('A', "#");
    addProduction('B', "bB");
    addProduction('B', "#");

    // Calculate First sets
    for (auto production : productions) {
        calculateFirst(production.first);
    }

    // Calculate Follow sets
    for (auto production : productions) {
        calculateFollow(production.first);
    }

    // Output First sets
    cout << "First sets:" << endl;
    for (auto f : first) {
        cout << "First(" << f.first << ") = { ";
        for (char c : f.second) {
            cout << c << " ";
        }
        cout << "}" << endl;
    }

    // Output Follow sets
    cout << "\nFollow sets:" << endl;
    for (auto f : follow) {
        cout << "Follow(" << f.first << ") = { ";
        for (char c : f.second) {
            cout << c << " ";
        }
        cout << "}" << endl;
    }

    return 0;
}
