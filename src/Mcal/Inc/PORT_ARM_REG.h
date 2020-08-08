/*
 * PORT_ARM_REG.h
 *
 *  Created on: Jul 23, 2020
 *      Author: kh
 */

#ifndef PORT_ARM_REG_H_
#define PORT_ARM_REG_H_

#define PORT_PRIVATE_PRI_BASE_ADD                    0x40000000
#define PORT_PRIVATE_PRI_BASE_ALIAS                0x42000000

#define GPIO_PORT_A_APB_BASE         0x40004000
#define GPIO_PORT_A_AHB_BASE         0x40058000
#define GPIO_PORT_B_APB_BASE         0x40005000
#define GPIO_PORT_B_AHB_BASE         0x40059000
#define GPIO_PORT_C_APB_BASE         0x40006000
#define GPIO_PORT_C_AHB_BASE         0x4005A000
#define GPIO_PORT_D_APB_BASE         0x40007000
#define GPIO_PORT_D_AHB_BASE         0x4005B000
#define GPIO_PORT_E_APB_BASE         0x40024000
#define GPIO_PORT_E_AHB_BASE         0x4005C000
#define GPIO_PORT_F_APB_BASE         0x40025000
#define GPIO_PORT_F_AHB_BASE         0x4005D000



#define PORT_DIRECTION_OFFSET                   0x400
#define PORT_ALTERNATE_FUNCTION_SELECT_OFFSET   0x420
#define PORT_CONTROL_OFFSET                     0x52C

#define PORT_CONTROL_START_BIT(PORT_PIN)        0 + (PORT_PIN * 4)
#define PORT_CONTROL_END_BIT(PORT_PIN)          3 + (PORT_PIN * 4)

#define PORT_CURRENT_2_mA_OFFSET                0x500
#define PORT_CURRENT_4_mA_OFFSET                0x504
#define PORT_CURRENT_8_mA_OFFSET                0x508

#define PORT_LOCK_OFFSET                        0x520
#define PORT_COMMIT_OFFSET                      0x524

#define PORT_INTERNAL_OPEN_DRAIN_OFFSET         0x50C
#define PORT_INTERNAL_PULL_UP_OFFSET            0x510
#define PORT_INTERNAL_PULL_DOWN_OFFSET          0x514

#define PORT_DIGITAL_ENABLE_OFFSET              0x51C
#define PORT_ANALOG_ENABLE_OFFSET               0x528

#endif /* PORT_ARM_REG_H_ */
