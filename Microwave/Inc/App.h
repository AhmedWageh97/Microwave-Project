/*****************************************************************************/
/** File:    App.h                                                          **/
/**                                                                         **/
/** Description: This file define all needed variables, data-types and      **/
/**              files needed for Application.                              **/
/**                                                                         **/
/** Author:  Ahmed Wageh                                                    **/
/**                                                                         **/
/** Date:    24/2/2020                                                      **/
/*****************************************************************************/

#ifndef _APP_H_
#define _APP_H_

/* Inclusion */
#include "StdTypes.h"
#include "HAL.h"
#include "Module_Keypad.h"
#include "Lcd_Config.h" /* contain all configurauins of LCD */
#include "Keypad_Config.h" /* contain all configurauins of Keypad */
#include "App_Functions.h" /* contain app functions */


/* Externed variables */
extern APP_stateType ProgramState;  /* Extern from APP_Function.c */
extern uint8 TimerIntCounter;  /* Extern from APP_Function.c */
extern HAL_Timer0_ConfigType Timer0_Configurations; /* Extern from APP_Function.c */




#endif /* _APP_H_ */