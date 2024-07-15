/**
 * @file cw32f030_crc.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-05-08
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

/* Includes ------------------------------------------------------------------*/
#include "cw32f030_crc.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief 采用8bit方式，计算CRC16
 *
 * @param CrcMode    : CRC16_IBM    CRC16_MAXIM
 *                     CRC16_USB    CRC16_MODBUS
 *                     CRC16_CCITT  CRC16_CCITTFALSE
 *                     CRC16_X25    CRC16_XMODEM
 * @param pByteBuf   : uint8_t型Buffer指针
 * @param ByteCnt    ：0x01 - 0xFFFF
 * @return uint16_t  ：0x00 - 0xFFFF
 */
uint16_t CRC16_Calc_8bit(uint8_t CrcMode, uint8_t *pByteBuf, uint16_t ByteCnt)
{
    /* Check the parameters */
    assert_param(IS_CRC_CRC16_MODE(CrcMode));
    CW_CRC->CR = CrcMode;
    while (ByteCnt)
    {
        CW_CRC->DR8 = *pByteBuf;
        pByteBuf++;
        ByteCnt--;
    }
    return (CW_CRC->RESULT16);
}


/**
 * @brief   采用16bit方式，计算CRC16
 *
 * @param CrcMode        : CRC16_IBM    CRC16_MAXIM
 *                         CRC16_USB    CRC16_MODBUS
 *                         CRC16_CCITT  CRC16_CCITTFALSE
 *                         CRC16_X25    CRC16_XMODEM
 * @param pHWBuf         : uint16_t型Buffer指针
 * @param HalfWordCnt    ：0x01 - 0xFFFF
 * @return uint16_t      ：0x00 - 0xFFFF
 */
uint16_t CRC16_Calc_16bit(uint8_t CrcMode, uint16_t *pHWBuf, uint16_t HalfWordCnt)
{
    /* Check the parameters */
    assert_param(IS_CRC_CRC16_MODE(CrcMode));
    CW_CRC->CR = CrcMode;
    while (HalfWordCnt)
    {
        CW_CRC->DR16 = *pHWBuf;
        pHWBuf++;
        HalfWordCnt--;
    }
    return (CW_CRC->RESULT16);
}


/**
 * @brief   采用32bit方式，计算CRC16
 *
 * @param CrcMode    : CRC16_IBM    CRC16_MAXIM
 *                     CRC16_USB    CRC16_MODBUS
 *                     CRC16_CCITT  CRC16_CCITTFALSE
 *                     CRC16_X25    CRC16_XMODEM
 * @param pWBuf      : uint32_t型Buffer指针
 * @param WordCnt    ：0x01 - 0xFFFF
 * @return uint16_t  ：0x00 - 0xFFFF
 */
uint16_t CRC16_Calc_32bit(uint8_t CrcMode, uint32_t *pWBuf, uint16_t WordCnt)
{
    /* Check the parameters */
    assert_param(IS_CRC_CRC16_MODE(CrcMode));
    CW_CRC->CR = CrcMode;
    while (WordCnt)
    {
        CW_CRC->DR32 = *pWBuf;
        pWBuf++;
        WordCnt--;
    }
    return (CW_CRC->RESULT16);
}

/**
 * @brief   采用8bit方式，计算CRC32
 *
 * @param CrcMode       : CRC32_DEFAULT   CRC32_MPEG2
 * @param pByteBuf      : uint8_t型Buffer指针
 * @param ByteCnt       ：0x01 - 0xFFFF
 * @return uint32_t     ：0x00 - 0xFFFF FFFF
 */
uint32_t CRC32_Calc_8bit(uint8_t CrcMode, uint8_t *pByteBuf, uint16_t ByteCnt)
{
    /* Check the parameters */
    assert_param(IS_CRC_CRC32_MODE(CrcMode));
    CW_CRC->CR = CrcMode;
    while (ByteCnt)
    {
        CW_CRC->DR8 = *pByteBuf;
        pByteBuf++;
        ByteCnt--;
    }
    return (CW_CRC->RESULT32);
}


/**
 * @brief 采用16bit方式，计算CRC32
 *
 * @param CrcMode        : CRC32_DEFAULT   CRC32_MPEG2
 * @param pHWBuf         : uint16_t型Buffer指针
 * @param HalfWordCnt    ：0x01 - 0xFFFF
 * @return uint32_t      ：0x00 - 0xFFFF FFFF
 */
uint32_t CRC32_Calc_16bit(uint8_t CrcMode, uint16_t *pHWBuf, uint16_t HalfWordCnt)
{
    /* Check the parameters */
    assert_param(IS_CRC_CRC32_MODE(CrcMode));
    CW_CRC->CR = CrcMode;
    while (HalfWordCnt)
    {
        CW_CRC->DR16 = *pHWBuf;
        pHWBuf++;
        HalfWordCnt--;
    }
    return (CW_CRC->RESULT32);
}


/**
 * @brief   采用32bit方式，计算CRC16
 *
 * @param CrcMode       : CRC32_DEFAULT   CRC32_MPEG2
 * @param pWBuf         : uint32_t型Buffer指针
 * @param WordCnt       ：0x01 - 0xFFFF
 * @return uint32_t     ：0x00 - 0xFFFF FFFF
 */
uint32_t CRC32_Calc_32bit(uint8_t CrcMode, uint32_t *pWBuf, uint16_t WordCnt)
{
    /* Check the parameters */
    assert_param(IS_CRC_CRC32_MODE(CrcMode));
    CW_CRC->CR = CrcMode;
    while (WordCnt)
    {
        CW_CRC->DR32 = *pWBuf;
        pWBuf++;
        WordCnt--;
    }
    return (CW_CRC->RESULT32);
}

//=============================================================================

