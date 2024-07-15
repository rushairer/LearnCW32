/**
 * @file cw32f030_systick.c
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

/* Includes ------------------------------------------------------------------*/
#include "cw32f030_systick.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/
__IO uint32_t uwTick;
uint32_t uwTickPrio   = (1UL << __NVIC_PRIO_BITS); /* Invalid PRIO */
TickFreqTypeDef uwTickFreq = TICK_FREQ_DEFAULT;  /* 1KHz */

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
  * @brief This function configures the source of the time base.
  *        The time source is configured  to have 1ms time base with a dedicated
  *        Tick interrupt priority.
  * @note This function is called  automatically at the beginning of program after
  *       reset by HAL_Init() or at any time when clock is reconfigured  by HAL_RCC_ClockConfig().
  * @note In the default implementation, SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals.
  *       Care must be taken if HAL_Delay() is called from a peripheral ISR process,
  *       The SysTick interrupt must have higher priority (numerically lower)
  *       than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
  *       The function is declared as __Weak  to be overwritten  in case of other
  *       implementation  in user file.
  * @param system hclk freq.
  * @retval HAL status
  */
__WEAK void InitTick(uint32_t HclkFreq)
{
    /*Configure the SysTick to have interrupt in 1ms time basis*/
    if (SysTick_Config(HclkFreq / (1000U / uwTickFreq)) > 0U)
    {
        return ;
    }
    /* Configure the SysTick IRQ priority */
    if (TICK_INT_PRIORITY < (1UL << __NVIC_PRIO_BITS))
    {
        NVIC_SetPriority(SysTick_IRQn, TICK_INT_PRIORITY);
        uwTickPrio = TICK_INT_PRIORITY;
    }
    else
    {
        return ;
    }
}


/**
  * @brief  Provides a tick value in millisecond.
  * @note   This function is declared as __WEAK  to be overwritten  in case of other
  *       implementations in user file.
  * @retval tick value
  */
__WEAK uint32_t GetTick(void)
{
    return uwTick;
}


/**
  * @brief This function provides accurate delay (in milliseconds) based
  *        on variable incremented.
  * @note In the default implementation , SysTick timer is the source of time base.
  *       It is used to generate interrupts at regular time intervals where uwTick
  *       is incremented.
  * @note ThiS function is declared as __WEAK to be overwritten in case of other
  *       implementations in user file.
  * @param Delay specifies the delay time length, in milliseconds.
  * @retval None
  */
__WEAK void SysTickDelay(uint32_t Delay)
{
    uint32_t tickstart = GetTick();
    uint32_t wait = Delay;
    /* Add a freq to guarantee minimum wait */
    if (wait < MAX_SYSTICK_DELAY)
    {
        wait += (uint32_t)(uwTickFreq);
    }
    while ((GetTick() - tickstart) < wait)
    {
    }
}


/**
  * @brief Suspend Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_SuspendTick()
  *       is called, the the SysTick interrupt will be disabled and so Tick increment
  *       is suspended.
  * @note This function is declared as __WEAK to be overwritten in case of other
  *       implementations in user file.
  * @retval None
  */
__WEAK void SuspendTick(void)

{
    /* Disable SysTick Interrupt */
    REGBITS_CLR(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}


/**
  * @brief Resume Tick increment.
  * @note In the default implementation , SysTick timer is the source of time base. It is
  *       used to generate interrupts at regular time intervals. Once HAL_ResumeTick()
  *       is called, the the SysTick interrupt will be enabled and so Tick increment
  *       is resumed.
  * @note This function is declared as __WEAK  to be overwritten  in case of other
  *       implementations in user file.
  * @retval None
  */
__WEAK void ResumeTick(void)
{
    /* Enable SysTick Interrupt */
    REGBITS_SET(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk);
}


/**
  * @brief This function handles System tick timer.
  */
__WEAK void SysTick_Handler(void)
{
    /* USER CODE BEGIN SysTick_IRQn */
    uwTick += uwTickFreq;
    /* USER CODE END SysTick_IRQn */
}
