/**
 * @file cw32f030_awt.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-05-18
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
#include "cw32f030_awt.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief AWT  去初始化
 *
 */
void AWT_DeInit(void)
{
    CW_AWT->CR = 0UL;
    CW_AWT->ARR = 0x0000FFFFUL;
    CW_AWT->IER = 0UL;
    CW_AWT->ICR = 0UL;
}

/**
 * @brief AWT定时器计数初始化
 *
 * @param AWT_TimeCntInitStruct
 */
void AWT_TimeCntInit(AWT_TimeCntInitTypeDef *AWT_TimeCntInitStruct)
{
    assert_param(IS_AWT_CLKSOURCE(AWT_TimeCntInitStruct->AWT_ClkSource));
    assert_param(IS_AWT_PRS_DIV(AWT_TimeCntInitStruct->AWT_Prescaler));
    assert_param(IS_AWT_ARR(AWT_TimeCntInitStruct->AWT_Period));
    assert_param(IS_AWT_MODE(AWT_TimeCntInitStruct->AWT_Mode));
    REGBITS_MODIFY(CW_AWT->CR, AWT_CR_SRC_Msk | \
                   AWT_CR_PRS_Msk | \
                   AWT_CR_MD_Msk
                   , \
                   AWT_TimeCntInitStruct->AWT_ClkSource | \
                   AWT_TimeCntInitStruct->AWT_Prescaler | \
                   AWT_TimeCntInitStruct->AWT_Mode);
    CW_AWT->ARR = AWT_TimeCntInitStruct->AWT_Period;
}

/**
 * @brief 结构体数据AWT_TimeCntInitStruct初始化
 *
 * @param AWT_TimeCntInitStruct
 */
void AWT_TimeCntStructInit(AWT_TimeCntInitTypeDef *AWT_TimeCntInitStruct)
{
    AWT_TimeCntInitStruct->AWT_ClkSource = AWT_CLKSOURCE_HSIOSC;
    AWT_TimeCntInitStruct->AWT_Prescaler = AWT_PRS_DIV2;
    AWT_TimeCntInitStruct->AWT_Mode = AWT_MODE_TIMECNT;
    AWT_TimeCntInitStruct->AWT_Period = (uint32_t)0x0000FFFF;
}

/**
 * @brief 使能AWT定时器
 *
 * @param NewState
 */
void AWT_Cmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        CW_AWT->CR |= AWT_CR_EN;
    }
    else
    {
        CW_AWT->CR &= (~AWT_CR_EN);
    }
}

/**
 * @brief 配置AWT的中断
 *
 * @param AWT_IT
 * @param NewState
 */
void AWT_ITConfig(uint32_t AWT_IT, FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_AWT_IT(AWT_IT));
    if (NewState != DISABLE)
    {
        CW_AWT->IER |= AWT_IT;
    }
    else
    {
        CW_AWT->IER &= (~AWT_IT);
    }
}


/**
 * @brief 获取AWT中断标志
 *
 * @param AWT_IT
 * @return ITStatus
 */
ITStatus AWT_GetITStatus(uint32_t AWT_IT)
{
    assert_param(IS_AWT_IT(AWT_IT));
    return (CW_AWT->ISR & AWT_IT) ? SET : RESET;
}

/**
 * @brief 清除AWT中断标志
 *
 * @param AWT_IT
 */
void AWT_ClearITPendingBit(uint32_t AWT_IT)
{
    assert_param(IS_AWT_IT(AWT_IT));
    CW_AWT->ICR &= (~AWT_IT);
}

/**
 * @brief AWT计数时钟源配置
 *
 * @param AWT_ClkSrouce
 */
void AWT_ClkSourceConfig(uint32_t AWT_ClkSource)
{
    assert_param(IS_AWT_CLKSOURCE(AWT_ClkSource));
    REGBITS_MODIFY(CW_AWT->CR, AWT_CR_SRC_Msk, AWT_ClkSource);
}

/**
 * @brief AWT计数时钟分频系数配置
 *
 * @param Prescaler
 */
void AWT_PrescalerConfig(uint32_t AWT_Prescaler)
{
    assert_param(IS_AWT_PRS_DIV(AWT_Prescaler));
    REGBITS_MODIFY(CW_AWT->CR, AWT_CR_PRS_Msk, AWT_Prescaler);
}

/**
 * @brief 读取AWT计数器CNT寄存器值
 *
 * @return uint16_t
 */
uint16_t AWT_GetCounter(void)
{
    return (uint16_t)(CW_AWT->CNT);
}

/**
 * @brief 读取AWT计数器重载值寄存器ARR值
 *
 * @return uint16_t
 */
uint16_t AWT_GetAutoreload(void)
{
    return (uint16_t)(CW_AWT->ARR);
}

/**
 * @brief 读取AWT时钟源
 *
 * @return uint32_t
 */
uint32_t AWT_GetClkSource(void)
{
    return (uint32_t)((CW_AWT->CR_f.SRC));
}

/**
 * @brief 读取AWT时钟分频系数
 *
 * @return uint32_t
 */
uint32_t AWT_GetPrescaler(void)
{
    return (uint32_t)((CW_AWT->CR_f.PRS));
}


