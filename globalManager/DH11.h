#ifndef __DH11_H__
#define __DH11_H__

#include<reg52.h>
#include "../globalManager/globalManager.h"
extern uint8_t rec_dat[9];   //������ʾ�Ľ�����������  
const DHT11Data DHT11_receive();      //����40λ������
static void DHT11_delay_us(uint8_t n);
static void DHT11_delay_ms(uint32_t z);  
static void DHT11_start();
static uint8_t DHT11_rec_byte();      //����һ���ֽ�
#endif