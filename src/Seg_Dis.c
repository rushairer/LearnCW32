#include "Seg_Dis.h"

/*  共阴数码管编码表：
 0x3f   0x06   0x5b  0x4f  0x66  0x6d  0x7d  0x07  0x7f  0x6f 
  0      1      2     3     4     5     6     7     8     9 
 0xbf   0x86   0xdb  0xcf  0xe6  0xed  0xfd  0x87  0xff  0xef           
  0.     1.     2.    3.    4.    5.    6.    7.    8.    9.          */
 
             
uint8_t Seg_Table[21] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f,
	0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x87, 0xff, 0xef,0xF7};// 0xF7:A.
uint8_t Seg_Reg[6] = {1,2,3,4,5,6};

void Seg_Init(void)
{
	__RCC_GPIOA_CLK_ENABLE();//打开GPIOA的时钟
	__RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitTypeDef GPIO_InitStruct; 
		
	GPIO_InitStruct.Pins = GPIO_PIN_0 | GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 | GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 | GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15; //PA00,E;PA04,G
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.IT = GPIO_IT_NONE;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  GPIO_Init(CW_GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pins = GPIO_PIN_3 | GPIO_PIN_4; 
  GPIO_Init(CW_GPIOB, &GPIO_InitStruct);
}

void Seg_Dis(uint8_t Pos,uint8_t Num)
{
	int i;
	uint8_t Dis_Value;
	Dis_Value = Seg_Table[Num];
	
	for(i = 0; i < 8; i++)
	{
      switch(i)
        {
          case 0:
              GPIO_WritePin(CW_GPIOA,GPIO_PIN_2,(Dis_Value >> i) & 0x01);    //PA02,A
              break;
          case 1:
              GPIO_WritePin(CW_GPIOA,GPIO_PIN_0,(Dis_Value >> i) & 0x01);    //PA00,B
              break;
          case 2:
              GPIO_WritePin(CW_GPIOA,GPIO_PIN_4,(Dis_Value >> i) & 0x01);    //PA04,C
              break;
          case 3:
              GPIO_WritePin(CW_GPIOA,GPIO_PIN_6,(Dis_Value >> i) & 0x01);    //PA06,D
              break;
          case 4:
              GPIO_WritePin(CW_GPIOA,GPIO_PIN_7,(Dis_Value >> i) & 0x01);    //PA07,E
              break;
          case 5:
              GPIO_WritePin(CW_GPIOA,GPIO_PIN_1,(Dis_Value >> i) & 0x01);    //PA01,F
              break;
          case 6:
              GPIO_WritePin(CW_GPIOA,GPIO_PIN_3,(Dis_Value >> i) & 0x01);    //PA03,G
              break;
          case 7:
              GPIO_WritePin(CW_GPIOA,GPIO_PIN_5,(Dis_Value >> i) & 0x01);    //PA05,DP
              break;
          default:
              break;
				}
	}
	
	switch(Pos)
	{
	  case 0:
      GPIO_WritePin(CW_GPIOA,GPIO_PIN_8,GPIO_Pin_RESET);  //PA8,COM1
      break;
    case 1:
		  GPIO_WritePin(CW_GPIOA,GPIO_PIN_11,GPIO_Pin_RESET);  //PA9,COM2
      break;
    case 2:
		  GPIO_WritePin(CW_GPIOA,GPIO_PIN_12,GPIO_Pin_RESET);  //PA10,COM3
      break;
		case 3:
		  GPIO_WritePin(CW_GPIOA,GPIO_PIN_15,GPIO_Pin_RESET);  //PA11,COM4
      break;
    case 4:
		  GPIO_WritePin(CW_GPIOB,GPIO_PIN_3,GPIO_Pin_RESET);  //PA12,COM5
      break;
    case 5:
		  GPIO_WritePin(CW_GPIOB,GPIO_PIN_4,GPIO_Pin_RESET);  //PA15,COM6
      break;
		default:
      break;
	}
}

/**
 * @brief 关闭所有公共端
 * 
 */
void Close_Com(void)
{
  GPIO_WritePin(CW_GPIOA,GPIO_PIN_8,GPIO_Pin_SET);    
	GPIO_WritePin(CW_GPIOB,GPIO_PIN_3,GPIO_Pin_SET);    
	GPIO_WritePin(CW_GPIOB,GPIO_PIN_4,GPIO_Pin_SET);    
  GPIO_WritePin(CW_GPIOA,GPIO_PIN_11,GPIO_Pin_SET);   
	GPIO_WritePin(CW_GPIOA,GPIO_PIN_12,GPIO_Pin_SET);   
	GPIO_WritePin(CW_GPIOA,GPIO_PIN_15,GPIO_Pin_SET);   
}

void DisplaySETV(uint32_t value)
{
	uint8_t Thousands;
  uint8_t Hundreds;
  uint8_t Tens;
  uint8_t Units; // 个位数
	
	Thousands = value / 1000;
	 if(Thousands > 0)
    {
       Units     = value % 10;
       value     = Units > 5 ? (value + 10) : value; // 根据后一位四舍五入
       Thousands = value / 1000 % 10;
       Hundreds  = value / 100 % 10;
       Tens      = value / 10 % 10;
			
       // 显示xx.x伏
       Seg_Reg[3] = Thousands;
       Seg_Reg[4] = Hundreds + 10; // 加dp显示
       Seg_Reg[5] = Tens;
		}
		
	 else
	   {
	     Units     = value % 10;
	     Tens      = value / 10 % 10;
       Hundreds  = value / 100 % 10;
	     
			 // 显示x.xx伏
	     Seg_Reg[3] = Hundreds + 10;              // 加dp显示
	     Seg_Reg[4] = Tens;
	     Seg_Reg[5] = Units;
	   }
}

void Display(uint32_t value)
{
	uint8_t Thousands;
  uint8_t Hundreds;
  uint8_t Tens;
  uint8_t Units; // 个位数
	
	Thousands = value / 1000;
	 if(Thousands > 0)
    {
       Units     = value % 10;
       value     = Units > 5 ? (value + 10) : value; // 根据后一位四舍五入
       Thousands = value / 1000 % 10;
       Hundreds  = value / 100 % 10;
       Tens      = value / 10 % 10;
			
       // 显示xx.x伏
       Seg_Reg[0] = Thousands;
       Seg_Reg[1] = Hundreds + 10; // 加dp显示
       Seg_Reg[2] = Tens;
		}
		
	 else
	   {
	     Units     = value % 10;
	     Tens      = value / 10 % 10;
       Hundreds  = value / 100 % 10;
	     
			 // 显示x.xx伏
	     Seg_Reg[0] = Hundreds + 10;              // 加dp显示
	     Seg_Reg[1] = Tens;
	     Seg_Reg[2] = Units;
	   }
}

void DisplayI(uint32_t value)
{
	uint8_t Thousands;
  uint8_t Hundreds;
  uint8_t Tens;
  uint8_t Units; // 个位数
	
	     Seg_Reg[3] = value/100 + 10;// 加dp显示
       Seg_Reg[4] = value%100/10; 
       Seg_Reg[5] = value%10;	
}

/**
 * @brief 数码管扫描显示函数,定时器周期性调用
 *
 */
void Dis_Refresh(void)
{
  static uint8_t num = 0;

	Close_Com();//先关闭公共端,防止重影
	Seg_Dis(num,Seg_Reg[num]);
	num++;
  if(num > 6)
  {
    num = 0;
  }
}
