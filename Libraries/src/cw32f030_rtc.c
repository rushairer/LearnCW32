/**
 * @file cw32f030_rtc.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-04-29
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
#include "cw32f030_rtc.h"
#include "cw32f030_rcc.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief RTC去初始化
 *
 */
void RTC_DeInit(void)
{
    /* 解锁RTC寄存器的写保护 */
    CW_RTC->KEY_f.KEY = RTC_KEY_WORD1;
    CW_RTC->KEY_f.KEY = RTC_KEY_WORD2;
    /* 对除RTC_CR0、RTC_CR1、RTC_CR2和RTC_COMPEN外，其他的RTC寄存器赋默认值 */
    CW_RTC->DATE = RTC_DATE_RESET_VALUE;
    CW_RTC->TIME = RTC_TIME_RESET_VALUE;
    CW_RTC->ALARMA = RTC_ALARMA_RESET_VALUE;
    CW_RTC->ALARMB = RTC_ALARMB_RESET_VALUE;
    CW_RTC->TAMPDATE = RTC_TAMPDATA_RESET_VALUE;
    CW_RTC->TAMPTIME = RTC_TAMPTIME_RESET_VALUE;
    CW_RTC->AWTARR = RTC_AWTARR_RESET_VALUE;
    CW_RTC->IER = RTC_IER_RESET_VALUE;
    CW_RTC->ICR = 0UL;    // 清除中断标志位
    /* 使能RTC寄存器的写保护 */
    CW_RTC->KEY_f.KEY = RTC_KEY_WORD1;
    CW_RTC->KEY_f.KEY = RTC_KEY_LOCKW;
    /* 复位RTC模块，RTC_CR0、RTC_CR1、RTC_CR2和RTC_COMPEN复位为默认值 */
    CW_SYSCTRL->APBRST1_f.RTC = 0;
    CW_SYSCTRL->APBRST1_f.RTC = 1;
    /* 关闭RTC模块的时钟 */
    CW_SYSCTRL->APBEN1_f.RTC = 0;
}

/**
 * @brief RTC模块初始化
 *
 * @param 初始化RTC模块，用户需首先启动启动RTC时钟源！！！自动运行RTC
 *
 * @return ErrorStatus 返回值为SUCCESS或ERROR
 */
ErrorStatus RTC_Init(RTC_InitTypeDef *RTC_InitStruct)
{
    assert_param(IS_RTC_RTCCLK_SOURCE(RTC_InitStruct->RTC_ClockSource));
    CW_SYSCTRL->APBEN1_f.RTC = 1;            //  启动RTC外设时钟，使能RTC模块
    RTC_Cmd(DISABLE);                        //  停止RTC，保证正确访问RTC寄存器
    RTC_SetClockSource(RTC_InitStruct->RTC_ClockSource);        // 设置RTC时钟源, 用户需首先启动RTC时钟源！！！
    if ((RCC_GetAllRstFlag()&SYSCTRL_RESETFLAG_POR_Msk) == RCC_FLAG_PORRST) //如果是上电复位,设置日期与时间,否则仅设置H24标志
    {
        RTC_SetDate(&RTC_InitStruct->DateStruct);
        RTC_SetTime(&RTC_InitStruct->TimeStruct);
    }
    else
    {
        RTC_UNLOCK();
        CW_RTC->CR0_f.H24 = RTC_InitStruct->TimeStruct.H24;
        RTC_LOCK();
    }
    CW_SYSCTRL->RESETFLAG = 0;               //  清除复位标志
    RTC_Cmd(ENABLE);
    return SUCCESS;
}


void RTC_Cmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    RTC_UNLOCK();
    CW_RTC->CR0_f.START = NewState;
    RTC_LOCK();
}

/**
 * @brief 读取中断RTC状态
 *
 * @param RTC_ITState
 * @return ITStatus
 */

ITStatus RTC_GetITState(uint32_t RTC_ITState)
{
    uint32_t RegTmp;
    assert_param(IS_RTC_GET_IT(RTC_ITState));
    do
    {
        RegTmp = CW_RTC->ISR;
    }
    while (RegTmp != CW_RTC->ISR);
    return (RegTmp & RTC_ITState) ? SET : RESET;
}

/**
 * @brief 设置中断使能
 *
 * @param RTC_IT
 * @param NewState
 */
void RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState)
{
    assert_param(IS_RTC_CONFIG_IT(RTC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    RTC_UNLOCK();
    //  CW_RTC->CR1_f.ACCESS = 1;
    //  while (!CW_RTC->CR1_f.WINDOW);
    if (!NewState)
    {
        CW_RTC->IER &= ~RTC_IT;
    }
    else
    {
        CW_RTC->IER |= RTC_IT;
    }
    //  CW_RTC->CR1_f.ACCESS = 0;
    RTC_LOCK();
}

/**
 * @brief 清除中断标志
 *
 * @param RTC_IT
 */
void RTC_ClearITPendingBit(uint32_t RTC_IT)
{
    assert_param(IS_RTC_CLAER_IT(RTC_IT));
    RTC_UNLOCK();
    //  CW_RTC->CR1_f.ACCESS = 1;
    //  while (!CW_RTC->CR1_f.WINDOW);
    CW_RTC->ICR = ~RTC_IT;
    //  CW_RTC->CR1_f.ACCESS = 0;
    RTC_LOCK();
}

/**
 * @brief 设置时间，HOUR、MINIUTE、SECOND必须为BCD方式，用户须保证HOUR、AMPM、H24之间的关联正确性
 *
 * @param RTC_TimeStruct
 */
void RTC_SetTime(RTC_TimeTypeDef *RTC_TimeStruct)
{
    assert_param(IS_RTC_SECONDS(RTC_BCDToBin(RTC_TimeStruct->Second)));
    assert_param(IS_RTC_MINUTES(RTC_BCDToBin(RTC_TimeStruct->Minute)));
    if (RTC_TimeStruct->H24 == RTC_HOUR12)
    {
        assert_param(IS_RTC_HOUR12(RTC_BCDToBin(RTC_TimeStruct->Hour)));
    }
    else
    {
        assert_param(IS_RTC_HOUR24(RTC_BCDToBin(RTC_TimeStruct->Hour)));
    }
    RTC_UNLOCK();
    CW_RTC->CR0_f.H24 = RTC_TimeStruct->H24;
    if (RTC_TimeStruct->H24 == RTC_HOUR12)
    {
        CW_RTC->TIME = ((uint32_t)(RTC_TimeStruct->AMPM) << 21) |
                       ((uint32_t)(RTC_TimeStruct->Hour) << 16) |
                       ((uint32_t)(RTC_TimeStruct->Minute) << 8) |
                       ((uint32_t)(RTC_TimeStruct->Second));
    }
    else
    {
        CW_RTC->TIME = ((uint32_t)(RTC_TimeStruct->Hour) << 16) |
                       ((uint32_t)(RTC_TimeStruct->Minute) << 8) |
                       ((uint32_t)(RTC_TimeStruct->Second));
    }
    CW_RTC->CR1_f.ACCESS = 0;
    RTC_LOCK();
}

/**
 * @brief
 *   设置日期，DAY、MONTH、YEAR必须为BCD方式，星期为0~6，代表星期日，星期一至星期六
 * @param RTC_DateStruct
 */
void RTC_SetDate(RTC_DateTypeDef *RTC_DateStruct)
{
    assert_param(IS_RTC_YEAR(RTC_BCDToBin(RTC_DateStruct->Year)));
    assert_param(IS_RTC_MONTH(RTC_BCDToBin(RTC_DateStruct->Month)));
    assert_param(IS_RTC_DAY(RTC_BCDToBin(RTC_DateStruct->Day)));
    assert_param(IS_RTC_WEEKDAY(RTC_DateStruct->Week));
    RTC_UNLOCK();
    CW_RTC->DATE = ((uint32_t)(RTC_DateStruct->Week) << 24) |
                   ((uint32_t)(RTC_DateStruct->Year) << 16) |
                   ((uint32_t)(RTC_DateStruct->Month) << 8) |
                   ((uint32_t)(RTC_DateStruct->Day));
    RTC_LOCK();
}

/**
 * @brief 获取当前时间，BCD格式
 *
 * @param RTC_TimeStruct
 */
void RTC_GetTime(RTC_TimeTypeDef *RTC_TimeStruct)
{
    uint32_t RegTmp = 0;
    RTC_TimeStruct->H24 = CW_RTC->CR0_f.H24;  // 读CR0是否需要连读两次，待硬件检测
    RegTmp = CW_RTC->TIME;
    while (RegTmp != CW_RTC->TIME)
    {
        RegTmp = CW_RTC->TIME;   // 连续两次读取的内容一致，认为读取成功
    }
    RTC_TimeStruct->Hour = (uint8_t)((RegTmp & RTC_TIME_HOUR_Msk) >> 16);
    RTC_TimeStruct->Minute = (uint8_t)((RegTmp & RTC_TIME_MINUTE_Msk) >> 8);
    RTC_TimeStruct->Second = (uint8_t)(RegTmp & RTC_TIME_SECOND_Msk);
    if (RTC_TimeStruct->H24 == RTC_HOUR12)
    {
        RTC_TimeStruct->AMPM = RTC_TimeStruct->Hour >> 5;
        RTC_TimeStruct->Hour &= 0x1f;
    }
}


/**
 * @brief 获取用当前日期，BCD格式
 *
 * @param RTC_Date
 */
void RTC_GetDate(RTC_DateTypeDef *RTC_Date)
{
    uint32_t RegTmp = 0;
    RegTmp = CW_RTC->DATE;
    while (RegTmp != CW_RTC->DATE)
    {
        RegTmp = CW_RTC->DATE;   // 连续两次读取的内容一致，认为读取成功
    }
    RTC_Date->Day = (uint8_t)(RegTmp & RTC_DATE_DAY_Msk);
    RTC_Date->Month = (uint8_t)((RegTmp & RTC_DATE_MONTH_Msk) >> 8);
    RTC_Date->Year = (uint8_t)((RegTmp & RTC_DATE_YEAR_Msk) >> 16);
    RTC_Date->Week = (uint8_t)((RegTmp & RTC_DATE_WEEK_Msk) >> 24);
}

/**
 * @brief 设置闹钟，BCD格式。 ||
 *        RTC_AlarmMask：bit32~24:WeeksMask，bit23:HourMask，bit15:MinuteMask，bit7:SecondMask ||
 *        闹钟时间，HOUR、MINIUTE、SECOND必须为BCD方式，用户须保证HOUR、AMPM、H24之间的关联正确性
 *
 * @param RTC_Alarm
 * @param RTC_AlarmStruct
 */
void RTC_SetAlarm(uint32_t RTC_Alarm, RTC_AlarmTypeDef *RTC_AlarmStruct)
{
    uint32_t RegTmp = 0;
    assert_param(IS_RTC_ALARM(RTC_Alarm));
    assert_param(IS_ALARM_MASK(RTC_AlarmStruct->RTC_AlarmMask));
    assert_param(IS_RTC_SECONDS(RTC_BCDToBin(RTC_AlarmStruct->RTC_AlarmTime.Second)));
    assert_param(IS_RTC_MINUTES(RTC_BCDToBin(RTC_AlarmStruct->RTC_AlarmTime.Minute)));
    if (RTC_AlarmStruct->RTC_AlarmTime.H24 == RTC_HOUR12)
    {
        assert_param(IS_RTC_HOUR12(RTC_BCDToBin(RTC_AlarmStruct->RTC_AlarmTime.Hour)));
    }
    else
    {
        assert_param(IS_RTC_HOUR24(RTC_BCDToBin(RTC_AlarmStruct->RTC_AlarmTime.Hour)));
    }
    RegTmp = RTC_AlarmStruct->RTC_AlarmMask |
             (uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.Hour << 16)  |
             (uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.Minute << 8) |
             (uint32_t)(RTC_AlarmStruct->RTC_AlarmTime.Second);
    RTC_UNLOCK();
    CW_RTC->CR1_f.ACCESS = 1;
    while (!CW_RTC->CR1_f.WINDOW);
    if (RTC_Alarm == RTC_Alarm_A)
    {
        CW_RTC->ALARMA = RegTmp;
    }
    else
    {
        CW_RTC->ALARMB = RegTmp;
    }
    CW_RTC->CR1_f.ACCESS = 0;
    RTC_LOCK();
}

/**
 * @brief 获取闹钟的设置，时间为BCD格式。
 *
 * @param RTC_Alarm
 * @param RTC_AlarmStruct
 */
void RTC_GetAlarm(uint32_t RTC_Alarm, RTC_AlarmTypeDef *RTC_AlarmStruct)
{
    uint32_t RegTmp = 0;
    assert_param(IS_RTC_ALARM(RTC_Alarm));
    if (RTC_Alarm == RTC_Alarm_A)
    {
        RegTmp = CW_RTC->ALARMA;
        while (RegTmp != CW_RTC->ALARMA)
        {
            RegTmp = CW_RTC->ALARMA;
        }
    }
    else
    {
        RegTmp = CW_RTC->ALARMB;
        while (RegTmp != CW_RTC->ALARMB)
        {
            RegTmp = CW_RTC->ALARMB;
        }
    }
    RTC_AlarmStruct->RTC_AlarmMask = RegTmp & RTC_AlarmMask_All;
    RTC_AlarmStruct->RTC_AlarmTime.H24 = CW_RTC->CR0_f.H24;     // 读CR0是否需要连读两次，待硬件检测
    RTC_AlarmStruct->RTC_AlarmTime.Hour = (uint8_t)((RegTmp & RTC_TIME_HOUR_Msk) >> 16);
    RTC_AlarmStruct->RTC_AlarmTime.Minute = (uint8_t)((RegTmp & RTC_TIME_MINUTE_Msk) >> 8);
    RTC_AlarmStruct->RTC_AlarmTime.Second = (uint8_t)(RegTmp & RTC_TIME_SECOND_Msk);
    if (RTC_AlarmStruct->RTC_AlarmTime.H24 == RTC_HOUR12)
    {
        RTC_AlarmStruct->RTC_AlarmTime.AMPM = RTC_AlarmStruct->RTC_AlarmTime.Hour >> 5;
        RTC_AlarmStruct->RTC_AlarmTime.Hour &= 0x1f;
    }
}

void RTC_AlarmCmd(uint32_t RTC_Alarm, FunctionalState NewState)
{
    assert_param(IS_RTC_CMD_ALARM(RTC_Alarm));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    RTC_UNLOCK();
    if (IS_RTC_START())         // 如果RTC正在运行，则使用WINDOWS、ACCESS访问
    {
        CW_RTC->CR1_f.ACCESS = 1;
        while (!CW_RTC->CR1_f.WINDOW);
    }
    if (RTC_Alarm == RTC_Alarm_A)
    {
        CW_RTC->CR2_f.ALARMAEN = NewState;
    }
    else
    {
        CW_RTC->CR2_f.ALARMBEN = NewState;
    }
    CW_RTC->CR1_f.ACCESS = 0;
    RTC_LOCK();
}

void RTC_TamperTriggerConfig(uint32_t RTC_TamperTrigger)
{
    assert_param(IS_RTC_TAMPER_TRIGGER(RTC_TamperTrigger));
    RTC_UNLOCK();
    if (IS_RTC_START())         // 如果RTC正在运行，则使用WINDOWS、ACCESS访问
    {
        CW_RTC->CR1_f.ACCESS = 1;
        while (!CW_RTC->CR1_f.WINDOW);
    }
    CW_RTC->CR2_f.TAMPEDGE = RTC_TamperTrigger;
    CW_RTC->CR1_f.ACCESS = 0;
    RTC_LOCK();
}

void RTC_TamperCmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    RTC_UNLOCK();
    if (IS_RTC_START())         // 如果RTC正在运行，则使用WINDOWS、ACCESS访问
    {
        CW_RTC->CR1_f.ACCESS = 1;
        while (!CW_RTC->CR1_f.WINDOW);
    }
    CW_RTC->CR2_f.TAMPEN = NewState;
    CW_RTC->CR1_f.ACCESS = 0;
    RTC_LOCK();
}

void RTC_GetTamperDate(RTC_DateTypeDef *RTC_Date)
{
    uint32_t RegTmp = 0;
    do
    {
        RegTmp = CW_RTC->TAMPDATE;
    }
    while (RegTmp != CW_RTC->TAMPDATE);
    RTC_Date->Week = (uint8_t)((RegTmp & RTC_TAMPDATE_WEEK_Msk) >> 13);
    RTC_Date->Month = (uint8_t)((RegTmp & RTC_TAMPDATE_MONTH_Msk) >> 8);
    RTC_Date->Day = (uint8_t)(RegTmp & RTC_TAMPDATE_DAY_Msk);
}

void RTC_GetTamperTime(RTC_TimeTypeDef *RTC_TimeStruct)
{
    uint32_t RegTmp = 0;
    do
    {
        RegTmp = CW_RTC->TAMPTIME;
    }
    while (RegTmp != CW_RTC->TAMPTIME);    // 连续两次读取的内容一致，认为读取成功
    RTC_TimeStruct->Second = (uint8_t)((RegTmp & RTC_TAMPTIME_SECOND_Msk) >> 16);
    RTC_TimeStruct->Minute = (uint8_t)((RegTmp & RTC_TAMPTIME_MINUTE_Msk) >> 8);
    RTC_TimeStruct->Hour = (uint8_t)(RegTmp & RTC_TAMPTIME_HOUR_Msk);
    RTC_TimeStruct->H24 = CW_RTC->CR0_f.H24;  // 读CR0是否需要连读两次，待硬件检测
    if (RTC_TimeStruct->H24 == RTC_HOUR12)
    {
        RTC_TimeStruct->AMPM = RTC_TimeStruct->Hour >> 5;
        RTC_TimeStruct->Hour &= 0x1f;
    }
}


/**
 * @brief 设置RTC的OUTPUT的信号源
 *
 * @param RTC_Output
 */
void RTC_OutputConfig(uint8_t RTC_Output)
{
    assert_param(IS_RTC_RTCOUT_SOURCE(RTC_Output));
    RTC_UNLOCK();
    if (IS_RTC_START())         // 如果RTC正在运行，则使用WINDOWS、ACCESS访问
    {
        CW_RTC->CR1_f.ACCESS = 1;
        while (!CW_RTC->CR1_f.WINDOW);
    }
    CW_RTC->CR2_f.RTCOUT = RTC_Output;
    CW_RTC->CR1_f.ACCESS = 0;
    RTC_LOCK();
}

/**
 * @brief RTC的自动唤醒定时器设置
 *
 * @param RCT_AWTStruct
 */
void RTC_AWTConfig(RTC_AWTTypeDef *RCT_AWTStruct)
{
    assert_param(IS_RTC_AWTTIMER_SOURCE(RCT_AWTStruct->AWT_ClockSource));
    RTC_UNLOCK();
    if (IS_RTC_START())         // 如果RTC正在运行，则使用WINDOWS、ACCESS访问
    {
        CW_RTC->CR1_f.ACCESS = 1;
        while (!CW_RTC->CR1_f.WINDOW);
    }
    CW_RTC->CR2_f.AWTSRC = RCT_AWTStruct->AWT_ClockSource;
    CW_RTC->AWTARR = (uint32_t)RCT_AWTStruct->AWT_ARRValue;
    CW_RTC->CR1_f.ACCESS = 0;
    RTC_LOCK();
}

/**
 * @brief 使能或禁止AWT功能
 *
 * @param NewState
 */
void RTC_AWTCmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    RTC_UNLOCK();
    if (IS_RTC_START())         // 如果RTC正在运行，则使用WINDOWS、ACCESS访问
    {
        CW_RTC->CR1_f.ACCESS = 1;
        while (!CW_RTC->CR1_f.WINDOW);
    }
    CW_RTC->CR2_f.AWTEN = NewState;
    CW_RTC->CR1_f.ACCESS = 0;
    RTC_LOCK();
}

/**
 * @brief
 *
 * @param Period
 */
void RTC_SetInterval(uint8_t Period)
{
    assert_param(IS_RTC_INTERVAL_PERIOD(Period));
    RTC_UNLOCK();
    if (IS_RTC_START())         // 如果RTC正在运行，则使用WINDOWS、ACCESS访问
    {
        CW_RTC->CR1_f.ACCESS = 1;
        while (!CW_RTC->CR1_f.WINDOW);
    }
    CW_RTC->CR0_f.INTERVAL = Period;
    CW_RTC->CR1_f.ACCESS = 0;
    RTC_LOCK();
}

/**
 * @brief 设置RTC的计时时钟来源
 *
 * @param RTC_ClockSource ：只能是RTC_RTCCLK_FROM_LSE、LSI、HSE有效值，字操作，影响WINDOW、ACCESS位
 *                          用户须先启动RTC时钟源
 */
void RTC_SetClockSource(uint32_t RTC_ClockSource)
{
    assert_param(IS_RTC_RTCCLK_SOURCE(RTC_ClockSource));
    RTC_UNLOCK();    /* 解除RTC寄存器的写保护 */
    //  CW_RTC->CR1_f.SOURCE = RTC_ClockSource;    // 设置RTC时钟源
    CW_RTC->CR1 = RTC_ClockSource;    // 设置RTC时钟源,同时将WINDOWS、ACCESS位清零
    RTC_LOCK();
}

/**
 * @brief 设置校准时钟参数：FREQ、STEP、SIGN、COMPEN ||
 * 注:RTC_CalibStruct->Step 为 0 时，要保证 RTC_CalibStruct->RefClock 大于 4MHz ||
 *    RTC_CalibStruct->Step 为 1 时，要保证 RTC_CalibStruct->RefClock 大于 12MHz ||
 *    RTC_CalibStruct->Step 为 2 时，要保证 RTC_CalibStruct->RefClock 大于 24MHz
 *
 * @param RTC_CalibStruct
 */
void RTC_CalibrationConfig(RTC_CalibTypeDef *RTC_CalibStruct)
{
    assert_param(IS_RTC_COMPEN_FREQ(RTC_CalibStruct->Freq));
    assert_param(IS_RTC_COMPEN_STEP(RTC_CalibStruct->Step));
    assert_param(IS_RTC_COMPEN_SIGN(RTC_CalibStruct->Sign));
    assert_param(IS_RTC_COMPEN_VALUE(RTC_CalibStruct->CompensationValue));
    RTC_UNLOCK();
    if (IS_RTC_START())         // 如果RTC正在运行，则使用WINDOWS、ACCESS访问
    {
        CW_RTC->CR1_f.ACCESS = 1;
        while (!CW_RTC->CR1_f.WINDOW);
    }
    CW_RTC->COMPEN = (RTC_CalibStruct->Freq << 16) |
                     (RTC_CalibStruct->Sign << 14) |
                     (RTC_CalibStruct->Step << 12) |
                     RTC_CalibStruct->CompensationValue;
    CW_RTC->CR1_f.ACCESS = 0;
    RTC_LOCK();
}

void RTC_CalibrationCmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    RTC_UNLOCK();
    if (IS_RTC_START())         // 如果RTC正在运行，则使用WINDOWS、ACCESS访问
    {
        CW_RTC->CR1_f.ACCESS = 1;
        while (!CW_RTC->CR1_f.WINDOW);
    }
    CW_RTC->COMPEN_f.EN = NewState;
    CW_RTC->CR1_f.ACCESS = 0;
    RTC_LOCK();
}

/**
  * @brief  Convert a 2 digit decimal to BCD format.
  * @param  Value Byte to be converted
  * @retval Converted byte
  */
uint8_t RTC_BinToBCD(uint8_t Value)
{
    uint32_t bcdhigh = 0U;
    uint8_t Param = Value;
    while (Param >= 10U)
    {
        bcdhigh++;
        Param -= 10U;
    }
    return ((uint8_t)(bcdhigh << 4U) | Param);
}

/**
  * @brief  Convert from 2 digit BCD to Binary.
  * @param  Value BCD value to be converted
  * @retval Converted byte
  */
uint8_t RTC_BCDToBin(uint8_t Value)
{
    uint32_t tmp;
    tmp = (((uint32_t)Value & 0xF0U) >> 4U) * 10U;
    return (uint8_t)(tmp + ((uint32_t)Value & 0x0FU));
}

/**
  * @}
  */
