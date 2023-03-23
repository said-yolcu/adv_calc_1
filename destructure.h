#ifndef DESTRUCTURE_H
#define DESTRUCTURE_H

#include "definitions.h"

void tokenize(Token *head, char *line, int begin);
Node *parse(Token *head, int maxLayer, int until);

#endif