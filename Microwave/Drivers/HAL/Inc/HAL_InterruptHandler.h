/*****************************************************************************/
/** File:    HAL_InterruptHandler.h                                             **/
/**                                                                         **/
/** Description: This file to handle all interrupt operations for all       **/
/**              prephirals.                                                **/
/**                                                                         **/
/** Author:  Ahmed Wageh                                                    **/
/**                                                                         **/
/** Date:    24/2/2020                                                      **/
/*****************************************************************************/
#ifndef _HAL_INTERRUPT_HANDLER_H_
#define _HAL_INTERRUPT_HANDLER_H_

/* Macros */
#define INT0_PORT  PORTB_BASE_ADDRESS	/* Interrupt 0 pin port address */
#define INT1_PORT  PORTB_BASE_ADDRESS	/* Interrupt 1 pin port address */
#define INT2_PORT  PORTB_BASE_ADDRESS	/* Interrupt 2 pin port address */
#define INT0_PIN   PIN_0				/* Interrupt 0 pin number */
#define INT1_PIN   PIN_1				/* Interrupt 1 pin number */
#define INT2_PIN   PIN_2				/* Interrupt 2 pin number */

/* Comment the next line if you will handle the ISR */
//#define DRIVER_HANDLE_ISR

#ifdef        DRIVER_HANDLE_ISR
#define NUMBER_OF_ACTIVE_INTERRUPTS 20
#endif

/* Active Interrupts -for interrupt handeling- */
/*#define INTERRUPT_EXT_0
#define INTERRUPT_EXT_1
#define INTERRUPT_EXT_2
#define RB_PORT_CHANGE_INTERRUPT
#define TIMER_0_INTERRUPT
#define TIMER_1_INTERRUPT
#define TIMER_2_INTERRUPT
#define TMR3_INTERRUPT
#define CCP1_INTERRUPT
#define CCP2_INTERRUPT
#define EUSART_TRANSMIT_INTERRUPT
#define EUSART_RECEIVE_INTERRUPT
#define MASTER_SNCHRONOUS_SERIAL_PORT_INTERRUPT
#define A_D_CONVERTER_INTERRUPT
#define PARALLEL_SLAVE_PORT_READ_WRITE_INTERRUPT
#define HIGH_LOW_VOLTAGE_DETECT_INTERRUPT
#define BUS_COLLISION_INTERRUPT
#define DATA_EEPROM_FLASH_WRITE_OPERATION_INTERRUPT
#define COMPARATOR_INTERRUPT
#define OSCILLATOR_FAIL_INTERRUPT*/

/*****************************************************************************/
/** Description: This is to indicate the index of each interrupt source.    **/
/**                                                                         **/
/** Type: Enumeration.                                                      **/
/**                                                                         **/
/** Values: From 0x00 to (NUMBER_OF_ACTIVE_INTERRUPTS-1) and they must be   **/
/**         increased by 1.                                                 **/
/*****************************************************************************/
typedef enum { INT_EXT0 =0x00, /* External Interrupt 0 */
               INT_EXT1 =0X01, /* External Interrupt 1 */
               INT_EXT2 =0X02, /* External Interrupt 2 */
               
               INT_RB   =0x03, /* RB Port Change Interrupt  */
               
               INT_TMR0 =0x04, /* Timer 0 Interrupt */
               INT_TMR1 =0x05, /* Timer 1 Interrupt */
               INT_TMR2 =0x06, /* Timer 2 Interrupt */
               INT_TMR3 =0x07, /* TMR3 Interrupt */
               
               INT_CCP1 =0x08, /* CCP1 Interrupt */
               INT_CCP2 =0x09, /* CCP2 Interrupt */
               
               INT_TX   =0x0A, /* EUSART Transmit Interrupt */
               INT_RC   =0x0B, /* EUSART Receive  Interrupt */

               INT_SSP  =0x0C, /* Master Snchronous Serial Port Interrupt */
               
               INT_AD   =0x0D, /* A/D Converter Interrupt */
               
               INT_PSP  =0x0E, /* Parallel Slave Port Read/Write Interrupt */
               
               INT_HLVD =0x0F, /* High/Low-Voltage Detect Interrupt */
               INT_BCL  =0x10, /* Bus Collision Interrupt */
               INT_EE   =0x11, /* Data EEPROM/Flash Write Operation Interrupt */
               INT_CM   =0x12, /* Comparator Interrupt */
               INT_OSCF =0x13  /* Oscillator Fail Interrupt */
               }InterruptSourceType;

/*****************************************************************************/
/** Description: This is to indicate if the interrupt  happened or not.     **/
/**                                                                         **/
/** Type: Enumeration.                                                      **/
/**                                                                         **/
/** Values: -  EXT_INT_NOT_HAPPENED  => 0 -> No Interrupt.                  **/
/**         -  EXT_INT_HAPPENED      => 1 -> Interrupt happened.            **/
/*****************************************************************************/
typedef enum{
             INT_NOT_HAPPENED=0,
             INT_HAPPENED=1
}InterruptOcurrancyType;

/* Functions prototypes */
/**
  * @brief        By a call to By a call to InterruptHandler_EnableInterrupt it 
  *                        enables specific interrupt source passed its identifier. 
  *        @param        GPIO_Device Enum value defined as InterruptSourceType to know 
  *                        which interrupt source you want to enable. [Optional if you 
  *                        defined DRIVER_HANDLE_ISR in HAL_InterruptHandler.h] .
  *        @param        flagPointer Pointer to flag with type of InterruptOcurrancyType 
  *                        to set if the interrupt happens "could be replaced with pointer 
  *                        to function to call (call-back function)" .  
  *        @return        None.
  */
#ifdef DRIVER_HANDLE_ISR
void InterruptHandler_EnableInterrupt(InterruptSourceType InterruptSource,
                                      InterruptOcurrancyType * flagPointer);
#else
void InterruptHandler_EnableInterrupt(InterruptSourceType InterruptSource);
#endif

/**
  * @brief        By a call to InterruptHandler_DisableInterrupt it disables 
  *                        specific iterrupt source passed its identifier. 
  *        @param        InterruptSource Enum value defined as InterruptSourceType to 
  *                        know which interrupt source you want to disable.
  *        @return        None.
  */
void InterruptHandler_DisableInterrupt(InterruptSourceType InterruptSource);

/**
  * @brief        By a call to InterruptHandler_DisableGlobalInterrupt it disables 
  *                        global interrupt. 
  *        @param        None.
  *        @return        None.
  */
void InterruptHandler_DisableGlobalInterrupt(void);

/**
  * @brief        By a call to InterruptHandler_DisableGlobalInterrupt it enables 
  *                        global interrupt. 
  *        @param        None.
  *        @return        None.
  */
void InterruptHandler_EnbleGlobalInterrupt(void);
#endif  /* _HAL_INTERRUPT_HANDLER_H_ */