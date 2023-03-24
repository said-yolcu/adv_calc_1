#ifndef DESTRUCTURE_H
#define DESTRUCTURE_H

#include "definitions.h"

void tokenize(Token *head, char *line, int begin);
Node *parse(Token *tail, int startLayer, int maxLayer, int until);
void printNodeTree(Node *root, char *prefix);

#endif