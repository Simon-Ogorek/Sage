#include "shared_types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Function_Status get_filename_ext(const char *filename, char *rtr) 
{
    rtr = strrchr(filename, '.');
    if (!strcmp(rtr, filename) || rtr == NULL) 
    {
        printf("Can't parse out file extension\n");
        return ERROR;
    }
    rtr++;
    return SUCCESS;
}