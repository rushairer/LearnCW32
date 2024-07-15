/**
 * @file cw32f030_i2c.h
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-04-27
 *
 * @copyright Copyright (c) 2021
 * x
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
#ifndef __CW32F03x_I2C_H
#define __CW32F03x_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "cw32f030.h"
#include "base_types.h"
#include "cw32f030_rcc.h"

//I2C从设备地址，按照8 BIT设置，最低位0或者1均可。
#define I2C_SLAVEADDRESS 0xA0                   //读EEPROM时设置为0XA0，主从通信时设置为0x60

//主从通信时从机地址设置（在从程序中设置）
#define OwnSlaveAddress0 0x60                   //按照8位设置，最低位设置为0或者1,写入寄存器之前会自动右移一位，再写入寄存器高7位
#define OwnSlaveAddress1 0xb0                   //按照8位设置，最低位设置为0或者1,写入寄存器之前会自动右移一位，再写入寄存器高7位
#define OwnSlaveAddress2 0xfe                   //按照8位设置，最低位设置为0或者1,写入寄存器之前会自动右移一位，再写入寄存器高7位


/**
 * @brief  I2C通道选择
 *
 */
typedef enum en_i2c_channel
{
    I2C1 = 0,///<通道1
    I2C2 = 1,///<通道2
} en_i2c_channel_t;

/**
 ******************************************************************************
 ** \brief I2C初始化配置结构
 *****************************************************************************/
typedef struct
{
    FunctionalState I2C_BaudEn;           ///<波特率计数器使能
    uint8_t         I2C_Baud;             ///<波特率计数器配置
    uint8_t         I2C_OwnSlaveAddr0;    ///<从机地址0
    FunctionalState I2C_OwnGc;            ///<广播响应使能
    uint8_t         I2C_OwnSlaveAddr1;    ///<从机地址1
    uint8_t         I2C_OwnSlaveAddr2;    ///<从机地址2
    FunctionalState I2C_FLT;              ///<FLT配置
    FunctionalState I2C_AA;               ///<ACK配置
} I2C_InitTypeDef;

/** @defgroup I2C_Exported_Constants
 * @{
 */
#define IS_I2C_ALL_PERIPH(PERIPH)               (((PERIPH) == CW_I2C1) || \
                                                 ((PERIPH) == CW_I2C2))
#define IS_I2C_OWN_ADDRESS0(ADDRESS0)           ((ADDRESS0) <= 0x7F)
#define IS_I2C_OWN_ADDRESS1(ADDRESS1)           ((ADDRESS1) <= 0x7F)
#define IS_I2C_OWN_ADDRESS2(ADDRESS2)           ((ADDRESS2) <= 0x7F)

#define IS_I2C_Baud_BRR(PARA)                   ((PARA) <= 0xFF)

/** @defgroup I2C_transfer_direction
  * @{
  */

#define I2C_Direction_Transmitter               ((uint8_t)0x00)
#define I2C_Direction_Receiver                  ((uint8_t)0x01)
#define IS_I2C_DIRECTION(DIRECTION)             (((DIRECTION) == I2C_Direction_Transmitter) || \
                                                 ((DIRECTION) == I2C_Direction_Receiver))
//波特率生成器启停设置
void I2C_BaudGeneratorEnable(I2C_TypeDef *I2Cx, FunctionalState NewState);
//设置波特率配置寄存器
void I2C_SetBaud(I2C_TypeDef *I2Cx, uint8_t u8TBaud);
//发送START信号
void I2C_GenerateSTART(I2C_TypeDef *I2Cx, FunctionalState NewState);
//发送STOP信号
void I2C_GenerateSTOP(I2C_TypeDef *I2Cx, FunctionalState NewState);
//Ack信号配置
void I2C_AcknowledgeConfig(I2C_TypeDef *I2Cx, FunctionalState NewState);
//Filter配置
void I2C_FilterConfig(I2C_TypeDef *I2Cx, FunctionalState NewState);
//做从机时的从机地址0配置
void I2C_SetOwnSlaveAddress0(I2C_TypeDef *I2Cx, uint8_t I2CSlaveAddr);
//做从机时的从机地址1配置
void I2C_SetOwnSlaveAddress1(I2C_TypeDef *I2Cx, uint8_t I2CSlaveAddr);
//做从机时的从机地址2配置
void I2C_SetOwnSlaveAddress2(I2C_TypeDef *I2Cx, uint8_t I2CSlaveAddr);
//做从机时广播响应配置
void I2C_GcConfig(I2C_TypeDef *I2Cx, FunctionalState NewState);
//I2C模块使能
void I2C_Cmd(I2C_TypeDef *I2Cx, FunctionalState NewState);
//获取SI中断标志
ITStatus I2C_GetIrq(I2C_TypeDef *I2Cx);
//清除SI中断标志
void I2C_ClearIrq(I2C_TypeDef *I2Cx);
//获取状态寄存器
uint8_t I2C_GetState(I2C_TypeDef *I2Cx);
//I2C MASTER初始化
void I2C_Master_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct);
//I2C SLAVE初始化
void I2C_Slave_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct);
//I2C1关闭初始化
void I2C1_DeInit(void);
//I2C2关闭初始化
void I2C2_DeInit(void);
//发送1字节数据
void I2C_SendData(I2C_TypeDef *I2Cx, uint8_t Data);
//接收1字节数据
uint8_t I2C_ReceiveData(I2C_TypeDef *I2Cx);
//发送地址字节
void I2C_Send7bitAddress(I2C_TypeDef *I2Cx, uint8_t Address, uint8_t I2C_Direction);
//软复位I2C1模块
void I2C1_SoftwareResetCmd(FunctionalState NewState);
//软复位I2C2模块
void I2C2_SoftwareResetCmd(FunctionalState NewState);
//主写EEPROM函数
void I2C_MasterWriteEepromData(I2C_TypeDef *I2Cx, uint8_t u8Addr, uint8_t *pu8Data, uint32_t u32Len);
//主读EEPROM函数
void I2C_MasterReadEepomData(I2C_TypeDef *I2Cx, uint8_t u8Addr, uint8_t *pu8Data, uint32_t u32Len);
//主发送数据
void I2C_MasterSendDataToSlave(I2C_TypeDef *I2Cx, uint8_t *pu8Data, uint32_t u32Len);
//主接收数据
void I2C_MasterRecDataFromSlave(I2C_TypeDef *I2Cx, uint8_t *pu8Data, uint32_t u32Len);
//从发送数据
void I2C_SlaveSendDataToMaster(I2C_TypeDef *I2Cx, uint8_t *pu8Data, uint32_t *u32Len);
//从接收数据
void I2C_SlaveRecDataFromMaster(I2C_TypeDef *I2Cx, uint8_t *pu8Data, uint32_t *pu32Len);
//从机状态检测
uint8_t I2C_MasterCheckSlaveBusy(I2C_TypeDef *I2Cx);

#ifdef __cplusplus
}
#endif

#endif /*__CW32F030_I2C_H */
