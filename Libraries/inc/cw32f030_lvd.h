/**
 * @file cw32f030_lvd.h
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

#ifndef __CW32F030_LVD_H
#define __CW32F030_LVD_H

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "base_types.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup LvdGroup Low Voltage Detector (LVD)
 **
 ******************************************************************************/
//@{
/******************************************************************************
 * Global definitions
 ******************************************************************************/
#define LVD_INT_PRIORITY                        ((uint32_t)3) /*VC interrupt priority (lowest by default)  */

/**
  * @}
  */
/** @defgroup LVD_interrupts_definition
  * @{
  */
#define LVD_TRIG_LEVEL                          ((uint16_t)0x0080)
#define LVD_TRIG_FALL                           ((uint16_t)0x0040)
#define LVD_TRIG_RISE                           ((uint16_t)0x0020)


#define IS_LVD_TRIG(TRIG)                       ((((TRIG) & (uint16_t)0xFF00) == 0x00) && ((TRIG) != 0x00))
#define IS_LVD_GET_TRIG(TRIG)                   (((TRIG) == LVD_TRIG_LEVEL) || \
                                                 ((TRIG) == LVD_TRIG_FALL) || \
                                                 ((TRIG) == LVD_TRIG_RISE))

/** @defgroup LVD_flags_definition
  * @{
  */
#define LVD_FLAG_FLTV                           ((uint16_t)0x0002)
#define LVD_FLAG_INTF                           ((uint16_t)0x0001)

#define IS_LVD_FLAG(FLAG)                       ((((FLAG) & (uint16_t)0xFF00) == 0x00) && ((FLAG) != 0x00))
#define IS_LVD_GET_FLAG(FLAG)                   (((FLAG) == LVD_FLAG_FLTV) || \
                                                 ((FLAG) == LVD_FLAG_INTF))


/** @defgroup LVD_Action
  * @{
  */
#define LVD_Action_Irq                          ((uint32_t)0x00000000)
#define LVD_Action_Reset                        ((uint32_t)0x00000002)

#define IS_LVD_ACTION(ACTION)                   (((ACTION) == LVD_Action_Irq) || \
                                                 ((ACTION) == LVD_Action_Reset))

/** @defgroup LVD_Source
  * @{
  */
#define LVD_Source_VDDA                         ((uint32_t)0x00000000)
#define LVD_Source_PA00                         ((uint32_t)0x00000004)
#define LVD_Source_PB00                         ((uint32_t)0x00000008)
#define LVD_Source_PB11                         ((uint32_t)0x0000000C)

#define IS_LVD_SOURCE(SOURCE)                   (((SOURCE) == LVD_Source_VDDA) || \
                                                 ((SOURCE) == LVD_Source_PA00) || \
                                                 ((SOURCE) == LVD_Source_PB00) || \
                                                 ((SOURCE) == LVD_Source_PB11))

/** @defgroup LVD_Threshold
  * @{
  */
#define LVD_Threshold_2p0V                      ((uint32_t)0x00000000)
#define LVD_Threshold_2p11V                     ((uint32_t)0x00000010)
#define LVD_Threshold_2p22V                     ((uint32_t)0x00000020)
#define LVD_Threshold_2p33V                     ((uint32_t)0x00000030)
#define LVD_Threshold_2p44V                     ((uint32_t)0x00000040)
#define LVD_Threshold_2p56V                     ((uint32_t)0x00000050)
#define LVD_Threshold_2p67V                     ((uint32_t)0x00000060)
#define LVD_Threshold_2p78V                     ((uint32_t)0x00000070)
#define LVD_Threshold_2p89V                     ((uint32_t)0x00000080)
#define LVD_Threshold_3p0V                      ((uint32_t)0x00000090)
#define LVD_Threshold_3p11V                     ((uint32_t)0x000000A0)
#define LVD_Threshold_3p22V                     ((uint32_t)0x000000B0)
#define LVD_Threshold_3p33V                     ((uint32_t)0x000000C0)
#define LVD_Threshold_3p44V                     ((uint32_t)0x000000D0)
#define LVD_Threshold_3p56V                     ((uint32_t)0x000000E0)
#define LVD_Threshold_3p67V                     ((uint32_t)0x000000F0)

#define IS_LVD_THRESHOLD(THRESHOLD)             (((THRESHOLD) == LVD_Threshold_2p0V)  || \
                                                 ((THRESHOLD) == LVD_Threshold_2p11V) || \
                                                 ((THRESHOLD) == LVD_Threshold_2p22V) || \
                                                 ((THRESHOLD) == LVD_Threshold_2p33V) || \
                                                 ((THRESHOLD) == LVD_Threshold_2p44V) || \
                                                 ((THRESHOLD) == LVD_Threshold_2p56V) || \
                                                 ((THRESHOLD) == LVD_Threshold_2p67V) || \
                                                 ((THRESHOLD) == LVD_Threshold_2p78V) || \
                                                 ((THRESHOLD) == LVD_Threshold_2p89V) || \
                                                 ((THRESHOLD) == LVD_Threshold_3p0V)  || \
                                                 ((THRESHOLD) == LVD_Threshold_3p11V) || \
                                                 ((THRESHOLD) == LVD_Threshold_3p22V) || \
                                                 ((THRESHOLD) == LVD_Threshold_3p33V) || \
                                                 ((THRESHOLD) == LVD_Threshold_3p44V) || \
                                                 ((THRESHOLD) == LVD_Threshold_3p56V) || \
                                                 ((THRESHOLD) == LVD_Threshold_3p67V))

/** @defgroup LVD_Filter
  * @{
  */
#define LVD_Filter_Disable                      ((uint32_t)0x00000000)
#define LVD_Filter_Enable                       ((uint32_t)0x00000001)

#define IS_LVD_FILTER(FILTER)                   (((FILTER) == LVD_Filter_Disable) || \
                                                 ((FILTER) == LVD_Filter_Enable))

/** @defgroup LVD_FilterClk
  * @{
  */
#define LVD_FilterClk_RC150K                    ((uint32_t)0x00000000)
#define LVD_FilterClk_HSI                       ((uint32_t)0x00000010)

#define IS_LVD_FILTER_CLK(FILTER_CLK)           (((FILTER_CLK) == LVD_FilterClk_RC150K) || \
                                                 ((FILTER_CLK) == LVD_FilterClk_HSI))

/** @defgroup LVD_FilterTime
  * @{
  */
#define LVD_FilterTime_1Clk                     ((uint32_t)0x00000000)
#define LVD_FilterTime_3Clk                     ((uint32_t)0x00000002)
#define LVD_FilterTime_7Clk                     ((uint32_t)0x00000004)
#define LVD_FilterTime_15Clk                    ((uint32_t)0x00000006)
#define LVD_FilterTime_63Clk                    ((uint32_t)0x00000008)
#define LVD_FilterTime_255Clk                   ((uint32_t)0x0000000A)
#define LVD_FilterTime_1023Clk                  ((uint32_t)0x0000000C)
#define LVD_FilterTime_4095Clk                  ((uint32_t)0x0000000E)

#define IS_LVD_FILTER_TIME(FILTER_TIME)         (((FILTER_TIME) == LVD_FilterTime_1Clk) || \
                                                 ((FILTER_TIME) == LVD_FilterTime_3Clk) || \
                                                 ((FILTER_TIME) == LVD_FilterTime_7Clk) || \
                                                 ((FILTER_TIME) == LVD_FilterTime_15Clk) || \
                                                 ((FILTER_TIME) == LVD_FilterTime_63Clk) || \
                                                 ((FILTER_TIME) == LVD_FilterTime_255Clk) || \
                                                 ((FILTER_TIME) == LVD_FilterTime_1023Clk) || \
                                                 ((FILTER_TIME) == LVD_FilterTime_4095Clk))

/**
 ******************************************************************************
 ** @brief LVD配置
 ** \note
 ******************************************************************************/
typedef struct
{
    uint32_t    LVD_Action;       // LVD触发动作
    uint32_t    LVD_Source;       // LVD输入电压源
    uint32_t    LVD_Threshold;    // LVD阈值电压
    uint32_t    LVD_FilterEn;       // 是否使用输出滤波
    uint32_t    LVD_FilterClk;    // 滤波时钟源
    uint32_t    LVD_FilterTime;   // 输出滤波时间
} LVD_InitTypeDef;

/******************************************************************************
 * Global definitions
 ******************************************************************************/


/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//使能NVIC中LVD中断
void LVD_EnableNvic(uint8_t intPriority);
//禁止NVIC中LVD中断
void LVD_DisableNvic(void);
//配置LVD中断/系统复位触发方式
void LVD_TrigConfig(uint16_t LVD_TRIG, FunctionalState NewState);
//使能LVD中断
void LVD_EnableIrq(uint8_t intPriority);
//禁止LVD中断
void LVD_DisableIrq(void);

//清除LVD中断标志
void LVD_ClearIrq(void);
//获取LVD中断标志
boolean_t LVD_GetIrqStatus(void);
//获取LVD指定的状态位
FlagStatus LVD_GetFlagStatus(uint16_t LVD_FLAG);
//获取Filter结果
boolean_t LVD_GetFilterResult(void);

//LVD初始化
void LVD_Init(LVD_InitTypeDef *LVD_InitStruct);
//LVD去初始化
void LVD_DeInit(void);

//使能LVD
void LVD_Enable(void);
//停止LVD
void LVD_Disable(void);

//@} // LvdGroup

#ifdef __cplusplus
}
#endif

#endif /* __CW32F030_LVD_H */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
