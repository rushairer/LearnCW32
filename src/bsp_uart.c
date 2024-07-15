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
#include "bsp_uart.h"
#include "stdio.h"

/******************************************************************
 * �� �� �� �ƣ�uart1_init
 * �� �� ˵ ������ʼ��USART1�Ĵ����շ�����
 * �� �� �� �Σ�__rate��������
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void uart1_init(uint32_t __rate)
{
	//����RCC
	RCC_AHBPeriphClk_Enable(DEBUG_USART_GPIO_CLK, ENABLE); // ʹ��GPIOʱ��
	DEBUG_USART_APBClkENx(DEBUG_USART_CLK, ENABLE);		   // ʹ�ܴ���ʱ��
	
	// ����GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	
    //UART TX RX ����
    DEBUG_USART_AFTX;
    DEBUG_USART_AFRX;
	
    GPIO_InitStructure.Pins = DEBUG_USART_TX_GPIO_PIN;			// ����
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;				// �������
    GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;					// ����ٶȸ�
    GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);	// ��ʼ��GPIO
	
    GPIO_InitStructure.Pins = DEBUG_USART_RX_GPIO_PIN;			
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT_PULLUP;			// ��������
    GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	
	// ����UART
	USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = __rate;				// ������
    USART_InitStructure.USART_Over = USART_Over_16;				// ����USART�Ĺ������ʡ�
    USART_InitStructure.USART_Source = USART_Source_PCLK;		// ����ʱ��Դ
    USART_InitStructure.USART_UclkFreq = DEBUG_USART_UclkFreq;  //����USARTʱ��Ƶ��(����Ƶһ�¼���)
    USART_InitStructure.USART_StartBit = USART_StartBit_FE;	 	//RXD�½��ؿ�ʼ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;		// ֹͣλ1
    USART_InitStructure.USART_Parity = USART_Parity_No ;		// ��ʹ��У��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��ʹ������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	// �շ�ģʽ
    USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	//���ȼ��������ȼ�����
    NVIC_SetPriority(DEBUG_USART_IRQ, 0);
    //UARTx�ж�ʹ��
    NVIC_EnableIRQ(DEBUG_USART_IRQ);
	
	//ʹ��UARTx RC�ж�
    USART_ITConfig(DEBUG_USARTx, USART_IT_RC, ENABLE);
}


#if !defined(__MICROLIB)
//��ʹ��΢��Ļ�����Ҫ�������ĺ���
#if (__ARMCLIB_VERSION <= 6000000)
//�����������AC5  �Ͷ�����������ṹ��
struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

//����_sys_exit()�Ա���ʹ�ð�����ģʽ
void _sys_exit(int x)
{
	x = x;
}
#endif

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
	// ����һ���ֽ�
    USART_SendData(DEBUG_USARTx, (uint8_t)ch);
	
	// �ȴ��������
	while( RESET == USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) ){}
	
    return ch;
}



/******************************************************************
 * �� �� �� �ƣ�UART1_IRQHandler
 * �� �� ˵ ��������1�жϷ�����
 * �� �� �� �Σ���
 * �� �� �� �أ���
 * ��       �ߣ�LC
 * ��       ע����
******************************************************************/
void UART1_IRQHandler(void)
{
    uint8_t TxRxBuffer;
	
    if (USART_GetITStatus(CW_UART1, USART_IT_RC) != RESET)
    {
		// ����һ���ֽ�
        TxRxBuffer = USART_ReceiveData_8bit(CW_UART1);
		
        USART_SendData_8bit(CW_UART1, TxRxBuffer); // �����ݷ���������֤
		
		// �����־λ
        USART_ClearITPendingBit(CW_UART1, USART_IT_RC);
    }
}


