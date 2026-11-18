#pragma once

#include <stdint.h>

#define DEFAULT_CONTAINER_SIZE 32

#define NOT_FOUND -1

#define IS_SUCCESSFUL(X) ( (X) == 0 )
#define IS_FAILURE(X) ((X) > 0)

typedef char Bool;

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

Function_Status get_filename_ext(const char *filename, char *rtr);