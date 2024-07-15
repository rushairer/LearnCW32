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
#ifndef __CW32F030_WWDT_H
#define __CW32F030_WWDT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cw32f030.h"

/******************************************************************************
 * type definitions ('typedef')
 ******************************************************************************/
typedef struct
{
    uint32_t WWDT_Prescaler;         /* 预分配系数，取值范围2的n次幂，n=12,13..19 */

    uint32_t WWDT_WindowValue;       /* 看门狗窗口值，取值范围小于0x80*/

    uint8_t WWDT_CounterValue;      /* 看门狗计数器初值，取值范围0x40 到 0x7F.  */

    FunctionalState WWDT_ITState;   /* 看门狗中断状态，取值范围ENABLE或DISABLE */
} WWDT_InitTypeDef;
/******************************************************************************
 * pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define WWDT_Prescaler_DIV4096                  ((uint32_t)0x00000000)
#define WWDT_Prescaler_DIV8192                  ((uint32_t)0x00000080)
#define WWDT_Prescaler_DIV16384                 ((uint32_t)0x00000100)
#define WWDT_Prescaler_DIV32768                 ((uint32_t)0x00000180)
#define WWDT_Prescaler_DIV65536                 ((uint32_t)0x00000200)
#define WWDT_Prescaler_DIV131072                ((uint32_t)0x00000280)
#define WWDT_Prescaler_DIV262144                ((uint32_t)0x00000300)
#define WWDT_Prescaler_DIV524288                ((uint32_t)0x00000380)
#define IS_WWDT_PRESCALER(PRESCALER)            (((PRESCALER) == WWDT_Prescaler_DIV4096) || \
                                                 ((PRESCALER) == WWDT_Prescaler_DIV8192) || \
                                                 ((PRESCALER) == WWDT_Prescaler_DIV16384) || \
                                                 ((PRESCALER) == WWDT_Prescaler_DIV32768) || \
                                                 ((PRESCALER) == WWDT_Prescaler_DIV65536) || \
                                                 ((PRESCALER) == WWDT_Prescaler_DIV131072) || \
                                                 ((PRESCALER) == WWDT_Prescaler_DIV262144) || \
                                                 ((PRESCALER) == WWDT_Prescaler_DIV524288))
#define IS_WWDT_WINDOW_VALUE(VALUE)             ((VALUE) <= 0x7F)
#define IS_WWDT_COUNTER(COUNTER)                (((COUNTER) >= 0x40) && ((COUNTER) <= 0x7F))


#define WWDT_GET_POV_STATUS(VALUE)              {(VALUE) = (FlagStatus)(CW_WWDT->SR);}
#define WWDT_CLR_POV_STATUS()                   {REGBITS_CLR(CW_WWDT->SR, WWDT_SR_POV_Msk);}
#define WWDT_ENABLE_IT()                        {REGBITS_SET(CW_WWDT->CR1,WWDT_CR1_IE_Msk);}
#define WWDT_FEED(VALUE)                        {REGBITS_MODIFY(CW_WWDT->CR0, WWDT_CR0_WCNT_Msk,(VALUE));}

/******************************************************************************
* Global variable definitions (declared in header file with 'extern')
******************************************************************************/


/******************************************************************************
* Global function prototypes
******************************************************************************/
void WWDT_DeInit(void);
void WWDT_Init(WWDT_InitTypeDef *WWDT_InitStruct);
void WWDT_Refresh(uint8_t Counter);


void WWDT_Cmd(void);
void WWDT_SetPrescaler(uint32_t WWDT_Prescaler);
void WWDT_SetWindowValue(uint8_t WindowValue);
void WWDT_SetCountValue(uint8_t CountValue);
uint8_t WWDT_GetCounterValue(void);
uint8_t WWDT_GetWindowValue(void);
void WWDT_EnableIT(void);
FlagStatus WWDT_GetFlagStatus(void);
void WWDT_ClearFlag(void);


#ifdef __cplusplus
}
#endif

#endif /*__CW32F030_WWDT_H */
/**
  * @}
  */
