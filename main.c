#include "./globalManager/globalManager.h"
void main()
{
	//ȫ�ֳ�ʼ������
	g_initSystemParameter();
//��������ģ��
#if CURRENT_Module==ALL_Module
	
#endif
//���ģ��
#if CURRENT_Module==MOTOR_Module
		//���1���Դ��룬����ת
		g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Down);
			//���2���Դ��룬����ת
		//g_getGlobalManagerObj().controlMotor2StatusFunc(Move_Up);
		forever{}
#endif
//GSMģ�����
#if CURRENT_Module==GSM_Module

#endif
}