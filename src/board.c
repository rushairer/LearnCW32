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
#include "cw32f030_systick.h"
#include "cw32f030_rcc.h"
#include "cw32f030_gpio.h"

/******************************************************************
 * 函 数 名 称：board_init
 * 函 数 说 明：初始化开发板
 * 函 数 形 参：无
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void board_init(void)
{
	
	RCC_HSE_Enable(RCC_HSE_MODE_OSC,8000000,RCC_HSE_DRIVER_NORMAL,RCC_HSE_FLT_CLOSE);//开启HSE时钟，HSE的频率范围为4MHz-32MHz
	
	RCC_HCLKPRS_Config(RCC_HCLK_DIV1);
	
	RCC_PLL_Enable(RCC_PLLSOURCE_HSEOSC,8000000,RCC_PLL_MUL_8);  //开启PLL，PLL输入为HSE
	
	RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_FLASH,ENABLE); // 使能FLASH时钟
	
	FLASH_SetLatency(FLASH_Latency_3);
	
	RCC_SysClk_Switch( RCC_SYSCLKSRC_PLL );   //切换系统时钟到PLL	
	
	RCC_SystemCoreClockUpdate(64000000);	 //更新系统时钟频率
	
	InitTick(64000000);                    //初始化SysTick

}

/******************************************************************
 * 函 数 名 称：delay_us
 * 函 数 说 明：利用滴答定时器延时多少us
 * 函 数 形 参：__us：延时的时长（单位us）
 * 函 数 返 回：无
 * 作       者：LC
 * 备       注：无
******************************************************************/
void delay_us(unsigned long __us) 
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 38;

    // 计算需要的时钟数 = 延迟微秒数 * 每微秒的时钟数
    ticks = __us * (64000000 / 1000000);

    // 获取当前的SysTick值
    told = SysTick->VAL;

    while (1)
    {
        // 重复刷新获取当前的SysTick值
        tnow = SysTick->VAL;

        if (tnow != told)
        {
            if (tnow < told)
                tcnt += told - tnow;
            else
                tcnt += SysTick->LOAD - tnow + told;

            told = tnow;

            // 如果达到了需要的时钟数，就退出循环
            if (tcnt >= ticks)
                break;
        }
    }
}
//搭配滴答定时器实现的精确ms延时
void delay_ms(unsigned long ms) 
{
	delay_us( ms * 1000 );
}

void delay_1us(unsigned long __us){ delay_us(__us); }
void delay_1ms(unsigned long ms){ delay_ms(ms); }



/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
