/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------
*        file  MCU.c
 *        brief  Implementation of MCU driver for ARM Arch. 
 * 
 *
 *
 *********************************************************************************************************************/




/*______INCLUDES________________________________*/
#include "Mcu.h"
#include "Mcu_Lcfg.h"
/*_______________________________________________*/

	
#define MCU_APPINT_ADD 							                        *((volatile uint32*)(MCU_APINT_BASE_ADD + MCU_APINT_OFFSET))
		
#define MCU_RESET_CAUSE_ADD  					                        *((volatile uint32*)(MCU_BASE_ADDRESS + MCU_RESET_CAUSE_OFFSET))

#define MCU_PLL_STAT_ADD                                                *((volatile uint32*)(MCU_BASE_ADDRESS + MCU_PLL_STAT_OFFSET))

#define MCU_GET_MODULE_OFFSET( MODULE_MODE , MODULE_NAME)               (MODULE_MODE + (MODULE_NAME * REGISTER_LENGTH_BYTS))

#define MCU_MIN_PLL_DIVISOR                                             5

#define MCU_MIN_PLL_SISDIV                                              2

#define MPU_PLL_STILL_LOCKED                                            0

/*___GLOBAL VARIABLES____________________________*/


volatile static  uint8 g_InitCheck                  = E_NOT_OK;   /*Check if Module is initialized or Not */
volatile static uint8 g_ClockInitCheck              = E_NOT_OK;   /*Check if Module is initialized or Not */
const static Mcu_ConfigType *g_CfgInitPtr;
const static Mcu_ModulesCfg *g_CfgInitModulesPtr;

volatile static uint8  g_ClockID ;


/*_________________________________________________*/

/*___FUNCTIONS DEFINITION _________________________*/
/******************************************************************************
* \Syntax          : void Mcu_PerformReset(void)      
* \Description     : Reset MicroController                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                       
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
#if (MCU_PERFORM_RESET_API == TRUE)    /*If MCU_PERFORM_RESET_API is False Function will not be Available  */

void Mcu_PerformReset(void)
{
	MCU_APPINT_ADD |= (MCU_VECTKEY_VALUE | MCU_RESET_TO_PERFORM) ;
}

#endif

/******************************************************************************
* \Syntax          : Mcu_RawResetType Mcu_GetResetRawValue( void )      
* \Description     : Find Cause for Reset                                     
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                       
* \Parameters (out): None                                                      
* \Return value:   : Mcu_RawResetType Reset raw value
*******************************************************************************/
Mcu_RawResetType Mcu_GetResetRawValue( void )
{
	return MCU_RESET_CAUSE_ADD ;    /*Return Cause of Reset */
}

/******************************************************************************
* \Syntax          : void MCU_init(const Mcu_ConfigType* ConfigPtr)      
* \Description     : Init The MCU Module                                     
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr Pointer to MCU driver configuration set.                       
* \Parameters (out): None                                                      
* \Return value:   : None                                  
*******************************************************************************/
void MCU_init(const Mcu_ConfigType* ConfigPtr)
{
	g_CfgInitPtr            = ConfigPtr ;         /*Get Configuration of Clock From User*/

	g_CfgInitModulesPtr     = ConfigModulesArr ;  /*Get Module Clock Configuration from User */

	g_InitCheck             = E_OK;               /*To Check That Function Init is Called*/
}

/******************************************************************************
* \Syntax          : MCU_ErrorReturn Mcu_InitClock( MCU_Clock_Type ClockSetting)       
* \Description     : Init Clock                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : MCU_Clock_Type (Clock ID)                       
* \Parameters (out): None                                                      
* \Return value:   : MCU_ErrorReturn (Error Status)                                  
*******************************************************************************/
MCU_ErrorReturn Mcu_InitClock( MCU_Clock_Type ClockSetting) 
{
	uint8  u8_ErrorStatus 	= E_OK , loop , u8_CheckClockID = FALSE , Bit_BandStart , Bit_BandEnd ;
	uint16  Sys_Div;              /*Calculate System Frequency Divisor*/
	
	if(g_InitCheck == E_OK)  /*Check it Init Function is Called and Configuration is seen to this Function*/
	{
		/*Clock Mode in RCC */
		for(loop = 0 ; loop < MCU_NUMBER_OF_CFGS ; loop ++ )   /*Find ID in Entered Cfg Array*/
		{
			if(g_CfgInitPtr[loop].clock_TypeID == ClockSetting )
			{
				g_ClockID = loop ;     /*Find Index of the Wanted ID*/
				u8_CheckClockID = TRUE ;  /*Raise Flag */
			}
		}
			
		if(u8_CheckClockID == TRUE)  /*Check if ID Exist */
		{
			if(g_CfgInitPtr[g_ClockID].clock_Mode == MCU_RUN_MODE ) /*If Entered Mode is Run Mode*/
			{
				BIT_BANDING(MCU_PRIVATE_PRI_BASE_ADD, MCU_PRIVATE_PRI_BASE_ALIAS, MCU_BASE_ADDRESS,MCU_RCC_OFFSET,MCU_RCC_ACG,STD_LOW);		/*Clear Bit in Run Mode */
			}
			else if(g_CfgInitPtr[g_ClockID].clock_Mode == MCU_SLEEP_MODE ||  g_CfgInitPtr[g_ClockID].clock_Mode == MCU_DEEP_SLEEP_MODE )
			{
			    BIT_BANDING(MCU_PRIVATE_PRI_BASE_ADD, MCU_PRIVATE_PRI_BASE_ALIAS, MCU_BASE_ADDRESS,MCU_RCC_OFFSET,MCU_RCC_ACG,STD_HIGH);   /*Set Bit in Sleep or Deepsleep Mode */
			}
			else
			{
				u8_ErrorStatus = E_NOT_OK ; /*Return Error*/
			}
			
			if(u8_ErrorStatus == E_OK) /*Check if No Error Detected in previous Lines*/
			{
				if(g_CfgInitPtr[g_ClockID].clock_Source == MCU_CLOCK_SOURCE_MAIN_OSC)  /*If The Chosen Oscillator is Main External Oscillator */
				{
				    BIT_BANDING(MCU_PRIVATE_PRI_BASE_ADD, MCU_PRIVATE_PRI_BASE_ALIAS, MCU_BASE_ADDRESS,MCU_RCC_OFFSET,MCU_RCC_MOSCDIS,STD_LOW);     /*Clear Bit in Run Mode */

				    Bit_BandStart = MCU_RCC_CRYSTAL_XTAL_START;  /*Get Start Bit of Register RCC of XTAL Bits*/
				    Bit_BandEnd =   MCU_RCC_CRYSTAL_XTAL_END ;   /*Get end Bit of Register RCC of XTAL Bits*/

				    BIT_GROUP_BANDING(MCU_PRIVATE_PRI_BASE_ADD , MCU_PRIVATE_PRI_BASE_ALIAS , MCU_BASE_ADDRESS , MCU_RCC_OFFSET , Bit_BandStart , Bit_BandEnd , MCU_APPLIED_FREQUENCY / 100); /*The first two Bits in MCU_APPLIED_FREQUENCY refer to value needed for the XTAL */
				}
				else if(g_CfgInitPtr[g_ClockID].clock_Source <= MCU_CLOCK_SOURCE_32_768KHZ_EXT)
				{
				    BIT_BANDING(MCU_PRIVATE_PRI_BASE_ADD, MCU_PRIVATE_PRI_BASE_ALIAS, MCU_BASE_ADDRESS,MCU_RCC_OFFSET,MCU_RCC_MOSCDIS,STD_HIGH);     /*Set Bit To disable Main Oscillator */
				}
				else
				{
				    u8_ErrorStatus = E_NOT_OK; /*Error Status : Error*/
				}

                if(u8_ErrorStatus == E_OK)  /*Check if No Error Detected in previous Lines*/
                {

                    Bit_BandStart = MCU_RCC2_OSCSRC2_START;  /*Start Bit of Clock source in RCC2*/
                    Bit_BandEnd =   MCU_RCC2_OSCSRC2_END ;   /*End Bit of Clock source in RCC2*/

                    if(g_CfgInitPtr[g_ClockID].clock_Source == MCU_CLOCK_SOURCE_MAIN_OSC)
                    {
                        if(g_CfgInitPtr[g_ClockID].Pll_Use == MCU_PLL_ENABLE)
                        {
                            BIT_BANDING(MCU_PRIVATE_PRI_BASE_ADD, MCU_PRIVATE_PRI_BASE_ALIAS, MCU_BASE_ADDRESS,MCU_RCC_OFFSET,MCU_RCC_USESYSDIV,STD_HIGH);  /*Enable Click division Bit this bit is forced to be set if we use PLL*/
                        }
                        else
                        {
                            /*Nothing*/
                        }
                        BIT_GROUP_BANDING(MCU_PRIVATE_PRI_BASE_ADD , MCU_PRIVATE_PRI_BASE_ALIAS , MCU_BASE_ADDRESS , MCU_RCC2_OFFSET , Bit_BandStart , Bit_BandEnd , MCU_CLOCK_SOURCE_MAIN_OSC);
                    }
                    else if (g_CfgInitPtr[g_ClockID].clock_Source == MCU_CLOCK_SOURCE_PREC_INT_OSC)
                    {
                        if(g_CfgInitPtr[g_ClockID].Pll_Use == MCU_PLL_ENABLE)
                        {
                            BIT_BANDING(MCU_PRIVATE_PRI_BASE_ADD, MCU_PRIVATE_PRI_BASE_ALIAS, MCU_BASE_ADDRESS,MCU_RCC_OFFSET,MCU_RCC_USESYSDIV,STD_HIGH);   /*Enable Click division Bit this bit is forced to be set if we use PLL*/
                        }
                        else
                        {
                            /*Nothing*/
                        }
                        BIT_GROUP_BANDING(MCU_PRIVATE_PRI_BASE_ADD , MCU_PRIVATE_PRI_BASE_ALIAS , MCU_BASE_ADDRESS , MCU_RCC2_OFFSET , Bit_BandStart , Bit_BandEnd , MCU_CLOCK_SOURCE_PREC_INT_OSC);
                    }
                    else if (g_CfgInitPtr[g_ClockID].clock_Source == MCU_CLOCK_SOURCE_PREC_INT_OSC_4) /*If Precision Oscillator is Selected */
                    {
                        BIT_GROUP_BANDING(MCU_PRIVATE_PRI_BASE_ADD , MCU_PRIVATE_PRI_BASE_ALIAS , MCU_BASE_ADDRESS , MCU_RCC2_OFFSET , Bit_BandStart , Bit_BandEnd , MCU_CLOCK_SOURCE_PREC_INT_OSC_4);
                    }
                    else if (g_CfgInitPtr[g_ClockID].clock_Source == MCU_CLOCK_SOURCE_LOW_FREQ_INT_OSC) /*If Precision Oscillator / 4 is Selected */
                    {
                        BIT_GROUP_BANDING(MCU_PRIVATE_PRI_BASE_ADD , MCU_PRIVATE_PRI_BASE_ALIAS , MCU_BASE_ADDRESS , MCU_RCC2_OFFSET , Bit_BandStart , Bit_BandEnd , MCU_CLOCK_SOURCE_LOW_FREQ_INT_OSC);
                    }
                    else if (g_CfgInitPtr[g_ClockID].clock_Source == MCU_CLOCK_SOURCE_32_768KHZ_EXT) /*If external 32.768 Oscillator is Selected */
                    {
                        BIT_GROUP_BANDING(MCU_PRIVATE_PRI_BASE_ADD , MCU_PRIVATE_PRI_BASE_ALIAS , MCU_BASE_ADDRESS , MCU_RCC2_OFFSET , Bit_BandStart , Bit_BandEnd , MCU_CLOCK_SOURCE_32_768KHZ_EXT);
                    }
                    else
                    {
                        u8_ErrorStatus = E_NOT_OK; /*Error Status : Error */
                    }

                }
                else
                {

                }

                if(u8_ErrorStatus == E_OK)  /*Check if No Error Detected in previous Lines*/
                {

                    if(g_CfgInitPtr[g_ClockID].Pll_Use == MCU_PLL_ENABLE) /*Check is PLL is Enabled */
                    {
                        if(g_CfgInitPtr[g_ClockID].clock_Source == MCU_CLOCK_SOURCE_MAIN_OSC || g_CfgInitPtr[g_ClockID].clock_Source == MCU_CLOCK_SOURCE_PREC_INT_OSC) /*PLL Can Be Enabled only in Main Oscillator and Precision Oscillator */
                        {
                            BIT_BANDING(MCU_PRIVATE_PRI_BASE_ADD, MCU_PRIVATE_PRI_BASE_ALIAS, MCU_BASE_ADDRESS,MCU_RCC2_OFFSET,MCU_RCC2_PWRDN2,STD_LOW); /*Clear Disable PLL Bit */

                            BIT_BANDING(MCU_PRIVATE_PRI_BASE_ADD, MCU_PRIVATE_PRI_BASE_ALIAS, MCU_BASE_ADDRESS,MCU_RCC2_OFFSET,MCU_RCC2_DIV400,STD_HIGH); /*Set DIV400 Bit */

                            if(g_CfgInitPtr[g_ClockID].Frequency_Value < MCU_PLL_MAX_FREQUENCY_TO_SYSTEM_MHz && g_CfgInitPtr[g_ClockID].Frequency_Value > MCU_PLL_MIN_FREQUENCY_TO_SYSTEM_MHz)
                            {
                                Sys_Div = ( MCU_PLL_FREQUENCY_OUTPUT_MHz  /  g_CfgInitPtr[g_ClockID].Frequency_Value)  ;

                                if(Sys_Div >= MCU_MIN_PLL_DIVISOR)
                                {
                                    if(Sys_Div % 2 == 0 )  /*Check if Number is Even */
                                    {
                                        Sys_Div -= (MCU_MIN_PLL_DIVISOR + 1); /*Equation Between Frequency Entered and Value Written in Register */
                                        Sys_Div /= 2;  /*Find Number of Steps Needed */
                                        Sys_Div += MCU_MIN_PLL_SISDIV ; /*Add Number of Steps to Base Step to Get Current step  */

                                        BIT_BANDING(MCU_PRIVATE_PRI_BASE_ADD, MCU_PRIVATE_PRI_BASE_ALIAS, MCU_BASE_ADDRESS,MCU_RCC2_OFFSET,MCU_RCC2_SYSDIV2LSB,STD_HIGH); /*Set  bit if Number is Even*/
                                    }
                                    else  /* Number is Odd */
                                    {
                                        Sys_Div -= (MCU_MIN_PLL_DIVISOR);  /*Equation Between Frequency Entered and Value Written in Register */
                                        Sys_Div /= 2;  /*Find Number of Steps Needed */
                                        Sys_Div += MCU_MIN_PLL_SISDIV ;  /*Add Number of Steps to Base Step to Get Current step  */

                                        BIT_BANDING(MCU_PRIVATE_PRI_BASE_ADD, MCU_PRIVATE_PRI_BASE_ALIAS, MCU_BASE_ADDRESS,MCU_RCC2_OFFSET,MCU_RCC2_SYSDIV2LSB,STD_LOW); /*clear bit if Number is Odd*/
                                    }

                                    Bit_BandStart = MCU_RCC2_SYSDIV_START;
                                    Bit_BandEnd =   MCU_RCC2_SYSDIV_END ;

                                    BIT_GROUP_BANDING(MCU_PRIVATE_PRI_BASE_ADD , MCU_PRIVATE_PRI_BASE_ALIAS , MCU_BASE_ADDRESS , MCU_RCC2_OFFSET , Bit_BandStart , Bit_BandEnd , Sys_Div);

                                }
                                else
                                {
                                    u8_ErrorStatus = E_NOT_OK ;  /*Error Status : Error */
                                }
                            }
                            else
                            {
                                u8_ErrorStatus = E_NOT_OK ; /*Error Status : Error */
                            }

                        }
                        else
                        {
                            u8_ErrorStatus = E_NOT_OK ;  /*Error Status : Error */
                        }
                    }
                    else if(g_CfgInitPtr[g_ClockID].Pll_Use == MCU_PLL_DISABLE)
                    {
                        BIT_BANDING(MCU_PRIVATE_PRI_BASE_ADD, MCU_PRIVATE_PRI_BASE_ALIAS, MCU_BASE_ADDRESS,MCU_RCC2_OFFSET,MCU_RCC2_PWRDN2,STD_HIGH);

                        if((MCU_APPLIED_FREQUENCY %100) > MCU_MIN_FREQUENCY_APPLIED && (MCU_APPLIED_FREQUENCY % 100) < MCU_MAX_FREQUENCY_APPLIED ) /*Check if Entered Frequency is Between The supported Range */
                        {
                            Sys_Div = (( MCU_APPLIED_FREQUENCY % 100 )  /  g_CfgInitPtr[g_ClockID].Frequency_Value) - 1 ; /*Equation Between Frequency Entered and Value Written in Register */

                            Bit_BandStart = MCU_RCC2_SYSDIV_START; /*Get Start of System Division Bits*/
                            Bit_BandEnd =   MCU_RCC2_SYSDIV_END ; /*Get End  of System Division Bits*/

                            BIT_GROUP_BANDING(MCU_PRIVATE_PRI_BASE_ADD , MCU_PRIVATE_PRI_BASE_ALIAS , MCU_BASE_ADDRESS , MCU_RCC2_OFFSET , Bit_BandStart , Bit_BandEnd , Sys_Div);
                        }
                        else
                        {
                            u8_ErrorStatus = E_NOT_OK ; /*Error Status : Error */
                        }
                    }
                    else
                    {
                        u8_ErrorStatus = E_NOT_OK; /*Error Status : Error */
                    }

                    BIT_BANDING(MCU_PRIVATE_PRI_BASE_ADD, MCU_PRIVATE_PRI_BASE_ALIAS, MCU_BASE_ADDRESS,MCU_RCC2_OFFSET,MCU_USE_RCC2,STD_HIGH); /*RCC2 Override RCC */

                }
                else
                {
                    u8_ErrorStatus = E_NOT_OK ; /*Error Status : Error */
                }
            }
			else
			{
			    u8_ErrorStatus = E_NOT_OK ; /*Return Error*/
			}

		}
		else
		{
		    u8_ErrorStatus = E_NOT_OK ; /*Return Error*/
		}

		if(u8_ErrorStatus == E_OK)
		{
		    g_ClockInitCheck = E_OK ;

		    for(loop = 0 ; loop < MCU_NUMBER_OF_MODULES ; loop ++)
		    {
		        BIT_BANDING(MCU_PRIVATE_PRI_BASE_ADD, MCU_PRIVATE_PRI_BASE_ALIAS, MCU_BASE_ADDRESS,MCU_GET_MODULE_OFFSET( g_CfgInitModulesPtr[loop].clock_Mode , g_CfgInitModulesPtr[loop].module_Name),g_CfgInitModulesPtr[loop].module_Port,STD_HIGH);
		    }
		}
		else
		{
		    u8_ErrorStatus = E_NOT_OK ; /*Error Status : Error */
		}

	}
	else
	{
	    u8_ErrorStatus = E_NOT_OK;  /*Error Status : Error */
	}


	return u8_ErrorStatus;
}

/******************************************************************************
* \Syntax          : MCU_ErrorReturn Mcu_DistributePllClock( void)
* \Description     : Distribute PLL Clock
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : MCU_ErrorReturn (Error Status)
*******************************************************************************/
MCU_ErrorReturn Mcu_DistributePllClock(void)
{
    uint8 u8_ErrorStatus = E_OK ;

    if(g_InitCheck == E_OK)
    {
        if(g_ClockInitCheck == E_OK)
        {
            if(g_CfgInitPtr[g_ClockID].Pll_Use == MCU_PLL_ENABLE)
            {
                BIT_BANDING(MCU_PRIVATE_PRI_BASE_ADD, MCU_PRIVATE_PRI_BASE_ALIAS, MCU_BASE_ADDRESS,MCU_RCC2_OFFSET,MCU_RCC2_BYPASS2,STD_LOW);  /*Enable Distribution Bit if we use PLL*/
            }
        }
        else
        {
            u8_ErrorStatus = E_NOT_OK ;  /*Error Status : Error */
        }
    }
    else
    {
        u8_ErrorStatus = E_NOT_OK ;  /*Error Status : Error */
    }

    return u8_ErrorStatus ;
}

/******************************************************************************
* \Syntax          : MCU_ErrorReturn Mcu_GetPllStatus(void);
* \Description     : Get PLL Clock Locked or unlocked
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : MCU_Enum_PLL_Status (Locked or Unlocked)
*******************************************************************************/
MCU_Enum_PLL_Status Mcu_GetPllStatus(void)
{
    MCU_Enum_PLL_Status u8_Pll_Status;

    if(g_InitCheck == E_OK)  /*Check if MCU init Function is called*/
    {
        if(g_ClockInitCheck == E_OK)  /*Check if Init Clock Function is Passed*/
        {
            if(g_CfgInitPtr[g_ClockID].Pll_Use == MCU_PLL_ENABLE)  /*Check if PLL is Enabled*/
            {
                if(MCU_PLL_STAT_ADD == MPU_PLL_STILL_LOCKED)
                {
                    u8_Pll_Status = MCU_PLL_LOCKED ;  /*PLL Status : Locked*/
                }
                else
                {
                    u8_Pll_Status = MCU_PLL_UNLOCKED ; /*PLL Status : Unlocked*/
                }
            }
            else
            {
                u8_Pll_Status = MCU_PLL_STATUS_UNDEFINED ; /*PLL Status : Undefined*/
            }
        }
        else
        {
            u8_Pll_Status = MCU_PLL_STATUS_UNDEFINED ; /*PLL Status : Undefined*/
        }
    }
    else
    {
        u8_Pll_Status = MCU_PLL_STATUS_UNDEFINED ; /*PLL Status : Undefined*/
    }

    return u8_Pll_Status ;   /*Return PLL Status*/
}
