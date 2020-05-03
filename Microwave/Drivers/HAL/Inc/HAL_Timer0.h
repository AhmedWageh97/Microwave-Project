/*****************************************************************************/
/** File:    HAL_Timer0.h                                                   **/
/**                                                                         **/
/** Description: This file define all needed APIs, data-types and files     **/
/**              needed for Timer0 Driver.                                  **/
/**                                                                         **/
/** Author:  Ahmed Wageh                                                    **/
/**                                                                         **/
/** Date:    24/2/2020                                                      **/
/*****************************************************************************/

#ifndef _HAL_TIMER0_H_
#define _HAL_TIMER0_H_

/* Inclusion */
#include "StdTypes.h"
#include "HAL_RegisterAccess.h"

/* Macros */
#define TIMER0L_Reg 0x0FD6 /* Timer0L Register base address */
#define TIMER0H_Reg 0x0FD7 /* Timer0H Register base address */

/* User-defined data types */
/*****************************************************************************/
/** Description: This is to indicate the size of Timer0 count register.     **/
/**                                                                         **/
/** Type: Enumeration.                                                      **/
/**                                                                         **/
/** Values: -   TIMER0_16_Bits       =>        0x00                         **/
/**         -   TIMER0_8_Bits       =>        0x01                         **/
/*****************************************************************************/
typedef enum {
      TIMER0_16_BITS=0x00,
      TIMER0_8_BITS =0x01
} HAL_Timer0_DataSizeType;

/*****************************************************************************/
/** Description: This is to indicate the mode of Timer0.                    **/
/**                                                                         **/
/** Type: Enumeration.                                                      **/
/**                                                                         **/
/** Values: - TIMER0_TIMER                  => 0x00 -> Timer0 increments    **/
/**                                                    with internal clock. **/
/**         - TIMER0_COUNTER_RISING_EDGE    => 0x01 -> Timer0 increments    **/
/**                                                    with external clock  **/
/**                                                    connected to T0CKI   **/
/**                                                    pin with rising edge.**/
/**         - TIMER0_COUNTER_FALLING_EDGE   => 0x02 -> Timer0 increments    **/
/**                                                    with external clock  **/
/**                                                    connected to T0CKI   **/
/**                                                    pin with falling     **/
/**                                                    edge.                **/
/*****************************************************************************/
typedef enum {
      TIMER0_TIMER                =0x00,
      TIMER0_COUNTER_RISING_EDGE  =0x01,
      TIMER0_COUNTER_FALLING_EDGE =0x02
} HAL_Timer0_ModeType;

/*****************************************************************************/
/** Description: This is to indicate the prescaler.     					**/
/**                                                                         **/
/** Type: Enumeration.                                                      **/
/**                                                                         **/
/** Values: -   TIMER0_PRESCALER_OFF   =>        0x00                       **/
/**         -   TIMER0_PRESCALER_2     =>        0x01                       **/
/**         -   TIMER0_PRESCALER_4     =>        0x02						**/
/**         -   TIMER0_PRESCALER_8     =>        0x03                       **/
/**         -   TIMER0_PRESCALER_16    =>        0x04                       **/
/**         -   TIMER0_PRESCALER_32    =>        0x05                       **/
/**         -   TIMER0_PRESCALER_64    =>        0x06                       **/
/**         -   TIMER0_PRESCALER_128   =>        0x07                       **/
/**         -   TIMER0_PRESCALER_256   =>        0x08						**/
/*****************************************************************************/
typedef enum {
      TIMER0_PRESCALER_OFF   =0x00,
      TIMER0_PRESCALER_2     =0x01,
      TIMER0_PRESCALER_4     =0x02,
      TIMER0_PRESCALER_8     =0x03,
      TIMER0_PRESCALER_16    =0x04,
      TIMER0_PRESCALER_32    =0x05,
      TIMER0_PRESCALER_64    =0x06,
      TIMER0_PRESCALER_128   =0x07,
      TIMER0_PRESCALER_256   =0x08
} HAL_Timer0_PrescalerType;

/*****************************************************************************/
/** Description: This is to define all needed configurations for Timer0.    **/
/**                                                                         **/
/** Type: Structure.                                                        **/
/**                                                                         **/
/** Elements: - Timer0_Mode  		=> The mode of the timer.         		**/
/**           - Timer0_DataSize 	=> 16 bits or 8 bits data length.       **/
/**           - Timer0_Prescaler    => Prescaler value.      				**/
/**           - Timer0_Data         => Data to be written in timer register **/
/*****************************************************************************/
typedef struct {
        HAL_Timer0_ModeType      Timer0_Mode;
        HAL_Timer0_DataSizeType  Timer0_DataSize;
        HAL_Timer0_PrescalerType Timer0_Prescaler;
        uint16                   Timer0_Data;
}HAL_Timer0_ConfigType;
 
 /* Function Prototype */
/**
  * @brief	By a call to HAL_Timer0_init Timer0 will be initialized with 
  *			configurations filled in passed pointer to struct. 
  *	@note	Calling this function doesn't start timer0 it just configures it.
  *	@param	Timer0_Config Pointer to HAL_Timer0_ConfigType which is filled 
  *			with needed configurations defined in HAL_Timer0_ConfigType 
  *			structure.
  *	@return	STD_OK if no Error and E_NOT_OK if there is Error.
  */
Std_ErrorType HAL_Timer0_init(HAL_Timer0_ConfigType * Timer0_Config);

/**
  * @brief	By a call to HAL_Timer0_start Timer0 will start. 
  *	@param	None.
  *	@return	None.
  */
void HAL_Timer0_start(void);

/**
  * @brief	By a call to HAL_Timer0_start Timer0 will stop. 
  *	@param	None.
  *	@return	None.
  */
void HAL_Timer0_stop(void);

/**
  * @brief	By a call to HAL_Timer0_updateConfig Timer0 configurations will 
  *			be updated with configurations filled in passed pointerto struct.
  *	@note	Calling this function initialize and start timer0. 
  *	@param	Timer0_Config Pointer to HAL_Timer0_ConfigType which is filled 
  *			with needed configurations defined in HAL_Timer0_ConfigType 
  *			structure.
  *	@return	STD_OK if no Error and E_NOT_OK if there is Error.
  */
Std_ErrorType HAL_Timer0_updateConfig(HAL_Timer0_ConfigType * Timer0_Config);

 
 

#endif /* _HAL_TIMER0_H_ */