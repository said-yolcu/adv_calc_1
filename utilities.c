
#include <string.h>
#include <stdio.h>

#include "definitions.h"

#define MAX_STR_LENGTH 100 // Mxx length of the left right string

// Print node tree in reverse (root at the bottom)
void printNodeTree(Node *root, char *prefix, int depth)
{
    if (root == NULL)
    {
        return;
    }

    char leftie[MAX_STR_LENGTH];
    char rightie[MAX_STR_LENGTH];

    strcpy(leftie, prefix);
    strcpy(rightie, prefix);

    strcat(leftie, " left");
    strcat(rightie, " right");

    // Print left-side, this node, than right-side
    printNodeTree(root->left, leftie, depth+1);

    // Print spaces before each node to be visual-friendly
    for (int i = 0; i < depth; i++)
    {
        // 3 spaces for each
        printf("%s", "   ");
    }
    printf("<%s>\n", root->name);

    printNodeTree(root->right, rightie, depth+1);

    // printf("%s type %d: <%s>\n", prefix, root->type, root->name);

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