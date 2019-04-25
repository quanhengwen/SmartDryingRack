#include "globalManager.h"
//全局管理全局对象
static  GlobalManager this;
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
		uint8_t adcValue=0;
		DHT11Data dh11Data;
		memset(&dh11Data,0,sizeof(DHT11Data));
		adcValue=getAdcValue(Channel1);//获取光敏传感器的数值(未转换公式)
		adcValue=getAdcValue(Channel2);//获取雨滴传感器的数值(未转换公式)
		adcValue=getAdcValue(Channel3);//获取风速传感器的数值(未转换公式)
		//todo 处理传感器的值与阈值判断
		//光敏传感器等
//		handleSendSmsInfo();
	
		dh11Data=DHT11_receive();
		sendThresholdToPhone(&dh11Data.RH);		
		sendThresholdToPhone(&dh11Data.TH);		
		return false;
}
static const bool handleSendSmsInfo(void)
{
	//todo发送gsm的信息
//	uint8_t adcData=getAdcValueDisplay();
//	sendThresholdToPhone(&adcData);
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