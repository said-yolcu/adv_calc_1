#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "definitions.h"
// #include "simpleMath.h"

char functions[5][4] = {"xor", "ls", "rs", "lr", "rr"};
char unaFunc[1][4] = {"not"};

char operators[11][4] = {"|", "&", "+", "-", "*"};

int max(int a, int b);

// Divide the "line" into tokens and store these
// tokens into the linkedlist with "head" as head
void tokenize(Token *head, char *line, int begin)
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
}

// Out of the tokens between Token "head" and Token with the number field "until"
// create a node tree, then return the root node of this tree
Node *parse(Token *head, int maxLayer, int until)
{
    Token *curr;
    int from = head->number;

    printf("destructure line 259 %s\n", "");

    // Iterate over each layer
    // for (int curLayer = 0; curLayer <= maxLayer; curLayer++)
    // Loop it once for test purposes
    for (int curLayer = 0; curLayer < 1; curLayer++)
    {

        printf("destructure line 267 %s\n", "");

        // Check for each operator
        // for (int opr = 0; opr < sizeof(operators) / sizeof(operators[0]); opr++)
        for (int opr = 0; opr < 1; opr++)
        {

            printf("destructure line 274 %s\n", "");

            // Initially points to head at each iteration
            curr = head;

            printf("destructure line 279 %s\n", "");

            // Move to the next token until the token on the searched layer
            // is encountered
            while (curr != NULL)
            {

                printf("destructure line 286 %s\n", "");

                // We have iterated the last token
                if (curr->number > until)
                {

                    printf("destructure line 292 %s\n", "");
                    break;
                }

                printf("destructure line 296 %s\n", "");

                // Check that its on the current layer
                if (curr->layer == curLayer)
                {
                    printf("curr->layer: %d, curLayer: %d\n", curr->layer, curLayer);
                    printf("curr->number: %d\n", curr->number);

                    printf("destructure line 302 %s\n", "");

                    printf("curr->this->name: %s, operators[opr]: %s\n",
                           curr->this->name, operators[opr]);

                    // "|", "&", "+", "-", "*" operations
                    if (strcmp(curr->this->name, operators[opr]) == 0)
                    {

                        printf("destructure line 308 %s\n", "");

                        if (curr->prev == NULL)
                        {

                            printf("destructure line 313 %s\n", "");

                            printf("Error! No expression before operator %s\n", operators[opr]);
                            return NULL;
                        }

                        // Node *left = parse(head, maxLayer, curr->prev->number);
                        // For testing purposes
                        Token *testLeft = head;

                        printf("destructure line 323 %s\n", "");

                        if (curr->next == NULL)
                        {
                            printf("destructure line 327 %s\n", "");

                            printf("Error! No expression after operator %s\n", operators[opr]);
                            return NULL;
                        }

                        // Node *right = parse(curr->next, maxLayer, until);
                        // For testing purposes
                        Token *testRight = curr->next;

                        printf("destructure line 337 %s\n", "");

                        // Cut the connections between left,this token , and right
                        curr->prev->next = NULL;
                        curr->prev = NULL;
                        curr->next->prev = NULL;
                        curr->next = NULL;

                        printf("destructure line 345 %s\n", "");

                        // Connect the branch to the left and right
                        // curr->this->left = left;
                        // curr->this->right = right;

                        // For testing purposes
                        curr->this->testLeft = testLeft;
                        curr->this->testRight = testRight;

                        printf("destructure line 355 %s\n", "");

                        printf("curr this is %s\n", curr->this->name);
                        return curr->this;
                    }

                    printf("destructure line 361 %s\n", "");
                }

                printf("destructure line 364 %s\n", "");
                curr = curr->next;

                printf("destructure line 367 %s\n", "");
            }
        }
    }
}

// Head of the layer and the layer number
int parseUntil(Token *layHead, int curLayer, int untilToken)
{
    if (curLayer != 0 && layHead->prev != NULL && layHead->prev->this->type != PAR)
    {
        printf("destructure line 248: %s\n", "Error: layer change w/o a paranthesis");
        return 1;
    }

    // If we are in a binary function paranthesis
    if (curLayer != 0 && layHead->prev != NULL && layHead->prev->prev != NULL &&
        layHead->prev->prev->this->type == BIN)
    {
    }
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}