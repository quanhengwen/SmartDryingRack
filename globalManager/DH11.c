#include"DH11.h"
static uint8_t  U8FLAG;
static uint8_t  U8temp;
static uint8_t  U8comdata;
static uint8_t  RHValue;
static uint8_t  THValue;
void DHT11_receive()      //接收40位的数据
{
			uint8_t  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;

			//读取模块数据周期不易小于 2S 
			 RHValue=0;
			 THValue=0;
	     Delay(20000);
			//主机拉低18ms 
			 Data=0;
			 Delay(180);
			 Data=1;
			//总线由上拉电阻拉高 主机延时20us
			 Delay_10us();
			 Delay_10us();
			 Delay_10us();
			 Delay_10us();
			//主机设为输入 判断从机响应信号 
			 Data=1;
			//判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	  
			 if(!Data)		 //T !	  
			 {
				 U8FLAG=2;
			 //判断从机是否发出 80us 的低电平响应信号是否结束	 
				 while((!Data)&&U8FLAG++);
				 U8FLAG=2;
			 //判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
				 while((Data)&&U8FLAG++);
			 //数据接收状态		 
				 get8BitData();
				 U8RH_data_H_temp=U8comdata;
				 get8BitData();
				 U8RH_data_L_temp=U8comdata;
				 get8BitData();
				 U8T_data_H_temp=U8comdata;
				 get8BitData();
				 U8T_data_L_temp=U8comdata;
				 get8BitData();
				 U8checkdata_temp=U8comdata;
				 Data=1;
			 //数据校验 
			 
				 U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
				 if(U8temp==U8checkdata_temp)
				 {
					 //不要小数位了
						RHValue=U8RH_data_H_temp;
						THValue=U8T_data_H_temp;
				 }
			 }
}
uint8_t DHT11_receive_TH()
{
		return THValue;
}
uint8_t DHT11_receive_RH()
{
		return RHValue;
}
static void get8BitData(void)
{
			uint8_t i;
          
       for(i=0;i<8;i++)	   
	    {
		
	   	    U8FLAG=2;	
	   	while((!Data)&&U8FLAG++);
			Delay_10us();
		    Delay_10us();
			Delay_10us();
	  		U8temp=0;
	     if(Data)U8temp=1;
		    U8FLAG=2;
		 while((Data)&&U8FLAG++);
	   	//超时则跳出for循环		  
	   	 if(U8FLAG==1)break;
	   	//判断数据位是0还是1	 
		// 如果高电平高过预定0高电平值则数据位为 1  	 
		   U8comdata<<=1;
	   	 U8comdata|=U8temp;
			}
}
static void Delay(uint16_t count)
{
  uint8_t i;
	for(;count>0;count--)
	{ 	
		for(i=0;i<27;i++);
	}
}
static void Delay_10us(void)
{
   uint8_t i;
   i--;
   i--;
   i--;
   i--;
   i--;
   i--;
}