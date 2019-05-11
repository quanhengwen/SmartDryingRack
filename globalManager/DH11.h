#ifndef __DH11_H__
#define __DH11_H__

#include<reg52.h>
#include "../globalManager/globalManager.h" 
/**
 * @brief 获取温湿度的值
 * @return 无
 */
_public_ extern void DHT11_receive();
/**
 * @brief 获取温度值
 * @return 无
 */
_public_ extern uint8_t DHT11_receive_TH();
/**
 * @brief 获取湿度值
 * @return 无
 */
_public_ extern uint8_t DHT11_receive_RH();
/*******************************************************************************
*说明:以下是私有部分函数
*******************************************************************************/
_private_ static void Delay(uint16_t count);
_private_	static void Delay_10us(void);
_private_	static void get8BitData(void);
#endif