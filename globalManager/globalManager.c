#include "globalManager.h"
//ȫ�ֹ���ȫ�ֶ���
static  GlobalManager this;
/**
 * @brief �ϵ��ʱ���ʼ��������Ƭ�����еĲ�������
 */
void g_initSystemParameter()
{
		//��ʱ���жϳ�ʼ��
		interrupt1Init();
	
		//�����ĳ�ʼ��
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
			case Move_Up:               //��ת
				Motor1ControlTurn(true,MOTOR1CIRCLENUMBER);
					 		//todo�Ѽ�¼д��EEPROM
				return true;
			case Move_Down:							 //��ת
				Motor1ControlTurn(false,MOTOR1CIRCLENUMBER);
					 		//todo�Ѽ�¼д��EEPROM
				return true;
			case Move_Stop:							//ֹͣ
				Motor1ControlStop();
				return true;
			default:
				return false;
		} 
}
static const bool controlMotor2Status(const MotorStatus status)
{
		switch(status){
			case Move_Up:               //��ת
				Motor2ControlTurn(true,MOTOR2CIRCLENUMBER);
				return true;
			case Move_Down:							 //��ת
				Motor2ControlTurn(false,MOTOR2CIRCLENUMBER);
				return true;
			case Move_Stop:							//ֹͣ
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
* �� �� ��         : timeout
* ��������		   :��ʱ���жϴ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void timeout(void) interrupt 1
{
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;

	g_CurrentCount++;
}