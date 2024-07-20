/*
 * 立创开发板软硬件资料与相关扩展板软硬件资料官网全部开源
 * 开发板官网：www.lckfb.com
 * 技术支持常驻论坛，任何技术问题欢迎随时交流学习
 * 立创论坛：https://oshwhub.com/forum
 * 关注bilibili账号：【立创开发板】，掌握我们的最新动态！
 * 不靠卖板赚钱，以培养中国工程师为己任
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-12     LCKFB-LP    first version
 */
#include "board.h"

// UARTx
#define DEBUG_USARTx          CW_UART1
#define DEBUG_USART_CLK       RCC_APB2_PERIPH_UART1
#define DEBUG_USART_APBClkENx RCC_APBPeriphClk_Enable2
#define DEBUG_USART_UclkFreq  64000000

// UARTx GPIO
#define DEBUG_USART_GPIO_CLK     RCC_AHB_PERIPH_GPIOA
#define DEBUG_USART_TX_GPIO_PORT CW_GPIOA
#define DEBUG_USART_TX_GPIO_PIN  GPIO_PIN_8
#define DEBUG_USART_RX_GPIO_PORT CW_GPIOA
#define DEBUG_USART_RX_GPIO_PIN  GPIO_PIN_9

// GPIO AF
#define DEBUG_USART_AFTX PA08_AFx_UART1TXD()
#define DEBUG_USART_AFRX PA09_AFx_UART1RXD()

// 中断
#define DEBUG_USART_IRQ UART1_IRQn

void uart1_init(uint32_t __rate);
