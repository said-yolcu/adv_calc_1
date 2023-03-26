#ifndef DESTRUCTURE_H
#define DESTRUCTURE_H

#include "definitions.h"

int tokenize(Token *head, char *line, int begin);
Node *parse(Token *tail, int startLayer, int maxLayer, int until);
long calculate(Node *root);

#endif