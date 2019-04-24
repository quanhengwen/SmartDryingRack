#ifndef ADCMANAGER_H
#define ADCMANAGER_H
#include "../globalManager/globalManager.h"
/**
 * @brief 获取adc的通道值
 * @param channel:通道，adc模块8个通道，从0到7选择
 * @return adc转换之后的真实的值，以数组的形式传回来
 */
_public_ extern const uint8_t *getAdcValue(const int8_t channel);
//测试函数
_public_ extern const uint8_t getAdcValueDisplay(void);
/*******************************************************************************
*说明：以下是私有函数
*******************************************************************************/ 
/**
 * @brief 处理adc出来的值
 * @param channel：处理的通道
 */
_private_ static void handleAdcValue(const int8_t channel);

#endif