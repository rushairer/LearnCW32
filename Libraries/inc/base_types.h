
#ifndef __BASE_TYPES_H
#define __BASE_TYPES_H

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>


/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/
#ifndef TRUE
    /** Value is true (boolean_t type) */
    #define TRUE        ((boolean_t) 1u)
#endif

#ifndef FALSE
    /** Value is false (boolean_t type) */
    #define FALSE       ((boolean_t) 0u)
#endif

/** Returns the minimum value out of two values */
#define MINIMUM(X, Y)  ((X) < (Y) ? (X) : (Y))

/** Returns the maximum value out of two values */
#define MAXIMUM(X, Y)  ((X) > (Y) ? (X) : (Y))

/** Returns the dimension of an array */
#define ARRAY_SZ(X)  (sizeof(X) / sizeof((X)[0]))

#ifdef __DEBUG_ASSERT
    #define ASSERT(x) do{ assert((x)> 0u) ; }while(0);
#else
    #define ASSERT(x) {}
#endif
/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/** logical datatype (only values are TRUE and FALSE) */
typedef uint8_t      boolean_t;

/** single precision floating point number (4 byte) */
typedef float        float32_t;

/** double precision floating point number (8 byte) */
typedef double       float64_t;

/** ASCII character for string generation (8 bit) */
typedef char         char_t;

/** function pointer type to void/void function */
typedef void (*func_ptr_t)(void);

/** function pointer type to void/uint8_t function */
typedef void (*func_ptr_arg1_t)(uint8_t u8Param);

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;
/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source)           */
/*****************************************************************************/



#define bv(n)                                   ((uint32_t)1u << (n))

#define bv0                                     (((uint32_t)1u) << 0)
#define bv1                                     (((uint32_t)1u) << 1)
#define bv2                                     (((uint32_t)1u) << 2)
#define bv3                                     (((uint32_t)1u) << 3)
#define bv4                                     (((uint32_t)1u) << 4)
#define bv5                                     (((uint32_t)1u) << 5)
#define bv6                                     (((uint32_t)1u) << 6)
#define bv7                                     (((uint32_t)1u) << 7)
#define bv8                                     (((uint32_t)1u) << 8)
#define bv9                                     (((uint32_t)1u) << 9)
#define bv10                                    (((uint32_t)1u) << 10)
#define bv11                                    (((uint32_t)1u) << 11)
#define bv12                                    (((uint32_t)1u) << 12)
#define bv13                                    (((uint32_t)1u) << 13)
#define bv14                                    (((uint32_t)1u) << 14)
#define bv15                                    (((uint32_t)1u) << 15)
#define bv16                                    (((uint32_t)1u) << 16)
#define bv17                                    (((uint32_t)1u) << 17)
#define bv18                                    (((uint32_t)1u) << 18)
#define bv19                                    (((uint32_t)1u) << 19)
#define bv20                                    (((uint32_t)1u) << 20)
#define bv21                                    (((uint32_t)1u) << 21)
#define bv22                                    (((uint32_t)1u) << 22)
#define bv23                                    (((uint32_t)1u) << 23)
#define bv24                                    (((uint32_t)1u) << 24)
#define bv25                                    (((uint32_t)1u) << 25)
#define bv26                                    (((uint32_t)1u) << 26)
#define bv27                                    (((uint32_t)1u) << 27)
#define bv28                                    (((uint32_t)1u) << 28)
#define bv29                                    (((uint32_t)1u) << 29)
#define bv30                                    (((uint32_t)1u) << 30)
#define bv31                                    (((uint32_t)1u) << 31)

#define REGBITS_SET(Reg, Mask)                  ((Reg) |= (Mask))
#define REGBITS_CLR(Reg, Mask)                  ((Reg) &= (~((uint32_t)(Mask))))
#define REGBITS_GET(Reg, Mask)                  ((Reg) & (Mask) )
#define REGBITS_MODIFY(Reg, Mask, Value)        ((Reg) = ((Reg) & (~(uint32_t)(Mask))) | (Value))

/* Exported macro ------------------------------------------------------------*/
#define USE_FULL_ASSERT
#ifdef  USE_FULL_ASSERT
    /**
    * @brief  The assert_param macro is used for function's parameters check.
    * @param  expr If expr is false, it calls assert_failed function
    *         which reports the name of the source file and the source
    *         line number of the call that failed.
    *         If expr is true, it returns no value.
    * @retval None
    */
    #define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
    /* Exported functions ------------------------------------------------------- */
    void assert_failed(uint8_t *file, uint32_t line);
#else
    #define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source)             */
/*****************************************************************************/

#endif /* __BASE_TYPES_H__ */

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/



