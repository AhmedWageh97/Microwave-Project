/*****************************************************************************/
/** File:    HAL_Timer0.c                                                   **/
/**                                                                         **/
/** Description: This file is the implementation of Timer0 Driver.          **/
/**                                                                         **/
/** Author:  Ahmed Wageh                                                    **/
/**                                                                         **/
/** Date:    24/2/2020                                                      **/
/*****************************************************************************/

/* Inclusion */
#include "HAL_Timer0.h"

/* Macros */
#define T0CON_BASE_ADDRESS 0x0FD5
#define TMR0L_BASE_ADDRESS 0x0FD6
#define TMR0H_BASE_ADDRESS 0x0FD7

#ifndef TMR0ON
#define TMR0ON   BIT_7
#endif /* TMR0ON */ 
#ifndef T08BIT 
#define T08BIT   BIT_6
#endif /* T08BIT */
#ifndef T0CS 
#define T0CS     BIT_5
#endif /* T0CS */
#ifndef T0SE 
#define T0SE     BIT_4
#endif /* T0SE */
#ifndef PSA 
#define PSA      BIT_3
#endif /* PSA */
#ifndef T0PS2 
#define T0PS2    BIT_2
#endif /* T0PS2 */
#ifndef T0PS1
#define T0PS1    BIT_1
#endif /* T0PS1 */
#ifndef T0PS0
#define T0PS0    BIT_0
#endif /* T0PS0 */


/* Private functions prototype */
static Std_ErrorType Timer0_ErrorCheck(HAL_Timer0_ConfigType * Timer0_Config);

/* Private functions defination */
static Std_ErrorType Timer0_ErrorCheck(HAL_Timer0_ConfigType * Timer0_Config)
{
       return STD_OK;
}
 
 /* public functions defination */
/*****************************************************************************/
/** Description: By a call to HAL_Timer0_init Timer0 will be initialized    **/
/**              with configurations filled in passed pointerto struct.     **/
/**                                                                         **/
/** Parameters: + Timer0_Config => Pointer to HAL_Timer0_ConfigType which   **/
/**                                is filled with needed configurations     **/
/**                                defined in HAL_Timer0_ConfigType         **/
/**                                structure.                               **/
/**                                                                         **/
/** Return: Std_ReturnType => - STD_OK: When all configurations filled      **/
/**                                     with correct data.                  **/
/**                           - E_NOT_OK: If there is data filled with      **/
/**                                       wrong data (out of range for      **/
/**                                       example) or pass NULL pointer     **/
/**                                                                         **/
/** Note: HAL_Timer0_init just initialize Timer0 and doesn't start it       **/
/*****************************************************************************/
Std_ErrorType HAL_Timer0_init(HAL_Timer0_ConfigType * Timer0_Config)
{
       Std_ErrorType _Function_Return;
       uint8 _Reg_Temp=0;
       
       /* Check parameters */
      _Function_Return= Timer0_ErrorCheck(Timer0_Config);
      if(_Function_Return == STD_ERROR)       return STD_ERROR; /* Error in struct */
      
      HAL_Timer0_stop();
      
      switch(Timer0_Config->Timer0_DataSize) /* data size */
      {
             case TIMER0_16_BITS:
                  _Reg_Temp &=~ (1<<TIMER0_8_BITS);
                  HAL_RegisterWrite(TMR0L_BASE_ADDRESS,Timer0_Config->Timer0_Data);
                  HAL_RegisterWrite(TMR0H_BASE_ADDRESS,Timer0_Config->Timer0_Data>>8);
             break;
             case TIMER0_8_BITS:
                  _Reg_Temp |=  (1<<TIMER0_8_BITS);
                  HAL_RegisterWrite(TMR0L_BASE_ADDRESS,Timer0_Config->Timer0_Data);
             break;
      }

      switch(Timer0_Config->Timer0_Mode)  /* set mode */
      {
             case TIMER0_TIMER:
                  _Reg_Temp &=~ (1<<T0CS);
             break;
             case TIMER0_COUNTER_RISING_EDGE:
                  _Reg_Temp |=  (1<<T0CS);
                  _Reg_Temp &=~ (1<<T0SE);
             break;
             case TIMER0_COUNTER_FALLING_EDGE:
                  _Reg_Temp |=  (1<<T0CS);
                  _Reg_Temp |=  (1<<T0SE);
             break;
      }
      switch(Timer0_Config->Timer0_Prescaler)  /* set prescaler */
      {
             case TIMER0_PRESCALER_OFF:
                  _Reg_Temp |=  (1<<PSA);
             break;
             case TIMER0_PRESCALER_2:
                  _Reg_Temp &=~ (1<<PSA);
                  _Reg_Temp &=~ (7<<T0PS0);
             break;
             case TIMER0_PRESCALER_4:
                  _Reg_Temp &=~ (1<<PSA);
                  _Reg_Temp &=~ (7<<T0PS0);
                  _Reg_Temp |=  (1<<T0PS0);
             break;
             case TIMER0_PRESCALER_8:
                  _Reg_Temp &=~ (1<<PSA);
                  _Reg_Temp &=~ (7<<T0PS0);
                  _Reg_Temp |=  (1<<T0PS1);
             break;
             case TIMER0_PRESCALER_16:
                  _Reg_Temp &=~ (1<<PSA);
                  _Reg_Temp &=~ (7<<T0PS0);
                  _Reg_Temp |=  (3<<T0PS0);
             break;
             case TIMER0_PRESCALER_32:
                  _Reg_Temp &=~ (1<<PSA);
                  _Reg_Temp &=~ (7<<T0PS0);
                  _Reg_Temp |=  (1<<T0PS2);
             break;
             case TIMER0_PRESCALER_64:
                  _Reg_Temp &=~ (1<<PSA);
                  _Reg_Temp |=  (7<<T0PS0);
                  _Reg_Temp &=~ (1<<T0PS1);
             break;
             case TIMER0_PRESCALER_128:
                  _Reg_Temp &=~ (1<<PSA);
                  _Reg_Temp |=  (7<<T0PS0);
                  _Reg_Temp &=~ (1<<T0PS0);
             break;
             case TIMER0_PRESCALER_256:
                  _Reg_Temp &=~ (1<<PSA);
                  _Reg_Temp |=  (7<<T0PS0);
             break;
      }
      HAL_RegisterWrite(T0CON_BASE_ADDRESS,_Reg_Temp); /* control Timer0 */
      return STD_OK;  /* Successful init*/
}

/*****************************************************************************/
/** Description: By a call to HAL_Timer0_start Timer0 will start.           **/
/**                                                                         **/
/** Parameters: None.                                                       **/
/**                                                                         **/
/** Return: None.                                                           **/
/*****************************************************************************/
void HAL_Timer0_start(void)
{
      HAL_RegisterSetBit(T0CON_BASE_ADDRESS,TMR0ON);
}

/*****************************************************************************/
/** Description: By a call to HAL_Timer0_start Timer0 will stop.            **/
/**                                                                         **/
/** Parameters: None.                                                       **/
/**                                                                         **/
/** Return: None.                                                           **/
/*****************************************************************************/
void HAL_Timer0_stop(void)
{
     HAL_RegisterClearBit(T0CON_BASE_ADDRESS,TMR0ON);
}

/*****************************************************************************/
/** Description: By a call to HAL_Timer0_updateConfig Timer0                **/
/**              configurations will be updated with configurations filled  **/
/**              in passed pointerto struct.                                **/
/**                                                                         **/
/** Parameters: + Timer0_Config => Pointer to HAL_Timer0_ConfigType which   **/
/**                                is filled with needed configurations     **/
/**                                defined in HAL_Timer0_ConfigType         **/
/**                                structure.                               **/
/**                                                                         **/
/** Return: Std_ReturnType => - STD_OK: When all configurations filled      **/
/**                                     with correct data.                  **/
/**                           - E_NOT_OK: If there is data filled with      **/
/**                                       wrong data (out of range for      **/
/**                                       example) or pass NULL pointer     **/
/**                                                                         **/
/** Note: HAL_Timer0_updateConfig = HAL_Timer0_init + HAL_Timer0_start.     **/
/*****************************************************************************/
Std_ErrorType HAL_Timer0_updateConfig(HAL_Timer0_ConfigType * Timer0_Config)
{
     Std_ErrorType _Function_Return;
     
     _Function_Return=HAL_Timer0_init(Timer0_Config);
     if(_Function_Return == STD_ERROR)       return STD_ERROR; /* Error in init */
     
     HAL_Timer0_start();
}