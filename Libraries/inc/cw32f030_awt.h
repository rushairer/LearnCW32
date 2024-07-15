/**
 * @file cw32f030_awt.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CW32F030_AWT_H
#define __CW32F030_AWT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cw32f030.h"

typedef struct
{
    uint32_t AWT_ClkSource;         /* 时钟源选择，设置值0 - 4 */
    uint32_t AWT_Prescaler;         /* 预分配系数，设置值1 - 15，对应取值范围2的n次幂，n=1,2…15 */
    uint32_t AWT_Period;            /* 计数重载周期，低16位有效，取值范围0x0000 到 0xFFFF.  */
    uint32_t AWT_Mode;              /* AWT工作模式，固定为11  */
} AWT_TimeCntInitTypeDef;

#define AWT_CLKSOURCE_HSIOSC                    ( uint32_t )(0x00UL << 8)
#define AWT_CLKSOURCE_LSI                       ( uint32_t )(0x01UL << 8)
#define AWT_CLKSOURCE_HSE                       ( uint32_t )(0x02UL << 8)
#define AWT_CLKSOURCE_LSE                       ( uint32_t )(0x03UL << 8)
#define AWT_CLKSOURCE_ETR                       ( uint32_t )(0x04UL << 8)
#define IS_AWT_CLKSOURCE(SOURCE)                (((SOURCE) == AWT_CLKSOURCE_HSIOSC) || \
                                                 ((SOURCE) == AWT_CLKSOURCE_LSI) || \
                                                 ((SOURCE) == AWT_CLKSOURCE_HSE) || \
                                                 ((SOURCE) == AWT_CLKSOURCE_LSE) || \
                                                 ((SOURCE) == AWT_CLKSOURCE_ETR))

#define AWT_PRS_DIV2                            ( uint32_t )(0x01UL << 4)
#define AWT_PRS_DIV4                            ( uint32_t )(0x02UL << 4)
#define AWT_PRS_DIV8                            ( uint32_t )(0x03UL << 4)
#define AWT_PRS_DIV16                           ( uint32_t )(0x04UL << 4)
#define AWT_PRS_DIV32                           ( uint32_t )(0x05UL << 4)
#define AWT_PRS_DIV64                           ( uint32_t )(0x06UL << 4)
#define AWT_PRS_DIV128                          ( uint32_t )(0x07UL << 4)
#define AWT_PRS_DIV256                          ( uint32_t )(0x08UL << 4)
#define AWT_PRS_DIV512                          ( uint32_t )(0x09UL << 4)
#define AWT_PRS_DIV1024                         ( uint32_t )(0x0AUL << 4)
#define AWT_PRS_DIV2048                         ( uint32_t )(0x0BUL << 4)
#define AWT_PRS_DIV4096                         ( uint32_t )(0x0CUL << 4)
#define AWT_PRS_DIV8192                         ( uint32_t )(0x0DUL << 4)
#define AWT_PRS_DIV16384                        ( uint32_t )(0x0EUL << 4)
#define AWT_PRS_DIV32768                        ( uint32_t )(0x0FUL << 4)
#define IS_AWT_PRS_DIV(DIV)                     (((DIV) == AWT_PRS_DIV2) || \
                                                 ((DIV) == AWT_PRS_DIV4) || \
                                                 ((DIV) == AWT_PRS_DIV8) || \
                                                 ((DIV) == AWT_PRS_DIV16) || \
                                                 ((DIV) == AWT_PRS_DIV32) || \
                                                 ((DIV) == AWT_PRS_DIV64) || \
                                                 ((DIV) == AWT_PRS_DIV128) || \
                                                 ((DIV) == AWT_PRS_DIV256) || \
                                                 ((DIV) == AWT_PRS_DIV512) || \
                                                 ((DIV) == AWT_PRS_DIV1024) || \
                                                 ((DIV) == AWT_PRS_DIV2048) || \
                                                 ((DIV) == AWT_PRS_DIV4096) || \
                                                 ((DIV) == AWT_PRS_DIV8192) || \
                                                 ((DIV) == AWT_PRS_DIV16384) || \
                                                 ((DIV) == AWT_PRS_DIV32768))

#define AWT_MODE_TIMECNT                        ( uint32_t )(0x03UL << 1)
#define IS_AWT_MODE(MODE)                       ((MODE) == AWT_MODE_TIMECNT)
#define AWT_CR_EN                               bv0

#define IS_AWT_ARR(ARR)                         ((ARR) <= 65535)

#define AWT_IT_UD                               ((uint32_t)0x08)
#define IS_AWT_IT(IT)                           ((((IT) & (uint32_t)0xFFFFFFF7) == 0x0000) && ((IT) != 0x0000))
#define IS_AWT_GET_IT(IT)                       ((IT) == AWT_IT_UD)


void AWT_DeInit(void);
void AWT_TimeCntInit(AWT_TimeCntInitTypeDef *AWT_TimeCntInitStruct);
void AWT_TimeCntStructInit(AWT_TimeCntInitTypeDef *AWT_TimeCntInitStruct);
void AWT_Cmd(FunctionalState NewState);
void AWT_ITConfig(uint32_t AWT_IT, FunctionalState NewState);
ITStatus AWT_GetITStatus(uint32_t AWT_IT);
void AWT_ClearITPendingBit(uint32_t AWT_IT);
void AWT_ClkSourceConfig(uint32_t AWT_ClkSource);
void AWT_PrescalerConfig(uint32_t AWT_Prescaler);
uint16_t AWT_GetCounter(void);
uint16_t AWT_GetAutoreload(void);
uint32_t AWT_GetClkSource(void);
uint32_t AWT_GetPrescaler(void);


#ifdef __cplusplus
}
#endif

#endif

