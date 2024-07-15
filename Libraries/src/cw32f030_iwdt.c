/**
 * @file cw32f030_iwdt.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-04-25
 *
 * @copyright Copyright (c) 2021
 *
 */
/* Includes ------------------------------------------------------------------*/
#include "cw32f030_iwdt.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief IWDT去初始化
 */
void IWDT_DeInit(void)
{
    CW_SYSCTRL->APBRST1_f.IWDT = 0;
    CW_SYSCTRL->APBRST1_f.IWDT = 1;
}

/**
 * @brief IWDT初始化
 * @param IWDT_InitStruct 该结构体包含IWDT需要配置的参数
 * @return 0:sucess 1:error
 */
int IWDT_Init(IWDT_InitTypeDef *IWDT_InitStruct)
{
    uint16_t timeout = 0xffff;
    assert_param(IS_IWDT_PRESCALER(IWDT_InitStruct->IWDT_Prescaler));
    assert_param(IS_IWDT_ACTION(IWDT_InitStruct->IWDT_OverFlowAction));
    assert_param(IS_IWDT_SLEEP_MODE(IWDT_InitStruct->IWDT_Pause));
    assert_param(IS_IWDT_WINDOW_VALUE(IWDT_InitStruct->IWDT_WindowValue));
    assert_param(IS_IWDT_RELOAD(IWDT_InitStruct->IWDT_ReloadValue));
    __IWDT_RUN();                // 需要先启动IWDT后，才能修改其他寄存器
    __IWDT_UNLOCK();             // 解锁寄存器保护
    if (IWDT_InitStruct->IWDT_ITState == ENABLE)
    {
        CW_IWDT->CR = IWDT_InitStruct->IWDT_Prescaler | \
                      IWDT_InitStruct->IWDT_OverFlowAction | \
                      IWDT_CR_IE_Msk | IWDT_InitStruct->IWDT_Pause;
    }
    else
    {
        CW_IWDT->CR = (IWDT_InitStruct->IWDT_Prescaler | \
                       IWDT_InitStruct->IWDT_OverFlowAction | \
                       IWDT_InitStruct->IWDT_Pause);
    }
    CW_IWDT->ARR = IWDT_InitStruct->IWDT_ReloadValue;
    CW_IWDT->WINR = IWDT_InitStruct->IWDT_WindowValue;
    while ((CW_IWDT->SR & (IWDT_SR_CRF_Msk | IWDT_SR_ARRF_Msk | IWDT_SR_WINRF_Msk)) && timeout--);
    if (timeout == 0) return 1;

    __IWDT_LOCK();
    return 0;
}

/**
 * @brief 启动IWDT
 */
void inline IWDT_Cmd(void)
{
    __IWDT_RUN();
}

/**
 * @brief 喂狗
 */
void inline IWDT_Refresh(void)
{
    __IWDT_REFRESH();
}

/**
 * @brief 寄存器保护解锁
 */
void inline IWDT_Unlock(void)
{
    __IWDT_UNLOCK();
}

/**
 * @brief 寄存器保护上锁
 */
void inline IWDT_Lock(void)
{
    __IWDT_LOCK();
}

/**
 * @brief 停止IWDT
 */
void inline IWDT_Stop(void)
{
    __IWDT_STOP();
}

/**
 * @brief 设置IWDT的预分频因数
 * @param IWDT_Prescaler 取值范围 IWDT_Prescaler_DIV4~IWDT_Prescaler_DIV512
 */
int IWDT_SetPrescaler(uint32_t IWDT_Prescaler)
{
    uint16_t timeout = 0xffff;
    assert_param(IS_IWDT_PRESCALER(IWDT_Prescaler));

    __IWDT_UNLOCK();
    while ((CW_IWDT->SR & IWDT_SR_CRF_Msk) && timeout--);
    if (timeout == 0) return 1;
    CW_IWDT->CR_f.PRS = IWDT_Prescaler;
    __IWDT_LOCK();
    return 0;
}

/**
 * @brief 设置IWDT的窗口值
 * @param WindowValue 取值范围0x00000000~0x00000FFF,当值为0x00000FFF时，窗口功能不开启
 */
int IWDT_SetWindowValue(uint32_t WindowValue)
{
    uint16_t timeout = 0xffff;
    assert_param(IS_IWDT_WINDOW_VALUE(WindowValue));

    __IWDT_UNLOCK();
    while ((CW_IWDT->SR & IWDT_SR_WINRF_Msk) && timeout--);
    if (timeout == 0) return 1;
    CW_IWDT->WINR = WindowValue;
    __IWDT_LOCK();
    return 0;
}

/**
 * @brief 设置IWDT的重载寄存器的值
 * @param ReloadValue 取值范围0x00000000~0x00000FFF
 */
int IWDT_SetReloadValue(uint32_t ReloadValue)
{
    uint16_t timeout = 0xffff;
    assert_param(IS_IWDT_RELOAD(ReloadValue));

    __IWDT_UNLOCK();
    while ((CW_IWDT->SR & IWDT_SR_ARRF_Msk) && timeout--);
    if (timeout == 0) return 1;
    CW_IWDT->ARR = ReloadValue;
    __IWDT_LOCK();
    return 0;
}

/**
 * @brief 设置IWDT的中断使能与禁能
 * @param NewState IWDT中断使能位状态 范围：ENABLE或DISABLE
 */
int IWDT_ITConfig(FunctionalState NewState)
{
    uint16_t timeout = 0xffff;
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    __IWDT_UNLOCK();
    while ((CW_IWDT->SR & IWDT_SR_CRF_Msk) && timeout--);
    if (timeout == 0) return 1;
    NewState ? (CW_IWDT->CR_f.IE = ENABLE) : (CW_IWDT->CR_f.IE = DISABLE);
    __IWDT_LOCK();
    return 0;
}

/**
 * @brief 获取IWDT的状态
 * @param StatusBit 状态位的位置,取值范围为：IWDT_SR_CRF_Msk
 *                                          IWDT_SR_ARRF_Msk
 *                                          IWDT_SR_WINRF_Msk
 *                                          IWDT_SR_OV_Msk
 *                                          IWDT_SR_RUN_Msk
 *                                          IWDT_SR_RELOAD_Msk
 *
 * @return FlagStatus
 */
FlagStatus IWDT_GetFlagStatus(uint32_t StatusBit)
{
    return (FlagStatus)(CW_IWDT->SR & StatusBit);
}

/**
 * @brief 清除IWDT的溢出标志OV
 */
void inline IWDT_ClearOVFlag(void)
{
    CW_IWDT->SR_f.OV = 0;
}

/**
 * @brief
 * @return uint32_t 返回IWDT的计数值
 */
uint32_t IWDT_GetCounterValue(void)
{
    uint32_t tmp1, tmp2;
    do
    {
        tmp1 = CW_IWDT->CNT;
        tmp2 = CW_IWDT->CNT;
    } while(tmp1 != tmp2);

    return tmp1;
}

/**
  * @brief  Set IWDT counting period.
  * @param  counting period:
               WDT_2_SECS
               WDT_1_SECS
               WDT_0_5_SECS
               WDT_0_25_SECS
  * @retval None
  */
void IWDT_SetPeriod(uint32_t period)
{
    IWDT_InitTypeDef IWDT_InitStruct = {0};

    assert_param(IS_IWDT_PERIOD(period));


    IWDT_InitStruct.IWDT_ITState = DISABLE;
    IWDT_InitStruct.IWDT_OverFlowAction = IWDT_OVERFLOW_ACTION_RESET;
    IWDT_InitStruct.IWDT_Pause = IWDT_SLEEP_CONTINUE;
    IWDT_InitStruct.IWDT_Prescaler = IWDT_Prescaler_DIV512;     // 默认设置为最大分频，计时间隔为51.2ms
    IWDT_InitStruct.IWDT_WindowValue = 0xFFF;          // 关闭窗口看门狗的功能
    IWDT_InitStruct.IWDT_ReloadValue = period;

    IWDT_Init(&IWDT_InitStruct);
    IWDT_Refresh();
}
