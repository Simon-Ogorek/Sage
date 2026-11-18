#pragma once

#include "shared_types.h"

typedef void * ListElement;
typedef struct List
{
    ListElement *data;

    int count;
    int size;
} List;

/**
 * @brief Allocates a list of size DEFAULT_CONTAINER_SIZE
 */
Function_Status List_Create(List *rtr);

/**
 * @brief Allocates a list of a defined size
 * @param size The starting size of the list
 */
Function_Status List_Create_Size(int size, List *rtr);

/**
 * @brief Expands a list by a percentage scale factor
 * @param list The list to be expanded
 * @param scale The percentage scale
 * @note Percentages that reduce size or don't affect 
 * the size result in errors
 */
Function_Status List_Expand_By_Scale(List *list, float scale);
/**
 * @brief Expands a list to a specified size
 * @param list The list to be expanded
 * @param new_size The new desired size
 * @note Sizes that reduce size or are the
 * current size result in errors
 */
Function_Status List_Expand_By_Count(List *list, int new_size);

/**
 * @brief Adds a element to the end of the list
 * @param list The list the value is to be inserted into
 * @param data The new list element
 * @note Lists may be expanded to accomodate new element
 */
Function_Status List_Append(List *list, void *data);
/**
 * @brief Adds a element to the first empty element
 * @param list The list the value is to be inserted into
 * @param data The new list element
 * @param rtr The resulting index
 * @note Lists may be expanded to accomodate new element
 * if there are no empty places
 * @note If you don't care about the rtr value use List_Throw
 */
Function_Status List_Place(List *list, void *data, int *rtr);
/**
 * @brief Adds a element to the first empty element
 * @param list The list the value is to be inserted into
 * @param data The new list element
 * @note Lists may be expanded to accomodate new element
 * if there are no empty places
 * @note If you want to know the resulting index use List_Place
 */
Function_Status List_Throw(List *list, void *data);
/**
 * @brief Adds a element to the start of the list
 * @param list The list the value is to be inserted into
 * @param data The new list element
 * @note Lists may be expanded to accomodate new element
 */
Function_Status List_Prepend(List *list, void *data);
/**
 * @brief Adds a element to the index by moving conflicting
 * elements to the right of the value
 * @param list The list the value is to be inserted into
 * @param data The new list element
 * @param index The index where the element should be positioned
 * @note Lists may be expanded to accomodate new element
 */
Function_Status List_Insert(List *list, void *data, int index);
/**
 * @brief Adds a element to the index by replacing the value
 * at the specified index
 * @param list The list the value is to be replaced into
 * @param data The new list element
 * @param index The index where the element should be positioned
 * @note Lists may be expanded to accomodate new element
 */
Function_Status List_Replace(List *list, void *data, int index);

/**
 * @brief Returns the first matching reference by index
 * @param list The list thats searched
 * @param data The value to compare
 * @return A non negative integer if found, -1 otherwise
 */
Function_Status List_Get_Reference(List *list, void *data, int *rtr);
/**
 * @brief Returns the first matching value by index
 * @param list The list thats searched
 * @param data The value to compare
 * @param comparitor Comparison function
 * @return A non negative integer if found, -1 otherwise
 * @note The comparison function should work on the
 * assumption of struct consistency only if the 
 * user adheres to it.
 */

Function_Status List_Get_Value(List *list, void *data, int *rtr);

Function_Status List_Delete(List *list, void *data);
Function_Status List_Delete_Index(List *list, void *data);

Function_Status List_For_Each(List *list, Function_Status (*function) (void *));
Function_Status List_Clear(List *list);
Function_Status List_Free(List *list);

Function_Status Validate_List(List *list);