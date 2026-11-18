#include "tri.h"

#include <stdio.h>

Function_Status Print_Tri(void *data)
{
    if (!data)
        return ERROR;

    Tri *temp = (Tri*)data;
    printf("[ %i/%i/%i | %i/%i/%i | %i/%i/%i ]\n",
        (*temp)[0],(*temp)[1],(*temp)[2],
        (*temp)[3],(*temp)[4],(*temp)[5],
        (*temp)[6],(*temp)[7],(*temp)[8]);

    return SUCCESS;
}
