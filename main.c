#include "./globalManager/globalManager.h"
/**
 * @brief mainDelay:��ʱ1����ĺ���
 * @param ms:������
 */
void mainDelay(uint16_t ms);
void main()
{
	int backCode=-1;
	bool isSendSmsInfo=false;
	
	//ȫ�ֳ�ʼ������
	g_initSystemParameter();
	//��ʱ20����ģ�鶼��ʼ��
	mainDelay(20000);	
//��������ģ��
#if CURRENT_Module==ALL_Module
			forever{
					mainDelay(500);//500����
					g_getGlobalManagerObj().handleSensorDataFunc();
				}
#endif
//���ģ��
#if CURRENT_Module==MOTOR_Module
		//���1���Դ��룬����ת
//		g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Up);
//		mainDelay(2000);
//		g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Down);
//		mainDelay(2000);
			//���2���Դ��룬����ת
//		g_getGlobalManagerObj().controlMotor2StatusFunc(Move_Down);
//		mainDelay(1000);	
	
		forever{
			//Motor3MakeATurn(true,5);
				//g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Up);		
//		g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Up);
//		mainDelay(5000);
//		g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Down);
//		mainDelay(5000);
//			
//			if(isSendSmsInfo){//������ʪ�ȶ���(�¶���ֵ�ﵽ)
//		//��ʱ�˿̵���Ѿ�����״̬
////		if(CLOSE==byte_read(MotorStatusAddress))
////			return false;
////		if(isSendOk)
////			return false;
//		//���Ƶ��1���·�
//		g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Down);
////		sendThresholdToPhone("1");
//		//�������
////		this.handleControlMagnetFunc(true);
//		//���Ƶ��2�����겼
		g_getGlobalManagerObj().controlMotor2StatusFunc(Move_Down);	
//		//�������
////		this.handleControlMagnetFunc(false);
//		//���Ͷ��Ÿ��ֻ�
////		handleSendSmsInfo();
//		//������״̬
////		byte_write(MotorStatusAddress,CLOSE);
//		isSendSmsInfo=false;
////		sendThresholdToPhone("2");
//	}else{
//		//todo ȥɹ�·�	
//	//��ʱ�˿̵���Ѿ�ɹ�·�״̬
////		if(OPEN==byte_read(MotorStatusAddress))
////			return false;
//		//�������
////		if(!isSendOk)
////			return false;
//		//sendThresholdToPhone("3");
////		this.handleControlMagnetFunc(true);		
//		//���Ƶ��2ɹ�·�
//		g_getGlobalManagerObj().controlMotor2StatusFunc(Move_Up);
//		//�������
////		this.handleControlMagnetFunc(false);		
//		//���Ƶ��1ɹ�·�
//		g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Up);
//		//���Ͷ��Ÿ��ֻ�
////		handleSendSmsInfo();
//		//������״̬
////		byte_write(MotorStatusAddress,OPEN);
//		isSendSmsInfo=true;
		//sendThresholdToPhone("4");
//	}
		};
#endif
//GSMģ�����
#if CURRENT_Module==GSM_Module
	forever{
		g_delay(1);//1�����
		WarnLed=~WarnLed;	
		//g_getGlobalManagerObj().handleSendSmsInfoFunc();
	}
#endif
//ADCģ�����
#if CURRENT_Module==ADC_Module
	forever{
		mainDelay(500);//1�����
//		WarnLed=~WarnLed;	
//		MagnetSwitch=WarnLed;
		g_getGlobalManagerObj().handleSensorDataFunc();
	}
#endif
}
//��ʱ1ms
void mainDelay(uint16_t ms)
{
  uint8_t count;
	for(;ms>0;ms--)
	{ 	
		for(count=0;count<27;count++);
	}
}