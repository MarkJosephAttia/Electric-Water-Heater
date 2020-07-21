/**
 * @file Std_Types.h
 * @author Mark Attia (markjosephattia@gmail.com)
 * @brief The Standard Types
 * @version 0.1
 * @date 2020-07-05
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef STD_TYPES_H
#define STD_TYPES_H

#define NULL                            ((void*)0)

typedef unsigned char                   u8;
typedef unsigned char                   uint8_t;
typedef signed char                     s8;
typedef signed char                     sint8_t;
typedef unsigned       int              u16;
typedef unsigned       int              uint16_t;
typedef signed short int                s16;
typedef signed short int                sint16_t;
typedef unsigned long int               u32;
typedef unsigned long int               uint32_t;
typedef signed long int                 s32;
typedef signed long int                 sint32_t;
typedef unsigned long long int          u64;
typedef unsigned long long int          uint64_t;
typedef signed long long int            s64;
typedef signed long long int            sint64_t;

typedef float                           f32;
typedef float                           float32_t;
typedef double                          f64;
typedef double                          float64_t;

typedef uint8_t Std_ReturnType;

#define E_OK                            (0)
#define E_NOT_OK                        (1)

#define STD_LOW                         (0)
#define STD_HIGH                        (1)

#define STD_IDLE                        (0)
#define STD_ACTIVE                      (1)

#define STD_OFF                         (0)
#define STD_ON                          (1)

#endif