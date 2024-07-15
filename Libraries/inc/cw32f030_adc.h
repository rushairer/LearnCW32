/**
* @file cw32f030_lvd.h
* @author WHXY
* @brief
* @version 0.1
* @date 2021-07-01
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

#ifndef __CW32F030_ADC_H
#define __CW32F030_ADC_H


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "base_types.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup AdcGroup AD Converter (ADC)
  **
 ******************************************************************************/

//@{

/******************************************************************************
 * Global definitions
 ******************************************************************************/
#define ADC_INT_PRIORITY                        ((uint32_t)3) /*ADC interrupt priority (lowest by default)  */

#define COEFF_TS                                (0.0924f)
#define ADDR_TRIM_1P5                           (0x0001260A)
#define ADDR_TRIM_2P5                           (0x0001260C)
#define ADDR_T0                                 (0x00012609)
/**
  * @}
  */

/** @defgroup ADC_interrupts_definition
  * @{
  */
#define ADC_IT_READY                            ((uint16_t)0x0080)
#define ADC_IT_OVW                              ((uint16_t)0x0040)
#define ADC_IT_WDTR                             ((uint16_t)0x0020)
#define ADC_IT_WDTH                             ((uint16_t)0x0010)
#define ADC_IT_WDTL                             ((uint16_t)0x0008)
#define ADC_IT_EOA                              ((uint16_t)0x0004)
#define ADC_IT_EOS                              ((uint16_t)0x0002)
#define ADC_IT_EOC                              ((uint16_t)0x0001)

#define IS_ADC_IT(IT)                           ((((IT) & (uint16_t)0xFF00) == 0x00) && ((IT) != 0x00))
#define IS_ADC_GET_IT(IT)                       (((IT) == ADC_IT_READY) || \
                                                 ((IT) == ADC_IT_OVW)   || \
                                                 ((IT) == ADC_IT_WDTR)  || \
                                                 ((IT) == ADC_IT_WDTH)  || \
                                                 ((IT) == ADC_IT_WDTL)  || \
                                                 ((IT) == ADC_IT_EOA)   || \
                                                 ((IT) == ADC_IT_EOS)   || \
                                                 ((IT) == ADC_IT_EOC))


/** @defgroup ADC external interrupts_definition
  * @{
  */
#define ADC_TRIG_DMA                            ((uint16_t)0x8000)
#define ADC_TRIG_I2C2                           ((uint16_t)0x4000)
#define ADC_TRIG_I2C1                           ((uint16_t)0x2000)
#define ADC_TRIG_SPI2                           ((uint16_t)0x1000)
#define ADC_TRIG_SPI1                           ((uint16_t)0x0800)
#define ADC_TRIG_UART3                          ((uint16_t)0x0400)
#define ADC_TRIG_UART2                          ((uint16_t)0x0200)
#define ADC_TRIG_UART1                          ((uint16_t)0x0100)
#define ADC_TRIG_BTIM3                          ((uint16_t)0x0080)
#define ADC_TRIG_BTIM2                          ((uint16_t)0x0040)
#define ADC_TRIG_BTIM1                          ((uint16_t)0x0020)
#define ADC_TRIG_GTIM4                          ((uint16_t)0x0010)
#define ADC_TRIG_GTIM3                          ((uint16_t)0x0008)
#define ADC_TRIG_GTIM2                          ((uint16_t)0x0004)
#define ADC_TRIG_GTIM1                          ((uint16_t)0x0002)
#define ADC_TRIG_ATIM                           ((uint16_t)0x0001)

#define IS_ADC_TRIG(TRIG)                       ((((TRIG) & (uint16_t)0x0000) == 0x00) && ((TRIG) != 0x00))
#define IS_ADC_GET_TRIG(TRIG)                   (((TRIG) == ADC_TRIG_DMA)|| \
                                                 ((TRIG) == ADC_TRIG_I2C2)  || \
                                                 ((TRIG) == ADC_TRIG_I2C1)  || \
                                                 ((TRIG) == ADC_TRIG_SPI2)  || \
                                                 ((TRIG) == ADC_TRIG_SPI1)  || \
                                                 ((TRIG) == ADC_TRIG_UART3) || \
                                                 ((TRIG) == ADC_TRIG_UART2) || \
                                                 ((TRIG) == ADC_TRIG_UART1) || \
                                                 ((TRIG) == ADC_TRIG_BTIM3) || \
                                                 ((TRIG) == ADC_TRIG_BTIM2) || \
                                                 ((TRIG) == ADC_TRIG_BTIM1) || \
                                                 ((TRIG) == ADC_TRIG_GTIM4) || \
                                                 ((TRIG) == ADC_TRIG_GTIM3) || \
                                                 ((TRIG) == ADC_TRIG_GTIM2) || \
                                                 ((TRIG) == ADC_TRIG_GTIM1) || \
                                                 ((TRIG) == ADC_TRIG_ATIM))


/******************************************************************************
 ** Global type definitions
 *****************************************************************************/

/** @defgroup ADC_OpMode
  * @{
  */
#define ADC_SingleChOneMode                     ((uint32_t)0x00000000)
#define ADC_SingleChMoreMode                    ((uint32_t)0x00000002)
#define ADC_SingleChContinuousMode              ((uint32_t)0x00000004)
#define ADC_SerialChContinuousMode              ((uint32_t)0x00000006)
#define ADC_SerialChScanMode                    ((uint32_t)0x00000008)
#define ADC_SerialChMoreMode                    ((uint32_t)0x0000000A)
#define ADC_SerialChBreakMode                   ((uint32_t)0x0000000C)


#define IS_ADC_OP_MODE(OP_MODE)                 (((OP_MODE) == ADC_SingleChOneMode)        || \
                                                 ((OP_MODE) == ADC_SingleChMoreMode)       || \
                                                 ((OP_MODE) == ADC_SingleChContinuousMode) || \
                                                 ((OP_MODE) == ADC_SerialChContinuousMode) || \
                                                 ((OP_MODE) == ADC_SerialChScanMode)       || \
                                                 ((OP_MODE) == ADC_SerialChMoreMode)       || \
                                                 ((OP_MODE) == ADC_SerialChBreakMode))


/** @defgroup ADC_ClkDiv
  * @{
  */
#define ADC_Clk_Div1                            ((uint32_t)0x00000000)
#define ADC_Clk_Div2                            ((uint32_t)0x00000100)
#define ADC_Clk_Div4                            ((uint32_t)0x00000200)
#define ADC_Clk_Div8                            ((uint32_t)0x00000300)
#define ADC_Clk_Div16                           ((uint32_t)0x00000400)
#define ADC_Clk_Div32                           ((uint32_t)0x00000500)
#define ADC_Clk_Div64                           ((uint32_t)0x00000600)
#define ADC_Clk_Div128                          ((uint32_t)0x00000700)

#define IS_ADC_CLK_DIV(CLK_DIV)                 (((CLK_DIV) == ADC_Clk_Div1)  || \
                                                 ((CLK_DIV) == ADC_Clk_Div2)  || \
                                                 ((CLK_DIV) == ADC_Clk_Div4)  || \
                                                 ((CLK_DIV) == ADC_Clk_Div8)  || \
                                                 ((CLK_DIV) == ADC_Clk_Div16) || \
                                                 ((CLK_DIV) == ADC_Clk_Div32) || \
                                                 ((CLK_DIV) == ADC_Clk_Div64) || \
                                                 ((CLK_DIV) == ADC_Clk_Div128))

/** @defgroup ADC_VrefSel
  * @{
  */
#define ADC_Vref_BGR1p5                         ((uint32_t)0x00000000)
#define ADC_Vref_BGR2p5                         ((uint32_t)0x00000040)
#define ADC_Vref_Extern1                        ((uint32_t)0x00000080)
#define ADC_Vref_VDDA                           ((uint32_t)0x000000C0)

#define IS_ADC_VREF_SEL(VREF_SEL)               (((VREF_SEL) == ADC_Vref_BGR1p5)  || \
                                                 ((VREF_SEL) == ADC_Vref_BGR2p5)  || \
                                                 ((VREF_SEL) == ADC_Vref_Extern1) || \
                                                 ((VREF_SEL) == ADC_Vref_VDDA))

/** @defgroup ADC_ChSel
  * @{
  * 通道0输入PA00
  * 通道1输入PA01
  * 通道2输入PA02
  * 通道3输入PA03
  * 通道4输入PA04
  * 通道5输入PA05
  * 通道6输入PA06
  * 通道7输入PA07
  * 通道8输入PB00
  * 通道9输入PB01
  * 通道10输入PB02
  * 通道11输入PB10
  * 通道12输入PB11
  * 1/3 VDDA(必须使用输入增益)
  * BGR_TS(必须使用输入增益)
  * Vref1P2(必须使用输入增益)
  */
#define ADC_ExInputCH0                          ((uint32_t)0x00000000)
#define ADC_ExInputCH1                          ((uint32_t)0x00000001)
#define ADC_ExInputCH2                          ((uint32_t)0x00000002)
#define ADC_ExInputCH3                          ((uint32_t)0x00000003)
#define ADC_ExInputCH4                          ((uint32_t)0x00000004)
#define ADC_ExInputCH5                          ((uint32_t)0x00000005)
#define ADC_ExInputCH6                          ((uint32_t)0x00000006)
#define ADC_ExInputCH7                          ((uint32_t)0x00000007)
#define ADC_ExInputCH8                          ((uint32_t)0x00000008)
#define ADC_ExInputCH9                          ((uint32_t)0x00000009)
#define ADC_ExInputCH10                         ((uint32_t)0x0000000A)
#define ADC_ExInputCH11                         ((uint32_t)0x0000000B)
#define ADC_ExInputCH12                         ((uint32_t)0x0000000C)
#define ADC_VddaDiV3Input                       ((uint32_t)0x0000000D)
#define ADC_TsInput                             ((uint32_t)0x0000000E)
#define ADC_Vref1P2Input                        ((uint32_t)0x0000000F)

#define IS_ADC_CH_SEL(CH_SEL)                   (((CH_SEL) == ADC_ExInputCH0)    || \
                                                 ((CH_SEL) == ADC_ExInputCH1)    || \
                                                 ((CH_SEL) == ADC_ExInputCH2)    || \
                                                 ((CH_SEL) == ADC_ExInputCH3)    || \
                                                 ((CH_SEL) == ADC_ExInputCH4)    || \
                                                 ((CH_SEL) == ADC_ExInputCH5)    || \
                                                 ((CH_SEL) == ADC_ExInputCH6)    || \
                                                 ((CH_SEL) == ADC_ExInputCH7)    || \
                                                 ((CH_SEL) == ADC_ExInputCH8)    || \
                                                 ((CH_SEL) == ADC_ExInputCH9)    || \
                                                 ((CH_SEL) == ADC_ExInputCH10)   || \
                                                 ((CH_SEL) == ADC_ExInputCH11)   || \
                                                 ((CH_SEL) == ADC_ExInputCH12)   || \
                                                 ((CH_SEL) == ADC_VddaDiV3Input) || \
                                                 ((CH_SEL) == ADC_TsInput)       || \
                                                 ((CH_SEL) == ADC_Vref1P2Input))

/** @defgroup ADC_SampleTime
  * @{
  */
#define ADC_SampTime5Clk                        ((uint32_t)0x00000000)
#define ADC_SampTime6Clk                        ((uint32_t)0x00000800)
#define ADC_SampTime8Clk                        ((uint32_t)0x00001000)
#define ADC_SampTime10Clk                       ((uint32_t)0x00001800)

#define IS_ADC_SAMPLE_TIME(SAMPLE_TIME)         (((SAMPLE_TIME) == ADC_SampTime5Clk) || \
                                                 ((SAMPLE_TIME) == ADC_SampTime6Clk) || \
                                                 ((SAMPLE_TIME) == ADC_SampTime8Clk) || \
                                                 ((SAMPLE_TIME) == ADC_SampTime10Clk))



/** @defgroup ADC_TrigSel
  * @{
  */
#define ADC_TrigATimerDisable                   ((uint32_t)0x00000000)
#define ADC_TrigATimerEnable                    ((uint32_t)0x00000001)

#define ADC_TrigGTimer1Disable                  ((uint32_t)0x00000000)
#define ADC_TrigGTimer1Enable                   ((uint32_t)0x00000002)

#define ADC_TrigGTimer2Disable                  ((uint32_t)0x00000000)
#define ADC_TrigGTimer2Enable                   ((uint32_t)0x00000004)

#define ADC_TrigGTimer3Disable                  ((uint32_t)0x00000000)
#define ADC_TrigGTimer3Enable                   ((uint32_t)0x00000008)

#define ADC_TrigGTimer4Disable                  ((uint32_t)0x00000000)
#define ADC_TrigGTimer4Enable                   ((uint32_t)0x00000010)

#define ADC_TrigBTimer1Disable                  ((uint32_t)0x00000000)
#define ADC_TrigBTimer1Enable                   ((uint32_t)0x00000020)

#define ADC_TrigBTimer2Disable                  ((uint32_t)0x00000000)
#define ADC_TrigBTimer2Enable                   ((uint32_t)0x00000040)

#define ADC_TrigBTimer3Disable                  ((uint32_t)0x00000000)
#define ADC_TrigBTimer3Enable                   ((uint32_t)0x00000080)

#define ADC_TrigUart1Disable                    ((uint32_t)0x00000000)
#define ADC_TrigUart1Enable                     ((uint32_t)0x00000100)

#define ADC_TrigUart2Disable                    ((uint32_t)0x00000000)
#define ADC_TrigUart2Enable                     ((uint32_t)0x00000200)

#define ADC_TrigUart3Disable                    ((uint32_t)0x00000000)
#define ADC_TrigUart3Enable                     ((uint32_t)0x00000400)

#define ADC_TrigSPI1Disable                     ((uint32_t)0x00000000)
#define ADC_TrigSPI1Enable                      ((uint32_t)0x00000800)

#define ADC_TrigSPI2Disable                     ((uint32_t)0x00000000)
#define ADC_TrigSPI2Enable                      ((uint32_t)0x00001000)

#define ADC_TrigI2C1Disable                     ((uint32_t)0x00000000)
#define ADC_TrigI2C1Enable                      ((uint32_t)0x00002000)

#define ADC_TrigI2C2Disable                     ((uint32_t)0x00000000)
#define ADC_TrigI2C2Enable                      ((uint32_t)0x00004000)

#define ADC_TrigDMADisable                      ((uint32_t)0x00000000)
#define ADC_TrigDMAEnable                       ((uint32_t)0x00008000)

#define IS_ADC_TRIG_SEL(TRIG_SEL)               (((TRIG_SEL) == ADC_TrigATimerDisable)  || \
                                                 ((TRIG_SEL) == ADC_TrigATimerEnable)   || \
                                                 ((TRIG_SEL) == ADC_TrigGTimer1Disable) || \
                                                 ((TRIG_SEL) == ADC_TrigGTimer1Enable)  || \
                                                 ((TRIG_SEL) == ADC_TrigGTimer2Disable) || \
                                                 ((TRIG_SEL) == ADC_TrigGTimer2Enable)  || \
                                                 ((TRIG_SEL) == ADC_TrigGTimer3Disable) || \
                                                 ((TRIG_SEL) == ADC_TrigGTimer3Enable)  || \
                                                 ((TRIG_SEL) == ADC_TrigGTimer4Disable) || \
                                                 ((TRIG_SEL) == ADC_TrigGTimer4Enable)  || \
                                                 ((TRIG_SEL) == ADC_TrigBTimer1Disable) || \
                                                 ((TRIG_SEL) == ADC_TrigBTimer1Enable)  || \
                                                 ((TRIG_SEL) == ADC_TrigBTimer2Disable) || \
                                                 ((TRIG_SEL) == ADC_TrigBTimer2Enable)  || \
                                                 ((TRIG_SEL) == ADC_TrigBTimer3Disable) || \
                                                 ((TRIG_SEL) == ADC_TrigBTimer3Enable)  || \
                                                 ((TRIG_SEL) == ADC_TrigUart1Disable)   || \
                                                 ((TRIG_SEL) == ADC_TrigUart1Enable)    || \
                                                 ((TRIG_SEL) == ADC_TrigUart2Disable)   || \
                                                 ((TRIG_SEL) == ADC_TrigUart2Enable)    || \
                                                 ((TRIG_SEL) == ADC_TrigUart3Disable)   || \
                                                 ((TRIG_SEL) == ADC_TrigUart3Enable)    || \
                                                 ((TRIG_SEL) == ADC_TrigSPI1Disable)    || \
                                                 ((TRIG_SEL) == ADC_TrigSPI1Enable)     || \
                                                 ((TRIG_SEL) == ADC_TrigSPI2Disable)    || \
                                                 ((TRIG_SEL) == ADC_TrigSPI2Enable)     || \
                                                 ((TRIG_SEL) == ADC_TrigI2C1Disable)    || \
                                                 ((TRIG_SEL) == ADC_TrigI2C1Enable)     || \
                                                 ((TRIG_SEL) == ADC_TrigI2C2Disable)    || \
                                                 ((TRIG_SEL) == ADC_TrigI2C2Enable)     || \
                                                 ((TRIG_SEL) == ADC_TrigDMADisable)     || \
                                                 ((TRIG_SEL) == ADC_TrigDMAEnable))



/** @defgroup ADC_SqrEns
  * @{
  */
#define ADC_SqrEns0                             ((uint32_t)0x00000000)
#define ADC_SqrEns01                            ((uint32_t)0x00010000)
#define ADC_SqrEns02                            ((uint32_t)0x00020000)
#define ADC_SqrEns03                            ((uint32_t)0x00030000)

#define IS_ADC_SQR_ENS(SQR_ENS)                 (((SQR_ENS) == ADC_SqrEns0)  || \
                                                 ((SQR_ENS) == ADC_SqrEns01) || \
                                                 ((SQR_ENS) == ADC_SqrEns02) || \
                                                 ((SQR_ENS) == ADC_SqrEns03))



/** @defgroup ADC_SqrChmux
  * @{
  * 通道0输入PA00
  * 通道1输入PA01
  * 通道2输入PA02
  * 通道3输入PA03
  * 通道4输入PA04
  * 通道5输入PA05
  * 通道6输入PA06
  * 通道7输入PA07
  * 通道8输入PB00
  * 通道9输入PB01
  * 通道10输入PB02
  * 通道11输入PB10
  * 通道12输入PB11
  * 1/3 VDDA(必须使用输入增益)
  * BGR_TS(必须使用输入增益)
  * Vref1P2(必须使用输入增益)
  */
#define ADC_SqrCh0                              ((uint32_t)0x00000000)
#define ADC_SqrCh1                              ((uint32_t)0x00000001)
#define ADC_SqrCh2                              ((uint32_t)0x00000002)
#define ADC_SqrCh3                              ((uint32_t)0x00000003)
#define ADC_SqrCh4                              ((uint32_t)0x00000004)
#define ADC_SqrCh5                              ((uint32_t)0x00000005)
#define ADC_SqrCh6                              ((uint32_t)0x00000006)
#define ADC_SqrCh7                              ((uint32_t)0x00000007)
#define ADC_SqrCh8                              ((uint32_t)0x00000008)
#define ADC_SqrCh9                              ((uint32_t)0x00000009)
#define ADC_SqrCh10                             ((uint32_t)0x0000000A)
#define ADC_SqrCh11                             ((uint32_t)0x0000000B)
#define ADC_SqrCh12                             ((uint32_t)0x0000000C)
#define ADC_SqrVddaDiV3                         ((uint32_t)0x0000000D)
#define ADC_SqrTs                               ((uint32_t)0x0000000E)
#define ADC_SqrVref1P2                          ((uint32_t)0x0000000F)

#define IS_ADC_SQR_CH(SQR_CH)                   (((SQR_CH) == ADC_SqrCh0)      || \
                                                 ((SQR_CH) == ADC_SqrCh1)      || \
                                                 ((SQR_CH) == ADC_SqrCh2)      || \
                                                 ((SQR_CH) == ADC_SqrCh3)      || \
                                                 ((SQR_CH) == ADC_SqrCh4)      || \
                                                 ((SQR_CH) == ADC_SqrCh5)      || \
                                                 ((SQR_CH) == ADC_SqrCh6)      || \
                                                 ((SQR_CH) == ADC_SqrCh7)      || \
                                                 ((SQR_CH) == ADC_SqrCh8)      || \
                                                 ((SQR_CH) == ADC_SqrCh9)      || \
                                                 ((SQR_CH) == ADC_SqrCh10)     || \
                                                 ((SQR_CH) == ADC_SqrCh11)     || \
                                                 ((SQR_CH) == ADC_SqrCh12)     || \
                                                 ((SQR_CH) == ADC_SqrVddaDiV3) || \
                                                 ((SQR_CH) == ADC_SqrTs)       || \
                                                 ((SQR_CH) == ADC_SqrVref1P2))



/** @defgroup ADC_WdtChmux
  * @{
  * 通道0输入PA00
  * 通道1输入PA01
  * 通道2输入PA02
  * 通道3输入PA03
  * 通道4输入PA04
  * 通道5输入PA05
  * 通道6输入PA06
  * 通道7输入PA07
  * 通道8输入PB00
  * 通道9输入PB01
  * 通道10输入PB02
  * 通道11输入PB10
  * 通道12输入PB11
  * 1/3 VDDA(必须使用输入增益)
  * BGR_TS(必须使用输入增益)
  * Vref1P2(必须使用输入增益)
  */
#define ADC_WdtCh0                              ((uint32_t)0x00000000)
#define ADC_WdtCh1                              ((uint32_t)0x00000100)
#define ADC_WdtCh2                              ((uint32_t)0x00000200)
#define ADC_WdtCh3                              ((uint32_t)0x00000300)
#define ADC_WdtCh4                              ((uint32_t)0x00000400)
#define ADC_WdtCh5                              ((uint32_t)0x00000500)
#define ADC_WdtCh6                              ((uint32_t)0x00000600)
#define ADC_WdtCh7                              ((uint32_t)0x00000700)
#define ADC_WdtCh8                              ((uint32_t)0x00000800)
#define ADC_WdtCh9                              ((uint32_t)0x00000900)
#define ADC_WdtCh10                             ((uint32_t)0x00000A00)
#define ADC_WdtCh11                             ((uint32_t)0x00000B00)
#define ADC_WdtCh12                             ((uint32_t)0x00000C00)
#define ADC_WdtVddaDiV3                         ((uint32_t)0x00000D00)
#define ADC_WdtTs                               ((uint32_t)0x00000E00)
#define ADC_WdtVref1P2                          ((uint32_t)0x00000F00)

#define IS_ADC_WDT_CH(WDT_CH)                   (((WDT_CH) == ADC_WdtCh0)      || \
                                                 ((WDT_CH) == ADC_WdtCh1)      || \
                                                 ((WDT_CH) == ADC_WdtCh2)      || \
                                                 ((WDT_CH) == ADC_WdtCh3)      || \
                                                 ((WDT_CH) == ADC_WdtCh4)      || \
                                                 ((WDT_CH) == ADC_WdtCh5)      || \
                                                 ((WDT_CH) == ADC_WdtCh6)      || \
                                                 ((WDT_CH) == ADC_WdtCh7)      || \
                                                 ((WDT_CH) == ADC_WdtCh8)      || \
                                                 ((WDT_CH) == ADC_WdtCh9)      || \
                                                 ((WDT_CH) == ADC_WdtCh10)     || \
                                                 ((WDT_CH) == ADC_WdtCh11)     || \
                                                 ((WDT_CH) == ADC_WdtCh12)     || \
                                                 ((WDT_CH) == ADC_WdtVddaDiV3) || \
                                                 ((WDT_CH) == ADC_WdtTs)       || \
                                                 ((WDT_CH) == ADC_WdtVref1P2))


/** @defgroup ADC_WdtAll
  * @{
  */
#define ADC_WdtDisable                          ((uint32_t)0x00000000)
#define ADC_WdtEnable                           ((uint32_t)0x00002000)

#define IS_ADC_WDT_EN(WDT_EN)                   (((WDT_EN) == ADC_WdtDisable) || \
                                                 ((WDT_EN) == ADC_WdtEnable))

/** @defgroup ADC_WdtrIrq
  * @{
  */
#define ADC_WdtrDisable                         ((uint32_t)0x00000000)
#define ADC_WdtrEnable                          ((uint32_t)0x00000020)

#define IS_ADC_WDTR_EN(WDTR_EN)                 (((WDTR_EN) == ADC_WdtrDisable) || \
                                                 ((WDTR_EN) == ADC_WdtrEnable))

/** @defghoup ADC_WdthIrq
  * @{
  */
#define ADC_WdthDisable                         ((uint32_t)0x00000000)
#define ADC_WdthEnable                          ((uint32_t)0x00000010)

#define IS_ADC_WDTH_EN(WDTH_EN)                 (((WDTH_EN) == ADC_WdthDisable) || \
                                                 ((WDTH_EN) == ADC_WdthEnable))

/** @defgloup ADC_WdtlIrq
  * @{
  */
#define ADC_WdtlDisable                         ((uint32_t)0x00000000)
#define ADC_WdtlEnable                          ((uint32_t)0x00000008)

#define IS_ADC_WDTL_EN(WDTL_EN)                 (((WDTL_EN) == ADC_WdtlDisable) || \
                                                 ((WDTL_EN) == ADC_WdtlEnable))



/** @defgroup ADC_Align
  * @{
  */
#define ADC_AlignRight                          ((uint32_t)0x00000000)
#define ADC_AlignLeft                           ((uint32_t)0x00000040)

#define IS_ADC_DATA_ALIGN(DATA_ALIGN)           (((DATA_ALIGN) == ADC_AlignRight)|| \
                                                 ((DATA_ALIGN) == ADC_AlignLeft))



/** @defgroup ADC_DataDiscard
  * @{
  */
#define ADC_DiscardNull                         ((uint32_t)0x00000000)
#define ADC_DiscardEnable                       ((uint32_t)0x00000020)

#define IS_ADC_DATA_DISCARD(DATA_DISCARD)       (((DATA_DISCARD) == ADC_DiscardNull) || \
                                                 ((DATA_DISCARD) == ADC_DiscardEnable))



/** @defgroup ADC_TsEn
  * @{
  */
#define ADC_TsDisable                           ((uint32_t)0x00000000)
#define ADC_TsEnable                            ((uint32_t)0x00000020)

#define IS_ADC_TS_ENABLE(TS_ENABLE)             (((TS_ENABLE) == ADC_TsDisable) || \
                                                 ((TS_ENABLE) == ADC_TsEnable))

/** @defgroup ADC_InBufEn
  * @{
  */
#define ADC_BufDisable                          ((uint32_t)0x00000000)
#define ADC_BufEnable                           ((uint32_t)0x00002000)

#define IS_ADC_BUF_ENABLE(BUF_ENABLE)           (((BUF_ENABLE) == ADC_BufDisable) || \
                                                 ((BUF_ENABLE) == ADC_BufEnable))

/** @defgroup ADC_DMAEn
  * @{
  */
#define ADC_DmaDisable                          ((uint32_t)0x00000000)
#define ADC_DmaEnable                           ((uint32_t)0x00000080)

#define IS_ADC_DMA_ENABLE(DMA_ENABLE)           (((DMA_ENABLE) == ADC_DmaDisable) || \
                                                 ((DMA_ENABLE) == ADC_DmaEnable))

/** @defgroup ADC_AccEn
  * @{
  */
#define ADC_AccDisable                          ((uint32_t)0x00000000)
#define ADC_AccEnable                           ((uint32_t)0x00000100)

#define IS_ADC_ACC_ENABLE(ACC_ENABLE)           (((ACC_ENABLE) == ADC_AccDisable) || \
                                                 ((ACC_ENABLE) == ADC_AccEnable))



/** @defgroup ADC_AutoStop
  * @{
  */
#define ADC_AutoStopDisable                     ((uint32_t)0x00000000)
#define ADC_AutoStopEnable                      ((uint32_t)0x00000002)

#define IS_ADC_AUTO_STOP(AUTO_STOP)             (((AUTO_STOP) == ADC_AutoStopDisable) || \
                                                 ((AUTO_STOP) == ADC_AutoStopEnable))

/******************************************************************************
 * Extern type definitions ('typedef')                                        *
 ******************************************************************************/

/**
 ******************************************************************************
 ** @brief  ADC配置
 *****************************************************************************/
typedef struct
{
    uint32_t           ADC_OpMode;            /*ADC操作模式*/

    uint32_t           ADC_ClkDiv;            /*ADC时钟选择*/

    uint32_t           ADC_SampleTime;        /*ADC采样时间*/

    uint32_t           ADC_VrefSel;           /*ADC参考电压*/

    uint32_t           ADC_InBufEn;           /*ADC输入增益使能*/

    uint32_t           ADC_TsEn;              /*内置温度传感器使能*/

    uint32_t           ADC_DMAEn;             /*ADC转换完成触发DMA使能*/

    uint32_t           ADC_Align;             /*ADC转换结果对齐方式*/

    uint32_t           ADC_AccEn;             /*转换结果累加使能*/
} ADC_InitTypeDef;

/**
 ******************************************************************************
 ** @brief  ADC模拟看门狗配置
 *****************************************************************************/
typedef struct
{
    uint32_t             ADC_WdtCh;    /*ADC模拟看门狗通道*/

    uint32_t             ADC_WdtAll;   /*ADC模拟看门狗使能*/

    uint32_t             ADC_WdtrIrq;  /*ADC区间模拟看门狗使能*/

    uint32_t             ADC_WdthIrq;  /*ADC上超出模拟看门狗使能*/

    uint32_t             ADC_WdtlIrq;  /*ADC下超出模拟看门狗使能*/

    uint32_t             ADC_Vth;      /*ADC模拟看门狗上阈值*/

    uint32_t             ADC_Vtl;      /*ADC模拟看门狗下阈值*/
} ADC_WdtTypeDef;

/**
 ******************************************************************************
 ** @brief  ADC单通道配置
 *****************************************************************************/
typedef struct
{
    uint32_t             ADC_Chmux;            /*ADC单通道转换模式待转换通道*/

    uint32_t             ADC_DiscardEn;        /*单通道ADC转换结果保存策略配置*/

    ADC_InitTypeDef      ADC_InitStruct;       /*ADC初始化*/

    ADC_WdtTypeDef       ADC_WdtStruct;        /*ADC模拟看门狗配置*/
} ADC_SingleChTypeDef;

/**
 ******************************************************************************
 ** @brief  ADC序列配置
 *****************************************************************************/
typedef struct
{
    uint32_t              ADC_SqrEns;            /*ADC序列转换的序列配置*/

    uint32_t              ADC_Sqr3Chmux;         /*ADC序列3待转换通道*/

    uint32_t              ADC_Sqr2Chmux;         /*ADC序列2待转换通道*/

    uint32_t              ADC_Sqr1Chmux;         /*ADC序列1待转换通道*/

    uint32_t              ADC_Sqr0Chmux;         /*ADC序列0待转换通道*/

    ADC_InitTypeDef       ADC_InitStruct;        /*ADC初始化*/
} ADC_SerialChTypeDef;


/**
 ******************************************************************************
 ** @brief  ADC中断配置
 *****************************************************************************/
typedef struct
{
    boolean_t     ADC_ReadyFlag;      /*ADC初始化完成标志*/

    boolean_t     ADC_OvwIrq;         /*ADC转换结果溢出中断*/

    boolean_t     ADC_WdtrIrq;        /*ADC模拟看门狗区间中断*/

    boolean_t     ADC_WdthIrq;        /*ADC模拟看门狗上阈值中断*/

    boolean_t     ADC_WdtlIrq;        /*ADC模拟看门狗下阈值中断*/

    boolean_t     ADC_EoaIrq;         /*ADC多次转换完成中断*/

    boolean_t     ADC_EosIrq;         /*ADC序列转换完成中断*/

    boolean_t     ADC_EocIrq;         /*ADC单次转换完成中断*/
} ADC_IrqTypeDef;





/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//ADC去初始化
void ADC_DeInit(void);
//ADC初始化
void ADC_Init(ADC_InitTypeDef *ADC_InitStruct);
//ADC默认值初始化
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct);
//ADC模拟看门狗默认值初始化
void ADC_WdtInit(ADC_WdtTypeDef *ADC_WdtStruct);
//ADC使能
void ADC_Enable(void);
//ADC禁用
void ADC_Disable(void);

//触发DMA读取命令
void ADC_DMACmd(FunctionalState NewState);
//触发DMA读取使能
void ADC_DMAEnable(void);
//触发DMA读取禁止
void ADC_DMADisable(void);

//ADC转换软件启动命令
void ADC_SoftwareStartConvCmd(FunctionalState NewState);
//ADC外部中断触发源配置
void ADC_ExtTrigCfg(uint16_t ADC_TRIG, FunctionalState NewState);

//单通道转换模式公共配置
void ADC_SingleChCommon(ADC_SingleChTypeDef *ADC_SingleChStruct);
//ADC单通道单次转换模式配置
void ADC_SingleChOneModeCfg(ADC_SingleChTypeDef *ADC_SingleChStruct);
//ADC单通道多次转换模式配置
void ADC_SingleChMoreModeCfg(ADC_SingleChTypeDef *ADC_SingleChStruct, uint8_t cntAdcSample);
//ADC单通道连续转换模式配置
void ADC_SingleChContinuousModeCfg(ADC_SingleChTypeDef *ADC_SingleChStruct);
//ADC序列转换模式公共配置
void ADC_SerialChCommon(ADC_SerialChTypeDef *ADC_SerialChStruct);
//ADC序列连续转换模式配置
void ADC_SerialChContinuousModeCfg(ADC_SerialChTypeDef *ADC_SerialChStruct);
//ADC序列扫描转换模式配置
void ADC_SerialChScanModeCfg(ADC_SerialChTypeDef *ADC_SerialChStruct);
//ADC序列多次转换模式配置
void ADC_SerialChMoreModeCfg(ADC_SerialChTypeDef *ADC_SerialChStruct, uint8_t cntAdcSample);
//ADC序列断续转换模式配置
void ADC_SerialChBreakModeCfg(ADC_SerialChTypeDef *ADC_SerialChStruct);

//序列SQR0转换通道配置
void ADC_Sqr0ChannelCfg(ADC_SerialChTypeDef *ADC_SerialChStruct);
//序列SQR0/SQR1转换通道配置
void ADC_Sqr01ChannelCfg(ADC_SerialChTypeDef *ADC_SerialChStruct);
//序列SQR0~SQR2转换通道配置
void ADC_Sqr02ChannelCfg(ADC_SerialChTypeDef *ADC_SerialChStruct);
//序列SQR0~SQR3转换通道配置
void ADC_Sqr03ChannelCfg(ADC_SerialChTypeDef *ADC_SerialChStruct);

//单通道模式的内置跟随器使能
void ADC_BufEnSingleCh(uint32_t enAdcSampCh);
//序列模式的内置跟随器使能
void ADC_BufEnSerialCh(uint32_t enAdcSampCh);

//ADC模拟看门狗配置
void ADC_WdtConfig(ADC_WdtTypeDef *ADC_WdtStruct);

//ADC中断配置
void ADC_ITConfig(uint16_t ADC_IT, FunctionalState NewState);
//ADC中断使能
void ADC_EnableIrq(uint8_t intPriority);
//ADC中断禁止
void ADC_DisableIrq(void);
//使能NVIC中ADC中断
void ADC_EnableNvic(uint8_t intPriority);
//禁用NVIC中ADC中断
void ADC_DisableNvic(void);
//获取ADC所有中断状态
void ADC_GetITStatusAll(volatile uint8_t *pFlagAdcIrq);
//获取ADC指定的中断状态
ITStatus ADC_GetITStatus(uint16_t ADC_IT);
//清除ADC所有中断状态
void ADC_ClearITPendingAll(void);
//清除ADC指定的中断状态
void ADC_ClearITPendingBit(uint16_t ADC_IT);

//获取单次转换采样值
uint16_t ADC_GetConversionValue(void);
//获取SQR0通道采样值
void ADC_GetSqr0Result(uint16_t *pAdcResult);
//获取SQR1通道采样值
void ADC_GetSqr1Result(uint16_t *pAdcResult);
//获取SQR2通道采样值
void ADC_GetSqr2Result(uint16_t *pAdcResult);
//获取SQR3通道采样值
void ADC_GetSqr3Result(uint16_t *pAdcResult);
//获取累加采样值
void ADC_GetAccResult(uint32_t *pAdcAccResult);
//清零累加采样值
void ADC_ClrAccResult(void);

//设置参考电压
void ADC_SetVref(uint32_t ADC_VrefSel);
//设置结果对齐方式
void ADC_SetAlign(uint32_t enAlign);
//设置单通道ADC转换结果溢出保存策略
void ADC_SetDiscard(uint32_t enDiscard);
//设置内置温度传感器使能控制
void ADC_SetTs(uint32_t enTs);
//读取ADC参考电压1.5V时的温度传感器的测量温度
void ADC_GetTsVref1V5(float *fAdcTsDegree);
//读取ADC参考电压2.5V时的温度传感器的测量温度
void ADC_GetTsVref2V5(float *fAdcTsDegree);
//设置ADC转换结束自动停止
void ADC_AutoStop(uint32_t enAutoStop);
//@}
#ifdef __cplusplus
}
#endif

#endif /* __CW32F030_ADC_H */
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
