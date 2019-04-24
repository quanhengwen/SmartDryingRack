#include"DH11.h"

uint8_t rec_dat[9];   //������ʾ�Ľ�����������
void DHT11_delay_us(uint8_t n)
{
    while(--n);
}

void DHT11_delay_ms(uint32_t z)
{
   uint32_t i,j;
   for(i=z;i>0;i--)
      for(j=110;j>0;j--);
}

void DHT11_start()
{
   Data=1;
   DHT11_delay_us(2);
   Data=0;
   DHT11_delay_ms(30);   //��ʱ18ms����
   Data=1;
   DHT11_delay_us(30);
}

uint8_t DHT11_rec_byte()      //����һ���ֽ�
{
   uint8_t i,dat=0;
  for(i=0;i<8;i++)    //�Ӹߵ������ν���8λ����
   {          
      while(!Data);   ////�ȴ�50us�͵�ƽ��ȥ
      DHT11_delay_us(8);     //��ʱ60us�������Ϊ��������Ϊ1������Ϊ0 
      dat<<=1;           //��λʹ��ȷ����8λ���ݣ�����Ϊ0ʱֱ����λ
      if(Data==1)    //����Ϊ1ʱ��ʹdat��1����������1
         dat+=1;
      while(Data);  //�ȴ�����������    
    }  
    return dat;
}

const DHT11Data DHT11_receive()      //����40λ������
{
		DHT11Data recvData;
    uint8_t R_H,R_L,T_H,T_L,RH,RL,TH,TL,revise; 
		memset(&recvData,0,sizeof(DHT11Data));
    DHT11_start();
    if(Data==0)
    {
        while(Data==0);   //�ȴ�����     
        DHT11_delay_us(40);  //���ߺ���ʱ80us
        R_H=DHT11_rec_byte();    //����ʪ�ȸ߰�λ  
        R_L=DHT11_rec_byte();    //����ʪ�ȵͰ�λ  
        T_H=DHT11_rec_byte();    //�����¶ȸ߰�λ  
        T_L=DHT11_rec_byte();    //�����¶ȵͰ�λ
        revise=DHT11_rec_byte(); //����У��λ

        DHT11_delay_us(25);    //����

        if((R_H+R_L+T_H+T_L)==revise)      //У��
        {
            RH=R_H;
            RL=R_L;
            TH=T_H;
            TL=T_L;
        } 
				recvData.RH=RH;
				recvData.TH=TH;
        /*���ݴ���������ʾ*/
        rec_dat[0]='0'+(RH/10);
        rec_dat[1]='0'+(RH%10);
        rec_dat[2]='R';
        rec_dat[3]='H';
        rec_dat[4]=' ';
        rec_dat[5]=' ';
        rec_dat[6]='0'+(TH/10);
        rec_dat[7]='0'+(TH%10);
        rec_dat[8]='C';
    }
		return recvData;
}
