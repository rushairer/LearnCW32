/**
 * @file cw32f030_lvd.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @file cw32f030_lvd.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-07-27
 *
 * @copyright Copyright (c) 2021
 *
 */
/*******************************************************************************
*
* 代码许可和免责信息
* 武汉力源半导体有限公司授予您使用所有编程代码示例的非专属的版权许可，您可以由此
* 生成根据您的特定需要而定制的相似功能。根据不能被排除的任何法定保证，武汉力源半
* 导体有限公司及其程序开发商和供应商对程序或技术支持（如果有）不提供任何明示或暗
* 含的保证或条件，包括但不限于暗含的有关适销性、适用于某种特定用途和非侵权的保证
* 或条件。
* 无论何种情形，武汉力源半导体有限公司及其程序开发商或供应商均不对下列各项负责，
* 即使被告知其发生的可能性时，也是如此：数据的丢失或损坏；直接的、特别的、附带的
* 或间接的损害，或任何后果性经济损害；或利润、业务、收入、商誉或预期可节省金额的
* 损失。
* 某些司法辖区不允许对直接的、附带的或后果性的损害有任何的排除或限制，因此某些或
* 全部上述排除或限制可能并不适用于您。
*
*******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "cw32f030.h"
#include "cw32f030_lvd.h"

/**
 ******************************************************************************
 ** \addtogroup LvdGroup
 ******************************************************************************/
//@{

/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

#define IS_VALID_INPUT(x)       ( (x) <= LvdInputPB11 )

#define IS_VALID_THRESHOLD(x)   ( (x) <= LvdTH3p3V )

#define IS_VALID_CLK(x)         ( (x) <= LvdFilterHsi )

#define IS_VALID_FILTER(x)      ( (x) <= LvdFilter4095Clk )

#define IS_VALID_IRQTYPE(x)     ( (x) <= LvdIrqFall )


/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')        *
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/

/**
 * @brief
 *          使能NVIC的LVD中断
 *
 * @param   intPriority:0~3
 *
 * @return  无
 */
void LVD_EnableNvic(uint8_t intPriority)
{
    NVIC_ClearPendingIRQ(LVD_IRQn);
    NVIC_SetPriority(LVD_IRQn, intPriority);
    NVIC_EnableIRQ(LVD_IRQn);
}

/**
 * @brief
 *          停止NVIC的LVD中断
 *
 * @param   无
 *
 * @return  无
 */
void LVD_DisableNvic(void)
{
    NVIC_ClearPendingIRQ(LVD_IRQn);
    NVIC_DisableIRQ(LVD_IRQn);
}

/**
 * @brief
 *          配置LVD中断/系统复位触发方式
 *
 * @param   LVD_TRIG:
 *          @arg LVD_TRIG_LEVEL
 *          @arg LVD_TRIG_FALL
 *          @arg LVD_TRIG_RISE
 * @param   NewState:
 *          @arg DISABLE
 *          @arg ENABLE
 *
 * @return  无
 */
void LVD_TrigConfig(uint16_t LVD_TRIG, FunctionalState NewState)
{
    uint8_t itMask = 0;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_LVD_TRIG(LVD_TRIG));
    /* Get the LVD TRIG index */
    itMask = (uint8_t) LVD_TRIG;
    if (NewState != DISABLE)
    {
        /* Enable the selected LVD interrupts */
        CW_LVD->CR1 |= itMask;
    }
    else
    {
        /* Disable the selected LVD interrupts */
        CW_LVD->CR1 &= (~(uint32_t) itMask);
    }
}

/**
 * @brief
 *          使能LVD中断
 *
 * @param   intPriority:0~3
 *
 * @return
 */
void LVD_EnableIrq(uint8_t intPriority)
{
    REGBITS_SET(CW_LVD->CR0, LVD_CR0_IE_Msk);
    LVD_EnableNvic(intPriority);
}

/**
 * @brief
 *          禁止LVD中断
 *
 * @param   无
 *
 * @return  无
 */
void LVD_DisableIrq(void)
{
    LVD_DisableNvic();
    REGBITS_CLR(CW_LVD->CR0, LVD_CR0_IE_Msk);
    REGBITS_CLR(CW_LVD->CR1, LVD_CR1_LEVEL_Msk | LVD_CR1_FALL_Msk | LVD_CR1_RISE_Msk);
}

/**
 * @brief
 *          LVD初始化
 *
 * @param   LVD_InitStruct
 *
 * @return  无
 */
void LVD_Init(LVD_InitTypeDef *LVD_InitStruct)
{
    ASSERT(LVD_InitStruct);
    assert_param(IS_LVD_ACTION(LVD_InitStruct->LVD_Action));
    assert_param(IS_LVD_SOURCE(LVD_InitStruct->LVD_Source));
    assert_param(IS_LVD_THRESHOLD(LVD_InitStruct->LVD_Threshold));
    assert_param(IS_LVD_FILTER_CLK(LVD_InitStruct->LVD_FilterClk));
    assert_param(IS_LVD_FILTER_TIME(LVD_InitStruct->LVD_FilterTime));
    assert_param(IS_LVD_FILTER(LVD_InitStruct->LVD_FilterEn));
    //Need to DISABLE first.
    LVD_Disable();
    LVD_DisableIrq();
    REGBITS_MODIFY(CW_LVD->CR1, LVD_CR1_FLTCLK_Msk | LVD_CR1_FLTTIME_Msk | LVD_CR1_FLTEN_Msk, \
                   (LVD_InitStruct->LVD_FilterClk | \
                    LVD_InitStruct->LVD_FilterTime | \
                    LVD_InitStruct->LVD_FilterEn));
    REGBITS_MODIFY(CW_LVD->CR0, LVD_CR0_VTH_Msk | LVD_CR0_SOURCE_Msk | LVD_CR0_ACTION_Msk, \
                   (LVD_InitStruct->LVD_Threshold | \
                    LVD_InitStruct->LVD_Source | \
                    LVD_InitStruct->LVD_Action));
}

/**
 * @brief
 *          LVD deinit
 *
 * @param   无
 *
 * @return  无
 */
void LVD_DeInit(void)
{
    LVD_DisableIrq();
    LVD_Disable();
}

/**
 * @brief
 *          使能LVD
 *
 * @param   无
 *
 * @return  无
 */
void LVD_Enable(void)
{
    REGBITS_SET(CW_LVD->CR0, LVD_CR0_EN_Msk);
}

/**
 * @brief
 *          停止LVD
 *
 * @param   无
 *
 * @return  无
 */
void LVD_Disable(void)
{
    REGBITS_CLR(CW_LVD->CR0, LVD_CR0_EN_Msk);
}

/**
 * @brief
 *          获取LVD中断标志
 *
 * @param   无
 *
 * @return  boolean_t: TRUE or FALSE
 */
boolean_t LVD_GetIrqStatus(void)
{
    return (boolean_t)(REGBITS_GET(CW_LVD->SR, LVD_SR_INTF_Msk));
}

/**
 * @brief
 *          获取LVD指定的中断状态
 *
 * @param   LVD_FLAG:
 *          @arg LVD_FLAG_FLTV
 *          @arg LVD_FLAG_INTF
 *
 * @return  FlagStatus: SET or RESET
 */
FlagStatus LVD_GetFlagStatus(uint16_t LVD_FLAG)
{
    assert_param(IS_LVD_GET_FLAG(LVD_FLAG));
    return (REGBITS_GET(CW_LVD->SR, LVD_FLAG) ? SET : RESET);
}

/**
 * @brief
 *          清除LVD中断标志
 *
 * @param   无
 *
 * @return  无
 */
void LVD_ClearIrq(void)
{
    REGBITS_CLR(CW_LVD->SR, LVD_SR_INTF_Msk);
}

/**
 * @brief
 *          获取Filter结果
 *
 * @param   无
 *
 * @return  boolean_t: TRUE or FALSE
 */
boolean_t LVD_GetFilterResult(void)
{
    return (boolean_t)(REGBITS_GET(CW_LVD->SR, LVD_SR_FLTV_Msk));
}
//@} // LvdGroup

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
