#include"DH11.h"
static uint8_t  U8FLAG;
static uint8_t  U8temp;
static uint8_t  U8comdata;
static uint8_t  RHValue;
static uint8_t  THValue;
void DHT11_receive()      //����40λ������
{
			uint8_t  U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;

			//��ȡģ���������ڲ���С�� 2S 
			 RHValue=0;
			 THValue=0;
	     Delay(20000);
			//��������18ms 
			 Data=0;
			 Delay(180);
			 Data=1;
			//������������������ ������ʱ20us
			 Delay_10us();
			 Delay_10us();
			 Delay_10us();
			 Delay_10us();
			//������Ϊ���� �жϴӻ���Ӧ�ź� 
			 Data=1;
			//�жϴӻ��Ƿ��е͵�ƽ��Ӧ�ź� �粻��Ӧ����������Ӧ����������	  
			 if(!Data)		 //T !	  
			 {
				 U8FLAG=2;
			 //�жϴӻ��Ƿ񷢳� 80us �ĵ͵�ƽ��Ӧ�ź��Ƿ����	 
				 while((!Data)&&U8FLAG++);
				 U8FLAG=2;
			 //�жϴӻ��Ƿ񷢳� 80us �ĸߵ�ƽ���緢����������ݽ���״̬
				 while((Data)&&U8FLAG++);
			 //���ݽ���״̬		 
				 get8BitData();
				 U8RH_data_H_temp=U8comdata;
				 get8BitData();
				 U8RH_data_L_temp=U8comdata;
				 get8BitData();
				 U8T_data_H_temp=U8comdata;
				 get8BitData();
				 U8T_data_L_temp=U8comdata;
				 get8BitData();
				 U8checkdata_temp=U8comdata;
				 Data=1;
			 //����У�� 
			 
				 U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
				 if(U8temp==U8checkdata_temp)
				 {
					 //��ҪС��λ��
						RHValue=U8RH_data_H_temp;
						THValue=U8T_data_H_temp;
				 }
			 }
}
uint8_t DHT11_receive_TH()
{
		return THValue;
}
uint8_t DHT11_receive_RH()
{
		return RHValue;
}
static void get8BitData(void)
{
			uint8_t i;
          
       for(i=0;i<8;i++)	   
	    {
		
	   	    U8FLAG=2;	
	   	while((!Data)&&U8FLAG++);
			Delay_10us();
		    Delay_10us();
			Delay_10us();
	  		U8temp=0;
	     if(Data)U8temp=1;
		    U8FLAG=2;
		 while((Data)&&U8FLAG++);
	   	//��ʱ������forѭ��		  
	   	 if(U8FLAG==1)break;
	   	//�ж�����λ��0����1	 
		// ����ߵ�ƽ�߹�Ԥ��0�ߵ�ƽֵ������λΪ 1  	 
		   U8comdata<<=1;
	   	 U8comdata|=U8temp;
			}
}
static void Delay(uint16_t count)
{
  uint8_t i;
	for(;count>0;count--)
	{ 	
		for(i=0;i<27;i++);
	}
}
static void Delay_10us(void)
{
   uint8_t i;
   i--;
   i--;
   i--;
   i--;
   i--;
   i--;
}