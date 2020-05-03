/*****************************************************************************/
/** File:    Module_Keypad.c                                                **/
/**                                                                         **/
/** Description: This file is the implementation of Keypad Driver.          **/
/**                                                                         **/
/** Author:  Ahmed Wageh                                                    **/
/**                                                                         **/
/** Date:    24/2/2020                                                      **/
/*****************************************************************************/

/* Inclusion */
#include "Module_Keypad.h"

/* Private functions prototype */
static Std_ErrorType Keypad_checkForError(Keypad_ConfigType * Keypad_Configuration);

/* Private functions defination */
static Std_ErrorType Keypad_checkForError(Keypad_ConfigType * Keypad_Configuration)
{
       if(Keypad_Configuration->rowsNumber <= 0)                return STD_ERROR;
       if(Keypad_Configuration->colsNumber <= 0)                return STD_ERROR;
       if(Keypad_Configuration->rowConfiguration == (HAL_GPIO_DeviceType *) NULL_PTR)      return STD_ERROR;
       if(Keypad_Configuration->colConfiguration == (HAL_GPIO_DeviceType *) NULL_PTR)      return STD_ERROR;
       if(Keypad_Configuration->returnDataArray == (keypad_returnDataType*) NULL_PTR)      return STD_ERROR;
       
       return STD_OK;
}

/* Public functions defination */
/*****************************************************************************/
/** Description: By a call to Keypad_init The passed keypad will be         **/
/**              initialized with filled configurations in passed pointer   **/
/**              to struct.                                                 **/
/**                                                                         **/
/** Parameters: + Keypad_Configuration => Pointer to Keypad_ConfigType      **/
/**                                       which is filled with needed       **/
/**                                       configurations defined in         **/
/**                                       Keypad_ConfigType structure.      **/
/**                                                                         **/
/** Return: Std_ReturnType => - STD_OK: When all configurations filled      **/
/**                                     with correct data.                  **/
/**                           - E_NOT_OK: If there is data filled with      **/
/**                                       wrong data (out of range for      **/
/**                                       example) or pass NULL pointer     **/
/*****************************************************************************/
Std_ErrorType Keypad_init(Keypad_ConfigType * Keypad_Configuration)
{
      Std_ErrorType _Function_Return;
      uint8 _Loop_Variable;
      uint8 _Loop_Variable_Max;
      
      /* Check parameters */
      _Function_Return= Keypad_checkForError(Keypad_Configuration);
      if(_Function_Return == STD_ERROR)       return STD_ERROR; /* Error in struct */
      
      /* Init process */
      if(Keypad_Configuration->rowsNumber >= Keypad_Configuration->colsNumber)
      {
              _Loop_Variable_Max=Keypad_Configuration->rowsNumber;
      }
      else
      {
             _Loop_Variable_Max=Keypad_Configuration->colsNumber;
      }
      // Init Cols as Input and Row as Output
      for(_Loop_Variable=0; _Loop_Variable<_Loop_Variable_Max; _Loop_Variable++)
      {
             if(_Loop_Variable < Keypad_Configuration->colsNumber)
             {
                   Keypad_Configuration->colConfiguration[_Loop_Variable].deviceDirection=INPUT;
                   _Function_Return=GPIO_DeviceInit(&Keypad_Configuration->colConfiguration[_Loop_Variable]);
                   if(_Function_Return == STD_ERROR)       return STD_ERROR; /* Error in struct */
             }
             if(_Loop_Variable < Keypad_Configuration->rowsNumber)
             {
                   Keypad_Configuration->rowConfiguration[_Loop_Variable].deviceDirection=OUTPUT;
                   _Function_Return=GPIO_DeviceInit(&Keypad_Configuration->rowConfiguration[_Loop_Variable]);
                   if(_Function_Return == STD_ERROR)       return STD_ERROR; /* Error in struct */
             }
      }
      
      return STD_OK; /* If the code reaches this point then NO ERROR happened */
}

/*****************************************************************************/
/** Description: By a call to Keypad_getReading The passed Keypad will be   **/
/**              read and asigned in the passed buffer.                     **/
/**                                                                         **/
/** Parameters: + Keypad_Configuration => Pointer to Keypad_ConfigType      **/
/**                                       which is filled with needed       **/
/**                                       configurations defined in         **/
/**                                       Keypad_ConfigType structure.      **/
/**             + keypad_returnData => Pointer to keypad_returnDataType     **/
/**                                    (Buffer) to set data on it with      **/
/**                                    KEYPAD_NOT_PRESSED if no button      **/
/**                                    pressed and element from             **/
/**                                    returnDataArray if any button        **/
/**                                    pressed.                             **/
/**                                                                         **/
/** Return: Std_ReturnType => - STD_OK:   When all configurations filled    **/
/**                                       with correct data.                **/
/**                           - E_NOT_OK: If there is data filled with      **/
/**                                       wrong data (out of range for      **/
/**                                       example) or pass NULL pointer.    **/
/*****************************************************************************/
Std_ErrorType Keypad_getReading(Keypad_ConfigType * Keypad_Configuration,
                                keypad_returnDataType * keypad_returnData)
{
      Std_ErrorType _Function_Return;
      HAL_GPIO_StatusType _Pins_Reading;
      uint8 _Loop_Variable_Main;
      uint8 _Loop_Variable_Branch;
      
      /* Check parameters */
      _Function_Return= Keypad_checkForError(Keypad_Configuration);
      if(_Function_Return == STD_ERROR)       return STD_ERROR; /* Error in struct */
      
      /* Get reading process */
      for(_Loop_Variable_Main=0; _Loop_Variable_Main < (Keypad_Configuration->rowsNumber); _Loop_Variable_Main++)
      {
            for(_Loop_Variable_Branch=0; _Loop_Variable_Branch < (Keypad_Configuration->rowsNumber); _Loop_Variable_Branch++)
            {
                    _Function_Return=GPIO_DeviceSet(&(Keypad_Configuration->rowConfiguration[_Loop_Variable_Branch]));
                    if(_Function_Return == STD_ERROR)       return STD_ERROR; /* Error in struct */
            } /* Set all ROW pins */
            /* Clear only one pin */
            _Function_Return=GPIO_DeviceClear(&(Keypad_Configuration->rowConfiguration[_Loop_Variable_Main]));
            if(_Function_Return == STD_ERROR)       return STD_ERROR; /* Error in struct */
            
            for(_Loop_Variable_Branch=0; _Loop_Variable_Branch < (Keypad_Configuration->colsNumber); _Loop_Variable_Branch++)
            {
                    _Function_Return=GPIO_DeviceGetRead(&(Keypad_Configuration->colConfiguration[_Loop_Variable_Branch]),
                                                        &_Pins_Reading);
                    if(_Function_Return == STD_ERROR)       return STD_ERROR; /* Error in struct */
                    
                    if(_Pins_Reading == LOW) /* key is pressed */
                    {
                         /* Debouncing */
                         HAL_GPIO_DEBOUNCE(Keypad_Configuration->colConfiguration[_Loop_Variable_Branch].devicePortBaseAddress,
                                           Keypad_Configuration->colConfiguration[_Loop_Variable_Branch].devicePin,LOW);

                         /* Buffer the data */
                         * keypad_returnData= Keypad_Configuration->returnDataArray[_Loop_Variable_Main][_Loop_Variable_Branch];
                         return STD_OK;  /* Exit */
                    }
            }

      }
      
      /* If the code reaches this point then no key pressed and NO ERROR happened */
      * keypad_returnData= KEYPAD_NOT_PRESSED;
      return STD_OK;
}