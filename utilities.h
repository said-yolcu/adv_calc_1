#ifndef UTILITIES_H
#define UTILITIES_H

#include <string.h>

#include "definitions.h"

void printNodeTree(Node *root, int depth);
int max(int a, int b);
bool checkAsg(Token *head);
void printVariables(Variable *first);

#endif