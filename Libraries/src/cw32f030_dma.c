/**
 * @file cw32f030_dma.c
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

/* Includes ------------------------------------------------------------------*/
#include "cw32f030_dma.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

void DMA_DeInit(DMACHANNEL_TypeDef *DMA_Channelx)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMA_Channelx));
    /* Disable the selected DMAy Channelx */
    DMA_Channelx->CSR &= (~DMA_CHANNEL_EN);        ///disable DMA Channel
    DMA_Channelx->CSR  = 0x00UL;                        ///reset CSR register
    DMA_Channelx->TRIG = 0x00UL;                        ///reset the trig register
    DMA_Channelx->CNT  = 0x00010000UL;             ///reset the CNT register
    DMA_Channelx->SRCADDR = 0x00UL;                ///reset srcaddr register
    DMA_Channelx->DSTADDR = 0x00UL;                ///reset dstaddr register
}

/**
 * @brief DMA通道初始化
 *
 * @param DMA_Channelx
 * @param DMA_InitStruct
 */
void DMA_Init(DMACHANNEL_TypeDef *DMA_Channelx, DMA_InitTypeDef *DMA_InitStruct)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMA_Channelx));
    assert_param(IS_DMA_MODE(DMA_InitStruct->DMA_Mode));
    assert_param(IS_DMA_TRANSFER_WIDTH(DMA_InitStruct->DMA_TransferWidth));
    assert_param(IS_DMA_SRCADDRESS_INC(DMA_InitStruct->DMA_SrcInc));
    assert_param(IS_DMA_DSTADDRESS_INC(DMA_InitStruct->DMA_DstInc));
    assert_param(IS_DMA_TRIG(DMA_InitStruct->TrigMode));
    assert_param(IS_DMA_HARD_TRIGSRC(DMA_InitStruct->HardTrigSource));
    assert_param(IS_DMA_TRANSFERCNT(DMA_InitStruct->DMA_TransferCnt));
    DMA_Channelx->CSR = ((DMA_Channelx->CSR & CSR_CLEAR_Mask) | \
                         DMA_InitStruct->DMA_Mode | DMA_InitStruct->DMA_TransferWidth | \
                         DMA_InitStruct->DMA_SrcInc | DMA_InitStruct->DMA_DstInc);
    DMA_Channelx->TRIG = ((DMA_Channelx->TRIG & TRIG_CLEAR_Mask) | DMA_InitStruct->TrigMode | \
                          DMA_InitStruct->HardTrigSource) ;
    DMA_Channelx->CNT = bv16 | DMA_InitStruct->DMA_TransferCnt ;
    DMA_Channelx->SRCADDR = DMA_InitStruct->DMA_SrcAddress ;
    DMA_Channelx->DSTADDR = DMA_InitStruct->DMA_DstAddress ;
}


/**
 * @brief DMA结构初始化
 *
 * @param DMA_InitStruct
 */
void DMA_StructInit(DMA_InitTypeDef *DMA_InitStruct)
{
    /*-------------- Reset DMA init structure parameters values ------------------*/
    /* Initialize the DMA_Mode */
    DMA_InitStruct->DMA_Mode = DMA_MODE_BLOCK;
    /* Initialize the DMA_TransferWidth */
    DMA_InitStruct->DMA_TransferWidth = DMA_TRANSFER_WIDTH_8BIT;
    /* Initialize the DMA_SrcInc */
    DMA_InitStruct->DMA_SrcInc = DMA_SrcAddress_Fix;
    /* Initialize the DMA_DstInc */
    DMA_InitStruct->DMA_DstInc = DMA_DstAddress_Fix;
    /* Initialize the TrigMode */
    DMA_InitStruct->TrigMode = DMA_SWTrig;
    /* Initialize the HardTrigSource, if we use softtrig ,we can not config it*/
    DMA_InitStruct->HardTrigSource = DMA_HardTrig_UART1_RXBufferNE;
    /* Initialize the DMA_TransferCnt */
    DMA_InitStruct->DMA_TransferCnt = 0x00;
    /* Initialize the DMA_SrcAddress */
    DMA_InitStruct->DMA_SrcAddress = 0x00;
    /* Initialize the DMA_DstAddress */
    DMA_InitStruct->DMA_DstAddress = 0x00;
}

/**
 * @brief 使能DMAy_Channelx 进行DMA传输
 *
 * @param DMA_Channelx
 * @param NewState
 */
void DMA_Cmd(DMACHANNEL_TypeDef *DMA_Channelx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMA_Channelx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected DMAy Channelx */
        DMA_Channelx->CSR |= DMA_CHANNEL_EN;
    }
    else
    {
        /* Disable the selected DMAy Channelx */
        DMA_Channelx->CSR &= ~DMA_CHANNEL_EN;
    }
}


/**
 * @brief 通过软件置1，立即触发该通道启动传输
 *
 * @param DMA_Channelx
 */
void DMA_SWTrigCmd(DMACHANNEL_TypeDef *DMA_Channelx)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMA_Channelx));
    DMA_Channelx->TRIG |= DMA_SOFTTRIG_EN;
}


/**
 * @brief 配置DMA_Channelx 指定中断使能
 *
 * @param DMA_Channelx   ：CW_DMACHANNEL1/2/3/4/5
 * @param DMA_IT         ：DMA_IT_TC  DMA_IT_TE
 * @param NewState       ：ENABLE DISABLE
 */
void DMA_ITConfig(DMACHANNEL_TypeDef *DMA_Channelx, uint32_t DMA_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMA_Channelx));
    assert_param(IS_DMA_CONFIG_IT(DMA_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected DMA interrupts */
        DMA_Channelx->CSR |= DMA_IT;
    }
    else
    {
        /* Disable the selected DMA interrupts */
        DMA_Channelx->CSR &= ~DMA_IT;
    }
}

/**
  * @brief  获取DMA_Channelx's 指定中断标志。
  * @param  DMAy_IT: specifies the DMAy interrupt source to check.
  *   This parameter can be one of the following values:
  *     @arg DMA_IT_TC1: DMA Channel1 transfer complete interrupt.
  *     @arg DMA_IT_TE1: DMA Channel1 transfer error interrupt.
  *     @arg DMA_IT_TC2: DMA Channel2 transfer complete interrupt.
  *     @arg DMA_IT_TE2: DMA Channel2 transfer error interrupt.
  *     @arg DMA_IT_TC3: DMA Channel3 transfer complete interrupt.
  *     @arg DMA_IT_TE3: DMA Channel3 transfer error interrupt.
  *     @arg DMA_IT_TC4: DMA Channel4 transfer complete interrupt.
  *     @arg DMA_IT_TE4: DMA Channel4 transfer error interrupt.
  *     @arg DMA_IT_TC5: DMA Channel5 transfer complete interrupt.
  *     @arg DMA_IT_TE5: DMA Channel5 transfer error interrupt.
  * @retval The new state of DMAy_IT (SET or RESET).
  */
ITStatus DMA_GetITStatus(uint32_t DMA_IT)
{
    /* Check the parameters */
    assert_param(IS_DMA_GET_IT(DMA_IT));
    return (CW_DMA->ISR & DMA_IT) ? SET : RESET;
}

/**
  * @brief  清除DMA_Channelx's 指定中断标志。
  * @param  DMAy_IT: specifies the DMAy interrupt pending bit to clear.
  *   This parameter can be any combination (for the same DMA) of the following values:
  *     @arg DMA_IT_TC1: DMA Channel1 transfer complete interrupt.
  *     @arg DMA_IT_TE1: DMA Channel1 transfer error interrupt.
  *     @arg DMA_IT_TC2: DMA Channel2 transfer complete interrupt.
  *     @arg DMA_IT_TE2: DMA Channel2 transfer error interrupt.
  *     @arg DMA_IT_TC3: DMA Channel3 transfer complete interrupt.
  *     @arg DMA_IT_TE3: DMA Channel3 transfer error interrupt.
  *     @arg DMA_IT_TC4: DMA Channel4 transfer complete interrupt.
  *     @arg DMA_IT_TE4: DMA Channel4 transfer error interrupt.
  *     @arg DMA_IT_TC5: DMA Channel5 transfer complete interrupt.
  *     @arg DMA_IT_TE5: DMA Channel5 transfer error interrupt.
  * @retval None
  */
void DMA_ClearITPendingBit(uint32_t DMA_IT)
{
    /* Check the parameters */
    assert_param(IS_DMA_CLEAR_IT(DMA_IT));
    CW_DMA->ICR &= (~DMA_IT);
}

/**
  * @brief  获取DMAy Channelx传输状态
  *
  * @param DMA_Channelx    ：CW_DMACHANNEL1/2/3/4/5
  * @return uint8_t        : DMA_CHANNEL_STATUS_INIT      DMA_CHANNEL_STATUS_ADDRESSOUTRANGE
  *                          DMA_CHANNEL_STATUS_STOPREQ   DMA_CHANNEL_STATUS_SRCADDERR
  *                          DMA_CHANNEL_STATUS_DSTADDERR DMA_CHANNEL_STATUS_TRANSCOMPLETE
  */
uint8_t DMA_GetFlagStatus(DMACHANNEL_TypeDef *DMA_Channelx)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMA_Channelx));
    return ((uint8_t)(DMA_Channelx->CSR >> 8));
}

