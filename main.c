#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definitions is already included in destructure.h
#include "definitions.h"
#include "free.h"
#include "destructure.h"

// Linked list of tokens, i.e. linked list of Node trees
Token *head;

void prompter(char *fullLine);
void deleteSpaces(char *updatedLine, char *rawLine);

int main(int argc, char const *argv[])
{
    // char fullLine[LINE_LENGTH];
    char *fullLine = (char *)malloc(LINE_LENGTH * sizeof(char));
    char *updatedLine = (char *)malloc(LINE_LENGTH * sizeof(char));

    // Take the line as a input
    prompter(fullLine);

    // Delete the spaces
    deleteSpaces(updatedLine, fullLine);

    printf("Updated line: %s\n", updatedLine);

    // Note that strlen does not count the terminating nullchar
    printf("You have typed: %s, it has length %d\n",
           updatedLine, (int)strlen(updatedLine));

    // Give storage to head
    head = (Token *)malloc(sizeof(Token));

    tokenize(head, updatedLine, 0);

    printf("line %d\n", 26);

    while (head != NULL && head->this != NULL)
    {
        printf("line %d\n", 30);
        printf("type %d: <%s>\n", head->this->type, head->this->name);
        head = head->next;
    }

    freeTokenStorage(head);
    return 0;
}

void prompter(char *fullLine)
{
    // Print out the prompt
    printf(">");

    fgets(fullLine, LINE_LENGTH, stdin);

    int len = (int)strlen(fullLine);

    fullLine[len - 1] = NULL_CHAR;
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