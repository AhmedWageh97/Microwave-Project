/*****************************************************************************/
/** File:    Module_Keypad.h                                                **/
/**                                                                         **/
/** Description: This file define all needed APIs to interface with keypad. **/
/**                                                                         **/
/** Author:  Ahmed Wageh                                                    **/
/**                                                                         **/
/** Date:    24/2/2020                                                      **/
/*****************************************************************************/

#ifndef _MODULE_KEYPAD_H_
#define _MODULE_KEYPAD_H_

/* Inclusion */
#include "HAL_GPIO.h"

/* Macros */
#define KEYPAD_MAX_COL_NUMBER 3
#define KEYPAD_MAX_ROW_NUMBER 4

#define KEYPAD_NOT_PRESSED 0

/* Data types defination */
typedef uint8 keypad_returnDataType; /* Define the type of return from keypad */

/*****************************************************************************/
/** Description: This is to define all needed configurations for Keypad.    **/
/**                                                                         **/
/** Type: Structure.                                                        **/
/**                                                                         **/
/** Elements: - rowsNumber        => The number of ROWS.                    **/
/**           - colsNumber        => The number of COLS.                    **/
/**           - rowConfiguration  => The configurations of row pins.        **/
/**           - colConfiguration  => The configurations of col pins         **/
/**           - returnDataArray   => 2-D array to return data from keypad.  **/
/*****************************************************************************/
typedef struct{
        uint8 rowsNumber;
        uint8 colsNumber;
        HAL_GPIO_DeviceType   rowConfiguration[KEYPAD_MAX_ROW_NUMBER];
        HAL_GPIO_DeviceType   colConfiguration[KEYPAD_MAX_COL_NUMBER];
        keypad_returnDataType returnDataArray[KEYPAD_MAX_ROW_NUMBER][KEYPAD_MAX_COL_NUMBER];
}Keypad_ConfigType;

/* Functions prototype */
/**
  * @brief	By a call to Keypad_init The passed keypad will be initialized 
  *			with filled configurations in passed pointer to struct. 
  *	@param	Keypad_Configuration Pointer to Keypad_ConfigType which is 
  *			filled with needed configurations defined in Keypad_ConfigType 
  *			structure. 
  *	@return	STD_OK if no Error and E_NOT_OK if there is Error.
  */
Std_ErrorType Keypad_init(Keypad_ConfigType * Keypad_Configuration);

/**
  * @brief	By a call to Keypad_getReading The passed Keypad will be read and 
  *			asigned in the passed buffer. 
  *	@param[in]	Keypad_Configuration Pointer to Keypad_ConfigType which is 
  *				filled with needed configurations defined in Keypad_ConfigType 
  *				structure. 
  *	@param[out]	keypad_returnData Pointer to keypad_returnDataType (Buffer) 
  *				to set data on it with KEYPAD_NOT_PRESSED if no button pressed 
  *				and element from returnDataArray if any button pressed.
  *	@return	STD_OK if no Error and E_NOT_OK if there is Error.
  */
Std_ErrorType Keypad_getReading(Keypad_ConfigType * Keypad_Configuration,
                                keypad_returnDataType * keypad_returnData);
#endif /* _MODULE_KEYPAD_H_ */