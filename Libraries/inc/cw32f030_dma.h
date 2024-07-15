/**
 * @file cw32f030_dma.h
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-05-17
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
#ifndef __CW32F03x_DMA_H__
#define __CW32F03x_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "base_types.h"
#include "cw32f030.h"
#include "system_cw32f030.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/
//============================================================
typedef struct
{
    uint32_t DMA_Mode;                 /*!< Specifies the operation mode of the DMAy Channelx.
                                        This parameter can be a value of  */
    uint32_t DMA_TransferWidth;        ///transfer data width
    uint32_t DMA_SrcInc;               /*!< Specifies whether the SRC address register is incremented or not.
                                        This parameter can be a value of @ref DMA_memory_incremented_mode */
    uint32_t DMA_DstInc;               /*!< Specifies whether the DST address register is incremented or not.
                                        This parameter can be a value of @ref DMA_peripheral_incremented_mode */
    uint32_t TrigMode ;

    uint32_t HardTrigSource ;

    uint32_t DMA_TransferCnt;           ///< Transfer counter

    uint32_t DMA_SrcAddress;           ///< Source address>

    uint32_t DMA_DstAddress;           ///< Dest address>

} DMA_InitTypeDef;


#define IS_DMA_ALL_PERIPH(PERIPH)               (((PERIPH) == CW_DMACHANNEL1) || \
                                                 ((PERIPH) == CW_DMACHANNEL2) || \
                                                 ((PERIPH) == CW_DMACHANNEL3) || \
                                                 ((PERIPH) == CW_DMACHANNEL4) || \
                                                 ((PERIPH) == CW_DMACHANNEL5))

#define DMA_MODE_BULK                           0x00UL
#define DMA_MODE_BLOCK                          0x08UL
#define IS_DMA_MODE(MODE)                       (((MODE) == DMA_MODE_BULK) || \
                                                 ((MODE) == DMA_MODE_BLOCK))

#define DMA_SrcAddress_Fix                      0x00UL
#define DMA_SrcAddress_Increase                 0x10UL
#define IS_DMA_SRCADDRESS_INC(INSTRANCE)        (((INSTRANCE) == DMA_SrcAddress_Increase)  || \
                                                 ((INSTRANCE) == DMA_SrcAddress_Fix))

#define DMA_DstAddress_Fix                      0x00UL
#define DMA_DstAddress_Increase                 0x20UL
#define IS_DMA_DSTADDRESS_INC(INSTRANCE)        (((INSTRANCE) == DMA_DstAddress_Increase)  || \
                                                 ((INSTRANCE) == DMA_DstAddress_Fix))

#define DMA_TRANSFER_WIDTH_8BIT                 0x00UL
#define DMA_TRANSFER_WIDTH_16BIT                0x40UL
#define DMA_TRANSFER_WIDTH_32BIT                0x80UL
#define IS_DMA_TRANSFER_WIDTH(INSTRANCE)        (((INSTRANCE) == DMA_TRANSFER_WIDTH_8BIT)  || \
                                                 ((INSTRANCE) == DMA_TRANSFER_WIDTH_16BIT) || \
                                                 ((INSTRANCE) == DMA_TRANSFER_WIDTH_32BIT))

#define IS_DMA_TRANSFERCNT(CNT)                 (((CNT)>= 1) && ((CNT)<= 65535))

#define DMA_SWTrig                              0x00UL
#define DMA_HardTrig                            0x01UL
#define IS_DMA_TRIG(TRIG)                       (((TRIG) == DMA_SWTrig) || \
                                                 ((TRIG) == DMA_HardTrig))

#define DMA_HardTrig_UART1_RXBufferNE           (uint32_t)(0x00UL << 2)
#define DMA_HardTrig_UART1_TXBufferE            (uint32_t)(0x01UL << 2)
#define DMA_HardTrig_UART2_RXBufferNE           (uint32_t)(0x02UL << 2)
#define DMA_HardTrig_UART2_TXBufferE            (uint32_t)(0x03UL << 2)
#define DMA_HardTrig_UART3_RXBufferNE           (uint32_t)(0x04UL << 2)
#define DMA_HardTrig_UART3_TXBufferE            (uint32_t)(0x05UL << 2)

#define DMA_HardTrig_SPI1_RXBufferNE            (uint32_t)(0x06UL << 2)
#define DMA_HardTrig_SPI1_TXBufferE             (uint32_t)(0x07UL << 2)
#define DMA_HardTrig_SPI2_RXBufferNE            (uint32_t)(0x08UL << 2)
#define DMA_HardTrig_SPI2_TXBufferE             (uint32_t)(0x09UL << 2)

#define DMA_HardTrig_ADC_TRANSCOMPLETE          (uint32_t)(0x0AUL << 2)

#define DMA_HardTrig_BTIM1_OVERINT              (uint32_t)(0x0BUL << 2)
#define DMA_HardTrig_BTIM1_TRIGINT              (uint32_t)(0x0CUL << 2)
#define DMA_HardTrig_BTIM2_OVERINT              (uint32_t)(0x0DUL << 2)
#define DMA_HardTrig_BTIM2_TRIGINT              (uint32_t)(0x0EUL << 2)
#define DMA_HardTrig_BTIM3_OVERINT              (uint32_t)(0x0FUL << 2)
#define DMA_HardTrig_BTIM3_TRIGINT              (uint32_t)(0x10UL << 2)

#define DMA_HardTrig_ATIM_CH1A2A3A4             (uint32_t)(0x11UL << 2)
#define DMA_HardTrig_ATIM_CH1B2B3B              (uint32_t)(0x12UL << 2)

#define DMA_HardTrig_GTIM1_OVERINT              (uint32_t)(0x13UL << 2)
#define DMA_HardTrig_GTIM1_TRIGINT              (uint32_t)(0x14UL << 2)
#define DMA_HardTrig_GTIM1_CH1COMINT            (uint32_t)(0x15UL << 2)
#define DMA_HardTrig_GTIM1_CH2COMINT            (uint32_t)(0x16UL << 2)
#define DMA_HardTrig_GTIM1_CH3COMINT            (uint32_t)(0x17UL << 2)
#define DMA_HardTrig_GTIM1_CH4COMINT            (uint32_t)(0x18UL << 2)

#define DMA_HardTrig_GTIM2_OVERINT              (uint32_t)(0x19UL << 2)
#define DMA_HardTrig_GTIM2_TRIGINT              (uint32_t)(0x1AUL << 2)
#define DMA_HardTrig_GTIM2_CH1COMINT            (uint32_t)(0x1BUL << 2)
#define DMA_HardTrig_GTIM2_CH2COMINT            (uint32_t)(0x1CUL << 2)
#define DMA_HardTrig_GTIM2_CH3COMINT            (uint32_t)(0x1DUL << 2)
#define DMA_HardTrig_GTIM2_CH4COMINT            (uint32_t)(0x1EUL << 2)

#define DMA_HardTrig_GTIM3_OVERINT              (uint32_t)(0x1FUL << 2)
#define DMA_HardTrig_GTIM3_TRIGINT              (uint32_t)(0x20UL << 2)
#define DMA_HardTrig_GTIM3_CH1COMINT            (uint32_t)(0x21UL << 2)
#define DMA_HardTrig_GTIM3_CH2COMINT            (uint32_t)(0x22UL << 2)
#define DMA_HardTrig_GTIM3_CH3COMINT            (uint32_t)(0x23UL << 2)
#define DMA_HardTrig_GTIM3_CH4COMINT            (uint32_t)(0x24UL << 2)

#define DMA_HardTrig_GTIM4_OVERINT              (uint32_t)(0x25UL << 2)
#define DMA_HardTrig_GTIM4_TRIGINT              (uint32_t)(0x26UL << 2)
#define DMA_HardTrig_GTIM4_CH1COMINT            (uint32_t)(0x27UL << 2)
#define DMA_HardTrig_GTIM4_CH2COMINT            (uint32_t)(0x28UL << 2)
#define DMA_HardTrig_GTIM4_CH3COMINT            (uint32_t)(0x29UL << 2)
#define DMA_HardTrig_GTIM4_CH4COMINT            (uint32_t)(0x2AUL << 2)

#define IS_DMA_HARD_TRIGSRC(TRIGSRC)            (((TRIGSRC) == DMA_HardTrig_UART1_RXBufferNE) || \
                                                 ((TRIGSRC) == DMA_HardTrig_UART1_TXBufferE)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_UART2_RXBufferNE) || \
                                                 ((TRIGSRC) == DMA_HardTrig_UART2_TXBufferE)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_UART3_RXBufferNE) || \
                                                 ((TRIGSRC) == DMA_HardTrig_UART3_TXBufferE)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_SPI1_RXBufferNE)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_SPI1_TXBufferE)   || \
                                                 ((TRIGSRC) == DMA_HardTrig_SPI2_RXBufferNE)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_SPI2_TXBufferE)   || \
                                                 ((TRIGSRC) == DMA_HardTrig_ADC_TRANSCOMPLETE)|| \
                                                 ((TRIGSRC) == DMA_HardTrig_BTIM1_OVERINT)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_BTIM1_TRIGINT)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_BTIM2_OVERINT)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_BTIM2_TRIGINT)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_BTIM3_OVERINT)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_BTIM3_TRIGINT)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_ATIM_CH1A2A3A4)   || \
                                                 ((TRIGSRC) == DMA_HardTrig_ATIM_CH1B2B3B)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM1_OVERINT)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM1_TRIGINT)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM1_CH1COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM1_CH2COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM1_CH3COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM1_CH4COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM2_OVERINT)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM2_TRIGINT)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM2_CH1COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM2_CH2COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM2_CH3COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM2_CH4COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM3_OVERINT)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM3_TRIGINT)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM3_CH1COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM3_CH2COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM3_CH3COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM3_CH4COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM4_OVERINT)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM4_TRIGINT)    || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM4_CH1COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM4_CH2COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM4_CH3COMINT)  || \
                                                 ((TRIGSRC) == DMA_HardTrig_GTIM4_CH4COMINT))


#define DMA_CHANNEL_EN                          bv0                  //DMA CHANNEL ENABLE
#define DMA_SOFTTRIG_EN                         bv1                  //Soft Trig Trans Start Now
#define CSR_CLEAR_Mask                          (uint32_t)0xFFFFFF07
#define TRIG_CLEAR_Mask                         (uint32_t)0xFFFFFF00
#define CNT_CLEAR_Mask                          (uint32_t)0xFFFF0000

#define DMA_IT_TC                               ((uint32_t)0x00000002)
#define DMA_IT_TE                               ((uint32_t)0x00000004)
#define IS_DMA_CONFIG_IT(IT)                    ((((IT) & 0xFFFFFFF9) == 0x00) && ((IT) != 0x00))

#define DMA_IT_TC1                              ((uint32_t)0x00000001)
#define DMA_IT_TE1                              ((uint32_t)0x00000002)
#define DMA_IT_TC2                              ((uint32_t)0x00000010)
#define DMA_IT_TE2                              ((uint32_t)0x00000020)
#define DMA_IT_TC3                              ((uint32_t)0x00000100)
#define DMA_IT_TE3                              ((uint32_t)0x00000200)
#define DMA_IT_TC4                              ((uint32_t)0x00001000)
#define DMA_IT_TE4                              ((uint32_t)0x00002000)
#define DMA_IT_TC5                              ((uint32_t)0x00010000)
#define DMA_IT_TE5                              ((uint32_t)0x00020000)
#define DMA_IT_ALL                              ((uint32_t)0x00033333)

#define IS_DMA_CLEAR_IT(IT)                     ((((IT) & 0xFFFCCCCC) == 0x00) && ((IT) != 0x00))
#define IS_DMA_GET_IT(IT)                       (((IT) == DMA_IT_TC1) || ((IT) == DMA_IT_TE1) || \
                                                 ((IT) == DMA_IT_TC2) || ((IT) == DMA_IT_TE2) || \
                                                 ((IT) == DMA_IT_TC3) || ((IT) == DMA_IT_TE3) || \
                                                 ((IT) == DMA_IT_TC4) || ((IT) == DMA_IT_TE4) || \
                                                 ((IT) == DMA_IT_TC5) || ((IT) == DMA_IT_TE5))


#define DMA_CHANNEL_STATUS_INIT                 ((uint8_t)0x00)
#define DMA_CHANNEL_STATUS_ADDRESSOUTRANGE      ((uint8_t)0x01)
#define DMA_CHANNEL_STATUS_STOPREQ              ((uint8_t)0x02)
#define DMA_CHANNEL_STATUS_SRCADDERR            ((uint8_t)0x03)
#define DMA_CHANNEL_STATUS_DSTADDERR            ((uint8_t)0x04)
#define DMA_CHANNEL_STATUS_TRANSCOMPLETE        ((uint8_t)0x05)

//============================================================

void DMA_DeInit(DMACHANNEL_TypeDef *DMAy_Channelx);
void DMA_Init(DMACHANNEL_TypeDef *DMAy_Channelx, DMA_InitTypeDef *DMA_InitStruct);
void DMA_StructInit(DMA_InitTypeDef *DMA_InitStruct);
void DMA_Cmd(DMACHANNEL_TypeDef *DMAy_Channelx, FunctionalState NewState);
void DMA_SWTrigCmd(DMACHANNEL_TypeDef *DMAy_Channelx);
void DMA_ITConfig(DMACHANNEL_TypeDef *DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState);
ITStatus DMA_GetITStatus(uint32_t DMAy_IT);
void DMA_ClearITPendingBit(uint32_t DMAy_IT);
uint8_t DMA_GetFlagStatus(DMACHANNEL_TypeDef *DMAy_Channelx);

//============================================================

#ifdef __cplusplus
}
#endif

#endif
