/*
 * WDT_ARM_REG.h
 *
 *  Created on: Jul 31, 2020
 *      Author: kh
 */

#ifndef WDT_ARM_REG_H_
#define WDT_ARM_REG_H_

#define WDG_PRIVATE_PRI_BASE_ADD                    0x40000000
#define WDG_PRIVATE_PRI_BASE_ALIAS                0x42000000

#define WDG_1_BASE_ADDRESS          0x40001000
#define WDG_0_BASE_ADDRESS          0x40000000

#define WDG_LOAD_OFFSET             0x000

#define WDG_CTL_OFFSET              0x008

#define WDG_WRC_BIT                 31
#define WDG_RESET_ENABLE_BIT        1

#define WDG_INTERRUPT_ENABLE_BIT    0

#define WDG_INTERRUPT_TYPE_BIT      2

#endif /* WDT_ARM_REG_H_ */
