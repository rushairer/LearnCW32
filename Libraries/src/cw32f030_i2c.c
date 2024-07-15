/**
 * @file cw32f030_i2c.c
 * @author WHXY
 * @brief
 * @version 0.1
 * @date 2021-04-27
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
#include "cw32f030_i2c.h"

/* Private_TypesDefinitions --------------------------------------------------*/

/* Private_Defines -----------------------------------------------------------*/

/* Private_Variables ---------------------------------------------------------*/

/* Private_FunctionPrototypes ------------------------------------------------*/

/* Private_Functions ---------------------------------------------------------*/

/* Public_Functions ----------------------------------------------------------*/

/**
 * @brief I2C 波特率发生器使能
 *
 * @param I2Cx      : I2C1  I2C2
 * @param NewState  : ENABLE  DISABLE
 */
void I2C_BaudGeneratorEnable(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Peripheral under reset */
        I2Cx->BRREN_f.EN = 1;
    }
    else
    {
        /* Peripheral not under reset */
        I2Cx->BRREN_f.EN = 0;
    }
}

/**
 * @brief  I2C：设置波特率计数器配置寄存器函数
 *
 * @param I2Cx      : I2C1  I2C2
 * @param u8TBaud   : 设置值= fPCLK/(8*fSCL) - 1
 *                  : 设置值需要根据fPCLK和fSCL计算
 */
void I2C_SetBaud(I2C_TypeDef *I2Cx, uint8_t u8TBaud)
{
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_Baud_BRR(u8TBaud));
    I2Cx->BRR = u8TBaud;
}

/**
 * @brief 发送START信号
 *
 * @param I2Cx      : I2C1  I2C2
 * @param NewState  : ENABLE  DISABLE
 */
void I2C_GenerateSTART(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Generate a START condition */
        if (I2Cx->STAT != 0xF8)
        {
            I2Cx->CR_f.STA = 1;  //set start
            I2Cx->CR_f.SI = 0;    //clear si
        }
        else
        {
            I2Cx->CR_f.STA = 1;  //set start
        }
        while ((I2Cx->CR & bv3) == 0x00);   //已产生0X08状态
        I2Cx->CR_f.STA = 0;  //clear start
    }
    else
    {
        /* Disable the START condition generation */
        I2Cx->CR_f.STA = 0;
    }
}

/**
 * @brief 发送STOP信号
 *
 * @param I2Cx       : I2C1  I2C2
 * @param NewState   : ENABLE  DISABLE
 */
void I2C_GenerateSTOP(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Generate a STOP condition */
        I2Cx->CR_f.STO = 1;
    }
    else
    {
        /* Disable the STOP condition generation */
        I2Cx->CR_f.STO = 0;
    }
}

/**
 * @brief ACK应答配置
 *
 * @param I2Cx      : I2C1  I2C2
 * @param NewState  : ENABLE  DISABLE
 */
void I2C_AcknowledgeConfig(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the acknowledgement */
        I2Cx->CR_f.AA = 1;
    }
    else
    {
        /* Disable the acknowledgement */
        I2Cx->CR_f.AA = 0;
    }
}

/**
 * @brief 滤波器配置
 *
 * @param I2Cx      : I2C1  I2C2
 * @param NewState  : ENABLE  DISABLE
 * 作为主机时，如果BRR的值小于或等于9，则I2Cx_CR.FLT设置为ENABLE；
 * 如果BRR的值大于9，则 I2Cx_CR.FLT为DISABLE；
 *
 * 作从机时，如果PCLK与SCL的频率比值小于或等于40，则I2Cx_CR.FLT设置为ENABLE；
 * 如果PCLK与SCL的频率比值大于40，则I2Cx_CR.FLT设置为DISABLE；
 */
void I2C_FilterConfig(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Peripheral under reset */
        I2Cx->CR_f.FLT = 1;
    }
    else
    {
        /* Peripheral not under reset */
        I2Cx->CR_f.FLT = 0;
    }
}

/**
 * @brief 做从机时的I2C地址0配置
 *
 * @param I2Cx          : I2C1  I2C2
 * @param I2CSlaveAddr  ：不能全0，可设置范围为0x01 - 0x7F
 */
void I2C_SetOwnSlaveAddress0(I2C_TypeDef *I2Cx, uint8_t I2CSlaveAddr)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Get the old register value */
    I2Cx->ADDR0_f.ADDR0 = (I2CSlaveAddr >> 1);
}

/**
 * @brief 做从机时的I2C地址1配置
 *
 * @param I2Cx            : I2C1  I2C2
 * @param I2CSlaveAddr    ：不能全0，可设置范围为0x01 - 0x7F
 */
void I2C_SetOwnSlaveAddress1(I2C_TypeDef *I2Cx, uint8_t I2CSlaveAddr)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Get the old register value */
    I2Cx->ADDR1_f.ADDR1 = (I2CSlaveAddr >> 1);
}

/**
 * @brief 做从机时的I2C地址2配置
 *
 * @param I2Cx           : I2C1  I2C2
 * @param I2CSlaveAddr   ：不能全0，可设置范围为0x01 - 0x7F
 */
void I2C_SetOwnSlaveAddress2(I2C_TypeDef *I2Cx, uint8_t I2CSlaveAddr)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Get the old register value */
    I2Cx->ADDR2_f.ADDR2 = (I2CSlaveAddr >> 1);
}

/**
 * @brief  广播地址响应位配置
 *
 * @param I2Cx      : I2C1  I2C2
 * @param NewState  : ENABLE  DISABLE
 */
void I2C_GcConfig(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* 允许响应广播 */
        I2Cx->ADDR0_f.GC = 1;
    }
    else
    {
        /* 禁止响应广播 */
        I2Cx->ADDR0_f.GC = 0;
    }
}

/**
 * @brief I2C模块使能控制
 *
 * @param I2Cx      : I2C1  I2C2
 * @param NewState  : ENABLE  DISABLE
 */
void I2C_Cmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected I2C peripheral */
        I2Cx->CR_f.EN = 1;
    }
    else
    {
        /* Disable the selected I2C peripheral */
        I2Cx->CR_f.EN = 0;
    }
}

/**
 * @brief I2C：获取中断标志位函数
 *
 * @param I2Cx        : I2C1  I2C2
 * @return ITStatus  : 为0表示无中断标志(SI = 0)，为1则为有中断标志(SI = 1)
 */
ITStatus I2C_GetIrq(I2C_TypeDef *I2Cx)
{
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    return (I2Cx->CR & bv3) ? SET : RESET;
}

/**
 * @brief I2C：清除中断标志位函数
 *
 * @param I2Cx   : I2C1  I2C2
 */
void I2C_ClearIrq(I2C_TypeDef *I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    I2Cx->CR_f.SI = 0;
}

/**
 * @brief I2C：读取状态寄存器函数
 *
 * @param I2Cx      : I2C1  I2C2
 * @return uint8_t  : 26种返回值，含义在不同模式下不同
 *
 */
uint8_t I2C_GetState(I2C_TypeDef *I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    return ((uint8_t)(I2Cx->STAT));
}

/**
 * @brief I2C:MASTER初始化函数
 *
 * @param I2Cx      : I2C1  I2C2
 * @param I2C_InitStruct
 */
void I2C_Master_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct)
{
    I2C_SetBaud(I2Cx, I2C_InitStruct->I2C_Baud);
    I2C_BaudGeneratorEnable(I2Cx, I2C_InitStruct->I2C_BaudEn);
    I2C_FilterConfig(I2Cx, I2C_InitStruct->I2C_FLT);
    I2C_AcknowledgeConfig(I2Cx, I2C_InitStruct->I2C_AA);
    if (I2C_InitStruct->I2C_Baud <= 9)
    {
        I2C_FilterConfig(I2Cx, ENABLE);
    }
}

/**
 * @brief I2C:SLAVE初始化函数
 *
 * @param I2Cx      : I2C1  I2C2
 * @param I2C_InitStruct
 */
void I2C_Slave_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct)
{
    I2C_FilterConfig(I2Cx, ENABLE);
    I2C_AcknowledgeConfig(I2Cx, I2C_InitStruct->I2C_AA);
    I2C_SetOwnSlaveAddress0(I2Cx, I2C_InitStruct->I2C_OwnSlaveAddr0);
    I2C_GcConfig(I2Cx, I2C_InitStruct->I2C_OwnGc);
    I2C_SetOwnSlaveAddress1(I2Cx, I2C_InitStruct->I2C_OwnSlaveAddr1);
    I2C_SetOwnSlaveAddress2(I2Cx, I2C_InitStruct->I2C_OwnSlaveAddr2);
}

/**
 * @brief I2C1 关闭初始化
 *
 */
void I2C1_DeInit(void)
{
    CW_SYSCTRL->APBRST1_f.I2C1 = 0;
    CW_SYSCTRL->APBRST1_f.I2C1 = 1;
    CW_I2C1->CR = 0x00;
}

/**
 * @brief I2C2 关闭初始化
 *
 */
void I2C2_DeInit(void)
{
    CW_SYSCTRL->APBRST1_f.I2C2 = 0;
    CW_SYSCTRL->APBRST1_f.I2C2 = 1;
    CW_I2C2->CR = 0x00;
}

/**
 * @brief 发送1字节数据
 *
 * @param I2Cx    : I2C1  I2C2
 * @param Data    : 0x00 - 0xFF
 */
void I2C_SendData(I2C_TypeDef *I2Cx, uint8_t Data)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Write in the DR register the data to be sent */
    I2Cx->DR = Data;
}

/**
 * @brief 接收1字节数据
 *
 * @param I2Cx      : I2C1  I2C2
 * @return uint8_t  : 0x00 - 0xFF
 */
uint8_t I2C_ReceiveData(I2C_TypeDef *I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Return the data in the DR register */
    return (uint8_t)I2Cx->DR;
}

/**
 * @brief 做主时发送从机地址字节
 *
 * @param I2Cx           : I2C1  I2C2
 * @param Address        : 按照8BIT设置，最低bit为0或者1均可以
 * @param I2C_Direction  : I2C_Direction_Transmitter  I2C_Direction_Receiver
 */
void I2C_Send7bitAddress(I2C_TypeDef *I2Cx, uint8_t Address, uint8_t I2C_Direction)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_DIRECTION(I2C_Direction));
    /* Test on the direction to set/reset the read/write bit */
    if (I2C_Direction != I2C_Direction_Transmitter)
    {
        /* Set the address bit0 for read */
        Address |= 0x01;
    }
    else
    {
        /* Reset the address bit0 for write */
        Address &= 0xfe;
    }
    /* Send the address */
    I2Cx->DR = Address;
}

/**
 * @brief 软复位I2C1
 *
 * @param NewState   : ENABLE  DISABLE
 */
void I2C1_SoftwareResetCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Peripheral under reset */
        CW_SYSCTRL->APBRST1_f.I2C1 = 1;
    }
    else
    {
        /* Peripheral not under reset */
        CW_SYSCTRL->APBRST1_f.I2C1 = 0;
    }
}

/**
 * @brief 软复位I2C2
 *
 * @param NewState   : ENABLE  DISABLE
 */
void I2C2_SoftwareResetCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Peripheral under reset */
        CW_SYSCTRL->APBRST1_f.I2C2 = 1;
    }
    else
    {
        /* Peripheral not under reset */
        CW_SYSCTRL->APBRST1_f.I2C2 = 0;
    }
}

/**
 ******************************************************************************
 * @brief  主机接收函数，适用读取EEPROM方式采用随机读取方式：需要先写入EEPROM的地址
 *
 * @param I2Cx           : I2C1  I2C2
 * @param u8Addr         : 读取EEPROM内存器地址
 * @param pu8Data        : 读取到的EEPROM的数据地址
 * @param u32Len         : 读取到的EEPROM的数据长度
 *
 ******************************************************************************/
void I2C_MasterReadEepomData(I2C_TypeDef *I2Cx, uint8_t u8Addr, uint8_t *pu8Data, uint32_t u32Len)
{
    uint8_t u8i = 0, u8State;
    I2C_GenerateSTART(I2Cx, ENABLE);
    while (1)
    {
        while (0 == I2C_GetIrq(I2Cx))
        {}
        u8State = I2C_GetState(I2Cx);
        switch (u8State)
        {
            case 0x08:   //发送完START信号
                I2C_GenerateSTART(I2Cx, DISABLE);
                I2C_Send7bitAddress(I2Cx, I2C_SLAVEADDRESS, 0X00);  //发送从机地址
                break;
            case 0x18:    //发送完SLA+W/R字节
                I2C_SendData(I2Cx, u8Addr);
                break;
            case 0x28:   //发送完1字节数据：发送EEPROM中memory地址也会产生，发送后面的数据也会产生
                I2Cx->CR_f.STA = 1;  //set start        //发送重复START信号,START生成函数改写后，会导致0X10状态被略过，故此处不调用函数
                break;
            case 0x10:   //发送完重复起始信号
                I2C_GenerateSTART(I2Cx, DISABLE);
                I2C_Send7bitAddress(I2Cx, I2C_SLAVEADDRESS, 0X01);
                break;
            case 0x40:   //发送完SLA+R信号，开始接收数据
                if (u32Len > 1)
                {
                    I2C_AcknowledgeConfig(I2Cx, ENABLE);
                }
                break;
            case 0x50:   //接收完一字节数据，在接收最后1字节数据之前设置AA=0;
                pu8Data[u8i++] = I2C_ReceiveData(I2Cx);
                if (u8i == u32Len - 1)
                {
                    I2C_AcknowledgeConfig(I2Cx, DISABLE);
                }
                break;
            case 0x58:   //接收到一个数据字节，且NACK已回复
                pu8Data[u8i++] = I2C_ReceiveData(I2Cx);
                I2C_GenerateSTOP(I2Cx, ENABLE);
                break;
            case 0x38:   //主机在发送 SLA+W 阶段或者发送数据阶段丢失仲裁  或者  主机在发送 SLA+R 阶段或者回应 NACK 阶段丢失仲裁
                I2C_GenerateSTART(I2Cx, ENABLE);
                break;
            case 0x48:   //发送完SLA+R后从机返回NACK
                I2C_GenerateSTOP(I2Cx, ENABLE);
                I2C_GenerateSTART(I2Cx, ENABLE);
                break;
            default:
                I2C_GenerateSTART(I2Cx, ENABLE);//其他错误状态，重新发送起始条件
                break;
        }
        I2C_ClearIrq(I2Cx);
        if (u8i == u32Len)
        {
            break;
        }
    }
}

/**
 ******************************************************************************
 * @brief  主机发送函数，适用读取EEPROM方式采用随机读取方式：需要先写入EEPROM的地址
 *
 * @param I2Cx           : I2C1  I2C2
 * @param u8Addr         : 写入EEPROM内存器地址
 * @param pu8Data        : 写入数据存放地址
 * @param u32Len         : 写入数据长度
 *
 ******************************************************************************/

void I2C_MasterWriteEepromData(I2C_TypeDef *I2Cx, uint8_t u8Addr, uint8_t *pu8Data, uint32_t u32Len)
{
    uint8_t u8i = 0, u8State;
    I2C_GenerateSTART(I2Cx, ENABLE);
    while (1)
    {
        while (0 == I2C_GetIrq(I2Cx))
        {;}
        u8State = I2C_GetState(I2Cx);
        switch (u8State)
        {
            case 0x08:   //发送完START信号
                I2C_GenerateSTART(I2Cx, DISABLE);
                I2C_Send7bitAddress(I2Cx, I2C_SLAVEADDRESS, 0X00); //从设备地址发送
                break;
            case 0x18:   //发送完SLA+W信号,ACK已收到
                I2C_SendData(I2Cx, u8Addr); //从设备内存地址发送
                break;
            case 0x28:   //发送完1字节数据：发送EEPROM中memory地址也会产生，发送后面的数据也会产生
                I2C_SendData(I2Cx, pu8Data[u8i++]);
                break;
            case 0x20:   //发送完SLA+W后从机返回NACK
            case 0x38:    //主机在发送 SLA+W 阶段或者发送数据阶段丢失仲裁  或者  主机在发送 SLA+R 阶段或者回应 NACK 阶段丢失仲裁
                I2C_GenerateSTART(I2Cx, ENABLE);
                break;
            case 0x30:   //发送完一个数据字节后从机返回NACK
                I2C_GenerateSTOP(I2Cx, ENABLE);
                break;
            default:
                break;
        }
        if (u8i > u32Len)
        {
            I2C_GenerateSTOP(I2Cx, ENABLE);//此顺序不能调换，出停止条件
            I2C_ClearIrq(I2Cx);
            break;
        }
        I2C_ClearIrq(I2Cx);
    }
}

/**
 ******************************************************************************
 * @brief  主机接收函数，适用MCU之间进行主从通信
 *
 * @param I2Cx           : I2C1  I2C2
 * @param pu8Data        : 接收数据存放地址
 * @param u32Len         : 接收数据长度
 *
 ******************************************************************************/
void I2C_MasterRecDataFromSlave(I2C_TypeDef *I2Cx, uint8_t *pu8Data, uint32_t u32Len)
{
    uint8_t u8i = 0, u8State;
    I2C_GenerateSTART(I2Cx, ENABLE);
    while (1)
    {
        while (0 == I2C_GetIrq(I2Cx))
        {}
        u8State = I2C_GetState(I2Cx);
        switch (u8State)
        {
            case 0x08:   //发送完START信号
            case 0x10:   //发送完重复起始信号
                I2C_GenerateSTART(I2Cx, DISABLE);
                I2C_Send7bitAddress(I2Cx, I2C_SLAVEADDRESS, 0X01);  //发送从机地址+R字节
                break;
            case 0x40:   //发送完SLA+R信号，开始接收数据
                if (u32Len > 1)
                {
                    I2C_AcknowledgeConfig(I2Cx, ENABLE);
                }
                break;
            case 0x50:   //接收完一字节数据，在接收最后1字节数据之前设置AA=0;
                pu8Data[u8i++] = I2C_ReceiveData(I2Cx);
                if (u8i == u32Len - 1)
                {
                    I2C_AcknowledgeConfig(I2Cx, DISABLE);
                }
                break;
            case 0x58:   //接收到一个数据字节，且NACK已回复
                pu8Data[u8i++] = I2C_ReceiveData(I2Cx);
                I2C_GenerateSTOP(I2Cx, ENABLE);
                break;
            case 0x38:   //主机在发送 SLA+W 阶段或者发送数据阶段丢失仲裁  或者  主机在发送 SLA+R 阶段或者回应 NACK 阶段丢失仲裁
                I2C_GenerateSTART(I2Cx, ENABLE);
                break;
            case 0x48:   //发送完SLA+R后从机返回NACK
                I2C_GenerateSTOP(I2Cx, ENABLE);
                I2C_GenerateSTART(I2Cx, ENABLE);
                break;
            default:
                I2C_GenerateSTART(I2Cx, ENABLE);//其他错误状态，重新发送起始条件
                break;
        }
        I2C_ClearIrq(I2Cx);
        if (u8i == u32Len)
        {
            break;
        }
    }
}

/**
 ******************************************************************************
 * @brief  主机发送函数，适用MCU之间进行主从通信
 *
 * @param I2Cx           : I2C1  I2C2
 * @param pu8Data        : 发送数据存放地址
 * @param u32Len         : 发送数据长度
 *
 ******************************************************************************/
void I2C_MasterSendDataToSlave(I2C_TypeDef *I2Cx, uint8_t *pu8Data, uint32_t u32Len)
{
    uint8_t u8i = 1;
    uint8_t u8State;
    I2C_GenerateSTART(I2Cx, ENABLE);
    while (1)
    {
     
        while (0 == I2C_GetIrq(I2Cx))
        {;}
LOOP1:
        u8State = I2C_GetState(I2Cx);
        
        switch (u8State)
        {
            case 0x08:   //发送完START信号
                I2C_GenerateSTART(I2Cx, DISABLE);
                I2C_Send7bitAddress(I2Cx, I2C_SLAVEADDRESS, 0X00); //从设备地址+W发送
                break;
            case 0x18:   //发送完SLA+W信号
                I2C_SendData(I2Cx, pu8Data[u8i - 1]);
                u8i++;
                break;            
            case 0x28:   //发送完1字节数据：发送EEPROM中memory地址也会产生，发送后面的数据也会产生
START:
                I2C_SendData(I2Cx, pu8Data[u8i - 1]);
                while (0 == I2C_GetIrq(I2Cx));                
                I2C_GenerateSTOP(I2Cx, ENABLE);               
                u8i++;
                I2C_ClearIrq(I2Cx);
                goto LOOP1;
                break;
            case 0x20:   //发送完SLA+W后从机返回NACK
            case 0x38:   //主机在发送 SLA+W 阶段或者发送数据阶段丢失仲裁  或者  主机在发送 SLA+R 阶段或者回应 NACK 阶段丢失仲裁
                I2C_GenerateSTART(I2Cx, ENABLE);
                break;
            case 0x30:   //发送完一个数据字节后从机返回NACK
                I2C_GenerateSTOP(I2Cx, ENABLE);
                break;
            case 0xF8:
//                I2C_GenerateSTART(I2Cx, ENABLE);
            goto START;
                
            default:
                break;
        }
        if (u8i > u32Len)
        {
            I2C_GenerateSTOP(I2Cx, ENABLE);//此顺序不能调换，出停止条件
            I2C_ClearIrq(I2Cx);
            break;
        }
        I2C_ClearIrq(I2Cx);
        
    }
}


/**
 * @brief 从机发送函数，适用MCU之间进行主从通信
 *
 * @param I2Cx           : I2C1  I2C2
 * @param pu8Data        : 发送数据存放地址
 * @param u32Len         : 发送数据长度
 */
void I2C_SlaveSendDataToMaster(I2C_TypeDef *I2Cx, uint8_t *pu8Data, uint32_t *u32Len)
{
    uint8_t u8i = 0, u8State;
    while (1)
    {
        while (0 == I2C_GetIrq(I2Cx))
        {}
        u8State = I2C_GetState(I2Cx);
        switch (u8State)
        {
            case 0xA8:   //接收到SLA+R,ACK已回应
            case 0xB0:   //主机丢失仲裁后被转从机并被SLA+R寻址，ACK已回应
                I2C_SendData(I2Cx, pu8Data[u8i++]);
                break;
            case 0xB8:   //从机已发送1字节数据，ACK已收到
                I2C_SendData(I2Cx, pu8Data[u8i++]);
                break;
            case 0xC8:    //从机最后一个数据字节已被发送(发送前自身AA被设置为0)，并已接收到ACK
            //                I2C_SendData(I2Cx,pu8Data[u8i++]);   //不需要发
            //                break;
            case 0xC0:    //已发送数据字节，已接收 NACK
                *u32Len = u8i;
                break;
            default:
                break;
        }
        I2C_ClearIrq(I2Cx);
        if ((0xC0 == u8State) || (0xC8 == u8State))
        {
            break;
        }
    }
}

/**
 * @brief 从机接收函数，适用MCU之间进行主从通信
 *
 * @param I2Cx           : I2C1  I2C2
 * @param pu8Data        : 接收数据存放地址
 * @param u32Len         : 接收数据长度
 */
void I2C_SlaveRecDataFromMaster(I2C_TypeDef *I2Cx, uint8_t *pu8Data, uint32_t *pu32Len)
{
    uint8_t u8i = 0, u8State;
    while (1)
    {
        while (0 == I2C_GetIrq(I2Cx))
        {}
        u8State = I2C_GetState(I2Cx);
        switch (u8State)
        {
            case 0x60:   //接收到SLA+W，ACK已回应
            case 0x68:   //主机丢失仲裁后被SLA+W寻址，ACK已回应
            case 0x70:   //接收到SLA（广播地址）+W，ACK已回应
            case 0x78:   //主机丢失仲裁后被SLA（广播地址）+W寻址，ACK已回应
                break;
            case 0x80:   //从机已接收到1字节数据，ACK已回复
            case 0x90:   //从机已接收到1字节广播数据，ACK已回复
            case 0x88:   //从机已接收到1字节数据，NACK已回应
            case 0x98:   //从机已接收到1字节广播数据，NACK已回应
                pu8Data[u8i++] = I2C_ReceiveData(I2Cx);
                break;
            case 0xA0:  //重复START信号或者STOP信号已收到
                *pu32Len = u8i;
                break;
            default:
                break;
        }
        I2C_ClearIrq(I2Cx);
        if (0xA0 == u8State)
        {
            break;
        }
    }
}

