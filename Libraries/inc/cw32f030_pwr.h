/**
 * @file cw32f030_pwr.h
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-06-21
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

#ifndef __CW32F030_PWR_H
#define __CW32F030_PWR_H

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "base_types.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup LpmGroup Low Power Management (LPM)
 **
 **
 ******************************************************************************/
//@{

/******************************************************************************
 ** Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/** @defgroup PWR_Sevonpend
  * @{
  */
#define PWR_Sevonpend_Disable                   ((uint32_t)0x00000000)
#define PWR_Sevonpend_Enable                    ((uint32_t)0x00000010)

#define IS_PWR_SEVONPEND(SEVONPEND)             (((SEVONPEND) == PWR_Sevonpend_Disable) || \
                                                 ((SEVONPEND) == PWR_Sevonpend_Enable))

/** @defgroup PWR_SleepDeep
  * @{
  */
#define PWR_SleepDeep_Disable                   ((uint32_t)0x00000000)
#define PWR_SleepDeep_Enable                    ((uint32_t)0x00000004)

#define IS_PWR_SLEEPDEEP(SLEEPDEEP)             (((SLEEPDEEP) == PWR_SleepDeep_Disable) || \
                                                 ((SLEEPDEEP) == PWR_SleepDeep_Enable))

/** @defgroup PWR_SleepOnExit
  * @{
  */
#define PWR_SleepOnExit_Disable                 ((uint32_t)0x00000000)
#define PWR_SleepOnExit_Enable                  ((uint32_t)0x00000002)

#define IS_PWR_SLEEPONEXIT(SLEEPONEXIT)         (((SLEEPONEXIT) == PWR_SleepOnExit_Disable) || \
                                                 ((SLEEPONEXIT) == PWR_SleepOnExit_Enable))

/**
 ******************************************************************************
 ** @brief Low Power Mode 配置结构体定义
 *****************************************************************************/
typedef struct
{
    uint32_t   PWR_Sevonpend;        // 使能:每次新中断会产生一个事件,如果使用WFE休眠,则可用于唤醒处理器.
    uint32_t   PWR_SleepDeep;        // 使能:执行WFI进入深度休眠;不使能:执行WFI进入休眠.
    uint32_t   PWR_SleepOnExit;      // 使能:退出异常处理并返回时,处理器自动进入休眠模式;不使能:该特性禁止.
} PWR_InitTypeDef;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
//功能配置及操作函数
//低功耗模式配置
void PWR_Config(PWR_InitTypeDef *PWR_InitStruct);
//进入低功耗模式
void PWR_GotoLpmMode(void);

//@} // PWRGroup

#ifdef __cplusplus
}
#endif


#endif /* __CW32F030_PWR_H */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


