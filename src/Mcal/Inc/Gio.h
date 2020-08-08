/*
 * Gio.h
 *
 *  Created on: Jul 26, 2020
 *      Author: kh
 */

#ifndef GIO_H_
#define GIO_H_

/*____________________________________________________________________________________

        INCLUDES
_______________________________________________________________________________________*/
#include "Platform_Types.h"
#include "Std_Types.h"
#include "Bit_Math.h"

/*_______MACROS__________________________________________*/


#define GIO_A_APB      0U      /*PORTA*/
#define GIO_B_APB      1U      /*PORTB*/
#define GIO_C_APB      2U      /*PORTC*/
#define GIO_D_APB      3U      /*PORTD*/
#define GIO_E_APB      4U      /*PORTE*/
#define GIO_F_APB      5U      /*PORTF*/

#define GIO_A_AHB      6U      /*PORTA*/
#define GIO_B_AHB      7U      /*PORTB*/
#define GIO_C_AHB      8U      /*PORTC*/
#define GIO_D_AHB      9U      /*PORTD*/
#define GIO_E_AHB      10U     /*PORTE*/
#define GIO_F_AHB      11U     /*PORTF*/
/*PINS*/
/*PORT A*/
#define GIO_PA_0  00U
#define GIO_PA_1  01U
#define GIO_PA_2  02U
#define GIO_PA_3  03U
#define GIO_PA_4  04U
#define GIO_PA_5  05U
#define GIO_PA_6  06U
#define GIO_PA_7  07U
/*PORT B*/
#define GIO_PB_0  10U
#define GIO_PB_1  11U
#define GIO_PB_2  12U
#define GIO_PB_3  13U
#define GIO_PB_4  14U
#define GIO_PB_5  15U
#define GIO_PB_6  16U
#define GIO_PB_7  17U
/*PORT C*/
#define GIO_PC_0  20U
#define GIO_PC_1  21U
#define GIO_PC_2  22U
#define GIO_PC_3  23U
#define GIO_PC_4  24U
#define GIO_PC_5  25U
#define GIO_PC_6  26U
#define GIO_PC_7  27U
/*PORT D*/
#define GIO_PD_0  30U
#define GIO_PD_1  31U
#define GIO_PD_2  32U
#define GIO_PD_3  33U
#define GIO_PD_4  34U
#define GIO_PD_5  35U
#define GIO_PD_6  36U
#define GIO_PD_7  37U
/*PORT E*/
#define GIO_PE_0  40U
#define GIO_PE_1  41U
#define GIO_PE_2  42U
#define GIO_PE_3  43U
#define GIO_PE_4  44U
/*PORT F*/
#define GIO_PF_0  50U
#define GIO_PF_1  51U
#define GIO_PF_2  52U
#define GIO_PF_3  53U
#define GIO_PF_4  54U

/*AHB PORTS                */

/*PORT A*/
#define GIO_PA_0_AHB  60U
#define GIO_PA_1_AHB  61U
#define GIO_PA_2_AHB  62U
#define GIO_PA_3_AHB  63U
#define GIO_PA_4_AHB  64U
#define GIO_PA_5_AHB  65U
#define GIO_PA_6_AHB  66U
#define GIO_PA_7_AHB  67U
/*PORT B*/
#define GIO_PB_0_AHB  70U
#define GIO_PB_1_AHB  71U
#define GIO_PB_2_AHB  72U
#define GIO_PB_3_AHB  73U
#define GIO_PB_4_AHB  74U
#define GIO_PB_5_AHB  75U
#define GIO_PB_6_AHB  76U
#define GIO_PB_7_AHB  77U
/*PORT C*/
#define GIO_PC_0_AHB  80U
#define GIO_PC_1_AHB  81U
#define GIO_PC_2_AHB  82U
#define GIO_PC_3_AHB  83U
#define GIO_PC_4_AHB  84U
#define GIO_PC_5_AHB  85U
#define GIO_PC_6_AHB  86U
#define GIO_PC_7_AHB  87U
/*PORT D*/
#define GIO_PD_0_AHB  90U
#define GIO_PD_1_AHB  91U
#define GIO_PD_2_AHB  92U
#define GIO_PD_3_AHB  93U
#define GIO_PD_4_AHB  94U
#define GIO_PD_5_AHB  95U
#define GIO_PD_6_AHB  96U
#define GIO_PD_7_AHB  97U
/*PORT E*/
#define GIO_PE_0_AHB  100U
#define GIO_PE_1_AHB  101U
#define GIO_PE_2_AHB  102U
#define GIO_PE_3_AHB  103U
#define GIO_PE_4_AHB  104U
/*PORT F*/
#define GIO_PF_0_AHB  110U
#define GIO_PF_1_AHB  111U
#define GIO_PF_2_AHB  112U
#define GIO_PF_3_AHB  113U
#define GIO_PF_4_AHB  114U

/*___TYPES_____________________________________________*/

typedef uint8 Dio_ChannelType ;
typedef uint8 Dio_PortType  ;
typedef uint8 Dio_LevelType ;
typedef uint8 Dio_PortLevelType;

/******************************************************************************
* \Syntax          : Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
* \Description     : Returns the value of the specified DIO channel.
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : Dio_ChannelType Channel Id
* \Parameters (out): None
* \Return value:   : Dio_LevelType Value of Pin STD_HIGH The physical level of the corresponding Pin is STD_HIGH STD_LOW The physical level of the corresponding Pin is STD_LOW
*******************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
/******************************************************************************
* \Syntax          : void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);
* \Description     : write Value to Channel
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : Dio_ChannelType Channel Id , Dio_LevelType High or low
* \Parameters (out): None
* \Return value:   : Dio_LevelType Value of Pin STD_HIGH The physical level of the corresponding Pin is STD_HIGH STD_LOW The physical level of the corresponding Pin is STD_LOW
*******************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/******************************************************************************
* \Syntax          : Dio_PortLevel TypeDio_ReadPort(Dio_PortType PortId);
* \Description     : Read Complete Port
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : Dio_PortType Port Number
* \Parameters (out): None
* \Return value:   : Dio_PortLevelType Value of Port
*******************************************************************************/
Dio_PortLevelType TypeDio_ReadPort(Dio_PortType PortId);

/******************************************************************************
* \Syntax          : void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);
* \Description     : Write Complete Port
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : Dio_PortType Port Number , Level Value to write into Port
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);
/******************************************************************************
* \Syntax          : Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
* \Description     :Flip Pin Value
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Reentrant
* \Parameters (in) : ChannelId
* \Parameters (out): Dio_LevelType New Pin Value after Flip
* \Return value:   : None
*******************************************************************************/
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
#endif /* GIO_H_ */
