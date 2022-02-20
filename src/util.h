#pragma once

#include <stdlib.h>

#define New(type) (type *)malloc(sizeof(type))
#define NewArray(type, size) (type *)malloc(sizeof(type) * size)
#define Delete(object)  \
    if (object != NULL) \
        free(object);   \
    object = NULL
