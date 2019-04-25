#ifndef EEPROM_H
#define EEPROM_H
#include <intrins.h>
#include <reg52.h>
 //使用方法：如下所示：
//	SectorErase(0x2000);    //擦除第一扇区
//    byte_write(0x2001,dat[0]);   //在地址为0x2001的内存写入一个字节
//    byte_write(0x2002,dat[1]);   //在地址为0x2002的内存写入一个字节
//    Delay_ms(1000);       //延时1s
// 
//    InitUART(9600);         //串口初始化函数
// 
//    while(1)
//    { 
//        TxStr[0] = byte_read(0x2001);     //从地址0x2001读取一个字节
//        TxStr[1] = byte_read(0x2002);     //从地址0x2002读取一个字节
// 
//        UartTXData(TxStr);     //将读取的字节发送至串口
// 
//        Delay_ms(2000);        //延时2s
//    }
		
		
typedef  unsigned int uint;
typedef  unsigned char uchar;
 
/********STC89C52扇区分布*******
第一扇区：2000H--21FF
第二扇区：2200H--23FF
第三扇区：2400H--25FF
第四扇区：2600H--27FF
第五扇区：2800H--29FF
第六扇区：2A00H--2BFF
第七扇区：2C00H--2DFF
第八扇区：2E00H--2FFF
*******************************/
 
#define RdCommand 0x01     //字节编程数据命令   
#define PrgCommand 0x02    //字节读数据命令   
#define EraseCommand 0x03  //扇区擦除数据命令
 
#define Error 1
#define Ok 0
#define WaitTime 0x01 //定义CPU的等待时间,40M以下为0,20M以下为1,10M以下为2,5M以下为3
 
/*****ISP/IAP特殊功能寄存器声明********/    
sfr ISP_DATA = 0xE2;
sfr ISP_ADDRH = 0xE3;
sfr ISP_ADDRL = 0xE4;
sfr ISP_CMD = 0xE5;
sfr ISP_TRIG = 0xE6;
sfr ISP_CONTR = 0xE7;
 
//从地址读取一个字节
unsigned char byte_read(unsigned int byte_addr);
//在地址写入一个字节
void byte_write(unsigned int byte_addr,unsigned char Orig_data);
//擦除一片区域
void SectorErase(unsigned int sector_addr);
#endif