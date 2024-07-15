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
#ifndef __CW32F030_UART_H
#define __CW32F030_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cw32f030.h"

/******************************************************************************
 * type definitions ('typedef')
 ******************************************************************************/

/**
 * @brief  USART Init Structure definition
 */

typedef struct
{
    uint32_t USART_BaudRate;            /*!< 波特率
                                           计算公式:
                                            - USART_Over = 00， BaudRate = UCLK / (16 * BRRI + BRRF)
                                            - USART_Over = 01， BaudRate = UCLK / (8 * BRRI)
                                            - USART_Over = 10， BaudRate = UCLK / (4 * BRRI)
                                            - USART_Over = 11， BaudRate = (256 * UCLK) / BRRI */

    uint16_t USART_Over;                /*!< 采样方式
                                           参数取值 @ref USART_Over */

    uint16_t USART_Source;              /*!< 传输时钟源UCLK
                                           参数取值 @ref USART_Source */

    uint32_t USART_UclkFreq;            /*!< 传输时钟UCLK频率 Hz */

    uint16_t USART_StartBit;            /*!< 起始位判定方式
                                           参数取值 @ref USART_Start_Bit */

    uint16_t USART_StopBits;            /*!< 停止位长度
                                           参数取值 @ref USART_Stop_Bits */

    uint16_t USART_Parity;              /*!< 校验方式
                                           参数取值 @ref USART_Parity
                                           @note 当设置为无校验时，数据字长为8位；
                                                 当设置为有校验时，数据字长自动设置为9位 */

    uint16_t USART_Mode;                /*!< 发送/接收使能
                                           参数取值 @ref USART_Mode */

    uint16_t USART_HardwareFlowControl; /*!< 硬件流控
                                           参数取值 @ref USART_Hardware_Flow_Control */
} USART_InitTypeDef;

/**
  * @brief  USART Clock Init Structure definition
  */

typedef struct
{
    uint16_t USART_Clock;   /*!< USART同步模式使能/失能
                               参数取值 @ref USART_Clock */

    uint16_t USART_Source;  /*!< 传输时钟源UCLK
                               参数取值 @ref USART_Source */
} USART_ClockInitTypeDef;

/******************************************************************************
 * pre-processor symbols/macros ('#define')
 ******************************************************************************/

/** @defgroup USART_Over
  * @{
  */

#define USART_Over_16                           ((uint16_t)0x0000)
#define USART_Over_8                            ((uint16_t)0x0200)
#define USART_Over_4                            ((uint16_t)0x0400)
#define USART_Over_sp                           ((uint16_t)0x0600)
#define IS_USART_Over(Over)                     (((Over) == USART_Over_16) || \
                                                 ((Over) == USART_Over_8)  || \
                                                 ((Over) == USART_Over_4)  || \
                                                 ((Over) == USART_Over_sp))

/** @defgroup USART_Source
  * @{
  */

#define USART_Source_PCLK                       ((uint16_t)0x0000)
#define USART_Source_LSE                        ((uint16_t)0x0200)
#define USART_Source_LSI                        ((uint16_t)0x0300)
#define IS_USART_Source(Source)                 (((Source) == USART_Source_PCLK) || \
                                                 ((Source) == USART_Source_LSE)  || \
                                                 ((Source) == USART_Source_LSI))

/** @defgroup USART_Start_Bit
  * @{
  */

#define USART_StartBit_FE                       ((uint16_t)0x0000) //RXD下降沿
#define USART_StartBit_LL                       ((uint16_t)0x0100) //RXD低电平
#define IS_USART_StartBit(StartBit)             (((StartBit) == USART_StartBit_FE) || \
                                                 ((StartBit) == USART_StartBit_LL))

/** @defgroup USART_Stop_Bits
  * @{
  */

#define USART_StopBits_1                        ((uint16_t)0x0000)
#define USART_StopBits_2                        ((uint16_t)0x0020)
#define USART_StopBits_1_5                      ((uint16_t)0x0010)
#define IS_USART_STOPBITS(STOPBITS)             (((STOPBITS) == USART_StopBits_1) || \
                                                 ((STOPBITS) == USART_StopBits_2) || \
                                                 ((STOPBITS) == USART_StopBits_1_5))

/** @defgroup USART_Parity
  * @{
  */

#define USART_Parity_No                         ((uint16_t)0x0000)
#define USART_Parity_Even                       ((uint16_t)0x0008)
#define USART_Parity_Odd                        ((uint16_t)0x000C)
#define USART_Parity_User                       ((uint16_t)0x0004)
#define IS_USART_PARITY(PARITY)                 (((PARITY) == USART_Parity_No)|| \
                                                 ((PARITY) == USART_Parity_Even) || \
                                                 ((PARITY) == USART_Parity_Odd)  || \
                                                 ((PARITY) == USART_Parity_User))

/** @defgroup USART_Mode
  * @{
  */

#define USART_Mode_Tx                           ((uint16_t)0x0001)
#define USART_Mode_Rx                           ((uint16_t)0x0002)
#define IS_USART_MODE(MODE)                     ((((MODE) & (uint16_t)0xFFFC) == 0x00) && ((MODE) != (uint16_t)0x00))

/** @defgroup USART_Hardware_Flow_Control
  * @{
  */

#define USART_HardwareFlowControl_None          ((uint16_t)0x0000)
#define USART_HardwareFlowControl_RTS           ((uint16_t)0x0008)
#define USART_HardwareFlowControl_CTS           ((uint16_t)0x0004)
#define USART_HardwareFlowControl_RTS_CTS       ((uint16_t)0x000C)
#define IS_USART_HARDWARE_FLOW_CONTROL(CONTROL)\
                                                (((CONTROL) == USART_HardwareFlowControl_None) || \
                                                 ((CONTROL) == USART_HardwareFlowControl_RTS)  || \
                                                 ((CONTROL) == USART_HardwareFlowControl_CTS)  || \
                                                 ((CONTROL) == USART_HardwareFlowControl_RTS_CTS))

/** @defgroup USART_Clock
  * @{
  */

#define USART_Clock_Disable                     ((uint16_t)0x0000)
#define USART_Clock_Enable                      ((uint16_t)0x0040)
#define IS_USART_CLOCK(CLOCK)                   (((CLOCK) == USART_Clock_Disable) || \
                                                 ((CLOCK) == USART_Clock_Enable))

/** @defgroup USART_Inversion_Pins
  * @{
  */

#define USART_InvPin_Tx                         ((uint16_t)0x0020)
#define USART_InvPin_Rx                         ((uint16_t)0x0010)
#define IS_USART_INVERSTION_PIN(INVPIN)         ((((INVPIN) & (uint16_t)0xFFCF) == 0x00) && ((INVPIN) != (uint16_t)0x00))

/** @defgroup USART_DMA_Requests
  * @{
  */

#define USART_DMAReq_Tx                         ((uint16_t)0x0080)
#define USART_DMAReq_Rx                         ((uint16_t)0x0040)
#define IS_USART_DMAREQ(DMAREQ)                 ((((DMAREQ) & (uint16_t)0xFF3F) == 0x00) && ((DMAREQ) != (uint16_t)0x00))

/** @defgroup USART_Interrupt
  * @{
  */

#define USART_IT_CTS                            ((uint16_t)0x0040)
#define USART_IT_PE                             ((uint16_t)0x0010)
#define USART_IT_FE                             ((uint16_t)0x0008)
#define USART_IT_RC                             ((uint16_t)0x0004)
#define USART_IT_TC                             ((uint16_t)0x0002)
#define USART_IT_TXE                            ((uint16_t)0x0001)
#define IS_USART_IT(IT)                         ((((IT) & (uint16_t)0xFFA0) == 0x00) && ((IT) != (uint16_t)0x00))
#define IS_USART_CLEAR_IT(IT)                   ((((IT) & (uint16_t)0xFFA1) == 0x00) && ((IT) != (uint16_t)0x00))

/** @defgroup USART_Flags
  * @{
  */

#define USART_FLAG_TXBUSY                       ((uint16_t)0x0100)
#define USART_FLAG_CTSLV                        ((uint16_t)0x0080)
#define USART_FLAG_CTS                          ((uint16_t)0x0040)
#define USART_FLAG_MATCH                        ((uint16_t)0x0020)
#define USART_FLAG_PE                           ((uint16_t)0x0010)
#define USART_FLAG_FE                           ((uint16_t)0x0008)
#define USART_FLAG_RC                           ((uint16_t)0x0004)
#define USART_FLAG_TC                           ((uint16_t)0x0002)
#define USART_FLAG_TXE                          ((uint16_t)0x0001)
#define IS_USART_FLAG(FLAG)                     ((((FLAG) & (uint16_t)0xFE00) == 0x00) && ((FLAG) != (uint16_t)0x00))
#define IS_USART_CLEAR_FLAG(FLAG)               ((((FLAG) & (uint16_t)0xFFA1) == 0x00) && ((FLAG) != (uint16_t)0x00))

#define IS_USART_BAUDRATE(BAUDRATE)             (((BAUDRATE) > 0) && ((BAUDRATE) <= 0x00F42400))
#define IS_USART_UCLKFREQ(UCLKFREQ)             (((UCLKFREQ) > 0) && ((UCLKFREQ) <= 0x03D09000))
#define IS_USART_DATA_16BIT(DATA)               ((DATA) <= 0x1FF)
#define IS_USART_DATA_8BIT(DATA)                ((DATA) <= 0xFF)
#define IS_USART_ADDRESS(ADDRESS)               ((ADDRESS) <= 0xFF)
#define IS_USART_ADDRESSMSK(ADDRESSMSK)         ((ADDRESSMSK) <= 0xFF)
#define IS_USART_ALL_PERIPH(PERIPH)             (((PERIPH) == CW_UART1) || \
                                                 ((PERIPH) == CW_UART2) || \
                                                 ((PERIPH) == CW_UART3))

/******************************************************************************
* Global variable definitions (declared in header file with 'extern')
******************************************************************************/


/******************************************************************************
* Global function prototypes
******************************************************************************/

/* 数据收发 */
void USART_SendData(UART_TypeDef *UARTx, uint16_t Data);
void USART_SendData_8bit(UART_TypeDef *UARTx, uint8_t Data);
uint16_t USART_ReceiveData(UART_TypeDef *USARTx);
uint8_t USART_ReceiveData_8bit(UART_TypeDef *USARTx);

/* 初始化 */
void USART_Init(UART_TypeDef *USARTx, USART_InitTypeDef *USART_InitStruct);
void USART_StructInit(USART_InitTypeDef *USART_InitStruct);
void USART_ClockInit(UART_TypeDef *USARTx, USART_ClockInitTypeDef *USART_ClockInitStruct);
void USART_ClockStructInit(USART_ClockInitTypeDef *USART_ClockInitStruct);
void UART1_DeInit(void);
void UART2_DeInit(void);
void UART3_DeInit(void);

/* 中断及标志 */
void USART_ITConfig(UART_TypeDef *USARTx, uint16_t USART_IT, FunctionalState NewState);
ITStatus USART_GetITStatus(UART_TypeDef *USARTx, uint16_t USART_IT);
void USART_ClearITPendingBit(UART_TypeDef *USARTx, uint16_t USART_IT);
FlagStatus USART_GetFlagStatus(UART_TypeDef *USARTx, uint16_t USART_FLAG);
void USART_ClearFlag(UART_TypeDef *USARTx, uint16_t USART_FLAG);

/* 发送和接收控制 */
void USART_DirectionModeCmd(UART_TypeDef *USARTx, uint16_t USART_DirectionMode, FunctionalState NewState);
void USART_InvPinCmd(UART_TypeDef *USARTx, uint16_t USART_InvPin, FunctionalState NewState);

/* 半双工通信 */
void USART_HalfDuplexCmd(UART_TypeDef *USARTx, FunctionalState NewState);

/* DMA */
void USART_DMACmd(UART_TypeDef *USARTx, uint16_t USART_DMAReq, FunctionalState NewState);

/* 多机通信 */
void USART_SetMultiMode(UART_TypeDef *USARTx, uint8_t USART_Address, uint8_t USART_AddressMsK);

#ifdef __cplusplus
}
#endif

#endif /*__CW32F030_UART_H */
/**
  * @}
  */
