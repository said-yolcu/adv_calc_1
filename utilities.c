
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "definitions.h"

// Print node tree in reverse (root at the bottom)
void printNodeTree(Node *root, int depth)
{
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

// Parse assignment. Return true if it is indeed an assignment, false otherwise
bool checkAsg(Token *head)
{
    // If it is an assignment statement
    if (head != NULL && head->this != NULL && head->this->type == VAR &&
        head->next != NULL && head->next->this != NULL &&
        head->next->this->type == ASG)
    {
        return true;
    }

    return false;
}

void printVariables(Variable *first)
{
    if (first == NULL)
    {
        return;
    }

    printf("Variable with name <%s> has value <%ld>\n",
           first->name, first->value);

    printVariables(first->next);
}

void error()
{
    printf("Error!\n");
}