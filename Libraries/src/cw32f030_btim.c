/**
 * @file cw32f030_btim.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-04-22
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
#include "cw32f030_btim.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/*******************************************************************************
// 说明：去初始化
// 参数：BTIMx x为1~3
// 返回值：无
*******************************************************************************/

void BTIM_DeInit(BTIM_TypeDef *BTIMx)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    BTIMx->BCR = 0UL;
    BTIMx->ARR = 0x0000FFFF;
    BTIMx->CNT = 0UL;
    BTIMx->ACR = 0UL;
    BTIMx->IER = 0UL;
    BTIMx->ICR = 0UL;
    BTIMx->DMA = 0UL;
}

/*******************************************************************************
// 说明：BTIM基本定时器初始化
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_TimeBaseInitStruct 指向BTIM_TimeBaseInitTypeDef类型结构体的指针
// 返回值：无
*******************************************************************************/
void BTIM_TimeBaseInit(BTIM_TypeDef *BTIMx, BTIM_TimeBaseInitTypeDef *BTIM_TimeBaseInitStruct)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_MODE(BTIM_TimeBaseInitStruct->BTIM_Mode));
    assert_param(IS_BTIM_PRS_DIV(BTIM_TimeBaseInitStruct->BTIM_Prescaler));
    REGBITS_MODIFY(BTIMx->BCR, BTIMx_BCR_MODE_Msk | BTIMx_BCR_PRS_Msk | BTIMx_BCR_ONESHOT_Msk,
                   BTIM_TimeBaseInitStruct->BTIM_Mode | BTIM_TimeBaseInitStruct->BTIM_Prescaler |
                   BTIM_TimeBaseInitStruct->BTIM_OPMode);
    BTIMx->ARR = BTIM_TimeBaseInitStruct->BTIM_Period;
}

/*******************************************************************************
// 说明：结构体数据BTIM_TimeBaseInitStruct初始化
// 参数：BTIM_TimeBaseInitStruct
// 返回值：无
*******************************************************************************/

void BTIM_TimeBaseStructInit(BTIM_TimeBaseInitTypeDef *BTIM_TimeBaseInitStruct)
{
    BTIM_TimeBaseInitStruct->BTIM_Prescaler =  BTIM_PRS_DIV1;
    BTIM_TimeBaseInitStruct->BTIM_Mode = BTIM_Mode_TIMER;
    BTIM_TimeBaseInitStruct->BTIM_Period = 0xFFFF;
}

/*******************************************************************************
// 说明：使能BTIMx定时器
// 参数：BTIM_TimeBaseInitStruct
// 返回值：无
*******************************************************************************/
void BTIM_Cmd(BTIM_TypeDef *BTIMx, FunctionalState NewState)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    NewState ? (BTIMx->BCR |= BTIMx_BCR_EN_Msk) : (BTIMx->BCR &= ~BTIMx_BCR_EN_Msk);
}


/*******************************************************************************
// 说明：配置BTIMx的中断
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_IT 中断事件类型
// 参数：NewState 中断事件类型的状态，ENABLE 或 DISABLE
// 返回值：无
*******************************************************************************/
void BTIM_ITConfig(BTIM_TypeDef *BTIMx, uint16_t BTIM_IT, FunctionalState NewState)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_BTIM_IT(BTIM_IT));
    NewState ? (BTIMx->IER |= BTIM_IT) : (BTIMx->IER &= ~BTIM_IT);
}


/*******************************************************************************
// 说明：配置BTIMx的DMA功能
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_DMASource DMA触发事件类型
// 参数：NewState 中断事件类型的状态，ENABLE 或 DISABLE
// 返回值：无
*******************************************************************************/
void BTIM_DMACmd(BTIM_TypeDef *BTIMx, uint16_t BTIM_DMASource, FunctionalState NewState)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_BTIM_DMA_SOURCE(BTIM_DMASource));
    NewState ? (BTIMx->DMA |= BTIM_DMASource) : (BTIMx->DMA &= ~BTIM_DMASource);
}

/*******************************************************************************
// 说明：配置BTIMx的预分配系数
// 参数：BTIMx CW_BTIM1~3
// 参数：Prescaler 预分配系数
// 参数：BTIM_PSCReloadMode 预分配系数是立即更新还是在溢出时更新,取值范围
//       BTIM_PSCReloadMode_Update 预分配系数在溢出时更新
//       BTIM_PSCReloadMode_Immediate 预分配系数立即更新
// 返回值：无
*******************************************************************************/
void BTIM_PrescalerConfig(BTIM_TypeDef *BTIMx, uint16_t Prescaler, uint16_t BTIM_PSCReloadMode)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_PRS_DIV(Prescaler));
    assert_param(IS_BTIM_PRESCALER_RELOAD(BTIM_PSCReloadMode));
    REGBITS_MODIFY(BTIMx->BCR, BTIMx_BCR_PRS_Msk, Prescaler);
    if (BTIM_PSCReloadMode == BTIM_PSCReloadMode_Immediate)
    {
        BTIMx->BCR &= ~BTIMx_BCR_EN_Msk;
        BTIMx->BCR |= BTIMx_BCR_EN_Msk;
    }
}

/*******************************************************************************
// 说明：配置BTIMx的工作模式
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_Mode 模式类型
//       BTIM_Mode_TIMER   定时器模式
//       BTIM_Mode_COUNTER 计数器模式
//       BTIM_Mode_TRIGGER 触发启动模式
//       BTIM_Mode_GATE    门控模式
// 返回值：无
*******************************************************************************/
void BTIM_ModeConfig(BTIM_TypeDef *BTIMx, uint16_t BTIM_Mode)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_MODE(BTIM_Mode));
    REGBITS_MODIFY(BTIMx->BCR, BTIMx_BCR_MODE_Msk, BTIM_Mode);
}

/*******************************************************************************
// 说明：配置BTIMx的触发输入信号来源
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_InputTriggerSource 触发源
//       BTIM_TS_ITR   内部ITR信号
//       BTIM_TS_ETR   外部ETR信号
// 返回值：无
*******************************************************************************/
void BTIM_SelectInputTrigger(BTIM_TypeDef *BTIMx, uint16_t BTIM_InputTriggerSource)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_TRIGGER_SELECTION(BTIM_InputTriggerSource));
    REGBITS_MODIFY(BTIMx->BCR, BTIMx_BCR_TRS_Msk, BTIM_InputTriggerSource);
}

/*******************************************************************************
// 说明：配置BTIMx外部输入ETR信号的极性
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_ETR_Polarity  极性类型
//       BTIM_ETR_Polarity_Positive   正极性
//       BTIM_ETR_Polarity_Negative 负极性
// 返回值：无
*******************************************************************************/
void BTIM_SelectETRInputPolarity(BTIM_TypeDef *BTIMx, uint16_t BTIM_ETR_Polarity)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_ETR_POLARITY(BTIM_ETR_Polarity));
    REGBITS_MODIFY(BTIMx->BCR, BTIMx_BCR_POL_Msk, BTIM_ETR_Polarity);
}

/*******************************************************************************
// 说明：配置BTIMx的单次运行模式
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_OPMode  运行类型
//       BTIM_OPMode_Single   单次运行
//       BTIM_OPMode_Repetitive 连续运行
// 返回值：无
*******************************************************************************/
void BTIM_SelectOnePulseMode(BTIM_TypeDef *BTIMx, uint16_t BTIM_OPMode)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_OPM_MODE(BTIM_OPMode));
    REGBITS_MODIFY(BTIMx->BCR, BTIMx_BCR_ONESHOT_Msk, BTIM_OPMode);
}

/*******************************************************************************
// 说明：配置BTIMx的翻转输出功能
// 参数：BTIMx CW_BTIM1~3
// 参数：NewState ENABLE 或 DISABLE
// 返回值：无
*******************************************************************************/
void BTIM_OutputToggleCmd(BTIM_TypeDef *BTIMx, FunctionalState NewState)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    NewState ? (BTIMx->BCR |= BTIMx_BCR_TOGEN_Msk) : (BTIMx->BCR &= ~BTIMx_BCR_TOGEN_Msk);
}

/*******************************************************************************
// 说明：配置BTIMx的外部输入ETR
// 参数：BTIMx CW_BTIM1~3
// 参数：BTIM_ExtTRGPolarity ETR信号的极性 BTIM_ETR_Polarity_Positive
//                                         BTIM_ETR_Polarity_Negative
// 参数：ExtTRGFilter  ETR滤波器配置
// 返回值：无
*******************************************************************************/
void BTIM_ETRConfig(BTIM_TypeDef *BTIMx, uint16_t BTIM_ExtTRGPolarity, uint16_t ExtTRGFilter)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_ETR_POLARITY(BTIM_ExtTRGPolarity));
    assert_param(IS_BTIM_EXT_FILTER(ExtTRGFilter));
    REGBITS_MODIFY(BTIMx->BCR, BTIMx_BCR_POL_Msk, BTIM_ExtTRGPolarity);
    REGBITS_MODIFY(BTIMx->ACR, BTIMx_ACR_ETRFLT_Msk, ExtTRGFilter);
}

/*******************************************************************************
// 说明：设置BTIM的计数初值
// 参数：BTIMx CW_BTIM1~3
// 参数：Counter 范围0x0000~0xFFFF
// 返回值：无
*******************************************************************************/
void BTIM_SetCounter(BTIM_TypeDef *BTIMx, uint16_t Counter)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    BTIMx->CNT = Counter;
}

/*******************************************************************************
// 说明：设置BTIM的自动重载值
// 参数：BTIMx CW_BTIM1~3
// 参数：Autoreload 范围0x0000~0xFFFF
// 返回值：无
*******************************************************************************/
void BTIM_SetAutoreload(BTIM_TypeDef *BTIMx, uint16_t Autoreload)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    BTIMx->ARR = Autoreload;
}

/*******************************************************************************
// 说明：获取BTIM的当前计数值
// 参数：BTIMx CW_BTIM1~3
// 返回值：CNT寄存器的值
*******************************************************************************/
uint16_t BTIM_GetCounter(BTIM_TypeDef *BTIMx)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    return BTIMx->CNT;
}

/*******************************************************************************
// 说明：获取BTIM的当前自动重载值
// 参数：BTIMx CW_BTIM1~3
// 返回值：ARR寄存器的值
*******************************************************************************/
uint16_t BTIM_GetAutoreload(BTIM_TypeDef *BTIMx)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    return BTIMx->ARR;
}

/*******************************************************************************
// 说明：获取BTIM的当前预分配系数
// 参数：BTIMx CW_BTIM1~3
// 返回值：预分频器当前正在使用的分频系数
*******************************************************************************/
uint16_t BTIM_GetPrescaler(BTIM_TypeDef *BTIMx)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    return BTIMx->BCR_f.PRSSTATUS;
}
/*******************************************************************************
// 说明： 检查BTIM的状态寄存器的各状态位是否置位
// 参数： BTIMx CW_BTIM1~3
// 参数： BTIM_FLAG 指定的状态位 ，参数范围： BTIM_IT_OV
//                                           BTIM_IT_TI
//                                           BTIM_IT_TOP
//
// 返回值： ITStatus
*******************************************************************************/
ITStatus BTIM_GetITStatus(BTIM_TypeDef *BTIMx, uint16_t BTIM_FLAG)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_IT(BTIM_FLAG));
    return (REGBITS_GET(BTIMx->ISR, BTIM_FLAG) ? SET : RESET);
}

/*******************************************************************************
// 说明： 清除BTIM的状态寄存器的各状态位
// 参数： BTIMx CW_BTIM1~3
// 参数： BTIM_FLAG 指定的状态位 ，参数范围： BTIM_IT_OV
//                                           BTIM_IT_TI
//                                           BTIM_IT_TOP
//
// 返回值： 预分频器当前正在使用的分频系数
*******************************************************************************/

void BTIM_ClearITPendingBit(BTIM_TypeDef *BTIMx, uint16_t BTIM_FLAG)
{
    assert_param(IS_BTIM_ALL_PERIPH(BTIMx));
    assert_param(IS_BTIM_IT(BTIM_FLAG));
    REGBITS_CLR(BTIMx->ICR, BTIM_FLAG);
}

