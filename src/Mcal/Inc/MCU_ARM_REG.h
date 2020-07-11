#ifndef MCU_ARM_REG_H_
#define MCU_ARM_REG_H_

/*_____________________________________________________________________________________________________*/
/*____BASE ADDRESS CFG____*/
/*_____________________________________________________________________________________________________*/

#define   MCU_PRIVATE_PRI_BASE_ALIAS                0x42000000

#define MCU_PRIVATE_PRI_BASE_ADD                    0x40000000

#define MCU_BASE_ADDRESS                            0x400FE000

#define MCU_RCC_OFFSET                              0x00000060

#define MCU_RCC2_OFFSET                             0x00000070
 
#define MCU_APINT_BASE_ADD		                    0xE000E000

#define MCU_APINT_OFFSET                            0x00000D0C

#define MCU_RESET_CAUSE_OFFSET                      0x0000005C

#define MCU_PLL_STAT_OFFSET                         0x00000168


/*_________________________________________________*/
#define MCU_RUN_MODE                                0x00000600

#define MCU_SLEEP_MODE                              0x00000700

#define MCU_DEEP_SLEEP_MODE                         0x00000800


/*__________________________________________________________________________________________________________________________________*/
/*   MCU ARM BIT CFG        
____________________________________________________________________________________________________________________________________*/



#define MCU_VECTKEY_VALUE 					0x5FA << 16    	/*APINT Vect Key to change Value */


/*_____________________________________________

       RCC2
_______________________________________________*/



#define MCU_USE_RCC2   			31         	    /* 1 	The RCC2 register fields override the RCC register fields.
													 0	The RCC register fields are used, and the fields in RCC2 are ignored.*/
#define MCU_RCC2_DIV400 		30  			/*_________________________________________________________
															Examples of Possible System Clock Frequencies with DIV400=1
															____________________________________________________________
														SYSDIV2 	SYSDIV2LSB 		Divisor 	Frequency (BYPASS2=0) 		TivaWare Parameter
														____________________________________________________________________________________________
														0x00 		reserved 			/2 		reserved 					-

														0x01		0 					/3 		reserved 					-
																	1 					/4 		reserved 					-

														0x02		0 					/5 		80 MHz 						MCU_SYSDIV_2_5
																	1 					/6 		66.67 MHz 					MCU_SYSDIV_3

														0x03		0 					/7		reserved 					-
																	1 					/8 		50 MHz 						MCU_SYSDIV_4

														0x04 		0 					/9 		44.44 MHz 					MCU_SYSDIV_4_5
																	1 					/10 	40 MHz 						MCU_SYSDIV_5
														... 		... 				... 	... 						...

														0x3F		0 					/127 	3.15 MHz 					MCU_SYSDIV_63_5
																	1 					/128 	3.125 MHz 					MCU_SYSDIV_64*/ 
																	
#define MCU_RCC2_SYSDIV_END 	28																	
#define MCU_RCC2_SYSDIV_START 	23              /*	__________________________________________________________________________________________________
														SYSDIV 	Divisor 	Frequency (BYPASS=0) 		Frequency (BYPASS=1) 		TivaWare™ Parameter
													___________________________________________________________________________________________________
														0x00 	/1 			reserved 				Clock source frequency/1 	MCU_SYSDIV_1
														0x01 	/2 			reserved 				Clock source frequency/2 	MCU_SYSDIV_2
														0x02 	/3 			66.67 MHz 				Clock source frequency/3 	MCU_SYSDIV_3
														0x03 	/4 			50 MHz 					Clock source frequency/4 	MCU_SYSDIV_4
														0x04 	/5 			40 MHz 					Clock source frequency/5 	MCU_SYSDIV_5
														0x05 	/6 			33.33 MHz 				Clock source frequency/6 	MCU_SYSDIV_6
														0x06 	/7 			28.57 MHz 				Clock source frequency/7 	MCU_SYSDIV_7
														0x07 	/8 			25 MHz 					Clock source frequency/8 	MCU_SYSDIV_8
														0x08 	/9 			22.22 MHz 				Clock source frequency/9 	MCU_SYSDIV_9
														0x09 	/10 		20 MHz 					Clock source frequency/10 	MCU_SYSDIV_10
														0x0A 	/11 		18.18 MHz 				Clock source frequency/11 	MCU_SYSDIV_11
														0x0B 	/12 		16.67 MHz 				Clock source frequency/12 	MCU_SYSDIV_12
														0x0C 	/13 		15.38 MHz 				Clock source frequency/13 	MCU_SYSDIV_13
														0x0D 	/14 		14.29 MHz 				Clock source frequency/14 	MCU_SYSDIV_14
														0x0E 	/15 		13.33 MHz 				Clock source frequency/15 	MCU_SYSDIV_15
														0x0F 	/16 		12.5 MHz (default) 		Clock source frequency/16 	MCU_SYSDIV_16
														....
														0x3F    /64         3.125 MHZ				Clock source frequency/64	MCU_SYSDIV_64 */


#define MCU_RCC2_SYSDIV2LSB 	22

#define MCU_RCC2_USBPWRDN 		14   				 /*Power Down USB PLL 1 (Power Down) 0 (Operates Normally)*/

#define MCU_RCC2_PWRDN2 		13    				 /*Power Down PLL 1 (Power Down) 0 (Operates Normally)*/

#define MCU_RCC2_BYPASS2 		11   				 /*PLL Bypass Use PLL or Not */  

#define MCU_RCC2_OSCSRC2_END  	6 
 
#define MCU_RCC2_OSCSRC2_START  4 					/*Oscillator Source 2
													Selects the input source for the OSC. The values are:
													Value 	Description
													
													0x0		MOSC
															Main oscillator
			
													0x1		PIOSC
															Precision internal oscillator
			
													0x2		PIOSC/4
															Precision internal oscillator / 4
			
													0x3		LFIOSC
															Low-frequency internal oscillator
			
													0x4-0x6 Reserved
													
													0x7		32.768 kHz
															32.768-kHz external oscillator*/	
															


/*_____________________________________________
       RCC
_______________________________________________*/	

														
#define MCU_RCC_ACG 			27 					/*Auto Clock Gating 1 in SCGn or DCGn Sleep and Deepsleep
													0 in Run Mode RCGCn*/
													
#define MCU_RCC_SYSDIV_END  	26
#define MCU_RCC_SYSDIV_START  	23 

#define MCU_RCC_USESYSDIV 		22  				/*1 Enable system Division 
													0 Disable System division*/
													
#define MCU_RCC_USEPWMDIV  		20 					/*1 Enable PWM Divisor
													0 Disable PWM Divisor*/
													

#define MCU_RCC_PWMDIV_END     	19  
#define MCU_RCC_PWMDIV_START 	17					/*	Value 	Divisor
														0x0 	/2
														0x1 	/4
														0x2		/8
														0x3 	/16
														0x4 	/32
														0x5 	/64
														0x6 	/64
														0x7 	/64 (default)*/
														
#define MCU_RCC_PWRDN 			13 					/*1  PLL power Down 
													  0  PLL Operates Normally*/
													  
													  
#define MCU_RCC_BYPASS 			11   				/*Use PLL or Not */


#define MCU_RCC_CRYSTAL_XTAL_END 	10	
#define MCU_RCC_CRYSTAL_XTAL_START 	6				/*	Value
														0x00-0x5 reserved
														0x06 4 MHz reserved
														0x07 4.096 MHz reserved
														0x08 4.9152 MHz reserved
														0x09 5 MHz (USB)
														0x0A 5.12 MHz
														0x0B 6 MHz (USB)
														0x0C 6.144 MHz
														0x0D 7.3728 MHz
														0x0E 8 MHz (USB)
														0x0F 8.192 MHz
														0x10 10.0 MHz (USB)
														0x11 12.0 MHz (USB)
														0x12 12.288 MHz
														0x13 13.56 MHz
														0x14 14.31818 MHz
														0x15 16.0 MHz (USB)
														0x16 16.384 MHz
														0x17 18.0 MHz (USB)
														0x18 20.0 MHz (USB)
														0x19 24.0 MHz (USB)
														0x1A 25.0 MHz (USB)*/

#define MCU_RCC_OSCRC_END 		5														
#define MCU_RCC_OSCRC_START 	4  					/*Oscillator Source
														Selects the input source for the OSC. The values are:
														Value Input Source
														0x0		MOSC
																Main oscillator
														
														0x1		PIOSC
																Precision internal oscillator
																(default)
														
														0x2		PIOSC/4
																Precision internal oscillator / 4
														
														0x3		LFIOSC
																Low-frequency internal oscillator*/
																
#define MCU_RCC_MOSCDIS  		0			 		/*Main Oscillator Enable or Disable */ 

/*_________________________________________________________________________________________________*/

/*__________________________________________________
       MODULE NAMES
____________________________________________________*/
#define MCU_WD_MODULE       0
#define MCU_TIMER_MODULE    1
#define MCU_GPIO_MODULE     2
#define MCU_DMA_MODULE      3
#define MCU_HIB_MODULE      5
#define MCU_UART_MODULE     6
#define MCU_SSI_MODULE      7
#define MCU_I2C_MODULE      8
#define MCU_USB_MODULE      10
#define MCU_CAN_MODULE      13
#define MCU_ADC_MODULE      14
#define MCU_ACMP_MODULE     15
#define MCU_PWM_MODULE      16
#define MCU_QEI_MODULE      17
#define MCU_EEPROM_MODULE   22
#define MCU_WTIMER_MODULE   23

/*__________________________________________________*/
#define MCU_WD_TIMER_0          0
#define MCU_WD_TIMER_1          1

#define MCU_TIMER_0             0
#define MCU_TIMER_1             1
#define MCU_TIMER_2             2
#define MCU_TIMER_3             3
#define MCU_TIMER_4             4
#define MCU_TIMER_5             5

#define MCU_GPIO_PORT_A         0
#define MCU_GPIO_PORT_B         1
#define MCU_GPIO_PORT_C         2
#define MCU_GPIO_PORT_D         3
#define MCU_GPIO_PORT_E         4
#define MCU_GPIO_PORT_F         5

#define MCU_DMA_0               0

#define MCU_HIB_0               0

#define MCU_UART_0              0
#define MCU_UART_1              1
#define MCU_UART_2              2
#define MCU_UART_3              3
#define MCU_UART_4              4
#define MCU_UART_5              5
#define MCU_UART_6              6
#define MCU_UART_7              7

#define MCU_SSI_0               0
#define MCU_SSI_1               1
#define MCU_SSI_2               2
#define MCU_SSI_3               3

#define MCU_I2C_0               0
#define MCU_I2C_1               1
#define MCU_I2C_2               2
#define MCU_I2C_3               3

#define MCU_USB_0               0

#define MCU_CAN_0               0
#define MCU_CAN_1               1

#define MCU_ADC_0               0
#define MCU_ADC_1               1

#define MCU_ACMP_0              0

#define MCU_PWM_0               0
#define MCU_PWM_1               1

#define MCU_QEI_0               0
#define MCU_QEI_1               1

															
#endif
