/**
  ******************************************************************************
  * @file    CW030xx_gpio.c
  * @author WHXY
  * @version
  * @date    2021-03-16
  * @brief   GPIO HAL module driver.
  *         This file provides firmware functions to manage the following
  *          functionalities of the General Purpose Input/Output (GPIO) peripheral:
  *           + Initialization and de-initialization functions
  *           + IO operation functions
  *
***/


/* Includes ------------------------------------------------------------------*/
#include "cw32f030_gpio.h"



//=============================================================================
//GPIO 初始化，多个引脚
/**
 * @brief GPIO 初始化，可同时设置多个引脚或单个引脚
 *
 * @param GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC CW_GPIOF
 * @param GPIO_Init 参见GPIO_InitTypeDef的定义
 */
void GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    if (GPIO_Init->Mode == GPIO_MODE_ANALOG)                         //模拟功能
    {
        REGBITS_SET(GPIOx->ANALOG, GPIO_Init->Pins);
    }
    else
    {
        REGBITS_CLR(GPIOx->ANALOG, GPIO_Init->Pins);                  //数字功能
        if ((GPIO_Init->Mode & GPIO_MODE_INPUT) == GPIO_MODE_INPUT)   //输入模式
        {
            REGBITS_SET(GPIOx->DIR, GPIO_Init->Pins);
            if (GPIO_Init->Mode == GPIO_MODE_INPUT_PULLUP)
            {
                REGBITS_SET(GPIOx->PUR, GPIO_Init->Pins);
                REGBITS_CLR(GPIOx->PDR, GPIO_Init->Pins);
            }
            if (GPIO_Init->Mode == GPIO_MODE_INPUT_PULLDOWN)
            {
                REGBITS_SET(GPIOx->PDR, GPIO_Init->Pins);
                REGBITS_CLR(GPIOx->PUR, GPIO_Init->Pins);
            }
            REGBITS_CLR(GPIOx->RISEIE, GPIO_Init->Pins);
            REGBITS_CLR(GPIOx->FALLIE, GPIO_Init->Pins);
            REGBITS_CLR(GPIOx->HIGHIE, GPIO_Init->Pins);
            REGBITS_CLR(GPIOx->LOWIE, GPIO_Init->Pins);
            if ((GPIO_Init->IT & GPIO_IT_RISING) == GPIO_IT_RISING)
            {
                REGBITS_SET(GPIOx->RISEIE, GPIO_Init->Pins);
            }
            if ((GPIO_Init->IT & GPIO_IT_FALLING) == GPIO_IT_FALLING)
            {
                REGBITS_SET(GPIOx->FALLIE, GPIO_Init->Pins);
            }
            if ((GPIO_Init->IT & GPIO_IT_HIGH) == GPIO_IT_HIGH)
            {
                REGBITS_SET(GPIOx->HIGHIE, GPIO_Init->Pins);
            }
            if ((GPIO_Init->IT & GPIO_IT_LOW) == GPIO_IT_LOW)
            {
                REGBITS_SET(GPIOx->LOWIE, GPIO_Init->Pins);
            }
        }
        else                                                           //输出模式
        {
            REGBITS_CLR(GPIOx->DIR, GPIO_Init->Pins);
            if (GPIO_Init->Mode == GPIO_MODE_OUTPUT_PP)
            {
                REGBITS_CLR(GPIOx->OPENDRAIN, GPIO_Init->Pins);
            }
            else
            {
                REGBITS_SET(GPIOx->OPENDRAIN, GPIO_Init->Pins);
            }
            if (GPIO_Init->Speed == GPIO_SPEED_HIGH)
            {
                REGBITS_SET(GPIOx->SPEED, GPIO_Init->Pins);
            }
            else
            {
                REGBITS_CLR(GPIOx->SPEED, GPIO_Init->Pins);
            }
        }
    }
}

//=============================================================================
//GPIO 反初始化， 多个引脚
/**
 * @brief GPIO 去初始化，可同时设置多个引脚或单个引脚
 *
 * @param GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC CW_GPIOF
 *
 * @param GPIO_Pins 参数取值如下
 *        @arg GPIO_PIN_0/1/2.../15/ALL 可通过与运算同时操作多个引脚
 */
void GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pins)
{
    REGBITS_SET(GPIOx->ANALOG, GPIO_Pins);
    REGBITS_SET(GPIOx->DIR, GPIO_Pins);
    REGBITS_CLR(GPIOx->PUR, GPIO_Pins);
    REGBITS_CLR(GPIOx->PDR, GPIO_Pins);
    REGBITS_CLR(GPIOx->RISEIE, GPIO_Pins);
    REGBITS_CLR(GPIOx->FALLIE, GPIO_Pins);
    REGBITS_CLR(GPIOx->HIGHIE, GPIO_Pins);
    REGBITS_CLR(GPIOx->LOWIE, GPIO_Pins);
    REGBITS_CLR(GPIOx->OPENDRAIN, GPIO_Pins);
}
//=============================================================================
//获取指定引脚电平，一个引脚
//注意：建议采用宏函数来获取引脚电平，例PA00_GETVALUE()
/**
 * @brief 获取一个引脚的电平
 *
 * @param GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC CW_GPIOF
 * @param GPIO_Pin 参数取值如下
 *        @arg GPIO_PIN_0/1/2.../15
 * @return GPIO_PinState 取值如下:
 *        @arg GPIO_Pin_SET
 *        @arg GPIO_Pin_RESET
 */
GPIO_PinState GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    if (GPIOx->IDR & GPIO_Pin)
    {
        return (GPIO_Pin_SET);
    }
    return (GPIO_Pin_RESET);
}

//=============================================================================
//设置指定引脚电平，多个引脚
//注意：如只操作一只引脚，建议采用宏函数，例PA00_SETHIGH(), PA00_SETLOW()
/**
 * @brief 设置指定引脚电平，可同时设置多个引脚
 *
 * @param GPIOx GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC CW_GPIOF
 * @param GPIO_Pins 参数取值如下
 *        @arg GPIO_PIN_0/1/2.../15/ALL;
 * @param PinState 取值如下:
 *        @arg GPIO_Pin_SET
 *        @arg GPIO_Pin_RESET
 */
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pins, GPIO_PinState PinState)
{
    if (PinState == GPIO_Pin_SET)
    {
        GPIOx->BSRR = GPIO_Pins;
    }
    else
    {
        GPIOx->BRR = GPIO_Pins;
    }
}

/**
 * @brief 设置指定引脚端口的输出值
 *
 * @param GPIOx GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC
 * @param Value
 */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t Value)
{
    GPIOx->ODR = Value;

}
//=============================================================================
//设置端口低字节（B0-B7）引脚电平
/**
 * @brief 设置端口低字节（B0-B7）引脚电平
 *
 * @param GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOF
 * @param Value 取值范围：0x00~0xFF
 */
void GPIO_LowByte_Write(GPIO_TypeDef *GPIOx, uint8_t Value)
{
    GPIOx->ODRLOWBYTE = Value;
}

//=============================================================================
//设置端口高字节（B8-B15）引脚电平
/**
 * @brief 设置端口高字节（B8-B15）引脚电平
 *
 * @param GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC
 * @param Value 取值范围：0x00~0xFF
 */
void GPIO_HighByte_Write(GPIO_TypeDef *GPIOx, uint8_t Value)
{
    GPIOx->ODRHIGHBYTE = Value;
}

//=============================================================================
//翻转指定引脚电平，多个引脚
//注意：如只操作一只引脚，建议采用宏函数，例PA00_TOG()
/**
 * @brief 翻转指定引脚电平，可同时设置多个引脚
 *
 * @param GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC CW_GPIOF
 * @param GPIO_Pins
 */
void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pins)
{
    GPIOx->TOG = GPIO_Pins;
}

//=============================================================================
//锁定指定引脚配置项，多个引脚
/**
 * @brief 锁定指定引脚配置项，可同时设置多个引脚
 *
 * @param GPIOx  参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC CW_GPIOF
 * @param GPIO_Pins
 */
void GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pins)
{
    REGBITS_SET(GPIOx->LOCK, GPIO_Pins);
}

//=============================================================================
//将PA13/PA14设置成GPIO
/**
 * @brief 将PA13/PA14设置成GPIO
 *
 */
void GPIO_SWD2GPIO(void)
{
    CW_SYSCTRL->CR2 =  CW_SYSCTRL->CR2 | (0x5A5A0000 | bv1);
}

//=============================================================================
//将PA13/PA14设置成SWD
/**
 * @brief 将PA13/PA14设置成SWD，PA13/SWDIO PA14/SWCLK
 *
 */
void GPIO_GPIO2SWD(void)
{
    CW_SYSCTRL->CR2 =  0x5A5A0000 | (CW_SYSCTRL->CR2 & (~(bv1)));
}

//=============================================================================
//配置端口滤波
// FltClk 只能是宏定义中定义的参数
/**
 * @brief 配置端口滤波
 *
 * @param GPIOx 参数为下列参数之一：
 *        @arg CW_GPIOA CW_GPIOB CW_GPIOC CW_GPIOF
 * @param GPIO_Pins
 * @param FltClk 只能是宏定义中定义的参数 GPIO_FLTCLK_xxx
 */
void GPIO_ConfigFilter(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pins, uint32_t FltClk)
{
    GPIOx->FILTER = FltClk | GPIO_Pins;
}

//=============================================================================
//配置端口辅助功能
//请使用CW32f030_gpio.h中的宏定义来配置每个端口的辅助功能

