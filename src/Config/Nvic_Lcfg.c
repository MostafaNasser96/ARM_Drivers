/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <Nvic_LCfg>
 *       Module:  NVIC
 *
 *  Description:  < LCFG >     
 *  
 *********************************************************************************************************************/

#include"nvic_lcfg.h"

const NVIC_CfgType NVIC_CfgArr[NVIC_NUM_OF_ENABLED_INT] = {
	
/* Interrupt_Number	    Group_Priority          SubGroup_Priority */
 { NVIC_16_32_TIMER_1_A	,    		1,                       0                  },
 { NVIC_DIO_PORT_A		,    		3,                       1                  },
 { NVIC_TIMER_WATCHDOG_0_1    	,    		1,                       1                  },
 { NVIC_DIO_PORT_C  ,	     	2,                       1                  }	
	
		
}; /*Initialize Array to Configure each Enabled Interrupt */


 

