#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 100 // Including the terminating nullchar
#define NULL_CHAR '\0'

void prompter(char *);

int main(int argc, char const *argv[])
{
    // char fullLine[LINE_LENGTH];
    char *fullLine = (char *)malloc(LINE_LENGTH * sizeof(char));

    prompter(fullLine);

    // Note that strlen does not count the terminating nullchar
    printf("You have typed: %s, it has length %d\n",
           fullLine, (int)strlen(fullLine));


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