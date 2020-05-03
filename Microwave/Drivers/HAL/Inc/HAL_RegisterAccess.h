/*****************************************************************************/
/** File:    HAL_RegisterAccess.h                                           **/
/**                                                                         **/
/** Description: This file define all needed APIs to deal  with  Registers. **/
/**                                                                         **/
/** Author:  Ahmed Wageh                                                    **/
/**                                                                         **/
/** Date:    24/2/2020                                                      **/
/*****************************************************************************/

#ifndef _HAL_REGISTER_ACCESS_H_
#define _HAL_REGISTER_ACCESS_H_
/* Inclusion */
#include "StdTypes.h"

/* Macros */
// Read from 8 bits Register
#define HAL_RegisterRead(REG_ADDRESS)  (*((vuint8_t * const)(REG_ADDRESS)))
// Write to 8 bits Register
#define HAL_RegisterWrite(REG_ADDRESS,__VALUE)  *((vuint8_t * const)(REG_ADDRESS))=__VALUE
// Set specific bit in 8 bits Register
#define HAL_RegisterSetBit(REG_ADDRESS,BIT_NO)  \
 *((vuint8_t * const)(REG_ADDRESS)) |= (1<<BIT_NO)
// Clear Specific bit in 8 bits Register
#define HAL_RegisterClearBit(REG_ADDRESS,BIT_NO)  \
 *((vuint8_t * const)(REG_ADDRESS)) &=~ (1<<BIT_NO)
// Write specific value to specific bit in 8 bits Register
#define HAL_RegisterAssignBit(REG_ADDRESS,BIT_NO,__VALUE) \
(_VALUE ?  HAL_RegisterSetBit(REG_ADDRESS,BIT_NO) : HAL_RegisterClearBit(REG_ADDRESS,BIT_NO))
// Pins defination
#define PIN_0 0
#define PIN_1 1
#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5
#define PIN_6 6
#define PIN_7 7
// Bits defination
#define BIT_0 0
#define BIT_1 1
#define BIT_2 2
#define BIT_3 3
#define BIT_4 4
#define BIT_5 5
#define BIT_6 6
#define BIT_7 7



#endif  /*_HAL_REGISTER_ACCESS_H_*/