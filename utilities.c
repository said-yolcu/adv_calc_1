
#include <string.h>
#include <stdio.h>

#include "definitions.h"

// #define MAX_STR_LENGTH 100 // Mxx length of the left right string

// Print node tree in reverse (root at the bottom)
void printNodeTree(Node *root, int depth)
{
    static int num = 0;

    // if (num >= 30)
    // {
    //     return;
    // }

    if (root == NULL)
    {
        return;
    }

    // Print left-side, this node, than right-side
    printNodeTree(root->left, depth + 1);

    // Print spaces before each node to be visual-friendly
    for (int i = 0; i < depth; i++)
    {
        // 3 spaces for each
        printf("%s", "   ");
    }
    printf("<%s>\n", root->name);

    printNodeTree(root->right, depth + 1);

    // printf("%s type %d: <%s>\n", prefix, root->type, root->name);

    num++;
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