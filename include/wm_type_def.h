/**
 * @file    wm_type_def.h
 *
 * @brief   WM type redefine
 *
 * @author  winnermicro
 *
 * Copyright (c) 2015 Winner Microelectronics Co., Ltd.
 */
#ifndef __WM_TYPE_DEF_H__
#define __WM_TYPE_DEF_H__

#include <stdint.h>
#include <stdbool.h>

// 8bit
typedef uint8_t u8;
typedef uint8_t u8_t;
typedef uint8_t u_char;
typedef uint8_t INT8U;
typedef int8_t s8;
typedef int8_t s8_t;
typedef int8_t INT8S;
typedef int8_t err_t;

// 16bit
typedef uint16_t u16;
typedef uint16_t u16_t;
typedef uint16_t uint16;
typedef int16_t s16;
typedef int16_t s16_t;
typedef int16_t int16;

// 32bit
typedef uint32_t u32;
typedef uint32_t u32_t;
typedef uint32_t uint32;
typedef uint32_t mem_ptr_t;
typedef int32_t s32;
typedef int32_t s32_t;
typedef int32_t int32;

// 64bit
typedef uint64_t u64;
typedef int64_t s64;

// #ifdef bool
// #undef bool
// #endif
// #ifdef u8
// #undef u8
// #endif
// #ifdef s8
// #undef s8
// #endif
// #ifdef u16
// #undef u16
// #endif
// #ifdef s16
// #undef s16
// #endif
// #ifdef u32
// #undef u32
// #endif
// #ifdef s32
// #undef s32
// #endif
// #ifdef u64
// #undef u64
// #endif
// #ifdef s64
// #undef s64
// #endif

// #ifdef u_char
// #undef u_char
// #endif
// typedef unsigned char u_char;

// #ifdef INT8U
// #undef INT8U
// #endif
// typedef unsigned char INT8U;

// #ifdef INT8S
// #undef INT8S
// #endif
// typedef signed char INT8S;

// typedef unsigned char        bool;
// typedef unsigned char        u8;
// typedef signed char          s8;
// typedef unsigned short       u16;
// typedef signed short         s16;
// typedef unsigned int         u32;
// typedef signed int           s32;
// typedef unsigned long long   u64;
// typedef long long                    s64;

// #if defined(_NEWLIB_VERSION_H__)
// #ifdef int32_t
// #undef int32_t
// typedef int int32_t;
// #endif

// #ifdef uint32_t
// #undef uint32_t
// typedef unsigned int uint32_t;
// #endif
// #endif

// #if defined(__MINILIBC__)
// typedef int int32_t;
// typedef unsigned int uint32_t;
// #endif

// #ifdef int32
// #undef int32
// #endif
// typedef int int32;

// #ifdef uint32
// #undef uint32
// #endif
// typedef unsigned int uint32;

// #ifdef int16
// #undef int16
// #endif
// typedef short  int16;

// #ifdef uint16
// #undef uint16
// #endif
// typedef unsigned short  uint16;

#ifdef ULONG
#undef ULONG
#endif
typedef unsigned long ULONG;

// #ifdef u8_t
// #undef u8_t
// #endif
// typedef unsigned char u8_t;

// #ifdef uint8_t
// #undef uint8_t
// #endif
// typedef unsigned char uint8_t;

// #ifdef u16_t
// #undef u16_t
// #endif
// typedef unsigned short u16_t;

// #ifdef uint16_t
// #undef uint16_t
// #endif
// typedef unsigned short uint16_t;

// #ifdef u32_t
// #undef u32_t
// #endif
// typedef unsigned int u32_t;


// #ifdef s8_t
// #undef s8_t
// #endif
// typedef signed char s8_t;

// #ifdef s16_t
// #undef s16_t
// #endif
// typedef signed short s16_t;

// #ifdef s32_t
// #undef s32_t
// #endif
// typedef signed int s32_t;
// #if (GCC_COMPILE==0)
// #ifdef size_t
// #undef size_t
// #endif
// typedef unsigned int size_t;
// #endif

// #ifdef err_t
// #undef err_t
// #endif
// typedef signed char err_t;


// #ifdef mem_ptr_t
// #undef mem_ptr_t
// #endif
// typedef unsigned int mem_ptr_t;

#ifdef  TRUE
#undef  TRUE
#endif
#define TRUE                     1

#ifdef  FALSE
#undef  FALSE
#endif
#define FALSE                    0

// #define true				1
// #define false				0

#define WM_SUCCESS               0
#define WM_FAILED               -1

#ifndef IGNORE_PARAMETER
#define IGNORE_PARAMETER(x)     ((x) = (x))
#endif

#endif
