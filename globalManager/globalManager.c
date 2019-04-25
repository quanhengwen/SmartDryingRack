#include "globalManager.h"
//ȫ�ֹ���ȫ�ֶ���
static  GlobalManager this;
static  SensorValue		globalSensorValue;
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
		DHT11Data dh11Data;
		memset(&dh11Data,0,sizeof(DHT11Data));
		memset(&globalSensorValue,0,sizeof(SensorValue));
		globalSensorValue.PhotosensitiveValue=getAdcValue(Channel1);//��ȡ��������������ֵ(δת����ʽ)
		globalSensorValue.RaindropValue=getAdcValue(Channel2);//��ȡ��δ���������ֵ(δת����ʽ)
		globalSensorValue.WindSpeedValue=getAdcValue(Channel3);//��ȡ���ٴ���������ֵ(δת����ʽ)
		dh11Data=DHT11_receive();
		globalSensorValue.TemperatureValue=dh11Data.TH;//�¶�ֵ
		globalSensorValue.HumidityValue=dh11Data.RH;//ʪ��ֵ
		//���½����ڲ��Է��͵����ڿ��Ƿ���ȷ
		sendThresholdToPhone(&dh11Data.RH);//ʪ��ֵ	
		sendThresholdToPhone(&dh11Data.TH);	//�¶�ֵ
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
	if(isSendSmsInfo){//������ʪ�ȶ���(�¶���ֵ�ﵽ)
		//���Ƶ��1���·�
		this.controlMotor1StatusFunc(Move_Up);
		//���Ƶ��2�����겼
		this.controlMotor2StatusFunc(Move_Up);	
		//���Ͷ��Ÿ��ֻ�
		handleSendSmsInfo();
	}else{
		//todo ȥɹ�·�	
	
	}
	return true;
}
static const bool handleSendSmsInfo(void)
{
	//todo����gsm����Ϣ
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