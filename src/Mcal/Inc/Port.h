/*
 * Port.h
 *
 *  Created on: Jul 11, 2020
 *      Author: kh
 */

#ifndef PORT_H_
#define PORT_H_

/*____________________________________________________________________________________

        INCLUDES
_______________________________________________________________________________________*/
#include "Platform_Types.h"
#include "Std_Types.h"
#include "Bit_Math.h"

#include "PORT_ARM_REG.h"

/*Available Ports */
/*APB Bus*/
#define PORT_A_APB      0U   /*PORTA*/
#define PORT_B_APB      1U   /*PORTB*/
#define PORT_C_APB      2U   /*PORTC*/
#define PORT_D_APB      3U   /*PORTD*/
#define PORT_E_APB      4U   /*PORTE*/
#define PORT_F_APB      5U   /*PORTF*/
/*AHB Bus*/
#define PORT_A_AHB      6U   /*PORTA*/
#define PORT_B_AHB      7U   /*PORTB*/
#define PORT_C_AHB      8U   /*PORTC*/
#define PORT_D_AHB      9U   /*PORTD*/
#define PORT_E_AHB      10U  /*PORTE*/
#define PORT_F_AHB      11U  /*PORTF*/

/*APB PORTS                */

/*PORT A*/
#define PORT_PA_0  00U
#define PORT_PA_1  01U
#define PORT_PA_2  02U
#define PORT_PA_3  03U
#define PORT_PA_4  04U
#define PORT_PA_5  05U
#define PORT_PA_6  06U
#define PORT_PA_7  07U
/*PORT B*/
#define PORT_PB_0  10U
#define PORT_PB_1  11U
#define PORT_PB_2  12U
#define PORT_PB_3  13U
#define PORT_PB_4  14U
#define PORT_PB_5  15U
#define PORT_PB_6  16U
#define PORT_PB_7  17U
/*PORT C*/
#define PORT_PC_0  20U
#define PORT_PC_1  21U
#define PORT_PC_2  22U
#define PORT_PC_3  23U
#define PORT_PC_4  24U
#define PORT_PC_5  25U
#define PORT_PC_6  26U
#define PORT_PC_7  27U
/*PORT D*/
#define PORT_PD_0  30U
#define PORT_PD_1  31U
#define PORT_PD_2  32U
#define PORT_PD_3  33U
#define PORT_PD_4  34U
#define PORT_PD_5  35U
#define PORT_PD_6  36U
#define PORT_PD_7  37U
/*PORT E*/
#define PORT_PE_0  40U
#define PORT_PE_1  41U
#define PORT_PE_2  42U
#define PORT_PE_3  43U
#define PORT_PE_4  44U
/*PORT F*/
#define PORT_PF_0  50U
#define PORT_PF_1  51U
#define PORT_PF_2  52U
#define PORT_PF_3  53U
#define PORT_PF_4  54U

/*AHB PORTS                */

/*PORT A*/
#define PORT_PA_0_AHB  60U
#define PORT_PA_1_AHB  61U
#define PORT_PA_2_AHB  62U
#define PORT_PA_3_AHB  63U
#define PORT_PA_4_AHB  64U
#define PORT_PA_5_AHB  65U
#define PORT_PA_6_AHB  66U
#define PORT_PA_7_AHB  67U
/*PORT B*/
#define PORT_PB_0_AHB  70U
#define PORT_PB_1_AHB  71U
#define PORT_PB_2_AHB  72U
#define PORT_PB_3_AHB  73U
#define PORT_PB_4_AHB  74U
#define PORT_PB_5_AHB  75U
#define PORT_PB_6_AHB  76U
#define PORT_PB_7_AHB  77U
/*PORT C*/
#define PORT_PC_0_AHB  80U
#define PORT_PC_1_AHB  81U
#define PORT_PC_2_AHB  82U
#define PORT_PC_3_AHB  83U
#define PORT_PC_4_AHB  84U
#define PORT_PC_5_AHB  85U
#define PORT_PC_6_AHB  86U
#define PORT_PC_7_AHB  87U
/*PORT D*/
#define PORT_PD_0_AHB  90U
#define PORT_PD_1_AHB  91U
#define PORT_PD_2_AHB  92U
#define PORT_PD_3_AHB  93U
#define PORT_PD_4_AHB  94U
#define PORT_PD_5_AHB  95U
#define PORT_PD_6_AHB  96U
#define PORT_PD_7_AHB  97U
/*PORT E*/
#define PORT_PE_0_AHB  100U
#define PORT_PE_1_AHB  101U
#define PORT_PE_2_AHB  102U
#define PORT_PE_3_AHB  103U
#define PORT_PE_4_AHB  104U
/*PORT F*/
#define PORT_PF_0_AHB  110U
#define PORT_PF_1_AHB  111U
#define PORT_PF_2_AHB  112U
#define PORT_PF_3_AHB  113U
#define PORT_PF_4_AHB  114U

#define PORT_GPIO                               0

/*____________Port A_____________________________ */
/*PA0 Alternate Functions */
#define PORT_PA0_DIGITAL_U0Rx                   1
#define PORT_PA0_DIGITAL_CAN1Rx                 8
/*PA1 Alternate Functions */
#define PORT_PA1_DIGITAL_U0Tx                   1
#define PORT_PA1_DIGITAL_CAN1Tx                 8
/*PA2 Alternate Functions */
#define PORT_PA2_DIGITAL_SSI0Clk                2
/*PA3 Alternate Functions */
#define PORT_PA3_DIGITAL_SSI0Fss                2
/*PA4 Alternate Functions */
#define PORT_PA4_DIGITAL_SSI0Rx                 2
/*PA5 Alternate Functions */
#define PORT_PA5_DIGITAL_SSI0Tx                 2
/*PA6 Alternate Functions */
#define PORT_PA6_DIGITAL_I2C1SCL                3
#define PORT_PA6_DIGITAL_M1PWM2                 5
/*PA7 Alternate Functions */
#define PORT_PA7_DIGITAL_I2C1SDA                3
#define PORT_PA7_DIGITAL_M1PWM3                 5

/*____________Port B_____________________________ */
/*PB0 Alternate Functions */
#define PORT_PB0_ANALOG_USB0ID                  16
#define PORT_PB0_DIGITAL_U1Rx                   1
#define PORT_PB0_DIGITAL_T2CCP0                 7
/*PB1 Alternate Functions */
#define PORT_PB1_ANALOG_USB0VBUS                16
#define PORT_PB1_DIGITAL_U1Tx                   1
#define PORT_PB1_DIGITAL_T2CCP1                 7
/*PB2 Alternate Functions */
#define PORT_PB2_DIGITAL_I2C0SCL                3
#define PORT_PB2_DIGITAL_T3CCP0                 7
/*PB3 Alternate Functions */
#define PORT_PB3_DIGITAL_I2C0SDA                3
#define PORT_PB3_DIGITAL_T3CCP1                 7
/*PB4 Alternate Functions */
#define PORT_PB4_ANALOG_AIN10                   16
#define PORT_PB4_DIGITAL_SSI2Clk                2
#define PORT_PB4_DIGITAL_M0PWM2                 4
#define PORT_PB4_DIGITAL_T1CCP0                 7
#define PORT_PB4_DIGITAL_CAN0Rx                 8
/*PB5 Alternate Functions */
#define PORT_PB5_ANALOG_AIN11                   16
#define PORT_PB5_DIGITAL_SSI2Fss                2
#define PORT_PB5_DIGITAL_M0PWM3                 4
#define PORT_PB5_DIGITAL_T1CCP1                 7
#define PORT_PB5_DIGITAL_CAN0Tx                 8
/*PB6 Alternate Functions */
#define PORT_PB6_DIGITAL_SSI2Rx                 2
#define PORT_PB6_DIGITAL_M0PWM0                 4
#define PORT_PB6_DIGITAL_T0CCP0                 7
/*PB7 Alternate Functions */
#define PORT_PB7_DIGITAL_SSI2Tx                 2
#define PORT_PB7_DIGITAL_M0PWM1                 4
#define PORT_PB7_DIGITAL_T0CCP1                 7

/*____________Port C_____________________________ */
/*PC0 Alternate Functions */
#define PORT_PC0_DIGITAL_TCKSWCLK               1
#define PORT_PC0_DIGITAL_T4CCP0                 7
/*PC1 Alternate Functions */
#define PORT_PC1_DIGITAL_TMSSWDIO               1
#define PORT_PC1_DIGITAL_T4CCP1                 7
/*PC2 Alternate Functions */
#define PORT_PC2_DIGITAL_TDI                    1
#define PORT_PC2_DIGITAL_T5CCP0                 7
/*PC3 Alternate Functions */
#define PORT_PC3_DIGITAL_TDOSWO                 1
#define PORT_PC3_DIGITAL_T5CCP1                 7
/*PC4 Alternate Functions */
#define PORT_PC4_ANALOG_C1_NEG                  16
#define PORT_PC4_DIGITAL_U4Rx                   1
#define PORT_PC4_DIGITAL_U1Rx                   2
#define PORT_PC4_DIGITAL_M0PWM6                 4
#define PORT_PC4_DIGITAL_IDX1                   6
#define PORT_PC4_DIGITAL_WT0CCP0                7
#define PORT_PC4_DIGITAL_U1RTS                  8
/*PC5 Alternate Functions */
#define PORT_PC5_ANALOG_C1_POS                  16
#define PORT_PC5_DIGITAL_U4Tx                   1
#define PORT_PC5_DIGITAL_U1Tx                   2
#define PORT_PC5_DIGITAL_M0PWM7                 4
#define PORT_PC5_DIGITAL_PhA1                   6
#define PORT_PC5_DIGITAL_WT0CCP1                7
#define PORT_PC5_DIGITAL_U1CTS                  8
/*PC6 Alternate Functions */
#define PORT_PC6_ANALOG_C0_POS                  16
#define PORT_PC6_DIGITAL_U3Rx                   1
#define PORT_PC6_DIGITAL_PhB1                   6
#define PORT_PC6_DIGITAL_WT1CCP0                7
#define PORT_PC6_DIGITAL_USB0EPEN               8
/*PC7 Alternate Functions */
#define PORT_PC7_ANALOG_C0_NEG                  16
#define PORT_PC7_DIGITAL_U3Tx                   1
#define PORT_PC7_DIGITAL_WT1CCP1                7
#define PORT_PC7_DIGITAL_USB0PFLT               8

/*____________Port D_____________________________ */
/*PD0 Alternate Functions */
#define PORT_PD0_ANALOG_AIN7                    16
#define PORT_PD0_DIGITAL_SSI3Clk                1
#define PORT_PD0_DIGITAL_SSI1Clk                2
#define PORT_PD0_DIGITAL_I2C3SCL                3
#define PORT_PD0_DIGITAL_M0PWM6                 4
#define PORT_PD0_DIGITAL_M1PWM0                 5
#define PORT_PD0_DIGITAL_WT2CCP0                7
/*PD1 Alternate Functions */
#define PORT_PD1_ANALOG_AIN6                    16
#define PORT_PD1_DIGITAL_SSI3Fss                1
#define PORT_PD1_DIGITAL_SSI1Fss                2
#define PORT_PD1_DIGITAL_I2C3SDA                3
#define PORT_PD1_DIGITAL_M0PWM7                 4
#define PORT_PD1_DIGITAL_M1PWM1                 5
#define PORT_PD1_DIGITAL_WT2CCP1                7
/*PD2 Alternate Functions */
#define PORT_PD2_ANALOG_AIN5                    16
#define PORT_PD2_DIGITAL_SSI3Rx                 1
#define PORT_PD2_DIGITAL_SSI1Rx                 2
#define PORT_PD2_DIGITAL_M0FAULT0               4
#define PORT_PD2_DIGITAL_WT3CCP0                7
#define PORT_PD2_DIGITAL_USB0EPEN               8
/*PD3 Alternate Functions */
#define PORT_PD3_ANALOG_AIN4                    16
#define PORT_PD3_DIGITAL_SSI3Tx                 1
#define PORT_PD3_DIGITAL_SSI1Tx                 2
#define PORT_PD3_DIGITAL_IDX0                   6
#define PORT_PD3_DIGITAL_WT3CCP1                7
#define PORT_PD3_DIGITAL_USB0PFLT               8
/*PD4 Alternate Functions */
#define PORT_PD4_ANALOG_USB0DM                  16
#define PORT_PD4_DIGITAL_U6Rx                   1
#define PORT_PD4_DIGITAL_WT4CCP0                7
/*PD5 Alternate Functions */
#define PORT_PD5_ANALOG_USB0DP                  16
#define PORT_PD5_DIGITAL_U6Tx                   1
#define PORT_PD5_DIGITAL_WT4CCP1                7
/*PD6 Alternate Functions */
#define PORT_PD6_DIGITAL_U2Rx                   1
#define PORT_PD6_DIGITAL_M0FAULT0               4
#define PORT_PD6_DIGITAL_PhA0                   6
#define PORT_PD6_DIGITAL_WT5CCP0                7
/*PD7 Alternate Functions */
#define PORT_PD7_DIGITAL_U2Tx                   1
#define PORT_PD7_DIGITAL_PhB0                   6
#define PORT_PD7_DIGITAL_WT5CCP1                7
#define PORT_PD7_DIGITAL_NMI                    8

/*____________Port E_____________________________ */
/*PE0 Alternate Functions */
#define PORT_PE0_ANALOG_AIN3                    16
#define PORT_PE0_DIGITAL_U7Rx                   1
/*PE1 Alternate Functions */
#define PORT_PE1_ANALOG_AIN2                    16
#define PORT_PE1_DIGITAL_U7Tx                   1
/*PE2 Alternate Functions */
#define PORT_PE2_ANALOG_AIN1                    16
/*PE3 Alternate Functions */
#define PORT_PE3_ANALOG_AIN0                    16
/*PE4 Alternate Functions */
#define PORT_PE4_ANALOG_AIN9                    16
#define PORT_PE4_DIGITAL_U5Rx                   1
#define PORT_PE4_DIGITAL_I2C2SCL                3
#define PORT_PE4_DIGITALM0PWM4                  4
#define PORT_PE4_DIGITAL_M1PWM2                 5
#define PORT_PE4_DIGITAL_CAN0Rx                 8
/*PE5 Alternate Functions */
#define PORT_PE5_ANALOG_AIN8                    16
#define PORT_PE5_DIGITAL_U5Tx                   1
#define PORT_PE5_DIGITAL_I2C2SDA                3
#define PORT_PE5_DIGITAL_M0PWM5                 4
#define PORT_PE5_DIGITAL_M1PWM3                 5
#define PORT_PE5_DIGITAL_CAN0Tx                 8

/*____________Port F_____________________________ */
/*PF0 Alternate Functions */
#define PORT_PF0_DIGITAL_U1RTS                  1
#define PORT_PF0_DIGITAL_SSI1Rx                 2
#define PORT_PF0_DIGITAL_CAN0Rx                 3
#define PORT_PF0_DIGITAL_M1PWM4                 5
#define PORT_PF0_DIGITAL_PhA0                   6
#define PORT_PF0_DIGITAL_T0CCP0                 7
#define PORT_PF0_DIGITAL_NMI                    8
#define PORT_PF0_DIGITAL_C0o                    9
/*PF1 Alternate Functions */
#define PORT_PF1_DIGITAL_U1CTS                  1
#define PORT_PF1_DIGITAL_SSI1Tx                 2
#define PORT_PF1_DIGITAL_M1PWM5                 5
#define PORT_PF1_DIGITAL_PhB0                   6
#define PORT_PF1_DIGITAL_T0CCP1                 7
#define PORT_PF1_DIGITAL_C1o                    9
#define PORT_PF1_DIGITAL_TRD1                   14
/*PF2 Alternate Functions */
#define PORT_PF1_DIGITAL_SSI1Clk                2
#define PORT_PF1_DIGITAL_M0FAULT0               4
#define PORT_PF1_DIGITAL_M1PWM6                 5
#define PORT_PF1_DIGITAL_T1CCP0                 7
#define PORT_PF1_DIGITAL_TRD0                   14
/*PF3 Alternate Functions */
#define PORT_PF4_DIGITAL_SSI1Fss                2
#define PORT_PF4_DIGITAL_CAN0Tx                 3
#define PORT_PF4_DIGITAL_M1PWM7                 5
#define PORT_PF4_DIGITAL_T1CCP1                 7
#define PORT_PF4_DIGITAL_TRCLK                  14
/*PF4 Alternate Functions */
#define PORT_PF4_DIGITAL_M1FAULT0               5
#define PORT_PF4_DIGITAL_IDX0                   6
#define PORT_PF4_DIGITAL_T2CCP0                 7
#define PORT_PF4_DIGITAL_USB0EPEN               8







typedef uint8 Port_PinType ;                    /*Shall cover all available port pins*/

typedef enum                                    /*PORT_PIN_IN / PORT_PIN_OUT*/
{
    PORT_PIN_IN ,

    PORT_PIN_OUT

}Port_PinDirectionType;


typedef uint8 Port_PinModeType ;                /*As several port pin modes shall be configurable on one pin, the range shall be determined by the implementation. */

typedef enum
{
    PORT_PULL_UP ,
    PORT_PULL_DOWN ,
    PORT_OPEN_DRAIN ,
    PORT_FLOATING_PIN
}Port_PinInternalAttachType;

typedef enum
{
    PORT_2_mA ,
    PORT_4_mA ,
    PORT_8_mA

}Port_PinOutputCurrentType;


typedef struct
{
    Port_PinType Pin_Type ;

    Port_PinDirectionType Pin_Direction ;

    Port_PinModeType  Pin_Mode ;

    Port_PinInternalAttachType Pin_AttachType ;

    Port_PinOutputCurrentType  Pin_CurruntType ;

}Port_ConfigType;
/******************************************************************************
* \Syntax          : void Port_Init(const Port_ConfigType * ConfigPtr)
* \Description     : Init Port
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : const Port_ConfigType * ConfigPtr
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr);

#endif /* PORT_H_ */
