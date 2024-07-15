/**
 * @file cw32f030_ram.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-05-14
 *
 * @copyright Copyright (c) 2021
 *
 */

/*******************************************************************************
*
* 代码许可和免责信息
* 武汉芯源半导体有限公司授予您使用所有编程代码示例的非专属的版权许可，您可以由此
* 生成根据您的特定需要而定制的相似功能。根据不能被排除的任何法定保证，武汉芯源半
* 导体有限公司及其程序开发商和供应商对程序或技术支持（如果有）不提供任何明示或暗
* 含的保证或条件，包括但不限于暗含的有关适销性、适用于某种特定用途和非侵权的保证
* 或条件。
* 无论何种情形，武汉芯源半导体有限公司及其程序开发商或供应商均不对下列各项负责，
* 即使被告知其发生的可能性时，也是如此：数据的丢失或损坏；直接的、特别的、附带的
* 或间接的损害，或任何后果性经济损害；或利润、业务、收入、商誉或预期可节省金额的
* 损失。
* 某些司法辖区不允许对直接的、附带的或后果性的损害有任何的排除或限制，因此某些或
* 全部上述排除或限制可能并不适用于您。
*
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "cw32f030_ram.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief   RAM中断配置
 *
 * @param RAM_IT     : RAM_IT_PARITY
 * @param NewState   : ENABLE  DISABLE
 */
void RAM_ITConfig(uint32_t RAM_IT, FunctionalState NewState)
{
    assert_param(IS_RAM_IT(RAM_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        CW_RAM->IER |= RAM_IT;
    }
    else
    {
        CW_RAM->IER &= (~RAM_IT);
    }
}

/**
 * @brief 获取RAM中断标志
 *
 * @param RAM_IT     : RAM_IT_PARITY
 * @return ITStatus    : SET  RESET
 */
ITStatus RAM_GetITStatus(uint32_t RAM_IT)
{
    assert_param(IS_RAM_GET_IT(RAM_IT));
    return (CW_RAM->ISR & RAM_IT) ? SET : RESET;
}

/**
 * @brief 清除RAM中断标志
 *
 * @param RAM_IT   : RAM_IT_PARITY
 */
void RAM_ClearITPendingBit(uint32_t RAM_IT)
{
    assert_param(IS_RAM_IT(RAM_IT));
    CW_RAM->ICR &= (~RAM_IT);
}

/**
 * @brief 获取发生奇偶校验错的RAM地址
 *
 * @return uint32_t
 */
uint32_t RAM_GetErrorAddress(void)
{
    return (CW_RAM->ADDR);
}

