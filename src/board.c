/*
 * ������������Ӳ�������������չ����Ӳ�����Ϲ���ȫ����Դ
 * �����������www.lckfb.com
 * ����֧�ֳ�פ��̳���κμ������⻶ӭ��ʱ����ѧϰ
 * ������̳��https://oshwhub.com/forum
 * ��עbilibili�˺ţ������������塿���������ǵ����¶�̬��
 * ��������׬Ǯ���������й�����ʦΪ����
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-12     LCKFB-LP    first version
 */

#include "board.h"
#include "cw32f030_systick.h"
#include "cw32f030_rcc.h"
#include "cw32f030_gpio.h"

/******************************************************************
 * �� �� �� �ƣ�board_init
 * �� �� ˵ ������ʼ��������
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void board_init(void)
{
	
	RCC_HSE_Enable(RCC_HSE_MODE_OSC,8000000,RCC_HSE_DRIVER_NORMAL,RCC_HSE_FLT_CLOSE);//����HSEʱ�ӣ�HSE��Ƶ�ʷ�ΧΪ4MHz-32MHz
	
	RCC_HCLKPRS_Config(RCC_HCLK_DIV1);
	
	RCC_PLL_Enable(RCC_PLLSOURCE_HSEOSC,8000000,RCC_PLL_MUL_8);  //����PLL��PLL����ΪHSE
	
	RCC_AHBPeriphClk_Enable(RCC_AHB_PERIPH_FLASH,ENABLE); // ʹ��FLASHʱ��
	
	FLASH_SetLatency(FLASH_Latency_3);
	
	RCC_SysClk_Switch( RCC_SYSCLKSRC_PLL );   //�л�ϵͳʱ�ӵ�PLL	
	
	RCC_SystemCoreClockUpdate(64000000);	 //����ϵͳʱ��Ƶ��
	
	InitTick(64000000);                    //��ʼ��SysTick

}

/******************************************************************
 * �� �� �� �ƣ�delay_us
 * �� �� ˵ �������õδ�ʱ����ʱ����us
 * �� �� �� �Σ�__us����ʱ��ʱ������λus��
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void delay_us(unsigned long __us) 
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 38;

    // ������Ҫ��ʱ���� = �ӳ�΢���� * ÿ΢���ʱ����
    ticks = __us * (64000000 / 1000000);

    // ��ȡ��ǰ��SysTickֵ
    told = SysTick->VAL;

    while (1)
    {
        // �ظ�ˢ�»�ȡ��ǰ��SysTickֵ
        tnow = SysTick->VAL;

        if (tnow != told)
        {
            if (tnow < told)
                tcnt += told - tnow;
            else
                tcnt += SysTick->LOAD - tnow + told;

            told = tnow;

            // ����ﵽ����Ҫ��ʱ���������˳�ѭ��
            if (tcnt >= ticks)
                break;
        }
    }
}
//����δ�ʱ��ʵ�ֵľ�ȷms��ʱ
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
