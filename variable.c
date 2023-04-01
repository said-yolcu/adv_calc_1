
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

// Set the variable with name as *varName* with value *value*
Variable *setVariable(Variable *first, char *varName, long value)
{
    Variable *curr;

    // Iterate over variables
    for (curr = first; curr != NULL && curr->next != NULL; curr = curr->next)
    {
        // Variable with the same name already exists
        if (strcmp(curr->name, varName) == 0)
        {
            curr->value = value;
            return first;
        }
    }

    // Last variable is certainly empty
    if ( strcmp(curr->name, "") == 0)
    {
        // Set the name and value
        strcpy(curr->name, varName);
        curr->value = value;

        // Set the next variable as empty
        curr->next = (Variable *)malloc(sizeof(Variable));
        strcpy(curr->next->name,"");
        curr->next->next=NULL;
        return first;
    }
}

long getVariable(Variable *first, char *varName)
{
    Variable *curr;

    for (curr = first; curr != NULL; curr = curr->next)
    {
        if (strcmp(curr->name, varName) == 0)
        {
            return curr->value;
        }
    }
    // Undefined variables are 0
    return 0;
}
