

#ifndef __SYSTEM_PS030_H
#define __SYSTEM_PS030_H

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include <stdint.h>
#include "base_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/* Global pre-processor symbols/macros ('define')                             */
/******************************************************************************/
#define HWWD_DISABLE        (1)

/**
 ******************************************************************************
 ** \brief Clock Setup macro definition
 **
 ** - 0: CLOCK_SETTING_NONE  - User provides own clock setting in application
 ** - 1: CLOCK_SETTING_CMSIS -
 ******************************************************************************/
#define CLOCK_SETTING_NONE  0u
#define CLOCK_SETTING_CMSIS 1u


/******************************************************************************/
/*                                                                            */
/*                      START OF USER SETTINGS HERE                           */
/*                      ===========================                           */
/*                                                                            */
/*                 All lines with '<<<' can be set by user.                   */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/* Global function prototypes ('extern', definition in C source)              */
/******************************************************************************/


extern uint32_t SystemCoreClock;          // System Clock Frequency (Core Clock)
extern void SystemInit (void);            // Initialize the system
//extern void SystemCoreClockUpdate (void); // Update SystemCoreClock variable

/**
 *******************************************************************************
 ** This hook is part of wait loops.
 ******************************************************************************/
//extern void delay1ms(uint32_t u32Cnt);
//extern void delay100us(uint32_t u32Cnt);
//extern void delay10us(uint32_t u32Cnt);
extern void FirmwareDelay(uint32_t DlyCnt );

extern void memclr(void* pu8Address, uint32_t u32Count);

void SetBit(uint32_t addr, uint32_t offset, boolean_t bFlag);
void ClrBit(uint32_t addr, uint32_t offset);
boolean_t GetBit(uint32_t addr, uint32_t offset);

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_PS030 _H__ */







