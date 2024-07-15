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
#ifndef __CW32F030_IWDT_H
#define __CW32F030_IWDT_H

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
    uint32_t IWDT_Prescaler;         /* 预分配系数，取值范围2的n次幂，n=2,3..9  */

    uint32_t IWDT_OverFlowAction;    /* 溢出后的动作                           */

    FunctionalState IWDT_ITState;    /* 看门狗中断状态，取值范围ENABLE或DISABLE */

    uint32_t IWDT_Pause;             /* Deepsleep模式下IWDT暂停控制            */

    uint32_t IWDT_ReloadValue;       /* 看门狗重载值，取值范围小于等于0x0FFF    */

    uint32_t IWDT_WindowValue;       /* 窗口比较器比较值,取值范围小于等于0x0FFF  */
} IWDT_InitTypeDef;
/******************************************************************************
 * pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define IWDT_FREQ                               10000UL

#define IWDT_Prescaler_DIV4                     ((uint32_t)0x00000000)
#define IWDT_Prescaler_DIV8                     ((uint32_t)0x00000001)
#define IWDT_Prescaler_DIV16                    ((uint32_t)0x00000002)
#define IWDT_Prescaler_DIV32                    ((uint32_t)0x00000003)
#define IWDT_Prescaler_DIV64                    ((uint32_t)0x00000004)
#define IWDT_Prescaler_DIV128                   ((uint32_t)0x00000005)
#define IWDT_Prescaler_DIV256                   ((uint32_t)0x00000006)
#define IWDT_Prescaler_DIV512                   ((uint32_t)0x00000007)
#define IS_IWDT_PRESCALER(PRESCALER)            (((PRESCALER) == IWDT_Prescaler_DIV4)||\
                                                 ((PRESCALER) == IWDT_Prescaler_DIV8)   ||\
                                                 ((PRESCALER) == IWDT_Prescaler_DIV16)  ||\
                                                 ((PRESCALER) == IWDT_Prescaler_DIV32)  ||\
                                                 ((PRESCALER) == IWDT_Prescaler_DIV64)  ||\
                                                 ((PRESCALER) == IWDT_Prescaler_DIV128) ||\
                                                 ((PRESCALER) == IWDT_Prescaler_DIV512))
#define IS_IWDT_WINDOW_VALUE(VALUE)             ((VALUE) <= 0xFFF)
#define IS_IWDT_RELOAD(COUNTER)                 ((COUNTER) <= 0xFFF)


#define IWDT_2_SECS                                39
#define IWDT_1_SECS                                19
#define IWDT_0_5_SECS                              9
#define IWDT_0_25_SECS                             4
#define IS_IWDT_PERIOD(PERIOD)                     ((PERIOD) == IWDT_2_SECS || (PERIOD) == IWDT_1_SECS ||\
                                                    (PERIOD) == IWDT_0_5_SECS || (PERIOD) == IWDT_0_25_SECS)

#define IWDT_UNLOCK_KEY                         0x5555
#define IWDT_LOCK_KEY                           0x6666
#define IWDT_RUN_KEY                            0xCCCC
#define IWDT_REFRESH_KEY                        0xAAAA
#define IWDT_STOP_KEY1                          0x5A5A
#define IWDT_STOP_KEY2                          0xA5A5

#define IWDT_OVERFLOW_ACTION_RESET              0
#define IWDT_OVERFLOW_ACTION_INT                IWDT_CR_ACTION_Msk
#define IS_IWDT_ACTION(ACTION)                  ((ACTION) == IWDT_OVERFLOW_ACTION_RESET || \
                                                 (ACTION) == IWDT_OVERFLOW_ACTION_INT)
#define IWDT_SLEEP_PAUSE                        IWDT_CR_PAUSE_Msk
#define IWDT_SLEEP_CONTINUE                     0
#define IS_IWDT_SLEEP_MODE(MODE)                ((MODE) == IWDT_SLEEP_PAUSE || \
                                                 (MODE) == IWDT_SLEEP_CONTINUE)

#define __IWDT_RUN()                            (CW_IWDT->KR = IWDT_RUN_KEY)
#define __IWDT_REFRESH()                        (CW_IWDT->KR = IWDT_REFRESH_KEY)
#define __IWDT_STOP()                           do{                        \
                                                    CW_IWDT->KR = IWDT_STOP_KEY1;\
                                                    CW_IWDT->KR = IWDT_STOP_KEY2;\
                                                } while(0)
#define __IWDT_UNLOCK()                         (CW_IWDT->KR = IWDT_UNLOCK_KEY)
#define __IWDT_LOCK()                           (CW_IWDT->KR = IWDT_LOCK_KEY)


/******************************************************************************
* Global variable definitions (declared in header file with 'extern')
******************************************************************************/


/******************************************************************************
* Global function prototypes
******************************************************************************/
void IWDT_DeInit(void);
int IWDT_Init(IWDT_InitTypeDef *IWDT_InitStruct);

void IWDT_Cmd(void);
void IWDT_Refresh(void);

void IWDT_Unlock(void);
void IWDT_Lock(void);
void IWDT_Stop(void);

int IWDT_SetPrescaler(uint32_t WWDT_Prescaler);
int IWDT_SetWindowValue(uint32_t WindowValue);
int IWDT_SetReloadValue(uint32_t ReloadValue);
int IWDT_ITConfig(FunctionalState NewState);
FlagStatus IWDT_GetFlagStatus(uint32_t StatusBit);
void IWDT_ClearOVFlag(void);
uint32_t IWDT_GetCounterValue(void);
void IWDT_SetPeriod(uint32_t period);

#ifdef __cplusplus
}
#endif

#endif /*__CW32F030_IWDT_H */
/**
  * @}
  */
