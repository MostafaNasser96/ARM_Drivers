/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  < Nvic_Cfg.h >
 *       Module:  -NVIC 
 *
 *  Description:  <Header file for NVIC Cfg module to initialize the Module>     
 *  
 *********************************************************************************************************************/

#ifndef NVIC_CFG_H_
#define NVIC_CFG_H_

/*______________________________________________________________________
        DEFINES
  ______________________________________________________________________*/

#define NVIC_NUM_OF_ENABLED_INT             4  				/*Number of Enabled Interrupts*/

/*____HARDWARE CFG____*/

#define NUMBER_OF_BITS 						32   			/*Number of Bits per Register*/

#define NVIC_OFFSET_BYTES 					4    			/*Number of Offset Bytes Between Registers */

#define MAX_INTERRUPT_NUMBER 				138             /*Number of Interrupts Supported*/



/*____BASE ADDRESS CFG____*/

#define NVIC_BASE_INT 						0xE000E000    	/*NVIC Base Address*/

#define NVIC_EN_BASE_OFFSET 				0x00000100    	/*NVIC Enable Register offset */

#define NVIC_APINT_OFFSET 					0x00000D0C    	/*APINT Register offset */

#define NVIC_VECTKEY_VALUE 					0x5FA << 16    	/*APINT Vect Key to change Value */

#define NVIC_PRI_BASE_OFFSET 				0x00000400    	/*NVIC Priority Register offset */

#define NVIC_NUMBER_OF_PRIORITY_PER_REG 	4		      	/*Number of Priority bits per register  */

#define NVIC_PRIORITY_SHIFT_BITS  			5             	/*Shift of Priority bits from bit 0 */

#define NVIS_BYTE_TO_BITES  				8              	/*convert byte to bits*/

/*
 * Choose from The Given Shapes
 *______________________________________________________________________
 * Where x(Number of Groups) and y(Number of Sub Groups)
 * _______________________________________________________
 *  -|  for x x x |    	8 Groups 1 Subgroup 
 *  -|  for x x y |  	4 Groups 2 Subgroups
 *  -|  for x y y |		2 Groups 4 Subgroups
 *  -|  for y y y |		1 Group  8 Subgroups
 *______________________________________________________________________ 
 */
 #define NVIC_GROUPING_XXX 			4
 #define NVIC_GROUPING_XXY 			5
 #define NVIC_GROUPING_XYY 			6
 #define NVIC_GROUPING_YYY 			7
 
/*_____CHOSEN STYLE________________________*/
#define NVIC_STYLE 					NVIC_GROUPING_XXY

/*_____GROUPING REG BITS___________________*/
#define NVIC_GROUP_SHIFT(VALUE) 	(VALUE << 8)

/*_____IN CASE XXX GROUPING________________*/
#define NVIC_XXX_GROUPS 			8
#define NVIC_XXX_SUBGROUPS 			1
 
/*_____IN CASE XXY GROUPING________________*/
#define NVIC_XXY_GROUPS 			4
#define NVIC_XXY_SUBGROUPS 			2 

/*_____IN CASE XYY GROUPING________________*/
#define NVIC_XYY_GROUPS 			2
#define NVIC_XYY_SUBGROUPS 			4
 
/*_____IN CASE YYY GROUPING________________*/
#define NVIC_YYY_GROUPS 			1
#define NVIC_YYY_SUBGROUPS 			8

/*_________________________________________*/ 

/*______________________________________________________________________
        ENUMS
  ______________________________________________________________________
  ______________________________________________________________________  
*/
typedef enum            /*Represent All Interrupt Numbers */
{
	NVIC_DIO_PORT_A = 0 			,
	NVIC_DIO_PORT_B     			,
	NVIC_DIO_PORT_C     			,
	NVIC_DIO_PORT_D     			,
	NVIC_DIO_PORT_E     			,
				
	NVIC_UART_0         			,
	NVIC_UART_1         			,
				
	NVIC_SSI_0          			,
				
	NVIC_I2C_0          			,
				
	NVIC_PWM_0_FAULT    			,
	NVIC_PWM_0_GEN_0    			,
	NVIC_PWM_0_GEN_1    			,
	NVIC_PWM_0_GEN_2    			,
				
	NVIC_QEI_0          			,
				
	NVIC_ADC_0_SEQ_0    			,
	NVIC_ADC_0_SEQ_1    			,
	NVIC_ADC_0_SEQ_2    			,
	NVIC_ADC_0_SEQ_3    			,
	
	NVIC_TIMER_WATCHDOG_0_1    		,
	NVIC_16_32_TIMER_0_A      		,
	NVIC_16_32_TIMER_0_B      		,
	NVIC_16_32_TIMER_1_A      		,
	NVIC_16_32_TIMER_1_B      		,
	NVIC_16_32_TIMER_2_A      		,
	NVIC_16_32_TIMER_2_B      		,
	
	NVIC_ANALOG_COMPARATOR_0   		,
	NVIC_ANALOG_COMPARATOR_1   		,
	
	/*_______27 Reserved______________*/
	
	NVIC_SYSTEM_CONTROL = 28   		,
	
	NVIC_FLASH_EEPROM_MEMORY_CONTROL,
	
	NVIC_DIO_PORT_F    			 	,
	
	/*_______31 & 32 Reserved________*/
	
	NVIC_UART_2 = 33   				,
	
	NVIC_SSI_1         				,
	
	NVIC_16_32_TIMER_3_A     		,
	NVIC_16_32_TIMER_3_B     		,
	
	NVIC_I2C_1         				,
	
	NVIC_QEI_1         				,
	
	NVIC_CAN_0         				,
	NVIC_CAN_1         				,
	
	/*_______41 & 42 Reserved________*/
	
	NVIC_HIBERNATION = 43 			,
	
	NVIC_USB           				,
					
	NVIC_PWM_GEN_3     				,
					
	NVIC_UDMA_SOFTWARE 				,
	NVIC_UDMA_ERROR    				,
					
	NVIC_ADC_1_SEQ_0   				,
	NVIC_ADC_1_SEQ_1   				,
	NVIC_ADC_1_SEQ_2   				,
	NVIC_ADC_1_SEQ_3   				,
	
	/*_______52 - 56 Reserved________*/
	
	NVIC_SSI_2 = 57    				,
	NVIC_SSI_3         				,
					
	NVIC_UART_3        				,
	NVIC_UART_4        				,
	NVIC_UART_5        				,
	NVIC_UART_6        				,
	NVIC_UART_7        				,
	
	/*_______64 - 67 Reserved________*/
	
	NVIC_I2C_2 = 68    				,
	NVIC_I2C_3         				,
	
	NVIC_16_32_TIMER_4_A     		,
	NVIC_16_32_TIMER_4_B     		,
	
	/*_______72 - 91 Reserved________*/
	
	NVIC_16_32_TIMER_5_A = 92		,
	NVIC_16_32_TIMER_5_B     		,
	NVIC_32_64_TIMER_0_A     		,
	NVIC_32_64_TIMER_0_B     		,
	NVIC_32_64_TIMER_1_A     		,
	NVIC_32_64_TIMER_1_B     		,
	NVIC_32_64_TIMER_2_A     		,
	NVIC_32_64_TIMER_2_B     		,
	NVIC_32_64_TIMER_3_A     		,
	NVIC_32_64_TIMER_3_B     		,
	NVIC_32_64_TIMER_4_A     		,
	NVIC_32_64_TIMER_4_B     		,
	NVIC_32_64_TIMER_5_A     		,
	NVIC_32_64_TIMER_5_B     		,
	
	NVIC_SYSTEM_EXCEPTION    		,
	
	/*_______107 - 133 Reserved________*/
	
	NVIC_PWM_1_GEN_0 = 134   		,
	NVIC_PWM_1_GEN_1         		,
	NVIC_PWM_1_GEN_2         		,
	NVIC_PWM_1_GEN_3         		,
	NVIC_PWM_1_FAULT
	
}Enum_Interrupt_Number;

#endif 
/**********************************************************************************************************************
 *  END OF FILE: Nvic_Cfg.h
 *********************************************************************************************************************/
