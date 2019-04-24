#include "adcManager.h"
static uint8_t ADC_DATA;
static uint8_t real_adc_value[10];
const uint8_t *getAdcValue(const int8_t channel)
{
		if(channel<0 || channel>7)
			return nullptr;
	  //0口作为模拟输入口
		ADC_DATA=0;
    ADC_adda= (channel&0x1);
    ADC_addb =(channel&0x2);
    ADC_addc =(channel&0x4);

    ADC_OE = 0;
    ADC_ST = 0;
    ADC_ST = 1;
    _nop_();//保证足够的上升沿
    ADC_ST = 0;
    while(!ADC_EOC); //wait conv
    ADC_OE = 1;
    ADC_DATA = P0;
    ADC_OE = 0;
    handleAdcValue(channel);
		return real_adc_value;
}
const uint8_t getAdcValueDisplay(void)
{
	return ADC_DATA;
}
static void handleAdcValue(const int8_t channel)
{
		if(channel<0 || channel>7)
			return;
		memset(real_adc_value,0,sizeof(uint8_t)*10);
		//todo 处理获取到模拟电压和实际对应的公式
			
}