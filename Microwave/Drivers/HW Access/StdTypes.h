/*****************************************************************************/
/** File:    StdTypes.h                                                     **/
/**                                                                         **/
/** Description: This header file define all needed standard data-types     **/
/**                 used in all layers.                                     **/
/**                                                                         **/
/** Author:  Ahmed Wageh                                                    **/
/**                                                                         **/
/** Date:    24/2/2020                                                      **/
/*****************************************************************************/
#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_

/* Macros */
/* NULL Definition */
#ifndef NULL
#define        NULL        0
#endif

#ifndef        NULL_PTR
#define NULL_PTR  ((void*)0)
#endif

/* Data types definations */
typedef bit                     boolean;
typedef char                    sint8;
typedef unsigned char           uint8;
typedef signed int              sint16;
typedef unsigned int            uint16;
typedef signed long             sint32;
typedef unsigned long           uint32;
typedef signed long long        sint64;
typedef unsigned long long      uint64;
typedef float                   float32;
typedef double                  float64;


typedef volatile char           vint8_t;
typedef volatile uint8          vuint8_t;

typedef volatile sint16         vint16_t;
typedef volatile uint16         vuint16_t;

typedef volatile sint32         vint32_t;
typedef volatile uint32         vuint32_t;

typedef volatile sint64         vint64_t;
typedef volatile uint64         vuint64_t;

/* Optimized integer data types */
#ifndef FALSE
#define FALSE                (0U)
#endif
#ifndef TRUE
#define TRUE                (1U)
#endif

#ifndef False
#define False                (boolean)0
#endif
#ifndef True
#define True                (boolean)1
#endif

/* User-defined data-types */
typedef enum {STD_ERROR=0,
              STD_OK=1} Std_ErrorType; /* Error type */

#endif  /*_STD_TYPES_H_*/