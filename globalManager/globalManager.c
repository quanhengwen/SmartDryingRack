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
void g_delay(const uint32_t ms)
{
	if(!ms)
		return;
	g_EndCount=ms;
	g_CurrentCount=0;
	do{}while(g_CurrentCount<g_EndCount);
}
static void  interrupt1Init()
{
	EA = OPEN;
	TMOD = 0x11;
	ET0 = OPEN;
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
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
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;

	g_CurrentCount++;
}