/**
 * @file cw32f030_rcc.h
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
#ifndef __CW32F030_RCC_H
#define __CW32F030_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cw32f030.h"
#include "system_cw32f030.h"

//==================================================================================
#define HSIOSC_VALUE                               ((uint32_t)48000000)                 /*!< Value of the Internal oscillator in Hz*/
#define HSE_VALUE                                  ((uint32_t)16000000)                 /*!< Value of the External oscillator in Hz */

#define LSI_VALUE                               ((uint32_t)32800) /*!< Value of the External oscillator in Hz */
#define LSE_VALUE                               ((uint32_t)32768) /*!< Value of the External oscillator in Hz */
/* SYSCTRL CR0 --------------------------------------------------------*/
#define SYSCTRL_BYPASS                          (0x5A5A0000U)
#define SYSCTRL_BYPASS_MASK                     (0xFFFF0000U)

#define RCC_HCLK_DIV1                           (0x0UL << SYSCTRL_CR0_HCLKPRS_Pos)/*!< SYSCLK not divided */
#define RCC_HCLK_DIV2                           (0x1UL << SYSCTRL_CR0_HCLKPRS_Pos)/*!< SYSCLK divided by 2 */
#define RCC_HCLK_DIV4                           (0x2UL << SYSCTRL_CR0_HCLKPRS_Pos)/*!< SYSCLK divided by 4 */
#define RCC_HCLK_DIV8                           (0x3UL << SYSCTRL_CR0_HCLKPRS_Pos)/*!< SYSCLK divided by 8 */
#define RCC_HCLK_DIV16                          (0x4UL << SYSCTRL_CR0_HCLKPRS_Pos)/*!< SYSCLK divided by 16 */
#define RCC_HCLK_DIV32                          (0x5UL << SYSCTRL_CR0_HCLKPRS_Pos)/*!< SYSCLK divided by 32 */
#define RCC_HCLK_DIV64                          (0x6UL << SYSCTRL_CR0_HCLKPRS_Pos)/*!< SYSCLK divided by 64 */
#define RCC_HCLK_DIV128                         (0x7ul << SYSCTRL_CR0_HCLKPRS_Pos)/*!< SYSCLK divided by 128 */
#define IS_RCC_HCLKPRS(INSTANCE)                (((INSTANCE) == RCC_HCLK_DIV1)  ||\
                                                 ((INSTANCE) == RCC_HCLK_DIV2)  ||\
                                                 ((INSTANCE) == RCC_HCLK_DIV4)  ||\
                                                 ((INSTANCE) == RCC_HCLK_DIV8)  ||\
                                                 ((INSTANCE) == RCC_HCLK_DIV16) ||\
                                                 ((INSTANCE) == RCC_HCLK_DIV32) ||\
                                                 ((INSTANCE) == RCC_HCLK_DIV64) ||\
                                                 ((INSTANCE) == RCC_HCLK_DIV128))

#define RCC_PCLK_DIV1                           (0x0UL << SYSCTRL_CR0_PCLKPRS_Pos)  /*!< HCLK not divided */
#define RCC_PCLK_DIV2                           (0x1UL << SYSCTRL_CR0_PCLKPRS_Pos)  /*!< HCLK divided by 2 */
#define RCC_PCLK_DIV4                           (0x2UL << SYSCTRL_CR0_PCLKPRS_Pos)  /*!< HCLK divided by 4 */
#define RCC_PCLK_DIV8                           (0x3UL << SYSCTRL_CR0_PCLKPRS_Pos)  /*!< HCLK divided by 8 */
#define IS_RCC_PCLKPRS(INSTANCE)                (((INSTANCE) == RCC_PCLK_DIV1) ||\
                                                 ((INSTANCE) == RCC_PCLK_DIV2) ||\
                                                 ((INSTANCE) == RCC_PCLK_DIV4) ||\
                                                 ((INSTANCE) == RCC_PCLK_DIV8))

#define RCC_SYSCLKSRC_HSI                       (0x00000000U) /*!< HSI selected as system clock */
#define RCC_SYSCLKSRC_HSE                       (0x00000001U) /*!< HSE selected as system clock */
#define RCC_SYSCLKSRC_PLL                       (0x00000002U) /*!< PLL selected as system clock */
#define RCC_SYSCLKSRC_LSI                       (0x00000003U) /*!< LSI selected as system clock */
#define RCC_SYSCLKSRC_LSE                       (0x00000004U) /*!< LSE selected as system clock */
#define IS_RCC_SYSCLKSRC(INSTANCE)              (((INSTANCE) == RCC_SYSCLKSRC_HSI) ||\
                                                 ((INSTANCE) == RCC_SYSCLKSRC_HSE) ||\
                                                 ((INSTANCE) == RCC_SYSCLKSRC_PLL) ||\
                                                 ((INSTANCE) == RCC_SYSCLKSRC_LSI) ||\
                                                 ((INSTANCE) == RCC_SYSCLKSRC_LSE))

/* SYSCTRL CR1 --------------------------------------------------------*/
#define RCC_SYSCTRL_HSIEN                       bv0
#define RCC_SYSCTRL_HSEEN                       bv1
#define RCC_SYSCTRL_PLLEN                       bv2
#define RCC_SYSCTRL_LSIEN                       bv3
#define RCC_SYSCTRL_LSEEN                       bv4

#define RCC_SYSCTRL_LSELOCKEN                   bv5
#define RCC_SYSCTRL_LSELOCKDIS                  0x00UL
#define IS_RCC_LSELOCK_STATUS(INSTANCE)         (((INSTANCE) == RCC_SYSCTRL_LSELOCKEN) ||\
                                                 ((INSTANCE) == RCC_SYSCTRL_LSELOCKDIS))

#define RCC_SYSCTRL_LSECCS                      bv6
#define RCC_SYSCTRL_HSECCS                      bv7
#define RCC_SYSCTRL_CLKCCS                      bv8
#define IS_RCC_CCS_STATUS(INSTANCE)             (((INSTANCE) == RCC_SYSCTRL_LSECCS) ||\
                                                 ((INSTANCE) == RCC_SYSCTRL_HSECCS) ||\
                                                 ((INSTANCE) == RCC_SYSCTRL_CLKCCS))

/* SYSCTRL CR2 --------------------------------------------------------*/
#define RCC_SYSCTRL_SWDIOEN                     0x00UL
#define RCC_SYSCTRL_SWDIODIS                    bv1
#define IS_RCC_SWDIO_STATUS(INSTANCE)           (((INSTANCE) == RCC_SYSCTRL_SWDIOEN) ||\
                                                 ((INSTANCE) == RCC_SYSCTRL_SWDIODIS))

#define RCC_SYSCTRL_LOCKUPEN                    bv2
#define RCC_SYSCTRL_LOCKUPDIS                   0x00UL
#define IS_RCC_LOCKUP_STATUS(INSTANCE)          (((INSTANCE) == RCC_SYSCTRL_LOCKUPEN) ||\
                                                 ((INSTANCE) == RCC_SYSCTRL_LOCKUPDIS))

#define RCC_SYSCTRL_WAKEUPCLKEN                 bv3
#define RCC_SYSCTRL_WAKEUPCLKDIS                0x00UL
#define IS_RCC_WAKEUPCLK_STATUS(INSTANCE)       (((INSTANCE) == RCC_SYSCTRL_WAKEUPCLKEN) ||\
                                                 ((INSTANCE) == RCC_SYSCTRL_WAKEUPCLKDIS))
/* SYSCTRL HSI --------------------------------------------------------*/
#define RCC_HSI_TRIMCODEADDR                    (0x00012600U)
#define RCC_HSIOSC_DIV6                         (0x5U)
#define RCC_HSIOSC_DIV1                         (0x6U)
#define RCC_HSIOSC_DIV2                         (0x8U)
#define RCC_HSIOSC_DIV3                         (0x7U)
#define RCC_HSIOSC_DIV4                         (0x9U)
#define RCC_HSIOSC_DIV8                         (0xBU)
#define RCC_HSIOSC_DIV10                        (0xCU)
#define RCC_HSIOSC_DIV12                        (0xDU)
#define RCC_HSIOSC_DIV14                        (0xEU)
#define RCC_HSIOSC_DIV16                        (0xFU)

#define IS_RCC_HSIOSC_DIV(INSTANCE)             (((INSTANCE) == RCC_HSIOSC_DIV1)  ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV2)  ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV3)  ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV4)  ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV6)  ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV8)  ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV10) ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV12) ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV14) ||\
                                                 ((INSTANCE) == RCC_HSIOSC_DIV16))

/* SYSCTRL LSI --------------------------------------------------------*/
#define RCC_LSI_TRIMCODEADDR                    (0x00012602U)
#define RCC_LSI_WAITCYCLE_6                     ((uint32_t)(0x0UL << SYSCTRL_LSI_WAITCYCLE_Pos))
#define RCC_LSI_WAITCYCLE_18                    ((uint32_t)(0x1UL << SYSCTRL_LSI_WAITCYCLE_Pos))
#define RCC_LSI_WAITCYCLE_66                    ((uint32_t)(0x2UL << SYSCTRL_LSI_WAITCYCLE_Pos))
#define RCC_LSI_WAITCYCLE_258                   ((uint32_t)(0x3UL << SYSCTRL_LSI_WAITCYCLE_Pos))


/* SYSCTRL HSE --------------------------------------------------------*/
#define RCC_HSE_FLT_CLOSE                       (0x00000000U)
#define RCC_HSE_FLT_OPEN                        SYSCTRL_HSE_FLT_Msk //(0x80UL)
#define IS_RCC_HSE_FLT(INSTANCE)                (((INSTANCE) == RCC_HSE_FLT_CLOSE) ||\
                                                 ((INSTANCE) == RCC_HSE_FLT_OPEN))

#define RCC_HSE_MODE_OSC                        (0x00000000U)
#define RCC_HSE_MODE_CLK                        SYSCTRL_HSE_MODE_Msk //(0x40UL)
#define IS_RCC_HSE_MODE(INSTANCE)               (((INSTANCE) == RCC_HSE_MODE_OSC) ||\
                                                 ((INSTANCE) == RCC_HSE_MODE_CLK))

#define RCC_HSE_WAITCYCLE_8192                  (0x00000000U)
#define RCC_HSE_WAITCYCLE_32768                 ((uint32_t)(0x1UL << SYSCTRL_HSE_WAITCYCLE_Pos))
#define RCC_HSE_WAITCYCLE_131072                ((uint32_t)(0x2UL << SYSCTRL_HSE_WAITCYCLE_Pos))
#define RCC_HSE_WAITCYCLE_262144                ((uint32_t)(0x3UL << SYSCTRL_HSE_WAITCYCLE_Pos))

#define RCC_HSE_FREQ_GT4M                       (0x00000000U)
#define RCC_HSE_FREQ_GT8M                       ((uint32_t)(0x1UL << SYSCTRL_HSE_FREQRANGE_Pos))
#define RCC_HSE_FREQ_GT16M                      ((uint32_t)(0x2UL << SYSCTRL_HSE_FREQRANGE_Pos))
#define RCC_HSE_FREQ_GT24M                      ((uint32_t)(0x3UL << SYSCTRL_HSE_FREQRANGE_Pos))
#define IS_RCC_HSE_FREQIN(INSTANCE)             (((INSTANCE) >=4000000)  && ((INSTANCE) <=32000000))

#define RCC_HSE_DRIVER_LEAST                    0x00U
#define RCC_HSE_DRIVER_SMALL                    0x01U
#define RCC_HSE_DRIVER_NORMAL                   0x02U
#define RCC_HSE_DRIVER_LARGER                   0x03U
#define IS_RCC_HSE_DRIVER(INSTANCE)             (((INSTANCE) == RCC_HSE_DRIVER_LEAST)  ||\
                                                 ((INSTANCE) == RCC_HSE_DRIVER_SMALL)  ||\
                                                 ((INSTANCE) == RCC_HSE_DRIVER_NORMAL) ||\
                                                 ((INSTANCE) == RCC_HSE_DRIVER_LARGER))

/* SYSCTRL LSE --------------------------------------------------------*/
#define RCC_LSE_MODE_OSC                        (0x00000000U)
#define RCC_LSE_MODE_CLK                        SYSCTRL_LSE_MODE_Msk

#define IS_RCC_LSE_MODE(INSTANCE)               (((INSTANCE) == RCC_LSE_MODE_OSC) ||\
                                                 ((INSTANCE) == RCC_LSE_MODE_CLK))

#define RCC_LSE_AMP_LEAST                       (0x00000000U)
#define RCC_LSE_AMP_SMALL                       ((uint32_t)(0x1UL << SYSCTRL_LSE_AMP_Pos))
#define RCC_LSE_AMP_NORMAL                      ((uint32_t)(0x2UL << SYSCTRL_LSE_AMP_Pos))
#define RCC_LSE_AMP_LARGER                      ((uint32_t)(0x3UL << SYSCTRL_LSE_AMP_Pos))
#define IS_RCC_LSE_AMP(AMP)                     (((AMP) == RCC_LSE_AMP_LEAST)  ||\
                                                 ((AMP) == RCC_LSE_AMP_SMALL)  ||\
                                                 ((AMP) == RCC_LSE_AMP_NORMAL) ||\
                                                 ((AMP) == RCC_LSE_AMP_LARGER))

#define RCC_LSE_DRIVER_LEAST                    (0x00000000U)
#define RCC_LSE_DRIVER_SMALL                    (0x00000001U)
#define RCC_LSE_DRIVER_NORMAL                   (0x00000002U)
#define RCC_LSE_DRIVER_LARGER                   (0x00000003U)

#define IS_RCC_LSE_DRIVER(DRIVER)               (((DRIVER) == RCC_LSE_DRIVER_LEAST)||\
                                                 ((DRIVER) == RCC_LSE_DRIVER_SMALL)   ||\
                                                 ((DRIVER) == RCC_LSE_DRIVER_NORMAL)  ||\
                                                 ((DRIVER) == RCC_LSE_DRIVER_LARGER))

#define RCC_LSE_WAITCYCLE_256                   (0x00000000U)
#define RCC_LSE_WAITCYCLE_1024                  ((uint32_t)(0x1UL << SYSCTRL_LSE_WAITCYCLE_Pos))
#define RCC_LSE_WAITCYCLE_4096                  ((uint32_t)(0x2UL << SYSCTRL_LSE_WAITCYCLE_Pos))
#define RCC_LSE_WAITCYCLE_16384                 ((uint32_t)(0x3UL << SYSCTRL_LSE_WAITCYCLE_Pos))



/* SYSCTRL PLL --------------------------------------------------------*/
#define RCC_PLLSOURCE_HSEOSC                    (0x00000000U)  /*!< HSE oscillator clock selected as PLL entry clock source */
#define RCC_PLLSOURCE_HSECLK                    (0x00000001U)  /*!< HSE input clock selected as PLL entry clock source */
#define RCC_PLLSOURCE_HSI                       (0x00000003U)  /*!< HSI clock selected as PLL entry clock source */

#define IS_RCC_PLLSOURCE(INSTANCE)              (((INSTANCE) == RCC_PLLSOURCE_HSEOSC)   ||\
                                                 ((INSTANCE) == RCC_PLLSOURCE_HSECLK)         ||\
                                                 ((INSTANCE) == RCC_PLLSOURCE_HSI))

#define RCC_PLL_WAITCYCLE_128                   (0x00000000U)
#define RCC_PLL_WAITCYCLE_256                   ((uint32_t)(0x1UL << SYSCTRL_PLL_WAITCYCLE_Pos))
#define RCC_PLL_WAITCYCLE_512                   ((uint32_t)(0x2UL << SYSCTRL_PLL_WAITCYCLE_Pos))
#define RCC_PLL_WAITCYCLE_1024                  ((uint32_t)(0x3UL << SYSCTRL_PLL_WAITCYCLE_Pos))
#define RCC_PLL_WAITCYCLE_2048                  ((uint32_t)(0x4UL << SYSCTRL_PLL_WAITCYCLE_Pos))
#define RCC_PLL_WAITCYCLE_4096                  ((uint32_t)(0x5UL << SYSCTRL_PLL_WAITCYCLE_Pos))
#define RCC_PLL_WAITCYCLE_8192                  ((uint32_t)(0x6UL << SYSCTRL_PLL_WAITCYCLE_Pos))
#define RCC_PLL_WAITCYCLE_16384                 ((uint32_t)(0x7UL << SYSCTRL_PLL_WAITCYCLE_Pos))

#define RCC_PLL_FREQOUT_GT12M                   (0x00000000U)
#define RCC_PLL_FREQOUT_GT18M                   ((uint32_t)(0x1UL << SYSCTRL_PLL_FREQOUT_Pos))
#define RCC_PLL_FREQOUT_GT24M                   ((uint32_t)(0x2UL << SYSCTRL_PLL_FREQOUT_Pos))
#define RCC_PLL_FREQOUT_GT36M                   ((uint32_t)(0x3UL << SYSCTRL_PLL_FREQOUT_Pos))
#define RCC_PLL_FREQOUT_GT48M                   ((uint32_t)(0x4UL << SYSCTRL_PLL_FREQOUT_Pos))
#define IS_RCC_PLL_FREQIN(INSTANCE)             (INSTANCE >=4000000)  && (INSTANCE <=24000000)


#define RCC_PLL_MUL_2                           (0x2U)
#define RCC_PLL_MUL_3                           (0x3U)
#define RCC_PLL_MUL_4                           (0x4U)
#define RCC_PLL_MUL_5                           (0x5U)
#define RCC_PLL_MUL_6                           (0x6U)
#define RCC_PLL_MUL_7                           (0x7U)
#define RCC_PLL_MUL_8                           (0x8U)
#define RCC_PLL_MUL_9                           (0x9U)
#define RCC_PLL_MUL_10                          (0xAU)
#define RCC_PLL_MUL_11                          (0xBU)
#define RCC_PLL_MUL_12                          (0xCU)
#define IS_RCC_PLL_MUL(INSTANCE)                (((INSTANCE) == RCC_PLL_MUL_2)  ||\
                                                 ((INSTANCE) == RCC_PLL_MUL_3)  ||\
                                                 ((INSTANCE) == RCC_PLL_MUL_4)  ||\
                                                 ((INSTANCE) == RCC_PLL_MUL_5)  ||\
                                                 ((INSTANCE) == RCC_PLL_MUL_6)  ||\
                                                 ((INSTANCE) == RCC_PLL_MUL_7)  ||\
                                                 ((INSTANCE) == RCC_PLL_MUL_8)  ||\
                                                 ((INSTANCE) == RCC_PLL_MUL_9)  ||\
                                                 ((INSTANCE) == RCC_PLL_MUL_10) ||\
                                                 ((INSTANCE) == RCC_PLL_MUL_11) ||\
                                                 ((INSTANCE) == RCC_PLL_MUL_12))


#define RCC_IT_HSEFAULT                         (bv8)
#define RCC_IT_LSEFAULT                         (bv7)
#define RCC_IT_HSEFAIL                          (bv6)
#define RCC_IT_LSEFAIL                          (bv5)
#define RCC_IT_LSERDY                           (bv4)
#define RCC_IT_LSIRDY                           (bv3)
#define RCC_IT_PLLRDY                           (bv2)
#define RCC_IT_HSERDY                           (bv1)
#define RCC_IT_HSIRDY                           (bv0)
#define IS_RCC_IT(IT)                           ((((IT) & 0xFFFFFFE0) == 0x0UL) && ((IT) != 0x0UL))
#define IS_RCC_GET_IT(IT)                       (((IT) == RCC_IT_HSEFAULT) || \
                                                 ((IT) == RCC_IT_LSEFAULT) || \
                                                 ((IT) == RCC_IT_HSEFAIL)  || \
                                                 ((IT) == RCC_IT_LSEFAIL)  ||\
                                                 ((IT) == RCC_IT_LSERDY)   ||\
                                                 ((IT) == RCC_IT_LSIRDY)   ||\
                                                 ((IT) == RCC_IT_PLLRDY)   ||\
                                                 ((IT) == RCC_IT_HSERDY)   ||\
                                                 ((IT) == RCC_IT_HSIRDY))


#define RCC_FLAG_HSISTABLE                      bv11
#define RCC_FLAG_HSESTABLE                      bv12
#define RCC_FLAG_PLLSTABLE                      bv13
#define RCC_FLAG_LSESTABLE                      bv15
#define RCC_FLAG_LSISTABLE                      bv14
#define IS_RCC_STABLEFLAG(FLAG)                 (((FLAG) == RCC_FLAG_HSISTABLE) || ((FLAG) == RCC_FLAG_HSESTABLE) ||\
                                                 ((FLAG) == RCC_FLAG_PLLSTABLE) || ((FLAG) == RCC_FLAG_LSESTABLE) ||\
                                                 ((FLAG) == RCC_FLAG_LSISTABLE))

#define RCC_FLAG_PINRST                         bv6
#define RCC_FLAG_PORRST                         bv0
#define RCC_FLAG_LVDRST                         bv3
#define RCC_FLAG_LOCKUPRST                      bv8
#define RCC_FLAG_IWDTRST                        bv4
#define RCC_FLAG_WWDTRST                        bv5
#define RCC_FLAG_SYSRESETREQRST                 bv9
#define RCC_FLAG_ALLRST                         ((uint32_t)0x00000379)
#define IS_RCC_RSTFLAG(FLAG)                    (((FLAG) == RCC_FLAG_PINRST) || ((FLAG) == RCC_FLAG_PORRST) || \
                                                 ((FLAG) == RCC_FLAG_LVDRST) || ((FLAG) == RCC_FLAG_IWDTRST) || \
                                                 ((FLAG) == RCC_FLAG_WWDTRST) || ((FLAG) == RCC_FLAG_LOCKUPRST) || \
                                                 ((FLAG) == RCC_FLAG_SYSRESETREQRST) || ((FLAG) == RCC_FLAG_ALLRST))


#define RCC_AHB_PERIPH_GPIOF                    bv9
#define RCC_AHB_PERIPH_GPIOC                    bv6
#define RCC_AHB_PERIPH_GPIOB                    bv5
#define RCC_AHB_PERIPH_GPIOA                    bv4
#define RCC_AHB_PERIPH_CRC                      bv2
#define RCC_AHB_PERIPH_FLASH                    bv1
#define RCC_AHB_PERIPH_DMA                      bv0
#define IS_RCC_AHB_PERIPH(PERIPH)               ((((PERIPH) & 0xFFFFFD88 ) == 0x00) && ((PERIPH) != 0x00))

#define __RCC_GPIOF_CLK_ENABLE()                REGBITS_SET(CW_SYSCTRL->AHBEN, RCC_AHB_PERIPH_GPIOF)
#define __RCC_GPIOC_CLK_ENABLE()                REGBITS_SET(CW_SYSCTRL->AHBEN, RCC_AHB_PERIPH_GPIOC)
#define __RCC_GPIOB_CLK_ENABLE()                REGBITS_SET(CW_SYSCTRL->AHBEN, RCC_AHB_PERIPH_GPIOB)
#define __RCC_GPIOA_CLK_ENABLE()                REGBITS_SET(CW_SYSCTRL->AHBEN, RCC_AHB_PERIPH_GPIOA)
#define __RCC_CRC_CLK_ENABLE()                  REGBITS_SET(CW_SYSCTRL->AHBEN, RCC_AHB_PERIPH_CRC)
#define __RCC_FLASH_CLK_ENABLE()                REGBITS_SET(CW_SYSCTRL->AHBEN, RCC_AHB_PERIPH_FLASH)
#define __RCC_DMA_CLK_ENABLE()                  REGBITS_SET(CW_SYSCTRL->AHBEN, RCC_AHB_PERIPH_DMA)

#define __RCC_GPIOF_CLK_DISABLE()               (CW_SYSCTRL->AHBEN &= ~(RCC_AHB_PERIPH_GPIOF))
#define __RCC_GPIOC_CLK_DISABLE()               (CW_SYSCTRL->AHBEN &= ~(RCC_AHB_PERIPH_GPIOC))
#define __RCC_GPIOB_CLK_DISABLE()               (CW_SYSCTRL->AHBEN &= ~(RCC_AHB_PERIPH_GPIOB))
#define __RCC_GPIOA_CLK_DISABLE()               (CW_SYSCTRL->AHBEN &= ~(RCC_AHB_PERIPH_GPIOA))
#define __RCC_CRC_CLK_DISABLE()                 (CW_SYSCTRL->AHBEN &= ~(RCC_AHB_PERIPH_CRC))
#define __RCC_FLASH_CLK_DISABLE()               (CW_SYSCTRL->AHBEN &= ~(RCC_AHB_PERIPH_FLASH))
#define __RCC_DMA_CLK_DISABLE()                 (CW_SYSCTRL->AHBEN &= ~(RCC_AHB_PERIPH_DMA))

#define RCC_APB1_PERIPH_I2C2                    bv12
#define RCC_APB1_PERIPH_I2C1                    bv11
#define RCC_APB1_PERIPH_UART3                   bv8
#define RCC_APB1_PERIPH_UART2                   bv7
#define RCC_APB1_PERIPH_SPI2                    bv6
#define RCC_APB1_PERIPH_IWDT                    bv5
#define RCC_APB1_PERIPH_WWDT                    bv4
#define RCC_APB1_PERIPH_RTC                     bv3
#define RCC_APB1_PERIPH_GTIM2                   bv2
#define RCC_APB1_PERIPH_GTIM1                   bv1
#define IS_RCC_APB1_PERIPH(PERIPH)              ((((PERIPH) & 0xFFFFE601 ) == 0x00) && ((PERIPH) != 0x00))

#define __RCC_I2C2_CLK_ENABLE()                 REGBITS_SET(CW_SYSCTRL->APBEN1, RCC_APB1_PERIPH_I2C2)
#define __RCC_I2C1_CLK_ENABLE()                 REGBITS_SET(CW_SYSCTRL->APBEN1, RCC_APB1_PERIPH_I2C1)
#define __RCC_UART3_CLK_ENABLE()                REGBITS_SET(CW_SYSCTRL->APBEN1, RCC_APB1_PERIPH_UART3)
#define __RCC_UART2_CLK_ENABLE()                REGBITS_SET(CW_SYSCTRL->APBEN1, RCC_APB1_PERIPH_UART2)
#define __RCC_SPI2_CLK_ENABLE()                 REGBITS_SET(CW_SYSCTRL->APBEN1, RCC_APB1_PERIPH_SPI2)
#define __RCC_IWDT_CLK_ENABLE()                 REGBITS_SET(CW_SYSCTRL->APBEN1, RCC_APB1_PERIPH_IWDT)
#define __RCC_WWDT_CLK_ENABLE()                 REGBITS_SET(CW_SYSCTRL->APBEN1, RCC_APB1_PERIPH_WWDT)
#define __RCC_RTC_CLK_ENABLE()                  REGBITS_SET(CW_SYSCTRL->APBEN1, RCC_APB1_PERIPH_RTC)
#define __RCC_GTIM2_CLK_ENABLE()                REGBITS_SET(CW_SYSCTRL->APBEN1, RCC_APB1_PERIPH_GTIM2)
#define __RCC_GTIM1_CLK_ENABLE()                REGBITS_SET(CW_SYSCTRL->APBEN1, RCC_APB1_PERIPH_GTIM1)

#define __RCC_I2C2_CLK_DISABLE()                (CW_SYSCTRL->APBEN1 &= ~(RCC_APB1_PERIPH_I2C2))
#define __RCC_I2C1_CLK_DISABLE()                (CW_SYSCTRL->APBEN1 &= ~(RCC_APB1_PERIPH_I2C1))
#define __RCC_UART3_CLK_DISABLE()               (CW_SYSCTRL->APBEN1 &= ~(RCC_APB1_PERIPH_UART3))
#define __RCC_UART2_CLK_DISABLE()               (CW_SYSCTRL->APBEN1 &= ~(RCC_APB1_PERIPH_UART2))
#define __RCC_SPI2_CLK_DISABLE()                (CW_SYSCTRL->APBEN1 &= ~(RCC_APB1_PERIPH_SPI2))
#define __RCC_IWDT_CLK_DISABLE()                (CW_SYSCTRL->APBEN1 &= ~(RCC_APB1_PERIPH_IWDT))
#define __RCC_WWDT_CLK_DISABLE()                (CW_SYSCTRL->APBEN1 &= ~(RCC_APB1_PERIPH_WWDT))
#define __RCC_RTC_CLK_DISABLE()                 (CW_SYSCTRL->APBEN1 &= ~(RCC_APB1_PERIPH_RTC))
#define __RCC_GTIM2_CLK_DISABLE()               (CW_SYSCTRL->APBEN1 &= ~(RCC_APB1_PERIPH_GTIM2))
#define __RCC_GTIM1_CLK_DISABLE()               (CW_SYSCTRL->APBEN1 &= ~(RCC_APB1_PERIPH_GTIM1))

#define RCC_APB2_PERIPH_AWT                     bv13
#define RCC_APB2_PERIPH_BTIM                    bv12
#define RCC_APB2_PERIPH_GTIM4                   bv11
#define RCC_APB2_PERIPH_GTIM3                   bv10
#define RCC_APB2_PERIPH_UART1                   bv9
#define RCC_APB2_PERIPH_SPI1                    bv8
#define RCC_APB2_PERIPH_ATIM                    bv7
#define RCC_APB2_PERIPH_VC                      bv4
#define RCC_APB2_PERIPH_ADC                     bv2
#define IS_RCC_APB2_PERIPH(PERIPH)              ((((PERIPH) & 0xFFFFC06D ) == 0x00) && ((PERIPH) != 0x00))

#define __RCC_AWT_CLK_ENABLE()                  REGBITS_SET(CW_SYSCTRL->APBEN2, RCC_APB2_PERIPH_AWT)
#define __RCC_BTIM_CLK_ENABLE()                 REGBITS_SET(CW_SYSCTRL->APBEN2, RCC_APB2_PERIPH_BTIM)
#define __RCC_GTIM4_CLK_ENABLE()                REGBITS_SET(CW_SYSCTRL->APBEN2, RCC_APB2_PERIPH_GTIM4)
#define __RCC_GTIM3_CLK_ENABLE()                REGBITS_SET(CW_SYSCTRL->APBEN2, RCC_APB2_PERIPH_GTIM3)
#define __RCC_UART1_CLK_ENABLE()                REGBITS_SET(CW_SYSCTRL->APBEN2, RCC_APB2_PERIPH_UART1)
#define __RCC_SPI1_CLK_ENABLE()                 REGBITS_SET(CW_SYSCTRL->APBEN2, RCC_APB2_PERIPH_SPI1)
#define __RCC_ATIM_CLK_ENABLE()                 REGBITS_SET(CW_SYSCTRL->APBEN2, RCC_APB2_PERIPH_ATIM)
#define __RCC_VC_CLK_ENABLE()                   REGBITS_SET(CW_SYSCTRL->APBEN2, RCC_APB2_PERIPH_VC)
#define __RCC_ADC_CLK_ENABLE()                  REGBITS_SET(CW_SYSCTRL->APBEN2, RCC_APB2_PERIPH_ADC)


#define __RCC_AWT_CLK_DISABLE()                 (CW_SYSCTRL->APBEN2 &= ~(RCC_APB2_PERIPH_AWT))
#define __RCC_BTIM_CLK_DISABLE()                (CW_SYSCTRL->APBEN2 &= ~(RCC_APB2_PERIPH_BTIM))
#define __RCC_GTIM4_CLK_DISABLE()               (CW_SYSCTRL->APBEN2 &= ~(RCC_APB2_PERIPH_GTIM4))
#define __RCC_GTIM3_CLK_DISABLE()               (CW_SYSCTRL->APBEN2 &= ~(RCC_APB2_PERIPH_GTIM3))
#define __RCC_UART1_CLK_DISABLE()               (CW_SYSCTRL->APBEN2 &= ~(RCC_APB2_PERIPH_UART1))
#define __RCC_SPI1_CLK_DISABLE()                (CW_SYSCTRL->APBEN2 &= ~(RCC_APB2_PERIPH_SPI1))
#define __RCC_ATIM_CLK_DISABLE()                (CW_SYSCTRL->APBEN2 &= ~(RCC_APB2_PERIPH_ATIM))
#define __RCC_VC_CLK_DISABLE()                  (CW_SYSCTRL->APBEN2 &= ~(RCC_APB2_PERIPH_VC))
#define __RCC_ADC_CLK_DISABLE()                 (CW_SYSCTRL->APBEN2 &= ~(RCC_APB2_PERIPH_ADC))

#define RCC_MCO_DIV1                            (0x00U)
#define RCC_MCO_DIV2                            ((uint8_t)(0x01U << SYSCTRL_MCO_DIV_Pos))
#define RCC_MCO_DIV8                            ((uint8_t)(0x02U << SYSCTRL_MCO_DIV_Pos))
#define RCC_MCO_DIV64                           ((uint8_t)(0x03U << SYSCTRL_MCO_DIV_Pos))
#define RCC_MCO_DIV128                          ((uint8_t)(0x04U << SYSCTRL_MCO_DIV_Pos))
#define RCC_MCO_DIV256                          ((uint8_t)(0x05U << SYSCTRL_MCO_DIV_Pos))
#define RCC_MCO_DIV512                          ((uint8_t)(0x06U << SYSCTRL_MCO_DIV_Pos))
#define RCC_MCO_DIV1024                         ((uint8_t)(0x07U << SYSCTRL_MCO_DIV_Pos))

#define IS_RCC_MCO_DIV(INSTANCE)                (((INSTANCE) == RCC_MCO_DIV1)   ||\
                                                 ((INSTANCE) == RCC_MCO_DIV2)   ||\
                                                 ((INSTANCE) == RCC_MCO_DIV8)   ||\
                                                 ((INSTANCE) == RCC_MCO_DIV64)  ||\
                                                 ((INSTANCE) == RCC_MCO_DIV128) ||\
                                                 ((INSTANCE) == RCC_MCO_DIV256) ||\
                                                 ((INSTANCE) == RCC_MCO_DIV512) ||\
                                                 ((INSTANCE) == RCC_MCO_DIV1024))

#define RCC_MCO_SRC_NONE                        (0x00U)
#define RCC_MCO_SRC_HCLK                        (0x01U)
#define RCC_MCO_SRC_PCLK                        (0x02U)
#define RCC_MCO_SRC_HSI                         (0x03U)
#define RCC_MCO_SRC_LSI                         (0x04U)
#define RCC_MCO_SRC_HSE                         (0x05U)
#define RCC_MCO_SRC_LSE                         (0x06U)
#define RCC_MCO_SRC_PLL                         (0x07U)
#define RCC_MCO_SRC_RC150K                      (0x08U)
#define RCC_MCO_SRC_RC10K                       (0x09U)

#define IS_RCC_MCO_SRC(INSTANCE)                (((INSTANCE) == RCC_MCO_SRC_NONE)   || \
                                                 ((INSTANCE) == RCC_MCO_SRC_HCLK)   || \
                                                 ((INSTANCE) == RCC_MCO_SRC_PCLK)   || \
                                                 ((INSTANCE) == RCC_MCO_SRC_HSI)    || \
                                                 ((INSTANCE) == RCC_MCO_SRC_LSI)    || \
                                                 ((INSTANCE) == RCC_MCO_SRC_HSE)    || \
                                                 ((INSTANCE) == RCC_MCO_SRC_LSE)    || \
                                                 ((INSTANCE) == RCC_MCO_SRC_PLL)    || \
                                                 ((INSTANCE) == RCC_MCO_SRC_RC150K) || \
                                                 ((INSTANCE) == RCC_MCO_SRC_RC10K))

#define RCC_TIMITR_BTIM1                        (0UL)
#define RCC_TIMITR_BTIM2                        (1UL)
#define RCC_TIMITR_BTIM3                        (2UL)
#define RCC_TIMITR_GTIM1                        (3UL)
#define RCC_TIMITR_GTIM2                        (4UL)
#define RCC_TIMITR_GTIM3                        (5UL)
#define RCC_TIMITR_GTIM4                        (6UL)
#define RCC_TIMITR_ATIM                         (7UL)

#define IS_RCC_TIMITR_SOURCE(SRC)               ((SRC) < 8)

//==================================================================================
extern void RCC_HCLKPRS_Config(uint32_t HCLKPRS);
extern void RCC_PCLKPRS_Config(uint32_t PCLKPRS);
extern void RCC_SYSCLKSRC_Config(uint32_t SYSCLKSRC);
extern void RCC_CCS_Config(uint32_t CCS, FunctionalState NewState);
extern void RCC_LSELOCK_Config(uint32_t LSELOCK);
extern void RCC_WAKEUPCLK_Config(uint32_t WAKEUPCLK);
extern void RCC_LOCKUP_Config(uint32_t LOCKUP);
extern void RCC_SWDIO_Config(uint32_t SWDIO);
extern int RCC_DeInit(void);
extern void RCC_SystemCoreClockUpdate(uint32_t NewFreq);
extern int RCC_HSI_Enable(uint32_t HSIDiv);
extern void RCC_HSI_Disable(void);
extern int RCC_LSI_Enable(void);
extern void RCC_LSI_Disable(void);
extern int RCC_HSE_Enable(uint32_t Mode, uint32_t FreqIn, uint8_t Driver, uint32_t Flt);
extern void RCC_HSE_Disable(void);
extern int RCC_LSE_Enable(uint32_t Mode, uint8_t Amp, uint8_t Driver);
extern void RCC_LSE_Disable(void);
extern int RCC_PLL_Enable(uint32_t PLLSource, uint32_t FreqIn, uint32_t PLLMul);
extern void RCC_PLL_Disable(void);
extern uint8_t RCC_SysClk_Switch(uint32_t NewClk);
extern void RCC_ITConfig(uint32_t RCC_IT, FunctionalState NewState);
extern ITStatus RCC_GetITStatus(uint32_t RCC_IT);
extern void RCC_ClearITPendingBit(uint32_t RCC_IT);
extern FlagStatus RCC_GetStableFlag(uint32_t RCC_STABLEFLAG);
extern uint32_t RCC_GetAllStableFlag(void);
extern void RCC_AHBPeriphClk_Enable(uint32_t Periph, FunctionalState NewState);
extern void RCC_APBPeriphClk_Enable1(uint32_t Periph, FunctionalState NewState);
extern void RCC_APBPeriphClk_Enable2(uint32_t Periph, FunctionalState NewState);
extern void RCC_AHBPeriphReset(uint32_t Periph, FunctionalState NewState);
extern void RCC_APBPeriphReset1(uint32_t Periph, FunctionalState NewState);
extern void RCC_APBPeriphReset2(uint32_t Periph, FunctionalState NewState);
extern FlagStatus RCC_GetRstFlag(uint32_t RCC_RSTFLAG);
extern uint32_t RCC_GetAllRstFlag(void);
extern void RCC_ClearRstFlag(uint32_t RCC_RSTFLAG);
extern void RCC_HCLK_OUT(void);
extern void RCC_PCLK_OUT(void);
extern void RCC_HSE_OUT(void);
extern void RCC_HSI_OUT(void);
extern void RCC_LSE_OUT(void);
extern void RCC_LSI_OUT(void);
extern void RCC_PLL_OUT(void);
extern void RCC_MCO_OUT(uint8_t Source, uint8_t Div);

extern uint32_t RCC_Sysctrl_GetHClkFreq(void);
extern uint32_t RCC_Sysctrl_GetPClkFreq(void);

void RCC_BTIM3ITRSelect(uint32_t Source);
void RCC_BTIM2ITRSelect(uint32_t Source);
void RCC_BTIM1ITRSelect(uint32_t Source);
void RCC_GTIM1ITRSelect(uint32_t Source);
void RCC_GTIM2ITRSelect(uint32_t Source);
void RCC_GTIM3ITRSelect(uint32_t Source);
void RCC_GTIM4ITRSelect(uint32_t Source);
void RCC_ATIMITRSelect(uint32_t Source);

#ifdef __cplusplus
}
#endif

#endif /* __CW32F030_RCC_H */
