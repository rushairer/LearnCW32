/**
 * @file cw32f030_flash.h
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
#ifndef __CW32F03x_FLASH_H__
#define __CW32F03x_FLASH_H__

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

/** @defgroup FLASH状态
  * @{
  */
#define FLASH_FLAG_OK                           (0UL)
#define FLASH_FLAG_BSY                          (bv5)  /*!< FLASH Busy flag */
#define FLASH_FLAG_PGERR                        (bv4)  /*!< FLASH Program error flag */
#define FLASH_FLAG_WRPRTERR                     (bv1)  /*!< FLASH Write protected error flag */
#define FLASH_FLAG_PCERR                        (bv0)  /*!< FLASH PC error flag */
#define FLASH_ERROR_ADDR                        0x80

/** @defgroup 读访问周期延时
  * @{
  */
#define FLASH_Latency_1                         ((uint32_t)0x00000000)  /*!< FLASH One Latency cycle */
#define FLASH_Latency_2                         ((uint32_t)0x00000001)  /*!< FLASH Two Latency cycles */
#define FLASH_Latency_3                         ((uint32_t)0x00000002)  /*!< FLASH THREE Latency cycles */
#define IS_FLASH_LATENCY(LATENCY)               (((LATENCY) == FLASH_Latency_1) || \
                                                 ((LATENCY) == FLASH_Latency_2) || \
                                                 ((LATENCY) == FLASH_Latency_3))

/** @defgroup FETCH开关
  * @{
  */
#define FLASH_Prefetch_Enable                   ((uint32_t)0x00000008)  /*!< FLASH Prefetch Enable */
#define FLASH_Prefetch_Disable                  ((uint32_t)0x00000000)  /*!< FLASH Prefetch Disable */
#define IS_FLASH_PREFETCH_STATE(STATE)          (((STATE) == FLASH_Prefetch_Enable) || \
                                                 ((STATE) == FLASH_Prefetch_Disable))

/** @defgroup CACHE开关
  * @{
  */
#define FLASH_Cache_Enable                      ((uint32_t)0x00000010)  /*!< FLASH Buffer Enable */
#define FLASH_Cache_Disable                     ((uint32_t)0x00000000)  /*!< FLASH Buffer Disable */
#define IS_FLASH_CACHE_STATE(STATE)             (((STATE) == FLASH_Cache_Enable) || \
                                                 ((STATE) == FLASH_Cache_Disable))

/** @defgroup 读保护等级
  * @{
  */
#define FLASH_RDLEVEL0                          ((uint16_t)0x00)
#define FLASH_RDLEVEL1                          ((uint16_t)0x01)
#define FLASH_RDLEVEL2                          ((uint16_t)0x02)
#define FLASH_RDLEVEL3                          ((uint16_t)0x03)
#define IS_FLASH_RDLEVEL(LEVEL)                 (((LEVEL) == FLASH_RDLEVEL0) || \
                                                 ((LEVEL) == FLASH_RDLEVEL1) || \
                                                 ((LEVEL) == FLASH_RDLEVEL2) || \
                                                 ((LEVEL) == FLASH_RDLEVEL3))

/** @defgroup 中断标志位
  * @{
  */
#define FLASH_IT_PROG                           (bv4)
#define FLASH_IT_PAGELOCK                       (bv1)
#define FLASH_IT_PC                             (bv0)
#define IS_FLASH_IT(IT)                         ((((IT) & 0xFFFFFFEC) == 0x0UL) && ((IT) != 0x0UL))
#define IS_FLASH_GET_IT(IT)                     (((IT) == FLASH_IT_PROG) || \
                                                 ((IT) == FLASH_IT_PAGELOCK) || \
                                                 ((IT) == FLASH_IT_PC))

/** @defgroup FLASH页
 * @{
 */
#define FLASH_WRProt_AllPages                   ((uint32_t)0x0000FFFF) /*!< Write protection of all Pages */
#define IS_FLASH_PAGE_Number(PAGENUMBER)        ((PAGENUMBER) <= 127)
#define IS_FLASH_ADDRESS(ADDRESS)               (((ADDRESS) >= 0x00000000) && ((ADDRESS) < 0x00010000))

//============================================================
//设置FLASH读访问周期
void FLASH_SetLatency(uint32_t FLASH_Latency);
//设置预取使能
void FLASH_PrefetchCmd(uint32_t FLASH_Prefetch);
//设置BUFFER使能
void FLASH_CacheCmd(uint32_t FLASH_Buffer);
//获取FLASH的Fetch状态
FlagStatus FLASH_GetPrefetchStatus(void);
//获取FLASH的Cache状态
FlagStatus FLASH_GetCacheStatus(void);
//获取FLASH的读保护等级
uint8_t FLASH_GetReadOutLevel(void);
//设置FLASH的读保护等级
void FLASH_SetReadOutLevel(uint16_t RdLevel);
//解锁FLASH所有页面
void FLASH_UnlockAllPages(void);
//锁定FLASH所有页面
void FLASH_LockAllPages(void);
//解锁FLASH指定页面：按照页面号解锁，0~127
uint8_t FLASH_UnlockPage(uint8_t Page_Number);
//解锁FLASH指定页面：按照起始和终止地址解锁
uint8_t FLASH_UnlockPages(uint32_t StartAddr, uint32_t EndAddr);
//擦除FLASH指定页面：按照页面号擦除，0~127
uint8_t FLASH_ErasePage(uint8_t Page_Number);
//擦除FLASH指定页面：按照起始和终止地址擦除
uint8_t FLASH_ErasePages(uint32_t StartAddr, uint32_t EndAddr);
//指定地址开始写一定长度的数据，按照字节写
uint8_t FLASH_WriteBytes(uint32_t WriteAddr, uint8_t *pWrBuf, uint16_t WrByteCnt);
//指定地址开始写一定长度的数据，按照半字写
uint8_t FLASH_WirteHalfWords(uint32_t WriteAddr, uint16_t *pWrBuf, uint16_t WrByteCnt);
//指定地址开始写一定长度的数据，按照字写
uint8_t FLASH_WriteWords(uint32_t WriteAddr, uint32_t *pWrBuf, uint16_t WrByteCnt);
//锁定FLASH指定页面：按照页面号锁定，0~127
uint8_t FLASH_LockPage(uint8_t Page_Number);
//锁定FLASH指定页面：按照起始和终止地址锁定
uint8_t FLASH_LockPages(uint32_t StartAddr, uint32_t EndAddr);
//FLASH指定中断使能配置
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);
//获取指定FLASH中断标志位
ITStatus FLASH_GetITStatus(uint32_t FLASH_IT);
//清除指定FLASH中断标志位
void FLASH_ClearITPendingBit(uint32_t FLASH_IT);
//获取FLASH模块当前状态//
uint32_t FLASH_GetStatus(void);

//============================================================

#ifdef __cplusplus
}
#endif

#endif
