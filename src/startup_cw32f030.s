/**
  ******************************************************************************
  * @file      startup_cw32f030_gcc.s
  * @author    akako
  * @brief     CW32F030xx devices vector table GCC toolchain.
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == Reset_Handler,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M0+ processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018-2021 Akako
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

.syntax unified
.cpu cortex-m0plus
.fpu softvfp
.thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval None
*/

  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0          /* set stack pointer */

/* Call the clock system initialization function.*/
  bl  SystemInit

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit

/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call static constructors */
  bl __libc_init_array
/* Call the application s entry point.*/
  bl main

LoopForever:
  b LoopForever

.size Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 *
 * @param  None
 * @retval None
*/
  .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler

/******************************************************************************
*
* The minimal vector table for a Cortex M0.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
  .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
  .word _estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVC_Handler
  .word 0
  .word 0
  .word PendSV_Handler
  .word SysTick_Handler

  .word WDT_IRQHandler            /* 0 Watch Dog Timer Interrupt Handler         */
  .word LVD_IRQHandler            /* 1 Low Voltage Detect Interrupt Handler      */
  .word RTC_IRQHandler            /* 2 Real Time Clock Interrupt Handler         */
  .word FLASHRAM_IRQHandler       /* 3 Flash/RAM Interrupt Handler               */
  .word RCC_IRQHandler            /* 4 RCC Interupt Handler                      */
  .word GPIOA_IRQHandler          /* 5 GPIOA Interrupt Handler                   */
  .word GPIOB_IRQHandler          /* 6 GPIOB Interrupt Handler                   */
  .word GPIOC_IRQHandler          /* 7 GPIOC Interrupt Handler                   */
  .word GPIOF_IRQHandler          /* 8 GPIOF Interrupt Handler                   */
  .word DMACH1_IRQHandler         /* 9 DMA Channel 1 Interrupt Handler           */
  .word DMACH23_IRQHandler        /* 10 DMA Channel 2/3 Interrupt Handler        */
  .word DMACH45_IRQHandler        /* 11 DMA Channel 4/5 Interrupt Handler        */
  .word ADC_IRQHandler            /* 12 ADC Interrupt Handler                    */
  .word ATIM_IRQHandler           /* 13 Advanced Timer Interrupt Handler         */
  .word VC1_IRQHandler            /* 14 Voltage Comparator 1 Interrupt Handler   */
  .word VC2_IRQHandler            /* 15 Voltage Comparator 2 Interrupt Handler   */
  .word GTIM1_IRQHandler          /* 16 General Timer1 Interrupt Handler         */
  .word GTIM2_IRQHandler          /* 17 General Timer2 Interrupt Handler         */
  .word GTIM3_IRQHandler          /* 18 General Timer3 Interrupt Handler         */
  .word GTIM4_IRQHandler          /* 19 General Timer4 Interrupt Handler         */
  .word BTIM1_IRQHandler          /* 20 Base Timer1 Interrupt Handler            */
  .word BTIM2_IRQHandler          /* 21 Base Timer2 Interrupt Handler            */
  .word BTIM3_IRQHandler          /* 22 Base Timer3 Interrupt Handler            */
  .word I2C1_IRQHandler           /* 23 I2C1 Interrupt Handler                   */
  .word I2C2_IRQHandler           /* 24 I2C2 Interrupt Handler                   */
  .word SPI1_IRQHandler           /* 25 SPI1 Interrupt Handler                   */
  .word SPI2_IRQHandler           /* 26 SPI2 Interrupt Handler                   */
  .word UART1_IRQHandler          /* 27 UART1 Interrupt Handler                  */
  .word UART2_IRQHandler          /* 28 UART2 Interrupt Handler                  */
  .word UART3_IRQHandler          /* 29 UART3 Interrupt Handler                  */
  .word AWT_IRQHandler            /* 30 Auto Wakeup Timer Handler                */
  .word FAULT_IRQHandler          /* 31 FAULT Interrupt Handler                  */

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

  .weak      NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak      HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak      SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak      PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak      SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak      WDT_IRQHandler
  .thumb_set WDT_IRQHandler,Default_Handler

  .weak      LVD_IRQHandler
  .thumb_set LVD_IRQHandler,Default_Handler

  .weak      RTC_IRQHandler
  .thumb_set RTC_IRQHandler,Default_Handler

  .weak      FLASHRAM_IRQHandler
  .thumb_set FLASHRAM_IRQHandler,Default_Handler

  .weak      RCC_IRQHandler
  .thumb_set RCC_IRQHandler,Default_Handler

  .weak      GPIOA_IRQHandler
  .thumb_set GPIOA_IRQHandler,Default_Handler

  .weak      GPIOB_IRQHandler
  .thumb_set GPIOB_IRQHandler,Default_Handler

  .weak      GPIOC_IRQHandler
  .thumb_set GPIOC_IRQHandler,Default_Handler

  .weak      GPIOF_IRQHandler
  .thumb_set GPIOF_IRQHandler,Default_Handler

  .weak      DMACH1_IRQHandler
  .thumb_set DMACH1_IRQHandler,Default_Handler

  .weak      DMACH23_IRQHandler
  .thumb_set DMACH23_IRQHandler,Default_Handler

  .weak      DMACH45_IRQHandler
  .thumb_set DMACH45_IRQHandler,Default_Handler

  .weak      ADC_IRQHandler
  .thumb_set ADC_IRQHandler,Default_Handler

  .weak      ATIM_IRQHandler
  .thumb_set ATIM_IRQHandler,Default_Handler

  .weak      VC1_IRQHandler
  .thumb_set VC1_IRQHandler,Default_Handler

  .weak      VC2_IRQHandler
  .thumb_set VC2_IRQHandler,Default_Handler

  .weak      GTIM1_IRQHandler
  .thumb_set GTIM1_IRQHandler,Default_Handler

  .weak      GTIM2_IRQHandler
  .thumb_set GTIM2_IRQHandler,Default_Handler

  .weak      GTIM3_IRQHandler
  .thumb_set GTIM3_IRQHandler,Default_Handler

  .weak      GTIM4_IRQHandler
  .thumb_set GTIM4_IRQHandler,Default_Handler

  .weak      BTIM1_IRQHandler
  .thumb_set BTIM1_IRQHandler,Default_Handler

  .weak      BTIM2_IRQHandler
  .thumb_set BTIM2_IRQHandler,Default_Handler

  .weak      BTIM3_IRQHandler
  .thumb_set BTIM3_IRQHandler,Default_Handler

  .weak      I2C1_IRQHandler
  .thumb_set I2C1_IRQHandler,Default_Handler

  .weak      I2C2_IRQHandler
  .thumb_set I2C2_IRQHandler,Default_Handler

  .weak      SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler

  .weak      SPI2_IRQHandler
  .thumb_set SPI2_IRQHandler,Default_Handler

  .weak      UART1_IRQHandler
  .thumb_set UART1_IRQHandler,Default_Handler

  .weak      UART2_IRQHandler
  .thumb_set UART2_IRQHandler,Default_Handler

  .weak      UART3_IRQHandler
  .thumb_set UART3_IRQHandler,Default_Handler

  .weak      AWT_IRQHandler
  .thumb_set AWT_IRQHandler,Default_Handler

  .weak      FAULT_IRQHandler
  .thumb_set FAULT_IRQHandler,Default_Handler

