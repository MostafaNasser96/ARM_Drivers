/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <MCU_LCfg>
 *       Module:  MCU
 *
 *  Description:  < LCFG >     
 *  
 *********************************************************************************************************************/

#include"Mcu_Lcfg.h"

const Mcu_ConfigType MCU_CfgArr[MCU_NUMBER_OF_CFGS] = {
	
/* Clock ID	Clock Mode          		Clock Source 				PLL Status 		    	Frequency Value*/
 { 0,		MCU_RUN_MODE,	  	MCU_CLOCK_SOURCE_PREC_INT_OSC ,	 MCU_PLL_DISABLE ,              16  },
 { 1,		MCU_RUN_MODE,		MCU_CLOCK_SOURCE_MAIN_OSC     ,	 MCU_PLL_DISABLE,               80  },
 { 2,		MCU_RUN_MODE,  		MCU_CLOCK_SOURCE_MAIN_OSC     ,  MCU_PLL_ENABLE ,               40  },
 { 3,		MCU_RUN_MODE,  		MCU_CLOCK_SOURCE_32_768KHZ_EXT,  MCU_PLL_DISABLE,               80  }
	
		
}; /*Initialize Array to Configure each Enabled Interrupt */

const Mcu_ModulesCfg ConfigModulesArr[MCU_NUMBER_OF_MODULES] = {
/* Clock Mode                  Module Name                Module Port*/
 { MCU_RUN_MODE ,            MCU_WTIMER_MODULE    ,         MCU_TIMER_0  },
 { MCU_RUN_MODE ,            MCU_GPIO_MODULE    ,         MCU_GPIO_PORT_F  },
 { MCU_RUN_MODE ,            MCU_WD_MODULE    ,         MCU_WD_TIMER_0       },
 { MCU_RUN_MODE ,            MCU_TIMER_MODULE   ,         MCU_TIMER_1     },

};


/*___________________________________________________________________________________________________________________________
 |	Clock ID    |		Clock Mode		|	Clock Source               		  |	PLL Status					  |	FREQUENCY`  |
_|______________|_______________________|_____________________________________|_______________________________|_____________| 							
 |		1		|		Run Mode		|	Main Oscillator 				  |	Choose From Fixed Frequencies |	FREQ. Value	|
 |		2		|		Sleep Mode 		|	Precision Internal Oscillator 	  |	(PLL Enable)				  |				|
 |		3 		|		Deepsleep Mode	|	Precision Internal Oscillator / 4 |	Choose Divisor 				  |				|
 |	   ...		|						|	Low Frequency Internal Oscillator |	(PLL Disable)				  |				|
 |		N		|						|	32.768 External Oscillator        |								  |				|
_|______________|_______________________|_____________________________________|_______________________________|_____________|
*/
/*Range of Frequencies In Case PLL Enable	|	Range of Frequencies In Case PLL Enable  */

/*
|___________________________________________|____________________________________________|
|				80							|			 FREQUENCY_SOURCE /1             |
|				66.66	                    |            FREQUENCY_SOURCE /2             |
|				57.14	                    |            FREQUENCY_SOURCE /3             |
|				50	                        |            FREQUENCY_SOURCE /4             |
|				44.44	                    |            FREQUENCY_SOURCE /5             |
|				40	                        |            FREQUENCY_SOURCE /6             |
|				36.36	                    |            FREQUENCY_SOURCE /7             |
|				33.33	                    |            FREQUENCY_SOURCE /8             |
|				30.76	                    |            FREQUENCY_SOURCE /9             |
|				28.57	                    |            FREQUENCY_SOURCE /10            |
|				26.66	                    |            FREQUENCY_SOURCE /11            |
|				25	                        |            FREQUENCY_SOURCE /12            |
|				23.52	                    |            FREQUENCY_SOURCE /13            |
|				22.22	                    |            FREQUENCY_SOURCE /14            |
|				21.05	                    |            FREQUENCY_SOURCE /15            |
|				20	                        |            FREQUENCY_SOURCE /16            |
|				19.04	                    |            FREQUENCY_SOURCE /17            |
|				18.18	                    |            FREQUENCY_SOURCE /18            |
|				17.39	                    |            FREQUENCY_SOURCE /19            |
|				16.66	                    |            FREQUENCY_SOURCE /20            |
|				16	                        |            FREQUENCY_SOURCE /21            |
|				15.38	                    |            FREQUENCY_SOURCE /22            |
|				14.81	                    |            FREQUENCY_SOURCE /23            |
|				14.28	                    |            FREQUENCY_SOURCE /24            |
|				13.79	                    |            FREQUENCY_SOURCE /25            |
|				13.33	                    |            FREQUENCY_SOURCE /26            |
|				12.90	                    |            FREQUENCY_SOURCE /27            |
|				12.5	                    |            FREQUENCY_SOURCE /28            |
|				12.12	                    |            FREQUENCY_SOURCE /29            |
|				11.76	                    |            FREQUENCY_SOURCE /30            |
|				11.42	                    |            FREQUENCY_SOURCE /31            |
|				11.11	                    |            FREQUENCY_SOURCE /32            |
|				10.81	                    |            FREQUENCY_SOURCE /33            |
|				10.52	                    |            FREQUENCY_SOURCE /34            |
|				10.25	                    |            FREQUENCY_SOURCE /35            |
|				10	                        |            FREQUENCY_SOURCE /36            |
|				9.756	                    |            FREQUENCY_SOURCE /37            |
|				9.523	                    |            FREQUENCY_SOURCE /38            |
|				9.302	                    |            FREQUENCY_SOURCE /39            |
|				9.090	                    |            FREQUENCY_SOURCE /40            |
|				8.888	                    |            FREQUENCY_SOURCE /41            |
|				8.695	                    |            FREQUENCY_SOURCE /42            |
|				8.510	                    |            FREQUENCY_SOURCE /43            |
|				8.333	                    |            FREQUENCY_SOURCE /44            |
|				8.163	                    |            FREQUENCY_SOURCE /45            |
|				8	                        |            FREQUENCY_SOURCE /46            |
|				7.843	                    |            FREQUENCY_SOURCE /47            |
|				7.692	                    |            FREQUENCY_SOURCE /48            |
|				7.547	                    |            FREQUENCY_SOURCE /49            |
|				7.407	                    |            FREQUENCY_SOURCE /40            |
|				7.272	                    |            FREQUENCY_SOURCE /50            |
|				7.142	                    |            FREQUENCY_SOURCE /51            |
|				7.017	                    |            FREQUENCY_SOURCE /52            |
|				6.896	                    |            FREQUENCY_SOURCE /53            |
|				6.779	                    |            FREQUENCY_SOURCE /54            |
|				6.666	                    |            FREQUENCY_SOURCE /55            |
|				6.557	                    |            FREQUENCY_SOURCE /56            |
|				6.451	                    |            FREQUENCY_SOURCE /57            |
|				6.349	                    |            FREQUENCY_SOURCE /58            |
|				6.25	                    |            FREQUENCY_SOURCE /59            |
|				6.153	                    |            FREQUENCY_SOURCE /60            |
|				6.060	                    |            FREQUENCY_SOURCE /61            |
|				5.970	                    |            FREQUENCY_SOURCE /62            |
|				5.882	                    |            FREQUENCY_SOURCE /63            |
|				5.797	                    |            FREQUENCY_SOURCE /64            |
|				5.714	                    |                                            |
|				5.633	                    |                                            |
|				5.555	                    |                                            |
|				5.479	                    |                                            |
|				5.405	                    |                                            |
|				5.333	                    |                                            |
|				5.263	                    |                                            |
|				5.194	                    |                                            |
|				5.128	                    |                                            |
|				5.063	                    |                                            |
|				5	                        |                                            |
|				4.938	                    |                                            |
|				4.878	                    |                                            |
|				4.819	                    |                                            |
|				4.761	                    |                                            |
|				4.705	                    |                                            |
|				4.651	                    |                                            |
|				4.597	                    |                                            |
|				4.545	                    |                                            |
|				4.494	                    |                                            |
|				4.444	                    |                                            |
|				4.395	                    |                                            |
|				4.347	                    |                                            |
|				4.301	                    |                                            |
|				4.255	                    |                                            |
|				4.210	                    |                                            |
|				4.166	                    |                                            |
|				4.123	                    |                                            |
|				4.081	                    |                                            |
|				4.040	                    |                                            |
|				4	                        |                                            |
|				3.960	                    |                                            |
|				3.921	                    |                                            |
|				3.883	                    |                                            |
|				3.846	                    |                                            |
|				3.809	                    |                                            |
|				3.773	                    |                                            |
|				3.738	                    |                                            |
|				3.703	                    |                                            |
|				3.669	                    |                                            |
|				3.636	                    |                                            |
|				3.603	                    |                                            |
|				3.571	                    |                                            |
|				3.539	                    |                                            |
|				3.508	                    |                                            |
|				3.478	                    |                                            |
|				3.448	                    |                                            |
|				3.418	                    |                                            |
|				3.389	                    |                                            |
|				3.361	                    |                                            |
|				3.333	                    |                                            |
|				3.305	                    |                                            |
|				3.278	                    |                                            |
|				3.252	                    |                                            |
|				3.225	                    |                                            |
|				3.2	                        |                                            |
|				3.174	                    |                                            |
|				3.149	                    |                                            |
____________________________________________|____________________________________________|

*/























































 

