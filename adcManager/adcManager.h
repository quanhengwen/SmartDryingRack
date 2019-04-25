#ifndef ADCMANAGER_H
#define ADCMANAGER_H
#include "../globalManager/globalManager.h"
/**
 * @brief 获取adc的通道值
 * @param channel:通道，adc模块8个通道，从0到7选择
 * @return adc转换之后的真实的值
 */
_public_ extern const uint8_t getAdcValue(const int8_t channel);
#endif