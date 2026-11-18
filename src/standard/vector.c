#include "vector.h"

#include <stdio.h>
Function_Status Print_Vector_3(void *data)
{
    if (!data)
        return ERROR;

    Vector3 *temp = (Vector3*)data;
    printf("[ %f,%f,%f ]\n", (*temp)[0], (*temp)[1], (*temp)[2]);

    return SUCCESS;
}

Function_Status Print_Vector_2(void *data)
{
    if (!data)
        return ERROR;

    Vector2 *temp = (Vector2*)data;
    printf("[ %f,%f ]\n", (*temp)[0], (*temp)[1]);

    return SUCCESS;
}