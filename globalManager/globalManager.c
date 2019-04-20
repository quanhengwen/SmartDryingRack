#include "globalManager.h"
static  GlobalManager *this=nullptr;
/**
 * @brief �ϵ��ʱ���ʼ��������Ƭ�����еĲ�������
 */
void g_initSystemParameter()
{
		//��ʱ���жϳ�ʼ��
		interrupt1Init();
	
}
const GlobalManager *getGlobalManagerObj()
{
	return this?this:newGlobalManagerObj();
}
static const GlobalManager *newGlobalManagerObj()
{
	assert(this==nullptr)
	this=(GlobalManager *)malloc(sizeof(GlobalManager));
	CHECK_PTR(this);
	return this;
}
void  deleteGlobalManagerObj()
{
	CHECK_PTR(this);
	free(this);	
}
static bool controlMotor1Status(const MotorStatus status)
{
		switch(status){
			case Move_Up:               //��ת
				return true;
			case Move_Down:							 //��ת
				return true;
			case Move_Stop:							//ֹͣ
				return true;
			default:
				return false;
		} 
}
static bool controlMotor2Status(const MotorStatus status)
{
		switch(status){
			case Move_Up:               //��ת
				return true;
			case Move_Down:							 //��ת
				return true;
			case Move_Stop:							//ֹͣ
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