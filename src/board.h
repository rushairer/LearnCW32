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

#include "base_types.h"
#include "cw32f030.h"
#include "system_cw32f030.h"

#include "cw32f030_adc.h"
#include "cw32f030_atim.h"
#include "cw32f030_awt.h"
#include "cw32f030_btim.h"
#include "cw32f030_crc.h"
#include "cw32f030_debug.h"
#include "cw32f030_digitalsign.h"
#include "cw32f030_dma.h"
#include "cw32f030_flash.h"
#include "cw32f030_gpio.h"
#include "cw32f030_gtim.h"
#include "cw32f030_i2c.h"
#include "cw32f030_iwdt.h"
#include "cw32f030_lvd.h"
#include "cw32f030_pwr.h"
#include "cw32f030_ram.h"
#include "cw32f030_rcc.h"
#include "cw32f030_rtc.h"
#include "cw32f030_spi.h"
#include "cw32f030_systick.h"
#include "cw32f030_uart.h"
#include "cw32f030_wwdt.h"

void board_init(void);

// ����δ�ʱ��ʵ�ֵľ�ȷus��ʱ
void delay_us(unsigned long __us);

void delay_ms(unsigned long ms);
void delay_1us(unsigned long __us);
void delay_1ms(unsigned long ms);
