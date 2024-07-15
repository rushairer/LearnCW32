/**
 * @file cw32f030_digitalsign.h
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-05-14
 *
 * @copyright Copyright (c) 2021
 *
 */

/*******************************************************************************
*
* 代码许可和免责信息
* 武汉芯源半导体有限公司授予您使用所有编程代码示例的非专属的版权许可，您可以由此
* 生成根据您的特定需要而定制的相似功能。根据不能被排除的任何法定保证，武汉芯源半
* 导体有限公司及其程序开发商和供应商对程序或技术支持（如果有）不提供任何明示或暗
* 含的保证或条件，包括但不限于暗含的有关适销性、适用于某种特定用途和非侵权的保证
* 或条件。
* 无论何种情形，武汉芯源半导体有限公司及其程序开发商或供应商均不对下列各项负责，
* 即使被告知其发生的可能性时，也是如此：数据的丢失或损坏；直接的、特别的、附带的
* 或间接的损害，或任何后果性经济损害；或利润、业务、收入、商誉或预期可节省金额的
* 损失。
* 某些司法辖区不允许对直接的、附带的或后果性的损害有任何的排除或限制，因此某些或
* 全部上述排除或限制可能并不适用于您。
*
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CW32F03x_DIGITALSIGN_H__
#define __CW32F03x_DIGITALSIGN_H__

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "base_types.h"
#include "cw32f030.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/
//============================================================

#define DIGITALSIGN_BASE                        0x00012610UL

#define CHIP_TYPE_BASE                          0x00012610UL
#define PIN_COUNT_BASE                          0x00012626UL
#define FLASH_SIZE_BASE                         0x00012628UL
#define RAM_SIZE_BASE                           0x0001262CUL

#define CHIP_UID_BASE                           0x00012660UL

#define CHIP_TYPE_LENGTH                        22
#define CHIP_UID_LENGTH                         10
//============================================================

//获取芯片型号//
void DIGITALSIGN_GetChipType(uint8_t *pChipType);
//获取管脚数量//
uint16_t DIGITALSIGN_GetPinCount(void);
//获取FLASH容量//
uint32_t DIGITALSIGN_GetFlashSize(void);
//获取RAM容量//
uint32_t DIGITALSIGN_GetRamSize(void);
//获取芯片UID//
void DIGITALSIGN_GetChipUid(uint8_t *pChipUid);

//============================================================


#ifdef __cplusplus
}
#endif

#endif
