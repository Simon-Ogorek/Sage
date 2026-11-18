#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Function_Status List_Create(List *rtr)
{
    return List_Create_Size(DEFAULT_CONTAINER_SIZE, rtr);
}

Function_Status List_Create_Size(int size, List *rtr)
{
    if (size <= 0)
    {
        printf("Can't make a list of zero size or less\n");
        return ERROR;
    }
    rtr = (List *)calloc(1, sizeof(List));

    if (!rtr)
    {
        printf("Failed to allocate a new list\n");
        return ERROR;
    }
     
    rtr->data = calloc(size, sizeof(void *));

    if (!rtr->data)
    {
        free(rtr);
        rtr = NULL;
        printf("Failed to allocate the data of a new list\n");
        return ERROR;
    }

    rtr->size = size;
    rtr->count = 0;

    return SUCCESS;
}

Function_Status List_Expand_By_Scale(List *list, float scale)
{
    if (IS_FAILURE(Validate_List(list)))
        return ERROR;

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
    if (IS_FAILURE(Validate_List(list)))
        return ERROR;

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
    if (IS_FAILURE(Validate_List(list)))
        return ERROR;

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
    if (IS_FAILURE(Validate_List(list)))
        return ERROR;

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
    if (IS_FAILURE(Validate_List(list)))
        return ERROR;

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

Function_Status List_Get_Reference(List *list, void *data, int *rtr)
{
    if (IS_FAILURE(Validate_List(list)))
        return ERROR;

    int i = 0;
    void *comparison;

    for (; i < list->size; i++)
    {
        comparison = list->data[i];
        if (comparison == data)
        {
            *rtr = i;
            return SUCCESS;
        }
    }

    *rtr = NOT_FOUND;
    return SUCCESS;
}

Function_Status List_Delete(List *list, void *data)
{
    if (IS_FAILURE(Validate_List(list)))
        return ERROR;

    int index;
    Function_Status status = List_Get_Reference(list, data, &index);

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
    if (IS_FAILURE(Validate_List(list)))
        return ERROR;

    int index;
    List_Get_Reference(list, data, &index);

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
    if (IS_FAILURE(Validate_List(list)))
        return ERROR;

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
    if (IS_FAILURE(Validate_List(list)))
        return ERROR;

    memset(list->data, 0, list->size * sizeof(void *));

    return SUCCESS;
}

Function_Status List_Free(List *list)
{
    if (IS_FAILURE(Validate_List(list)))
        return ERROR;

    free(list->data);
    free(list);

    return SUCCESS;
}

Function_Status Validate_List(List *list)
{
    Bool not_null = list != NULL;
    Bool initialized = not_null && list->data && list->size > 0;
    Bool is_sane = not_null && list->count <= list->size;

    if (not_null && initialized && is_sane)
    {
        return SUCCESS;
    }

    if (!not_null)
    {
        printf("List is null\n");
        return ERROR;
    }

    if (!initialized)
        printf("List is not initialized\n");

    if (!is_sane)
        printf("List has a count higher than its size\n");

    return ERROR;
}