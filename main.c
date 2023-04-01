#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// definitions is already included in destructure.h
#include "definitions.h"
#include "free.h"
#include "destructure.h"
#include "utilities.h"
#include "variable.h"

// Linked list of tokens, i.e. linked list of Node trees
// Head always points to the head of the linkedlist
Token *head = NULL;

// First variable on the linked list
Variable *first = NULL;

int prompter(char *fullLine);
int deleteSpaces(char *updatedLine, char *rawLine);

int main(int argc, char const *argv[])
{
    // char fullLine[LINE_LENGTH];
    char *fullLine = (char *)malloc(LINE_LENGTH * sizeof(char));
    char *updatedLine = (char *)malloc(LINE_LENGTH * sizeof(char));

    // Give storage to the variable linked list before the loop
    first = (Variable *)malloc(sizeof(Variable));
    strcpy(first->name, "");
    first->next = NULL;

    // Return status of the prompter
    int retSta = 0;

    while (true)
    {
        // EOF after typing some characters on the line
        if (retSta == -2)
        {
            break;
        }

        // Take the line as a input. If End of File, break out of while loop
        if ((retSta = prompter(fullLine)) == -1)
        {
            break;
        }
        // New line
        else if (retSta == -3)
        {
            continue;
        }

        // Delete the spaces
        if (deleteSpaces(updatedLine, fullLine) == -1)
        {
            // Error in line
            continue;
        }

        // Give storage to head
        head = (Token *)malloc(sizeof(Token));

        int maxLayer = tokenize(head, updatedLine, 0);

        // If an error has happened, restart the loop
        if (maxLayer == -1)
        {
            continue;
        }

        int numToken = 0;

        // Create and intermediate token pointer to traverse over the list
        Token *token = head;

        while (token != NULL && token->this != NULL)
        {
            numToken++;

            token = token->next;
        }

        Token *tail = token->prev;

        // Is it an assignment
        bool isAsg = checkAsg(head);

        // Until this numbered Token
        int until;

        // Name of the assigned variable
        char varName[MAX_NAME];

        // Check if it is an assignment statement
        if (isAsg)
        {
            strcpy(varName, head->this->name);

            // If there is nothing after assignment operator
            if (head->next->next == NULL)
            {
                printf("Error!%s\n", "");
            }
            until = head->next->next->number;
        }
        // If it is not an assignment
        else
        {
            until = head->number;
        }

        // Do not forget, we are transversing the linked list
        // backwards while parsing
        Node *root = parse(tail, 0, maxLayer, until);

        // An error happened, restart the loop
        if (root == NULL)
        {
            continue;
        }


        // Calculate the result. Result is the right-hand side in the case of
        // assignment
        long result = calculate(root, first);

        // If assignment
        if (isAsg)
        {
            // Set the variable with name varName as result
            first = setVariable(first, varName, result);
        }
        // If not assignment
        else
        {
            // Print the calculation result
            printf("%ld\n", result);
        }
    }


    // Free the dynamically allocated storage
    freeTokenStorage(head);
    freeVariables(first);
    return 0;
}

// Prompts the user to enter a line. Returns -1 if there is a problem encountered
// 0 if successful
int prompter(char *fullLine)
{
    // Return status
    // 0 -> successful
    // -1 -> end the program immediately
    // -2 -> end the program after printing the calculation
    // -3 -> new line
    int retSta = 0;

    char *lineCopy = fullLine;
    // Print out the prompt
    printf(">");

    char c;

    while ((c = getchar()) && c != EOF)
    {
        // New line
        if (c == '\n')
        {
            retSta = 0;
            *lineCopy = NULL_CHAR;
            break;
        }
        *lineCopy++ = c;
    }

    // char is End of File
    if (c == EOF)
    {
        retSta = -2;
        *lineCopy = NULL_CHAR;
    }

    int len = (int)strlen(fullLine);

    if (len == 0)
    {
        if (retSta == -2)
        {
            return -1;
        }
        return -3;
    }


    // Ignore the comments by making *%* a null char
    for (int i = 0; i < len; i++)
    {
        if (lineCopy[i] == '%')
        {
            lineCopy[i] = NULL_CHAR;
            break;
        }
    }

    return retSta;
}

int deleteSpaces(char *updatedLine, char *rawLine)
{
    char *rawCopy = rawLine;

    // Is there blank characters (blank space or tab) between certain two characters
    bool is_blank = false;

    while (*rawCopy != '\0')
    {

        // If the char is a blank space or tab, pass
        if (*rawCopy == ' ' || *rawCopy == '\t')
        {
            is_blank = true;

            rawCopy++;
            continue;
        }

        if (is_blank)
        {
            if ((updatedLine - 1) != NULL && isalnum(*(updatedLine - 1)) &&
                (rawCopy) != NULL && isalnum(*(rawCopy)))
            {
                // If there are alphanumerical chars on the both sides of a blank
                // it results in error. Variables, numbers, and functions should
                // be separated by operators or parantheses
                
                // Blank between alphanumerical characters
                printf("Error! %s\n", "");
                return -1;
            }

            is_blank = false;
        }

        // Copy other parts
        *updatedLine++ = *rawCopy++;
    }

    *updatedLine = '\0';
    return 0;
}
