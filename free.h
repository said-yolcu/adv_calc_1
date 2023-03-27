#ifndef FREE_H
#define FREE_H

#include "definitions.h"

void freeTokenStorage(Token *head);
void freeNodeStorage(Node *root);
void freeVariables(Variable *first);

#endif