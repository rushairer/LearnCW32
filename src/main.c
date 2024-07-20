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
#include "stdio.h"
#include "bsp_uart.h"

int main(void)
{
    board_init(); // 开发板初始化

    uart1_init(115200); // 串口1波特率115200

    GPIO_InitTypeDef GPIO_InitStruct; // GPIO初始化结构体

    __RCC_GPIOC_CLK_ENABLE(); // 使能GPIO时钟

    GPIO_InitStruct.Pins  = GPIO_PIN_13;         // GPIO引脚
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP; // 推挽输出
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;     // 输出速度高
    GPIO_Init(CW_GPIOC, &GPIO_InitStruct);       // 初始化

    while (1) {
        // 高电平
        GPIO_WritePin(CW_GPIOC, GPIO_PIN_13, GPIO_Pin_SET);
        printf("[SET]\r\n");
        delay_ms(100);

        // 低电平
        GPIO_WritePin(CW_GPIOC, GPIO_PIN_13, GPIO_Pin_RESET);
        printf("[RESET]\r\n");
        delay_ms(100);
    }
}
