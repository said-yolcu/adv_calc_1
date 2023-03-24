
#include <string.h>
#include <stdio.h>

#include "definitions.h"

#define MAX_STR_LENGTH 100 // Mxx length of the left right string

void printNodeTree(Node *root, char *prefix)
{
    if (root == NULL)
    {
        return;
    }

    printf("%s type %d: <%s>\n", prefix, root->type, root->name);

    char leftie[MAX_STR_LENGTH];
    char rightie[MAX_STR_LENGTH];

    strcpy(leftie, prefix);
    strcpy(rightie, prefix);

    strcat(leftie, " left");
    strcat(rightie, " right");

    printNodeTree(root->left, leftie);
    printNodeTree(root->right, rightie);
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