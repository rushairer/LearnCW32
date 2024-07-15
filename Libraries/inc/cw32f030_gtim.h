/**
 * @file cw32f030_gtim.h
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-04-26
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CW32F030_GTIM_H
#define __CW32F030_GTIM_H


#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "base_types.h"
#include "cw32f030.h"

/******************************************************************************
 * type definitions ('typedef')
 ******************************************************************************/

/**
 * @brief GTIM 基础初始化参数
 */
typedef struct
{
    uint32_t Mode;                          /*!< GTIM的模式选择。 */
    uint32_t OneShotMode;                   /*!< GTIM的单次/连续计数模式选择。 */
    FunctionalState ToggleOutState;         /*!< GTIM的翻转输出使能选择。 */
    uint32_t Prescaler;                     /*!< GTIM的预分频系数。 */
    uint32_t ReloadValue;                   /*!< GTIM的重载值。 */
} GTIM_InitTypeDef;

/**
 * @brief GTIM 编码器模式下的初始化参数
 */

typedef struct
{
    uint32_t EncodeMode;
    uint32_t EncodeResetMode;
    uint32_t EncodeReloadMode;
    uint32_t CH1Filter;
    uint32_t CH2Filter;
    uint32_t CH3Filter;
    uint32_t CH1Invert;
    uint32_t CH2Invert;
    uint32_t CH3Invert;
} GTIM_EncodeInitTypeDef;

/**
 * @brief GTIM 输入捕获的配置参数
 */
typedef struct
{
    uint32_t CHx;
    uint32_t ICPolarity;
    uint32_t ICFilter;
    uint32_t ICInvert;
} GTIM_ICInitTypeDef;

/******************************************************************************
 * pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IS_GTIM_DEFINE(GTIMx)                   (((GTIMx) == CW_GTIM1) || \
                                                 ((GTIMx) == CW_GTIM2) || \
                                                 ((GTIMx) == CW_GTIM3) || \
                                                 ((GTIMx) == CW_GTIM4))


#define GTIM_MODE_TIME                          (0UL)
#define GTIM_MODE_COUNTER                       (1UL << 1)
#define GTIM_MODE_TRIGGER                       (2UL << 1)
#define GTIM_MODE_GATE                          (3UL << 1)
#define IS_GTIM_MODE(MODE)                      (((MODE) == GTIM_MODE_TIME) || \
                                                 ((MODE) == GTIM_MODE_COUNTER) || \
                                                 ((MODE) == GTIM_MODE_TRIGGER) || \
                                                 ((MODE) == GTIM_MODE_GATE))

#define GTIM_TRIGGER_ETR                        (0UL)
#define GTIM_TRIGGER_ITR                        (1UL <<3)
#define IS_GTIM_TRS(MODE)                       (((MODE) == GTIM_TRIGGER_ETR) || \
                                                 ((MODE) == GTIM_TRIGGER_ITR))

#define ITR_SOURCE_BTIM1                        (0UL)
#define ITR_SOURCE_BTIM2                        (1UL)
#define ITR_SOURCE_BTIM3                        (2UL)
#define ITR_SOURCE_GTIM1                        (3UL)
#define ITR_SOURCE_GTIM2                        (4UL)
#define ITR_SOURCE_GTIM3                        (5UL)
#define ITR_SOURCE_GTIM4                        (6UL)
#define ITR_SOURCE_ATIM                         (7UL)
#define IS_ITR_SOURCE(ITR)                      (((ITR) == ITR_SOURCE_BTIM1) || \
                                                 ((ITR) == ITR_SOURCE_BTIM2) || \
                                                 ((ITR) == ITR_SOURCE_BTIM3) || \
                                                 ((ITR) == ITR_SOURCE_GTIM1) || \
                                                 ((ITR) == ITR_SOURCE_GTIM2) || \
                                                 ((ITR) == ITR_SOURCE_GTIM3) || \
                                                 ((ITR) == ITR_SOURCE_GTIM4) || \
                                                 ((ITR) == ITR_SOURCE_ATIM))

#define GTIM_ETR_POL_RISE_HIGH                  (0UL)
#define GTIM_ETR_POL_FALL_LOW                   (1UL << 4)
#define IS_GTIM_ETR_POL(MODE)                   (((MODE) == GTIM_ETR_POL_RISE_HIGH) || \
                                                 ((MODE) == GTIM_ETR_POL_FALL_LOW))

#define GTIM_COUNT_CONTINUE                     (0UL)
#define GTIM_COUNT_ONESHOT                      (1UL << 5)
#define IS_GTIM_ONESHOT(MODE)                   (((MODE) == GTIM_COUNT_CONTINUE) || \
                                                 ((MODE) == GTIM_COUNT_ONESHOT))

#define GTIM_PRESCALER_DIV1                     (0UL)
#define GTIM_PRESCALER_DIV2                     (1UL << 7)
#define GTIM_PRESCALER_DIV4                     (2UL << 7)
#define GTIM_PRESCALER_DIV8                     (3UL << 7)
#define GTIM_PRESCALER_DIV16                    (4UL << 7)
#define GTIM_PRESCALER_DIV32                    (5UL << 7)
#define GTIM_PRESCALER_DIV64                    (6UL << 7)
#define GTIM_PRESCALER_DIV128                   (7UL << 7)
#define GTIM_PRESCALER_DIV256                   (8UL << 7)
#define GTIM_PRESCALER_DIV512                   (9UL << 7)
#define GTIM_PRESCALER_DIV1024                  (10UL << 7)
#define GTIM_PRESCALER_DIV2048                  (11UL << 7)
#define GTIM_PRESCALER_DIV4096                  (12UL << 7)
#define GTIM_PRESCALER_DIV8192                  (13UL << 7)
#define GTIM_PRESCALER_DIV16384                 (14UL << 7)
#define GTIM_PRESCALER_DIV32768                 (15UL << 7)
#define IS_GTIM_PRESCALER(DIV)                  (((DIV) == GTIM_PRESCALER_DIV1) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV2) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV4) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV8) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV16) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV32) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV64) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV128) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV256) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV512) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV1024) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV2048) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV4096) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV8192) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV16384) || \
                                                 ((DIV) == GTIM_PRESCALER_DIV32768))

#define GTIM_ENCODE_MODE0                       (0UL)
#define GTIM_ENCODE_MODE1                       (1UL << 15)
#define GTIM_ENCODE_MODE2                       (2UL << 15)
#define GTIM_ENCODE_MODE3                       (3UL << 15)
#define IS_GTIM_ENCODE_MODE(MODE)               (((MODE) == GTIM_ENCODE_MODE0) || \
                                                 ((MODE) == GTIM_ENCODE_MODE1) || \
                                                 ((MODE) == GTIM_ENCODE_MODE2) || \
                                                 ((MODE) == GTIM_ENCODE_MODE3))

#define GTIM_ENCODE_RESET_NONE                  (0UL)
#define GTIM_ENCODE_RESET_RISE                  (1UL << 17)
#define GTIM_ENCODE_RESET_FALL                  (2UL << 17)
#define IS_GTIM_ENCODE_RESET(MODE)              (((MODE) == GTIM_ENCODE_RESET_NONE) || \
                                                 ((MODE) == GTIM_ENCODE_RESET_RISE) || \
                                                 ((MODE) == GTIM_ENCODE_RESET_FALL))

#define GTIM_ENCODE_RELOAD_NONE                 (0UL)
#define GTIM_ENCODE_RELOAD_RISE                 (1UL << 19)
#define GTIM_ENCODE_RELOAD_FALL                 (2UL << 19)
#define IS_GTIM_ENCODE_RELOAD(MODE)             (((MODE) == GTIM_ENCODE_RELOAD_NONE) || \
                                                 ((MODE) == GTIM_ENCODE_RELOAD_RISE) || \
                                                 ((MODE) == GTIM_ENCODE_RELOAD_FALL))

#define GTIM_CHx_FILTER_NONE                    (0UL)
#define GTIM_CHx_FILTER_PCLK_N2                 (1UL)
#define GTIM_CHx_FILTER_PCLK_N4                 (2UL)
#define GTIM_CHx_FILTER_PCLK_N6                 (3UL)
#define GTIM_CHx_FILTER_PCLKDIV4_N4             (4UL)
#define GTIM_CHx_FILTER_PCLKDIV4_N6             (5UL)
#define GTIM_CHx_FILTER_PCLKDIV8_N4             (6UL)
#define GTIM_CHx_FILTER_PCLKDIV8_N6             (7UL)
#define IS_GTIM_CHx_FILTER(MODE)                (((MODE) == GTIM_CHx_FILTER_NONE) || \
                                                 ((MODE) == GTIM_CHx_FILTER_PCLK_N2) || \
                                                 ((MODE) == GTIM_CHx_FILTER_PCLK_N4) || \
                                                 ((MODE) == GTIM_CHx_FILTER_PCLK_N6) || \
                                                 ((MODE) == GTIM_CHx_FILTER_PCLKDIV4_N4) || \
                                                 ((MODE) == GTIM_CHx_FILTER_PCLKDIV4_N6) || \
                                                 ((MODE) == GTIM_CHx_FILTER_PCLKDIV8_N4) || \
                                                 ((MODE) == GTIM_CHx_FILTER_PCLKDIV8_N6))

#define GTIM_CHx_INVERT_OFF                     (1UL)
#define GTIM_CHx_INVERT_ON                      (0UL)
#define IS_GTIM_CHx_INVERT(VAL)                 (((VAL) ==  GTIM_CHx_INVERT_OFF) || \
                                                 ((VAL) == GTIM_CHx_INVERT_ON))

#define GTIM_ETR_FILTER_NONE                    (0UL)
#define GTIM_ETR_FILTER_PCLK_N2                 (1UL << 4)
#define GTIM_ETR_FILTER_PCLK_N4                 (2UL << 4)
#define GTIM_ETR_FILTER_PCLK_N6                 (3UL << 4)
#define GTIM_ETR_FILTER_PCLKDIV4_N4             (4UL << 4)
#define GTIM_ETR_FILTER_PCLKDIV4_N6             (5UL << 4)
#define GTIM_ETR_FILTER_PCLKDIV8_N4             (6UL << 4)
#define GTIM_ETR_FILTER_PCLKDIV8_N6             (7UL << 4)
#define IS_GTIM_ETR_FILTER(MODE)                (((MODE) == GTIM_ETR_FILTER_NONE) || \
                                                 ((MODE) == GTIM_ETR_FILTER_PCLK_N2) || \
                                                 ((MODE) == GTIM_ETR_FILTER_PCLK_N4) || \
                                                 ((MODE) == GTIM_ETR_FILTER_PCLK_N6) || \
                                                 ((MODE) == GTIM_ETR_FILTER_PCLKDIV4_N4) || \
                                                 ((MODE) == GTIM_ETR_FILTER_PCLKDIV4_N6) || \
                                                 ((MODE) == GTIM_ETR_FILTER_PCLKDIV8_N4) || \
                                                 ((MODE) == GTIM_ETR_FILTER_PCLKDIV8_N6))


#define GTIM_ICPolarity_Rising                  (1UL)
#define GTIM_ICPolarity_Falling                 (2UL)
#define GTIM_ICPolarity_BothEdge                (3UL)
#define IS_GTIM_ICPolarity(MODE)                (((MODE) == GTIM_ICPolarity_Rising) || \
                                                 ((MODE) == GTIM_ICPolarity_Falling) || \
                                                 ((MODE) == GTIM_ICPolarity_BothEdge))

#define GTIM_OC_OUTPUT_FORCE_LOW                (8UL)
#define GTIM_OC_OUTPUT_FORCE_HIGH               (9UL)
#define GTIM_OC_OUTPUT_MATCH_LOW                (10UL)
#define GTIM_OC_OUTPUT_MATCH_HIGH               (11UL)
#define GTIM_OC_OUTPUT_MATHC_TOGGLE             (13UL)
#define GTIM_OC_OUTPUT_PWM_HIGH                 (14UL)
#define GTIM_OC_OUTPUT_PWM_LOW                  (15UL)
#define IS_GTIM_OC_OUTPUT(MODE)                 (((MODE) == GTIM_OC_OUTPUT_FORCE_LOW) || \
                                                 ((MODE) == GTIM_OC_OUTPUT_FORCE_HIGH) || \
                                                 ((MODE) == GTIM_OC_OUTPUT_MATCH_LOW) || \
                                                 ((MODE) == GTIM_OC_OUTPUT_MATCH_HIGH) || \
                                                 ((MODE) == GTIM_OC_OUTPUT_MATHC_TOGGLE) || \
                                                 ((MODE) == GTIM_OC_OUTPUT_PWM_HIGH) || \
                                                 ((MODE) == GTIM_OC_OUTPUT_PWM_LOW))

#define GTIM_CHANNEL1                           (0UL)
#define GTIM_CHANNEL2                           (4UL)
#define GTIM_CHANNEL3                           (8UL)
#define GTIM_CHANNEL4                           (12UL)
#define IS_GTIM_CHANNEL(CHANNEL)                (((CHANNEL) == GTIM_CHANNEL1) || \
                                                 ((CHANNEL) == GTIM_CHANNEL2) || \
                                                 ((CHANNEL) == GTIM_CHANNEL3) || \
                                                 ((CHANNEL) == GTIM_CHANNEL4))

#define GTIM_IT_OV                              (1UL)
#define GTIM_IT_TI                              (1UL<<1)
#define GTIM_IT_UD                              (1UL<<2)
#define GTIM_IT_CC1                             (1UL<<3)
#define GTIM_IT_CC2                             (1UL<<4)
#define GTIM_IT_CC3                             (1UL<<5)
#define GTIM_IT_CC4                             (1UL<<6)
#define GTIM_IT_DIRCHANGE                       (1UL<<9)
#define IS_GTIM_IT(IT)                          ((((IT) & 0xFFFFFD80) == 0x0UL) && ((IT) != 0x0UL))
#define IS_GTIM_GET_IT(IT)                      (((IT) == GTIM_IT_OV) || \
                                                 ((IT) == GTIM_IT_TI) || \
                                                 ((IT) == GTIM_IT_UD) || \
                                                 ((IT) == GTIM_IT_CC1) || \
                                                 ((IT) == GTIM_IT_CC2) || \
                                                 ((IT) == GTIM_IT_CC3) || \
                                                 ((IT) == GTIM_IT_CC4) || \
                                                 ((IT) == GTIM_IT_DIRCHANGE))

#define GTIM_DMA_OV                             (1UL)
#define GTIM_DMA_TRS                            (1UL<<1)
#define GTIM_DMA_CC1                            (1UL<<2)
#define GTIM_DMA_CC2                            (1UL<<3)
#define GTIM_DMA_CC3                            (1UL<<4)
#define GTIM_DMA_CC4                            (1UL<<5)
#define IS_GTIM_DMA(DMA)                        ((((DMA) & 0xFFFFFFC0) == 0x0UL) && (DMA) != 0x0UL)


/******************************************************************************
* Global variable definitions (declared in header file with 'extern')
******************************************************************************/


/******************************************************************************
* Global function prototypes
******************************************************************************/
void GTIM1_DeInit(void);
void GTIM2_DeInit(void);
void GTIM3_DeInit(void);
void GTIM4_DeInit(void);
void GTIM_TimeBaseInit(GTIM_TypeDef *GTIMx, GTIM_InitTypeDef *GTIM_InitStruct);

void GTIM_EncodeInit(GTIM_TypeDef *GTIMx, GTIM_EncodeInitTypeDef *GTIM_EncodeInitStruct);
void GTIM_OCInit(GTIM_TypeDef *GTIMx, uint32_t CHx, uint32_t OCMode);
void GTIM_ICInit(GTIM_TypeDef *GTIMx, GTIM_ICInitTypeDef *GTIM_ICInitStruct);
void GTIM_Cmd(GTIM_TypeDef *GTIMx, FunctionalState NewState);

void GTIM_ETRConfig(GTIM_TypeDef *GTIMx, uint32_t ETRPolarity, uint32_t ETRFilter);
void GTIM_ICChannelConfig(GTIM_TypeDef *GTIMx, uint32_t CHx, uint32_t CHxFilter, uint32_t CHxInvert);
void GTIM_SetPrescaler(GTIM_TypeDef *GTIMx, uint32_t GTIMPrescaler);
void GTIM_SetReloadValue(GTIM_TypeDef *GTIMx, uint32_t ReloadValue);
void GTIM_SetCounterValue(GTIM_TypeDef *GTIMx, uint32_t Value);
void GTIM_SetCompare1(GTIM_TypeDef *GTIMx, uint32_t Value);
void GTIM_SetCompare2(GTIM_TypeDef *GTIMx, uint32_t Value);
void GTIM_SetCompare3(GTIM_TypeDef *GTIMx, uint32_t Value);
void GTIM_SetCompare4(GTIM_TypeDef *GTIMx, uint32_t Value);
uint32_t GTIM_GetCapture1(GTIM_TypeDef *GTIMx);
uint32_t GTIM_GetCapture2(GTIM_TypeDef *GTIMx);
uint32_t GTIM_GetCapture3(GTIM_TypeDef *GTIMx);
uint32_t GTIM_GetCapture4(GTIM_TypeDef *GTIMx);
void GTIM_ITConfig(GTIM_TypeDef *GTIMx, uint32_t GTIM_IT, FunctionalState NewState);
ITStatus GTIM_GetITStatus(GTIM_TypeDef *GTIMx, uint32_t GTIM_IT);
void GTIM_ClearITPendingBit(GTIM_TypeDef *GTIMx, uint32_t GTIM_IT);
void GTIM_DMAConfig(GTIM_TypeDef *GTIMx, uint32_t GTIM_DMA, FunctionalState NewState);
void GTIM1_ITRConfig(uint32_t ITRSouce);
void GTIM2_ITRConfig(uint32_t ITRSouce);
void GTIM3_ITRConfig(uint32_t ITRSouce);
void GTIM4_ITRConfig(uint32_t ITRSouce);

#ifdef __cplusplus
}
#endif

#endif /*__CW32F030_GTIM_H */
