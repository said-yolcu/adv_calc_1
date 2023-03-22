#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "definitions.h"

char functions[6][4] = {"xor", "ls", "rs", "lr", "rr", "not"};

// Divide the "line" into tokens and store these
// tokens into the linkedlist with "head" as head
void tokenize(Token *head, char *line, int begin)
{
    int i;
    printf("destructure line %d\n", 13);

    // Current token
    Token *curr = head;

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

            bool is_var = true; // is variable

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

            // Set the type
            if (is_var)
            {
                curr->this->type = VAR;
            }
            else
            {
                curr->this->type = FUN;
            }

            curr->next = NULL;

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

            printf("destructure line %d\n", 121);

            i--;
        }

        // First create storage, then move to next
        curr->next = (Token *)malloc(sizeof(Token));
        curr->next->prev = curr;
        curr = curr->next;
    }
}

void parse(Node *root, Token *head)
{
}