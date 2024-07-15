/**
 * @file cw32f030_uart.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-06-26
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
#include "cw32f030_uart.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief 通过USARTx发送一个数据(16bit)
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @param Data :待发送的数据
 */
void USART_SendData(UART_TypeDef *USARTx, uint16_t Data)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_DATA_16BIT(Data));
    USARTx->TDR = (Data & (uint16_t)0x01FF);
}

/**
 * @brief 通过USARTx发送一个数据(8bit)
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @param Data :待发送的数据
 */
void USART_SendData_8bit(UART_TypeDef *USARTx, uint8_t Data)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_DATA_8BIT(Data));
    USARTx->TDR = Data;
}

/**
 * @brief 通过USARTx接收一个数据(16bit)
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @return uint16_t :接收的数据
 */
uint16_t USART_ReceiveData(UART_TypeDef *USARTx)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    return (uint16_t)(USARTx->RDR & (uint16_t)0x01FF);
}

/**
 * @brief 通过USARTx接收一个数据(8bit)
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @return uint8_t :接收的数据
 */
uint8_t USART_ReceiveData_8bit(UART_TypeDef *USARTx)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    return (uint8_t)(USARTx->RDR);
}

/**
 * @brief 根据USART_InitStruct中指定的参数初始化UARTx外设
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @param USART_InitStruct :指向USART_InitTypeDef类型结构体的指针
 */
void USART_Init(UART_TypeDef *USARTx, USART_InitTypeDef *USART_InitStruct)
{
    uint16_t integerdivider = 0x00;
    uint16_t fractionaldivider = 0x00;
    float32_t temp = 0;
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_BAUDRATE(USART_InitStruct->USART_BaudRate));
    assert_param(IS_USART_Over(USART_InitStruct->USART_Over));
    assert_param(IS_USART_Source(USART_InitStruct->USART_Source));
    assert_param(IS_USART_UCLKFREQ(USART_InitStruct->USART_UclkFreq));
    assert_param(IS_USART_StartBit(USART_InitStruct->USART_StartBit));
    assert_param(IS_USART_STOPBITS(USART_InitStruct->USART_StopBits));
    assert_param(IS_USART_PARITY(USART_InitStruct->USART_Parity));
    assert_param(IS_USART_MODE(USART_InitStruct->USART_Mode));
    assert_param(IS_USART_HARDWARE_FLOW_CONTROL(USART_InitStruct->USART_HardwareFlowControl));
    /* UARTx_CR1 */
    REGBITS_MODIFY(USARTx->CR1, UARTx_CR1_OVER_Msk | UARTx_CR1_START_Msk  | \
                   UARTx_CR1_STOP_Msk | UARTx_CR1_PARITY_Msk | \
                   UARTx_CR1_RXEN_Msk | UARTx_CR1_TXEN_Msk    \
                   , \
                   (uint32_t)USART_InitStruct->USART_Over | \
                   USART_InitStruct->USART_StartBit       | \
                   USART_InitStruct->USART_StopBits       | \
                   USART_InitStruct->USART_Parity         | \
                   USART_InitStruct->USART_Mode);
    /* UARTx_CR2 */
    REGBITS_MODIFY(USARTx->CR2, UARTx_CR2_SOURCE_Msk | UARTx_CR2_RTSEN_Msk | \
                   UARTx_CR2_CTSEN_Msk  \
                   , \
                   (uint32_t)USART_InitStruct->USART_Source | \
                   USART_InitStruct->USART_HardwareFlowControl);
    /* 波特率设置 */
    if (USART_Over_16 == USART_InitStruct->USART_Over)
    {
        /* 16倍采样 */
        temp = (float32_t)(USART_InitStruct->USART_UclkFreq) / (16 * (USART_InitStruct->USART_BaudRate));
        integerdivider = (uint16_t)temp;
        fractionaldivider = (uint16_t)((temp - integerdivider) * 16 + 0.5);
        USARTx->BRRI = (uint16_t)integerdivider;
        USARTx->BRRF = (uint16_t)fractionaldivider;
    }
    else if (USART_Over_8 == USART_InitStruct->USART_Over)
    {
        /* 8倍采样 */
        integerdivider = (uint16_t)((float32_t)(USART_InitStruct->USART_UclkFreq) / (8 * (USART_InitStruct->USART_BaudRate)) + 0.5);
        USARTx->BRRI = (uint16_t)integerdivider;
    }
    else if (USART_Over_4 == USART_InitStruct->USART_Over)
    {
        /* 4倍采样 */
        integerdivider = (uint16_t)((float32_t)(USART_InitStruct->USART_UclkFreq) / (4 * (USART_InitStruct->USART_BaudRate)) + 0.5);
        USARTx->BRRI = (uint16_t)integerdivider;
    }
    else
    {
        /* 专用采样 */
        /* 专用采样仅适合传输时钟源为LSE或者LSI时，进行2400bps、4800bps或9600bps波特率下的UART通信 */
        integerdivider = (uint16_t)((float32_t)(USART_InitStruct->USART_UclkFreq) * 256 / (USART_InitStruct->USART_BaudRate) + 0.5);
        USARTx->BRRI = (uint16_t)integerdivider;
    }
}

/**
 * @brief 默认值赋值USART_InitStruct结构体成员
 *
 * @param USART_InitStruct :指向USART_InitTypeDef类型结构体的指针
 */
void USART_StructInit(USART_InitTypeDef *USART_InitStruct)
{
    /* USART_InitStruct members default value */
    USART_InitStruct->USART_BaudRate = 9600;
    USART_InitStruct->USART_Over = USART_Over_16;
    USART_InitStruct->USART_Source = USART_Source_PCLK;
    USART_InitStruct->USART_StartBit = USART_StartBit_FE;
    USART_InitStruct->USART_StopBits = USART_StopBits_1;
    USART_InitStruct->USART_Parity = USART_Parity_No ;
    USART_InitStruct->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct->USART_HardwareFlowControl = USART_HardwareFlowControl_None;
}

/**
 * @brief USARTx同步模式初始化，CPOL=1、CPHA=1，只能做主机
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @param USART_ClockInitStruct :指向USART_ClockInitTypeDef类型结构体的指针
 */
void USART_ClockInit(UART_TypeDef *USARTx, USART_ClockInitTypeDef *USART_ClockInitStruct)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CLOCK(USART_ClockInitStruct->USART_Clock));
    assert_param(IS_USART_Source(USART_ClockInitStruct->USART_Source));
    REGBITS_MODIFY(USARTx->CR1, UARTx_CR1_SYNC_Msk, (uint32_t)USART_ClockInitStruct->USART_Clock);
    REGBITS_MODIFY(USARTx->CR2, UARTx_CR2_SOURCE_Msk, (uint32_t)USART_ClockInitStruct->USART_Source);
}

/**
 * @brief 默认值赋值USART_ClockInitStruct结构体成员
 *
 * @param USART_ClockInitStruct :指向USART_ClockInitTypeDef类型结构体的指针
 */
void USART_ClockStructInit(USART_ClockInitTypeDef *USART_ClockInitStruct)
{
    /* USART_ClockInitStruct members default value */
    USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
    USART_ClockInitStruct->USART_Source = USART_Source_PCLK;
}

/**
 * @brief UART1去初始化
 *
 */
void UART1_DeInit(void)
{
    CW_SYSCTRL->APBRST2_f.UART1 = 0;
    CW_SYSCTRL->APBRST2_f.UART1 = 1;
}

/**
 * @brief UART2去初始化
 *
 */
void UART2_DeInit(void)
{
    CW_SYSCTRL->APBRST1_f.UART2 = 0;
    CW_SYSCTRL->APBRST1_f.UART2 = 1;
}

/**
 * @brief UART3去初始化
 *
 */
void UART3_DeInit(void)
{
    CW_SYSCTRL->APBRST1_f.UART3 = 0;
    CW_SYSCTRL->APBRST1_f.UART3 = 1;
}

/**
 * @brief 使能/失能USARTx中断
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @param USART_IT :中断源
 *   参数可以是:
 *     @arg USART_IT_CTS:  CTS信号变化中断
 *     @arg USART_IT_PE:   奇偶校验错误中断
 *     @arg USART_IT_FE:   帧结构错误中断
 *     @arg USART_IT_RC:   接收完成中断
 *     @arg USART_IT_TC:   发送完成中断
 *     @arg USART_IT_TXE:  发送缓冲空中断
 * @param NewState :ENABLE or DISABLE
 */
void USART_ITConfig(UART_TypeDef *USARTx, uint16_t USART_IT, FunctionalState NewState)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_IT(USART_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    NewState ? (USARTx->IER |= USART_IT) : (USARTx->IER &= (uint16_t)~USART_IT);
    // if (NewState != DISABLE)
    // {
    //   USARTx->IER |= USART_IT;
    // }
    // else
    // {
    //   USARTx->IER &= (uint16_t)~USART_IT;
    // }
}

/**
 * @brief 获取USARTx中断标志位
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @param USART_IT :中断源
 *   参数可以是：
 *     @arg USART_IT_CTS:   CTS信号变化中断
 *     @arg USART_IT_PE:    奇偶校验错误中断
 *     @arg USART_IT_FE:    帧结构错误中断
 *     @arg USART_IT_RC:    接收完成中断
 *     @arg USART_IT_TC:    发送完成中断
 *     @arg USART_IT_TXE:   发送缓冲器空中断
 * @return ITStatus :USART_IT当前状态 (SET or RESET)
 */
ITStatus USART_GetITStatus(UART_TypeDef *USARTx, uint16_t USART_IT)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_IT(USART_IT));
    return (REGBITS_GET(USARTx->ISR, USART_IT) ? SET : RESET);
}

/**
 * @brief 清除USARTx中断标志位
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @param USART_IT :中断源
 *   参数可以是：
 *     @arg USART_IT_CTS:   CTS信号变化中断
 *     @arg USART_IT_PE:    奇偶校验错误中断
 *     @arg USART_IT_FE:    帧结构错误中断
 *     @arg USART_IT_RC:    接收完成中断
 *     @arg USART_IT_TC:    发送完成中断
 * @note
 *    -TXE中断标志位只能通过写UARTx_TDR寄存器来清除
 *    -RC中断标志位只能软件清除，不能通过读UARTx_RDR寄存器来清除
 */
void USART_ClearITPendingBit(UART_TypeDef *USARTx, uint16_t USART_IT)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CLEAR_IT(USART_IT));
    REGBITS_CLR(USARTx->ICR, USART_IT);
}

/**
 * @brief 获取USARTx标志位
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @param  USART_FLAG :标志
 *   参数可以是：
 *     @arg USART_FLAG_TXBUSY:  发送忙标志
 *     @arg USART_FLAG_CTSLV:   CTS信号电平状态标志
 *     @arg USART_FLAG_CTS:     CTS信号变化标志
 *     @arg USART_FLAG_MATCH:   从机地址匹配标志
 *     @arg USART_FLAG_PE:      奇偶校验错误标志
 *     @arg USART_FLAG_FE:      帧结构错误标志
 *     @arg USART_FLAG_RC:      接收完成标志
 *     @arg USART_FLAG_TC:      发送完成标志
 *     @arg USART_FLAG_TXE:     发送缓冲器空标志
 * @return FlagStatus :USART_FLAG当前状态 (SET or RESET)
 */
FlagStatus USART_GetFlagStatus(UART_TypeDef *USARTx, uint16_t USART_FLAG)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_FLAG(USART_FLAG));
    return (REGBITS_GET(USARTx->ISR, USART_FLAG) ? SET : RESET);
}

/**
 * @brief 清除USARTx标志位
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @param  USART_FLAG :标志
 *   参数可以是：
 *     @arg USART_FLAG_CTS:     CTS信号变化标志
 *     @arg USART_FLAG_PE:      奇偶校验错误标志
 *     @arg USART_FLAG_FE:      帧结构错误标志
 *     @arg USART_FLAG_RC:      接收完成标志
 *     @arg USART_FLAG_TC:      发送完成标志
 * @note
 *    -TXBUSY、CTSLV、MATCH标志位由硬件自动设置和清除
 *    -TXE标志位只能通过写UARTx_TDR寄存器来清除
 *    -RC标志位只能软件清除，不能通过读UARTx_RDR寄存器来清除
 */
void USART_ClearFlag(UART_TypeDef *USARTx, uint16_t USART_FLAG)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_CLEAR_FLAG(USART_FLAG));
    REGBITS_CLR(USARTx->ICR, USART_FLAG);
}

/**
 * @brief 使能/失能TXD输出、RXD输入
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @param USART_DirectionMode :传输方向
 *   参数可以是：
 *     @arg USART_Mode_Tx: TXD输出
 *     @arg USART_Mode_Rx: RXD输入
 * @param NewState :ENABLE or DISABLE
 */
void USART_DirectionModeCmd(UART_TypeDef *USARTx, uint16_t USART_DirectionMode, FunctionalState NewState)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_MODE(USART_DirectionMode));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    NewState ? (USARTx->CR1 |= USART_DirectionMode) : (USARTx->CR1 &= (uint16_t)~USART_DirectionMode);
    // if (NewState != DISABLE)
    // {
    //   USARTx->CR1 |= USART_DirectionMode;
    // }
    // else
    // {
    //   USARTx->CR1 &= (uint16_t)~USART_DirectionMode;
    // }
}

/**
 * @brief 使能/失能TXD输出信号、RXD输入信号反相
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @param USART_InvPin :反相引脚
 *   参数可以是：
 *     @arg USART_InvPin_Tx: TXD引脚输出信号反相
 *     @arg USART_InvPin_Rx: RXD引脚输入信号反相
 * @param NewState :ENABLE or DISABLE
 */
void USART_InvPinCmd(UART_TypeDef *USARTx, uint16_t USART_InvPin, FunctionalState NewState)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_INVERSTION_PIN(USART_InvPin));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    NewState ? (USARTx->CR2 |= USART_InvPin) : (USARTx->CR2 &= (uint16_t)~USART_InvPin);
    // if (NewState != DISABLE)
    // {
    //   USARTx->CR2 |= USART_InvPin;
    // }
    // else
    // {
    //   USARTx->CR2 &= (uint16_t)~USART_InvPin;
    // }
}

/**
 * @brief 使能/失能USARTx半双工通信
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @param NewState :ENABLE or DISABLE
 */

void USART_HalfDuplexCmd(UART_TypeDef *USARTx, FunctionalState NewState)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    USARTx->CR2_f.SIGNAL = NewState;
}

/**
 * @brief 使能/失能USARTx DMA
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @param USART_DMAReq :DMA请求
 *   参数可以是：
 *     @arg USART_DMAReq_Tx: DMA发送请求
 *     @arg USART_DMAReq_Rx: DMA接收请求
 * @param NewState :ENABLE or DISABLE
 */
void USART_DMACmd(UART_TypeDef *USARTx, uint16_t USART_DMAReq, FunctionalState NewState)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_DMAREQ(USART_DMAReq));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    NewState ? (USARTx->CR2 |= USART_DMAReq) : (USARTx->CR2 &= (uint16_t)~USART_DMAReq);
    // if (NewState != DISABLE)
    // {
    //   USARTx->CR2 |= USART_DMAReq;
    // }
    // else
    // {
    //   USARTx->CR2 &= (uint16_t)~USART_DMAReq;
    // }
}

/**
 * @brief USARTx多机通信配置
 *
 * @param USARTx :USARTx外设
 *        参数可以是:
 *           CW_UART1、CW_UART2、CW_UART3
 * @param USART_Address :从机地址
 * @param USART_AddressMsK :从机地址掩码
 * @note
 *        主机和从机均需配置为自定义校验
 */
void USART_SetMultiMode(UART_TypeDef *USARTx, uint8_t USART_Address, uint8_t USART_AddressMsK)
{
    assert_param(IS_USART_ALL_PERIPH(USARTx));
    assert_param(IS_USART_ADDRESS(USART_Address));
    assert_param(IS_USART_ADDRESSMSK(USART_AddressMsK));
    REGBITS_SET(USARTx->CR2, UARTx_CR2_ADDREN_Msk);
    REGBITS_MODIFY(USARTx->ADDR, UARTx_ADDR_ADDR_Msk, (uint32_t)USART_Address);
    REGBITS_MODIFY(USARTx->MASK, UARTx_MASK_MASK_Msk, (uint32_t)USART_AddressMsK);
}






