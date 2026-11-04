#include "shared_types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if (!dot || dot == filename) 
    {
        return "";
    }
    return dot + 1;
}

List *List_Create()
{
    return List_Create_Size(DEFAULT_CONTAINER_SIZE);
}

List *List_Create_Size(int size)
{
    List *newList = (List *)calloc(1, sizeof(List));
    if (!newList)
    {
        printf("Failed to allocate a new list\n");
        return NULL;
    }
     
    newList->data = calloc(size, sizeof(void *));

    if (!newList->data)
    {
        printf("Failed to allocate the data of a new list\n");
        return NULL;
    }

    newList->size = size;
    newList->count = 0;

    return newList;
}

Function_Status List_Expand_By_Scale(List *list, float scale)
{
    int new_size;

    if (scale <= 1.0)
    {
        printf("List can't be expanded with a arguement that shrinks it");
        return ERROR;
    }

    if ((int)(list->size * scale) == list->size)
    {
        printf("List expansion netted no gains in size");
        return ERROR;
    }

    new_size = (int)(list->size * scale);
    list->data = realloc(list->data, new_size);

    if (list->data)
    {
        list->size = new_size;
        return SUCCESS;
    }
    else
    {
        printf("List expansion failed due to a allocation fail");
        new_size = 0;
        return MEMORY_FAIL;
    }
}

Function_Status List_Expand_By_Count(List *list, int new_size)
{
    if (new_size < list->size)
    {
        printf("List can't be expanded with a arguement that shrinks it");
        return ERROR;
    }

    list->data = realloc(list->data, new_size);

    if (list->data)
    {
        list->size = new_size;
        return SUCCESS;
    }
    else
    {
        printf("List expansion failed due to a allocation fail");
        list->size = 0;
        return MEMORY_FAIL;
    }
}

Function_Status List_Append(List *list, void *data)
{
    return List_Replace(list, data, list->count);
}

Function_Status List_Prepend(List *list, void *data)
{
    return List_Insert(list, data, 0);
}

Function_Status List_Insert(List *list, void *data, int index)
{
    if (!list || !list->data)
    {
        printf("Can't insert into a unitialized list");
        return ERROR;
    }

    if (index < 0)
    {
        printf("Can't index a list with a negative index");
        return ERROR;
    }

    if (list->size <= index)
    {
        if (IS_FAILURE(List_Expand_By_Count(list, list->size * 2)))
        {
            return ERROR;
        }
    }

    void *tempA = list->data[index];

    void *tempB;

    for (int i = index + 1; i < list->size && list->data[i]; i++)
    {
        tempB = list->data[i];
        list->data[i] = tempA;
        tempA = tempB;
    }

    list->data[index] = data;


    list->count++;

    return SUCCESS;
}

Function_Status List_Place(List *list, void *data, int *rtr)
{
    if (!list || !list->data)
    {
        printf("Can't place into a unitialized list");
        return ERROR;
    }

    if (list->size <= list->count)
    {
        if (IS_FAILURE(List_Expand_By_Scale(list, 2)))
        {
            printf("Failed to expand list");
            return ERROR;
        }
    }

    void *temp;
    int i;

    for (i = 0; i < list->size; i++)
    {
        temp = list->data[i];

        if (!temp)
        {
            list->data[i] = data;
            if (rtr)
            {
                *rtr = i;
            }
            else
            {
                printf("Suggestion: NULL ptr on return value, use List_Throw instead");
            }
            return SUCCESS;
        }
    }
    printf("List may be corrupted, List_Place fail");
    return ERROR;
}

Function_Status List_Throw(List *list, void *data)
{
    if (!list || !list->data)
    {
        printf("Can't throw into a unitialized list");
        return ERROR;
    }

    if (list->size <= list->count)
    {
        List_Expand_By_Scale(list, 2);
    }

    void *temp;
    int i;

    for (i = 0; i < list->size; i++)
    {
        temp = list->data[i];

        if (!temp)
        {
            list->data[i] = data;
            return SUCCESS;
        }
    }
    printf("List may be corrupted, List_Throw fail");
    return ERROR;
}

Function_Status List_Replace(List *list, void *data, int index)
{
    if (!list || !list->data)
    {
        printf("Can't replace into a unitialized list");
        return ERROR;
    }

    if (index < 0)
    {
        printf("Can't index a list with a negative index");
        return ERROR;
    }

    if (list->size <= index)
    {
        if (IS_FAILURE(List_Expand_By_Count(list, index + 1)))
        {
            return ERROR;
        }
    }

    
    list->data[index] = data;

    list->count++;

    return SUCCESS;
}

int List_Get_Reference(List *list, void *data)
{
    int i = 0;
    void *comparison;

    for (; i < list->size; i++)
    {
        comparison = list->data[i];
        if (comparison == data)
        {
            return i;
        }
    }

    return NOT_FOUND;
}

Function_Status List_Delete(List *list, void *data)
{
    int index = List_Get_Reference(list, data);
    if (index != NOT_FOUND)
    {
        list->data[index] = NULL;
        list->count--;
        return SUCCESS;
    }
    else
    {
        printf("Value does not exist for deletion");
        return ERROR;
    }
}

Function_Status List_Delete_Index(List *list, void *data)
{
    int index = List_Get_Reference(list, data);
    if (index != NOT_FOUND)
    {
        list->data[index] = NULL;
        return SUCCESS;
    }
    else
    {
        printf("Value does not exist for deletion");
        return ERROR;
    }
}

Function_Status List_For_Each(List *list, Function_Status (*function) (void *))
{
    void *temp;
    for (int i = 0; i < list->size; i++)
    {
        temp = list->data[i];
        if (temp)
        {
            if (IS_FAILURE(function(temp)))
            {
                return ERROR;
            }
        }
    }
    return SUCCESS;
}

Function_Status List_Clear(List *list)
{
    if (!list || !list->data)
    {
        printf("Unitialized list can't be cleared");
        return ERROR;
    }

    memset(list->data, 0, list->size * sizeof(void *));

    return SUCCESS;
}

Function_Status List_Free(List *list)
{
    if (!list)
    {
        printf("Tried to free null List");
        return ERROR;
    }

    if (list->data)
    {
        free(list->data);
    }
    else
    {
        printf("Double free on list attempted");
        return ERROR;
    }

    free(list);

    return SUCCESS;
}

HashMap *HashMap_Create()
{
    return HashMap_Create_Size(DEFAULT_CONTAINER_SIZE);
}

HashMap *HashMap_Create_Size(int size)
{
    HashMap *newHashMap = (HashMap *)calloc(1, sizeof(HashMap));
    newHashMap->size = size;

    return newHashMap;
}

int Hashmap_Insert(HashMap *hashmap, void *data)
{
}

int Hashmap_Delete(HashMap *hashmap, void *data)
{
}

int Hashmap_Contains(HashMap *hashmap, void *data)
{
}

int Hashmap_Free(HashMap *hashmap)
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