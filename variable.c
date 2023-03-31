
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"

// Set the variable with name as *varName* with value *value*
Variable *setVariable(Variable *first, char *varName, long value)
{
    Variable *curr;

    // printf("Variable.c line 13 %s\n", "");

    // Iterate over variables
    for (curr = first; curr != NULL && curr->next != NULL; curr = curr->next)
    {
        // printf("Variable.c line 18 %s\n", "");

        // Variable with the same name already exists
        if (strcmp(curr->name, varName) == 0)
        {
            // printf("Variable.c line 23 %s\n", "");

            curr->value = value;
            return first;
        }
    }

    // Last variable is certainly empty
    if ( strcmp(curr->name, "") == 0)
    {
        // printf("Variable.c line 32 %s\n", "");

        // Set the name and value
        strcpy(curr->name, varName);
        curr->value = value;

        // Set the next variable as empty
        curr->next = (Variable *)malloc(sizeof(Variable));
        strcpy(curr->next->name,"");
        curr->next->next=NULL;
        return first;
    }

    // printf("variable.c line 39 %s\n", "");

    // printf("curr->name: <%s>, varName: <%s>\n", curr->name, varName);

    // // Came to the end of the list, we must put the variable here
    // // Create storage for the variable and fill the fields
    // curr->next = (Variable *)malloc(sizeof(Variable));
    // curr = curr->next;
    // strcpy(curr->name, varName);
    // curr->value = value;
    // curr->next = NULL;

    // return first;
}

long getVariable(Variable *first, char *varName)
{
    Variable *curr;

    // printf("Variable.c line 49 %s\n", "");
    for (curr = first; curr != NULL; curr = curr->next)
    {
        // printf("Variable.c line 52 %s\n", "");
        // printf("variable.c curr->name: %s, varName: %s\n", curr->name, varName);

        if (strcmp(curr->name, varName) == 0)
        {
            // printf("Variable.c line 57 %s\n", "");
            return curr->value;
        }
    }
    // Undefined variables are 0
    return 0;
}
