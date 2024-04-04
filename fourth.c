#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 10

char grammar[MAX_RULES][MAX_SYMBOLS];
int numRules;

bool hasLeftRecursion(char *rule) {
    return rule[0] == rule[3];
}

void removeLeftRecursion(char *rule) {
    char alpha[MAX_SYMBOLS], beta[MAX_SYMBOLS];
    int i, j;
    int alphaIndex = 0, betaIndex = 0;

    for (i = 4; rule[i] != '|' && rule[i] != '\0'; i++) {
        alpha[alphaIndex++] = rule[i];
    }
    alpha[alphaIndex] = '\0';

    if (rule[i] == '|') {
        i++;
    }
    for (; rule[i] != '\0'; i++) {
        beta[betaIndex++] = rule[i];
    }
    beta[betaIndex] = '\0';

    printf("%c -> %s%c'\n", rule[0], beta, rule[0]);
    printf("%c' -> %s%c' | epsilon\n", rule[0], alpha, rule[0]);
}

void modifyGrammar() {
    int i;

    for (i = 0; i < numRules; i++) {
        if (hasLeftRecursion(grammar[i])) {
            removeLeftRecursion(grammar[i]);
        } else {
            printf("%s\n", grammar[i]);
        }
    }
}

int main() {
    printf("Enter the number of rules: ");
    scanf("%d", &numRules);
    getchar(); // To consume the newline character after the integer input

    printf("Enter the grammar rules:");
    for (int i = 0; i < numRules; i++) {
        fgets(grammar[i], MAX_SYMBOLS, stdin);
    }

    printf("\nModified Grammar:\n");
    modifyGrammar();

    return 0;
}
