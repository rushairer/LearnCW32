/**
 * @file cw32f030_systick.h
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-05-13
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
#ifndef __CW32F030_SYSTICK_H
#define __CW32F030_SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cw32f030.h"

/* Exported types ------------------------------------------------------------*/

typedef enum
{
    TICK_FREQ_10HZ         = 100U,
    TICK_FREQ_100HZ        = 10U,
    TICK_FREQ_1KHZ         = 1U,
    TICK_FREQ_DEFAULT      = TICK_FREQ_1KHZ
} TickFreqTypeDef;

#define TICK_INT_PRIORITY                       ((uint32_t)0) /*!< tick interrupt priority (lowest by default)  */
#define MAX_SYSTICK_DELAY                       0xFFFFFFFFU
#define IS_TICKFREQ(FREQ)                       (((FREQ) == TICK_FREQ_10HZ)  || \
                                                 ((FREQ) == TICK_FREQ_100HZ) || \
                                                 ((FREQ) == TICK_FREQ_1KHZ))

/* Exported functions --------------------------------------------------------*/
void InitTick(uint32_t HclkFreq);
void SysTickDelay(uint32_t Delay);
uint32_t GetTick(void);
void SuspendTick(void);
void ResumeTick(void);
void SysTick_Handler(void);

/* Exported variables ---------------------------------------------------------*/
extern __IO uint32_t uwTick;
extern uint32_t uwTickPrio;
extern TickFreqTypeDef uwTickFreq;



#ifdef __cplusplus
}
#endif

#endif /* __CW32F030_SYSTICK_H */

/************************ (C) COPYRIGHT CW *****END OF FILE****/
