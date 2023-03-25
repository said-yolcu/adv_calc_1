#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "definitions.h"
#include "utilities.h"

char functions[5][4] = {"xor", "ls", "rs", "lr", "rr"};
char unaFunc[1][4] = {"not"};

char operators[5][4] = {"|", "&", "+", "-", "*"};

int max(int a, int b);

// Divide the "line" into tokens and store these
// tokens into the linkedlist with "head" as head
int tokenize(Token *head, char *line, int begin)
{
    int i;
    printf("destructure line %d\n", 13);

    // Current token
    Token *curr = head;

    int layer = 0;
    int maxLayer = layer;
    int number = 0;

    // Traverse the line
    for (i = begin; line[i] != NULL_CHAR; i++)
    {
        printf("destructure line %d\n", 17);
        printf("%c\n", line[i]);

        // Operator
        if (line[i] == '+' || line[i] == '*' || line[i] == '-' || line[i] == '&' || line[i] == '|')
        {
            printf("destructure line %d\n", 22);

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

            printf("destructure line %d\n", 30);

        } // Parantheses
        else if (line[i] == '(' || line[i] == ')')
        {
            printf("destructure line %d\n", 36);

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

            printf("destructure line %d\n", 45);

        } // Comma
        else if (line[i] == ',')
        {
            printf("destructure line %d\n", 50);

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

            printf("destructure line %d\n", 60);

        } // Variable
        else if (('a' <= line[i] && line[i] <= 'z') || ('A' <= line[i] && line[i] <= 'Z'))
        {
            printf("destructure line %d\n", 64);

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

            printf("destructure line %d\n", 99);

            i--;

        } // Number
        else if ('0' <= line[i] && line[i] <= '9')
        {

            printf("destructure line %d\n", 105);

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

            printf("destructure line %d\n", 121);

            i--;
        }

        maxLayer = max(maxLayer, layer);

        // numberth token counting from the beginning (head)
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

    printf("destructure line 259 %s\n", "");

    // Iterate over each layer
    for (int curLayer = startLayer; curLayer <= maxLayer; curLayer++)
    // Loop it once for test purposes
    // for (int curLayer = 0; curLayer < 1; curLayer++)
    {

        printf("destructure line 267 %s\n", "");

        // Parse for each operator
        for (int opr = 0; opr < sizeof(operators) / sizeof(operators[0]); opr++)
        // for (int opr = 0; opr < 1; opr++)
        {

            printf("destructure line 274 %s\n", "");

            // Initially points to tail at each iteration
            curr = tail;

            if (curr->number == until)
            {
                printf("destructure line 282 %s\n", "");
                return curr->this;
            }

            printf("destructure line 286 %s\n", "");

            // Move to the next token until the token on the searched layer
            // is encountered
            while (curr != NULL)
            {

                printf("destructure line 293 %s\n", "");

                // We have iterated the last token
                if (curr->number < until)
                {

                    printf("destructure line 299 %s\n", "");
                    break;
                }

                printf("destructure line 303 %s\n", "");

                // Parse it if it is on the current layer, do not parse otherwise
                if (curr->layer == curLayer)
                {
                    printf("curr->layer: %d, curLayer: %d\n", curr->layer, curLayer);
                    printf("curr->number: %d\n", curr->number);

                    printf("destructure line 311 %s\n", "");

                    printf("curr->this->name: %s, operators[opr]: %s\n",
                           curr->this->name, operators[opr]);

                    // "|", "&", "+", "-", "*" operations
                    if (strcmp(curr->this->name, operators[opr]) == 0)
                    {

                        printf("destructure line 320 %s\n", "");

                        if (curr->prev == NULL)
                        {

                            printf("destructure line 325 %s\n", "");

                            printf("Error! No expression before operator %s\n", operators[opr]);
                            return NULL;
                        }

                        Node *left = parse(curr->prev, startLayer, maxLayer, until);
                        // For testing purposes
                        // Token *testLeft = head;

                        printf("destructure line 334 %s\n", "");

                        if (curr->next == NULL)
                        {
                            printf("destructure line 339 %s\n", "");

                            printf("Error! No expression after operator %s\n", operators[opr]);
                            return NULL;
                        }

                        Node *right = parse(tail, startLayer, maxLayer, curr->next->number);
                        // For testing purposes
                        // Token *testRight = curr->next;

                        printf("destructure line 349 %s\n", "");

                        // Cut the connections between left,this token , and right
                        curr->prev->next = NULL;
                        curr->prev = NULL;
                        curr->next->prev = NULL;
                        curr->next = NULL;

                        printf("destructure line 357 %s\n", "");

                        // Connect the branch to the left and right
                        curr->this->left = left;
                        curr->this->right = right;

                        // For testing purposes
                        // curr->this->testLeft = testLeft;
                        // curr->this->testRight = testRight;

                        printf("destructure line 367 %s\n", "");

                        printf("curr this is %s\n", curr->this->name);
                        return curr->this;
                    }

                    printf("destructure line 374 %s\n", "");
                }

                printf("destructure line 377 %s\n", "");

                // Point to the previous token
                curr = curr->prev;

                printf("destructure line 380 %s\n", "");
            }
        }

        // Initially points to tail at each iteration
        curr = tail;

        printf("curr->this->name: %s, curr->number %d\n",
               curr->this->name, curr->number);

        printf("destructure line 388 %s\n", "");

        // Parse for parantheses , this includes functions
        while (curr != NULL && curr->number >= until)
        {
            printf("destructure line 393 %s\n", "");

            // We have iterated the last token
            if (curr->number < until)
            {
                printf("destructure line 399 %s\n", "");

                printf("Error! No opening paranthesis found %s\n", "");
                return NULL;
            }
            printf("destructure line 406 %s\n", "");

            // If it is a paranthesis
            if (curr->this->type == PAR)
            {
                printf("destructure line 412 %s\n", "");

                // It should be an closing paranthesis, we are going backwards
                if (strcmp(curr->this->name, ")") != 0)
                {
                    printf("destructure line 417 %s\n", "");

                    printf("Error! Should be an closing paranthesis %s\n", "");
                    return NULL;
                }

                // Find the opening paranthesis
                Token *open = curr;

                printf("destructure line 426 %s\n", "");

                while (open != NULL)
                {
                    printf("destructure line 430 %s\n", "");

                    printf("Opening paranthesis candidate #%d, %s\n", open->number,
                           open->this->name);

                    printf("type: %d, name: %s, layer: %d, curLayer: %d\n", open->this->type,
                           open->this->name, open->layer, curLayer);

                    // First opening paranthesis on the current layer
                    if (open->this->type == PAR && strcmp(open->this->name, "(") == 0 &&
                        open->layer == curLayer)
                    {
                        printf("destructure line 436 %s\n", "");

                        int newUntil = open->next->number;

                        // Check whether it is a binary function
                        // or a unary function
                        // or a pure paranthesis
                        // Binary Function case
                        if (open->prev != NULL && open->prev->this->type == BIN)
                        {
                            printf("destructure line 446 %s\n", "");

                            Node *funNode = open->prev->this;

                            printf("destructure line 450 %s\n", "");

                            printf("Comma candidate #%d, <%s>\n", open->number,
                                   open->this->name);

                            // Look between the current position of *open* and
                            // *current* for the comma
                            printf("open->number: %d, curr->number: %d\n",
                                   open->number, curr->number);
                            while (open != NULL && open->number < curr->number)
                            {
                                printf("Comma candidate #%d, <%s><%s>\n", open->number,
                                       open->this->name, ",");

                                printf("open->number: %d, curr->number: %d\n",
                                       open->number, curr->number);

                                printf("destructure line 456 %s\n", "");

                                printf("type name :$%d$ $%d$ open layer: %d, curLayer: %d\n", open->this->type == COM,
                                       strcmp(open->this->name, ",") == 0, open->layer, curLayer);

                                // Look for the comma
                                if (open->this->type == COM &&
                                    strcmp(open->this->name, ",") == 0 &&
                                    // Comma is one layer above the parantheses
                                    open->layer == curLayer + 1)
                                {
                                    printf("destructure line 463 %s\n", "");

                                    // Left branch is in parantheses, therefore 1 layer above
                                    Node *left = parse(open->prev, curLayer + 1, maxLayer, newUntil);

                                    printf("destructure line 468 %s\n", "");

                                    // Right branch is in parantheses, therefore 1 layer above
                                    Node *right = parse(curr->prev, curLayer + 1, maxLayer, open->next->number);

                                    printf("destructure line 473 %s\n", "");

                                    // Connect the branch to the left and right
                                    funNode->left = left;
                                    funNode->right = right;

                                    printf("destructure line 479 %s\n", "");

                                    // Return the resulting binary function node
                                    return funNode;
                                }
                                printf("destructure line 484 %s\n", "");

                                // Increment *open*
                                open = open->next;
                            }
                            printf("destructure line 490 %s\n", "");

                            printf("Error! There should be a comma in the binary function %s\n", "");
                            return NULL;

                        } // Unary function case
                        else if (open->prev != NULL && open->prev->this->type == UNA)
                        {
                            printf("destructure line 498 %s\n", "");

                            Node *funNode = open->prev->this;

                            printf("destructure line 502 %s\n", "");

                            // Only has one branch: Left, it is 1 layer above
                            Node *left = parse(curr->prev, curLayer + 1, maxLayer, newUntil);

                            printf("destructure line 507 %s\n", "");

                            // Connect the branch to the left
                            funNode->left = left;

                            printf("destructure line 512 %s\n", "");

                            // Return the resulting binary function node
                            return funNode;
                        }
                    }

                    printf("destructure line 519 %s\n", "");

                    // Decrement to the previous token
                    open = open->prev;
                }
                printf("destructure line 524 %s\n", "");
            }

            printf("destructure line 528 %s\n", "");

            // Decrement to the previous token
            curr = curr->prev;
        }
        printf("destructure line 533 %s\n", "");

        return NULL;
    }
}
