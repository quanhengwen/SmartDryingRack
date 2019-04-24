#include "gsmManager.h"
#define Buf_Max 	 	  70 	//����1���泤��
uint8_t First_Int = 0;
xdata uint8_t Uart1_Buf[Buf_Max];
const bool sendThresholdToPhone(const uint8_t *content)
{
	bool ret;
	
	ret = UART1_Send_AT_Command(content," ",1,50);//����ͨ���Ƿ�ɹ�
	if(!ret)
	{
		return false;
	}
//	
//	ret = UART1_Send_AT_Command("AT+CPIN?","READY",2,50);//��ѯ���Ƿ����
//	if(!ret)
//	{
//		return false;
//	}
	//todo ������Ϣ���ֻ�ȥ
//	ret = UART1_Send_AT_Command(phone,"OK",2,50);//����
//	if(!ret)
//	{
//		return false;
//	}
	return true;
}
static const bool UART1_Send_AT_Command(uint8_t *sendData,uint8_t *backData,uint8_t wait_time, uint16_t interval_time)       
{
	uint8_t count=0;

	CLR_Buf();  //����ս���buffer
	while(count < wait_time)                    
	{
		UART1_Send_Command(sendData);//��ָ���ȥ ���Զ����\r\n��׺��
		g_delay(interval_time*100);
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
//	UART1_SendData(0x0D);
//	UART1_SendData(0x0A);
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