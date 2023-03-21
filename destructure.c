#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "definitions.h"

char functions[6][4] = {"xor", "ls", "rs", "lr", "rr", "not"};

void tokenize(Token *root, char *line, int begin)
{
    int i;
    printf("destructure line %d\n", 13);

    // Current token
    Token *curr = root;

    // Traverse the line
    for (i = begin; line[i] != NULL_CHAR; i++)
    {
        printf("destructure line %d\n", 17);
        printf("%c\n", line[i]);

        // Operator
        if (line[i] == '+' || line[i] == '*' || line[i] == '-' || line[i] == '&' || line[i] == '|')
        {
            printf("destructure line %d\n", 22);
            curr->type = OPR;

            char str[2];
            str[0] = line[i];

            strcpy(curr->name, str);

            curr->next = NULL;

            printf("destructure line %d\n", 30);

        } // Parantheses
        else if (line[i] == '(' || line[i] == ')')
        {
            printf("destructure line %d\n", 36);
            curr->type = PAR;

            char str[2];
            str[0] = line[i];

            strcpy(curr->name, str);

            curr->next = NULL;

            printf("destructure line %d\n", 45);

        } // Comma
        else if (line[i] == ',')
        {
            printf("destructure line %d\n", 50);
            curr->type = COM;

            char str[2];
            str[0] = line[i];

            strcpy(curr->name, str);

            curr->next = NULL;

            printf("destructure line %d\n", 60);

        } // Variable
        else if (('a' <= line[i] && line[i] <= 'z') || ('A' <= line[i] && line[i] <= 'Z'))
        {
            printf("destructure line %d\n", 64);
            int start = i;
            int len = 0;

            while ((('a' <= line[i] && line[i] <= 'z') || ('A' <= line[i] && line[i] <= 'Z')) && line[i] != NULL_CHAR)
            {
                i++;
                len++;
            }

            bool is_var = true; // is variable

            strncpy(curr->name, line + start, len);

            for (int ind = 0; ind < sizeof(functions) / sizeof(functions[0]); ind++)
            {
                if (strcmp(functions[ind], curr->name) == 0)
                {
                    is_var = false;
                    break;
                }
            }

            if (is_var)
            {
                curr->type = VAR;
            }
            else
            {
                curr->type = FUN;
            }

            curr->next = NULL;

            printf("destructure line %d\n", 99);

            i--;

        } // Number
        else if ('0' <= line[i] && line[i] <= '9')
        {

            printf("destructure line %d\n", 105);
            int start = i;
            int len = 0;

            while (('0' <= line[i] && line[i] <= '9') && line[i] != NULL_CHAR)
            {
                i++;
                len++;
            }

            curr->type = NUM;

            strncpy(curr->name, line + start, len);

            curr->next = NULL;

            printf("destructure line %d\n", 121);

            i--;
        }

        // First create storage, then move to next
        curr->next = (Token *)malloc(sizeof(Token));
        curr = curr->next;
    }
}