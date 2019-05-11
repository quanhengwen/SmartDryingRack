#include "globalManager.h"
//ȫ�ֹ���ȫ�ֶ���
static  GlobalManager this;
static  SensorValue		globalSensorValue;
static  bool					isControlMotor=false;
static  uint32_t			stopGetWindData=-1;
static  bool isSendOk=true;//Ĭ�Ͽ�����ʱ��װ�ô�������״̬��Ҳ�������·�״̬
code  uint8_t  motor3Table[]={0x05,0x01,0x09,0x08,0x0A,0x02,0x06,0x04};
/**
 * @brief �ϵ��ʱ���ʼ��������Ƭ�����еĲ�������
 */
void g_initSystemParameter()
{
		isControlMotor=false;
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
				Motor1ControlTurn(false,MOTOR1CIRCLENUMBER);
					 		//todo�Ѽ�¼д��EEPROM
				return true;
			case Move_Down:							 //��ת
				Motor1ControlTurn(true,MOTOR1CIRCLENUMBER);
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
		UART1_Send_Command_END("909090\r\n");	
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
		UART1_Send_Command_END("8080\r\n");	
}
const bool handleSensorData(void)
{	
	uint8_t xdata sendSmsBuff[100];
	memset(&globalSensorValue,0,sizeof(SensorValue));
	globalSensorValue.PhotosensitiveValue=getAdcValue(Channel1)*100.0/255;//��ȡ��������������ֵ
	globalSensorValue.RaindropValue=getAdcValue(Channel2)*100.0/255;//��ȡ��δ���������ֵ
	globalSensorValue.WindSpeedValue=getAdcValue(Channel3)*100.0/255;//��ȡ���ٴ���������ֵ
	TR0=0;//��ֹ����
	DHT11_receive();
	TR0=1;//��ֹ����
	globalSensorValue.TemperatureValue=DHT11_receive_TH();//�¶�ֵ
	globalSensorValue.HumidityValue=DHT11_receive_RH();//ʪ��ֵ
	sprintf(sendSmsBuff,"from Smart clothes Message: Light:%x,Rain:%x,Wind:%x,Temperature:%x,Humidity:%x\r\n",(int)globalSensorValue.PhotosensitiveValue\
																																,(int)globalSensorValue.RaindropValue\
																																,(int)globalSensorValue.WindSpeedValue\
																																,(int)globalSensorValue.TemperatureValue\
																																,(int)globalSensorValue.HumidityValue);
		UART1_Send_Command_END(sendSmsBuff);	//�¶�ֵ																															
		//�����ݽ��д���																														
		EA=0;//��ֹ����
		isControlMotor=true;
		interrupt1Init();
		EA=1;//��ֹ����																																
		handleSensorDataAnalysis();																																	
		EA=0;//��ֹ����
		isControlMotor=false;
		interrupt1Init();
		EA=1;//��ֹ����																																		
		return true;
}
void Motor3MakeATurn(bool const direction,const uint32_t speed)
{
	uint8_t index=0;
	if(direction)
	{
		for(index=0; index<8; index++)
		{
			P1  =	motor3Table[index];
			g_delay(speed);
		}
	}else{
		for(index=7; index>0; --index)
		{
			P1 = motor3Table[index];
			g_delay(speed);
		}
	}
}
const int handleSensorDataAnalysis(void)
{
	bool	isSendSmsInfo=false;
	isSendSmsInfo=globalSensorValue.PhotosensitiveValue>=PhotosensitiveThreshold?true:false;
	if(isSendSmsInfo)
			goto DataAnalysis;
	isSendSmsInfo=globalSensorValue.RaindropValue<=RaindropThreshold?true:false;
	if(isSendSmsInfo)
			goto DataAnalysis;	
	isSendSmsInfo=globalSensorValue.WindSpeedValue>=WindSpeedThreshold?true:false;
	if(isSendSmsInfo)
			goto DataAnalysis;	
	isSendSmsInfo=globalSensorValue.TemperatureValue<=TemperatureThreshold?true:false;
	if(isSendSmsInfo)
			goto DataAnalysis;
	isSendSmsInfo=globalSensorValue.HumidityValue>=HumidityThreshold?true:false;
DataAnalysis:	
	if(isSendSmsInfo){
		//��ʱ�˿̵���Ѿ�����״̬
//		if(CLOSE==byte_read(MotorStatusAddress))
//			return false;
//		UART1_Send_Command_END("00000000000\r\n");
		if(true==isSendOk)
			return false;
//		UART1_Send_Command_END("1111111111\r\n");
		//���Ƶ��1���·�
		this.controlMotor1StatusFunc(Move_Down);
		//�������
		this.handleControlMagnetFunc(true);
		//���Ƶ��2�����겼
		this.controlMotor2StatusFunc(Move_Down);	
		//�������
		this.handleControlMagnetFunc(false);
		//���Ͷ��Ÿ��ֻ�
		handleSendSmsInfo();
		//������״̬
//		byte_write(MotorStatusAddress,CLOSE);
		isSendOk=true;
	}else{
		//todo ȥɹ�·�	
	//��ʱ�˿̵���Ѿ�ɹ�·�״̬
//		if(OPEN==byte_read(MotorStatusAddress))
//			return false;
		//�������
//		sendThresholdToPhone(&isSendOk);
//		UART1_Send_Command_END("2222222222\r\n");		
		if(false==isSendOk)
			return false;
//		UART1_Send_Command_END("3333333333\r\n");
		//sendThresholdToPhone("3");
		this.handleControlMagnetFunc(true);	
		//���Ƶ��2ɹ�·�
//		UART1_Send_Command_END("44444444444\r\n");	
		this.controlMotor2StatusFunc(Move_Up);		
		//�������
		this.handleControlMagnetFunc(false);		
		//���Ƶ��1ɹ�·�
//		UART1_Send_Command_END("555555555\r\n");	
		this.controlMotor1StatusFunc(Move_Up);	
		//���Ͷ��Ÿ��ֻ�
//		UART1_Send_Command_END("6666666666666\r\n");		
		handleSendSmsInfo();	
//		UART1_Send_Command_END("77777777777\r\n");			
		//������״̬
//		byte_write(MotorStatusAddress,OPEN);
		isSendOk=false;
	}
	return true;
}
static const bool handleSendSmsInfo(void)
{
	//todo����gsm����Ϣ
	uint8_t xdata sendSmsBuff[100];
	int16_t failCount=0;//ʧ�ܴ���
	memset(sendSmsBuff,0,sizeof(uint8_t)*100);
	sprintf(sendSmsBuff,"from Smart clothes Message: Light:%x,Rain:%x,Wind:%x,Temperature:%x,Humidity:%x\r\n",(int)globalSensorValue.PhotosensitiveValue\
																																,(int)globalSensorValue.RaindropValue\
																																,(int)globalSensorValue.WindSpeedValue\
																																,(int)globalSensorValue.TemperatureValue\
																																,(int)globalSensorValue.HumidityValue);
	forever{
		//�Զ���ʧ�ܴ����Ͳ�����
		if(10==failCount)
			break;//todo ����ʧ��֮��Ĵ���
		if(sendThresholdToPhone(sendSmsBuff))
			break;//todo ���ͳɹ�֮��Ĵ���
		failCount++;
	}
	return true;
}
void g_delay(const uint32_t one_1ms)
{
	uint8_t i,count=one_1ms;
	if(!isControlMotor){
		for(;count>0;count--)
		{ 	
			for(i=0;i<27;i++);
		}
	}else{
			g_EndCount=one_1ms;
			g_CurrentCount=0;
	do{}while(g_CurrentCount<g_EndCount);
	}
}
static void  interrupt1Init()
{
	if(!isControlMotor){
		EA = OPEN;
		TMOD |= 0x01;
		ET0 = OPEN;
		//10 us
		TH0=(65536-10)/256;
		TL0=(65536-10)%256;
		TR0=OPEN;
	}else{
		EA = OPEN;
		TMOD |= 0x01;
		ET0 = OPEN;
		//10 us
		TH0=(65536-1000)/256;
		TL0=(65536-1000)%256;
		TR0=OPEN;
	}
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
	PCON &= 0x7F;		//
	SCON = 0x50;		//
	TMOD &= 0x0F;		//
	TMOD |= 0x20;		//
	TL1 = 0xFD;		  //
	TH1 = 0xFD;		  //
	ET1 = 0;		    //
	TR1 = OPEN;		    //
	ES  = OPEN;					//
	
	
#endif
}
static const bool handleControlMagnet(const bool isOpen)
{
	//��������ƿ���
	if(isOpen){
			MagnetSwitch=CLOSE;//�͵�ƽ��
	}else{
			MagnetSwitch=OPEN;	//�ߵ�ƽ�ر�		
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
	if(!isControlMotor){
		//10 us
		TH0=(65536-10)/256;
		TL0=(65536-10)%256;
		ADC_CLOCK=~ADC_CLOCK;//��adcģ�鷢�ͷ���
	}else{
		TH0=(65536-1000)/256;
		TL0=(65536-1000)%256;
		g_CurrentCount++;
	}
}