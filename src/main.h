/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 CW.
 * All rights reserved.</center></h2>
 *
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "base_types.h"
#include "cw32f030.h"
#include "system_cw32f030.h"
// #include "interrupts_cw32f030.h"

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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */
void LED_Init(void);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT CW *****END OF FILE****/
