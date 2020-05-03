/*****************************************************************************/
/** File:    HAL_InterruptHandler.c                                         **/
/**                                                                         **/
/** Description: This file to handle all interrupt operations for all       **/
/**              prephirals.                                                **/
/**                                                                         **/
/** Author:  Ahmed Wageh                                                    **/
/**                                                                         **/
/** Date:    24/2/2020                                                      **/
/*****************************************************************************/

/* Inclusion */
#include "StdTypes.h"
#include "HAL_InterruptHandler.h"
#include "HAL_RegisterAccess.h"


/* Private Macroos */

#define INTCON_ADDRESS    0x0FF2
#define INTCON3_ADDRESS   0x0FF0
#define PIR1_ADDRESS      0x0F9E
#define PIR2_ADDRESS      0x0FA1
#define PIE1_ADDRESS      0x0F9D
#define PIE2_ADDRESS      0x0FA0

#ifndef RBIF
#define RBIF BIT_0
#endif  /* RBIF */
#ifndef INT0IF
#define INT0IF BIT_1
#endif  /* INT0IF */
#ifndef TMR0IF
#define TMR0IF BIT_2
#endif  /* TMR0IF */
#ifndef TMR1IF
#define TMR1IF BIT_0
#endif  /* TMR1IF */
#ifndef TMR2IF
#define TMR2IF BIT_1
#endif  /* TMR2IF */
#ifndef CCP1IF
#define CCP1IF BIT_2
#endif  /* CCP1IF */
#ifndef SSPIF
#define SSPIF BIT_3
#endif  /* SSPIF */
#ifndef TXIF
#define TXIF BIT_4
#endif  /* TXIF */
#ifndef RCIF
#define RCIF BIT_5
#endif  /* RCIF */
#ifndef ADIF
#define ADIF BIT_6
#endif  /* ADIF */
#ifndef PSPIF
#define PSPIF BIT_7
#endif  /* PSPIF */
#ifndef INT1IF
#define INT1IF BIT_0
#endif  /* INT1IF */
#ifndef INT2IF
#define INT2IF BIT_1
#endif  /* INT2IF */
#ifndef CCP2IF
#define CCP2IF BIT_0
#endif  /* CCP2IF */
#ifndef TMR3IF
#define TMR3IF BIT_1
#endif  /* TMR3IF */
#ifndef HLVDIF
#define HLVDIF BIT_2
#endif  /* HLVDIF */
#ifndef BCLIF
#define BCLIF BIT_3
#endif  /* BCLIF */
#ifndef EEIF
#define EEIF BIT_4
#endif  /* EEIF */
#ifndef CMIF
#define CMIF BIT_6
#endif  /* CMIF */
#ifndef OSCFIF
#define OSCFIF BIT_6
#endif  /* OSCFIF */

/* Private variables */
#ifdef DRIVER_HANDLE_ISR
static InterruptOcurrancyType * InterruptHandler_Flags[NUMBER_OF_ACTIVE_INTERRUPTS]=
                 {0};
#endif

/* Public functions defination */
/*****************************************************************************/
/** Description: By a call to InterruptHandler_EnableInterrupt it enables   **/
/**              specific interrupt source passed its identifier.           **/
/**                                                                         **/
/** Parameters: + InterruptSource => Enum value defined as                  **/
/**                                  InterruptSourceType to know which      **/
/**                                  interrupt source you want to enable.   **/
/**               [Optional if you defined DRIVER_HANDLE_ISR in             **/
/**                HAL_InterruptHandler.h]                                  **/
/**             + flagPointer => Pointer to flag with type of               **/
/**                              InterruptOcurrancyType to set if the       **/
/**                              interrupt happens "could be replaced with  **/
/**                              pointer to function to call (call-back     **/
/**                              function)".                                **/
/**                                                                         **/
/** Return: None.                                                           **/
/*****************************************************************************/
#ifdef DRIVER_HANDLE_ISR
void InterruptHandler_EnableInterrupt(InterruptSourceType InterruptSource,
                                      InterruptOcurrancyType * flagPointer)
#else
void InterruptHandler_EnableInterrupt(InterruptSourceType InterruptSource)
#endif
{
     InterruptHandler_EnbleGlobalInterrupt();
#ifdef DRIVER_HANDLE_ISR
         InterruptHandler_Flags[InterruptSource]=flagPointer;
#endif
         switch(InterruptSource)
         {
                 case INT_EXT0:
                      HAL_RegisterSetBit(INTCON_ADDRESS,INT0IE);
                 break;                                                     
                 case INT_EXT1:
                      HAL_RegisterSetBit(INTCON3_ADDRESS,INT1IE);
                 break;                                                     
                 case INT_EXT2:
                      HAL_RegisterSetBit(INTCON3_ADDRESS,INT2IE);
                 break;                                                     
                 case INT_RB:
                      HAL_RegisterSetBit(INTCON_ADDRESS,RBIE);
                 break;                                                     
                 case INT_TMR0:
                      HAL_RegisterSetBit(INTCON_ADDRESS,TMR0IE);
                 break;        
                 case INT_TMR1:
                      HAL_RegisterSetBit(PIE1_ADDRESS,TMR1IE);
                 break;        
                 case INT_TMR2:
                      HAL_RegisterSetBit(PIE1_ADDRESS,TMR2IE);
                 break;        
                 case INT_TMR3:
                      HAL_RegisterSetBit(PIE2_ADDRESS,TMR3IE);
                 break;        
                 case INT_CCP1:
                      HAL_RegisterSetBit(PIE1_ADDRESS,CCP1IE);
                 break;                                                       
                 case INT_CCP2:
                      HAL_RegisterSetBit(PIE1_ADDRESS,CCP2IE);
                 break;
                 case INT_TX:
                      HAL_RegisterSetBit(PIE1_ADDRESS,TXIE);
                 break;
                 case INT_RC:
                      HAL_RegisterSetBit(PIE1_ADDRESS,RCIE);
                 break;
                 case INT_SSP:
                      HAL_RegisterSetBit(PIE1_ADDRESS,SSPIE);
                 break;
                 case INT_AD:
                      HAL_RegisterSetBit(PIE1_ADDRESS,ADIE);
                 break;
                 case INT_PSP:
                      HAL_RegisterSetBit(PIE1_ADDRESS,PSPIE);
                 break;                                                     
                 case INT_HLVD:
                      HAL_RegisterSetBit(PIE2_ADDRESS,HLVDIE);
                 break;                                                     
                 case INT_BCL:
                      HAL_RegisterSetBit(PIE2_ADDRESS,BCLIE);
                 break;                                                     
                 case INT_EE:
                      HAL_RegisterSetBit(PIE2_ADDRESS,EEIE);
                 break;                                                     
                 case INT_CM:
                      HAL_RegisterSetBit(PIE2_ADDRESS,CMIE);
                 break;                                                       
                 case INT_OSCF:
                      HAL_RegisterSetBit(PIE2_ADDRESS,OSCFIE);
                 break;
         }
}

/*****************************************************************************/
/** Description: By a call to InterruptHandler_DisableInterrupt it disables **/
/**              specific iterrupt source passed its identifier.            **/
/**                                                                         **/
/** Parameters: + InterruptSource => Enum value defined as                  **/
/**                                  InterruptSourceType to know which      **/
/**                                  interrupt source you want to disable.  **/
/**                                                                         **/
/** Return: None.                                                           **/
/*****************************************************************************/
void InterruptHandler_DisableInterrupt(InterruptSourceType InterruptSource)
{
#ifdef DRIVER_HANDLE_ISR
     InterruptHandler_Flags[InterruptSource]=NULL;
#endif
         switch(InterruptSource)
         {
                 case INT_EXT0:
                      HAL_RegisterClearBit(INTCON_ADDRESS,INT0IE);
                 break;                                                     
                 case INT_EXT1:
                      HAL_RegisterClearBit(INTCON3_ADDRESS,INT1IE);
                 break;                                                     
                 case INT_EXT2:
                      HAL_RegisterClearBit(INTCON3_ADDRESS,INT2IE);
                 break;                                                     
                 case INT_RB:
                      HAL_RegisterClearBit(INTCON_ADDRESS,RBIE);
                 break;                                                     
                 case INT_TMR0:
                      HAL_RegisterClearBit(INTCON_ADDRESS,TMR0IE);
                 break;        
                 case INT_TMR1:
                      HAL_RegisterClearBit(PIE1_ADDRESS,TMR1IE);
                 break;        
                 case INT_TMR2:
                      HAL_RegisterClearBit(PIE1_ADDRESS,TMR2IE);
                 break;        
                 case INT_TMR3:
                      HAL_RegisterClearBit(PIE2_ADDRESS,TMR3IE);
                 break;        
                 case INT_CCP1:
                      HAL_RegisterClearBit(PIE1_ADDRESS,CCP1IE);
                 break;                                                       
                 case INT_CCP2:
                      HAL_RegisterClearBit(PIE1_ADDRESS,CCP2IE);
                 break;
                 case INT_TX:
                      HAL_RegisterClearBit(PIE1_ADDRESS,TXIE);
                 break;
                 case INT_RC:
                      HAL_RegisterClearBit(PIE1_ADDRESS,RCIE);
                 break;
                 case INT_SSP:
                      HAL_RegisterClearBit(PIE1_ADDRESS,SSPIE);
                 break;
                 case INT_AD:
                      HAL_RegisterClearBit(PIE1_ADDRESS,ADIE);
                 break;
                 case INT_PSP:
                      HAL_RegisterClearBit(PIE1_ADDRESS,PSPIE);
                 break;                                                     
                 case INT_HLVD:
                      HAL_RegisterClearBit(PIE2_ADDRESS,HLVDIE);
                 break;                                                     
                 case INT_BCL:
                      HAL_RegisterClearBit(PIE2_ADDRESS,BCLIE);
                 break;                                                     
                 case INT_EE:
                      HAL_RegisterClearBit(PIE2_ADDRESS,EEIE);
                 break;                                                     
                 case INT_CM:
                      HAL_RegisterClearBit(PIE2_ADDRESS,CMIE);
                 break;                                                       
                 case INT_OSCF:
                      HAL_RegisterClearBit(PIE2_ADDRESS,OSCFIE);
                 break;
         }
}

/*****************************************************************************/
/** Description: By a call to InterruptHandler_DisableGlobalInterrupt it    **/
/**              disables global interrupt.                                 **/
/**                                                                         **/
/** Parameters: None.                                                       **/
/**                                                                         **/
/** Return: None.                                                           **/
/*****************************************************************************/
void InterruptHandler_DisableGlobalInterrupt(void)
{
    /* Disable Global Interrupt Enable bit */
    HAL_RegisterClearBit(INTCON_ADDRESS,BIT_7);
    
    /* Disable all unmasked peripheral interrupts */
    HAL_RegisterClearBit(INTCON_ADDRESS,BIT_6);
}

/*****************************************************************************/
/** Description: By a call to InterruptHandler_EnbleGlobalInterrupt it      **/
/**              enables global interrupt.                                  **/
/**                                                                         **/
/** Parameters: None.                                                       **/
/**                                                                         **/
/** Return: None.                                                           **/
/*****************************************************************************/
void InterruptHandler_EnbleGlobalInterrupt(void)
{
    /* Enable Global Interrupt bit */
    HAL_RegisterSetBit(INTCON_ADDRESS,BIT_7);
    
    /* Enables all unmasked peripheral interrupts */
    HAL_RegisterSetBit(INTCON_ADDRESS,BIT_6);
}

/* Interrupt Service Routine handler */
#ifdef DRIVER_HANDLE_ISR
void interrupt (void)
{
     uint8 _Temp;
     _Temp=HAL_RegisterRead(INTCON_ADDRESS);
#ifdef INTERRUPT_EXT_0
     if(_Temp & (1<<INT0IF))
     {
          if(InterruptHandler_Flags[INT_EXT0]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_EXT0])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(INTCON_ADDRESS,INT0IF);
     }
#endif
#ifdef TIMER_0_INTERRUPT
     if(_Temp & (1<<TMR0IF))
     {
          if(InterruptHandler_Flags[INT_TMR0]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_TMR0])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(INTCON_ADDRESS,TMR0IF);
     }
#endif
#ifdef RB_PORT_CHANGE_INTERRUPT
     if(_Temp & (1<<RBIF))
     {
          if(InterruptHandler_Flags[INT_RB]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_RB])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(INTCON_ADDRESS,RBIF);
     }
#endif

     _Temp=HAL_RegisterRead(INTCON3_ADDRESS);

#ifdef INTERRUPT_EXT_1
     if(_Temp & (1<<INT1IF))
     {
          if(InterruptHandler_Flags[INT_EXT1]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_EXT1])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(INTCON3_ADDRESS,INT1IF);
     }
#endif
#ifdef INTERRUPT_EXT_2
     if(_Temp & (1<<INT2IF))
     {
          if(InterruptHandler_Flags[INT_EXT2]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_EXT2])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(INTCON3_ADDRESS,INT2IF);
     }
#endif

     _Temp=HAL_RegisterRead(PIR1_ADDRESS);

#ifdef TIMER_1_INTERRUPT
     if(_Temp & (1<<TMR1IF))
     {
          if(InterruptHandler_Flags[INT_TMR1]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_TMR1])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR1_ADDRESS,TMR1IF);
     }
#endif
#ifdef TIMER_2_INTERRUPT
     if(_Temp & (1<<TMR2IF))
     {
          if(InterruptHandler_Flags[INT_TMR2]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_TMR2])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR1_ADDRESS,TMR2IF);
     }
#endif
#ifdef CCP1_INTERRUPT
     if(_Temp & (1<<CCP1IF))
     {
          if(InterruptHandler_Flags[INT_CCP1]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_CCP1])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR1_ADDRESS,CCP1IF);
     }
#endif
#ifdef MASTER_SNCHRONOUS_SERIAL_PORT_INTERRUPT
     if(_Temp & (1<<SSPIF))
     {
          if(InterruptHandler_Flags[INT_SSP]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_SSP])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR1_ADDRESS,SSPIF);
     }
#endif
#ifdef EUSART_TRANSMIT_INTERRUPT
     if(_Temp & (1<<TXIF))
     {
          if(InterruptHandler_Flags[INT_TX]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_TX])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR1_ADDRESS,TXIF);
     }
#endif
#ifdef EUSART_RECEIVE_INTERRUPT
     if(_Temp & (1<<RCIF))
     {
          if(InterruptHandler_Flags[INT_RC]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_RC])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR1_ADDRESS,RCIF);
     }
#endif
#ifdef A_D_CONVERTER_INTERRUPT
     if(_Temp & (1<<ADIF))
     {
          if(InterruptHandler_Flags[INT_AD]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_AD])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR1_ADDRESS,ADIF);
     }
#endif
#ifdef PARALLEL_SLAVE_PORT_READ_WRITE_INTERRUPT
     if(_Temp & (1<<PSPIF))
     {
          if(InterruptHandler_Flags[INT_PSP]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_PSP])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR1_ADDRESS,PSPIF);
     }
#endif

     _Temp=HAL_RegisterRead(PIR2_ADDRESS);

#ifdef CCP2_INTERRUPT
     if(_Temp & (1<<CCP2IF))
     {
          if(InterruptHandler_Flags[INT_CCP2]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_CCP2])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR2_ADDRESS,CCP2IF);
     }
#endif
#ifdef TMR3_INTERRUPT
     if(_Temp & (1<<TMR3IF))
     {
          if(InterruptHandler_Flags[INT_TMR3]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_TMR3])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR2_ADDRESS,TMR3IF);
     }
#endif
#ifdef HIGH_LOW_VOLTAGE_DETECT_INTERRUPT
     if(_Temp & (1<<HLVDIF))
     {
          if(InterruptHandler_Flags[INT_HLVD]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_HLVD])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR2_ADDRESS,HLVDIF);
     }
#endif
#ifdef BUS_COLLISION_INTERRUPT
     if(_Temp & (1<<BCLIF))
     {
          if(InterruptHandler_Flags[INT_BCL]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_BCL])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR2_ADDRESS,BCLIF);
     }
#endif
#ifdef DATA_EEPROM_FLASH_WRITE_OPERATION_INTERRUPT
     if(_Temp & (1<<EEIF))
     {
          if(InterruptHandler_Flags[INT_EE]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_EE])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR2_ADDRESS,EEIF);
     }
#endif
#ifdef COMPARATOR_INTERRUPT
     if(_Temp & (1<<CMIF))
     {
          if(InterruptHandler_Flags[INT_CM]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_CM])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR2_ADDRESS,CMIF);
     }
#endif
#ifdef OSCILLATOR_FAIL_INTERRUPT
     if(_Temp & (1<<OSCFIF))
     {
          if(InterruptHandler_Flags[INT_OSCF]!= NULL_PTR)
          {
                  *(InterruptHandler_Flags[INT_OSCF])=INT_HAPPENED;
          }
          HAL_RegisterClearBit(PIR2_ADDRESS,OSCFIF);
     }
#endif

}
#endif