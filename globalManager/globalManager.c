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
	
		//函数的初始化
		this.controlMotor1StatusFunc=controlMotor1Status;
		this.controlMotor2StatusFunc=controlMotor2Status;
		this.handleSensorDataFunc=handleSensorData;	
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
		uint8_t *adcValuePtr=nullptr;
		adcValuePtr=getAdcValue(0);//获取adc通道1的真实转换值，也就是in0对应的传感器的值
		//todo 处理传感器的值与阈值判断 
	
	
			return false;
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
}