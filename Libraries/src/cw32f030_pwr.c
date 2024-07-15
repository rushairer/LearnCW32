/**
 * @file cw32f030_pwr.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-08-09
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

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "cw32f030.h"
#include "cw32f030_pwr.h"

/**
 *******************************************************************************
 ** \addtogroup LpmGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
/*
#define IS_VALID_SEVONPEND(x)           (SevPndDisable == (x) ||\
                                         SevPndEnable  == (x))
#define IS_VALID_SLEEPDEEP(x)           (SlpDpDisable  == (x) ||\
                                         SlpDpEnable   == (x))
#define IS_VALID_SLEEPONEXIT(x)         (SlpExtDisable == (x) ||\
                                         SlpExtEnable  == (x))
*/

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @brief 低功耗模式配置
 *
 * @param PWR_InitStruct      低功耗模式配置结构体指针
 *
 * @return
 */
void PWR_Config(PWR_InitTypeDef *PWR_InitStruct)
{
    //ASSERT(NULL != PWR_InitStruct);
    assert_param(IS_PWR_SEVONPEND(PWR_InitStruct->PWR_Sevonpend));
    assert_param(IS_PWR_SLEEPDEEP(PWR_InitStruct->PWR_SleepDeep));
    assert_param(IS_PWR_SLEEPONEXIT(PWR_InitStruct->PWR_SleepOnExit));
    REGBITS_MODIFY(SCB->SCR, SCB_SCR_SEVONPEND_Msk | \
                   SCB_SCR_SLEEPDEEP_Msk | \
                   SCB_SCR_SLEEPONEXIT_Msk, \
                   PWR_InitStruct->PWR_Sevonpend | \
                   PWR_InitStruct->PWR_SleepDeep | \
                   PWR_InitStruct->PWR_SleepOnExit);
}

/**
 * @brief 进入睡眠模式
 *
 * @return
 */
void PWR_GotoLpmMode(void)
{
    uint32_t RegBack;
    if (SCB->SCR & SCB_SCR_SLEEPDEEP_Msk)    // 进入深度休眠，需要做一些保护操作
    {
        if (CW_SYSCTRL->APBEN2_f.VC)     // VC的时钟打开，需要判断VC的ready位状态是否为1，否则无法进入深度睡眠
        {
            while (!CW_VC1->SR_f.READY);
            while (!CW_VC2->SR_f.READY);
        }
        // 进入深度休眠，HCLK的时钟频率需要小于等于4Mhz，否者容易损坏内核
        RegBack = CW_SYSCTRL->CR0;
        CW_SYSCTRL->CR0_f.HCLKPRS = 6;    // 64分频，HCLK的频率不会超过4Mhz
    }
    __WFI();
    // 退出休眠后，恢复HCLK的配置
    CW_SYSCTRL->CR0 = RegBack;
}

//@} // LpmGroup

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
