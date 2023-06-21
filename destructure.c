#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

#include "definitions.h"
#include "utilities.h"
#include "variable.h"

char functions[5][4] = {"xor", "ls", "rs", "lr", "rr"};
char unaFunc[1][4] = {"not"};

char operators[5][4] = {"|", "&", "+", "-", "*"};

// Divide the "line" into tokens and store these
// tokens into the linkedlist with "head" as head
int tokenize(Token *head, char *line, int begin)
{
    int i;

    // Current token
    Token *curr = head;

    int layer = 0;
    int maxLayer = layer;
    int number = 0;

    // Traverse the line
    for (i = begin; line[i] != NULL_CHAR; i++)
    {
        // Operator
        if (line[i] == '+' || line[i] == '*' || line[i] == '-' || line[i] == '&' || line[i] == '|')
        {
            // Allocate storage for "this" node
            curr->this = (Node *)malloc(sizeof(Node));

            // Left and right nodes are currently null
            curr->this->left = NULL;
            curr->this->right = NULL;

            // Set the type
            curr->this->type = OPR;

            char str[2];
            str[0] = line[i];

            // Set the name
            strcpy(curr->this->name, str);

            // Next token is currently null
            curr->next = NULL;

            // Set the layer
            curr->layer = layer;
        }
        // Parantheses
        else if (line[i] == '(' || line[i] == ')')
        {
            // Allocate storage for "this" node
            curr->this = (Node *)malloc(sizeof(Node));

            // Left and right nodes are currently null
            curr->this->left = NULL;
            curr->this->right = NULL;

            // Set the type
            curr->this->type = PAR;

            char str[2];
            str[0] = line[i];

            // Set the name
            strcpy(curr->this->name, str);

            // Next token is currently null
            curr->next = NULL;

            // Set the layer and update global layer
            if (line[i] == '(')
            {
                curr->layer = layer;
                layer++;
            }
            else // line[i] == ')'
            {
                layer--;
                curr->layer = layer;
            }
        }
        // Comma
        else if (line[i] == ',')
        {
            // Allocate storage for "this" node
            curr->this = (Node *)malloc(sizeof(Node));

            // Left and right nodes are currently null
            curr->this->left = NULL;
            curr->this->right = NULL;

            // Set the type
            curr->this->type = COM;

            char str[2];
            str[0] = line[i];

            // Set the name
            strcpy(curr->this->name, str);

            // Next token is currently null
            curr->next = NULL;

            // Set the layer
            curr->layer = layer;
        }
        // Variable or function
        else if (('a' <= line[i] && line[i] <= 'z') || ('A' <= line[i] && line[i] <= 'Z'))
        {
            // Allocate storage for "this" node
            curr->this = (Node *)malloc(sizeof(Node));

            // Left and right nodes are currently null
            curr->this->left = NULL;
            curr->this->right = NULL;

            int start = i;
            int len = 0;

            while ((('a' <= line[i] && line[i] <= 'z') || ('A' <= line[i] && line[i] <= 'Z')) && line[i] != NULL_CHAR)
            {
                i++;
                len++;
            }

            bool is_var = true;  // is variable
            bool is_una = false; // is unary function

            // Set the name
            strncpy(curr->this->name, line + start, len);

            for (int ind = 0; ind < sizeof(functions) / sizeof(functions[0]); ind++)
            {
                if (strcmp(functions[ind], curr->this->name) == 0)
                {
                    is_var = false;
                    break;
                }
            }

            for (int ind = 0; ind < sizeof(unaFunc) / sizeof(unaFunc[0]); ind++)
            {
                if (strcmp(unaFunc[ind], curr->this->name) == 0)
                {
                    is_var = false;
                    is_una = true;
                    break;
                }
            }

            // Set the type
            if (is_var)
            {
                curr->this->type = VAR;
            }
            else if (is_una)
            {
                curr->this->type = UNA;
            }
            else // is binary
            {
                curr->this->type = BIN;
            }

            curr->next = NULL;

            // Set the layer
            curr->layer = layer;

            i--;
        }
        // Number
        else if ('0' <= line[i] && line[i] <= '9')
        {
            // Allocate storage for "this" node
            curr->this = (Node *)malloc(sizeof(Node));

            // Left and right nodes are currently null
            curr->this->left = NULL;
            curr->this->right = NULL;

            int start = i;
            int len = 0;

            while (('0' <= line[i] && line[i] <= '9') && line[i] != NULL_CHAR)
            {
                i++;
                len++;
            }

            // Set the type
            curr->this->type = NUM;

            // Set the name
            strncpy(curr->this->name, line + start, len);

            curr->next = NULL;

            // Set the layer
            curr->layer = layer;

            i--;
        }
        // Assignment
        else if (line[i] == '=')
        {
            // Allocate storage for "this" node
            curr->this = (Node *)malloc(sizeof(Node));

            // Left and right nodes are currently null
            curr->this->left = NULL;
            curr->this->right = NULL;

            // Set the type
            curr->this->type = ASG;

            char str[2];
            str[0] = line[i];

            // Set the name
            strcpy(curr->this->name, str);

            // Next token is currently null
            curr->next = NULL;

            // Set the layer
            curr->layer = layer;
        }
        // Invalid character
        else
        {
            // printf("Error! Invalid character %c at position %d\n", line[i], i);
            error();
            return -1;
        }

        maxLayer = max(maxLayer, layer);

        // *number*th token counting from the beginning (head)
        curr->number = number;
        number++;

        // First create storage, then move to next
        curr->next = (Token *)malloc(sizeof(Token));
        curr->next->prev = curr;
        curr = curr->next;
    }

    return maxLayer;
}

// Out of the tokens between Token "head" and Token with the number field "until"
// create a node tree, then return the root node of this tree
// We should start from "tail" and move BACKWARDS
Node *parse(Token *tail, int startLayer, int maxLayer, int until)
{
    Token *curr;
    int from = tail->number;

    // Iterate over each layer
    for (int curLayer = startLayer; curLayer <= maxLayer; curLayer++)
    {
        // Parse for each operator
        for (int opr = 0; opr < sizeof(operators) / sizeof(operators[0]); opr++)
        {
            // Initially points to tail at each iteration
            curr = tail;

            // Move to the next token until the token on the searched layer
            // is encountered
            while (curr != NULL)
            {
                // We have iterated the last token
                if (curr->number < until)
                {
                    break;
                }

                // Parse it if it is on the current layer, do not parse otherwise
                if (curr->layer == curLayer)
                {
                    // "|", "&", "+", "-", "*" operations
                    if (strcmp(curr->this->name, operators[opr]) == 0)
                    {
                        if (curr->prev == NULL)
                        {
                            // printf("Error! No expression before operator %s\n", operators[opr]);
                            error();
                            return NULL;
                        }

                        Node *left = parse(curr->prev, startLayer, maxLayer, until);

                        // If an error occurred parsing the left side
                        if (left == NULL)
                        {
                            return NULL;
                        }

                        // Do not forget we have some non-NULL but empty Tokens at the
                        // end of the list
                        if (curr->next == NULL || curr->next->this == NULL)
                        {
                            // printf("Error! No expression after operator %s\n", operators[opr]);
                            error();
                            return NULL;
                        }

                        Node *right = parse(tail, startLayer, maxLayer, curr->next->number);

                        // If an error occurred parsing the right side
                        if (right == NULL)
                        {
                            return NULL;
                        }

                        // Cut the connections between left,this token , and right
                        curr->prev->next = NULL;
                        curr->prev = NULL;
                        curr->next->prev = NULL;
                        curr->next = NULL;

                        // Connect the branch to the left and right
                        curr->this->left = left;
                        curr->this->right = right;

                        return curr->this;
                    }

                    // There should not be any assignment here, as we are only parsing the
                    // right-side of assignment
                    if (curr->this->type == ASG)
                    {
                        error();
                        return NULL;
                    }

                    // We should not encounter any commas before parsing parantheses
                    if (curr->this->type == COM)
                    {
                        error();
                        return NULL;
                    }
                }

                // Point to the previous token
                curr = curr->prev;
            }
        }

        // Initially points to tail at each iteration
        curr = tail;

        // Parse for parantheses , this includes functions
        while (curr != NULL && curr->number >= until)
        {
            // If it is a paranthesis
            if (curr->this->type == PAR)
            {
                // It should be an closing paranthesis, we are going backwards
                if (strcmp(curr->this->name, ")") != 0)
                {
                    // printf("Error! Opening paranthesis w/o a closing paranthesis %s\n", "");
                    error();
                    return NULL;
                }

                // Opening paranthesis
                Token *open = curr;

                // Find the opening paranthesis
                while (open != NULL)
                {
                    // First opening paranthesis on the current layer
                    if (open->this->type == PAR && strcmp(open->this->name, "(") == 0 &&
                        open->layer == curLayer)
                    {
                        int newUntil = open->next->number;

                        // Check whether it is a binary function
                        // or a unary function
                        // or a pure paranthesis
                        // Binary Function case
                        if (open->prev != NULL && open->prev->this->type == BIN)
                        {
                            Node *funNode = open->prev->this;

                            // Look between the current position of *open* and
                            // *current* for the comma
                            // printf("open->number: %d, curr->number: %d\n", open->number, curr->number);
                            while (open != NULL && open->number < curr->number)
                            {
                                // Check for the comma
                                if (open->this->type == COM &&
                                    // This strcmp is unnecessary, but remember the golden rule do not change the code if it works
                                    strcmp(open->this->name, ",") == 0 &&
                                    // Comma is one layer above the parantheses
                                    open->layer == curLayer + 1)
                                {
                                    // Left branch is in parantheses, therefore 1 layer above
                                    Node *left = parse(open->prev, curLayer + 1, maxLayer, newUntil);

                                    // If an error occurred parsing the left side
                                    if (left == NULL)
                                    {
                                        return NULL;
                                    }

                                    // Right branch is in parantheses, therefore 1 layer above
                                    Node *right = parse(curr->prev, curLayer + 1, maxLayer, open->next->number);

                                    // If an error occurred parsing the right side
                                    if (right == NULL)
                                    {
                                        return NULL;
                                    }

                                    // Connect the branch to the left and right
                                    funNode->left = left;
                                    funNode->right = right;

                                    // Return the resulting binary function node
                                    return funNode;
                                }

                                // Increment *open*
                                open = open->next;
                            }

                            // If there is no comma, print ERROR
                            // printf("Error! There should be a comma in the binary function %s\n", "");
                            error();
                            return NULL;
                        }
                        // Unary function case
                        else if (open->prev != NULL && open->prev->this->type == UNA)
                        {
                            Node *funNode = open->prev->this;

                            // Only has one branch: Left, it is 1 layer above
                            Node *left = parse(curr->prev, curLayer + 1, maxLayer, newUntil);

                            // If an error occurred parsing the left side
                            if (left == NULL)
                            {
                                return NULL;
                            }

                            // Connect the branch to the left
                            funNode->left = left;
                            // Right branch is NULL
                            funNode->right = NULL;

                            // Return the resulting binary function node
                            return funNode;
                        }
                        // Pure Paranthesis
                        else
                        {
                            return parse(curr->prev, curLayer + 1, maxLayer, newUntil);
                        }
                    }

                    // Decrement to the previous token
                    open = open->prev;
                }

                // No opening paranthesis are found corresponding to an existing closing paranthesis
                // printf("Error! No opening paranthesis found %s\n", "");
                error();
                return NULL;
            }

            // Decrement to the previous token
            curr = curr->prev;
        }

        // *curr* points to *tail* before each iteration
        curr = tail;

        // If we have made it this far, then it means all the operators and
        // parantheses and functions are parsed. The interval we are parsing
        // in this function call must comprise a single token:
        // a variable or a number
        if (curr != NULL && curr->number == until)
        {
            // It is a variable or number
            if (curr->this->type == VAR || curr->this->type == NUM)
            {
                return curr->this;
            }
            // It is neither of them
            else
            {
                // printf("Error! Single token must be a variable or number %s\n", "");
                error();
                return NULL;
            }
        }

        // printf("Error! At this point we must have a single token %s\n", "");
        error();
        return NULL;
    }
}

// Calculate the result of the parsed line
long calculate(Node *root, Variable *first)
{

    // Bit size of a long (64 bits)
    int longSize = (int)(sizeof(long) / sizeof(char) * 8);

    // If *root* is NULL. This must be the first thing to be checked
    if (root == NULL)
    {
        // This return value may change later
        return 0;
    }

    // NUMBER
    if (root->type == NUM)
    {
        // Convert string to long
        return strtol(root->name, NULL, 10);
    }

    // VARIABLE
    if (root->type == VAR)
    {
        return getVariable(first, root->name);
    }

    // If it is an operation or function
    // Calculate *left* and *right* branches

    long left = calculate(root->left, first);
    long right = calculate(root->right, first);

    // OPERATOR
    if (root->type == OPR)
    {
        // Bitwise-or
        if (strcmp(root->name, "|") == 0)
        {
            return left | right;
        }
        // Bitwise-and
        else if (strcmp(root->name, "&") == 0)
        {
            return left & right;
        }
        // Plus
        else if (strcmp(root->name, "+") == 0)
        {
            return left + right;
        }
        // Minus
        else if (strcmp(root->name, "-") == 0)
        {
            return left - right;
        }
        // Multiplication
        else if (strcmp(root->name, "*") == 0)
        {
            return left * right;
        }
    }
    // BINARY FUNCTION
    if (root->type == BIN)
    {
        // Bitwise-xor
        if (strcmp(root->name, "xor") == 0)
        {
            return left ^ right;
        }
        // Left shift
        else if (strcmp(root->name, "ls") == 0)
        {
            return left << right;
        }
        // Right shift
        else if (strcmp(root->name, "rs") == 0)
        {
            return left >> right;
        }
        // Left rotate
        else if (strcmp(root->name, "lr") == 0)
        {
            // No rotation case
            if (right == 0 || right == longSize)
            {
                return left;
            }

            // *rightEnd* is the leftmost side of the
            // *left* number, which rotates over the
            // edge to the right end side

            // Filter the leftmost *left* number of bits
            long filter = (-1) << (longSize - right);
            long rightEnd = left & filter;
            rightEnd >>= 1;
            rightEnd &= LONG_MAX;
            rightEnd >>= (longSize - right - 1);

            left = left << right;
            return left | rightEnd;
        }
        else if (strcmp(root->name, "rr") == 0)
        {
            // No rotation case
            if (right == 0 || right == longSize)
            {
                return left;
            }

            // *leftEnd* is the rightmost side of the
            // *right* number, which rotates over the
            // edge to the left end side

            // Filter the rightmost *right* number of bits
            long filter = LONG_MAX;
            filter >>= longSize - right - 1;
            long leftEnd = left & filter;

            // Move rightmost bits to left side
            leftEnd <<= longSize - right;

            // Shift right once and make leftmost bit 0
            left >>= 1;
            left &= LONG_MAX;

            left >>= (right - 1);

            return left | leftEnd;
        }
    }

    // UNARY FUNCTION
    if (root->type == UNA)
    {
        // It is certainly *not*, but check it nonetheless
        if (strcmp(root->name, "not") == 0)
        {
            return ~left;
        }
    }
}
