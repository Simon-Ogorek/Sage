#include "hashmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Function_Status HashMap_Create(HashMap *rtr)
{
    return HashMap_Create_Size(DEFAULT_CONTAINER_SIZE, rtr);
}

Function_Status HashMap_Create_Size(int size, HashMap *rtr)
{
    rtr = (HashMap *)calloc(1, sizeof(HashMap));
    rtr->size = size;

    return SUCCESS;
}

Function_Status Hashmap_Insert(HashMap *hashmap, void *data);

Function_Status Hashmap_Delete(HashMap *hashmap, void *data);

Function_Status Hashmap_Contains(HashMap *hashmap, void *data, Bool *rtr);

Function_Status Hashmap_Free(HashMap *hashmap)
{
    if (hashmap)
    {
        printf("Tried to free null Hashmap");
        return ERROR;
    }

    if (hashmap->data)
    {
        free(hashmap->data);
    }
    else
    {
        printf("Double free on hashmap attempted");
        return ERROR;
    }

    free(hashmap);

    return 0;
}