#pragma once

#include "shared_types.h"

typedef struct Model
{
    int hash;
    int assigned_index;
    
    List *positions;
    List *normals;

    List *texels;
    
    List *tris;

    int ref_count;
} Model;


int Initialize_Models();
int Model_Create(char *filepath);
int Model_Inspect(Model *model);