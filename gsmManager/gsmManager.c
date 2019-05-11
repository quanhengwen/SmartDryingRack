#include "gsmManager.h"
#define Buf_Max 	 	  70 	//����1���泤��
uint8_t First_Int = 0;
xdata uint8_t Uart1_Buf[Buf_Max];
/*******************************************************************************
*˵��:����绰���޸���������޸Ĳ���ĵ绰��
*******************************************************************************/
xdata uint8_t  *phone_num = "AT+CMGS=\"17377349850\""; 
const bool sendThresholdToPhone(const uint8_t *content)
{

#ifdef UseTest
	bool ret;
	ret = UART1_Send_AT_Command(content,"",1,50);//����ͨ���Ƿ�ɹ�
	if(!ret)
	{
		TestWarnLed=~	TestWarnLed;
		return false;
	}
	return true;
#else
	uint8_t ret;
	char end_char[2];
	
	end_char[0] = 0x1A;//�����ַ�
	end_char[1] = '\0';
	
	//���ô洢λ��
	ret = UART1_Send_AT_Command("AT+CPMS=\"SM\",\"ME\",\"SM\"","OK",3,200);
	if(ret == 0)
	{
		return false;
	}
	
	ret = UART1_Send_AT_Command("AT+CMGF=1","OK",3,100);//����ΪTEXTģʽ
	if(ret == 0)
	{
		return false;
	}
	
	
	ret = UART1_Send_AT_Command("AT+CSCS=\"GSM\"","OK",3,100);//�����ַ���ʽ
	if(ret == 0)
	{
		return false;
	}
	
	ret = UART1_Send_AT_Command(phone_num,">",3,100);//���������˵ĵ绰����
	if(ret == 0)
	{
		return false;
	}
	
	UART1_SendString(content); //�˺������Ͷ������� ���ӻس�����
	ret = UART1_Send_AT_Command_END(end_char,"OK",1,500);//���ͽ��������ȴ�����ok,�ȴ�5S��һ�Σ���Ϊ���ųɹ����͵�״̬ʱ��Ƚϳ�
	if(ret == 0)
	{
		return false;
	}
	return true;
#endif
}
/*----------------------------
UART1 �����ַ���
-----------------------------*/
static void UART1_SendString(char *s)
{
	while(*s)//����ַ���������
	{
		UART1_SendData(*s++);//���͵�ǰ�ַ�
	}
}
static const bool UART1_Send_AT_Command(uint8_t *sendData,uint8_t *backData,uint8_t wait_time, uint16_t interval_time)       
{
	uint8_t count=0;

	CLR_Buf();  //����ս���buffer
	while(count < wait_time)                    
	{
		UART1_Send_Command(sendData);//��ָ���ȥ ���Զ����\r\n��׺��
		g_delay(interval_time);
		if(Find(backData))            //������ҪӦ����ַ�
		{
			return true;
		}
		count++;
	}
	return false;
}
/*******************************************************************************
* ������ : CLR_Buf
* ����   : �������2��������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
*******************************************************************************/
static void CLR_Buf(void)
{
	uint8_t count;
	for(count=0;count<Buf_Max;count++)      //��������������
	{
		Uart1_Buf[count] = 0x00;
	}
    First_Int = 0;              //�����ַ�������ʼ�洢λ��
}
/**********************************
��������
**********************************/
static void UART1_Send_Command(uint8_t *s)
{
	CLR_Buf(); 
	while(*s)//����ַ���������
	{
		UART1_SendData(*s++);//���͵�ǰ�ַ�
	}
	#ifndef UseTest
	UART1_SendData(0x0D);
	#endif 
}
/*----------------------------
UART1 ���ʹ�������
-----------------------------*/
static void UART1_SendData(uint8_t dat)
{
	ES=0;			//�ش����ж�
	SBUF=dat;			
	while(TI!=1);	//�ȴ����ͳɹ�
	TI=0;			//��������жϱ�־
	ES=1;			//�������ж�
}
/*******************************************************************************
* ������ : Find
* ����   : �жϻ������Ƿ���ָ�����ַ���
* ����   : 
* ���   : 
* ����   : unsigned char:1 �ҵ�ָ���ַ���0 δ�ҵ�ָ���ַ� 
* ע��   : 
*******************************************************************************/

static const bool Find(uint8_t *content)
{ 
	ES = 0;  //�Ľ�����
	if(strstr(Uart1_Buf,content)!=NULL)
	{
		ES = 1;
		return true;
	}	
	else
	{
		ES = 1;
		return false;
	}	
}
static uint8_t UART1_Send_AT_Command_END(uint8_t *b,uint8_t *a,uint8_t wait_time,uint16_t interval_time)         
{
	uint8_t i;

	CLR_Buf(); 
	i = 0;
	while(i < wait_time)                    
	{
		UART1_Send_Command_END(b);
		g_delay(interval_time);
		if(Find(a))            //������ҪӦ����ַ�
		{
			return 1;
		}
		i++;
	}
	
	return 0;
}
void UART1_Send_Command_END(char *s)
{
	CLR_Buf(); 
	while(*s)//����ַ���������
	{
		UART1_SendData(*s++);//���͵�ǰ�ַ�
	}
}
/********************* UART1�жϺ���************************/
void UART1_ISR (void) interrupt 4
{
	if (RI)
	{
		RI = 0;                           //���RIλ
		Uart1_Buf[First_Int] = SBUF;  	  //�����յ����ַ����浽������
		First_Int++;                	  //����ָ������ƶ�
		if(First_Int >= Buf_Max)       	  //���������,������ָ��ָ�򻺴���׵�ַ
		{
			First_Int = 0;
		}
	}
	if (TI)
	{
		TI = 0;                          //���TIλ
	}
}
