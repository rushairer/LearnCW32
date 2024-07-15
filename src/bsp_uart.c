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
#include "bsp_uart.h"
#include "stdio.h"

/******************************************************************
 * 函 数 名 称：uart1_init
 * 函 数 说 明：初始化USART1的串口收发功能
 * 函 数 形 参：__rate：波特率
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void uart1_init(uint32_t __rate)
{
	//配置RCC
	RCC_AHBPeriphClk_Enable(DEBUG_USART_GPIO_CLK, ENABLE); // 使能GPIO时钟
	DEBUG_USART_APBClkENx(DEBUG_USART_CLK, ENABLE);		   // 使能串口时钟
	
	// 配置GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	
    //UART TX RX 复用
    DEBUG_USART_AFTX;
    DEBUG_USART_AFRX;
	
    GPIO_InitStructure.Pins = DEBUG_USART_TX_GPIO_PIN;			// 引脚
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;				// 推挽输出
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;					// 输出速度高
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);	// 初始化GPIO
	
    GPIO_InitStructure.Pins = DEBUG_USART_RX_GPIO_PIN;			
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLUP;			// 上拉输入
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	
	// 配置UART
	USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = __rate;				// 波特率
    USART_InitStructure.USART_Over = USART_Over_16;				// 配置USART的过采样率。
    USART_InitStructure.USART_Source = USART_Source_PCLK;		// 设置时钟源
    USART_InitStructure.USART_UclkFreq = DEBUG_USART_UclkFreq;  //设置USART时钟频率(和主频一致即可)
    USART_InitStructure.USART_StartBit = USART_StartBit_FE;	 	//RXD下降沿开始
    USART_InitStructure.USART_StopBits = USART_StopBits_1;		// 停止位1
    USART_InitStructure.USART_Parity = USART_Parity_No ;		// 不使用校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用流控
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// 收发模式
    USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	//优先级，无优先级分组
    NVIC_SetPriority(DEBUG_USART_IRQ, 0);
    //UARTx中断使能
    NVIC_EnableIRQ(DEBUG_USART_IRQ);
	
	//使能UARTx RC中断
    USART_ITConfig(DEBUG_USARTx, USART_IT_RC, ENABLE);
}


#if !defined(__MICROLIB)
//不使用微库的话就需要添加下面的函数
#if (__ARMCLIB_VERSION <= 6000000)
//如果编译器是AC5  就定义下面这个结构体
struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
	x = x;
}
#endif

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
	// 发送一个字节
    USART_SendData(DEBUG_USARTx, (uint8_t)ch);
	
	// 等待发送完成
	while( RESET == USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) ){}
	
    return ch;
}



/******************************************************************
 * 函 数 名 称：UART1_IRQHandler
 * 函 数 说 明：串口1中断服务函数
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void UART1_IRQHandler(void)
{
    uint8_t TxRxBuffer;
	
    if (USART_GetITStatus(CW_UART1, USART_IT_RC) != RESET)
    {
		// 接收一个字节
        TxRxBuffer = USART_ReceiveData_8bit(CW_UART1);
		
        USART_SendData_8bit(CW_UART1, TxRxBuffer); // 将数据发回用于验证
		
		// 清除标志位
        USART_ClearITPendingBit(CW_UART1, USART_IT_RC);
    }
}


