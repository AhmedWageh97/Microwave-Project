/*****************************************************************************/
/** File:    HAL_GPIO.c                                                     **/
/**                                                                         **/
/** Description: This file is the implementation of GPIO Driver.            **/
/**                                                                         **/
/** Author:  Ahmed Wageh                                                    **/
/**                                                                         **/
/** Date:    24/2/2020                                                      **/
/*****************************************************************************/

/* Inclusion */
#include "HAL_GPIO.h"


/* Local Macros */
#define PORT_DIRECTION_OFFSET 0x12  /* The difference of the addressees 
                                       between PORTx and TRISx */
#define PORT_LATCH_OFFSET 0x09      /* The difference of the addressees
                                       between PORTx and LATx */
#define ADCON1_ADDRESS 0x0FC1      /* ADCON1 address needed to disable
                                      analog function for portB */

/* Private functions prototype */
static Std_ErrorType GPIO_CheckError(HAL_GPIO_DeviceType * GPIO_Device);

/* Private functions defination */
static Std_ErrorType GPIO_CheckError(HAL_GPIO_DeviceType * GPIO_Device)
{
      if(GPIO_Device  == (HAL_GPIO_DeviceType *)NULL_PTR)
      {
          return STD_ERROR; /* NULL Pointer error */
      }
      if(GPIO_Device->devicePortBaseAddress != PORTA_BASE_ADDRESS &&
         GPIO_Device->devicePortBaseAddress != PORTB_BASE_ADDRESS &&
         GPIO_Device->devicePortBaseAddress != PORTC_BASE_ADDRESS &&
         GPIO_Device->devicePortBaseAddress != PORTD_BASE_ADDRESS &&
         GPIO_Device->devicePortBaseAddress != PORTE_BASE_ADDRESS)
      {
          return STD_ERROR; /* Wrong Base Address */
      }
      
      if(GPIO_Device->devicePin >= 8)
      {
          return STD_ERROR;/* Wrong Pin No */
      }
      
      if(GPIO_Device->deviceDirection >=0x02)
      {
          return STD_ERROR;/* Wrong Direction */
      }
      
      return STD_OK;  /* No Error */
}

/* Global functions declaration */
/*****************************************************************************/
/** Description: By a call to GPIO_DeviceInit The passed GPIO device will   **/
/**              be initialized with filled configurations in passed        **/
/**              pointer to struct.                                         **/
/**                                                                         **/
/** Parameters: + GPIO_Device => Pointer to HAL_GPIO_DeviceType which is    **/
/**                              filled with needed configurations defined  **/
/**                              HAL_GPIO_DeviceType structure.             **/
/**                                                                         **/
/** Return: Std_ReturnType => - STD_OK: When all configurations filled      **/
/**                                     with correct data.                  **/
/**                           - E_NOT_OK: If there is data filled with   	**/
/**                                       wrong data (out of range for      **/
/**                                       example) or pass NULL pointer     **/
/*****************************************************************************/
Std_ErrorType GPIO_DeviceInit(HAL_GPIO_DeviceType * GPIO_Device)
{     uint8 _Temp;  /* temp variable */
      
      _Temp= GPIO_CheckError(GPIO_Device);  /* Error check */
      if(STD_ERROR==_Temp)      return STD_ERROR;   /* Error in struct */
      
      /* Assigning the value of direction the device without affecting
         other bits */
      _Temp  = HAL_RegisterRead((GPIO_Device->devicePortBaseAddress)+PORT_DIRECTION_OFFSET);
      if(GPIO_Device->deviceDirection==OUTPUT)
                _Temp &=~ (1<<(GPIO_Device->devicePin));
      else if(GPIO_Device->deviceDirection==INPUT){
                _Temp |= (1<<(GPIO_Device->devicePin));
                if(GPIO_Device->devicePortBaseAddress==PORTB_BASE_ADDRESS ||
                   GPIO_Device->devicePortBaseAddress==PORTA_BASE_ADDRESS){
                        HAL_RegisterWrite(ADCON1_ADDRESS,HAL_RegisterRead(ADCON1_ADDRESS)|(0x0F));
                        /* set PCFG<3:0> to disable all analog function for all
                           channels */
                }
      }
      HAL_RegisterWrite((GPIO_Device->devicePortBaseAddress)+PORT_DIRECTION_OFFSET,_Temp);
      
      /* Set the pin to initial state */
      HAL_RegisterWrite(GPIO_Device->devicePortBaseAddress,GPIO_OUTPUT_INITIAL_STATE);
      
      return STD_OK;  /* No Error */
}

/*****************************************************************************/
/** Description: By a call to GPIO_DeviceSet The passed GPIO device will    **/
/**              be set (its pin will be HIGH or 1).                        **/
/**                                                                         **/
/** Parameters: + GPIO_Device => Pointer to HAL_GPIO_DeviceType which is    **/
/**                              filled with needed configurations defined  **/
/**                              HAL_GPIO_DeviceType structure.             **/
/**                                                                         **/
/** Return: Std_ReturnType => - STD_OK: When all configurations filled      **/
/**                                     with correct data.                  **/
/**                           - E_NOT_OK: If there is data filled with      **/
/**                                       wrong data (out of range for      **/
/**                                       example) or pass NULL pointer.    **/
/*****************************************************************************/
Std_ErrorType GPIO_DeviceSet(HAL_GPIO_DeviceType * GPIO_Device)
{
      uint8 _Temp;  /* temp variable */

      _Temp= GPIO_CheckError(GPIO_Device);  /* Error check */
      if(STD_ERROR==_Temp)      return STD_ERROR;   /* Error in struct */

       /* Set the pin of the device (HIGH) */
      HAL_RegisterSetBit(GPIO_Device->devicePortBaseAddress,GPIO_Device->devicePin);

      return STD_OK;  /* No Error */
}

/*****************************************************************************/
/** Description: By a call to GPIO_DeviceClear The passed GPIO device will  **/
/**              be cleared (its pin will be LOW or 0).                     **/
/**                                                                         **/
/** Parameters: + GPIO_Device => Pointer to HAL_GPIO_DeviceType which is    **/
/**                              filled with needed configurations defined  **/
/**                              HAL_GPIO_DeviceType structure.             **/
/**                                                                         **/
/** Return: Std_ReturnType => - STD_OK:   When all configurations filled    **/
/**                                       with correct data.                **/
/**                           - E_NOT_OK: If there is data filled with      **/
/**                                       wrong data (out of range for      **/
/**                                       example) or pass NULL pointer.    **/
/*****************************************************************************/
Std_ErrorType GPIO_DeviceClear(HAL_GPIO_DeviceType * GPIO_Device)
{
      uint8 _Temp;  /* temp variable */

      _Temp= GPIO_CheckError(GPIO_Device);  /* Error check */
      if(STD_ERROR==_Temp)      return STD_ERROR;   /* Error in struct */

       /* Clear the pin of the device (LOW) */
      HAL_RegisterClearBit(GPIO_Device->devicePortBaseAddress,GPIO_Device->devicePin);

      return STD_OK;  /* No Error */
}

/*****************************************************************************/
/** Description: By a call to GPIO_DeviceToggle The passed GPIO device      **/
/**              status will be changed (its pin will be LOW or 0 if it     **/
/**              was HIGH or 1 and vice verca).                             **/
/**                                                                         **/
/** Parameters: + GPIO_Device => Pointer to HAL_GPIO_DeviceType which is    **/
/**                              filled with needed configurations defined  **/
/**                              HAL_GPIO_DeviceType structure.             **/
/**                                                                         **/
/** Return: Std_ReturnType => - STD_OK:   When all configurations filled    **/
/**                                       with correct data.                **/
/**                           - E_NOT_OK: If there is data filled with      **/
/**                                       wrong data (out of range for      **/
/**                                       example) or pass NULL pointer.    **/
/*****************************************************************************/
Std_ErrorType GPIO_DeviceToggle(HAL_GPIO_DeviceType * GPIO_Device)
{
      uint8 _Temp;  /* temp variable */

      _Temp= GPIO_CheckError(GPIO_Device);  /* Error check */
      if(STD_ERROR==_Temp)      return STD_ERROR;   /* Error in struct */

      /* Get the status and toggle it */
      _Temp  = HAL_RegisterRead(GPIO_Device->devicePortBaseAddress);
      if(_Temp & (1<<(GPIO_Device->devicePin)))
      {     
            HAL_RegisterClearBit(GPIO_Device->devicePortBaseAddress,GPIO_Device->devicePin);
      }
      else
      {
            HAL_RegisterSetBit(GPIO_Device->devicePortBaseAddress,GPIO_Device->devicePin);
      }
      
      return STD_OK;  /* No Error */
}

/*****************************************************************************/
/** Description: By a call to GPIO_DeviceAssignStatus The passed GPIO       **/
/**              device pin will be setted by passed GPIO_DeviceStatus      **/
/**              which is (LOW or HIGH)                                     **/
/**                                                                         **/
/** Parameters: + GPIO_Device => Pointer to HAL_GPIO_DeviceType which is    **/
/**                              filled with needed configurations defined  **/
/**                              HAL_GPIO_DeviceType structure.             **/
/**             + GPIO_DeviceStatus => The status needed to be assigned to  **/
/**                                    device pin.                          **/
/**                                                                         **/
/** Return: Std_ReturnType => - STD_OK:   When all configurations filled    **/
/**                                       with correct data.                **/
/**                           - E_NOT_OK: If there is data filled with      **/
/**                                       wrong data (out of range for      **/
/**                                       example) or pass NULL pointer.    **/
/*****************************************************************************/
Std_ErrorType GPIO_DeviceAssignStatus(HAL_GPIO_DeviceType * GPIO_Device,
                                      HAL_GPIO_StatusType GPIO_DeviceStatus)
{
      uint8 _Temp;  /* temp variable */

      _Temp= GPIO_CheckError(GPIO_Device);  /* Error check */
      if(STD_ERROR==_Temp)      return STD_ERROR;   /* Error in struct */

     /* Assign state to device pin */
     switch(GPIO_DeviceStatus)
      {
           case LOW:
                GPIO_DeviceClear(GPIO_Device);
           break;
           
           case HIGH:
                GPIO_DeviceSet(GPIO_Device);
           break;
           
           default:
                return STD_ERROR;   /* Error in GPIO_DeviceStatus */
      }

      return STD_OK;  /* No Error */
}

/*****************************************************************************/
/** Description: By a call to GPIO_DeviceGetRead The passed GPIO            **/
/**              device pin status will be read and asigned in the passed   **/
/**              buffer.                                                    **/
/**                                                                         **/
/** Parameters: + GPIO_Device => Pointer to HAL_GPIO_DeviceType which is    **/
/**                              filled with needed configurations defined  **/
/**                              HAL_GPIO_DeviceType structure.             **/
/**             + ReturnStatus => Pointer to HAL_GPIO_StatusType (Buffer)   **/
/**                               to set data on it.                        **/
/**                                                                         **/
/** Return: Std_ReturnType => - STD_OK:   When all configurations filled    **/
/**                                       with correct data.                **/
/**                           - E_NOT_OK: If there is data filled with      **/
/**                                       wrong data (out of range for      **/
/**                                       example) or pass NULL pointer.    **/
/*****************************************************************************/
Std_ErrorType GPIO_DeviceGetRead(HAL_GPIO_DeviceType * GPIO_Device,
                                 HAL_GPIO_StatusType * ReturnStatus)
{
      uint8 _Temp;  /* temp variable */

      _Temp= GPIO_CheckError(GPIO_Device);  /* Error check */
      if(STD_ERROR==_Temp)      return STD_ERROR;   /* Error in struct */
      
      if(ReturnStatus == (HAL_GPIO_StatusType *)NULL_PTR) /* Passing NULL pointer */
      return STD_ERROR;

      _Temp  = HAL_RegisterRead(GPIO_Device->devicePortBaseAddress);
      if(_Temp & (1<<(GPIO_Device->devicePin)))     *(ReturnStatus) = HIGH;
      else                                          *(ReturnStatus) = LOW;

      return STD_OK;  /* No Error */
}