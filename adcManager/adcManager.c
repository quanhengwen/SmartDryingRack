#include "adcManager.h"
const uint8_t getAdcValue(const int8_t channel)
{
		uint8_t ADC_DATA=0;
		if(channel<0 || channel>7)
			return nullptr;
	  //0口作为模拟输入口
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
		return ADC_DATA;
}