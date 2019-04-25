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
		//��ʼ������
		uartInit();
		//�����ĳ�ʼ��
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
const bool handleSensorData(void)
{
		uint8_t adcValue=0;
		DHT11Data dh11Data;
		memset(&dh11Data,0,sizeof(DHT11Data));
		adcValue=getAdcValue(Channel1);//��ȡ��������������ֵ(δת����ʽ)
		adcValue=getAdcValue(Channel2);//��ȡ��δ���������ֵ(δת����ʽ)
		adcValue=getAdcValue(Channel3);//��ȡ���ٴ���������ֵ(δת����ʽ)
		//todo ����������ֵ����ֵ�ж�
		//������������
//		handleSendSmsInfo();
	
		dh11Data=DHT11_receive();
		sendThresholdToPhone(&dh11Data.RH);		
		sendThresholdToPhone(&dh11Data.TH);		
		return false;
}
static const bool handleSendSmsInfo(void)
{
	//todo����gsm����Ϣ
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
	//����9600�Ĳ�����
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
	//��������ƿ���
	if(isOpen){
			MagnetSwitch=OPEN;//�ߵ�ƽ��
	}else{
			MagnetSwitch=CLOSE;	//�͵�ƽ�ر�		
	}
	return true;
}
/*******************************************************************************
* �� �� ��         : timeout
* ��������		   :��ʱ���жϴ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void timeout(void) interrupt 1
{
	//10 us
	TH0=(65536-10)/256;
	TL0=(65536-10)%256;

	g_CurrentCount++;
	ADC_CLOCK=~ADC_CLOCK;//��adcģ�鷢�ͷ���
}