#pragma once

#include "shared_types.h"

#include "hashmap.h"

typedef struct HashMap
{
    void *data;

    int count;
    int size;
} HashMap;

Function_Status HashMap_Create(HashMap *rtr);
Function_Status HashMap_Create_Size(int size, HashMap *rtr);

Function_Status Hashmap_Insert(HashMap *hashmap, void *data);

Function_Status Hashmap_Delete(HashMap *hashmap, void *data);

Function_Status Hashmap_Contains(HashMap *hashmap, void *data, Bool *rtr);

Function_Status Hashmap_Free(HashMap *hashmap);