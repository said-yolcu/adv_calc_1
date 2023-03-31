#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define LINE_LENGTH 257 // Including the terminating nullchar
#define NULL_CHAR '\0'
#define MAX_NAME 40 // Max length of the variable name. May reset later

// Cannot define a global variable in a header that would be included in multiple
// files. Multiple *definitions* is not allowed. But we can *declare* it multiple
// times.

// Node structure
typedef struct Nodes
{
    enum
    {
        VAR, // 0 Variable
        OPR, // 1 Operator: + * - & |
        BIN, // 2 Binary Function: xor, ls, rs, lr, rr
        UNA, // 3 Unary Function: not
        COM, // 4 Comma
        PAR, // 5 Parantheses
        NUM, // 6 Number
        ASG  // 7 Assignment
    } type;

    char name[MAX_NAME];

    struct Nodes *left;  // Node on the left
    struct Nodes *right; // Node on the rigth

    struct Tokens *testLeft;  // Token head on the left
    struct Tokens *testRight; // Token head on the right
} Node;

// Token structure, each token consists of a Node tree
typedef struct Tokens
{
    int layer;

    // Whichth token from the beginning, starting from 0
    int number;

    struct Tokens *next; // Next token
    struct Tokens *prev; // Previous token

    Node *this; // Pointer to this node
} Token;

// Variable structure
typedef struct Variables
{
    // Name of the variable
    char name[MAX_NAME]; 

    // Value of the variable. Do not forget it is LONG not INT
    long value; 

    // Pointer to next variable
    struct Variables * next;
}Variable;

#endif