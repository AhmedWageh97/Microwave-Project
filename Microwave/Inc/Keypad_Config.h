/*****************************************************************************/
/** File:    Keypad_Config.h                                                **/
/**                                                                         **/
/** Description: This file define all needed configurations for keypad      **/
/**              Driver.                                                    **/
/**                                                                         **/
/** Author:  Ahmed Wageh                                                    **/
/**                                                                         **/
/** Date:    24/2/2020                                                      **/
/*****************************************************************************/

#ifndef _KEYPAD_CONFIG_H_
#define _KEYPAD_CONFIG_H_

/* Inclusion */
#include "Module_Keypad.h"

/* Keypad Configurations */
Keypad_ConfigType Keypad1 =  {
        4,
        3,
        {
            {PORTD_BASE_ADDRESS,PIN_3,OUTPUT},
            {PORTD_BASE_ADDRESS,PIN_2,OUTPUT},
            {PORTD_BASE_ADDRESS,PIN_1,OUTPUT},
            {PORTD_BASE_ADDRESS,PIN_0,OUTPUT}
        },
        {
            {PORTB_BASE_ADDRESS,PIN_0,INPUT},
            {PORTB_BASE_ADDRESS,PIN_1,INPUT},
            {PORTB_BASE_ADDRESS,PIN_2,INPUT}
        },
        {
            {'1','2','3'},
            {'4','5','6'},
            {'7','8','9'},
            {'*','0','#'}
        }
};

keypad_returnDataType Keypad1_Read=KEYPAD_NOT_PRESSED;

#endif /* _KEYPAD_CONFIG_H_ */