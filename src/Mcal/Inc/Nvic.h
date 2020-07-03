/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  < Nvic.h >
 *       Module:  -NVIC 
 *  Description:  <Header file for NVIC module to initialize the Module>     
 *  
 *********************************************************************************************************************/

#ifndef NVIC_H_
#define NVIC_H_

#include "Platform_Types.h"
#include "Std_Types.h" 
#include "Bit_Math.h"

#include "nvic_cfg.h"


/*_______ENABLE INTERRUPT ___________________________________________*/

#define NVIC_FULL_ADD (NVIC_BASE_INT + NVIC_EN_BASE_OFFSET)  /* (Address = Base Address) + (Offset from the base Address)*/

#define NVIC_EN_NUM(INT_NUMBER)  SET_BIT((*((volatile uint32*) (NVIC_FULL_ADD + ((INT_NUMBER/NUMBER_OF_BITS ) * NVIC_OFFSET_BYTES)))),(INT_NUMBER % NUMBER_OF_BITS))
/*(INT_NUMBER/NUMBER_OF_BITS ) to get Number of REG , (INT_NUMBER % NUMBER_OF_BITS) to get Bit Number in the Register */

/*_______APINT REGISTER _____________________________________________*/

#define NVIC_APPINT_ADD *((volatile uint32*)(NVIC_BASE_INT + NVIC_APINT_OFFSET))   /*Address of APINT Register*/

/*_______INTERRUPT PRIORITY _________________________________________*/

#define NVIC_PRI(INT_NUMBER, INT_GROUP)     *((volatile uint32*) ((NVIC_BASE_INT + NVIC_PRI_BASE_OFFSET) + ((INT_NUMBER/NVIC_NUMBER_OF_PRIORITY_PER_REG) * NVIC_OFFSET_BYTES)) ) |= ((INT_GROUP) << ((NVIC_PRIORITY_SHIFT_BITS + ((INT_NUMBER % NVIC_NUMBER_OF_PRIORITY_PER_REG)) * NVIS_BYTE_TO_BITES)))
/*___________________________________________________________________________________________________________________________*/


/*__GLOBAL TYPES AND STRUCTURES ______________________________*/

typedef uint8 Error_Return_Type ;         				/*Return Error (OK or NOK)*/

typedef uint8 NVIC_Group_Priority ;       				/*Group priority According to Grouping Style */

typedef uint8 NVIC_Subgroup_Priority ;    				/*Subgroup priority According to Grouping Style */

typedef struct
{
    Enum_Interrupt_Number 		Interrupt_Number;     	/*Interrupt Number */
    NVIC_Group_Priority 		Group_Priority;       	/*Group Priority*/
    NVIC_Subgroup_Priority 		SubGroup_Priority;    	/*Subgroup Priority*/

}NVIC_CfgType;

/*______________________________________________________________*/

/*________________FUNCTIONS PROTOTYPES_____________________*/

/******************************************************************************
* \Syntax          : Error_Return_Type NVIC_init(void)       
* \Description     : Init The NVIC Module                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : void                       
* \Parameters (out): None                                                      
* \Return value:   : Error_Return_Type  E_OK
*                                       E_NOT_OK                                  
*******************************************************************************/
Error_Return_Type NVIC_init(void);

#endif
