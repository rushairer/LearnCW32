/**
 * @file cw32f030_atim.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-04-29
 *
 * @copyright Copyright (c) 2021
 *
 */
/* Includes ------------------------------------------------------------------*/
#include "cw32f030_atim.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/
/**
 * @brief ATIM复位，寄存器恢复为默认值
 */
void ATIM_DeInit(void)
{
    CW_SYSCTRL->APBRST2_f.ATIM = 0;
    CW_SYSCTRL->APBRST2_f.ATIM = 1;
}


/**
 * @brief ATIM 初始化
 * @param ATIM_InitStruct  详见ATIM_InitTypeDef的定义
 */
void ATIM_Init(ATIM_InitTypeDef *ATIM_InitStruct)
{
    assert_param(IS_ATIM_COUNTING_DIRECTION(ATIM_InitStruct->CounterDirection));
    assert_param(IS_ATIM_OP_MODE(ATIM_InitStruct->CounterOPMode));
    assert_param(IS_ATIM_COUNT_MODE(ATIM_InitStruct->CounterAlignedMode));
    assert_param(IS_ATIM_PRESCALER(ATIM_InitStruct->Prescaler));
    assert_param(IS_ATIM_CLOCK(ATIM_InitStruct->ClockSelect));
    REGBITS_MODIFY(CW_ATIM->CR, ATIM_CR_DIR_Msk | ATIM_CR_ONESHOT_Msk | \
                   ATIM_CR_PRS_Msk | ATIM_CR_MODE_Msk | \
                   ATIM_CR_BUFPEN_Msk | ATIM_CR_CT_Msk \
                   , \
                   ATIM_InitStruct->CounterDirection | ATIM_InitStruct->CounterOPMode |
                   ATIM_InitStruct->Prescaler | ATIM_InitStruct->CounterAlignedMode |
                   (ATIM_InitStruct->BufferState ? ATIM_BUFFER_ENABLE : ATIM_BUFFER_DISABLE) |
                   ATIM_InitStruct->ClockSelect);
    CW_ATIM->ARR = ATIM_InitStruct->ReloadValue;
    CW_ATIM->RCR = ATIM_InitStruct->RepetitionCounter | (ATIM_InitStruct->OverFlowMask ? 1UL << 8 : 0) | \
                   (ATIM_InitStruct->UnderFlowMask ? 1UL << 9 : 0);
}


/**
 * @brief ATIM 启动
 *
 * @param NewState ENABLE or DISABLE
 */
void ATIM_Cmd(FunctionalState NewState)
{
    CW_ATIM->CR_f.EN = NewState;
}

/**
 * @brief ATIM中断设置
 * @param ATIM_IT 中断源
 * @param NewState ENABLE 或 DISABLE
 */
void ATIM_ITConfig(uint32_t ATIM_IT, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        CW_ATIM->CR |= ATIM_IT;
    }
    else
    {
        CW_ATIM->CR &= ~ATIM_IT;
    }
}

/**
 * @brief 获取ATIM中断标志位
 * @param ATIM_IT 中断源
 * @return ITStatus
 */
ITStatus ATIM_GetITStatus(uint32_t ATIM_IT)
{
    return (CW_ATIM->ISR & ATIM_IT) ? SET : RESET;
}

/**
 * @brief 清除ATIM中断标志位
 */
void ATIM_ClearITPendingBit(uint32_t ATIM_IT)
{
    CW_ATIM->ICR = ~ATIM_IT;
}

/**
 * @brief 设置ATIM重载值
 * @param Value
 */
void ATIM_SetReloadValue(uint32_t Value)
{
    CW_ATIM->ARR = Value;
}

/**
 * @brief 设置通道1的功能
 *
 * @param Function ATIM_CHxA_BUFF ATIM_CHxA_CIE ATIM_CHxA_CDE
 *                 ATIM_CHxB_BUFF ATIM_CHxB_CIE ATIM_CHxB_CDE
 * @param NewState ENABLE 或 DISABLE
 */
void ATIM_CH1Config(uint32_t Function, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        CW_ATIM->CH1CR |= Function;
    }
    else
    {
        CW_ATIM->CH1CR &= ~(Function);
    }
}

/**
 * @brief 设置通道2的功能
 *
 * @param Function ATIM_CHxA_BUFF ATIM_CHxA_CIE ATIM_CHxA_CDE
 *                 ATIM_CHxB_BUFF ATIM_CHxB_CIE ATIM_CHxB_CDE
 * @param NewState ENABLE 或 DISABLE
 */
void ATIM_CH2Config(uint32_t Function, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        CW_ATIM->CH2CR |= Function;
    }
    else
    {
        CW_ATIM->CH2CR &= ~(Function);
    }
}

/**
 * @brief 设置通道3的功能
 *
 * @param Function ATIM_CHxA_BUFF ATIM_CHxA_CIE ATIM_CHxA_CDE
 *                 ATIM_CHxB_BUFF ATIM_CHxB_CIE ATIM_CHxB_CDE
 * @param NewState ENABLE 或 DISABLE
 */
void ATIM_CH3Config(uint32_t Function, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        CW_ATIM->CH3CR |= Function;
    }
    else
    {
        CW_ATIM->CH3CR &= ~(Function);
    }
}

/**
 * @brief 设置通道4的功能
 *
 * @param Function ATIM_CH4_BUFF ATIM_CH4_CIE ATIM_CH4_CDE *
 * @param NewState ENABLE 或 DISABLE
 */
void ATIM_CH4Config(uint32_t Function, FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        CW_ATIM->CH4CR |= Function;
    }
    else
    {
        CW_ATIM->CH4CR &= ~(Function);
    }
}

/**
 * @brief 输入捕获通道1A设置
 * @param ATIM_ICInitStruct
 */
void ATIM_IC1AInit(ATIM_ICInitTypeDef *ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));
    REGBITS_MODIFY(CW_ATIM->CH1CR, (ATIM_CH1CR_BKSA_Msk | ATIM_CH1CR_CSA_Msk),
                   (ATIM_ICInitStruct->ICPolarity | ATIM_CH_A_IC));
    CW_ATIM->FLTR_f.OCM1AFLT1A = ATIM_ICInitStruct->ICFilter;
}

/**
 * @brief 输入捕获通道1B设置
 * @param ATIM_ICInitStruct
 */
void ATIM_IC1BInit(ATIM_ICInitTypeDef *ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));
    REGBITS_MODIFY(CW_ATIM->CH1CR, (ATIM_CH1CR_BKSB_Msk | ATIM_CH1CR_CSB_Msk),
                   (ATIM_ICInitStruct->ICPolarity << 2 | ATIM_CH_B_IC));
    CW_ATIM->FLTR_f.OCM1BFLT1B = ATIM_ICInitStruct->ICFilter;
}


/**
 * @brief 输入捕获通道2A设置
 * @param ATIM_ICInitStruct
 */
void ATIM_IC2AInit(ATIM_ICInitTypeDef *ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));
    REGBITS_MODIFY(CW_ATIM->CH2CR, (ATIM_CH2CR_BKSA_Msk | ATIM_CH2CR_CSA_Msk),
                   (ATIM_ICInitStruct->ICPolarity | ATIM_CH_A_IC));
    CW_ATIM->FLTR_f.OCM2AFLT2A = ATIM_ICInitStruct->ICFilter;
}

/**
 * @brief 输入捕获通道2B设置
 * @param ATIM_ICInitStruct
 */
void ATIM_IC2BInit(ATIM_ICInitTypeDef *ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));
    REGBITS_MODIFY(CW_ATIM->CH2CR, (ATIM_CH2CR_BKSB_Msk | ATIM_CH2CR_CSB_Msk),
                   (ATIM_ICInitStruct->ICPolarity << 2 | ATIM_CH_B_IC));
    CW_ATIM->FLTR_f.OCM2BFLT2B = ATIM_ICInitStruct->ICFilter;
}

/**
 * @brief 输入捕获通道3A设置
 * @param ATIM_ICInitStruct
 */
void ATIM_IC3AInit(ATIM_ICInitTypeDef *ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));
    REGBITS_MODIFY(CW_ATIM->CH3CR, (ATIM_CH3CR_BKSA_Msk | ATIM_CH3CR_CSA_Msk),
                   (ATIM_ICInitStruct->ICPolarity | ATIM_CH_A_IC));
    CW_ATIM->FLTR_f.OCM3AFLT3A = ATIM_ICInitStruct->ICFilter;
}

/**
 * @brief 输入捕获通道3B设置
 * @param ATIM_ICInitStruct
 */
void ATIM_IC3BInit(ATIM_ICInitTypeDef *ATIM_ICInitStruct)
{
    assert_param(IS_ATIM_IC_POLARITY(ATIM_ICInitStruct->ICPolarity));
    assert_param(IS_ATIM_IC_FILTER(ATIM_ICInitStruct->ICFilter));
    REGBITS_MODIFY(CW_ATIM->CH3CR, (ATIM_CH3CR_BKSB_Msk | ATIM_CH3CR_CSB_Msk),
                   (ATIM_ICInitStruct->ICPolarity << 2 | ATIM_CH_B_IC));
    CW_ATIM->FLTR_f.OCM3BFLT3B = ATIM_ICInitStruct->ICFilter;
}

/**
 * @brief CH1A比较输出设置
 * @param ATIM_OCInitStruct
 */
void ATIM_OC1AInit(ATIM_OCInitTypeDef *ATIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_MODE(ATIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_POLARITY(ATIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_IT(ATIM_OCInitStruct->OCInterruptSelect));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->BufferState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCDMAState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCInterruptState));
    REGBITS_MODIFY(CW_ATIM->FLTR, ATIM_FLTR_OCM1AFLT1A_Msk | ATIM_FLTR_CCP1A_Msk,
                   ATIM_OCInitStruct->OCMode | (ATIM_OCInitStruct->OCPolarity << 3));
    CW_ATIM->CR_f.CISA = ATIM_OCInitStruct->OCInterruptSelect;
    REGBITS_MODIFY(CW_ATIM->CH1CR,  ATIM_CH1CR_BUFEA_Msk | ATIM_CH1CR_CDEA_Msk | ATIM_CH1CR_CIEA_Msk,
                   (ATIM_OCInitStruct->BufferState ? ATIM_CH1CR_BUFEA_Msk : 0) | \
                   (ATIM_OCInitStruct->OCDMAState ? ATIM_CH1CR_CDEA_Msk : 0) | \
                   (ATIM_OCInitStruct->OCInterruptState ? ATIM_CH1CR_CIEA_Msk : 0));
}

/**
 * @brief CH1B比较输出设置
 * @param ATIM_OCInitStruct
 */
void ATIM_OC1BInit(ATIM_OCInitTypeDef *ATIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_MODE(ATIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_POLARITY(ATIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_IT(ATIM_OCInitStruct->OCInterruptSelect));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->BufferState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCDMAState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCInterruptState));
    REGBITS_MODIFY(CW_ATIM->FLTR, ATIM_FLTR_OCM1BFLT1B_Msk | ATIM_FLTR_CCP1B_Msk,
                   (ATIM_OCInitStruct->OCMode << 4) | (ATIM_OCInitStruct->OCPolarity << 7));
    REGBITS_MODIFY(CW_ATIM->CH1CR, ATIM_CH1CR_CISB_Msk | ATIM_CH1CR_BUFEB_Msk | ATIM_CH1CR_CDEB_Msk | ATIM_CH1CR_CIEB_Msk,
                   (ATIM_OCInitStruct->OCInterruptSelect << 12) | \
                   (ATIM_OCInitStruct->BufferState ? ATIM_CH1CR_BUFEB_Msk : 0) | \
                   (ATIM_OCInitStruct->OCDMAState ? ATIM_CH1CR_CDEB_Msk : 0) | \
                   (ATIM_OCInitStruct->OCInterruptState ? ATIM_CH1CR_CIEB_Msk : 0));
}

/**
 * @brief CH2A比较输出设置
 * @param ATIM_OCInitStruct
 */
void ATIM_OC2AInit(ATIM_OCInitTypeDef *ATIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_MODE(ATIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_POLARITY(ATIM_OCInitStruct->OCPolarity));
    REGBITS_MODIFY(CW_ATIM->FLTR, ATIM_FLTR_OCM2AFLT2A_Msk | ATIM_FLTR_CCP2A_Msk,
                   (ATIM_OCInitStruct->OCMode << 8) | (ATIM_OCInitStruct->OCPolarity << 11));
    CW_ATIM->CR_f.CISA = ATIM_OCInitStruct->OCInterruptSelect;
    REGBITS_MODIFY(CW_ATIM->CH2CR,  ATIM_CH2CR_BUFEA_Msk | ATIM_CH2CR_CDEA_Msk | ATIM_CH2CR_CIEA_Msk,
                   (ATIM_OCInitStruct->BufferState ? ATIM_CH2CR_BUFEA_Msk : 0) | \
                   (ATIM_OCInitStruct->OCDMAState ? ATIM_CH2CR_CDEA_Msk : 0) | \
                   (ATIM_OCInitStruct->OCInterruptState ? ATIM_CH2CR_CIEA_Msk : 0));
}

/**
 * @brief CH2B比较输出设置
 * @param ATIM_OCInitStruct
 */
void ATIM_OC2BInit(ATIM_OCInitTypeDef *ATIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_MODE(ATIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_POLARITY(ATIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_IT(ATIM_OCInitStruct->OCInterruptSelect));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->BufferState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCDMAState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCInterruptState));
    REGBITS_MODIFY(CW_ATIM->FLTR, ATIM_FLTR_OCM2BFLT2B_Msk | ATIM_FLTR_CCP2B_Msk,
                   (ATIM_OCInitStruct->OCMode << 12) | (ATIM_OCInitStruct->OCPolarity << 15));
    REGBITS_MODIFY(CW_ATIM->CH2CR, ATIM_CH2CR_CISB_Msk | ATIM_CH2CR_BUFEB_Msk | ATIM_CH2CR_CDEB_Msk | ATIM_CH2CR_CIEB_Msk,
                   (ATIM_OCInitStruct->OCInterruptSelect << 12) | \
                   (ATIM_OCInitStruct->BufferState ? ATIM_CH2CR_BUFEB_Msk : 0) | \
                   (ATIM_OCInitStruct->OCDMAState ? ATIM_CH2CR_CDEB_Msk : 0) | \
                   (ATIM_OCInitStruct->OCInterruptState ? ATIM_CH2CR_CIEB_Msk : 0));
}

/**
 * @brief CH3A比较输出设置
 * @param ATIM_OCInitStruct
 */
void ATIM_OC3AInit(ATIM_OCInitTypeDef *ATIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_MODE(ATIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_POLARITY(ATIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_IT(ATIM_OCInitStruct->OCInterruptSelect));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->BufferState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCDMAState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCInterruptState));
    REGBITS_MODIFY(CW_ATIM->FLTR, ATIM_FLTR_OCM3AFLT3A_Msk | ATIM_FLTR_CCP3A_Msk,
                   (ATIM_OCInitStruct->OCMode << 16) | (ATIM_OCInitStruct->OCPolarity << 19));
    CW_ATIM->CR_f.CISA = ATIM_OCInitStruct->OCInterruptSelect;
    REGBITS_MODIFY(CW_ATIM->CH3CR,  ATIM_CH3CR_BUFEA_Msk | ATIM_CH3CR_CDEA_Msk | ATIM_CH3CR_CIEA_Msk,
                   (ATIM_OCInitStruct->BufferState ? ATIM_CH3CR_BUFEA_Msk : 0) | \
                   (ATIM_OCInitStruct->OCDMAState ? ATIM_CH3CR_CDEA_Msk : 0) | \
                   (ATIM_OCInitStruct->OCInterruptState ? ATIM_CH3CR_CIEA_Msk : 0));
}

/**
 * @brief CH3B比较输出设置
 * @param ATIM_OCInitStruct
 */
void ATIM_OC3BInit(ATIM_OCInitTypeDef *ATIM_OCInitStruct)
{
    assert_param(IS_ATIM_OC_MODE(ATIM_OCInitStruct->OCMode));
    assert_param(IS_ATIM_OC_POLARITY(ATIM_OCInitStruct->OCPolarity));
    assert_param(IS_ATIM_OC_IT(ATIM_OCInitStruct->OCInterruptSelect));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->BufferState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCDMAState));
    assert_param(IS_FUNCTIONAL_STATE(ATIM_OCInitStruct->OCInterruptState));
    REGBITS_MODIFY(CW_ATIM->FLTR, ATIM_FLTR_OCM3BFLT3B_Msk | ATIM_FLTR_CCP3B_Msk,
                   (ATIM_OCInitStruct->OCMode << 20) | (ATIM_OCInitStruct->OCPolarity << 23));
    REGBITS_MODIFY(CW_ATIM->CH3CR, ATIM_CH3CR_CISB_Msk | ATIM_CH3CR_BUFEB_Msk | ATIM_CH3CR_CDEB_Msk | ATIM_CH3CR_CIEB_Msk,
                   (ATIM_OCInitStruct->OCInterruptSelect << 12) | \
                   (ATIM_OCInitStruct->BufferState ? ATIM_CH3CR_BUFEB_Msk : 0) | \
                   (ATIM_OCInitStruct->OCDMAState ? ATIM_CH3CR_CDEB_Msk : 0) | \
                   (ATIM_OCInitStruct->OCInterruptState ? ATIM_CH3CR_CIEB_Msk : 0));
}


/**
 * @brief 通道4的比较设置
 * @param NewState 通道比较使能
 * @param ITSelect 中断产生条件选择，参数为下列参数之一
 *        @arg ATIM_OC_IT_NONE
 *        @arg ATIM_OC_IT_UP_COUNTER
 *        @arg ATIM_OC_IT_DOWN_COUNTER
 *        @arg ATIM_OC_IT_BOTH_COUNTER
 * @param DMAState 比较触发DMA使能
 * @param ITState 比较触发中断使能
 * @param BufferState 比较缓存使能控制
 */
void ATIM_OC4Init(FunctionalState NewState, uint32_t ITSelect, FunctionalState DMAState,
                  FunctionalState ITState, FunctionalState BufferState)
{
    assert_param(IS_ATIM_OC_IT(ITSelect));
    CW_ATIM->CH4CR = (NewState ? 1UL << 5 : 0) | (ITSelect << 3) | (DMAState ? 1UL << 2 : 0) | \
                     (ITState ? 1UL << 1 : 0) | (BufferState ? 1 : 0);
}

/**
 * @brief 设置PWM输出的参数
 *
 * @param OCREFAType 比较器A单点比较或双点比较 OCREFA_TYPE_SINGLE OCREFA_TYPE_DOUBLE
 * @param OutputType PWM输出类型独立或互补 OUTPUT_TYPE_ALONE OUTPUT_TYPE_COMP
 * @param Deadtime 死区时间，单位为定时器的计数时隙。-1：禁止， 0~0xFF：插入的死区时隙
 *                 取值范围。
 */
void ATIM_PWMOutputConfig(uint32_t OCREFAType, uint32_t OutputType, int16_t Deadtime)
{
    assert_param(IS_ATIM_OCREFA_TYPE(OCREFAType));
    assert_param(IS_ATIM_OUTPUT_TYPE(OutputType));
    assert_param(IS_ATIM_DEADTIME(Deadtime));
    REGBITS_MODIFY(CW_ATIM->CR, ATIM_CR_COMP_Msk | ATIM_CR_PWM2S_Msk, OCREFAType | OutputType);
    if (Deadtime >= 0)
    {
        CW_ATIM->DTR_f.DTEN = 1;
        CW_ATIM->DTR_f.DTR = Deadtime;
    }
    else
    {
        CW_ATIM->DTR_f.DTEN = 0;
    }
}

void ATIM_CtrlPWMOutputs(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    CW_ATIM->DTR_f.MOE = NewState;
}

/**
 * @brief 设置外部触发参数
 * @param ATIM_ETRPolarity 外部触发信号有效极性 参数为下列参数之一：
 *        @arg ATIM_ETR_POLARITY_NONINVERT: 同相
 *        @arg ATIM_ETR_POLARITY_INVERT: 反相
 * @param ETRFilter 外部触发通道的滤波设置 参数为下列参数之一：
 *        @arg ATIM_ETR_FILTER_NONE: 无滤波
 *        @arg ATIM_ETR_FILTER_PCLK_N3: PCLK时钟采样，3个连续有效
 *        @arg ATIM_ETR_FILTER_PCLKDIV4_N3: PCLK/4时钟采样，3个连续有效
 *        @arg ATIM_ETR_FILTER_PCLKDIV16_N3: PCLK/16时钟采样，3个连续有效
 *        @arg ATIM_ETR_FILTER_PCLKDIV64_N3: PCLK/64时钟采样，3个连续有效
 */
void ATIM_ETRConfig(uint32_t ATIM_ETRPolarity, uint32_t ATIM_ETRFilter)
{
    assert_param(IS_ATIM_ETR_POLARITY(ATIM_ETRPolarity));
    assert_param(IS_ATIM_ETR_FILTER(ATIM_ETRFilter));
    REGBITS_MODIFY(CW_ATIM->FLTR,
                   ATIM_FLTR_ETP_Msk | ATIM_FLTR_FLTET_Msk,
                   ATIM_ETRPolarity | ATIM_ETRFilter);
}

/**
 * @brief 设置Brake输入信号的参数
 * @param ATIM_BrakePolarity 信号极性，参数为下列参数之一：
 *        @arg ATIM_BRAKE_POLARITY_NONINVERT: 同相
 *        @arg ATIM_BRAKE_POLARITY_INVERT: 反相
 * @param ATIM_BrakeFilter
 *        @arg ATIM_BRAKE_FILTER_NONE: 无滤波
 *        @arg ATIM_BRAKE_FILTER_PCLK_N3: PCLK时钟采样，3个连续有效
 *        @arg ATIM_BRAKE_FILTER_PCLKDIV4_N3: PCLK/4时钟采样，3个连续有效
 *        @arg ATIM_BRAKE_FILTER_PCLKDIV16_N3: PCLK/16时钟采样，3个连续有效
 *        @arg ATIM_BRAKE_FILTER_PCLKDIV64_N3: PCLK/64时钟采样，3个连续有效
 */
void ATIM_BrakeConfig(uint32_t ATIM_BrakePolarity, uint32_t ATIM_BrakeFilter)
{
    assert_param(IS_ATIM_BRAKE_POLARITY(ATIM_BrakePolarity));
    assert_param(IS_ATIM_BRAKE_FILTER(ATIM_BrakeFilter));
    REGBITS_MODIFY(CW_ATIM->FLTR,
                   ATIM_FLTR_BKP_Msk | ATIM_FLTR_FLTBK_Msk,
                   ATIM_BrakePolarity | ATIM_BrakeFilter);
}

/**
 * @brief 设置ATIM触发ADC的采样的触发源
 * @param ATIM_ADCTriggerSource 参数为下列参数之一
 *        @arg ATIM_ADC_TRIGGER_CH3B
 *        @arg ATIM_ADC_TRIGGER_CH2B
 *        @arg ATIM_ADC_TRIGGER_CH1B
 *        @arg ATIM_ADC_TRIGGER_CH3A
 *        @arg ATIM_ADC_TRIGGER_CH2A
 *        @arg ATIM_ADC_TRIGGER_CH1A
 *        @arg ATIM_ADC_TRIGGER_UPDATA_EVENT
 * @param NewState DISABLE或ENABLE
 */
void ATIM_ADCTriggerConfig(uint32_t ATIM_ADCTriggerSource, FunctionalState NewState)
{
    assert_param(IS_ATIM_ADC_TRIGGER(ATIM_ADCTriggerSource));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        CW_ATIM->TRIG |= (ATIM_ADCTriggerSource | ATIM_ADC_TRIGGER_GLOBAL);
    }
    else
    {
        CW_ATIM->TRIG &= ~ATIM_ADCTriggerSource;
    }
}

uint16_t ATIM_GetCapture1A(void)
{
    return (uint16_t) CW_ATIM->CH1CCRA;
}


uint16_t ATIM_GetCapture2A(void)
{
    return (uint16_t) CW_ATIM->CH2CCRA;
}


uint16_t ATIM_GetCapture3A(void)
{
    return (uint16_t) CW_ATIM->CH3CCRA;
}


uint16_t ATIM_GetCapture1B(void)
{
    return (uint16_t) CW_ATIM->CH1CCRB;
}


uint16_t ATIM_GetCapture2B(void)
{
    return (uint16_t) CW_ATIM->CH2CCRB;
}


uint16_t ATIM_GetCapture3B(void)
{
    return (uint16_t) CW_ATIM->CH3CCRB;
}


void ATIM_SetCompare1A(uint16_t Compare)
{
    CW_ATIM->CH1CCRA = (uint32_t)Compare;
}

void ATIM_SetCompare2A(uint16_t Compare)
{
    CW_ATIM->CH2CCRA = (uint32_t)Compare;
}

void ATIM_SetCompare3A(uint16_t Compare)
{
    CW_ATIM->CH3CCRA = (uint32_t)Compare;
}

void ATIM_SetCompare1B(uint16_t Compare)
{
    CW_ATIM->CH1CCRB = (uint32_t)Compare;
}

void ATIM_SetCompare2B(uint16_t Compare)
{
    CW_ATIM->CH2CCRB = (uint32_t)Compare;
}

void ATIM_SetCompare3B(uint16_t Compare)
{
    CW_ATIM->CH3CCRB = (uint32_t)Compare;
}

void ATIM_SetCompare4(uint16_t Compare)
{
    CW_ATIM->CH4CCR = (uint32_t) Compare;
}

void ATIM_MasterModeConfig(uint8_t ATIM_MasterOutput)
{
    assert_param(IS_ATIM_MASTER_OUTPUT(ATIM_MasterOutput));
    CW_ATIM->MSCR_f.MMS = ATIM_MasterOutput;
}

void ATIM_SlaverModeConfig(uint8_t ATIM_SlaverType)
{
    assert_param(IS_ATIM_SLAVER_TYPE(ATIM_SlaverType));
    CW_ATIM->MSCR_f.SMS = ATIM_SlaverType;
}

void ATIM_TriggerSelect(uint8_t ATIM_TriggerSource)
{
    assert_param(IS_ATIM_TRIGGER_SOURCE(ATIM_TriggerSource));
    CW_ATIM->MSCR_f.TS = ATIM_TriggerSource;
}

void ATIM_UpdateEventSelect(uint8_t ATIM_UpdateEvent)
{
    assert_param(IS_ATIM_UPDATE_EVENT(ATIM_UpdateEvent));
    CW_ATIM->CR_f.URS = ATIM_UpdateEvent;
}
