#include "globalManager.h"
//全局管理全局对象
static  GlobalManager this;
static  SensorValue		globalSensorValue;
static  bool					isControlMotor=false;
static  uint32_t			stopGetWindData=-1;
static  bool isSendOk=true;//默认开机的时候，装置处于收缩状态，也就是收衣服状态
code  uint8_t  motor3Table[]={0x05,0x01,0x09,0x08,0x0A,0x02,0x06,0x04};
/**
 * @brief 上电的时候初始化整个单片机所有的参数函数
 */
void g_initSystemParameter()
{
		isControlMotor=false;
		//定时器中断初始化
		interrupt1Init();
		//初始化串口
		uartInit();
		//函数的初始化
		this.controlMotor1StatusFunc=controlMotor1Status;
		this.controlMotor2StatusFunc=controlMotor2Status;
		this.handleSensorDataFunc=handleSensorData;	
		this.handleSendSmsInfoFunc=handleSendSmsInfo;
	  this.handleControlMagnetFunc=handleControlMagnet;
}
const GlobalManager g_getGlobalManagerObj()
{
	return this;
}
static const bool controlMotor1Status(const MotorStatus status)
{
		switch(status){
			case Move_Up:               //正转
				Motor1ControlTurn(false,MOTOR1CIRCLENUMBER);
					 		//todo把记录写入EEPROM
				return true;
			case Move_Down:							 //反转
				Motor1ControlTurn(true,MOTOR1CIRCLENUMBER);
					 		//todo把记录写入EEPROM
				return true;
			case Move_Stop:							//停止
				Motor1ControlStop();
				return true;
			default:
				return false;
		}
}
static const bool controlMotor2Status(const MotorStatus status)
{
		UART1_Send_Command_END("909090\r\n");	
		switch(status){
			case Move_Up:               //正转
				Motor2ControlTurn(true,MOTOR2CIRCLENUMBER);
				return true;
			case Move_Down:							 //反转
				Motor2ControlTurn(false,MOTOR2CIRCLENUMBER);
				return true;
			case Move_Stop:							//停止
				Motor2ControlStop();
				return true;
			default:
				return false;
		}
		UART1_Send_Command_END("8080\r\n");	
}
const bool handleSensorData(void)
{	
	uint8_t xdata sendSmsBuff[100];
	memset(&globalSensorValue,0,sizeof(SensorValue));
	globalSensorValue.PhotosensitiveValue=getAdcValue(Channel1)*100.0/255;//获取光敏传感器的数值
	globalSensorValue.RaindropValue=getAdcValue(Channel2)*100.0/255;//获取雨滴传感器的数值
	globalSensorValue.WindSpeedValue=getAdcValue(Channel3)*100.0/255;//获取风速传感器的数值
	TR0=0;//防止干扰
	DHT11_receive();
	TR0=1;//防止干扰
	globalSensorValue.TemperatureValue=DHT11_receive_TH();//温度值
	globalSensorValue.HumidityValue=DHT11_receive_RH();//湿度值
	sprintf(sendSmsBuff,"from Smart clothes Message: Light:%x,Rain:%x,Wind:%x,Temperature:%x,Humidity:%x\r\n",(int)globalSensorValue.PhotosensitiveValue\
																																,(int)globalSensorValue.RaindropValue\
																																,(int)globalSensorValue.WindSpeedValue\
																																,(int)globalSensorValue.TemperatureValue\
																																,(int)globalSensorValue.HumidityValue);
		UART1_Send_Command_END(sendSmsBuff);	//温度值																															
		//对数据进行处理																														
		EA=0;//防止干扰
		isControlMotor=true;
		interrupt1Init();
		EA=1;//防止干扰																																
		handleSensorDataAnalysis();																																	
		EA=0;//防止干扰
		isControlMotor=false;
		interrupt1Init();
		EA=1;//防止干扰																																		
		return true;
}
void Motor3MakeATurn(bool const direction,const uint32_t speed)
{
	uint8_t index=0;
	if(direction)
	{
		for(index=0; index<8; index++)
		{
			P1  =	motor3Table[index];
			g_delay(speed);
		}
	}else{
		for(index=7; index>0; --index)
		{
			P1 = motor3Table[index];
			g_delay(speed);
		}
	}
}
const int handleSensorDataAnalysis(void)
{
	bool	isSendSmsInfo=false;
	isSendSmsInfo=globalSensorValue.PhotosensitiveValue>=PhotosensitiveThreshold?true:false;
	if(isSendSmsInfo)
			goto DataAnalysis;
	isSendSmsInfo=globalSensorValue.RaindropValue<=RaindropThreshold?true:false;
	if(isSendSmsInfo)
			goto DataAnalysis;	
	isSendSmsInfo=globalSensorValue.WindSpeedValue>=WindSpeedThreshold?true:false;
	if(isSendSmsInfo)
			goto DataAnalysis;	
	isSendSmsInfo=globalSensorValue.TemperatureValue<=TemperatureThreshold?true:false;
	if(isSendSmsInfo)
			goto DataAnalysis;
	isSendSmsInfo=globalSensorValue.HumidityValue>=HumidityThreshold?true:false;
DataAnalysis:	
	if(isSendSmsInfo){
		//此时此刻电机已经收缩状态
//		if(CLOSE==byte_read(MotorStatusAddress))
//			return false;
//		UART1_Send_Command_END("00000000000\r\n");
		if(true==isSendOk)
			return false;
//		UART1_Send_Command_END("1111111111\r\n");
		//控制电机1收衣服
		this.controlMotor1StatusFunc(Move_Down);
		//电磁铁开
		this.handleControlMagnetFunc(true);
		//控制电机2收遮雨布
		this.controlMotor2StatusFunc(Move_Down);	
		//电磁铁关
		this.handleControlMagnetFunc(false);
		//发送短信给手机
		handleSendSmsInfo();
		//保存电机状态
//		byte_write(MotorStatusAddress,CLOSE);
		isSendOk=true;
	}else{
		//todo 去晒衣服	
	//此时此刻电机已经晒衣服状态
//		if(OPEN==byte_read(MotorStatusAddress))
//			return false;
		//电磁铁开
//		sendThresholdToPhone(&isSendOk);
//		UART1_Send_Command_END("2222222222\r\n");		
		if(false==isSendOk)
			return false;
//		UART1_Send_Command_END("3333333333\r\n");
		//sendThresholdToPhone("3");
		this.handleControlMagnetFunc(true);	
		//控制电机2晒衣服
//		UART1_Send_Command_END("44444444444\r\n");	
		this.controlMotor2StatusFunc(Move_Up);		
		//电磁铁关
		this.handleControlMagnetFunc(false);		
		//控制电机1晒衣服
//		UART1_Send_Command_END("555555555\r\n");	
		this.controlMotor1StatusFunc(Move_Up);	
		//发送短信给手机
//		UART1_Send_Command_END("6666666666666\r\n");		
		handleSendSmsInfo();	
//		UART1_Send_Command_END("77777777777\r\n");			
		//保存电机状态
//		byte_write(MotorStatusAddress,OPEN);
		isSendOk=false;
	}
	return true;
}
static const bool handleSendSmsInfo(void)
{
	//todo发送gsm的信息
	uint8_t xdata sendSmsBuff[100];
	int16_t failCount=0;//失败次数
	memset(sendSmsBuff,0,sizeof(uint8_t)*100);
	sprintf(sendSmsBuff,"from Smart clothes Message: Light:%x,Rain:%x,Wind:%x,Temperature:%x,Humidity:%x\r\n",(int)globalSensorValue.PhotosensitiveValue\
																																,(int)globalSensorValue.RaindropValue\
																																,(int)globalSensorValue.WindSpeedValue\
																																,(int)globalSensorValue.TemperatureValue\
																																,(int)globalSensorValue.HumidityValue);
	forever{
		//自定义失败次数就不发了
		if(10==failCount)
			break;//todo 发送失败之后的处理
		if(sendThresholdToPhone(sendSmsBuff))
			break;//todo 发送成功之后的处理
		failCount++;
	}
	return true;
}
void g_delay(const uint32_t one_1ms)
{
	uint8_t i,count=one_1ms;
	if(!isControlMotor){
		for(;count>0;count--)
		{ 	
			for(i=0;i<27;i++);
		}
	}else{
			g_EndCount=one_1ms;
			g_CurrentCount=0;
	do{}while(g_CurrentCount<g_EndCount);
	}
}
static void  interrupt1Init()
{
	if(!isControlMotor){
		EA = OPEN;
		TMOD |= 0x01;
		ET0 = OPEN;
		//10 us
		TH0=(65536-10)/256;
		TL0=(65536-10)%256;
		TR0=OPEN;
	}else{
		EA = OPEN;
		TMOD |= 0x01;
		ET0 = OPEN;
		//10 us
		TH0=(65536-1000)/256;
		TL0=(65536-1000)%256;
		TR0=OPEN;
	}
}
static void  uartInit()
{
	//设置9600的波特率
#ifdef RATE12
    RCAP2L=0xD9;
    RCAP2H=0xFF;
    T2CON=0x34;
    SCON=0x50;
    ES=OPEN;
    EA=OPEN;
#else
	PCON &= 0x7F;		//
	SCON = 0x50;		//
	TMOD &= 0x0F;		//
	TMOD |= 0x20;		//
	TL1 = 0xFD;		  //
	TH1 = 0xFD;		  //
	ET1 = 0;		    //
	TR1 = OPEN;		    //
	ES  = OPEN;					//
	
	
#endif
}
static const bool handleControlMagnet(const bool isOpen)
{
	//电磁铁控制开关
	if(isOpen){
			MagnetSwitch=CLOSE;//低电平开
	}else{
			MagnetSwitch=OPEN;	//高电平关闭		
	}
	return true;
}
/*******************************************************************************
* 函 数 名         : timeout
* 函数功能		   :定时器中断触发
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void timeout(void) interrupt 1
{
	if(!isControlMotor){
		//10 us
		TH0=(65536-10)/256;
		TL0=(65536-10)%256;
		ADC_CLOCK=~ADC_CLOCK;//给adc模块发送方波
	}else{
		TH0=(65536-1000)/256;
		TL0=(65536-1000)%256;
		g_CurrentCount++;
	}
}