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
 { NVIC_DIO_PORT_A	,    		1,                       0                  },
 { NVIC_UART_2		,    		3,                       1                  },
 { NVIC_I2C_1    	,    		1,                       1                  },
 { NVIC_DIO_PORT_C  ,	     	2,                       1                  }	
	
		
}; /*Initialize Array to Configure each Enabled Interrupt */


 

