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

// 搭配滴答定时器实现的精确us延时
void delay_us(unsigned long __us);

void delay_ms(unsigned long ms);
void delay_1us(unsigned long __us);
void delay_1ms(unsigned long ms);
