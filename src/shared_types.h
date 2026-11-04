#pragma once

#define DEFAULT_CONTAINER_SIZE 32

#define IS_SUCCESSFUL(X) ( (X) == 0 )
#define IS_FAILURE(X) ((X) > 0)

typedef enum Resource_Status 
{
    READY,
    INACTIVE,
    FREE
} Resource_Status;

typedef enum Function_Status
{
    SUCCESS,
    ERROR,
    MEMORY_FAIL
} Function_Status;

typedef enum Search_Status
{
    FOUND,
    NOT_FOUND
} Search_Status;

typedef float Vector2[2];
typedef float Vector3[3];
typedef float Vector4[4];
 
typedef int Tri[9];

const char *get_filename_ext(const char *filename);

typedef void * ListElement;
typedef struct List
{
    ListElement *data;

    int count;
    int size;
} List;

typedef struct HashMap
{
    void *data;

    int count;
    int size;
} HashMap;


Function_Status Print_Vector_3(void *data);
Function_Status Print_Vector_2(void *data);
Function_Status Print_Tri(void *data);

/**
 * @brief Allocates a list of size DEFAULT_CONTAINER_SIZE
 * @return A List struct or NULL on failure
 */
List *List_Create();

/**
 * @brief Allocates a list of a defined size
 * @param size The starting size of the list
 * @return A List struct or NULL on failure
 */
List *List_Create_Size(int size);

/**
 * @brief Expands a list by a percentage scale factor
 * @param list The list to be expanded
 * @param scale The percentage scale
 * @return A function status
 * @note Percentages that reduce size or don't affect 
 * the size result in errors
 */
Function_Status List_Expand_By_Scale(List *list, float scale);
/**
 * @brief Expands a list to a specified size
 * @param list The list to be expanded
 * @param new_size The new desired size
 * @return A function status
 * @note Sizes that reduce size or are the
 * current size result in errors
 */
Function_Status List_Expand_By_Count(List *list, int new_size);

/**
 * @brief Adds a element to the end of the list
 * @param list The list the value is to be inserted into
 * @param data The new list element
 * @return A function status
 * @note Lists may be expanded to accomodate new element
 */
Function_Status List_Append(List *list, void *data);
/**
 * @brief Adds a element to the first empty element
 * @param list The list the value is to be inserted into
 * @param data The new list element
 * @param rtr The resulting index
 * @return A function status
 * @note Lists may be expanded to accomodate new element
 * if there are no empty places
 * @note If you don't care about the rtr value use List_Throw
 */
Function_Status List_Place(List *list, void *data, int *rtr);
/**
 * @brief Adds a element to the first empty element
 * @param list The list the value is to be inserted into
 * @param data The new list element
 * @return A function status
 * @note Lists may be expanded to accomodate new element
 * if there are no empty places
 * @note If you want to know the resulting index use List_Place
 */
Function_Status List_Throw(List *list, void *data);
/**
 * @brief Adds a element to the start of the list
 * @param list The list the value is to be inserted into
 * @param data The new list element
 * @return A function status
 * @note Lists may be expanded to accomodate new element
 */
Function_Status List_Prepend(List *list, void *data);
/**
 * @brief Adds a element to the index by moving conflicting
 * elements to the right of the value
 * @param list The list the value is to be inserted into
 * @param data The new list element
 * @param index The index where the element should be positioned
 * @return A function status
 * @note Lists may be expanded to accomodate new element
 */
Function_Status List_Insert(List *list, void *data, int index);
/**
 * @brief Adds a element to the index by replacing the value
 * at the specified index
 * @param list The list the value is to be replaced into
 * @param data The new list element
 * @param index The index where the element should be positioned
 * @return A function status
 * @note Lists may be expanded to accomodate new element
 */
Function_Status List_Replace(List *list, void *data, int index);

/**
 * @brief Returns the first matching reference by index
 * @param list The list thats searched
 * @param data The value to compare
 * @return A non negative integer if found, -1 otherwise
 */
int List_Get_Reference(List *list, void *data);
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
int List_Get_Value(List *list, void *data);

Function_Status List_Delete(List *list, void *data);
Function_Status List_Delete_Index(List *list, void *data);

Function_Status List_For_Each(List *list, Function_Status (*function) (void *));
Function_Status List_Clear(List *list);
Function_Status List_Free(List *list);

HashMap *HashMap_Create();
HashMap *HashMap_Create_Size(int size);

int Hashmap_Insert(HashMap *hashmap, void *data);

int Hashmap_Delete(HashMap *hashmap, void *data);

int Hashmap_Contains(HashMap *hashmap, void *data);

int Hashmap_Free(HashMap *hashmap);

