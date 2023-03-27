#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void deleteSpaces(char *updatedLine, char *rawLine);

int main(int argc, char const *argv[])
{
    // char fullLine[LINE_LENGTH];
    char *fullLine = (char *)malloc(LINE_LENGTH * sizeof(char));
    char *updatedLine = (char *)malloc(LINE_LENGTH * sizeof(char));

    // Give storage to the variable linked list before the loop
    first = (Variable *)malloc(sizeof(Variable));
    strcpy(first->name,"");
    first->next = NULL;

    while (true)
    {

        // Take the line as a input. If End of File, break out of while loop
        if (prompter(fullLine) == -1)
        {
            break;
        }

        // Delete the spaces
        deleteSpaces(updatedLine, fullLine);

        printf("Updated line: %s\n", updatedLine);

        // Note that strlen does not count the terminating nullchar
        printf("You have typed: %s, it has length %d\n",
               updatedLine, (int)strlen(updatedLine));

        // Give storage to head
        head = (Token *)malloc(sizeof(Token));

        int maxLayer = tokenize(head, updatedLine, 0);

        // printf("line %d\n", 26);

        int numToken = 0;

        // Create and intermediate token pointer to traverse over the list
        Token *token = head;

        while (token != NULL && token->this != NULL)
        {
            numToken++;

            printf("line %d\n", 30);
            printf("type %d: <%s> with number %d and layer %d\n", token->this->type,
                   token->this->name, token->number, token->layer);
            token = token->next;
        }

        Token *tail = token->prev;

        printf("tail is #%d with type %d and name %s\n", tail->number,
               tail->this->type, tail->this->name);

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
                printf("Error!Nothing after assignment operator %s\n", "");
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

        // Print root node
        // printf("root type %d: <%s>\n",
        //        root->type, root->name);

        // Token *leftHead = root->testLeft;
        // Token *rightHead = root->testRight;

        // while (leftHead != NULL && leftHead->this != NULL)
        // {
        //     printf("left type %d: <%s>\n",
        //            leftHead->this->type, leftHead->this->name);

        //     leftHead = leftHead->next;
        // }

        // while (rightHead != NULL && rightHead->this != NULL)
        // {
        //     printf("right type %d: <%s>\n",
        //            rightHead->this->type, rightHead->this->name);

        //     rightHead = rightHead->next;
        // }

        // Print node tree
        printNodeTree(root, 0);

        // Calculate the result. Result is the right-hand side in the case of
        // assignment
        long result = calculate(root, first);

        // If assignment
        if (isAsg)
        {
            printf("main line 137 %s\n", "");
            // Set the variable with name varName as result
            first = setVariable(first, varName, result);
        }
        // If not assignment
        else
        {
            // Print the calculation result
            printf("The result is %ld with hex %lx\n", result, result);
        }

        printVariables(first);
    }
    // printf("line 74%s\n", "");

    freeTokenStorage(head);
    freeVariables(first);
    return 0;
}

int prompter(char *fullLine)
{
    // Print out the prompt
    printf(">");

    if (fgets(fullLine, LINE_LENGTH, stdin) == NULL)
    {
        return -1;
    }

    int len = (int)strlen(fullLine);

    fullLine[len - 1] = NULL_CHAR;

    return 0;
}

void deleteSpaces(char *updatedLine, char *rawLine)
{
    char *rawCopy = rawLine;

    while (*rawCopy != '\0')
    {
        // If the char is a blank space or tab, pass
        if (*rawCopy == ' ' || *rawCopy == '\t')
        {
            rawCopy++;
            continue;
        }

        // Copy other parts
        *updatedLine++ = *rawCopy++;
    }

    *updatedLine = '\0';
}