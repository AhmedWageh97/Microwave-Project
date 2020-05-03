/*****************************************************************************/
/** File:    HAL_GPIO.h                                                     **/
/**                                                                         **/
/** Description: This file define all needed APIs, data-types and files     **/
/**                 needed for GPIO Driver.                                 **/
/**                                                                         **/
/** Author:  Ahmed Wageh                                                    **/
/**                                                                         **/
/** Date:    24/2/2020                                                      **/
/*****************************************************************************/

#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_

/* Inclusion */
#include "StdTypes.h"
#include "HAL_RegisterAccess.h"

/* Macros */
// PORTS Addresses
#define PORTA_BASE_ADDRESS 0x0F80       /* The base address of port A */
#define PORTB_BASE_ADDRESS 0x0F81       /* The base address of port B */
#define PORTC_BASE_ADDRESS 0x0F82       /* The base address of port C */
#define PORTD_BASE_ADDRESS 0x0F83       /* The base address of port D */
#define PORTE_BASE_ADDRESS 0x0F84       /* The base address of port E */


#define GPIO_OUTPUT_INITIAL_STATE  LOW  /* The initial state of O/P Device */

/* Macro function for debouncing */
#define HAL_GPIO_DEBOUNCE(PORT_ADDRESS,PIN_NUMBER,IN_VALUE)  \
while(((HAL_RegisterRead(PORT_ADDRESS) & (1<<PIN_NUMBER)) >> PIN_NUMBER)==IN_VALUE);

/* User-defined data-types Defination */

/*****************************************************************************/
/** Description: This is to indicate the direction of the pin.              **/
/**                                                                         **/
/** Type: Enumeration.                                                      **/
/**                                                                         **/
/** Values: -        OUTPUT       =>        0x00                            **/
/**         -        INPUT        =>        0x01                            **/
/*****************************************************************************/
typedef enum {
      OUTPUT=0x00,
      INPUT =0x01
} HAL_GPIO_DeviceDirectionType;

/*****************************************************************************/
/** Description: This is to indicate the status of the pin.                 **/
/**                                                                         **/
/** Type: Enumeration.                                                      **/
/**                                                                         **/
/** Values: -        LOW        =>        0x00                              **/
/**         -        HIGH       =>        0x01                              **/
/*****************************************************************************/
typedef enum {
      LOW =0x00,
      HIGH=0x01
} HAL_GPIO_StatusType;

/*****************************************************************************/
/** Description: This is to define all needed configurations for GPIO.      **/
/**                                                                         **/
/** Type: Structure.                                                        **/
/**                                                                         **/
/** Elements: - devicePortBaseAddress  => The address of the port which the **/
/**                                       GPIO device connected to.         **/
/**           - devicePin              => The pin number which the GPIO     **/
/**                                       device connected to.              **/
/**           - deviceDirection        => The direction of the device.      **/
/*****************************************************************************/
typedef struct {
      uint16                       devicePortBaseAddress;
      uint8                        devicePin;
      HAL_GPIO_DeviceDirectionType deviceDirection;
} HAL_GPIO_DeviceType;

/* Functions Prototypes */
/**
  * @brief        By a call to GPIO_DeviceInit The passed GPIO device will be 
  *                        initialized with filled configurations in passed pointer to struct. 
  *        @param        GPIO_Device Pointer to HAL_GPIO_DeviceType which is filled with 
  *                        needed configurations defined HAL_GPIO_DeviceType structure.
  *        @return        STD_OK if no Error and E_NOT_OK if there is Error.
  */
Std_ErrorType GPIO_DeviceInit(HAL_GPIO_DeviceType * GPIO_Device);

/**
  * @brief        By a call to GPIO_DeviceSet The passed GPIO device will be set 
  *                        (its pin will be HIGH or 1). 
  *        @param        GPIO_Device Pointer to HAL_GPIO_DeviceType which is filled with 
  *                        needed configurations defined HAL_GPIO_DeviceType structure.
  *        @return        STD_OK if no Error and E_NOT_OK if there is Error.
  */
Std_ErrorType GPIO_DeviceSet(HAL_GPIO_DeviceType * GPIO_Device);

/**
  * @brief        By a call to GPIO_DeviceClear The passed GPIO device will be 
  *                        cleared (its pin will be LOW or 0). 
  *        @param        GPIO_Device Pointer to HAL_GPIO_DeviceType which is filled with 
  *                        needed configurations defined HAL_GPIO_DeviceType structure.
  *        @return        STD_OK if no Error and E_NOT_OK if there is Error.
  */
Std_ErrorType GPIO_DeviceClear(HAL_GPIO_DeviceType * GPIO_Device);

/**
  * @brief        By a call to GPIO_DeviceToggle The passed GPIO device status 
  *                        will be changed (its pin will be LOW or 0 if it was HIGH or 1 
  *                        and vice verca). 
  *        @param        GPIO_Device Pointer to HAL_GPIO_DeviceType which is filled with 
  *                        needed configurations defined HAL_GPIO_DeviceType structure.
  *        @return        STD_OK if no Error and E_NOT_OK if there is Error.
  */
Std_ErrorType GPIO_DeviceToggle(HAL_GPIO_DeviceType * GPIO_Device);

/**
  * @brief         By a call to GPIO_DeviceAssignStatus The passed GPIO device 
  *                        pin will be setted by passed GPIO_DeviceStatus which is 
  *                        (LOW or HIGH). 
  *        @param        GPIO_Device Pointer to HAL_GPIO_DeviceType which is filled with 
  *                        needed configurations defined HAL_GPIO_DeviceType structure. 
  *        @param        GPIO_DeviceStatus The status needed to be assigned to device pin.
  *        @return        STD_OK if no Error and E_NOT_OK if there is Error.
  */
Std_ErrorType GPIO_DeviceAssignStatus(HAL_GPIO_DeviceType * GPIO_Device,
                                      HAL_GPIO_StatusType GPIO_DeviceStatus);
                                                                          
/**
  * @brief        By a call to GPIO_DeviceInit The passed GPIO device will be 
  *                        initialized with filled configurations in passed pointer to struct. 
  *        @param[in]        GPIO_Device Pointer to HAL_GPIO_DeviceType which is filled with 
  *                                needed configurations defined HAL_GPIO_DeviceType structure. 
  *        @param[out]        ReturnStatus Pointer to HAL_GPIO_StatusType (Buffer)to set data 
  *                                on it.
  *        @return        STD_OK if no Error and E_NOT_OK if there is Error.
  */
Std_ErrorType GPIO_DeviceGetRead(HAL_GPIO_DeviceType * GPIO_Device,
                                 HAL_GPIO_StatusType * ReturnStatus);


#endif  /*_HAL_GPIO_H_*/