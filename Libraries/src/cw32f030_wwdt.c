/**
 * @file cw32f030_wwdt.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-04-23
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
#include "cw32f030_wwdt.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief WWDT去初始化
 * @param 无
 * @return 无
 */
void WWDT_DeInit(void)
{
    CW_SYSCTRL->APBRST1_f.WWDT = 0;
    CW_SYSCTRL->APBRST1_f.WWDT = 1;
}

/**
 * @brief 初始化WWDT
 * @param WWDT_InitStruct 详见结构体定义WWDT_InitTypeDef
 */
void WWDT_Init(WWDT_InitTypeDef *WWDT_InitStruct)
{
    assert_param(IS_WWDT_COUNTER(WWDT_InitStruct->WWDT_CounterValue));
    assert_param(IS_WWDT_PRESCALER(WWDT_InitStruct->WWDT_Prescaler));
    assert_param(IS_WWDT_WINDOW_VALUE(WWDT_InitStruct->WWDT_WindowValue));
    CW_SYSCTRL->APBEN1_f.WWDT = 1U;    /* WWDT的APB总线访问时钟使能 */
    CW_WWDT->CR0 = (WWDT_InitStruct->WWDT_CounterValue & WWDT_CR0_WCNT_Msk);
    if (WWDT_InitStruct->WWDT_ITState == ENABLE)
    {
        CW_WWDT->CR1 = WWDT_InitStruct->WWDT_WindowValue | WWDT_InitStruct->WWDT_Prescaler | WWDT_CR1_IE_Msk;
    }
    else
    {
        CW_WWDT->CR1 = (WWDT_InitStruct->WWDT_WindowValue | WWDT_InitStruct->WWDT_Prescaler) & (~WWDT_CR1_IE_Msk);
    }
}

/**
 * @brief 使能WWDT，使能WWDT后不能禁止
 */
void WWDT_Cmd(void)
{
    CW_WWDT->CR0_f.EN = 1U;
}

/**
 * @brief 喂狗函数
 * @param Counter WWDT计数器的更新值，取值范围0x40~0x7F
 */
void WWDT_Refresh(uint8_t Counter)
{
    assert_param(IS_WWDT_COUNTER(Counter));
    CW_WWDT->CR0_f.WCNT = Counter;
}

/**
 * @brief 设置WWDT的预分频系数
 * @param WWDT_Prescaler 取值范围WWDT_Prescaler_DIV4096~WWDT_Prescaler_DIV524288
 */
void WWDT_SetPrescaler(uint32_t WWDT_Prescaler)
{
    assert_param(IS_WWDT_PRESCALER(WWDT_Prescaler));
    REGBITS_MODIFY(CW_WWDT->CR1, WWDT_CR1_PRS_Msk, WWDT_Prescaler);
}

/**
 * @brief 设置WWDT的窗口系数
 * @param WindowValue 窗口值，取值范围0x40~0x7F
 */
void WWDT_SetWindowValue(uint8_t WindowValue)
{
    assert_param(IS_WWDT_WINDOW_VALUE(WindowValue));
    CW_WWDT->CR1_f.WINR = WindowValue;
}

/**
 * @brief 设置WWDT的CNT值
 * @param CountValue 窗口值，取值范围0x40~0x7F, 小于0x40将产生复位
 */
void WWDT_SetCountValue(uint8_t CountValue)
{
    CW_WWDT->CR0_f.WCNT = CountValue;
}

/**
 * @brief 获取当前计数器的值
 * @return uint8_t 当前计数器的值
 */
uint8_t WWDT_GetCounterValue(void)
{
    return (uint8_t)(CW_WWDT->CR0 & WWDT_CR0_WCNT_Msk);
}

/**
 * @brief 获取当前设置的窗口值
 * @return uint8_t 当前设置的窗口值
 */
uint8_t WWDT_GetWindowValue(void)
{
    return (uint8_t)(CW_WWDT->CR1 & WWDT_CR1_WINR_Msk);
}

/**
 * @brief  设置WWDT的预溢出中断使能 复位后，默认关闭中断使能
 */
void WWDT_EnableIT(void)
{
    CW_WWDT->CR1_f.IE = ENABLE;
}

/**
 * @brief 获取WWDT的状态寄存器的预溢出位状态
 * @return FlagStatus
 */
FlagStatus WWDT_GetFlagStatus(void)
{
    return (FlagStatus)(CW_WWDT->SR);
}

/**
 * @brief 清除WWDT的状态寄存器的预溢出位状态
 */
void WWDT_ClearFlag(void)
{
    REGBITS_CLR(CW_WWDT->SR, WWDT_SR_POV_Msk);
}
