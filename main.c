#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definitions is already included in destructure.h
// #include "definitions.h"
#include "destructure.h"

Token *head;

void prompter(char *fullLine);
void freeTokenStorage(Token *head);

int main(int argc, char const *argv[])
{
    // char fullLine[LINE_LENGTH];
    char *fullLine = (char *)malloc(LINE_LENGTH * sizeof(char));

    prompter(fullLine);

    // Note that strlen does not count the terminating nullchar
    printf("You have typed: %s, it has length %d\n",
           fullLine, (int)strlen(fullLine));

    // Give storage to head
    head = (Token *)malloc(sizeof(Token));

    tokenize(head, fullLine, 0);

    printf("line %d\n", 26);

    while (head != NULL)
    {
        printf("line %d\n", 30);
        printf("type %d: <%s>\n", head->type, head->name);
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

void freeTokenStorage(Token *head)
{
    if (head != NULL && head->next != NULL)
    {
        freeTokenStorage(head->next);
    }

    if (head != NULL)
    {
        free(head);
    }
}