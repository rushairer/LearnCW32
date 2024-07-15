/**
 * @file cw32f030_crc.h
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-05-13
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
#ifndef __CW32F03x_CRC_H__
#define __CW32F03x_CRC_H__

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


uint16_t CRC16_Calc_8bit(uint8_t CrcMode, uint8_t  *pByteBuf, uint16_t ByteCnt);
uint16_t CRC16_Calc_16bit(uint8_t CrcMode, uint16_t *pHWBuf, uint16_t HalfWordCnt);
uint16_t CRC16_Calc_32bit(uint8_t CrcMode, uint32_t *pWBuf, uint16_t WordCnt);

uint32_t CRC32_Calc_8bit(uint8_t CrcMode, uint8_t  *pByteBuf, uint16_t ByteCnt);
uint32_t CRC32_Calc_16bit(uint8_t CrcMode, uint16_t *pHWBuf, uint16_t HalfWordCnt);
uint32_t CRC32_Calc_32bit(uint8_t CrcMode, uint32_t *pWBuf, uint16_t WordCnt);


//============================================================

#define CRC16_IBM                               0x00UL
#define CRC16_MAXIM                             0x01UL
#define CRC16_USB                               0x02UL
#define CRC16_MODBUS                            0x03UL
#define CRC16_CCITT                             0x04UL
#define CRC16_CCITTFALSE                        0x05UL
#define CRC16_X25                               0x06UL
#define CRC16_XMODEM                            0x07UL
#define CRC32_DEFAULT                           0x08UL
#define CRC32_MPEG2                             0x09UL


#define IS_CRC_CRC16_MODE(MODE)                 (((MODE) == CRC16_IBM) || \
                                                 ((MODE) == CRC16_MAXIM)  || \
                                                 ((MODE) == CRC16_USB)    || \
                                                 ((MODE) == CRC16_MODBUS) || \
                                                 ((MODE) == CRC16_CCITT)  || \
                                                 ((MODE) == CRC16_CCITTFALSE) || \
                                                 ((MODE) == CRC16_X25)    || \
                                                 ((MODE) == CRC16_XMODEM))
#define IS_CRC_CRC32_MODE(MODE)                 (((MODE) == CRC32_DEFAULT) || \
                                                 ((MODE) == CRC32_MPEG2))

//============================================================

#ifdef __cplusplus
}
#endif

#endif
