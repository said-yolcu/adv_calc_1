#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definitions is already included in destructure.h
#include "definitions.h"
#include "free.h"
#include "destructure.h"

// Linked list of tokens, i.e. linked list of Node trees
// Head always points to the head of the linkedlist
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

    // Do not forget, we are transversing the linked list
    // backwards while parsing
    Node *root = parse(tail, 0, 0, head->number);

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
    printNodeTree(root, "");

    printf("line 74%s\n", "");

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