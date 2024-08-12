#ifndef __SEG_DIS_H
#define __SEG_DIS_H

#include "cw32f030_gpio.h"
#include "cw32f030_rcc.h"

void Seg_Init(void);
void Seg_Dis(uint8_t Pos,uint8_t Num);
void Close_Com(void);
void Display(uint32_t value);
void DisplayI(uint32_t value);
void Dis_Refresh(void);

#endif
