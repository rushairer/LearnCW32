#include "ADC.h"

uint16_t Volt_Buffer[ADC_SAMPLE_SIZE];
uint16_t Curr_Buffer[ADC_SAMPLE_SIZE];

void ADC_init(void)
{
    ADC_InitTypeDef     ADC_InitStructure;         //ADC配置结构体
    ADC_SerialChTypeDef ADC_SerialChStructure;     //ADC序列通道结构体
    GPIO_InitTypeDef    GPIO_Init_Struct;
	
    __RCC_GPIOB_CLK_ENABLE(); //打开ADC对应引脚时钟   
    __RCC_ADC_CLK_ENABLE();   // 打开ADC时钟
	
    
    PB01_ANALOG_ENABLE();                    //使能模拟引脚
		PB00_ANALOG_ENABLE();                   //使能模拟引脚
		PB10_ANALOG_ENABLE();                   //使能模拟引脚
		PB11_ANALOG_ENABLE(); 
	
    ADC_StructInit(&ADC_InitStructure);      // ADC默认值初始化
    ADC_InitStructure.ADC_ClkDiv     = ADC_Clk_Div128; //ADC工作时钟配置 PCLK/4 = 6/4 = 1.5Mhz
	
/*信号电压较低时，可以降低参考电压来提高分辨率。 改变参考电压后，同样二进制表示的电压值就会不一样，
  最大的二进制（全1）表示的就是你的参考电压，在计算实际电压时，就需要将参考电压考虑进去。*/
    ADC_InitStructure.ADC_VrefSel    = ADC_Vref_BGR1p5;     //参考电压设置为1.5V
    ADC_InitStructure.ADC_SampleTime = ADC_SampTime10Clk;   //由于电压信号为慢速信号，ADC采样时间为十个ADC采样周期以确保准确

   	ADC_SerialChStructure.ADC_Sqr0Chmux  = ADC_SqrCh11;      //配置ADC序列，PB01是ADC的第9通道
    ADC_SerialChStructure.ADC_Sqr1Chmux  = ADC_SqrCh9;
   	ADC_SerialChStructure.ADC_Sqr2Chmux  = ADC_SqrCh8;      //配置ADC序列，PB01是ADC的第9通道
    ADC_SerialChStructure.ADC_Sqr3Chmux  = ADC_SqrCh12;
    ADC_SerialChStructure.ADC_SqrEns     = ADC_SqrEns03;
    ADC_SerialChStructure.ADC_InitStruct = ADC_InitStructure; //ADC初始化
		
    ADC_SerialChContinuousModeCfg(&ADC_SerialChStructure);   //ADC序列连续转换模式配置
    ADC_ClearITPendingAll();           //清除ADC所有中断状态
    ADC_Enable();                      // ADC使能
    ADC_SoftwareStartConvCmd(ENABLE);  //ADC转换软件启动命令
}

void Get_ADC_Value(void)
{
	static uint8_t cnt;
     ADC_GetSqr0Result(&Volt_Buffer[cnt]);
	
  ADC_GetSqr3Result(&Curr_Buffer[cnt]);	
	
	cnt++;
	if(cnt >= ADC_SAMPLE_SIZE)
    {
        cnt = 0;				
    }
}
