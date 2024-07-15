/**
 * @file cw32f030_adc.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-08-09
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

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "cw32f030.h"
#include "cw32f030_adc.h"
#include "cw32f030_gpio.h"

/**
 ******************************************************************************
 ** \addtogroup AdcGroup
 ******************************************************************************/
//@{
/******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 *****************************************************************************/

/**
 * @brief
 *          获取ADC所有中断状态
 *
 * @param   pFlagAdcIrq
 */
void ADC_GetITStatusAll(volatile uint8_t *pFlagAdcIrq)
{
    *pFlagAdcIrq = (uint8_t)(CW_ADC->ISR);
}

/**
 * @brief
 *          获取ADC指定的中断状态
 *
 * @param   ADC_IT:
 *          @arg ADC_IT_READY
 *          @arg ADC_IT_OVW
 *          @arg ADC_IT_WDTR
 *          @arg ADC_IT_WDTH
 *          @arg ADC_IT_WDTL
 *          @arg ADC_IT_EOA
 *          @arg ADC_IT_EOS
 *          @arg ADC_IT_EOC
 *
 * @return  ITStatus: SET or RESET
 */
ITStatus ADC_GetITStatus(uint16_t ADC_IT)
{
    assert_param(IS_ADC_GET_IT(ADC_IT));
    return (REGBITS_GET(CW_ADC->ISR, ADC_IT) ? SET : RESET);
}

/**
 * @brief
 *          清除ADC所有中断状态
 */
void ADC_ClearITPendingAll(void)
{
    REGBITS_CLR(CW_ADC->ICR,
                (ADC_ISR_OVW_Msk | ADC_ISR_WDTR_Msk | \
                 ADC_ISR_WDTH_Msk | ADC_ISR_WDTL_Msk | ADC_ISR_EOA_Msk | \
                 ADC_ISR_EOS_Msk | ADC_ISR_EOC_Msk));
}

/**
 * @brief
 *          清除ADC指定的中断状态
 *
 * @param   ADC_IT
 *          @arg ADC_IT_OVW
 *          @arg ADC_IT_WDTR
 *          @arg ADC_IT_WDTH
 *          @arg ADC_IT_WDTL
 *          @arg ADC_IT_EOA
 *          @arg ADC_IT_EOS
 *          @arg ADC_IT_EOC
 */
void ADC_ClearITPendingBit(uint16_t ADC_IT)
{
    assert_param(IS_ADC_GET_IT(ADC_IT));
    REGBITS_CLR(CW_ADC->ICR, ADC_IT);
}

/**
 * @brief
 *          ADC中断使能
 *
 * @param   intPriority
 */
void ADC_EnableIrq(uint8_t intPriority)
{
    ADC_EnableNvic(intPriority);
}

/**
 * @brief
 *          ADC中断禁止
 */
void ADC_DisableIrq(void)
{
    REGBITS_CLR(CW_ADC->IER,
                ADC_IER_OVW_Msk | ADC_IER_WDTR_Msk | ADC_IER_WDTH_Msk | \
                ADC_IER_WDTL_Msk | ADC_IER_EOA_Msk | ADC_IER_EOS_Msk | \
                ADC_IER_EOC_Msk);
    ADC_DisableNvic();
}

/**
 * @brief
 *          ADC模拟看门狗配置
 *
 * @param   ADC_WdtStruct
 */
void ADC_WdtConfig(ADC_WdtTypeDef *ADC_WdtStruct)
{
    ASSERT(NULL != ADC_WdtStruct);
    assert_param(IS_ADC_WDT_CH(ADC_WdtStruct->ADC_WdtCh));
    assert_param(IS_ADC_WDT_EN(ADC_WdtStruct->ADC_WdtAll));
    assert_param(IS_ADC_WDTR_EN(ADC_WdtStruct->ADC_WdtrIrq));
    assert_param(IS_ADC_WDTH_EN(ADC_WdtStruct->ADC_WdthIrq));
    assert_param(IS_ADC_WDTL_EN(ADC_WdtStruct->ADC_WdtlIrq));
    //所有通道模拟看门狗使能控制
    //阈值比较通道选择
    REGBITS_MODIFY(CW_ADC->CR1, ADC_CR1_WDTALL_Msk | ADC_CR1_WDTCH_Msk,
                   ADC_WdtStruct->ADC_WdtAll | \
                   ADC_WdtStruct->ADC_WdtCh);
    REGBITS_MODIFY(CW_ADC->IER,
                   ADC_IER_WDTR_Msk | ADC_IER_WDTH_Msk | ADC_IER_WDTL_Msk,
                   ADC_WdtStruct->ADC_WdtrIrq | \
                   ADC_WdtStruct->ADC_WdthIrq | \
                   ADC_WdtStruct->ADC_WdtlIrq);
    CW_ADC->VTH = ADC_WdtStruct->ADC_Vth;              //模拟看门狗检测高阈值
    CW_ADC->VTL = ADC_WdtStruct->ADC_Vtl;              //模拟看门狗检测低阈值
    if (ADC_WdtStruct->ADC_WdtCh == ADC_WdtVref1P2)
    {
        REGBITS_SET(CW_ADC->CR0, ADC_CR0_BGREN_Msk);
    }
}

/**
 * @brief
 *          ADC初始化
 *
 * @param   ADC_InitStruct
 */
void ADC_Init(ADC_InitTypeDef *ADC_InitStruct)
{
    ASSERT(NULL != ADC_InitStruct);
    assert_param(IS_ADC_OP_MODE(ADC_InitStruct->ADC_OpMode));
    assert_param(IS_ADC_CLK_DIV(ADC_InitStruct->ADC_ClkDiv));
    assert_param(IS_ADC_SAMPLE_TIME(ADC_InitStruct->ADC_SampleTime));
    assert_param(IS_ADC_VREF_SEL(ADC_InitStruct->ADC_VrefSel));
    assert_param(IS_ADC_BUF_ENABLE(ADC_InitStruct->ADC_InBufEn));
    assert_param(IS_ADC_TS_ENABLE(ADC_InitStruct->ADC_TsEn));
    assert_param(IS_ADC_DMA_ENABLE(ADC_InitStruct->ADC_DMAEn));
    assert_param(IS_ADC_DATA_ALIGN(ADC_InitStruct->ADC_Align));
    assert_param(IS_ADC_ACC_ENABLE(ADC_InitStruct->ADC_AccEn));
    REGBITS_MODIFY(CW_ADC->CR0,
                   ADC_CR0_BUF_Msk | ADC_CR0_SAM_Msk | ADC_CR0_CLK_Msk | \
                   ADC_CR0_REF_Msk | ADC_CR0_TSEN_Msk | ADC_CR0_MODE_Msk,
                   ADC_InitStruct->ADC_InBufEn | \
                   ADC_InitStruct->ADC_SampleTime | \
                   ADC_InitStruct->ADC_ClkDiv | \
                   ADC_InitStruct->ADC_VrefSel | \
                   ADC_InitStruct->ADC_TsEn | \
                   ADC_InitStruct->ADC_OpMode);
    REGBITS_MODIFY(CW_ADC->CR1, ADC_CR1_DMAEN_Msk | ADC_CR1_ALIGN_Msk,
                   ADC_InitStruct->ADC_DMAEn | \
                   ADC_InitStruct->ADC_Align);
    if (ADC_InitStruct->ADC_AccEn)
    {
        REGBITS_MODIFY(CW_ADC->CR2, ADC_CR2_ACCEN_Msk | ADC_CR2_ACCRST_Msk,
                       ADC_InitStruct->ADC_AccEn | \
                       1u << ADC_CR2_ACCRST_Pos);
    }
    if (ADC_InitStruct->ADC_VrefSel == ADC_Vref_Extern1)
    {
        //初始化ExRef：PB00
        REGBITS_SET(CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_GPIOB_Msk); //打开GPIO时钟
        PB00_ANALOG_ENABLE();
    }
}

/**
 * @brief
 *        ADC默认值初始化
 *
 * @param ADC_InitStruct
 */
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct)
{
    /* Reset ADC init structure parameters values */
    ADC_InitStruct->ADC_OpMode = ADC_SingleChOneMode; //单通道单次转换模式
    ADC_InitStruct->ADC_ClkDiv = ADC_Clk_Div1; //PCLK
    ADC_InitStruct->ADC_SampleTime = ADC_SampTime5Clk; //5个ADC时钟周期
    ADC_InitStruct->ADC_VrefSel = ADC_Vref_BGR2p5; //VDDA参考电压
    ADC_InitStruct->ADC_InBufEn = ADC_BufDisable; //关闭跟随器
    ADC_InitStruct->ADC_TsEn = ADC_TsDisable; //关闭内置温度传感器
    ADC_InitStruct->ADC_DMAEn = ADC_DmaDisable; //不触发DMA
    ADC_InitStruct->ADC_Align = ADC_AlignRight; //ADC转换结果右对齐
    ADC_InitStruct->ADC_AccEn = ADC_AccDisable; //转换结果累加不使能
}

/**
 * @brief
 *        ADC模拟看门狗默认值初始化
 *
 * @param ADC_WdtStruct
 */
void ADC_WdtInit(ADC_WdtTypeDef *ADC_WdtStruct)
{
    ADC_WdtStruct->ADC_WdtCh = ADC_WdtCh0;
    ADC_WdtStruct->ADC_WdtAll = ADC_WdtDisable;
    ADC_WdtStruct->ADC_WdtrIrq = ADC_WdtrDisable;
    ADC_WdtStruct->ADC_WdthIrq = ADC_WdthDisable;
    ADC_WdtStruct->ADC_WdtlIrq = ADC_WdtlDisable;
    ADC_WdtStruct->ADC_Vth = 0x0FFF;
    ADC_WdtStruct->ADC_Vtl = 0x00;
}

/**
 * @brief
 *        ADC外部中断触发源配置
 *
 * @param ADC_TRIG:
 *        @arg ADC_TRIG_DMA
 *        @arg ADC_TRIG_I2C2
 *        @arg ADC_TRIG_I2C1
 *        @arg ADC_TRIG_SPI2
 *        @arg ADC_TRIG_SPI1
 *        @arg ADC_TRIG_UART3
 *        @arg ADC_TRIG_UART2
 *        @arg ADC_TRIG_UART1
 *        @arg ADC_TRIG_BTIM3
 *        @arg ADC_TRIG_BTIM2
 *        @arg ADC_TRIG_BTIM1
 *        @arg ADC_TRIG_GTIM4
 *        @arg ADC_TRIG_GTIM3
 *        @arg ADC_TRIG_GTIM2
 *        @arg ADC_TRIG_GTIM1
 *        @arg ADC_TRIG_ATIM
 * @param NewState:
 *        @arg DISABLE
 *        @arg ENABLE
 */
void ADC_ExtTrigCfg(uint16_t ADC_TRIG, FunctionalState NewState)
{
    uint16_t trigMask = 0;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_TRIG(ADC_TRIG));
    /* Get the ADC TRIG index */
    trigMask = ADC_TRIG;
    if (NewState != DISABLE)
    {
        /* Enable the selected ADC interrupts */
        CW_ADC->TRIGGER |= trigMask;
    }
    else
    {
        /* Disable the selected ADC interrupts */
        CW_ADC->TRIGGER &= (~(uint32_t) trigMask);
    }
}

/**
 * @brief
 *          ADC去初始化
 */
void ADC_DeInit(void)
{
    // Enable ADC reset state
    REGBITS_CLR(CW_SYSCTRL->APBRST2, SYSCTRL_APBRST2_ADC_Msk);
    // Release ADC from reset state
    REGBITS_SET(CW_SYSCTRL->APBRST2, SYSCTRL_APBRST2_ADC_Msk);
}

/**
 * @brief
 *        ADC转换软件启动命令
 *
 * @param NewState
 *        @arg DISABLE
 *        @arg ENABLE
 */
void ADC_SoftwareStartConvCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        REGBITS_SET(CW_ADC->START, ADC_START_START_Msk);
    }
    else
    {
        REGBITS_CLR(CW_ADC->START, ADC_START_START_Msk);
    }
}

/**
 * @brief
 *          ADC使能
 */
void ADC_Enable(void)
{
    REGBITS_SET(CW_ADC->CR0, ADC_CR0_EN_Msk);
    //等待 ADC 模块启动完成
    while (!ADC_GetITStatus(ADC_IT_READY));
}

/**
 * @brief
 *          ADC禁用
 */
void ADC_Disable(void)
{
    REGBITS_CLR(CW_ADC->CR0, ADC_CR0_EN_Msk);
}

/**
 * @brief
 *          单通道转换模式公共配置
 *
 * @param   ADC_SingleChStruct
 */
void ADC_SingleChCommon(ADC_SingleChTypeDef *ADC_SingleChStruct)
{
    ASSERT(NULL != ADC_SingleChStruct);
    assert_param(IS_ADC_CH_SEL(ADC_SingleChStruct->ADC_Chmux));
    assert_param(IS_ADC_DATA_DISCARD(ADC_SingleChStruct->ADC_DiscardEn));
    ADC_Init(&ADC_SingleChStruct->ADC_InitStruct);
    ADC_BufEnSingleCh(ADC_SingleChStruct->ADC_Chmux);
    if (ADC_SingleChStruct->ADC_WdtStruct.ADC_WdtAll == ADC_WdtEnable)
    {
        ADC_WdtConfig(&ADC_SingleChStruct->ADC_WdtStruct);
    }
    REGBITS_MODIFY(CW_ADC->CR1, ADC_CR1_DISCARD_Msk | ADC_CR1_CHMUX_Msk,
                   ADC_SingleChStruct->ADC_DiscardEn | \
                   ADC_SingleChStruct->ADC_Chmux);
}

/**
 * @brief
 *        ADC单通道单次转换模式配置
 *
 * @param ADC_SingleChStruct
 */
void ADC_SingleChOneModeCfg(ADC_SingleChTypeDef *ADC_SingleChStruct)
{
    ADC_SingleChCommon(ADC_SingleChStruct);
    REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_MODE_Msk, ADC_SingleChOneMode);
}

/**
 * @brief
 *        ADC单通道多次转换模式配置
 *
 * @param ADC_SingleChStruct
 * @param cntAdcSample: 0 ~ 255
 */
void ADC_SingleChMoreModeCfg(ADC_SingleChTypeDef *ADC_SingleChStruct,
                             uint8_t cntAdcSample)
{
    ADC_SingleChStruct->ADC_InitStruct.ADC_AccEn = ADC_AccEnable;    //Must be added
    ADC_SingleChCommon(ADC_SingleChStruct);
    REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_MODE_Msk, ADC_SingleChMoreMode);
    CW_ADC->CR2_f.CNT = cntAdcSample;
}

/**
 * @brief
 *        ADC单通道连续转换模式配置
 *
 * @param ADC_SingleChStruct
 */
void ADC_SingleChContinuousModeCfg(ADC_SingleChTypeDef *ADC_SingleChStruct)
{
    ADC_SingleChCommon(ADC_SingleChStruct);
    REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_MODE_Msk, ADC_SingleChContinuousMode);
}

/**
 * @brief
 *        ADC序列转换模式公共配置
 *
 * @param ADC_SerialChStruct
 */
void ADC_SerialChCommon(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
    if (NULL == ADC_SerialChStruct)
    {
        return;
    }
    ADC_Init(&ADC_SerialChStruct->ADC_InitStruct);
    switch (ADC_SerialChStruct->ADC_SqrEns)
    {
        case ADC_SqrEns0:
            ADC_Sqr0ChannelCfg(ADC_SerialChStruct);
            break;
        case ADC_SqrEns01:
            ADC_Sqr01ChannelCfg(ADC_SerialChStruct);
            break;
        case ADC_SqrEns02:
            ADC_Sqr02ChannelCfg(ADC_SerialChStruct);
            break;
        case ADC_SqrEns03:
            ADC_Sqr03ChannelCfg(ADC_SerialChStruct);
            break;
        default:
            break;
    }
}

/**
 * @brief
 *        ADC序列连续转换模式配置
 *
 * @param ADC_SerialChStruct
 */
void ADC_SerialChContinuousModeCfg(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
    ADC_SerialChCommon(ADC_SerialChStruct);
    REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_MODE_Msk, ADC_SerialChContinuousMode);
}

/**
 * @brief
 *        ADC序列扫描转换模式配置
 *
 * @param ADC_SerialChStruct
 */
void ADC_SerialChScanModeCfg(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
    ADC_SerialChCommon(ADC_SerialChStruct);
    REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_MODE_Msk, ADC_SerialChScanMode);
}

/**
 * @brief
 *        ADC序列多次转换模式配置
 *
 * @param ADC_SerialChStruct
 * @param cntAdcSample: 0 ~ 255
 */
void ADC_SerialChMoreModeCfg(ADC_SerialChTypeDef *ADC_SerialChStruct,
                             uint8_t cntAdcSample)
{
    ADC_SerialChStruct->ADC_InitStruct.ADC_AccEn = ADC_AccEnable;    //Must be added
    ADC_SerialChCommon(ADC_SerialChStruct);
    REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_MODE_Msk, ADC_SerialChMoreMode);
    CW_ADC->CR2_f.CNT = cntAdcSample;
}

/**
 * @brief
 *        ADC序列断续转换模式配置
 *
 * @param ADC_SerialChStruct
 */
void ADC_SerialChBreakModeCfg(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
    ADC_SerialChCommon(ADC_SerialChStruct);
    REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_MODE_Msk, ADC_SerialChBreakMode);
}

/**
 * @brief
 *          单通道模式的内置跟随器使能
 *
 * @param   enAdcSampCh:
 *          @arg ADC_ExInputCH0
 *          @arg ADC_ExInputCH1
 *          @arg ADC_ExInputCH2
 *          @arg ADC_ExInputCH3
 *          @arg ADC_ExInputCH4
 *          @arg ADC_ExInputCH5
 *          @arg ADC_ExInputCH6
 *          @arg ADC_ExInputCH7
 *          @arg ADC_ExInputCH8
 *          @arg ADC_ExInputCH9
 *          @arg ADC_ExInputCH10
 *          @arg ADC_ExInputCH11
 *          @arg ADC_ExInputCH12
 *          @arg ADC_VddaDiV3Input
 *          @arg ADC_TsInput
 *          @arg ADC_Vref1P2Input
 */
void ADC_BufEnSingleCh(uint32_t enAdcSampCh)
{
    if ((enAdcSampCh == ADC_VddaDiV3Input) || (enAdcSampCh == ADC_TsInput)
            || (enAdcSampCh == ADC_Vref1P2Input))
    {
        REGBITS_SET(CW_ADC->CR0, ADC_CR0_BUF_Msk);
    }
    if (enAdcSampCh == ADC_Vref1P2Input)
    {
        REGBITS_SET(CW_ADC->CR0, ADC_CR0_BGREN_Msk);
    }
    //如果ADC通道选择了内置温度传感器输出电压，则需要使能内置温度传感器
    else if (enAdcSampCh == ADC_TsInput)
    {
        //使能内置温度传感器
        REGBITS_SET(CW_ADC->CR0, ADC_CR0_TSEN_Msk);
    }
    else {}
}

/**
 * @brief
 *          序列模式的内置跟随器使能
 *
 * @param enAdcSampCh:
 *        @arg ADC_SqrCh0
 *        @arg ADC_SqrCh1
 *        @arg ADC_SqrCh2
 *        @arg ADC_SqrCh3
 *        @arg ADC_SqrCh4
 *        @arg ADC_SqrCh5
 *        @arg ADC_SqrCh6
 *        @arg ADC_SqrCh7
 *        @arg ADC_SqrCh8
 *        @arg ADC_SqrCh9
 *        @arg ADC_SqrCh10
 *        @arg ADC_SqrCh11
 *        @arg ADC_SqrCh12
 *        @arg ADC_SqrVddaDiV3
 *        @arg ADC_SqrTs
 *        @arg ADC_SqrVref1P2
 */
void ADC_BufEnSerialCh(uint32_t enAdcSampCh)
{
    if ((enAdcSampCh == ADC_SqrVddaDiV3) || (enAdcSampCh == ADC_SqrTs)
            || (enAdcSampCh == ADC_SqrVref1P2))
    {
        REGBITS_SET(CW_ADC->CR0, ADC_CR0_BUF_Msk);
    }
    if (enAdcSampCh == ADC_SqrVref1P2)
    {
        REGBITS_SET(CW_ADC->CR0, ADC_CR0_BGREN_Msk);
    }
    //如果ADC通道选择了内置温度传感器输出电压，则需要使能内置温度传感器
    else if (enAdcSampCh == ADC_SqrTs)
    {
        //使能内置温度传感器
        REGBITS_SET(CW_ADC->CR0, ADC_CR0_TSEN_Msk);
    }
    else {}
}

/**
 * @brief
 *          序列SQR0转换通道配置
 *
 * @param   ADC_SerialChStruct
 */
void ADC_Sqr0ChannelCfg(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
    ASSERT(NULL != ADC_SerialChStruct);
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr0Chmux));
    assert_param(IS_ADC_SQR_ENS(ADC_SerialChStruct->ADC_SqrEns));
    //ADC_SerialChStruct->ADC_SqrEns = ADC_SqrEns0;
    REGBITS_MODIFY(CW_ADC->SQR, ADC_SQR_ENS_Msk | ADC_SQR_SQR0_Msk,
                   ADC_SerialChStruct->ADC_SqrEns | \
                   ADC_SerialChStruct->ADC_Sqr0Chmux);
    ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr0Chmux);
}

/**
 * @brief
 *          序列SQR0/SQR1转换通道配置
 *
 * @param   ADC_SerialChStruct
 */
void ADC_Sqr01ChannelCfg(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
    ASSERT(NULL != ADC_SerialChStruct);
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr0Chmux));
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr1Chmux));
    assert_param(IS_ADC_SQR_ENS(ADC_SerialChStruct->ADC_SqrEns));
    //ADC_SerialChStruct->ADC_SqrEns = ADC_SqrEns01;
    REGBITS_MODIFY(CW_ADC->SQR,
                   ADC_SQR_ENS_Msk | ADC_SQR_SQR0_Msk | ADC_SQR_SQR1_Msk,
                   ADC_SerialChStruct->ADC_SqrEns | \
                   (ADC_SerialChStruct->ADC_Sqr1Chmux << ADC_SQR_SQR1_Pos) | \
                   ADC_SerialChStruct->ADC_Sqr0Chmux);
    ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr0Chmux);
    ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr1Chmux);
}

/**
 * @brief
 *          序列SQR0~SQR2转换通道配置
 *
 * @param   ADC_SerialChStruct
 */
void ADC_Sqr02ChannelCfg(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
    ASSERT(NULL != ADC_SerialChStruct);
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr0Chmux));
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr1Chmux));
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr2Chmux));
    assert_param(IS_ADC_SQR_ENS(ADC_SerialChStruct->ADC_SqrEns));
    //ADC_SerialChStruct->ADC_SqrEns = ADC_SqrEns02;
    REGBITS_MODIFY(CW_ADC->SQR,
                   ADC_SQR_ENS_Msk | ADC_SQR_SQR0_Msk | \
                   ADC_SQR_SQR1_Msk | ADC_SQR_SQR2_Msk,
                   ADC_SerialChStruct->ADC_SqrEns | \
                   (ADC_SerialChStruct->ADC_Sqr2Chmux << ADC_SQR_SQR2_Pos) | \
                   (ADC_SerialChStruct->ADC_Sqr1Chmux << ADC_SQR_SQR1_Pos) | \
                   ADC_SerialChStruct->ADC_Sqr0Chmux);
    ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr0Chmux);
    ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr1Chmux);
    ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr2Chmux);
}

/**
 * @brief
 *          序列SQR0~SQR3转换通道配置
 *
 * @param   ADC_SerialChStruct
 */
void ADC_Sqr03ChannelCfg(ADC_SerialChTypeDef *ADC_SerialChStruct)
{
    ASSERT(NULL != ADC_SerialChStruct);
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr0Chmux));
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr1Chmux));
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr2Chmux));
    assert_param(IS_ADC_SQR_CH(ADC_SerialChStruct->ADC_Sqr3Chmux));
    assert_param(IS_ADC_SQR_ENS(ADC_SerialChStruct->ADC_SqrEns));
    //ADC_SerialChStruct->ADC_SqrEns = ADC_SqrEns03;
    REGBITS_MODIFY(CW_ADC->SQR,
                   ADC_SQR_ENS_Msk | ADC_SQR_SQR0_Msk | \
                   ADC_SQR_SQR1_Msk | ADC_SQR_SQR2_Msk | ADC_SQR_SQR3_Msk,
                   ADC_SerialChStruct->ADC_SqrEns | \
                   (ADC_SerialChStruct->ADC_Sqr3Chmux << ADC_SQR_SQR3_Pos) | \
                   (ADC_SerialChStruct->ADC_Sqr2Chmux << ADC_SQR_SQR2_Pos) | \
                   (ADC_SerialChStruct->ADC_Sqr1Chmux << ADC_SQR_SQR1_Pos) | \
                   ADC_SerialChStruct->ADC_Sqr0Chmux);
    ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr0Chmux);
    ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr1Chmux);
    ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr2Chmux);
    ADC_BufEnSerialCh(ADC_SerialChStruct->ADC_Sqr3Chmux);
}

/**
 * @brief
 *          触发DMA读取命令
 *
 * @param   NewState:
 *          @arg DISABLE
 *          @arg ENABLE
 */
void ADC_DMACmd(FunctionalState NewState)
{
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        REGBITS_SET(CW_ADC->CR1, ADC_CR1_DMAEN_Msk);
    }
    else
    {
        REGBITS_CLR(CW_ADC->CR1, ADC_CR1_DMAEN_Msk);
    }
}

/**
 * @brief
 *       触发DMA读取使能
 *
 */
void ADC_DMAEnable(void)
{
    REGBITS_SET(CW_ADC->CR1, ADC_CR1_DMAEN_Msk);
}

/**
 * @brief
 *       触发DMA读取禁止
 *
 */
void ADC_DMADisable(void)
{
    REGBITS_CLR(CW_ADC->CR1, ADC_CR1_DMAEN_Msk);
}

/**
 * @brief
 *          获取单次转换采样值
 *
 * @param
 *
 * @return uint16_t
 */
uint16_t ADC_GetConversionValue(void)
{
    return (uint16_t)(CW_ADC->RESULT0);
}

/**
 * @brief
 *          获取SQR0通道采样值
 *
 * @param   pAdcResult
 */
void ADC_GetSqr0Result(uint16_t *pAdcResult)
{
    if (NULL == pAdcResult)
    {
        return;
    }
    *pAdcResult = (uint16_t)(CW_ADC->RESULT0);
}

/**
 * @brief
 *          获取SQR1通道采样值
 *
 * @param   pAdcResult
 */
void ADC_GetSqr1Result(uint16_t *pAdcResult)
{
    if (NULL == pAdcResult)
    {
        return;
    }
    *pAdcResult = (uint16_t)(CW_ADC->RESULT1);
}

/**
 * @brief
 *          获取SQR2通道采样值
 *
 * @param   pAdcResult
 */
void ADC_GetSqr2Result(uint16_t *pAdcResult)
{
    if (NULL == pAdcResult)
    {
        return;
    }
    *pAdcResult = (uint16_t)(CW_ADC->RESULT2);
}

/**
 * @brief
 *          获取SQR3通道采样值
 *
 * @param   pAdcResult
 */
void ADC_GetSqr3Result(uint16_t *pAdcResult)
{
    if (NULL == pAdcResult)
    {
        return;
    }
    *pAdcResult = (uint16_t)(CW_ADC->RESULT3);
}

/**
 * @brief
 *          获取累加采样值
 *
 * @param   pAdcAccResult
 */
void ADC_GetAccResult(uint32_t *pAdcAccResult)
{
    if (NULL == pAdcAccResult)
    {
        return;
    }
    *pAdcAccResult = (uint32_t)(CW_ADC->RESULTACC);
}

/**
 * @brief
 *          清零累加采样值
 */
void ADC_ClrAccResult(void)
{
    REGBITS_SET(CW_ADC->CR2, ADC_CR2_ACCRST_Msk);
}

/**
 * @brief
 *          设置ADC参考电压
 *
 * @param   ADC_VrefSel:
 *          @arg ADC_Vref_BGR1p5
 *          @arg ADC_Vref_BGR2p5
 *          @arg ADC_Vref_Extern1
 *          @arg ADC_Vref_VDDA
 */
void ADC_SetVref(uint32_t ADC_VrefSel)
{
    assert_param(IS_ADC_VREF_SEL(ADC_VrefSel));
    REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_REF_Msk,
                   ADC_VrefSel);
    if (ADC_VrefSel == ADC_Vref_Extern1)
    {
        //初始化ExRef：PB00
        REGBITS_SET(CW_SYSCTRL->AHBEN, SYSCTRL_AHBEN_GPIOB_Msk); //打开GPIO时钟
        PB00_ANALOG_ENABLE();
    }
}
/**
 * @brief
 *          设置ADC结果对齐方式
 *
 * @param   enAlign:
 *          @arg ADC_AlignRight
 *          @arg ADC_AlignLeft
 */
void ADC_SetAlign(uint32_t enAlign)
{
    REGBITS_MODIFY(CW_ADC->CR1, ADC_CR1_ALIGN_Msk, enAlign);
}

/**
 * @brief
 *        设置单通道ADC转换结果溢出保存策略
 *
 * @param enDiscard:
 *        @arg ADC_DiscardNull
 *        @arg ADC_DiscardEnable
 */
void ADC_SetDiscard(uint32_t enDiscard)
{
    assert_param(IS_ADC_DATA_DISCARD(enDiscard));
    REGBITS_MODIFY(CW_ADC->CR1, ADC_CR1_DISCARD_Msk, enDiscard);
}

/**
 * @brief
 *        设置内置温度传感器使能控制
 *
 * @param enTs:
 *        @arg ADC_TsDisable
 *        @arg ADC_TsEnable
 */
void ADC_SetTs(uint32_t enTs)
{
    assert_param(IS_ADC_TS_ENABLE(enTs));
    REGBITS_MODIFY(CW_ADC->CR0, ADC_CR0_TSEN_Msk, enTs);
}

/**
 * @brief
 *        读取ADC参考电压1.5V时的温度传感器的测量温度
 *
 * @param fAdcTsDegree
 */
void ADC_GetTsVref1V5(float *fAdcTsDegree)
{
    uint16_t u16AdcResult;
    uint8_t temp1;
    uint16_t temp2;
    temp1 = *((uint8_t *)(ADDR_T0));
    temp2 = *((uint16_t *)(ADDR_TRIM_1P5));
    /*Caution: Must select ADC_GetSqr0Result()~ADC_GetSqr3Result() instead of ADC_GetConversionValue() if using ADC_SQR convertion.
    * ADC single channel convertion is default.
    */
    u16AdcResult = ADC_GetConversionValue();
    //ADC_GetSqr0Result(&u16AdcResult);    //Using ADC_SQR0.
    //ADC_GetSqr1Result(&u16AdcResult);    //Using ADC_SQR1.
    //ADC_GetSqr2Result(&u16AdcResult);    //Using ADC_SQR2.
    //ADC_GetSqr3Result(&u16AdcResult);    //Using ADC_SQR3.
    *fAdcTsDegree = temp1 * 0.5f + COEFF_TS * 1.5f * (u16AdcResult - temp2);
}

/**
 * @brief
 *        读取ADC参考电压2.5V时的温度传感器的测量温度
 *
 * @param fAdcTsDegree
 */
void ADC_GetTsVref2V5(float *fAdcTsDegree)
{
    uint16_t u16AdcResult;
    uint8_t temp1;
    uint16_t temp2;
    temp1 = *((uint8_t *)(ADDR_T0));
    temp2 = *((uint16_t *)(ADDR_TRIM_2P5));
    /*Caution: Must select ADC_GetSqr0Result()~ADC_GetSqr3Result() instead of ADC_GetConversionValue() if using ADC_SQR convertion.
    * ADC single channel convertion is default.
    */
    u16AdcResult = ADC_GetConversionValue();
    //ADC_GetSqr0Result(&u16AdcResult);    //Using ADC_SQR0.
    //ADC_GetSqr1Result(&u16AdcResult);    //Using ADC_SQR1.
    //ADC_GetSqr2Result(&u16AdcResult);    //Using ADC_SQR2.
    //ADC_GetSqr3Result(&u16AdcResult);    //Using ADC_SQR3.
    *fAdcTsDegree = temp1 * 0.5f + COEFF_TS * 2.5f * (u16AdcResult - temp2);
}

/**
 * @brief
 *          ADC自动停止配置
 *
 * @param   enAutoStop:
 *          @arg ADC_AutoStopDisable
 *          @arg ADC_AutoStopEnable
 */
void ADC_AutoStop(uint32_t enAutoStop)
{
    REGBITS_MODIFY(CW_ADC->START, ADC_START_AUTOSTOP_Msk, enAutoStop);
}

/**
 * @brief
 *          ADC中断配置
 *
 * @param   ADC_IT:
 *          @arg ADC_IT_READY
 *          @arg ADC_IT_OVW
 *          @arg ADC_IT_WDTR
 *          @arg ADC_IT_WDTH
 *          @arg ADC_IT_WDTL
 *          @arg ADC_IT_EOA
 *          @arg ADC_IT_EOS
 *          @arg ADC_IT_EOC
 * @param   NewState:
 *          @arg DISABLE
 *          @arg ENABLE
 */
void ADC_ITConfig(uint16_t ADC_IT, FunctionalState NewState)
{
    uint8_t itMask = 0;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_IT(ADC_IT));
    /* Get the ADC IT index */
    itMask = (uint8_t) ADC_IT;
    if (NewState != DISABLE)
    {
        /* Enable the selected ADC interrupts */
        CW_ADC->IER |= itMask;
    }
    else
    {
        /* Disable the selected ADC interrupts */
        CW_ADC->IER &= (~(uint32_t) itMask);
    }
}

/**
 * @brief
 *          使能NVIC中ADC中断
 *
 * @param   intPriority:
 *          @arg 0 ~ 3
 */
void ADC_EnableNvic(uint8_t intPriority)
{
    if (intPriority < (1UL << __NVIC_PRIO_BITS))
    {
        NVIC_ClearPendingIRQ(ADC_IRQn);
        NVIC_EnableIRQ(ADC_IRQn);
        NVIC_SetPriority(ADC_IRQn, intPriority);
    }
}

/**
 * @brief
 *          禁用NVIC中ADC中断
 *
 * @param
 *
 */
void ADC_DisableNvic(void)
{
    NVIC_ClearPendingIRQ(ADC_IRQn);
    NVIC_DisableIRQ(ADC_IRQn);
    NVIC_SetPriority(ADC_IRQn, ADC_INT_PRIORITY);
}
//@} // AdcGroup

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

