
#define LINE_LENGTH 100 // Including the terminating nullchar
#define NULL_CHAR '\0'
#define MAX_NAME 20 // Max length of the variable name. May reset later

typedef struct Tokens
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

    struct Tokens *next; // Next token
    struct Tokens *prev; // Previous token
} Token;

typedef struct Nodes
{
    Token *this;         // Pointer to the token
                         // this node represents
    struct Nodes *left;  // Node on the left
    struct Nodes *right; // Node on the rigth
} Node;