#include "globalManager.h"
//全局管理全局对象
static  GlobalManager this;
static  SensorValue		globalSensorValue;
/**
 * @brief 上电的时候初始化整个单片机所有的参数函数
 */
void g_initSystemParameter()
{
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
				Motor1ControlTurn(true,MOTOR1CIRCLENUMBER);
					 		//todo把记录写入EEPROM
				return true;
			case Move_Down:							 //反转
				Motor1ControlTurn(false,MOTOR1CIRCLENUMBER);
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
}
const bool handleSensorData(void)
{
		DHT11Data dh11Data;
		memset(&dh11Data,0,sizeof(DHT11Data));
		memset(&globalSensorValue,0,sizeof(SensorValue));
		globalSensorValue.PhotosensitiveValue=getAdcValue(Channel1);//获取光敏传感器的数值(未转换公式)
		globalSensorValue.RaindropValue=getAdcValue(Channel2);//获取雨滴传感器的数值(未转换公式)
		globalSensorValue.WindSpeedValue=getAdcValue(Channel3);//获取风速传感器的数值(未转换公式)
		dh11Data=DHT11_receive();
		globalSensorValue.TemperatureValue=dh11Data.TH;//温度值
		globalSensorValue.HumidityValue=dh11Data.RH;//湿度值
		//以下仅用于测试发送到串口看是否正确
		sendThresholdToPhone(&dh11Data.RH);//湿度值	
		sendThresholdToPhone(&dh11Data.TH);	//温度值
		handleSensorDataAnalysis();	
		return true;
}
static const bool handleSensorDataAnalysis(void)
{
		bool	isSendSmsInfo=false;
	isSendSmsInfo=globalSensorValue.PhotosensitiveValue>=PhotosensitiveThreshold?true:false;
	isSendSmsInfo=globalSensorValue.RaindropValue>=RaindropThreshold?true:false;
	isSendSmsInfo=globalSensorValue.WindSpeedValue>=WindSpeedThreshold?true:false;
	isSendSmsInfo=globalSensorValue.TemperatureValue>=TemperatureThreshold?true:false;
	isSendSmsInfo=globalSensorValue.HumidityValue>=HumidityThreshold?true:false;
	if(isSendSmsInfo){//发送温湿度短信(温度阈值达到)
		//控制电机1收衣服
		this.controlMotor1StatusFunc(Move_Up);
		//控制电机2收遮雨布
		this.controlMotor2StatusFunc(Move_Up);	
		//发送短信给手机
		handleSendSmsInfo();
	}else{
		//todo 去晒衣服	
	
	}
	return true;
}
static const bool handleSendSmsInfo(void)
{
	//todo发送gsm的信息
	uint8_t xdata sendSmsBuff[50];
	memset(sendSmsBuff,0,sizeof(uint8_t)*50);
	sprintf(sendSmsBuff,"Light:%d,Rain:%d,Wind:%d,Temp:%d,Hum:%d",globalSensorValue.PhotosensitiveValue\
																																,globalSensorValue.RaindropValue\
																																,globalSensorValue.WindSpeedValue\
																																,globalSensorValue.TemperatureValue\
																																,globalSensorValue.HumidityValue);
	sendThresholdToPhone(sendSmsBuff);
	return true;
}
void g_delay(const uint32_t one_10us)
{
	if(!one_10us)
		return;
	g_EndCount=one_10us;
	g_CurrentCount=0;
	forever{
		if(g_CurrentCount>=g_EndCount)
			break;
	}
}
static void  interrupt1Init()
{
	EA = OPEN;
	TMOD = 0x11;
	ET0 = OPEN;
	//10 us
	TH0=(65536-10)/256;
	TL0=(65536-10)%256;
	TR0=OPEN;
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
		PCON &= 0x7F;
		SCON = 0x50;
		TMOD &= 0x0F;	
		TMOD |= 0x20;
		TL1 = 0xFD;
		TH1 = 0xFD;
		ET1 = 0;
		TR1 = OPEN;	
		ES  = OPEN;
#endif
}
static const bool handleControlMagnet(const bool isOpen)
{
	//电磁铁控制开关
	if(isOpen){
			MagnetSwitch=OPEN;//高电平开
	}else{
			MagnetSwitch=CLOSE;	//低电平关闭		
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
	//10 us
	TH0=(65536-10)/256;
	TL0=(65536-10)%256;

	g_CurrentCount++;
	ADC_CLOCK=~ADC_CLOCK;//给adc模块发送方波
}