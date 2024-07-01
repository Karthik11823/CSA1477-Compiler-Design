#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 10

// Structure to represent a production rule
typedef struct {
    char lhs; // Left-hand side non-terminal
    char rhs[MAX_SYMBOLS]; // Right-hand side symbols
    int numSymbols; // Number of symbols on the right-hand side
} ProductionRule;

// Function prototypes
void eliminateLeftRecursion(ProductionRule rules[], int numRules, char nonTerminal);
void printRules(ProductionRule rules[], int numRules);

int main() {
    ProductionRule rules[MAX_RULES];
    int numRules;

    // Example grammar rules
    rules[0].lhs = 'A';
    strcpy(rules[0].rhs, "Aa");
    rules[0].numSymbols = 2;

    rules[1].lhs = 'A';
    strcpy(rules[1].rhs, "AbA");
    rules[1].numSymbols = 3;

    numRules = 2;

    printf("Original Grammar:\n");
    printRules(rules, numRules);

    // Eliminate left recursion for non-terminal 'A'
    eliminateLeftRecursion(rules, numRules, 'A');

    printf("\nGrammar after Left Recursion Elimination:\n");
    printRules(rules, numRules);

    return 0;
}

// Function to eliminate left recursion for a given non-terminal
void eliminateLeftRecursion(ProductionRule rules[], int numRules, char nonTerminal) {
    int i, j;
    bool recursion = false;
    int newRulesStartIndex = numRules;

    // Separate rules with and without left recursion
    for (i = 0; i < numRules; ++i) {
        if (rules[i].lhs == nonTerminal) {
            if (rules[i].rhs[0] == nonTerminal) {
                // Left recursion found
                recursion = true;
                break;
            }
        }
    }

    if (!recursion) {
        printf("No left recursion found for non-terminal %c\n", nonTerminal);
        return;
    }

    // Create new rules without left recursion
    for (i = 0; i < numRules; ++i) {
        if (rules[i].lhs == nonTerminal) {
            if (rules[i].rhs[0] == nonTerminal) {
                // Eliminate left recursion
                char newNonTerminal = 'A' + newRulesStartIndex; // New non-terminal name
                rules[numRules].lhs = newNonTerminal;
                strcpy(rules[numRules].rhs, rules[i].rhs + 1);
                rules[numRules].rhs[strlen(rules[numRules].rhs)] = newNonTerminal; // Append new non-terminal
                rules[numRules].numSymbols = strlen(rules[numRules].rhs);
                numRules++;

                strcpy(rules[i].rhs, "epsilon"); // Replace old rule with epsilon
                rules[i].numSymbols = 1;

                // Create new rules for remaining productions
                for (j = 0; j < newRulesStartIndex; ++j) {
                    if (rules[j].lhs == nonTerminal) {
                        strcpy(rules[numRules].rhs, rules[j].rhs);
                        rules[numRules].rhs[strlen(rules[numRules].rhs)] = newNonTerminal; // Append new non-terminal
                        rules[numRules].lhs = nonTerminal;
                        rules[numRules].numSymbols = strlen(rules[numRules].rhs);
                        numRules++;
                    }
                }
                rules[numRules - 1].rhs[strlen(rules[numRules - 1].rhs) - 1] = newNonTerminal;
				}
				}
				}
				}
            

