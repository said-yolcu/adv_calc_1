#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definitions is already included in destructure.h
// #include "definitions.h"
#include "destructure.h"

Token *root;

void prompter(char *);

int main(int argc, char const *argv[])
{
    // char fullLine[LINE_LENGTH];
    char *fullLine = (char *)malloc(LINE_LENGTH * sizeof(char));

    prompter(fullLine);

    // Note that strlen does not count the terminating nullchar
    printf("You have typed: %s, it has length %d\n",
           fullLine, (int)strlen(fullLine));

    // Give storage to root
    root = (Token *)malloc(sizeof(Token));

    tokenize(root, fullLine, 0);

    printf("line %d\n", 26);

    while (root != NULL)
    {
        printf("line %d\n", 30);
        printf("type %d: <%s>\n", root->type, root->name);
        root = root->next;
    }

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