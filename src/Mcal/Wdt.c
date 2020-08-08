/*
 * Wdt.c
 *
 *  Created on: Jul 31, 2020
 *      Author: kh
 */

#include "WDT_ARM_REG.h"
#include "Wdt.h"
#include "Wdt_Cfg.h"

#define WDG_ADDRESS(BASE, OFFSET)  (*((volatile uint32 *) (BASE + OFFSET)))
#define WDG_Ms_TO_s 1000
#define WDG_WRC_AVAILABLE    1

uint16 g_MaxTimeOut ;
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
void Wdg_Init( const Wdg_ConfigType* ConfigPtr)
{
    /*1. Load the WDTLOAD register with the desired timer load value.*/
    WDG_ADDRESS(WDG_0_BASE_ADDRESS, WDG_LOAD_OFFSET) =  ((ConfigPtr->Initial_TimeOut * WDG_0_SYSTEM_CLOCK_Mhz * WDG_Ms_TO_s   ) );  /*Convert from ms to Ticks*/
    /*2. If WDT1, wait for the WRC bit in the WDTCTL register to be set.*/
    /*while((GET_BIT(WDG_ADDRESS(WDG_1_BASE_ADDRESS , WDG_CTL_OFFSET) , WDG_WRC_BIT )) != WDG_WRC_AVAILABLE) ;*/
    /*3. If the Watchdog is configured to trigger system resets, set the RESEN bit in the WDTCTL register.*/
    if(WDG_TRIGGER_RESET == ENABLE)
    {
        BIT_BANDING(WDG_PRIVATE_PRI_BASE_ADD, WDG_PRIVATE_PRI_BASE_ALIAS, WDG_0_BASE_ADDRESS, WDG_CTL_OFFSET , WDG_RESET_ENABLE_BIT , STD_HIGH);
    }

    /*4. If WDT1, wait for the WRC bit in the WDTCTL register to be set.*/
    /*while((GET_BIT(WDG_ADDRESS(WDG_1_BASE_ADDRESS , WDG_CTL_OFFSET) , WDG_WRC_BIT )) != WDG_WRC_AVAILABLE) ;*/

//    BIT_BANDING(WDG_PRIVATE_PRI_BASE_ADD, WDG_PRIVATE_PRI_BASE_ALIAS, WDG_0_BASE_ADDRESS, WDG_CTL_OFFSET , WDG_INTERRUPT_TYPE_BIT , ConfigPtr->Interrupt_Type);

    /*while((GET_BIT(WDG_ADDRESS(WDG_1_BASE_ADDRESS , WDG_CTL_OFFSET) , WDG_WRC_BIT )) != WDG_WRC_AVAILABLE) ;*/

    /*5. Set the INTEN bit in the WDTCTL register to enable the Watchdog, enable interrupts, and lock the control register.*/

    g_MaxTimeOut = ConfigPtr->Max_TimeOut ;

    BIT_BANDING(WDG_PRIVATE_PRI_BASE_ADD, WDG_PRIVATE_PRI_BASE_ALIAS, WDG_0_BASE_ADDRESS, WDG_CTL_OFFSET , WDG_INTERRUPT_ENABLE_BIT , STD_HIGH);

}

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
void Wdg_SetTriggerCondition( uint16 timeout )
{
    if(timeout <= g_MaxTimeOut)
    {
        WDG_ADDRESS(WDG_0_BASE_ADDRESS, WDG_LOAD_OFFSET) =  ((timeout * WDG_0_SYSTEM_CLOCK_Mhz * WDG_Ms_TO_s   ) );  /*Convert from ms to Ticks*/

        //while((GET_BIT(WDG_ADDRESS(WDG_0_BASE_ADDRESS , WDG_CTL_OFFSET) , WDG_WRC_BIT )) != WDG_WRC_AVAILABLE) ;
    }
}
