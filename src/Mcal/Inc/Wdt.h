/*
 * Wdt.h
 *
 *  Created on: Jul 31, 2020
 *      Author: kh
 */

#ifndef WDT_H_
#define WDT_H_
#include "Platform_Types.h"
#include "Std_Types.h"
#include "Bit_Math.h"

#define WDG_1_CLOCK_MHz 16
#define WDG_0_SYSTEM_CLOCK_Mhz  16

typedef enum
{
    Wdg_STANDARD_INTERRUPT ,
    Wdg_NON_MASKABLE_INTERRUPT
}Wdg_InterruptType;

typedef uint16 Wdg_InitialTimeout ;

typedef uint16 Wdg_MaxTimeoutWDT ;

typedef struct
{
    Wdg_InterruptType       Interrupt_Type;
    Wdg_InitialTimeout      Initial_TimeOut;
    Wdg_MaxTimeoutWDT       Max_TimeOut;
}Wdg_ConfigType;

/******************************************************************************
* \Syntax          : void Wdg_Init( const Wdg_ConfigType* ConfigPtr);
* \Description     : Wdg Timer Initialization
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : ConfigPtr
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void Wdg_Init( const Wdg_ConfigType* ConfigPtr);

/******************************************************************************
* \Syntax          : void Wdg_SetTriggerCondition( uint16 timeout );
* \Description     : Trigger Wdg Timer
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : timeout in ms
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void Wdg_SetTriggerCondition( uint16 timeout );

#endif /* WDT_H_ */
