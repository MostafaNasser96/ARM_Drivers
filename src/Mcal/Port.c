/*
 * Port.c
 *
 *  Created on: Jul 11, 2020
 *      Author: Mostafa
 */
#include "Port.h"

/*________________MACROS______________________________________________________________________________________________________*/
#define PORT_DIV                        10            /*To Determine PORT Name and PORT Pin*/

#define ANALOG_ENABLE                   16            /*Analog Function of Pin as Digital Alternate Function between 1 and 15*/
#define DIGITAL_ENABLE_MIN              1             /*Minimum Number of Alternate Digital Function*/
#define DIGITAL_ENABLE_MAX              15            /*Maximum Number of Alternate Digital function*/

#define PORT_LOCKED                     1             /*Lock PORT */
#define PORT_UNLOCKED                   0x4C4F434B    /*Pattern to unlock PORT*/

#define PORT_ENABLE_COMMIT              1             /*Commit PORT*/

#define MODE_FOUND                      1             /*If MODE (ANALOG or DIGITAL) found for the specific PIN */
#define MODE_NOT_FOUND                  0             /*NOT FOUND*/

#define NUMBER_OF_PINS                  43            /*Number of PINS Available*/
#define NUMBER_OF_ALTERNATE_FUNCTIONS   16            /*Number of Alternate Functions*/

#define PORT_ADDRESS(Base , Offset )    (*((volatile uint32 * ) (Base + Offset))) /*Get Address*/
/*_____________________________________________________________________________________________________________________________*/

/*____________GLOBAL VARIABLES_________________________________________________________________________________________________*/
static uint8 g_InitCheck = E_OK ;

static uint8 g_PORT_AvailableModesArr[NUMBER_OF_PINS][NUMBER_OF_ALTERNATE_FUNCTIONS] = {  /*Available Modes for Each PIN*/
 /*_________________________________________________________________________________________________________________________________________________________________________________*/
/*0 Analog Mode */           /*from 1 to 15 Digital Mode */
/*__________________________________________________________________________________________________________________________________________________________________________________*/
{     0                     ,PORT_PA0_DIGITAL_U0Rx , 0 , 0 , 0 , 0 , 0 , 0 , PORT_PA0_DIGITAL_CAN1Rx , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     ,PORT_PA1_DIGITAL_U0Tx , 0 , 0 , 0 , 0 , 0 , 0 , PORT_PA1_DIGITAL_CAN1Tx , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     , 0 , PORT_PA2_DIGITAL_SSI0Clk , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     , 0 , PORT_PA3_DIGITAL_SSI0Fss , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     , 0 , PORT_PA4_DIGITAL_SSI0Rx , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     , 0 , PORT_PA5_DIGITAL_SSI0Tx , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     , 0 , 0 , PORT_PA6_DIGITAL_I2C1SCL , 0 , PORT_PA6_DIGITAL_M1PWM2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     , 0 , 0 , PORT_PA7_DIGITAL_I2C1SDA , 0 , PORT_PA7_DIGITAL_M1PWM3 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PB0_ANALOG_USB0ID    , PORT_PB0_DIGITAL_U1Rx , 0 , 0 , 0 , 0 , 0 , PORT_PB0_DIGITAL_T2CCP0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PB1_ANALOG_USB0VBUS  , PORT_PB1_DIGITAL_U1Tx , 0 , 0 , 0 , 0 , 0 , PORT_PB1_DIGITAL_T2CCP1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     , 0 , 0 , PORT_PB2_DIGITAL_I2C0SCL , 0 , 0 , 0 , PORT_PB2_DIGITAL_T3CCP0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     , 0 , 0 , PORT_PB3_DIGITAL_I2C0SDA , 0 , 0 , 0 , PORT_PB3_DIGITAL_T3CCP1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PB4_ANALOG_AIN10     , 0 , PORT_PB4_DIGITAL_SSI2Clk , 0 , PORT_PB4_DIGITAL_M0PWM2 , 0 , 0 , PORT_PB4_DIGITAL_T1CCP0 , PORT_PB4_DIGITAL_CAN0Rx , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PB5_ANALOG_AIN11     , 0 , PORT_PB5_DIGITAL_SSI2Fss , 0 , PORT_PB5_DIGITAL_M0PWM3 , 0 , 0 , PORT_PB5_DIGITAL_T1CCP1 , PORT_PB5_DIGITAL_CAN0Tx , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     , 0 , PORT_PB6_DIGITAL_SSI2Rx , 0 , PORT_PB6_DIGITAL_M0PWM0 , 0 , 0 , PORT_PB6_DIGITAL_T0CCP0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     , 0 , PORT_PB7_DIGITAL_SSI2Tx , 0 , PORT_PB7_DIGITAL_M0PWM1 , 0 , 0 , PORT_PB7_DIGITAL_T0CCP1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     ,PORT_PC0_DIGITAL_TCKSWCLK , 0 , 0 , 0 , 0 , 0 , PORT_PC0_DIGITAL_T4CCP0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     ,PORT_PC1_DIGITAL_TMSSWDIO , 0 , 0 , 0 , 0 , 0 , PORT_PC1_DIGITAL_T4CCP1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     ,PORT_PC2_DIGITAL_TDI , 0 , 0 , 0 , 0 , 0 , PORT_PC2_DIGITAL_T5CCP0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     ,PORT_PC3_DIGITAL_TDOSWO , 0 , 0 , 0 , 0 , 0 , PORT_PC3_DIGITAL_T5CCP1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PC4_ANALOG_C1_NEG    ,PORT_PC4_DIGITAL_U4Rx , PORT_PC4_DIGITAL_U1Rx , 0 , PORT_PC4_DIGITAL_M0PWM6 , 0 , PORT_PC4_DIGITAL_IDX1 , PORT_PC4_DIGITAL_WT0CCP0 , PORT_PC4_DIGITAL_U1RTS , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PC5_ANALOG_C1_POS    ,PORT_PC5_DIGITAL_U4Tx , PORT_PC5_DIGITAL_U1Tx , 0 , PORT_PC5_DIGITAL_M0PWM7 , 0 , PORT_PC5_DIGITAL_PhA1 , PORT_PC5_DIGITAL_WT0CCP1 , PORT_PC5_DIGITAL_U1CTS , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PC6_ANALOG_C0_POS    ,PORT_PC6_DIGITAL_U3Rx , 0 , 0 , 0 , 0 , PORT_PC6_DIGITAL_PhB1 , PORT_PC6_DIGITAL_WT1CCP0 , PORT_PC6_DIGITAL_USB0EPEN , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PC7_ANALOG_C0_NEG    ,PORT_PC7_DIGITAL_U3Tx , 0 , 0 , 0 , 0 , 0 , PORT_PC7_DIGITAL_WT1CCP1 , PORT_PC7_DIGITAL_USB0PFLT , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PD0_ANALOG_AIN7      ,PORT_PD0_DIGITAL_SSI3Clk , PORT_PD0_DIGITAL_SSI1Clk , PORT_PD0_DIGITAL_I2C3SCL , PORT_PD0_DIGITAL_M0PWM6 , PORT_PD0_DIGITAL_M1PWM0 , 0 , PORT_PD0_DIGITAL_WT2CCP0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PD1_ANALOG_AIN6      ,PORT_PD1_DIGITAL_SSI3Fss , PORT_PD1_DIGITAL_SSI1Fss , PORT_PD1_DIGITAL_I2C3SDA , PORT_PD1_DIGITAL_M0PWM7 , PORT_PD1_DIGITAL_M1PWM1 , 0 , PORT_PD1_DIGITAL_WT2CCP1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PD2_ANALOG_AIN5      ,PORT_PD2_DIGITAL_SSI3Rx , PORT_PD2_DIGITAL_SSI1Rx , 0 , PORT_PD2_DIGITAL_M0FAULT0 , 0 , 0 , PORT_PD2_DIGITAL_WT3CCP0 , PORT_PD2_DIGITAL_USB0EPEN , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PD3_ANALOG_AIN4      ,PORT_PD3_DIGITAL_SSI3Tx , PORT_PD3_DIGITAL_SSI1Tx , 0 , 0 , 0 , PORT_PD3_DIGITAL_IDX0 , PORT_PD3_DIGITAL_WT3CCP1 , PORT_PD3_DIGITAL_USB0PFLT , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PD4_ANALOG_USB0DM    ,PORT_PD4_DIGITAL_U6Rx , 0 , 0 , 0 , 0 , 0 , PORT_PD4_DIGITAL_WT4CCP0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PD5_ANALOG_USB0DP    ,PORT_PD5_DIGITAL_U6Tx , 0 , 0 , 0 , 0 , 0 , PORT_PD5_DIGITAL_WT4CCP1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     ,PORT_PD6_DIGITAL_U2Rx , 0 , 0 , PORT_PD6_DIGITAL_M0FAULT0 , 0 , PORT_PD6_DIGITAL_PhA0 , PORT_PD6_DIGITAL_WT5CCP0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     ,PORT_PD7_DIGITAL_U2Tx , 0 , 0 , 0 , 0 , PORT_PD7_DIGITAL_PhB0 , PORT_PD7_DIGITAL_WT5CCP1 , PORT_PD7_DIGITAL_NMI , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PE0_ANALOG_AIN3      ,PORT_PE0_DIGITAL_U7Rx , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PE1_ANALOG_AIN2      ,PORT_PE1_DIGITAL_U7Tx , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PE2_ANALOG_AIN1      ,0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PE3_ANALOG_AIN0      ,0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PE4_ANALOG_AIN9      ,PORT_PE4_DIGITAL_U5Rx , 0 , PORT_PE4_DIGITAL_I2C2SCL , PORT_PE4_DIGITALM0PWM4 , PORT_PE4_DIGITAL_M1PWM2 , 0 , 0 , PORT_PE4_DIGITAL_CAN0Rx , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{ PORT_PE5_ANALOG_AIN8      ,PORT_PE5_DIGITAL_U5Tx , 0 , PORT_PE5_DIGITAL_I2C2SDA , PORT_PE5_DIGITAL_M0PWM5 , PORT_PE5_DIGITAL_M1PWM3 , 0 , 0 , PORT_PE5_DIGITAL_CAN0Tx , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     ,PORT_PF0_DIGITAL_U1RTS , PORT_PF0_DIGITAL_SSI1Rx , PORT_PF0_DIGITAL_CAN0Rx , 0 , PORT_PF0_DIGITAL_M1PWM4 , PORT_PF0_DIGITAL_PhA0 , PORT_PF0_DIGITAL_T0CCP0 , PORT_PF0_DIGITAL_NMI , PORT_PF0_DIGITAL_C0o , 0 , 0 , 0 , 0 , 0 , 0 },
{     0                     ,PORT_PF1_DIGITAL_U1CTS , PORT_PF1_DIGITAL_SSI1Tx , 0 , 0 , PORT_PF1_DIGITAL_M1PWM5 , PORT_PF1_DIGITAL_PhB0 , PORT_PF1_DIGITAL_T0CCP1 , 0 , PORT_PF1_DIGITAL_C1o , 0 , 0 , 0 , 0 , PORT_PF1_DIGITAL_TRD1 , 0 },
{     0                     ,0 , PORT_PF1_DIGITAL_SSI1Clk , 0 , PORT_PF1_DIGITAL_M0FAULT0 , PORT_PF1_DIGITAL_M1PWM6 , 0 , PORT_PF1_DIGITAL_T1CCP0 , 0 , 0 , 0 , 0 , 0 , 0 , PORT_PF1_DIGITAL_TRD0 , 0 },
{     0                     ,0 , PORT_PF4_DIGITAL_SSI1Fss , PORT_PF4_DIGITAL_CAN0Tx , 0 , PORT_PF4_DIGITAL_M1PWM7 , 0 , PORT_PF4_DIGITAL_T1CCP1 , 0 , 0 , 0 , 0 , 0 , 0 , PORT_PF4_DIGITAL_TRCLK , 0 },
{     0                     ,0 , 0 , 0 , 0 , PORT_PF4_DIGITAL_M1FAULT0 , PORT_PF4_DIGITAL_IDX0 , PORT_PF4_DIGITAL_T2CCP0 , PORT_PF4_DIGITAL_USB0EPEN , 0 , 0 , 0 , 0 , 0 , 0 , 0 }
};
/*_____________________________________________________________________________________________________________________________*/

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
void Port_Init(const Port_ConfigType * ConfigPtr)
{
    uint8 Bit_BandStart , Bit_BandEnd , ModeFind = MODE_NOT_FOUND , loop ;
    uint32 Base_Address ;

    if(ConfigPtr->Pin_Mode == PORT_GPIO) /*If Mode of PIN is GPIO*/
    {
        ModeFind = MODE_FOUND ; /*Mode Found as GPIO is Available for all the PINS*/
    }
    else
    {
        for ( loop = 0 ; loop < NUMBER_OF_ALTERNATE_FUNCTIONS ; loop++)
        {
            if(g_PORT_AvailableModesArr[ConfigPtr->Pin_Type][loop] == ConfigPtr->Pin_Mode) /*search if Chosen Mode is Available for Thie PIN*/
            {
                ModeFind = MODE_FOUND ;
                loop = NUMBER_OF_ALTERNATE_FUNCTIONS ; /*To Exit The Loop*/
            }
        }
    }

    if(ModeFind == MODE_FOUND) /*If Mode is Found*/
    {
        /*2. Set the direction of the GPIO port pins by programming the GPIODIR register. A write of a '1' indicates output and a write of a '0' indicates input.*/
        if(ConfigPtr->Pin_Type / PORT_DIV == PORT_A_APB)
        {
            Base_Address = GPIO_PORT_A_APB_BASE ;  /*Base Address of PORTA in APB*/
        }
        else if(ConfigPtr->Pin_Type / PORT_DIV == PORT_B_APB)
        {
            Base_Address = GPIO_PORT_B_APB_BASE ;  /*Base Address of PORTB in APB*/
        }
        else if(ConfigPtr->Pin_Type / PORT_DIV == PORT_C_APB)
        {
            Base_Address = GPIO_PORT_C_APB_BASE ;  /*Base Address of PORTC in APB*/
        }
        else if(ConfigPtr->Pin_Type / PORT_DIV == PORT_D_APB)
        {
            Base_Address = GPIO_PORT_D_APB_BASE ;  /*Base Address of PORTD in APB*/
        }
        else if(ConfigPtr->Pin_Type / PORT_DIV == PORT_E_APB)
        {
            Base_Address = GPIO_PORT_E_APB_BASE ;  /*Base Address of PORTE in APB*/
        }
        else if(ConfigPtr->Pin_Type / PORT_DIV == PORT_F_APB)
        {
            Base_Address = GPIO_PORT_F_APB_BASE ;  /*Base Address of PORTF in APB*/
        }
        else if(ConfigPtr->Pin_Type / PORT_DIV == PORT_A_AHB)
        {
            Base_Address = GPIO_PORT_A_AHB_BASE ;  /*Base Address of PORTA in AHB*/
        }
        else if(ConfigPtr->Pin_Type / PORT_DIV == PORT_B_AHB)
        {
            Base_Address = GPIO_PORT_B_AHB_BASE ;  /*Base Address of PORTB in AHB*/
        }
        else if(ConfigPtr->Pin_Type / PORT_DIV == PORT_C_AHB)
        {
            Base_Address = GPIO_PORT_C_AHB_BASE ;  /*Base Address of PORTC in AHB*/
        }
        else if(ConfigPtr->Pin_Type / PORT_DIV == PORT_D_AHB)
        {
            Base_Address = GPIO_PORT_D_AHB_BASE ;  /*Base Address of PORTD in AHB*/
        }
        else if(ConfigPtr->Pin_Type / PORT_DIV == PORT_E_AHB)
        {
            Base_Address = GPIO_PORT_E_AHB_BASE ;  /*Base Address of PORTE in AHB*/
        }
        else if(ConfigPtr->Pin_Type / PORT_DIV == PORT_F_AHB)
        {
            Base_Address = GPIO_PORT_F_AHB_BASE ; /*Base Address of PORTF in AHB*/
        }
        else
        {
            g_InitCheck = E_NOT_OK;  /*The Module is Not Initialized in Correct Way*/
        }

        if(g_InitCheck == E_OK)
        {

            BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_DIRECTION_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,ConfigPtr->Pin_Direction);    /*Set pin Input/Output*/

            PORT_ADDRESS(Base_Address , PORT_LOCK_OFFSET) = PORT_UNLOCKED ; /*Unlock PORT*/

            BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_COMMIT_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,PORT_ENABLE_COMMIT); /*Enable Commit*/

            /*3. Configure the GPIOAFSEL register to program each bit as a GPIO or alternate pin. If an alternate pin is chosen for a bit, then the PMCx field must be programmed in the GPIOPCTL register for
                 the specific peripheral required. */
            if(ConfigPtr->Pin_Mode == PORT_GPIO )
            {
                BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_ALTERNATE_FUNCTION_SELECT_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW);    /*Set pin GPIO*/
            }
            else
            {
                BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_ALTERNATE_FUNCTION_SELECT_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_HIGH);    /*Set pin Alternate Function*/

                Bit_BandStart = PORT_CONTROL_START_BIT(ConfigPtr->Pin_Type) ;
                Bit_BandEnd   = PORT_CONTROL_END_BIT(ConfigPtr->Pin_Type);

                BIT_GROUP_BANDING(PORT_PRIVATE_PRI_BASE_ADD , PORT_PRIVATE_PRI_BASE_ALIAS , Base_Address , PORT_CONTROL_OFFSET , Bit_BandStart , Bit_BandEnd , ConfigPtr->Pin_Mode); /*Set The Chosen Alternate Function*/
            }

            /*4. Set the drive strength for each of the pins through the GPIODR2R, GPIODR4R, and GPIODR8R registers. */
            if(ConfigPtr->Pin_CurruntType == PORT_2_mA)
            {
                BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_CURRENT_8_mA_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW);  /*Disable 8mA*/
                BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_CURRENT_4_mA_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW);  /*Disable 4mA*/
                BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_CURRENT_2_mA_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_HIGH); /*Enable 2mA*/
            }
            else if(ConfigPtr->Pin_CurruntType == PORT_4_mA)
            {
                BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_CURRENT_8_mA_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW); /*Disable 8mA*/
                BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_CURRENT_2_mA_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW); /*Disable 2mA*/
                BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_CURRENT_4_mA_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_HIGH); /*Enable 4mA*/

            }
            else if(ConfigPtr->Pin_CurruntType == PORT_8_mA)
            {
                BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_CURRENT_2_mA_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW); /*Disable 2mA*/
                BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_CURRENT_4_mA_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW); /*Disable 4mA*/
                BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_CURRENT_8_mA_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_HIGH); /*Enable 8mA*/
            }
            else
            {
                g_InitCheck = E_NOT_OK ;
            }
            /*5. Program each pad in the port to have either pull-up, pull-down, or open drain functionality through the GPIOPUR, GPIOPDR, GPIOODR register. Slew rate may also be programmed, if needed,
                through the GPIOSLR register.*/
            if(g_InitCheck == E_OK)
            {
                if(ConfigPtr->Pin_AttachType == PORT_OPEN_DRAIN)
                {
                    BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_INTERNAL_PULL_UP_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW);
                    BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_INTERNAL_PULL_DOWN_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW);
                    PORT_ADDRESS(Base_Address , PORT_LOCK_OFFSET) = PORT_UNLOCKED ;  /*Unlock PORT*/
                    BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_INTERNAL_OPEN_DRAIN_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_HIGH);
                }
                else if(ConfigPtr->Pin_AttachType == PORT_PULL_UP)
                {
                    BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_INTERNAL_OPEN_DRAIN_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW);
                    BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_INTERNAL_PULL_DOWN_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW);
                    PORT_ADDRESS(Base_Address , PORT_LOCK_OFFSET) = PORT_UNLOCKED ;  /*Unlock PORT*/
                    BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_INTERNAL_PULL_UP_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_HIGH);
                }
                else if(ConfigPtr->Pin_AttachType == PORT_PULL_DOWN)
                {
                    BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_INTERNAL_OPEN_DRAIN_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW);
                    BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_INTERNAL_PULL_UP_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW);
                    PORT_ADDRESS(Base_Address , PORT_LOCK_OFFSET) = PORT_UNLOCKED ;  /*Unlock PORT*/
                    BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_INTERNAL_PULL_DOWN_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_HIGH);
                }
                else if(ConfigPtr->Pin_AttachType == PORT_FLOATING_PIN)
                {

                }
                else
                {
                    g_InitCheck = E_NOT_OK ;
                }

                /*6. To enable GPIO pins as digital I/Os, set the appropriate DEN bit in the GPIODEN register. To enable GPIO pins to their analog function (if available),
                 * set the GPIOAMSEL bit in the GPIOAMSEL register.*/
                if(g_InitCheck == E_OK)
                {
                    if(ConfigPtr->Pin_Mode == PORT_GPIO) /*In Case GPIO*/
                    {
                        BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_ANALOG_ENABLE_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW);
                        PORT_ADDRESS(Base_Address , PORT_LOCK_OFFSET) = PORT_UNLOCKED ;
                        BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_DIGITAL_ENABLE_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_HIGH);
                    }
                    else if(ConfigPtr->Pin_Mode >= DIGITAL_ENABLE_MIN && ConfigPtr->Pin_Mode <= DIGITAL_ENABLE_MAX ) /*In Case Digital Function*/
                    {
                        BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_ANALOG_ENABLE_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW);
                        PORT_ADDRESS(Base_Address , PORT_LOCK_OFFSET) = PORT_UNLOCKED ;
                        BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_DIGITAL_ENABLE_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_HIGH);
                    }
                    else if(ConfigPtr->Pin_Mode == ANALOG_ENABLE) /*In Case Analog Function*/
                    {
                        BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_DIGITAL_ENABLE_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_LOW);
                        PORT_ADDRESS(Base_Address , PORT_LOCK_OFFSET) = PORT_UNLOCKED ;
                        BIT_BANDING(PORT_PRIVATE_PRI_BASE_ADD, PORT_PRIVATE_PRI_BASE_ALIAS, Base_Address, PORT_ANALOG_ENABLE_OFFSET , (ConfigPtr->Pin_Type % PORT_DIV) ,STD_HIGH);
                    }
                    else
                    {
                        g_InitCheck = E_NOT_OK;
                    }

                        PORT_ADDRESS(Base_Address , PORT_LOCK_OFFSET) = PORT_LOCKED ; /*Lock PORT*/
                }
            }
        }
    }
    else
    {
        g_InitCheck = E_NOT_OK;
    }
}

