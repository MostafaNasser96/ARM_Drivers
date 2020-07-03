/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------
*        file  Nvic.c
 *        brief  Implementation of NVIC driver for ARM Arch. 
 *
 *      details  The user Defines Configuraton Array for the enabled Interrupts of the System And pass it to the NVIC_Init Function
				  to configure them 
 *
 *
 *********************************************************************************************************************/




/*______INCLUDES________________________________*/
#include "nvic.h"
#include "nvic_lcfg.h"
/*_______________________________________________*/

/*___GLOBAL VARIABLES____________________________*/
volatile static uint8 g_InitCheck = E_NOT_OK;   /*Check if Module is initialized or Not */
/*_________________________________________________*/

/*___FUNCTIONS DEFINITION _________________________*/
/******************************************************************************
* \Syntax          : Error_Return_Type NVIC_init(void)       
* \Description     : Init The NVIC Module                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : void                       
* \Parameters (out): None                                                      
* \Return value:   : Error_Return_Type  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
Error_Return_Type NVIC_init(void)
{
    /*TODO : switch to privilege mode - use switch function in processor.h*/

    uint8 u8_Loop ,  u8_NumberOfGroups , u8_NumberOfSubGroups, u8_NumberPriority , u8_ErrorStatus 	= E_OK; 

	NVIC_CfgType const * ptr_NVIC_Cfg 	= NVIC_CfgArr ;   /*Get The Cfg Array of Structure that user entered */

    switch(	NVIC_STYLE	)  /*Check Grouping Types */
    {
        case NVIC_GROUPING_XXX :  
		
            NVIC_APPINT_ADD 	= NVIC_VECTKEY_VALUE | NVIC_GROUP_SHIFT(NVIC_GROUPING_XXX) ; /*In case XXX Grouping */
            u8_NumberOfGroups  	= NVIC_XXX_GROUPS ;                                          /*8 Groups */
            u8_NumberOfSubGroups = NVIC_XXX_SUBGROUPS;                                        /*1 Subgroups */
            break;
			
        case NVIC_GROUPING_XXY :
		
            NVIC_APPINT_ADD 	= NVIC_VECTKEY_VALUE | NVIC_GROUP_SHIFT(NVIC_GROUPING_XXY)  ; /*In case XXY Grouping */
            u8_NumberOfGroups  	= NVIC_XXY_GROUPS ;                                           /*4 Groups */
            u8_NumberOfSubGroups = NVIC_XXY_SUBGROUPS;                                         /*2 Subgroups */
			
            break;
        case NVIC_GROUPING_XYY :
		
            NVIC_APPINT_ADD 	= NVIC_VECTKEY_VALUE | NVIC_GROUP_SHIFT(NVIC_GROUPING_XYY)  ; /*In case XYY Grouping */
            u8_NumberOfGroups  	= NVIC_XYY_GROUPS ;                                           /*2 Groups */
            u8_NumberOfSubGroups = NVIC_XYY_SUBGROUPS;                                         /*4 Subgroups */
			
            break;
        case NVIC_GROUPING_YYY :
		
            NVIC_APPINT_ADD		= NVIC_VECTKEY_VALUE | NVIC_GROUP_SHIFT(NVIC_GROUPING_YYY)  ; /*In case YYY Grouping */
            u8_NumberOfGroups  	= NVIC_YYY_GROUPS ;                                           /*1 Groups */
            u8_NumberOfSubGroups = NVIC_YYY_SUBGROUPS;                                         /*8 Subgroups */
			
            break;
        default :
		
            u8_ErrorStatus 		= E_NOT_OK;  /*Return Error */
			
            break;
    }

    if(u8_ErrorStatus 	==	 E_OK)  /*If There is no Error Returned*/
    {
        for(u8_Loop = 0 ; u8_Loop < NVIC_NUM_OF_ENABLED_INT  ; u8_Loop ++) /*Loop for the interrupts */
        {
            if(u8_ErrorStatus == E_OK)
            {
                if(ptr_NVIC_Cfg[u8_Loop].Interrupt_Number <= MAX_INTERRUPT_NUMBER)
                {
                    NVIC_EN_NUM(ptr_NVIC_Cfg[u8_Loop].Interrupt_Number); /*Enable Interrupt Number */

                    if(ptr_NVIC_Cfg[u8_Loop].Group_Priority < u8_NumberOfGroups &&  ptr_NVIC_Cfg[u8_Loop].SubGroup_Priority < u8_NumberOfSubGroups) /*Check Grouping*/
                    {
                        if(u8_NumberOfGroups == NVIC_XXX_GROUPS && u8_NumberOfSubGroups == NVIC_XXX_SUBGROUPS)  /*In Case 8 Groups and 1 Subgroup 3 bits for Groups from (0 to 7)*/
                        {
                            u8_NumberPriority = (uint8) ptr_NVIC_Cfg[u8_Loop].Group_Priority ; /*set Priority*/
							
                            NVIC_PRI((uint32)ptr_NVIC_Cfg[u8_Loop].Interrupt_Number, (uint32)u8_NumberPriority); /*Set Group Priority */
                        }
                        else if(u8_NumberOfGroups == NVIC_XXY_GROUPS && u8_NumberOfSubGroups == NVIC_XXY_SUBGROUPS)  /*In Case 4 Groups and 2 Subgroups 2 bits for Groups( 0 or 1 or 2 or 3) and 1 for Subgroups (0 or 1)*/
                        {
                            u8_NumberPriority = (uint8)(ptr_NVIC_Cfg[u8_Loop].Group_Priority << 1) + (uint8)ptr_NVIC_Cfg[u8_Loop].SubGroup_Priority ; /*Shift Group No left by 1 and add it to No of Subgroups */
							
                            NVIC_PRI((uint32)ptr_NVIC_Cfg[u8_Loop].Interrupt_Number,(uint32)u8_NumberPriority);
													
											  }
                        else if(u8_NumberOfGroups == NVIC_XYY_GROUPS && u8_NumberOfSubGroups == NVIC_XYY_SUBGROUPS) /*In Case 2 Groups and 4 Subgroups  1 bit for Groups( 0 or 1) and 2 for Subgroups (0 or 1 or 2 or 3 )*/
                        {
														u8_NumberPriority = (uint8)(ptr_NVIC_Cfg[u8_Loop].Group_Priority << 2) + (uint8)ptr_NVIC_Cfg[u8_Loop].SubGroup_Priority ; /*Shift Group No left by 2 and add it to No of Subgroups */
							
                            NVIC_PRI((uint32)ptr_NVIC_Cfg[u8_Loop].Interrupt_Number, (uint32)u8_NumberPriority);
                        }
                        else if(u8_NumberOfGroups == NVIC_YYY_GROUPS && u8_NumberOfSubGroups == NVIC_YYY_SUBGROUPS) /*In Case 1 Group and 8 Subgroups 3 bits for Subgroups from (0 to 7)*/
                        {
                            u8_NumberPriority = (uint8)ptr_NVIC_Cfg[u8_Loop].SubGroup_Priority ; /*set Priority*/
							
                            NVIC_PRI((uint32)ptr_NVIC_Cfg[u8_Loop].Interrupt_Number, (uint32)u8_NumberPriority);
                        }

                    }
                    else
                    {
                        u8_ErrorStatus  = E_NOT_OK; /*error status : Not Ok*/
                    }
                }
                else
                {
                    u8_ErrorStatus = E_NOT_OK;  /*error status : Not Ok*/
                }
            }
       }
		 }
		
		if(u8_ErrorStatus == E_OK)  /*If Error Status is Ok Then Init is Done */
		{
			g_InitCheck = E_OK;
		}
    else
    {
        /*Nothing*/
    }
	
	return u8_ErrorStatus;  /*Return Error Status */

}



