/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  < MCU.h >
 *       Module:  -MCU 
 *  Description:  <Header file for MCU module to initialize the Module>     
 *  
 *********************************************************************************************************************/

#ifndef MCU_H_
#define MCU_H_
/*____________________________________________________________________________________

		INCLUDES                                                    
_______________________________________________________________________________________*/
#include "Platform_Types.h"
#include "Std_Types.h" 
#include "Bit_Math.h"

#include "Mcu_Cfg.h"
#include "MCU_ARM_REG.h"
/*____________________________________________________________________________________

		MACROS                                                    
_______________________________________________________________________________________*/

#define MCU_RESET_MOSCFAIL 						16																										
#define MCU_RESET_WATCH_DOG_1 					5
#define MCU_RESET_SOFTWARE						4
#define MCU_RESET_WATCH_DOG_0 					3
#define MCU_RESET_BROWN_OUT						2
#define MCU_RESET_POWER_ON						1
#define MCU_RESET_EXTERNAL						0
			
#define MCU_RESET_SOFTWARE_CORE 		  		1
#define MCU_RESET_SOFTWARE_MICRO		 		4


/*______CLOCK SOURCES___________________________*/         
#define MCU_CLOCK_SOURCE_MAIN_OSC			 	0         
#define MCU_CLOCK_SOURCE_PREC_INT_OSC 			1
#define MCU_CLOCK_SOURCE_PREC_INT_OSC_4 		2
#define MCU_CLOCK_SOURCE_LOW_FREQ_INT_OSC 		3
#define MCU_CLOCK_SOURCE_32_768KHZ_EXT 			7

/*__________________________________________________
       MODULE NAMES
____________________________________________________*/
#define MCU_WD      							0
#define MCU_TIMER   							1
#define MCU_GPIO    							2
#define MCU_DMA     							3
#define MCU_HIB     							4
#define MCU_UART    							5
#define MCU_SSI     							6
#define MCU_I2C     							7
#define MCU_USB     							8
#define MCU_CAN     							9
#define MCU_ADC     							10
#define MCU_ACMP    							11
#define MCU_PWM     							12
#define MCU_QEI     							13
#define MCU_EEPROM  							14
#define MCU_WTIMER  							15

/*__________________________________________________
       MODULE CAPACITY
____________________________________________________*/
#define MCU_WD_MAX 								2
#define MCU_TIMER_MAX	 						6
#define MCU_GPIO_MAX  							6
#define MCU_DMA_MAX  							1
#define MCU_HIB_MAX  							1
#define MCU_UART_MAX  							8
#define MCU_SSI_MAX  							4
#define MCU_I2C_MAX  							4
#define MCU_USB_MAX  							1
#define MCU_CAN_MAX  							2
#define MCU_ADC_MAX  							2
#define MCU_ACMP_MAX  							1
#define MCU_PWM_MAX  							2
#define MCU_QEI_MAX  							2
#define MCU_EEPROM_MAX      					1
#define MCU_WTIMER_MAX  						6
/*____________________________________________________*/

#define MCU_PLL_FREQUENCY_OUTPUT_MHz            400

#define MCU_PLL_MAX_FREQUENCY_TO_SYSTEM_MHz     80
#define MCU_PLL_MIN_FREQUENCY_TO_SYSTEM_MHz     3
#define MCU_MAX_FREQUENCY_APPLIED              25
#define MCU_MIN_FREQUENCY_APPLIED              4

/*SUPPORTED CRYSTAL VALUES*/
 #define MPU_CRYSTAL_FREQUENCY_4_MHz            604
 #define MPU_CRYSTAL_FREQUENCY_4_096_MHz        704
 #define MPU_CRYSTAL_FREQUENCY_4_9152_MHz       805
 #define MPU_CRYSTAL_FREQUENCY_5_MHz            905
 #define MPU_CRYSTAL_FREQUENCY_5_12_MHz         1005
 #define MPU_CRYSTAL_FREQUENCY_6 MHz            1106
 #define MPU_CRYSTAL_FREQUENCY_6_144_MHz        1206
 #define MPU_CRYSTAL_FREQUENCY_7_3728_MHz       1308
 #define MPU_CRYSTAL_FREQUENCY_8_MHz            1408
 #define MPU_CRYSTAL_FREQUENCY_8_192_MHz        1508
 #define MPU_CRYSTAL_FREQUENCY_10_0_MHz         1610
 #define MPU_CRYSTAL_FREQUENCY_12_0_MHz         1712
 #define MPU_CRYSTAL_FREQUENCY_12_288_MHz       1812
 #define MPU_CRYSTAL_FREQUENCY_13_56_MHz        1913
 #define MPU_CRYSTAL_FREQUENCY_14_31818_MHz     2014
 #define MPU_CRYSTAL_FREQUENCY_16_0_MHz         2116
 #define MPU_CRYSTAL_FREQUENCY_16_384_MHz       2216
 #define MPU_CRYSTAL_FREQUENCY_18_0_MHz         2318
 #define MPU_CRYSTAL_FREQUENCY_20_0_MHz         2420
 #define MPU_CRYSTAL_FREQUENCY_24_0_MHz         2524
 #define MPU_CRYSTAL_FREQUENCY_25_0_MHz         2625
/*____________________________________________________________________________________

		GLOBAL TYPES AND STRUCTURES                                                   
_______________________________________________________________________________________*/

typedef uint8 MCU_Clock_Type ;
typedef uint32 MCU_Clock_Mode ;
typedef uint8 MCU_Clock_Source ;
typedef uint8 MCU_Frequency_Value ;
typedef uint32 Mcu_RawResetType;
typedef uint8 MCU_ErrorReturn;
typedef uint8 MCU_ModuleName ;
typedef uint8 MCU_ModulePortNumber ;
/*_________________________________*/
typedef enum
{
	MCU_PLL_LOCKED ,
	
	MCU_PLL_UNLOCKED ,

	MCU_PLL_STATUS_UNDEFINED
		
}MCU_Enum_PLL_Status ;
/*_________________________________*/
typedef enum
{
	MCU_PLL_ENABLE ,
	
	MCU_PLL_DISABLE
		
}MCU_Enum_PLL_USE ;
/*_________________________________*/
typedef struct
{	
	MCU_Clock_Type 			clock_TypeID;
	MCU_Clock_Mode 			clock_Mode;
	MCU_Clock_Source 		clock_Source ;
	MCU_Enum_PLL_USE	   	Pll_Use;
	MCU_Frequency_Value     Frequency_Value;
		
}Mcu_ConfigType;


typedef struct
{
    MCU_Clock_Mode          clock_Mode;
    MCU_ModuleName          module_Name ;
    MCU_ModulePortNumber    module_Port ;

}Mcu_ModulesCfg;
/*_________________________________*/

/*____________________________________________________________________________________

		FUNCTIONS PROTOTYPES                                                   
_______________________________________________________________________________________*/



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
extern	void MCU_init(const Mcu_ConfigType* ConfigPtr);

/******************************************************************************
* \Syntax          : Mcu_RawResetType Mcu_GetResetRawValue( void )      
* \Description     : Find Cause for Reset                                     
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                       
* \Parameters (out): None                                                      
* \Return value:   : Mcu_RawResetType Reset raw valu                                  
*******************************************************************************/
extern	Mcu_RawResetType Mcu_GetResetRawValue( void );
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
#if (MCU_PERFORM_RESET_API == TRUE)
extern	void Mcu_PerformReset(void);
#endif

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
MCU_ErrorReturn Mcu_InitClock( MCU_Clock_Type ClockSetting) ;

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
MCU_ErrorReturn Mcu_DistributePllClock(void);

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
MCU_Enum_PLL_Status Mcu_GetPllStatus(void);



#endif
