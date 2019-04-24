#ifndef __DH11_H__
#define __DH11_H__

#include<reg52.h>
#include "../globalManager/globalManager.h"
extern uint8_t rec_dat[9];   //用于显示的接收数据数组

void DHT11_delay_ms(uint32_t z);    
const DHT11Data DHT11_receive();      //接收40位的数据
#endif