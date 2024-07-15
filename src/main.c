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
#include "stdio.h"
#include "bsp_uart.h"

int main(void)
{
    board_init(); // �������ʼ��

    uart1_init(115200); // ����1������115200

    GPIO_InitTypeDef GPIO_InitStruct; // GPIO��ʼ���ṹ��

    __RCC_GPIOC_CLK_ENABLE(); // ʹ��GPIOʱ��

    GPIO_InitStruct.Pins  = GPIO_PIN_13;         // GPIO����
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP; // �������
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;     // ����ٶȸ�
    GPIO_Init(CW_GPIOC, &GPIO_InitStruct);       // ��ʼ��

    while (1) {
        // �ߵ�ƽ
        GPIO_WritePin(CW_GPIOC, GPIO_PIN_13, GPIO_Pin_SET);
        printf("[SET]\r\n");
        delay_ms(100);

        // �͵�ƽ
        GPIO_WritePin(CW_GPIOC, GPIO_PIN_13, GPIO_Pin_RESET);
        printf("[RESET]\r\n");
        delay_ms(100);
    }
}
