#pragma once

#include <stdlib.h>
#include <stdint.h>

#define New(type) (type *)malloc(sizeof(type))

#define NewArray(type, size) (type *)malloc(sizeof(type) * size)

#define Delete(object)  \
    if (object != NULL) \
        free(object);   \
    object = NULL

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float f16;
typedef double f32;
typedef long double f64;
