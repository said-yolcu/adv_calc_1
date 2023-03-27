#ifndef VARIABLE_H
#define VARIABLE_H

#include "definitions.h"

Variable *setVariable(Variable *first, char *varName, long value);
long getVariable(Variable *first, char *varName);

#endif