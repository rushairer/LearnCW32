
;/*****************************************************************************/
;/*  Startup for ARM                                                          */
;/*  Version     V1.0                                                         */
;/*  Date        2021-03-12                                                   */
;/*  Target-mcu  {MCU_PN_H}                                                   */
;/*****************************************************************************/

; Stack Configuration
; Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; Heap Configuration
;  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors
                DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ;< -15 Reset Vector, invoked on Power up and warm reset
                DCD     NMI_Handler               ;< -14 Non maskable Interrupt, cannot be stopped or preempted
                DCD     HardFault_Handler         ;< -13 Hard Fault, all classes of Fault
                DCD     0                         ;< -12 Reserved
                DCD     0                         ;< -11 Reserved
                DCD     0                         ;< -10 Reserved
                DCD     0                         ;< -9 Reserved
                DCD     0                         ;< -8 Reserved
                DCD     0                         ;< -7 Reserved
                DCD     0                         ;< -6 Reserved
                DCD     SVC_Handler               ;< -5 System Service Call via SVC instruction
                DCD     0                         ;< -4 Reserved
                DCD     0                         ;< -3 Reserved
                DCD     PendSV_Handler            ;< -2 Pendable request for system service
                DCD     SysTick_Handler           ;< -1 System Tick Timer

                DCD     WDT_IRQHandler            ;< 0 Watch Dog Timer Interrupt Handler
                DCD     LVD_IRQHandler            ;< 1 Low Voltage Detect Interrupt Handler
                DCD     RTC_IRQHandler            ;< 2 Real Time Clock Interrupt Handler
                DCD     FLASHRAM_IRQHandler       ;< 3 Flash/RAM Interrupt Handler
                DCD     RCC_IRQHandler            ;< 4 RCC Interupt Handler
                DCD     GPIOA_IRQHandler          ;< 5 GPIOA Interrupt Handler
                DCD     GPIOB_IRQHandler          ;< 6 GPIOB Interrupt Handler
                DCD     GPIOC_IRQHandler          ;< 7 GPIOC Interrupt Handler
                DCD     GPIOF_IRQHandler          ;< 8 GPIOF Interrupt Handler
                DCD     DMACH1_IRQHandler         ;< 9 DMA Channel 1 Interrupt Handler
                DCD     DMACH23_IRQHandler        ;< 10 DMA Channel 2/3 Interrupt Handler
                DCD     DMACH45_IRQHandler        ;< 11 DMA Channel 4/5 Interrupt Handler
                DCD     ADC_IRQHandler            ;< 12 ADC Interrupt Handler
                DCD     ATIM_IRQHandler           ;< 13 Advanced Timer Interrupt Handler
                DCD     VC1_IRQHandler            ;< 14 Voltage Comparator 1 Interrupt Handler
                DCD     VC2_IRQHandler            ;< 15 Voltage Comparator 2 Interrupt Handler
                DCD     GTIM1_IRQHandler          ;< 16 General Timer1 Interrupt Handler
                DCD     GTIM2_IRQHandler          ;< 17 General Timer2 Interrupt Handler
                DCD     GTIM3_IRQHandler          ;< 18 General Timer3 Interrupt Handler
                DCD     GTIM4_IRQHandler          ;< 19 General Timer4 Interrupt Handler
                DCD     BTIM1_IRQHandler          ;< 20 Base Timer1 Interrupt Handler
                DCD     BTIM2_IRQHandler          ;< 21 Base Timer2 Interrupt Handler
                DCD     BTIM3_IRQHandler          ;< 22 Base Timer3 Interrupt Handler
                DCD     I2C1_IRQHandler           ;< 23 I2C1 Interrupt Handler
                DCD     I2C2_IRQHandler           ;< 24 I2C2 Interrupt Handler
                DCD     SPI1_IRQHandler           ;< 25 SPI1 Interrupt Handler
                DCD     SPI2_IRQHandler           ;< 26 SPI2 Interrupt Handler
                DCD     UART1_IRQHandler          ;< 27 UART1 Interrupt Handler
                DCD     UART2_IRQHandler          ;< 28 UART2 Interrupt Handler
                DCD     UART3_IRQHandler          ;< 29 UART3 Interrupt Handler
                DCD     AWT_IRQHandler            ;< 30 Auto Wakeup Timer Handler
                DCD     FAULT_IRQHandler          ;< 31 FAULT Interrupt Handler



__Vectors_End

__Vectors_Size 	EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main

                LDR     R1, =0x0
                LDR     R0, [R1]
                MOV     SP, R0

                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP


HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT  WDT_IRQHandler           [WEAK]
                EXPORT  LVD_IRQHandler           [WEAK]
                EXPORT  RTC_IRQHandler           [WEAK]
                EXPORT  FLASHRAM_IRQHandler      [WEAK]
                EXPORT  RCC_IRQHandler           [WEAK]
                EXPORT  GPIOA_IRQHandler         [WEAK]
                EXPORT  GPIOB_IRQHandler         [WEAK]
                EXPORT  GPIOC_IRQHandler         [WEAK]
                EXPORT  GPIOF_IRQHandler         [WEAK]
                EXPORT  DMACH1_IRQHandler        [WEAK]
                EXPORT  DMACH23_IRQHandler       [WEAK]
                EXPORT  DMACH45_IRQHandler       [WEAK]
                EXPORT  ADC_IRQHandler           [WEAK]
                EXPORT  ATIM_IRQHandler          [WEAK]
                EXPORT  VC1_IRQHandler           [WEAK]
                EXPORT  VC2_IRQHandler           [WEAK]
                EXPORT  GTIM1_IRQHandler         [WEAK]
                EXPORT  GTIM2_IRQHandler         [WEAK]
                EXPORT  GTIM3_IRQHandler         [WEAK]
                EXPORT  GTIM4_IRQHandler         [WEAK]
                EXPORT  BTIM1_IRQHandler         [WEAK]
                EXPORT  BTIM2_IRQHandler         [WEAK]
                EXPORT  BTIM3_IRQHandler         [WEAK]
                EXPORT  I2C1_IRQHandler          [WEAK]
                EXPORT  I2C2_IRQHandler          [WEAK]
                EXPORT  SPI1_IRQHandler          [WEAK]
                EXPORT  SPI2_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler         [WEAK]
                EXPORT  UART2_IRQHandler         [WEAK]
                EXPORT  UART3_IRQHandler         [WEAK]
                EXPORT  AWT_IRQHandler           [WEAK]
                EXPORT  FAULT_IRQHandler         [WEAK]

WDT_IRQHandler
LVD_IRQHandler
RTC_IRQHandler
FLASHRAM_IRQHandler
RCC_IRQHandler
GPIOA_IRQHandler
GPIOB_IRQHandler
GPIOC_IRQHandler
GPIOF_IRQHandler
DMACH1_IRQHandler
DMACH23_IRQHandler
DMACH45_IRQHandler
ADC_IRQHandler
ATIM_IRQHandler
VC1_IRQHandler
VC2_IRQHandler
GTIM1_IRQHandler
GTIM2_IRQHandler
GTIM3_IRQHandler
GTIM4_IRQHandler
BTIM1_IRQHandler
BTIM2_IRQHandler
BTIM3_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
AWT_IRQHandler
FAULT_IRQHandler


               B .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
