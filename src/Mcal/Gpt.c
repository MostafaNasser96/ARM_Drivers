/*
 * Gpt.c
 *
 *  Created on: Jul 13, 2020
 *      Author: kh
 */

#include "Gpt.h"
#include "Gpt_Cfg.h"

#define GPT_NO_OF_CHANNELS              12


#define GPT_CFG_REG(BASE_ADDRESS)     (*(volatile uint32 *) ( BASE_ADDRESS ))

#define GPT_INTERVAL_LOAD_REG(BASE_ADDRESS, OFFSET)     (*(volatile uint32 *) ( BASE_ADDRESS + OFFSET ))

#define GPT_COUNTER_VALUE_REG(BASE_ADDRESS, OFFSET)     (*(volatile uint32 *) ( BASE_ADDRESS + OFFSET ))

#define GPT_PERIODIC_MODE   1

#define MAX_16_BIT                          65535
#define MAX_24_BIT                          16777215
#define MAX_32_BIT                          4294967295
#define MAX_48_BIT                          281474976710655

#define GPT_INDIVIDUAL_MODE_16_BIT            1
#define GPT_INDIVIDUAL_MODE_24_BIT            2
#define GPT_INDIVIDUAL_MODE_32_BIT            3
#define GPT_INDIVIDUAL_MODE_48_BIT            4
#define GPT_CONCATENATED_MODE_32_BIT          5
#define GPT_CONCATENATED_MODE_64_BIT          6



static uint8 g_CheckInit = E_NOT_OK;

static uint8 g_ChannelMode[GPT_NO_OF_CHANNELS] = {0} ;

static uint8 g_ChannelTarget[GPT_NO_OF_CHANNELS] = {0} ;

static uint32 g_Base_Address[GPT_NO_OF_CHANNELS] = {0};
static uint32 g_Base_PreDefAddress ;
static uint8  g_PreDef_OneTime = E_OK ;

static uint8 g_No_Of_Bits[GPT_NO_OF_CHANNELS] = {0};

static Gpt_ConfigType g_arrUsedChannels[GPT_NO_OF_CHANNELS] = {0};

static void (*CallBack_0_Ptr) (void) = 0;
static void (*CallBack_1_Ptr) (void) = 0;
static void (*CallBack_2_Ptr) (void) = 0;
static void (*CallBack_3_Ptr) (void) = 0;
static void (*CallBack_4_Ptr) (void) = 0;
static void (*CallBack_5_Ptr) (void) = 0;
static void (*CallBack_W_0_Ptr) (void)= 0 ;
static void (*CallBack_W_1_Ptr) (void)= 0 ;
static void (*CallBack_W_2_Ptr) (void)= 0 ;
static void (*CallBack_W_3_Ptr) (void)= 0 ;
static void (*CallBack_W_4_Ptr) (void)= 0 ;
static void (*CallBack_W_5_Ptr) (void)= 0 ;

 void Timer0_W_Handler(void);
 void Timer1_W_Handler(void);
 void Timer2_W_Handler(void);
 void Timer3_W_Handler(void);
 void Timer4_W_Handler(void);
 void Timer5_W_Handler(void);
 void Timer0_Handler(void);
 void Timer1_Handler(void);
 void Timer2_Handler(void);
 void Timer3_Handler(void);
 void Timer4_Handler(void);
 void Timer5_Handler(void);


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
void Gpt_Init( const Gpt_ConfigType* ConfigPtr)
{
    uint32 Bit_BandStart, Bit_BandEnd ;

    if(ConfigPtr != NULL_PTR)
    {
        if(g_arrUsedChannels[ConfigPtr->channel_ID].channel_ID == 0 )
        {

            g_arrUsedChannels[ConfigPtr->channel_ID].channel_ID = ConfigPtr->channel_ID ;
            g_arrUsedChannels[ConfigPtr->channel_ID].channel_Mode = ConfigPtr->channel_Mode ;
            g_arrUsedChannels[ConfigPtr->channel_ID].channel_MaxTicks = ConfigPtr->channel_MaxTicks;
            g_arrUsedChannels[ConfigPtr->channel_ID].channel_Frequency = ConfigPtr->channel_Frequency;

            if(ConfigPtr->channel_ID == GPT_16_32_BIT_TIMER_0)
            {
                g_Base_Address[ConfigPtr->channel_ID] = GPT_16_32_BIT_TIMER_0_BASE ;

                CallBack_0_Ptr = ConfigPtr->Gpt_PtrCallBack_Fnc ;
            }
            else if(ConfigPtr->channel_ID == GPT_16_32_BIT_TIMER_1)
            {
                g_Base_Address[ConfigPtr->channel_ID] = GPT_16_32_BIT_TIMER_1_BASE ;

                CallBack_1_Ptr = ConfigPtr->Gpt_PtrCallBack_Fnc ;
            }
            else if(ConfigPtr->channel_ID == GPT_16_32_BIT_TIMER_2)
            {
                g_Base_Address[ConfigPtr->channel_ID] = GPT_16_32_BIT_TIMER_2_BASE ;

                CallBack_2_Ptr = ConfigPtr->Gpt_PtrCallBack_Fnc ;
            }
            else if(ConfigPtr->channel_ID == GPT_16_32_BIT_TIMER_3)
            {
                g_Base_Address[ConfigPtr->channel_ID] = GPT_16_32_BIT_TIMER_3_BASE ;

                CallBack_3_Ptr = ConfigPtr->Gpt_PtrCallBack_Fnc ;
            }
            else if(ConfigPtr->channel_ID == GPT_16_32_BIT_TIMER_4)
            {
                g_Base_Address[ConfigPtr->channel_ID] = GPT_16_32_BIT_TIMER_4_BASE ;

                CallBack_4_Ptr = ConfigPtr->Gpt_PtrCallBack_Fnc ;
            }
            else if(ConfigPtr->channel_ID == GPT_16_32_BIT_TIMER_5)
            {
                g_Base_Address[ConfigPtr->channel_ID] = GPT_16_32_BIT_TIMER_5_BASE ;

                CallBack_5_Ptr = ConfigPtr->Gpt_PtrCallBack_Fnc ;
            }
            else if(ConfigPtr->channel_ID == GPT_32_64_BIT_WIDE_TIMER_0)
            {
                g_Base_Address[ConfigPtr->channel_ID] = GPT_32_64_BIT_WIDE_TIMER_0_BASE ;

                CallBack_W_0_Ptr = ConfigPtr->Gpt_PtrCallBack_Fnc ;
            }
            else if(ConfigPtr->channel_ID == GPT_32_64_BIT_WIDE_TIMER_1)
            {
                g_Base_Address[ConfigPtr->channel_ID] = GPT_32_64_BIT_WIDE_TIMER_1_BASE ;

                CallBack_W_1_Ptr = ConfigPtr->Gpt_PtrCallBack_Fnc ;
            }
            else if(ConfigPtr->channel_ID == GPT_32_64_BIT_WIDE_TIMER_2)
            {
                g_Base_Address[ConfigPtr->channel_ID] = GPT_32_64_BIT_WIDE_TIMER_2_BASE ;

                CallBack_W_2_Ptr = ConfigPtr->Gpt_PtrCallBack_Fnc ;
            }
            else if(ConfigPtr->channel_ID == GPT_32_64_BIT_WIDE_TIMER_3)
            {
                g_Base_Address[ConfigPtr->channel_ID] = GPT_32_64_BIT_WIDE_TIMER_3_BASE ;

                CallBack_W_3_Ptr = ConfigPtr->Gpt_PtrCallBack_Fnc ;
            }
            else if(ConfigPtr->channel_ID == GPT_32_64_BIT_WIDE_TIMER_4)
            {
                g_Base_Address[ConfigPtr->channel_ID] = GPT_32_64_BIT_WIDE_TIMER_4_BASE ;

                CallBack_W_4_Ptr = ConfigPtr->Gpt_PtrCallBack_Fnc ;
            }
            else if(ConfigPtr->channel_ID == GPT_32_64_BIT_WIDE_TIMER_5)
            {
                g_Base_Address[ConfigPtr->channel_ID] = GPT_32_64_BIT_WIDE_TIMER_5_BASE ;

                CallBack_W_5_Ptr = ConfigPtr->Gpt_PtrCallBack_Fnc ;
            }

            /*Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making any changes*/
            BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_Address[ConfigPtr->channel_ID] ,GPT_CONTROL_OFFSET ,GPT_CONTROL_EN_A,STD_LOW);
            BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_Address[ConfigPtr->channel_ID] ,GPT_CONTROL_OFFSET ,GPT_CONTROL_EN_B,STD_LOW);

            /*Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000*/
            GPT_CFG_REG(g_Base_Address[ConfigPtr->channel_ID]) = 0 ;

            Bit_BandStart = GPT_TIMER_MODE_START ;
            Bit_BandEnd   = GPT_TIMER_MODE_END   ;

            /*Set Channel A to chosen Mode Periodic or One Shot Mode*/
            BIT_GROUP_BANDING(GPT_PRIVATE_PRI_BASE_ADD , GPT_PRIVATE_PRI_BASE_ALIAS , g_Base_Address[ConfigPtr->channel_ID] , GPT_TIMER_A_MODE_OFFSET , Bit_BandStart , Bit_BandEnd ,ConfigPtr->channel_Mode);

            /*Disable Notification */
            BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_Address[ConfigPtr->channel_ID] ,GPT_INTERRUPT_MASK_OFFSET ,GPT_INTERRUPT_B_TIME_OUT,STD_LOW);
            BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_Address[ConfigPtr->channel_ID] ,GPT_INTERRUPT_MASK_OFFSET ,GPT_INTERRUPT_A_TIME_OUT,STD_LOW);

            /*Find Number of Bits in Max Ticks */

            g_No_Of_Bits[ConfigPtr->channel_ID] = 0;

            while(ConfigPtr->channel_MaxTicks != FALSE)
            {
                g_No_Of_Bits[ConfigPtr->channel_ID]++;

                (g_arrUsedChannels[ConfigPtr->channel_ID].channel_MaxTicks) = (g_arrUsedChannels[ConfigPtr->channel_ID].channel_MaxTicks) >> 1 ;

            }

            g_arrUsedChannels[ConfigPtr->channel_ID].channel_MaxTicks = ConfigPtr->channel_MaxTicks;

            g_CheckInit = E_OK;

            if(g_PreDef_OneTime == E_OK)
            {

                if(GPT_PREDEF_TIMER_CHANNEL== GPT_16_32_BIT_TIMER_0)
                {
                    g_Base_PreDefAddress = GPT_16_32_BIT_TIMER_0_BASE ;
                }
                else if(GPT_PREDEF_TIMER_CHANNEL == GPT_16_32_BIT_TIMER_1)
                {
                    g_Base_PreDefAddress = GPT_16_32_BIT_TIMER_1_BASE ;
                }
                else if(GPT_PREDEF_TIMER_CHANNEL == GPT_16_32_BIT_TIMER_2)
                {
                    g_Base_PreDefAddress = GPT_16_32_BIT_TIMER_2_BASE ;
                }
                else if(GPT_PREDEF_TIMER_CHANNEL == GPT_16_32_BIT_TIMER_3)
                {
                    g_Base_PreDefAddress = GPT_16_32_BIT_TIMER_3_BASE ;
                }
                else if(GPT_PREDEF_TIMER_CHANNEL == GPT_16_32_BIT_TIMER_4)
                {
                    g_Base_PreDefAddress = GPT_16_32_BIT_TIMER_4_BASE ;
                }
                else if(GPT_PREDEF_TIMER_CHANNEL == GPT_16_32_BIT_TIMER_5)
                {
                    g_Base_PreDefAddress = GPT_16_32_BIT_TIMER_5_BASE ;
                }
                else if(GPT_PREDEF_TIMER_CHANNEL == GPT_32_64_BIT_WIDE_TIMER_0)
                {
                    g_Base_PreDefAddress = GPT_32_64_BIT_WIDE_TIMER_0_BASE ;
                }
                else if(GPT_PREDEF_TIMER_CHANNEL == GPT_32_64_BIT_WIDE_TIMER_1)
                {
                    g_Base_PreDefAddress = GPT_32_64_BIT_WIDE_TIMER_1_BASE ;
                }
                else if(GPT_PREDEF_TIMER_CHANNEL == GPT_32_64_BIT_WIDE_TIMER_2)
                {
                    g_Base_PreDefAddress = GPT_32_64_BIT_WIDE_TIMER_2_BASE ;
                }
                else if(GPT_PREDEF_TIMER_CHANNEL == GPT_32_64_BIT_WIDE_TIMER_3)
                {
                    g_Base_PreDefAddress = GPT_32_64_BIT_WIDE_TIMER_3_BASE ;
                }
                else if(GPT_PREDEF_TIMER_CHANNEL == GPT_32_64_BIT_WIDE_TIMER_4)
                {
                    g_Base_PreDefAddress = GPT_32_64_BIT_WIDE_TIMER_4_BASE ;
                }
                else if(GPT_PREDEF_TIMER_CHANNEL == GPT_32_64_BIT_WIDE_TIMER_5)
                {
                    g_Base_PreDefAddress = GPT_32_64_BIT_WIDE_TIMER_5_BASE ;
                }

                #if(GPT_PREDEF_TIMER_1US_16BIT == ENABLE || GPT_PREDEF_TIMER_1US_24BIT == ENABLE || GPT_PREDEF_TIMER_1US_32BIT == ENABLE || GPT_PREDEF_TIMER_100US_32BIT == ENABLE )
                    /*Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared) before making any changes*/
                    BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_PreDefAddress ,GPT_CONTROL_OFFSET ,GPT_CONTROL_EN_A,STD_LOW);
                    BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_PreDefAddress ,GPT_CONTROL_OFFSET ,GPT_CONTROL_EN_B,STD_LOW);

                    /*Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000*/
                    GPT_CFG_REG(g_Base_PreDefAddress) = 0 ;

                    Bit_BandStart = GPT_TIMER_MODE_START ;
                    Bit_BandEnd   = GPT_TIMER_MODE_END   ;

                    /*Set Channel A to chosen Mode Periodic or One Shot Mode*/
                    BIT_GROUP_BANDING(GPT_PRIVATE_PRI_BASE_ADD , GPT_PRIVATE_PRI_BASE_ALIAS , g_Base_PreDefAddress , GPT_TIMER_A_MODE_OFFSET , Bit_BandStart , Bit_BandEnd ,GPT_PERIODIC_MODE);

                    /*Disable Notification */
                    BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_PreDefAddress ,GPT_INTERRUPT_MASK_OFFSET ,GPT_INTERRUPT_B_TIME_OUT,STD_LOW);
                    BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_PreDefAddress ,GPT_INTERRUPT_MASK_OFFSET ,GPT_INTERRUPT_A_TIME_OUT,STD_LOW);

                    Bit_BandStart = GPT_CFG_START ;
                    Bit_BandEnd   = GPT_CFG_END   ;

                    /*Set channel A to 32 bit Mode*/
                    BIT_GROUP_BANDING(GPT_PRIVATE_PRI_BASE_ADD , GPT_PRIVATE_PRI_BASE_ALIAS , g_Base_PreDefAddress , GPT_CFG_OFFSET , Bit_BandStart , Bit_BandEnd ,GPT_CFG_32_BIT_W_TIMER);

                    GPT_INTERVAL_LOAD_REG(g_Base_PreDefAddress, GPT_TIMER_A_INTERVAL_LOAD_OFFSET) = 0xFFFFFFFF;

                    GPT_INTERVAL_LOAD_REG(g_Base_PreDefAddress, GPT_TIMER_A_PRESCALLER_OFFSET) = 0x7FFF;

                    BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_PreDefAddress ,GPT_CONTROL_OFFSET ,GPT_CONTROL_EN_A,STD_HIGH);

                #endif

                g_PreDef_OneTime = E_NOT_OK ;
            }

        }
        else
        {

        }

    }
    else
    {
        g_CheckInit = E_NOT_OK;  /*Init Status : Error*/
    }
}


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
void Gpt_DisableNotification(Gpt_ChannelType Channel)
{
    if(g_CheckInit == E_OK)
    {
        BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_Address[Channel] ,GPT_INTERRUPT_MASK_OFFSET ,GPT_INTERRUPT_A_TIME_OUT,STD_LOW);
    }
}

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
void Gpt_EnableNotification(Gpt_ChannelType Channel)
{
    if(g_CheckInit == E_OK)
    {
        BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_Address[Channel] ,GPT_INTERRUPT_MASK_OFFSET ,GPT_INTERRUPT_A_TIME_OUT,STD_HIGH);

    }
}


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
void Gpt_StartTimer( Gpt_ChannelType Channel, Gpt_ValueType Value )
{
    uint8 Bit_BandStart , Bit_BandEnd ;

    if(g_CheckInit == E_OK)
    {

        if(Value <= g_arrUsedChannels[Channel].channel_MaxTicks)
        {
            if(g_arrUsedChannels[Channel].channel_ID <=  GPT_16_32_BIT_TIMER_5)
            {
                  /*____________________________________________________
                           * In Case of  16  Bit Individual
                    _____________________________________________________*/

                  if(Value <= MAX_24_BIT )
                  {


                      if(Value <= MAX_16_BIT )
                      {
                          Bit_BandStart = GPT_CFG_START ;
                          Bit_BandEnd   = GPT_CFG_END   ;

                          /*Set channel A to 16 bit Mode*/
                          BIT_GROUP_BANDING(GPT_PRIVATE_PRI_BASE_ADD , GPT_PRIVATE_PRI_BASE_ALIAS ,g_Base_Address[Channel] , GPT_CFG_OFFSET , Bit_BandStart , Bit_BandEnd ,GPT_CFG_16_BIT_TIMER);

                          g_ChannelMode[Channel] = GPT_INDIVIDUAL_MODE_16_BIT ;  /*save Channel Mode */

                          GPT_INTERVAL_LOAD_REG(g_Base_Address[Channel], GPT_TIMER_A_INTERVAL_LOAD_OFFSET) = (uint16) Value;
                      }
                      else
                      {
                          Bit_BandStart = GPT_CFG_START ;
                          Bit_BandEnd   = GPT_CFG_END   ;

                          /*Set channel A to 24 bit Mode*/
                          BIT_GROUP_BANDING(GPT_PRIVATE_PRI_BASE_ADD , GPT_PRIVATE_PRI_BASE_ALIAS ,g_Base_Address[Channel] , GPT_CFG_OFFSET , Bit_BandStart , Bit_BandEnd ,GPT_CFG_16_BIT_TIMER);

                          g_ChannelMode[Channel] = GPT_INDIVIDUAL_MODE_24_BIT ;  /*save Channel Mode */

                          GPT_INTERVAL_LOAD_REG(g_Base_Address[Channel], GPT_TIMER_A_INTERVAL_LOAD_OFFSET) = (uint16) Value ;
                          GPT_INTERVAL_LOAD_REG(g_Base_Address[Channel], GPT_TIMER_A_PRESCALLER_OFFSET) = (uint8) (Value >> 16 ) ;

                      }


                  }

                  /*____________________________________________________
                             * In Case of  32  Bit Concatenated
                    _____________________________________________________*/
                  else if (Value <= MAX_32_BIT )
                  {

                      Bit_BandStart = GPT_CFG_START ;
                      Bit_BandEnd   = GPT_CFG_END   ;

                      /*Set channel A to 32 bit Mode*/
                      BIT_GROUP_BANDING(GPT_PRIVATE_PRI_BASE_ADD , GPT_PRIVATE_PRI_BASE_ALIAS , g_Base_Address[Channel], GPT_CFG_OFFSET , Bit_BandStart , Bit_BandEnd ,GPT_CFG_32_BIT_TIMER);

                      g_ChannelMode[Channel] = GPT_CONCATENATED_MODE_32_BIT ;  /*save Channel Mode */

                      GPT_INTERVAL_LOAD_REG(g_Base_Address[Channel], GPT_TIMER_B_INTERVAL_LOAD_OFFSET) = (uint16) ((Value) >> 16);
                      GPT_INTERVAL_LOAD_REG(g_Base_Address[Channel], GPT_TIMER_A_INTERVAL_LOAD_OFFSET) = (uint32) Value;

                  }
            }
            /*___________________________________________________________________________________________________
                    * In Case of Wide timers 32 / 64 Bit
             ___________________________________________________________________________________________________*/
            else if(g_arrUsedChannels[Channel].channel_ID >=  GPT_32_64_BIT_WIDE_TIMER_0 && g_arrUsedChannels[Channel].channel_ID <=  GPT_32_64_BIT_WIDE_TIMER_5)
            {

                /*____________________________________________________
                          * In Case of  32  Bit Individual Mode
                  _____________________________________________________*/
                if(Value <= MAX_48_BIT )
                {

                    if(Value <= MAX_32_BIT)
                    {

                        Bit_BandStart = GPT_CFG_START ;
                        Bit_BandEnd   = GPT_CFG_END   ;

                        /*Set channel A to 32 bit Mode*/
                        BIT_GROUP_BANDING(GPT_PRIVATE_PRI_BASE_ADD , GPT_PRIVATE_PRI_BASE_ALIAS , g_Base_Address[Channel] , GPT_CFG_OFFSET , Bit_BandStart , Bit_BandEnd ,GPT_CFG_32_BIT_W_TIMER);

                        g_ChannelMode[Channel] = GPT_INDIVIDUAL_MODE_32_BIT ;  /*save Channel Mode */

                        GPT_INTERVAL_LOAD_REG(g_Base_Address[Channel], GPT_TIMER_A_INTERVAL_LOAD_OFFSET) = (uint32) Value;
                    }
                    else
                    {
                        Bit_BandStart = GPT_CFG_START ;
                        Bit_BandEnd   = GPT_CFG_END   ;

                        /*Set channel A to 48 bit Mode*/
                        BIT_GROUP_BANDING(GPT_PRIVATE_PRI_BASE_ADD , GPT_PRIVATE_PRI_BASE_ALIAS , g_Base_Address[Channel] , GPT_CFG_OFFSET , Bit_BandStart , Bit_BandEnd ,GPT_CFG_32_BIT_W_TIMER);

                        g_ChannelMode[Channel] = GPT_INDIVIDUAL_MODE_48_BIT ;  /*save Channel Mode */

                        GPT_INTERVAL_LOAD_REG(g_Base_Address[Channel], GPT_TIMER_A_INTERVAL_LOAD_OFFSET) = (uint32) Value;
                        GPT_INTERVAL_LOAD_REG(g_Base_Address[Channel], GPT_TIMER_A_PRESCALLER_OFFSET) = (uint32) (Value >> 16 );


                    }

                }
                /*____________________________________________________
                        * In Case of  64  Bit Concatenated
                 _____________________________________________________*/
                else
                {

                    Bit_BandStart = GPT_CFG_START ;
                    Bit_BandEnd   = GPT_CFG_END   ;

                    /*Set channel A & B to 64 bit Mode*/
                    BIT_GROUP_BANDING(GPT_PRIVATE_PRI_BASE_ADD , GPT_PRIVATE_PRI_BASE_ALIAS ,g_Base_Address[Channel] , GPT_CFG_OFFSET , Bit_BandStart , Bit_BandEnd ,GPT_CFG_64_BIT_W_TIMER);

                    g_ChannelMode[Channel] = GPT_CONCATENATED_MODE_64_BIT ;  /*save Channel Mode */

                    GPT_INTERVAL_LOAD_REG(g_Base_Address[Channel], GPT_TIMER_A_INTERVAL_LOAD_OFFSET) = (uint32) Value;
                    GPT_INTERVAL_LOAD_REG(g_Base_Address[Channel], GPT_TIMER_B_INTERVAL_LOAD_OFFSET) = (uint32) ((Value) >> REGISTER_LENGTH_BITS);
                }

            }


            g_ChannelTarget[Channel] = Value ;

            BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_Address[Channel] ,GPT_CONTROL_OFFSET ,GPT_CONTROL_EN_A,STD_HIGH);
            BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_Address[Channel] ,GPT_CONTROL_OFFSET ,GPT_CONTROL_EN_B,STD_HIGH);


        }
        else
        {
            /*Nothing*/
        }

    }
    else
    {
        /*Nothing*/
    }
}

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
void Gpt_StopTimer( Gpt_ChannelType Channel )
{
    if(g_CheckInit == E_OK)
    {
        BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_Address[Channel] ,GPT_CONTROL_OFFSET ,GPT_CONTROL_EN_A,STD_LOW);
        BIT_BANDING(GPT_PRIVATE_PRI_BASE_ADD, GPT_PRIVATE_PRI_BASE_ALIAS, g_Base_Address[Channel] ,GPT_CONTROL_OFFSET ,GPT_CONTROL_EN_B,STD_LOW);
    }
}

/******************************************************************************
* \Syntax          : Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel );
* \Description     : Get Elapsed Time in Ticks
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : Std_ReturnType
*******************************************************************************/
Gpt_ValueType Gpt_GetTimeElapsed( Gpt_ChannelType Channel )
{
    Gpt_ValueType u64_ElapsedTime , Value = 1;
    uint32 u32_Power , TempValue ;

    u32_Power = g_No_Of_Bits[Channel];

    while(u32_Power != 0)
    {
        Value *= 2 ;

        u32_Power-- ;
    }
    if(g_CheckInit == E_OK)
    {
        if(g_ChannelMode[Channel] == GPT_INDIVIDUAL_MODE_16_BIT)
        {
            u64_ElapsedTime =  (uint16) (GPT_COUNTER_VALUE_REG(g_Base_Address[Channel], GPT_TIMER_A_VALUE_OFFSET) & Value) ;
        }
        else if(g_ChannelMode[Channel] == GPT_INDIVIDUAL_MODE_24_BIT)
        {
            u64_ElapsedTime = (GPT_COUNTER_VALUE_REG(g_Base_Address[Channel], GPT_TIMER_A_VALUE_OFFSET) & Value);
        }
        else if(g_ChannelMode[Channel] == GPT_INDIVIDUAL_MODE_32_BIT)
        {
            u64_ElapsedTime = (uint32) (GPT_COUNTER_VALUE_REG(g_Base_Address[Channel], GPT_TIMER_A_VALUE_OFFSET) & Value);
        }
        else if(g_ChannelMode[Channel] == GPT_INDIVIDUAL_MODE_48_BIT)
        {
            TempValue = ((uint16) GPT_COUNTER_VALUE_REG(g_Base_Address[Channel], GPT_TIMER_A_PRESCALLER_VALUE_OFFSET)) ;
            u64_ElapsedTime = (GPT_COUNTER_VALUE_REG(g_Base_Address[Channel], GPT_TIMER_A_VALUE_OFFSET));

            while(TempValue != ((uint16) GPT_COUNTER_VALUE_REG(g_Base_Address[Channel], GPT_TIMER_A_PRESCALLER_VALUE_OFFSET)))
            {
                TempValue = ((uint16) GPT_COUNTER_VALUE_REG(g_Base_Address[Channel], GPT_TIMER_A_PRESCALLER_VALUE_OFFSET)) ;
                u64_ElapsedTime = (GPT_COUNTER_VALUE_REG(g_Base_Address[Channel], GPT_TIMER_A_VALUE_OFFSET));
            }
            u64_ElapsedTime |= TempValue << REGISTER_LENGTH_BITS ;
            u64_ElapsedTime &= Value ;
        }
        else if(g_ChannelMode[Channel] == GPT_CONCATENATED_MODE_32_BIT)
        {
            u64_ElapsedTime = (uint32)(GPT_COUNTER_VALUE_REG(g_Base_Address[Channel], GPT_TIMER_A_VALUE_OFFSET) & Value);
        }
        else if(g_ChannelMode[Channel] == GPT_CONCATENATED_MODE_64_BIT)
        {
            TempValue = ((uint32) GPT_COUNTER_VALUE_REG(g_Base_Address[Channel], GPT_TIMER_B_VALUE_OFFSET)) ;
            u64_ElapsedTime = (GPT_COUNTER_VALUE_REG(g_Base_Address[Channel], GPT_TIMER_A_VALUE_OFFSET) & Value);

            while(TempValue !=((uint32) GPT_COUNTER_VALUE_REG(g_Base_Address[Channel], GPT_TIMER_B_VALUE_OFFSET)))
            {
                TempValue = ((uint32) GPT_COUNTER_VALUE_REG(g_Base_Address[Channel], GPT_TIMER_B_VALUE_OFFSET)) ;
                u64_ElapsedTime = (GPT_COUNTER_VALUE_REG(g_Base_Address[Channel], GPT_TIMER_A_VALUE_OFFSET));
            }
            u64_ElapsedTime |= TempValue << REGISTER_LENGTH_BITS ;

            u64_ElapsedTime &= Value ;

        }

    }

    return u64_ElapsedTime ;
}


/******************************************************************************
* \Syntax          : Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel );
* \Description     : Get Remaining Time in Ticks
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : None
* \Parameters (out): None
* \Return value:   : Std_ReturnType
*******************************************************************************/
Gpt_ValueType Gpt_GetTimeRemaining( Gpt_ChannelType Channel )
{
    Gpt_ValueType u64_ElapsedTime , u64_RemainingTime = 0  ;

    if(g_CheckInit == E_OK)
    {
        u64_ElapsedTime = Gpt_GetTimeElapsed(Channel);

        u64_RemainingTime = g_ChannelTarget[Channel] - u64_ElapsedTime  ;
    }

    return u64_RemainingTime ;
}

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
Std_ReturnType Gpt_GetPredefTimerValue( Gpt_PredefTimer TypePredefTimer, uint32* TimeValuePtr)
{
    uint8 u8_ErrorStatus = E_OK ;
    uint32 TempValue ;

    if(g_CheckInit == E_OK)
    {
        if(TypePredefTimer == GPT_PREDEF_TIMER_1US_16BIT)
        {
            *TimeValuePtr = (uint16) (GPT_COUNTER_VALUE_REG(g_Base_PreDefAddress, GPT_TIMER_A_VALUE_OFFSET) & 0x0000FFFF);
        }
        else if (TypePredefTimer == GPT_PREDEF_TIMER_1US_24BIT)
        {
            *TimeValuePtr = (uint16) (GPT_COUNTER_VALUE_REG(g_Base_PreDefAddress, GPT_TIMER_A_VALUE_OFFSET) & 0x01FFFFFF);
        }
        else if (TypePredefTimer == GPT_PREDEF_TIMER_1US_32BIT)
        {
            *TimeValuePtr = (uint32) (GPT_COUNTER_VALUE_REG(g_Base_PreDefAddress, GPT_TIMER_A_VALUE_OFFSET));
        }
        else if (TypePredefTimer == GPT_PREDEF_TIMER_100US_32BIT)
        {
            TempValue = ((uint16) GPT_COUNTER_VALUE_REG(g_Base_PreDefAddress, GPT_TIMER_A_PRESCALLER_VALUE_OFFSET)) ;

            *TimeValuePtr = (GPT_COUNTER_VALUE_REG(g_Base_PreDefAddress, GPT_TIMER_A_VALUE_OFFSET));

            while(TempValue != ((uint16) GPT_COUNTER_VALUE_REG(g_Base_PreDefAddress, GPT_TIMER_A_PRESCALLER_VALUE_OFFSET)))
            {
                TempValue = ((uint16) GPT_COUNTER_VALUE_REG(g_Base_PreDefAddress, GPT_TIMER_A_PRESCALLER_VALUE_OFFSET)) ;
                *TimeValuePtr = (GPT_COUNTER_VALUE_REG(g_Base_PreDefAddress, GPT_TIMER_A_VALUE_OFFSET));
            }
            *TimeValuePtr = *TimeValuePtr >> 7 ;
            *TimeValuePtr |= (uint32)(TempValue << 25) ;
        }
        else
        {
            u8_ErrorStatus = E_NOT_OK ;
        }
    }
    else
    {
        u8_ErrorStatus = E_NOT_OK ;
    }

    return u8_ErrorStatus ;
}

 void Timer0_W_Handler(void)
{
    if(CallBack_W_0_Ptr != 0)
    {
        CallBack_W_0_Ptr();
    }
}

void Timer1_W_Handler(void)
{
    if(CallBack_W_1_Ptr != 0)
    {
        CallBack_W_1_Ptr();
    }
}

 void Timer2_W_Handler(void)
{
    if(CallBack_W_2_Ptr != 0)
    {
        CallBack_W_2_Ptr();
    }

}

 void Timer3_W_Handler(void)
{
    if(CallBack_W_3_Ptr != 0)
    {
        CallBack_W_3_Ptr();
    }
}

void Timer4_W_Handler(void)
{
    if(CallBack_W_4_Ptr != 0)
    {
        CallBack_W_4_Ptr();
    }

}

void Timer5_W_Handler(void)
{
    if(CallBack_W_5_Ptr != 0)
    {
        CallBack_W_5_Ptr();
    }

}

void Timer0_Handler(void)
{
    if(CallBack_0_Ptr != 0)
    {
        CallBack_0_Ptr();
    }

}

void Timer1_Handler(void)
{
    if(CallBack_1_Ptr != 0)
    {
        CallBack_1_Ptr();
    }

}

 void Timer2_Handler(void)
{
    if(CallBack_2_Ptr != 0)
    {
        CallBack_2_Ptr();
    }

}

void Timer3_Handler(void)
{
    if(CallBack_3_Ptr != 0)
    {
        CallBack_3_Ptr();
    }
}

void Timer4_Handler(void)
{
    if(CallBack_4_Ptr != 0)
    {
        CallBack_4_Ptr();
    }

}

void Timer5_Handler(void)
{
    if(CallBack_5_Ptr != 0)
    {
        CallBack_5_Ptr();
    }

}
