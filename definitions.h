#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define LINE_LENGTH 100 // Including the terminating nullchar
#define NULL_CHAR '\0'
#define MAX_NAME 20 // Max length of the variable name. May reset later

// Node structure
typedef struct Nodes
{
    enum
    {
        VAR, // 0 Variable
        OPR, // 1 Operator: + * - & |
        FUN, // 2 Function: xor, ls, rs, lr, rr, not
        COM, // 3 Comma
        PAR, // 4 Parantheses
        NUM  // 5 Number
    } type;

    char name[MAX_NAME];

    struct Nodes *left;  // Node on the left
    struct Nodes *right; // Node on the rigth
} Node;

// Token structure, each token consists of a Node tree
typedef struct Tokens
{
    /*
    enum
    {
        VAR, // 0 Variable
        OPR, // 1 Operator: + * - & |
        FUN, // 2 Function: xor, ls, rs, lr, rr, not
        COM, // 3 Comma
        PAR, // 4 Parantheses
        NUM  // 5 Number
    } type;

    char name[MAX_NAME];
    */
    struct Tokens *next; // Next token
    struct Tokens *prev; // Previous token

    Node *this; // Pointer to this node
} Token;

#endif