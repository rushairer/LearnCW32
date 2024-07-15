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
#ifndef __CW32F030_RTC_H
#define __CW32F030_RTC_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "base_types.h"
#include "cw32f030.h"


typedef struct
{
    uint8_t Day;
    uint8_t Month;
    uint8_t Year;
    uint8_t Week;
} RTC_DateTypeDef;

typedef struct
{
    uint8_t Second;
    uint8_t Minute;
    uint8_t Hour;
    uint8_t AMPM;
    uint8_t H24;                //RTC_HOUR24(1),RTC_HOUR12(0)
} RTC_TimeTypeDef;

typedef struct
{
    uint32_t RTC_ClockSource;
    RTC_TimeTypeDef TimeStruct;
    RTC_DateTypeDef DateStruct;

} RTC_InitTypeDef;


typedef struct
{
    RTC_TimeTypeDef RTC_AlarmTime;
    uint32_t RTC_AlarmMask;            /*!<  @ref RTC_AlarmMask_Definitions */
} RTC_AlarmTypeDef;

typedef struct
{
    uint8_t AWT_ClockSource;
    uint16_t AWT_ARRValue;
} RTC_AWTTypeDef;

typedef struct
{
    uint32_t Freq;
    uint32_t Sign;
    uint32_t Step;
    uint32_t CompensationValue;
} RTC_CalibTypeDef;




#define RTC_Alarm_A                             ((uint32_t)0x00000200)
#define RTC_Alarm_B                             ((uint32_t)0x00000400)
#define IS_RTC_ALARM(ALARM)                     (((ALARM) == RTC_Alarm_A) || ((ALARM) == RTC_Alarm_B))
#define IS_RTC_CMD_ALARM(ALARM) (((ALARM) & (RTC_Alarm_A | RTC_Alarm_B)) != (uint32_t)RESET)

/** @defgroup RTC_ACCESS_TIMEOUT
* @{
* RTC寄存器访问最大次数，RTC_CR1->WINDOW位未检测到1，判定访问RTC寄存器失败
*/

#define RTC_ACCESS_MAXTIMES                     ((uint32_t)200U)


/** @defgroup RTC_RTC1HZ_source
* @{
*/

#define RTC_RTC1HZ_NONE                         (0UL)
#define RTC_RTC1HZ_FROM_LSE                     (1UL << 5)
#define RTC_RTC1HZ_FROM_PCLK                    (3UL << 5)

#define IS_RTC_RTC1HZ_SOURCE(src)               (((src) == RTC_RTC1HZ_NONE) ||\
                                                 ((src) == RTC_RTC1HZ_FROM_PCLK) || \
                                                 ((src) == RTC_RTC1HZ_FROM_LSE))


#define RTC_HOUR24                              (1UL << 3)
#define RTC_HOUR12                              (0UL)
#define IS_RTC_HOUR_FORMAT(fmt)                 (((fmt) == RTC_HOUR24) || ((fmt) == RTC_HOUR12))
#define IS_RTC_HOUR12_FORMAT(fmt)               ((fmt) == RTC_HOUR12)


/** @defgroup RTC_Interval_Value
 * @{
 */

#define RTC_INTERVAL_NONE                       (0X00)
#define RTC_INTERVAL_EVERY_0_5S                 (0x01)
#define RTC_INTERVAL_EVERY_1S                   (0x02)
#define RTC_INTERVAL_EVERY_1M                   (0x03)
#define RTC_INTERVAL_EVERY_1H                   (0x04)
#define RTC_INTERVAL_EVERY_1D                   (0x05)
#define RTC_INTERVAL_EVERY_1MO                  (0x06)

#define IS_RTC_INTERVAL_PERIOD(per)             (per < 7)

/** @defgroup RTC_Clock_source
 * 000：外部晶体时钟LSE
 * 010：内置低频时钟LSI
 * 100：外部晶体时钟HSE / 128
 * 101：外部晶体时钟HSE / 256
 * 110：外部晶体时钟HSE / 512
 * 111：外部晶体时钟HSE / 1024
 * @{
 */

#define RTC_RTCCLK_FROM_LSE                     (0UL)
#define RTC_RTCCLK_FROM_LSI                     (2UL << 8)
#define RTC_RTCCLK_FROM_HSE_128                 (4UL << 8)
#define RTC_RTCCLK_FROM_HSE_256                 (5UL << 8)
#define RTC_RTCCLK_FROM_HSE_512                 (6UL << 8)
#define RTC_RTCCLK_FROM_HSE_1024                (7UL << 8)

#define IS_RTC_RTCCLK_SOURCE(src)               (((src) == RTC_RTCCLK_FROM_LSE) || \
                                                 ((src) == RTC_RTCCLK_FROM_LSI) || \
                                                 ((src) == RTC_RTCCLK_FROM_HSE_128) || \
                                                 ((src) == RTC_RTCCLK_FROM_HSE_256) || \
                                                 ((src) == RTC_RTCCLK_FROM_HSE_512) || \
                                                 ((src) == RTC_RTCCLK_FROM_HSE_1024))

#define RTC_IT_INTERVAL                         (1UL << 6)
#define RTC_IT_TAMPOV                           (1UL << 4)
#define RTC_IT_TAMP                             (1UL << 3)
#define RTC_IT_AWTIMER                          (1UL << 2)
#define RTC_IT_ALARMB                           (1UL << 1)
#define RTC_IT_ALARMA                           (1UL)
#define IS_RTC_GET_IT(IT)                       (((IT) == RTC_IT_INTERVAL) || \
                                                 ((IT) == RTC_IT_TAMPOV)   || \
                                                 ((IT) == RTC_IT_TAMP)     || \
                                                 ((IT) == RTC_IT_AWTIMER)  || \
                                                 ((IT) == RTC_IT_ALARMB)   || \
                                                 ((IT) == RTC_IT_ALARMA))
#define IS_RTC_CONFIG_IT(IT)                    ((((uint8_t)(IT) & 0x20) == 0) && \
                                                 ((uint8_t)(IT) < 0x40))
#define IS_RTC_CLAER_IT(IT)                     ((((uint8_t)(IT) & 0x20) == 0) && \
                                                 ((uint8_t)(IT) < 0x40))

/** @defgroup RTC_AlarmMask_Definitions
  * @{
  */
#define RTC_AlarmMask_None                      ((uint32_t)0x00000000)
#define RTC_AlarmMask_WeekSAT                   ((uint32_t)0x40000000)
#define RTC_AlarmMask_WeekFRI                   ((uint32_t)0x20000000)
#define RTC_AlarmMask_WeekTHU                   ((uint32_t)0x10000000)
#define RTC_AlarmMask_WeekWED                   ((uint32_t)0x08000000)
#define RTC_AlarmMask_WeekTUE                   ((uint32_t)0x04000000)
#define RTC_AlarmMask_WeekMON                   ((uint32_t)0x02000000)
#define RTC_AlarmMask_WeekSun                   ((uint32_t)0x01000000)
#define RTC_AlarmMask_Hours                     ((uint32_t)0x00800000)
#define RTC_AlarmMask_Minutes                   ((uint32_t)0x00008000)
#define RTC_AlarmMask_Seconds                   ((uint32_t)0x00000080)
#define RTC_AlarmMask_All                       ((uint32_t)0x7F808080)
#define IS_ALARM_MASK(MASK)                     (((MASK) & 0x807F7F7F) == (uint32_t)RESET)


#define RTC_TamperTrigger_RisingEdge            (0UL)
#define RTC_TamperTrigger_FallingEdge           (1UL)
#define IS_RTC_TAMPER_TRIGGER(TRIGGER)          (((TRIGGER) == RTC_TamperTrigger_RisingEdge) || \
                                                 ((TRIGGER) == RTC_TamperTrigger_FallingEdge))


/** @defgroup RTC_Compen_step
  * @{
  */
#define RTC_RTCOUT_AS_LOW                       (0x0)
#define RTC_RTCOUT_AS_ALARM_A                   (0x1)
#define RTC_RTCOUT_AS_ALARM_B                   (0x2)
#define RTC_RTCOUT_AS_AWT                       (0x3)

#define IS_RTC_RTCOUT_SOURCE(src)               (src < 4)
/*
#define IS_RTC_RTCOUT_SOURCE(src) (((src) == RTC_RTCOUT_AS_LOW) || \
                                   ((src) == RTC_RTCOUT_AS_ALARM_A) || \
                                   ((src) == RTC_RTCOUT_AS_ALARM_B) || \
                                   ((src) == RTC_RTCOUT_AS_AWT))                                       )
*/

/** @defgroup RTC_TimerSrc_Value
* @{
*/

#define RTC_AWTSOURCE_FROM_RTCCLK_2             (0x0)
#define RTC_AWTSOURCE_FROM_RTCCLK_4             (0x1)
#define RTC_AWTSOURCE_FROM_RTCCLK_8             (0x2)
#define RTC_AWTSOURCE_FROM_RTCCLK_16            (0x3)
#define RTC_AWTSOURCE_FROM_RTC1HZ_1             (0x4)
#define RTC_AWTSOURCE_FROM_RTC1HZ_2             (0x5)
#define RTC_AWTSOURCE_FROM_RTC1HZ_4             (0x6)
#define RTC_AWTSOURCE_FROM_RTC1HZ_8             (0x7)

#define IS_RTC_AWTTIMER_SOURCE(clk)             (clk < 8)
/*
#define IS_RTC_AWTTIMER_SOURCE(clk) (((clk) == RTC_AWTSOURCE_FROM_RTCCLK_2) || \
                                     ((clk) == RTC_AWTSOURCE_FROM_RTCCLK_4) || \
                                     ((clk) == RTC_AWTSOURCE_FROM_RTCCLK_8) || \
                                     ((clk) == RTC_AWTSOURCE_FROM_RTCCLK_16) || \
                                     ((clk) == RTC_AWTSOURCE_FROM_RTC1HZ_1) || \
                                     ((clk) == RTC_AWTSOURCE_FROM_RTC1HZ_2) || \
                                     ((clk) == RTC_AWTSOURCE_FROM_RTC1HZ_4) || \
                                     ((clk) == RTC_AWTSOURCE_FROM_RTC1HZ_8))
*/

/**
  * @}
  */

/** @defgroup RTC_Compen_Freq
  * @{
  */
#define RTC_COMPENFREQ_AS_4MHZ                  (0x0UL)
#define RTC_COMPENFREQ_AS_6MHZ                  (0x1UL)
#define RTC_COMPENFREQ_AS_8MHZ                  (0x2UL)
#define RTC_COMPENFREQ_AS_12MHZ                 (0x3UL)
#define RTC_COMPENFREQ_AS_16MHZ                 (0x4UL)
#define RTC_COMPENFREQ_AS_20MHZ                 (0x5UL)
#define RTC_COMPENFREQ_AS_24MHZ                 (0x6UL)
#define RTC_COMPENFREQ_AS_30MHZ                 (0x7UL)
#define RTC_COMPENFREQ_AS_48MHZ                 (0x8UL)

#define IS_RTC_COMPEN_FREQ(clk)                 (clk < 9)

/**
  * @}
  */

/** @defgroup RTC_Compen_step
  * @{
  */
#define RTC_COMPENSTEP_0_950PPM                 (0x0UL)
#define RTC_COMPENSTEP_0_238PPM                 (0x1UL)
#define RTC_COMPENSTEP_0_119PPM                 (0x2UL)

#define IS_RTC_COMPEN_STEP(stp)                 ((stp) < 3)

/**
  * @}
  */

#define RTC_COMPEN_SIGN_UP                      (0UL)
#define RTC_COMPEN_SIGN_DOWN                    (1UL)
#define IS_RTC_COMPEN_SIGN(SIGN)                ((SIGN) < 2)

#define IS_RTC_COMPEN_VALUE(VAL)                (((VAL) & 0xFFFFF000) == RESET)

/** @defgroup RTC_Month_Day_Definitions
  * @{
  */
#define RTC_Month_January                       ((uint8_t)0x01)
#define RTC_Month_February                      ((uint8_t)0x02)
#define RTC_Month_March                         ((uint8_t)0x03)
#define RTC_Month_April                         ((uint8_t)0x04)
#define RTC_Month_May                           ((uint8_t)0x05)
#define RTC_Month_June                          ((uint8_t)0x06)
#define RTC_Month_July                          ((uint8_t)0x07)
#define RTC_Month_August                        ((uint8_t)0x08)
#define RTC_Month_September                     ((uint8_t)0x09)
#define RTC_Month_October                       ((uint8_t)0x10)
#define RTC_Month_November                      ((uint8_t)0x11)
#define RTC_Month_December                      ((uint8_t)0x12)
#define IS_RTC_MONTH(MON)                       (((MON) >= 1) && ((MON) <= 12))
#define IS_RTC_DAY(DAY)                         (((DAY) >= 1) && ((DAY) <= 31))

/** @defgroup RTC_WeekDay_Definitions
* @{
*/

#define RTC_Weekday_Sunday                      ((uint8_t)0x00)
#define RTC_Weekday_Monday                      ((uint8_t)0x01)
#define RTC_Weekday_Tuesday                     ((uint8_t)0x02)
#define RTC_Weekday_Wednesday                   ((uint8_t)0x03)
#define RTC_Weekday_Thursday                    ((uint8_t)0x04)
#define RTC_Weekday_Friday                      ((uint8_t)0x05)
#define RTC_Weekday_Saturday                    ((uint8_t)0x06)

#define IS_RTC_WEEKDAY(wek)                     (wek < 7)

/** @defgroup RTC_Alarm_Definitions
  * @{
  */
#define IS_RTC_ALARM_DATE_WEEKDAY_DATE(dat)     (((dat) > 0) && ((dat) <= 31))
#define IS_RTC_ALARM_DATE_WEEKDAY_WEEKDAY(wek)  (((wek) == RTC_Weekday_Monday) || \
                                                 ((wek) == RTC_Weekday_Tuesday) ||   \
                                                 ((wek) == RTC_Weekday_Wednesday) || \
                                                 ((wek) == RTC_Weekday_Thursday) ||  \
                                                 ((wek) == RTC_Weekday_Friday) ||    \
                                                 ((wek) == RTC_Weekday_Saturday) ||  \
                                                 ((wek) == RTC_Weekday_Sunday))


/** @defgroup RTC_Time_Definitions
  * @{
  */
#define RTC_12_HOUR_CLOCK                       0
#define RTC_24_HOUR_CLOCK                       1
#define IS_RTC_HOUR12(hor)                      (((hor) >= 1) && ((hor) <= 12))
#define IS_RTC_HOUR24(hor)                      ((hor) <= 23)
#define IS_RTC_MINUTES(min)                     ((min) <= 59)
#define IS_RTC_SECONDS(sec)                     ((sec) <= 59)

/** @defgroup RTC_AM_PM_Definitions
  * @{
  */
#define RTC_H12_AM                              (0UL)
#define RTC_H12_PM                              (1UL)
#define IS_RTC_H12_AMPM(apm)                    (((apm) == RTC_H12_AM) || ((apm) == RTC_H12_PM))

/** @defgroup RTC_Year_Date_Definitions
  * @{
  */
#define IS_RTC_YEAR(yer)                        ((yer) <= 99)

/** @defgroup RTC_KEY_WORD
  * @{
  */
#define RTC_KEY_WORD1                           ((uint8_t)0xCA)
#define RTC_KEY_WORD2                           ((uint8_t)0x53)

#define RTC_KEY_LOCKW                           ((uint8_t)0x55)

#define IS_RTC_KEYWORD(kwd)                     (((kwd) == RTC_KEY_WORD1) || ((kwd) == RTC_KEY_WORD2))

#define RTC_UNLOCK()                            do{ CW_RTC->KEY_f.KEY = RTC_KEY_WORD1;\
                                                    CW_RTC->KEY_f.KEY = RTC_KEY_WORD2; }while (0)
#define RTC_LOCK()                              do{ CW_RTC->KEY_f.KEY = RTC_KEY_WORD1; \
                                                    CW_RTC->KEY_f.KEY = RTC_KEY_WORD1;}while (0)


/**
  * @}
  */
#define RTC_DATE_RESET_VALUE                    ((uint32_t) 0x00000000)
#define RTC_TIME_RESET_VALUE                    ((uint32_t) 0x12000000)
#define RTC_ALARMA_RESET_VALUE                  ((uint32_t) 0x12000000)
#define RTC_ALARMB_RESET_VALUE                  ((uint32_t) 0x12000000)
#define RTC_TAMPDATA_RESET_VALUE                ((uint32_t) 0x00000000)
#define RTC_TAMPTIME_RESET_VALUE                ((uint32_t) 0x00000000)
#define RTC_AWTARR_RESET_VALUE                  ((uint32_t) 0x0000FFFF)
#define RTC_IER_RESET_VALUE                     ((uint32_t) 0x00000000)


//============================================================

//RTC CONTROLLER REGSITER0
#define RTC_START_ENABLE()                      (CW_RTC->CR0_f.START = 1)
#define RTC_START_DISABLE()                     (CW_RTC->CR0_f.START = 0)

#define RTC_RTC1HZ_PCLK()                       (CW_RTC->CR0_f.RTC1HZ = RTC_RTC1HZ_FROM_PCLK)
#define RTC_RTC1HZ_LSE()                        (CW_RTC->CR0_f.RTC1HZ = RTC_RTC1HZ_FROM_LSE)

#define RTC_AMPM_12HOUR()                       (CW_RTC->CR0_f.AMPM = 0)
#define RTC_AMPM_24HOUR()                       (CW_RTC->CR0_f.AMPM = 1)

#define RTC_INTERVAL_0_5S()                     (CW_RTC->CR0_f.INTERVAL = RTC_INTERVAL_EVERY_0_5S)
#define RTC_INTERVAL_1S()                       (CW_RTC->CR0_f.INTERVAL = RTC_INTERVAL_EVERY_1S)
#define RTC_INTERVAL_1M()                       (CW_RTC->CR0_f.INTERVAL = RTC_INTERVAL_EVERY_1M)
#define RTC_INTERVAL_1H()                       (CW_RTC->CR0_f.INTERVAL = RTC_INTERVAL_EVERY_1H)
#define RTC_INTERVAL_1D()                       (CW_RTC->CR0_f.INTERVAL = RTC_INTERVAL_EVERY_1D)
#define RTC_INTERVAL_1MO()                      (CW_RTC->CR0_f.INTERVAL = RTC_INTERVAL_EVERY_1MO)

#define IS_RTC_START()                          (CW_RTC->CR0 & bv7)

//============================================================
//RTC CONTROLLER REGSITER1
#define RTC_RTCCLK_LSE()                        (CW_RTC->CR1_f.SOURCE = RTC_RTCCLK_FROM_LSE)
#define RTC_RTCCLK_LSI()                        (CW_RTC->CR1_f.SOURCE = RTC_RTCCLK_FROM_LIE)
#define RTC_RTCCLK_HSE128()                     (CW_RTC->CR1_f.SOURCE = RTC_RTCCLK_FROM_HSE_128)
#define RTC_RTCCLK_HSE256()                     (CW_RTC->CR1_f.SOURCE = RTC_RTCCLK_FROM_HSE_256)
#define RTC_RTCCLK_HSE512()                     (CW_RTC->CR1_f.SOURCE = RTC_RTCCLK_FROM_HSE_512)
#define RTC_RTCCLK_HSE1024()                    (CW_RTC->CR1_f.SOURCE = RTC_RTCCLK_FROM_HSE_1024)

#define RTC_WINDOW_GETVALUE()                   (CW_RTC->CR1_f.WINDOW)
#define RTC_ACCESS_GETVALUE()                   (CW_RTC->CR1_f.ACCESS)
#define RTC_ACCESS_SET()                        (CW_RTC->CR1_f.ACCESS = 1)
#define RTC_ACCESS_RESET()                      (CW_RTC->CR1_f.ACCESS = 0)

//============================================================
//RTC CONTROLLER REGSITER2
#define RTC_ALARM_A_ENABLE()                    (CW_RTC->CR2_f.ALARMAEN = 1)
#define RTC_ALARM_A_DISABLE()                   (CW_RTC->CR2_f.ALARMAEN = 0)
#define RTC_ALARM_B_ENABLE()                    (CW_RTC->CR2_f.ALARMBEN = 1)
#define RTC_ALARM_B_DISABLE()                   (CW_RTC->CR2_f.ALARMBEN = 0)
#define RTC_AWT_ENABLE()                        (CW_RTC->CR2_f.AWTEN = 1)
#define RTC_AWT_DISABLE()                       (CW_RTC->CR2_f.AWTEN = 0)
#define RTC_TAMP_ENABLE()                       (CW_RTC->CR2_f.TAMPEN = 1)
#define RTC_TAMP_DISABLE()                      (CW_RTC->CR2_f.TAMPEN = 0)
#define RTC_RTCOUT_LOW()                        (CW_RTC->CR2_f.RTCOUT = RTC_RTCOUT_AS_LOW)
#define RTC_RTCOUT_ALARM_A()                    (CW_RTC->CR2_f.RTCOUT = RTC_RTCOUT_AS_ALARM_A)
#define RTC_RTCOUT_ALARM_B()                    (CW_RTC->CR2_f.RTCOUT = RTC_RTCOUT_AS_ALARM_B)
#define RTC_RTCOUT_AWT()                        (CW_RTC->CR2_f.RTCOUT = RTC_RTCOUT_AS_AWT)
#define RTC_TAMPEDGE_FALL()                     (CW_RTC->CR2_f.TAMPEDGE = 1)
#define RTC_TAMPEDGE_RISE()                     (CW_RTC->CR2_f.TAMPEDGE = 0)
#define RTC_AWTSOURCE_RTCLK_2()                 (CW_RTC->CR2_f.TIMERSRC = RTC_AWTSOURCE_FROM_RTCCLK_2)
#define RTC_AWTSOURCE_RTCLK_4()                 (CW_RTC->CR2_f.TIMERSRC = RTC_AWTSOURCE_FROM_RTCCLK_4)
#define RTC_AWTSOURCE_RTCLK_8()                 (CW_RTC->CR2_f.TIMERSRC = RTC_AWTSOURCE_FROM_RTCCLK_8)
#define RTC_AWTSOURCE_RTCLK_16()                (CW_RTC->CR2_f.TIMERSRC = RTC_AWTSOURCE_FROM_RTCCLK_16)
#define RTC_AWTSOURCE_RTC1HZ_1()                (CW_RTC->CR2_f.TIMERSRC = RTC_AWTSOURCE_FROM_RTC1HZ_1)
#define RTC_AWTSOURCE_RTC1HZ_2()                (CW_RTC->CR2_f.TIMERSRC = RTC_AWTSOURCE_FROM_RTC1HZ_2)
#define RTC_AWTSOURCE_RTC1HZ_4()                (CW_RTC->CR2_f.TIMERSRC = RTC_AWTSOURCE_FROM_RTC1HZ_4)
#define RTC_AWTSOURCE_RTC1HZ_8()                (CW_RTC->CR2_f.TIMERSRC = RTC_AWTSOURCE_FROM_RTC1HZ_8)

//============================================================
//RTC COMPEN REGSITER
#define RTC_COMPEN_ENABLE()                     (CW_RTC->COMPEN_f.EN = 1)
#define RTC_COMPEN_DISABLE()                    (CW_RTC->COMPEN_f.EN = 0)

#define RTC_COMPEN_STEP_0_950PPM()              (CW_RTC->COMPEN_f.STEP = RTC_COMPENSTEP_0_950PPM)
#define RTC_COMPEN_STEP_0_238PPM()              (CW_RTC->COMPEN_f.STEP = RTC_COMPENSTEP_0_238PPM)
#define RTC_COMPEN_STEP_0_119PPM()              (CW_RTC->COMPEN_f.STEP = RTC_COMPENSTEP_0_119PPM)

//============================================================
//RTC ALARM A CONTROLLER REGSITER
#define RTC_ALARMA_HOURMASK_ENABLE()            (CW_RTC->ALARMA_f.HOURMASK = 1)
#define RTC_ALARMA_HOURMASK_DISABLE()           (CW_RTC->ALARMA_f.HOURMASK = 0)

#define RTC_ALARMA_MINUTEMASK_ENABLE()          (CW_RTC->ALARMA_f.MINUTEMASK = 1)
#define RTC_ALARMA_MINUTEMASK_DISABLE()         (CW_RTC->ALARMA_f.MINUTEMASK = 0)

#define RTC_ALARMA_SECONDMASK_ENABLE()          (CW_RTC->ALARMA_f.SECONDMASK = 1)
#define RTC_ALARMA_SECONDMASK_DISABLE()         (CW_RTC->ALARMA_f.SECONDMASK = 0)

//============================================================
//RTC ALARM B CONTROLLER REGSITER
#define RTC_ALARMB_HOURMASK_ENABLE()            (CW_RTC->ALARMB_f.HOURMASK = 1)
#define RTC_ALARMB_HOURMASK_DISABLE()           (CW_RTC->ALARMB_f.HOURMASK = 0)

#define RTC_ALARMB_MINUTEMASK_ENABLE()          (CW_RTC->ALARMB_f.MINUTEMASK = 1)
#define RTC_ALARMB_MINUTEMASK_DISABLE()         (CW_RTC->ALARMB_f.MINUTEMASK = 0)

#define RTC_ALARMB_SECONDMASK_ENABLE()          (CW_RTC->ALARMB_f.SECONDMASK = 1)
#define RTC_ALARMB_SECONDMASK_DISABLE()         (CW_RTC->ALARMB_f.SECONDMASK = 0)

//============================================================
//RTC INTERRUPT ENABLE REGSITER
#define RTC_IE_INTERVAL_ENABLE()                (CW_RTC->IER_f.INTERVAL = 1)
#define RTC_IE_INTERVAL_DISABLE()               (CW_RTC->IER_f.INTERVAL = 0)

#define RTC_IE_TAMPOV_ENABLE()                  (CW_RTC->IER_f.TAMPOV = 1)
#define RTC_IE_TAMPOV_DISABLE()                 (CW_RTC->IER_f.TAMPOV = 0)

#define RTC_IE_TAMP_ENABLE()                    (CW_RTC->IER_f.TAMP = 1)
#define RTC_IE_TAMP_DISABLE()                   (CW_RTC->IER_f.TAMP = 0)

#define RTC_IE_AWTIMER_ENABLE()                 (CW_RTC->IER_f.AWTIMER = 1)
#define RTC_IE_AWTIMER_DISABLE()                (CW_RTC->IER_f.AWTIMER = 0)

#define RTC_IE_ALARMA_ENABLE()                  (CW_RTC->IER_f.ALARMA = 1)
#define RTC_IE_ALARMA_DISABLE()                 (CW_RTC->IER_f.ALARMA = 0)

#define RTC_IE_ALARMB_ENABLE()                  (CW_RTC->IER_f.ALARMB = 1)
#define RTC_IE_ALARMB_DISABLE()                 (CW_RTC->IER_f.ALARMB = 0)

//============================================================
//RTC INTERRUPT CLEAR REGSITER
#define RTC_IE_INTERVAL_CLEAR()                 (CW_RTC->ICR_f.INTERVAL = 0)
#define RTC_IE_TAMPOV_CLEAR()                   (CW_RTC->ICR_f.TAMPOV = 0)
#define RTC_IE_TAMP_CLEAR()                     (CW_RTC->ICR_f.TAMP = 0)
#define RTC_IE_AWTIMER_CLEAR()                  (CW_RTC->ICR_f.AWTIMER = 0)
#define RTC_IE_ALARMA_CLEAR()                   (CW_RTC->ICR_f.ALARMA = 0)
#define RTC_IE_ALARMB_CLEAR()                   (CW_RTC->ICR_f.ALARMB = 0)



//============================================================
//  CW32F030 RTC HAL API Function（Total： 14），及所有位域的宏命令
//============================================================
void RTC_DeInit(void);
ErrorStatus RTC_Init(RTC_InitTypeDef *RTC_InitStruct);
void RTC_Cmd(FunctionalState NewState);
ITStatus RTC_GetITState(uint32_t RTC_ITState);
void RTC_ITConfig(uint32_t RTC_IT, FunctionalState NewState);
void RTC_ClearITPendingBit(uint32_t RTC_IT);
void RTC_SetTime(RTC_TimeTypeDef *RTC_TimeStruct);
void RTC_SetDate(RTC_DateTypeDef *RTC_Date);
void RTC_GetTime(RTC_TimeTypeDef *RTC_TimeStruct);
void RTC_GetDate(RTC_DateTypeDef *RTC_Date);
void RTC_SetAlarm(uint32_t RTC_Alarm, RTC_AlarmTypeDef *RTC_AlarmStruct);
void RTC_GetAlarm(uint32_t RTC_Alarm, RTC_AlarmTypeDef *RTC_AlarmStruct);
void RTC_AlarmCmd(uint32_t RTC_Alarm, FunctionalState NewState);
void RTC_TamperTriggerConfig(uint32_t RTC_TamperTrigger);
void RTC_TamperCmd(FunctionalState NewState);
void RTC_GetTamperDate(RTC_DateTypeDef *RTC_Date);
void RTC_GetTamperTime(RTC_TimeTypeDef *RTC_TimeStruct);
void RTC_OutputConfig(uint8_t RTC_Output);
void RTC_AWTConfig(RTC_AWTTypeDef *RCT_AWTStruct);
void RTC_AWTCmd(FunctionalState NewState);
void RTC_SetInterval(uint8_t Period);
void RTC_SetClockSource(uint32_t RTC_ClockSource);
void RTC_CalibrationConfig(RTC_CalibTypeDef *RTC_CalibStruct);
void RTC_CalibrationCmd(FunctionalState NewState);
uint8_t RTC_BinToBCD(uint8_t Value);
uint8_t RTC_BCDToBin(uint8_t Value);

#ifdef __cplusplus
}
#endif

#endif /*__CW32F030_RTC_H */
/**
  * @}
  */
