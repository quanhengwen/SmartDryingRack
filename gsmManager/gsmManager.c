#include "gsmManager.h"
#define Buf_Max 	 	  70 	//串口1缓存长度
uint8_t First_Int = 0;
xdata uint8_t Uart1_Buf[Buf_Max];
/*******************************************************************************
*说明:拨打电话，修改这里可以修改拨打的电话。
*******************************************************************************/
xdata uint8_t  *phone_num = "AT+CMGS=\"17377349850\""; 
const bool sendThresholdToPhone(const uint8_t *content)
{

#ifdef UseTest
	bool ret;
	ret = UART1_Send_AT_Command(content,"",1,50);//测试通信是否成功
	if(!ret)
	{
		TestWarnLed=~	TestWarnLed;
		return false;
	}
	return true;
#else
	uint8_t ret;
	char end_char[2];
	
	end_char[0] = 0x1A;//结束字符
	end_char[1] = '\0';
	
	//设置存储位置
	ret = UART1_Send_AT_Command("AT+CPMS=\"SM\",\"ME\",\"SM\"","OK",3,200);
	if(ret == 0)
	{
		return false;
	}
	
	ret = UART1_Send_AT_Command("AT+CMGF=1","OK",3,100);//配置为TEXT模式
	if(ret == 0)
	{
		return false;
	}
	
	
	ret = UART1_Send_AT_Command("AT+CSCS=\"GSM\"","OK",3,100);//设置字符格式
	if(ret == 0)
	{
		return false;
	}
	
	ret = UART1_Send_AT_Command(phone_num,">",3,100);//输入收信人的电话号码
	if(ret == 0)
	{
		return false;
	}
	
	UART1_SendString(content); //此函数发送短信内容 不加回车换行
	ret = UART1_Send_AT_Command_END(end_char,"OK",1,500);//发送结束符，等待返回ok,等待5S发一次，因为短信成功发送的状态时间比较长
	if(ret == 0)
	{
		return false;
	}
	return true;
#endif
}
/*----------------------------
UART1 发送字符串
-----------------------------*/
static void UART1_SendString(char *s)
{
	while(*s)//检测字符串结束符
	{
		UART1_SendData(*s++);//发送当前字符
	}
}
static const bool UART1_Send_AT_Command(uint8_t *sendData,uint8_t *backData,uint8_t wait_time, uint16_t interval_time)       
{
	uint8_t count=0;

	CLR_Buf();  //先清空接收buffer
	while(count < wait_time)                    
	{
		UART1_Send_Command(sendData);//把指令发出去 会自动添加\r\n后缀的
		g_delay(interval_time);
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
	#ifndef UseTest
	UART1_SendData(0x0D);
	#endif 
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
static uint8_t UART1_Send_AT_Command_END(uint8_t *b,uint8_t *a,uint8_t wait_time,uint16_t interval_time)         
{
	uint8_t i;

	CLR_Buf(); 
	i = 0;
	while(i < wait_time)                    
	{
		UART1_Send_Command_END(b);
		g_delay(interval_time);
		if(Find(a))            //查找需要应答的字符
		{
			return 1;
		}
		i++;
	}
	
	return 0;
}
void UART1_Send_Command_END(char *s)
{
	CLR_Buf(); 
	while(*s)//检测字符串结束符
	{
		UART1_SendData(*s++);//发送当前字符
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
