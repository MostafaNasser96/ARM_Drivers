/*
 * GPT_ARM_REG.h
 *
 *  Created on: Jul 13, 2020
 *      Author: kh
 */

#ifndef GPT_ARM_REG_H_
#define GPT_ARM_REG_H_

#define GPT_PRIVATE_PRI_BASE_ALIAS                  0x42000000

#define GPT_PRIVATE_PRI_BASE_ADD                    0x40000000



#define GPT_16_32_BIT_TIMER_0_BASE                  0x40030000
#define GPT_16_32_BIT_TIMER_1_BASE                  0x40031000
#define GPT_16_32_BIT_TIMER_2_BASE                  0x40032000
#define GPT_16_32_BIT_TIMER_3_BASE                  0x40033000
#define GPT_16_32_BIT_TIMER_4_BASE                  0x40034000
#define GPT_16_32_BIT_TIMER_5_BASE                  0x40035000
#define GPT_32_64_BIT_WIDE_TIMER_0_BASE             0x40036000
#define GPT_32_64_BIT_WIDE_TIMER_1_BASE             0x40037000
#define GPT_32_64_BIT_WIDE_TIMER_2_BASE             0x4004C000
#define GPT_32_64_BIT_WIDE_TIMER_3_BASE             0x4004D000
#define GPT_32_64_BIT_WIDE_TIMER_4_BASE             0x4004E000
#define GPT_32_64_BIT_WIDE_TIMER_5_BASE             0x4004F000

#define GPT_CONTROL_OFFSET                          0x0000000C
/*________________________*/
#define GPT_CONTROL_EN_A    0
#define GPT_CONTROL_EN_B    8

#define GPT_CFG_OFFSET                              0x00000000
/*________________________*/
#define GPT_CFG_START                               0
#define GPT_CFG_END                                 2

#define GPT_TIMER_A_MODE_OFFSET                     0x00000004

#define GPT_TIMER_B_MODE_OFFSET                     0x00000008
/*________________________*/
#define GPT_MODE_COUNT_DIRECTION                    4
#define GPT_TIMER_MODE_START                        0
#define GPT_TIMER_MODE_END                          1

#define GPT_TIMER_A_INTERVAL_LOAD_OFFSET            0x00000028

#define GPT_TIMER_B_INTERVAL_LOAD_OFFSET            0x0000002C

#define GPT_INTERRUPT_MASK_OFFSET                   0x00000018
/*______________________________*/
#define GPT_INTERRUPT_A_TIME_OUT                    0
#define GPT_INTERRUPT_B_TIME_OUT                    8


#define GPT_RAW_INTERRUPT_STATUS_OFFSET             0x0000001C
#define GPT_MASKED_INTERRUPT_STATUS_OFFSET          0x00000020
#define GPT_INTERRUPT_CLEAR_OFFSET                  0x00000024
/*_______________________________*/

#define GPT_INTERRUPT_TIMER_A_TIME_OUT              0
#define GPT_INTERRUPT_TIMER_B_TIME_OUT              8

#define GPT_TIMER_A_PRESCALLER_OFFSET               0x00000038

#define GPT_TIMER_A_VALUE_OFFSET                    0x00000050

#define GPT_TIMER_B_VALUE_OFFSET                    0x00000054

#define GPT_TIMER_A_PRESCALLER_VALUE_OFFSET         0x00000064

#define GPT_CLEAR_INTERRUPT_OFFSET                  0x024

#define GPT_INTERRUPT_A_BIT                         0



#endif /* GPT_ARM_REG_H_ */
