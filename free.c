
#include <stdlib.h>

#include "definitions.h"

void freeNodeStorage(Node *root);

// Free Token linked list
void freeTokenStorage(Token *head)
{
    if (head == NULL)
    {
        return;
    }

    // Free the succeeding Tokens
    freeTokenStorage(head->next);

    // Free this node tree
    free(head->this);

    // Free "head" token
    free(head);

    head = NULL;
}

// Free Node tree
void freeNodeStorage(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    // Free the left branch
    freeNodeStorage(root->left);

    // Free the right branch
    freeNodeStorage(root->right);

    // Free "root"
    free(root);

    root = NULL;
}

// Free variable linked list
void freeVariables(Variable *first)
{
    if (first == NULL)
    {
        return;
    }

    // Free succeeding variables
    freeVariables(first->next);

    // Then, free this variable
    free(first);

    // Do not let any dangling pointer
    first = NULL;
}