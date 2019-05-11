#ifndef __DH11_H__
#define __DH11_H__

#include<reg52.h>
#include "../globalManager/globalManager.h" 
/**
 * @brief ��ȡ��ʪ�ȵ�ֵ
 * @return ��
 */
_public_ extern void DHT11_receive();
/**
 * @brief ��ȡ�¶�ֵ
 * @return ��
 */
_public_ extern uint8_t DHT11_receive_TH();
/**
 * @brief ��ȡʪ��ֵ
 * @return ��
 */
_public_ extern uint8_t DHT11_receive_RH();
/*******************************************************************************
*˵��:������˽�в��ֺ���
*******************************************************************************/
_private_ static void Delay(uint16_t count);
_private_	static void Delay_10us(void);
_private_	static void get8BitData(void);
#endif