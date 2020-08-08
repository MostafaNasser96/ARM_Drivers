/*
 * Gio.c
 *
 *  Created on: Jul 26, 2020
 *      Author: kh
 */

#include "GIO_ARM_REG.h"
#include "Gio.h"

/*_________MACROS____________________________________________*/
#define  GIO_DIV    10

#define  GIO_MASK_SHIFT_VALUE                       4
#define  GIO_MASK_SHIFT_BITS                        2
#define GIO_MASK_MAX    255
#define DIO_MASK_READ_PIN(BASE , CHANNEL)           (*((volatile uint32 *) ((BASE  + GIO_DATA_OFFSET) + ((1 << CHANNEL )* GIO_MASK_SHIFT_VALUE))))

#define DIO_MASK_WRITE_PIN(BASE , CHANNEL)          ((*((volatile uint32 *) ((BASE  + GIO_DATA_OFFSET) + ((1 << CHANNEL )* GIO_MASK_SHIFT_VALUE)))) )

#define DIO_MASK_READ_PORT(BASE )                   (*((volatile uint32 *) (BASE  + GIO_DATA_OFFSET + (GIO_MASK_MAX * GIO_MASK_SHIFT_VALUE ))))

#define DIO_MASK_WRITE_PORT(BASE , MASK)            ((*((volatile uint32 *) ((BASE  + GIO_DATA_OFFSET) + ((MASK)* GIO_MASK_SHIFT_VALUE)))) )

#define DIO_PIN_DIRECTION(BASE)                     (*((volatile uint32 *)(BASE + GIO_DIRECTION_OFFSET)))

#define DIO_OUTPUT  1

/*_______________________________________________________________________________________________________________________________*/
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
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
    Dio_LevelType ReturnValue ;
    uint32 Base_Address ;

    if(ChannelId / GIO_DIV == GIO_A_APB)
    {
        Base_Address = GIO_PORT_A_APB_BASE ;  /*Base Address of PORTA in APB*/
    }
    else if(ChannelId / GIO_DIV == GIO_B_APB)
    {
        Base_Address = GIO_PORT_B_APB_BASE ;  /*Base Address of PORTB in APB*/
    }
    else if(ChannelId / GIO_DIV == GIO_C_APB)
    {
        Base_Address = GIO_PORT_C_APB_BASE ;  /*Base Address of PORTC in APB*/
    }
    else if(ChannelId / GIO_DIV == GIO_D_APB)
    {
        Base_Address = GIO_PORT_D_APB_BASE ;  /*Base Address of PORTD in APB*/
    }
    else if(ChannelId / GIO_DIV == GIO_E_APB)
    {
        Base_Address = GIO_PORT_E_APB_BASE ;  /*Base Address of PORTE in APB*/
    }
    else if(ChannelId / GIO_DIV == GIO_F_APB)
    {
        Base_Address = GIO_PORT_F_APB_BASE ;  /*Base Address of PORTF in APB*/
    }
    else if(ChannelId / GIO_DIV == GIO_A_AHB)
    {
        Base_Address = GIO_PORT_A_AHB_BASE ;  /*Base Address of PORTA in AHB*/
    }
    else if(ChannelId / GIO_DIV == GIO_B_AHB)
    {
        Base_Address = GIO_PORT_B_AHB_BASE ;  /*Base Address of PORTB in AHB*/
    }
    else if(ChannelId / GIO_DIV == GIO_C_AHB)
    {
        Base_Address = GIO_PORT_C_AHB_BASE ;  /*Base Address of PORTC in AHB*/
    }
    else if(ChannelId / GIO_DIV == GIO_D_AHB)
    {
        Base_Address = GIO_PORT_D_AHB_BASE ;  /*Base Address of PORTD in AHB*/
    }
    else if(ChannelId / GIO_DIV == GIO_E_AHB)
    {
        Base_Address = GIO_PORT_E_AHB_BASE ;  /*Base Address of PORTE in AHB*/
    }
    else if(ChannelId / GIO_DIV == GIO_F_AHB)
    {
        Base_Address = GIO_PORT_F_AHB_BASE ;  /*Base Address of PORTF in AHB*/
    }
    else
    {

    }

    ReturnValue = (Dio_LevelType) DIO_MASK_READ_PIN(Base_Address , (ChannelId % GIO_DIV)) >> (ChannelId % GIO_DIV)  ;

    return ReturnValue;
}

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
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
    uint32 Base_Address ;

    if(ChannelId / GIO_DIV == GIO_A_APB)
    {
        Base_Address = GIO_PORT_A_APB_BASE ;    /*Base Address of PORTA in APB*/
    }
    else if(ChannelId / GIO_DIV == GIO_B_APB)
    {
        Base_Address = GIO_PORT_B_APB_BASE ;    /*Base Address of PORTB in APB*/
    }
    else if(ChannelId / GIO_DIV == GIO_C_APB)
    {
        Base_Address = GIO_PORT_C_APB_BASE ;    /*Base Address of PORTC in APB*/
    }
    else if(ChannelId / GIO_DIV == GIO_D_APB)
    {
        Base_Address = GIO_PORT_D_APB_BASE ;    /*Base Address of PORTD in APB*/
    }
    else if(ChannelId / GIO_DIV == GIO_E_APB)
    {
        Base_Address = GIO_PORT_E_APB_BASE ;    /*Base Address of PORTE in APB*/
    }
    else if(ChannelId / GIO_DIV == GIO_F_APB)
    {
        Base_Address = GIO_PORT_F_APB_BASE ;    /*Base Address of PORTF in APB*/
    }
    else if(ChannelId / GIO_DIV == GIO_A_AHB)
    {
        Base_Address = GIO_PORT_A_AHB_BASE ;    /*Base Address of PORTA in AHB*/
    }
    else if(ChannelId / GIO_DIV == GIO_B_AHB)
    {
        Base_Address = GIO_PORT_B_AHB_BASE ;    /*Base Address of PORTB in AHB*/
    }
    else if(ChannelId / GIO_DIV == GIO_C_AHB)
    {
        Base_Address = GIO_PORT_C_AHB_BASE ;    /*Base Address of PORTC in AHB*/
    }
    else if(ChannelId / GIO_DIV == GIO_D_AHB)
    {
        Base_Address = GIO_PORT_D_AHB_BASE ;    /*Base Address of PORTD in AHB*/
    }
    else if(ChannelId / GIO_DIV == GIO_E_AHB)
    {
        Base_Address = GIO_PORT_E_AHB_BASE ;    /*Base Address of PORTE in AHB*/
    }
    else if(ChannelId / GIO_DIV == GIO_F_AHB)
    {
        Base_Address = GIO_PORT_F_AHB_BASE ;    /*Base Address of PORTF in AHB*/
    }
    else
    {

    }

    if(((DIO_PIN_DIRECTION(Base_Address) >> (ChannelId % GIO_DIV)) & 0x1 ) == DIO_OUTPUT)
    {
        DIO_MASK_WRITE_PIN(Base_Address , (ChannelId % GIO_DIV)) = (Level << (ChannelId % GIO_DIV));
    }
    else
    {
        /*Nothing Pin is Input*/
    }

}

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
Dio_PortLevelType TypeDio_ReadPort(Dio_PortType PortId)
{
    Dio_PortLevelType ReturnValue;
    uint32 Base_Address ;

    if(PortId == GIO_A_APB)
    {
        Base_Address = GIO_PORT_A_APB_BASE ;     /*Base Address of PORTA in APB*/
    }
    else if(PortId == GIO_B_APB)
    {
        Base_Address = GIO_PORT_B_APB_BASE ;     /*Base Address of PORTB in APB*/
    }
    else if(PortId == GIO_C_APB)
    {
        Base_Address = GIO_PORT_C_APB_BASE ;     /*Base Address of PORTC in APB*/
    }
    else if(PortId == GIO_D_APB)
    {
        Base_Address = GIO_PORT_D_APB_BASE ;     /*Base Address of PORTD in APB*/
    }
    else if(PortId == GIO_E_APB)
    {
        Base_Address = GIO_PORT_E_APB_BASE ;     /*Base Address of PORTE in APB*/
    }
    else if(PortId == GIO_F_APB)
    {
        Base_Address = GIO_PORT_F_APB_BASE ;     /*Base Address of PORTF in APB*/
    }
    else if(PortId == GIO_A_AHB)
    {
        Base_Address = GIO_PORT_A_AHB_BASE ;     /*Base Address of PORTA in AHB*/
    }
    else if(PortId == GIO_B_AHB)
    {
        Base_Address = GIO_PORT_B_AHB_BASE ;     /*Base Address of PORTB in AHB*/
    }
    else if(PortId == GIO_C_AHB)
    {
        Base_Address = GIO_PORT_C_AHB_BASE ;     /*Base Address of PORTC in AHB*/
    }
    else if(PortId == GIO_D_AHB)
    {
        Base_Address = GIO_PORT_D_AHB_BASE ;     /*Base Address of PORTD in AHB*/
    }
    else if(PortId == GIO_E_AHB)
    {
        Base_Address = GIO_PORT_E_AHB_BASE ;     /*Base Address of PORTE in AHB*/
    }
    else if(PortId == GIO_F_AHB)
    {
        Base_Address = GIO_PORT_F_AHB_BASE ;     /*Base Address of PORTF in AHB*/
    }
    else
    {

    }

    ReturnValue = (Dio_PortLevelType) ((DIO_MASK_READ_PORT(Base_Address ) )) ;

    return ReturnValue;

}

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
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
    uint32 Base_Address ;

    if(PortId == GIO_A_APB)
    {
        Base_Address = GIO_PORT_A_APB_BASE ;     /*Base Address of PORTA in APB*/
    }
    else if(PortId == GIO_B_APB)
    {
        Base_Address = GIO_PORT_B_APB_BASE ;     /*Base Address of PORTB in APB*/
    }
    else if(PortId == GIO_C_APB)
    {
        Base_Address = GIO_PORT_C_APB_BASE ;     /*Base Address of PORTC in APB*/
    }
    else if(PortId == GIO_D_APB)
    {
        Base_Address = GIO_PORT_D_APB_BASE ;     /*Base Address of PORTD in APB*/
    }
    else if(PortId == GIO_E_APB)
    {
        Base_Address = GIO_PORT_E_APB_BASE ;     /*Base Address of PORTE in APB*/
    }
    else if(PortId == GIO_F_APB)
    {
        Base_Address = GIO_PORT_F_APB_BASE ;     /*Base Address of PORTF in APB*/
    }
    else if(PortId == GIO_A_AHB)
    {
        Base_Address = GIO_PORT_A_AHB_BASE ;     /*Base Address of PORTA in AHB*/
    }
    else if(PortId == GIO_B_AHB)
    {
        Base_Address = GIO_PORT_B_AHB_BASE ;     /*Base Address of PORTB in AHB*/
    }
    else if(PortId == GIO_C_AHB)
    {
        Base_Address = GIO_PORT_C_AHB_BASE ;     /*Base Address of PORTC in AHB*/
    }
    else if(PortId == GIO_D_AHB)
    {
        Base_Address = GIO_PORT_D_AHB_BASE ;     /*Base Address of PORTD in AHB*/
    }
    else if(PortId == GIO_E_AHB)
    {
        Base_Address = GIO_PORT_E_AHB_BASE ;     /*Base Address of PORTE in AHB*/
    }
    else if(PortId == GIO_F_AHB)
    {
        Base_Address = GIO_PORT_F_AHB_BASE ;     /*Base Address of PORTF in AHB*/
    }
    else
    {

    }

    DIO_MASK_WRITE_PORT(Base_Address , DIO_PIN_DIRECTION( Base_Address )) = Level ;  /*SEt Port To The Vlaue*/

}

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
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
    Dio_LevelType Returned_Value ;
    Returned_Value = Dio_ReadChannel(ChannelId);  /*Get Value if PIN*/

    if(Returned_Value == STD_HIGH)
    {
        Returned_Value = STD_LOW ;  /*CLR Pin if it is HIGH*/
    }
    else
    {
        Returned_Value = STD_LOW ;  /*SET Pin if it is LOW*/
    }

    Dio_WriteChannel(ChannelId, Returned_Value); /*Write The New Value */

    return Returned_Value;  /*Return The New Value*/

}
