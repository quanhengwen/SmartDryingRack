#include "gsmManager.h"
#define Buf_Max 	 	  70 	//串口1缓存长度
uint8_t First_Int = 0;
xdata uint8_t Uart1_Buf[Buf_Max];
const bool sendThresholdToPhone(const uint8_t *content)
{
	bool ret;
	
	ret = UART1_Send_AT_Command(content," ",1,50);//测试通信是否成功
	if(!ret)
	{
		return false;
	}
//	
//	ret = UART1_Send_AT_Command("AT+CPIN?","READY",2,50);//查询卡是否插上
//	if(!ret)
//	{
//		return false;
//	}
	//todo 发送信息到手机去
//	ret = UART1_Send_AT_Command(phone,"OK",2,50);//拨号
//	if(!ret)
//	{
//		return false;
//	}
	return true;
}
static const bool UART1_Send_AT_Command(uint8_t *sendData,uint8_t *backData,uint8_t wait_time, uint16_t interval_time)       
{
	uint8_t count=0;

	CLR_Buf();  //先清空接收buffer
	while(count < wait_time)                    
	{
		UART1_Send_Command(sendData);//把指令发出去 会自动添加\r\n后缀的
		g_delay(interval_time*100);
		if(Find(backData))            //查找需要应答的字符
		{
			return true;
		}
		count++;
	}
	return false;
}
/*******************************************************************************
* 函数名 : CLR_Buf
* 描述   : 清除串口2缓存数据
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
static void CLR_Buf(void)
{
	uint8_t count;
	for(count=0;count<Buf_Max;count++)      //将缓存内容清零
	{
		Uart1_Buf[count] = 0x00;
	}
    First_Int = 0;              //接收字符串的起始存储位置
}
/**********************************
发送命令
**********************************/
static void UART1_Send_Command(uint8_t *s)
{
	CLR_Buf(); 
	while(*s)//检测字符串结束符
	{
		UART1_SendData(*s++);//发送当前字符
	}
//	UART1_SendData(0x0D);
//	UART1_SendData(0x0A);
}
/*----------------------------
UART1 发送串口数据
-----------------------------*/
static void UART1_SendData(uint8_t dat)
{
	ES=0;			//关串口中断
	SBUF=dat;			
	while(TI!=1);	//等待发送成功
	TI=0;			//清除发送中断标志
	ES=1;			//开串口中断
}
/*******************************************************************************
* 函数名 : Find
* 描述   : 判断缓存中是否含有指定的字符串
* 输入   : 
* 输出   : 
* 返回   : unsigned char:1 找到指定字符，0 未找到指定字符 
* 注意   : 
*******************************************************************************/

static const bool Find(uint8_t *content)
{ 
	ES = 0;  //改进程序
	if(strstr(Uart1_Buf,content)!=NULL)
	{
		ES = 1;
		return true;
	}	
	else
	{
		ES = 1;
		return false;
	}	
}

/********************* UART1中断函数************************/
void UART1_ISR (void) interrupt 4
{
	if (RI)
	{
		RI = 0;                           //清除RI位
		Uart1_Buf[First_Int] = SBUF;  	  //将接收到的字符串存到缓存中
		First_Int++;                	  //缓存指针向后移动
		if(First_Int >= Buf_Max)       	  //如果缓存满,将缓存指针指向缓存的首地址
		{
			First_Int = 0;
		}
	}
	if (TI)
	{
		TI = 0;                          //清除TI位
	}
}