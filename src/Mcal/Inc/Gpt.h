/*
 * Gpt.h
 *
 *  Created on: Jul 13, 2020
 *      Author: kh
 */

#ifndef GPT_H_
#define GPT_H_


/*____________________________________________________________________________________

        INCLUDES
_______________________________________________________________________________________*/
#include "Platform_Types.h"
#include "Std_Types.h"
#include "Bit_Math.h"

//#include "Gpt_Cfg.h"
#include "GPT_ARM_REG.h"

/*____CFG REG __________________________*/
#define GPT_CFG_32_BIT_TIMER        0x0
#define GPT_CFG_64_BIT_W_TIMER      0x0

#define GPT_CFG_16_BIT_TIMER        0x4
#define GPT_CFG_32_BIT_W_TIMER      0x4

#define GPT_TIMER_COUNT_DOWN        1
#define GPT_TIMER_COUNT_UP          0

/*_____Channel Type ____________________*/

#define GPT_16_32_BIT_TIMER_0                   0
#define GPT_16_32_BIT_TIMER_1                   1
#define GPT_16_32_BIT_TIMER_2                   2
#define GPT_16_32_BIT_TIMER_3                   3
#define GPT_16_32_BIT_TIMER_4                   4
#define GPT_16_32_BIT_TIMER_5                   5
#define GPT_32_64_BIT_WIDE_TIMER_0              6
#define GPT_32_64_BIT_WIDE_TIMER_1              7
#define GPT_32_64_BIT_WIDE_TIMER_2              8
#define GPT_32_64_BIT_WIDE_TIMER_3              9
#define GPT_32_64_BIT_WIDE_TIMER_4              10
#define GPT_32_64_BIT_WIDE_TIMER_5              11


typedef uint8   Gpt_ChannelType;
typedef uint8   Gpt_ChannelTickFrequency;
typedef uint64  GptChannelTickValueMax;
typedef uint64  Gpt_ValueType;

typedef enum
{
    GPT_NORMAL_MODE ,

    GPT_SLEEP_MODE

}Gpt_TimerMode;

typedef enum
{
    GPT_ONE_SHOT_MODE ,

    GPT_CONTINUOUS_MODE

}Gpt_ChannelMode;


typedef struct
{
    Gpt_ChannelType             channel_ID;

    Gpt_ChannelMode             channel_Mode ;

    Gpt_ChannelTickFrequency    channel_Frequency;

    GptChannelTickValueMax      channel_MaxTicks;

    void (*Gpt_PtrCallBack_Fnc)(void);

}Gpt_ConfigType;

typedef enum
{
    GPT_PREDEF_TIMER_1US_16BIT ,
    GPT_PREDEF_TIMER_1US_24BIT ,
    GPT_PREDEF_TIMER_1US_32BIT ,
    GPT_PREDEF_TIMER_100US_32BIT

}Gpt_PredefTimer;
/******************************************************************************
* \Syntax          : void Gpt_Init( const Gpt_ConfigType* ConfigPtr)
* \Description     : Initialize GPT Module
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
extern void Gpt_Init( const Gpt_ConfigType* ConfigPtr);

/******************************************************************************
* \Syntax          : void Gpt_DisableNotification(Gpt_ChannelType Channel)
* \Description     : Disable Interrupts
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
extern void Gpt_DisableNotification(Gpt_ChannelType Channel);

/******************************************************************************
* \Syntax          : void Gpt_EnableNotification(Gpt_ChannelType Channel)
* \Description     : Enable Interrupts
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
extern void Gpt_EnableNotification(Gpt_ChannelType Channel);


/******************************************************************************
* \Syntax          : void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value )
* \Description     : StartTimer
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
extern void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value );
/******************************************************************************
* \Syntax          : void Gpt_StopTimer( Gpt_ChannelType Channel );
* \Description     : StopTimer
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
extern void Gpt_StopTimer( Gpt_ChannelType Channel );
/******************************************************************************
* \Syntax          : Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel );
* \Description     : Get Elapsed Time in Ticks
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : Gpt_ValueType
*******************************************************************************/
extern Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel );
/******************************************************************************
* \Syntax          : Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel );
* \Description     : Get Remaining Time in Ticks
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : Gpt_ValueType
*******************************************************************************/
extern Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel );
/******************************************************************************
* \Syntax          : Std_ReturnType Gpt_GetPredefTimerValue( Gpt_PredefTimer TypePredefTimer, uint32* TimeValuePtr);
* \Description     : Get Pre Defined Value
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : Std_ReturnType
*******************************************************************************/
Std_ReturnType Gpt_GetPredefTimerValue( Gpt_PredefTimer TypePredefTimer, uint32* TimeValuePtr);
#endif /* GPT_H_ */
