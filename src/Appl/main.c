#include "Std_Types.h"
#include "Platform_Types.h"
#include "Bit_Math.h"
#include "nvic.h"
#include "Mcu.h"
#include "Mcu_Lcfg.h"
#include "Gpt.h"
#include "Port.h"
#include "Gio.h"
#include "Wdt.h"
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.c"
#include "driverlib/timer.h"

#define SYS_CTRL_RCGC2  (*((volatile unsigned long *)0x400FE108))   //offset of RCGC2 register is 0x108

#define SYS_CTRL_RCGC1  (*((volatile unsigned long *)0x400FE104))   //offset of RCGC2 register is 0x108

uint32 value = 0 , value2 , def;

void gk_Handler(void);

int main(void)
{


    NVIC_init();
    MCU_init(MCU_CfgArr);
    Mcu_InitClock(0) ;




    Gpt_ConfigType x5 = {GPT_16_32_BIT_TIMER_1 , GPT_ONE_SHOT_MODE, 4 , 16000001, gk_Handler};
    Gpt_Init( &x5);
    //Gpt_EnableNotification(GPT_16_32_BIT_TIMER_1);




    // Wdg_ConfigType x4 ={Wdg_STANDARD_INTERRUPT , 4000 , 10000};

//       Wdg_Init(&x);
//       Wdg_SetTriggerCondition(40000);

   Port_ConfigType x = {PORT_PF_1 ,PORT_PIN_OUT, PORT_GPIO, PORT_FLOATING_PIN , PORT_4_mA  };
   Port_ConfigType x2 = {PORT_PF_2 ,PORT_PIN_OUT, PORT_GPIO, PORT_FLOATING_PIN , PORT_4_mA  };
   Port_ConfigType x3 = {PORT_PF_3 ,PORT_PIN_OUT, PORT_GPIO, PORT_FLOATING_PIN , PORT_4_mA  };
  //  Port_ConfigType x2 = {PORT_PA_7 ,PORT_PIN_OUT, PORT_GPIO, PORT_OPEN_DRAIN , PORT_4_mA  };
//
    Port_Init(&x);
    Port_Init(&x2);
    Port_Init(&x3);

//
    //Dio_WritePort(GIO_F_APB, 0xF0);

//
//    value = Dio_ReadChannel(GIO_PF_3) ;
//    value = Dio_ReadChannel(GIO_PA_4) ;
//    value = Dio_ReadChannel(GIO_PA_7) ;
//    value = Dio_ReadChannel(GIO_PF_4) ;
//
//    value = TypeDio_ReadPort(GIO_F_APB) ;
//    value = Dio_FlipChannel(GIO_PF_4);
//    Wdg_Init(&x4);
    //Wdg_Init(&x4);


   // Dio_WriteChannel(PORT_PF_1, STD_HIGH);
                    // Dio_WriteChannel(PORT_PF_2, STD_LOW);
                    // Dio_WriteChannel(PORT_PF_3, STD_LOW);


                     Gpt_StartTimer(GPT_16_32_BIT_TIMER_1 , 16000000);
                     Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_1US_24_BIT, &value);
                     while((Gpt_GetTimeElapsed(GPT_16_32_BIT_TIMER_1)) != 0);
                     Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_1US_24_BIT, &value2);

                     def = value2 - value ;
                     def /= 16000000 ;

                     if(def == 4)
                     {
                         Dio_WriteChannel(PORT_PF_1, STD_HIGH);
                         Dio_WriteChannel(PORT_PF_2, STD_LOW);
                         Dio_WriteChannel(PORT_PF_3, STD_LOW);
                     }



	while(1)
	{
//	    Dio_WriteChannel(PORT_PF_1, STD_HIGH);
//	               Dio_WriteChannel(PORT_PF_2, STD_LOW);
//	               Dio_WriteChannel(PORT_PF_3, STD_LOW);
//
//	               Gpt_StartTimer(GPT_16_32_BIT_TIMER_1 , 16000000);
//
//	               while((Gpt_GetTimeElapsed(GPT_16_32_BIT_TIMER_1)) != 0);
//
//
//
//	               Dio_WriteChannel(PORT_PF_1, STD_LOW);
//	               Dio_WriteChannel(PORT_PF_2, STD_HIGH);
//	               Dio_WriteChannel(PORT_PF_3, STD_LOW);
//	               Gpt_StartTimer(GPT_16_32_BIT_TIMER_1 , 16000000);
//
//	               while((Gpt_GetTimeElapsed(GPT_16_32_BIT_TIMER_1)) != 0);

//	    Wdg_SetTriggerCondition(1010);
//
//	    Dio_WriteChannel(PORT_PF_1, STD_HIGH);
//	    Dio_WriteChannel(PORT_PF_2, STD_LOW);
//	    Dio_WriteChannel(PORT_PF_3, STD_LOW);
//
//	    Gpt_StartTimer(GPT_32_64_BIT_WIDE_TIMER_0 , 16000000);
//
//	    while((Gpt_GetTimeElapsed(GPT_32_64_BIT_WIDE_TIMER_0)) != 0);
//
//	    Wdg_SetTriggerCondition(1100);
//
//	    Dio_WriteChannel(PORT_PF_1, STD_LOW);
//	    Dio_WriteChannel(PORT_PF_2, STD_HIGH);
//	    Dio_WriteChannel(PORT_PF_3, STD_LOW);
//	    Gpt_StartTimer(GPT_32_64_BIT_WIDE_TIMER_0 , 16000000);
//
//	    while((Gpt_GetTimeElapsed(GPT_32_64_BIT_WIDE_TIMER_0)) != 0);
//
//	    Wdg_SetTriggerCondition(1100);
//
//	    Dio_WriteChannel(PORT_PF_1, STD_LOW);
//	    Dio_WriteChannel(PORT_PF_2, STD_LOW);
//	    Dio_WriteChannel(PORT_PF_3, STD_HIGH);
//
//	    Gpt_StartTimer(GPT_32_64_BIT_WIDE_TIMER_0 , 16000000);
//
//	    while((Gpt_GetTimeElapsed(GPT_32_64_BIT_WIDE_TIMER_0)) != 0);

	}

}

void WD_Handler(void)
{
//    Dio_WriteChannel(PORT_PF_1, STD_LOW);
//    Dio_WriteChannel(PORT_PF_2, STD_LOW);
//    Dio_WriteChannel(PORT_PF_3, STD_HIGH);
//
//    Gpt_StartTimer(GPT_32_64_BIT_WIDE_TIMER_0 , 16000000);
//
//    while((Gpt_GetTimeElapsed(GPT_32_64_BIT_WIDE_TIMER_0)) != 0);
}

void gk_Handler(void)
{
    //Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_1US_24_BIT, &value);
////    (*(volatile uint32 *) (0x40031000 + 0x024)) = 1;
//    if(value == 0)
//    {
//    Dio_WriteChannel(PORT_PF_1, STD_HIGH);
//                      Dio_WriteChannel(PORT_PF_2, STD_HIGH);
//                      Dio_WriteChannel(PORT_PF_3, STD_HIGH);
//                      value++;
//    }
//    else
//    {
//        Dio_WriteChannel(PORT_PF_1, STD_LOW);
//                              Dio_WriteChannel(PORT_PF_2, STD_HIGH);
//                              Dio_WriteChannel(PORT_PF_3, STD_LOW);
//                              value = 0;
//    }

}
