
#include <stdlib.h>

#include "definitions.h"

void freeNodeStorage(Node *root);

// The structure of these functions need to be changed, because the nodes will
// finally be collected under a single Token

void freeTokenStorage(Token *head)
{
    if (head != NULL && head->next != NULL)
    {
        // Free the succeeding Tokens
        freeTokenStorage(head->next);
    }

    if (head != NULL)
    {
        // Free this node tree
        // freeNodeStorage(head->this);
        free(head->this);

        // Free "head" token
        free(head);
    }
}

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
}