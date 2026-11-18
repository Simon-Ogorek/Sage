#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shared_types.h"
#include "types/obj.h"
#include "standard/tri.h"
#include "standard/vector.h"

#define INIT_SIZE 128

struct Model_Manager
{
    List *models;
} Model_Manager;

static struct Model_Manager model_manager;

int Initialize_Models()
{
    int i;
    Model *temp;

    List_Create_Size(INIT_SIZE, model_manager.models);

    for (i = 0; i < INIT_SIZE; i++)
    {
        temp = (Model *)calloc(1,sizeof(Model));

        if (temp)
        {
            if(IS_FAILURE(List_Append(model_manager.models, temp)))
            {
                printf("Could not complete initialization of Models\n");
                return ERROR;
            }
        }
        else
        {
            printf("Failed to allocate for initialization of Models\n");
            return MEMORY_FAIL;
        }
    }
    return SUCCESS;
}

Model *Get_Unused_Model()
{
    int i;
    Model *temp;

    if (!model_manager.models)
    {
        printf("Models have not been initialized\n");
        return NULL;
    }
    for (i = 0; i < model_manager.models->size; i++)
    {
        temp = (Model *)model_manager.models->data[i];

        if (!temp)
            continue;
        
        if (temp->ref_count == 0)
        {
            temp->ref_count++;
            return temp;
        }
    }
    return NULL;

}

int Model_Create(char *filepath)
{
    Function_Status status;
    Model *model = Get_Unused_Model();

    if (!model)
    {
        printf("Failed to get a Model reference");
        return MEMORY_FAIL;
    }

    List_Create(model->positions);
    List_Create(model->normals);
    List_Create(model->texels);
    List_Create(model->tris);

    if (!model->positions || !model->normals || !model->texels || !model->tris)
    {
        printf("List creation error when creating model");
        return ERROR;
    }

    if (!filepath)
    {
        printf("Can't create a model based on a null path");
        return ERROR;
    }

    char *extension;
    get_filename_ext(filepath, extension);
    printf("Got model ext: %s from %s\n", extension, filepath);
    if (!strcmp(extension, "obj"))
    {
        status = OBJ_Parse(filepath, model);
    }
    else
    {
        printf("Invalid file arguement");
        return ERROR;
    }

    if (IS_FAILURE(status))
    {
        printf("Models failed to parse");
        return ERROR;
    }

    if (IS_FAILURE(Model_Inspect(model)))
        return ERROR;
    
    return SUCCESS;
}

int Model_Free(Model *model)
{
    if (!model)
    {
        printf("Can't free a null model refernce");
        return ERROR;
    }

    if (model->positions)
        List_Free(model->positions);
    if (model->normals)
        List_Free(model->normals);
    if (model->texels)
        List_Free(model->positions);
    if (model->tris)
        List_Free(model->tris);

    return SUCCESS;
}

int Model_Inspect(Model *model)
{
    printf("* Positions *\n");
    if (IS_FAILURE(List_For_Each(model->positions, &Print_Vector_3)))
        return ERROR;

    printf("* Texels *\n");
    if (IS_FAILURE(List_For_Each(model->texels, &Print_Vector_2)))
        return ERROR;

    printf("* Normals *\n");
    if (IS_FAILURE(List_For_Each(model->normals, &Print_Vector_3)))
        return ERROR;

    printf("* Tris *\n");
    if (IS_FAILURE(List_For_Each(model->tris, &Print_Tri)))
        return ERROR;
}