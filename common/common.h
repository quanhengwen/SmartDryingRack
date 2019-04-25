#ifndef COMMON_H
#define COMMON_H
#include <reg52.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <intrins.h>
/*******************************************************************************
*˵��:�Զ���һЩ�궨��
*******************************************************************************/
#define RATE12   //ʹ�þ���Ϊ12HZ
//#define RATE110592   //ʹ�þ���Ϊ110592HZ
//ͨ��0��ò�Ҫ�ã���Ϊ����һ�����裬Ȼ�������
#define Channel1		1 //����������
#define Channel2		2 //��δ�����
#define Channel3		3 //���ٴ�����
		
#define ALL_Module 0 //����ģ�鿪��
#define ADC_Module 1 //adcģ�鿪��
#define GSM_Module 2 //gsmģ�鿪��
#define LCD_Module 3 //adcģ�鿪��
#define MOTOR_Module 4 //���ģ�鿪��
#define CURRENT_Module ALL_Module //Ĭ�ϲ���
#define forever	while(1)
#define nullptr	((void*)0) //��ָ��
#define _public_	//����
#define _private_ //˽��
#define CHECK_PTR(ptr)	assert(ptr) 
#define true	(!0)
#define false	(!true)
	
#define MOTOR1SPEED	7 //���1���ٶȿ���,ֵԽС�ٶ�Խ��(�Ѿ����¹���ɹ����Գɹ�)
#define MOTOR2SPEED	1 //���2���ٶȿ���,ֵԽС�ٶ�Խ��
//���1ת��Ȧ��
#define MOTOR1CIRCLENUMBER 1450
//���2ת��Ȧ��
#define MOTOR2CIRCLENUMBER 1450
//����һЩ����������ֵ������ʵ�ʵĲ���ʹ��0-100�ı�������Ҫ���ԣ�
#define TemperatureThreshold    50 //�¶���ֵ
#define HumidityThreshold    50 //ʪ����ֵ
#define RaindropThreshold    50 //�����ֵ
#define PhotosensitiveThreshold    50 //������ֵ
#define WindSpeedThreshold			50//������ֵ
/*******************************************************************************
*˵��:�Զ����һЩ��������
*******************************************************************************/

typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef float float_t;
typedef double double_t;
typedef int8_t bool;
/*******************************************************************************
*˵��:һЩ���ؽ����ö��
*******************************************************************************/
typedef enum _BackResult{
	Error_Result=-1,               //ʧ��
	Success_Result=0,							 //�ɹ�
}BackResult;
/*******************************************************************************
*˵��:���״̬��ö��
*******************************************************************************/
typedef enum _MotorStatus{
	Move_Up=1,               //��ת
	Move_Down=2,							 //��ת
	Move_Stop=3,							//ֹͣ
}MotorStatus;
/*******************************************************************************
*˵��:����ö��
*******************************************************************************/
typedef enum _SwitchStatus{
	OPEN=1,               //��
	CLOSE=0,							 //��
}SwitchStatus;
/*******************************************************************************
*˵��:���λ�Ķ���
*******************************************************************************/
sbit ADC_ST   = P3^2; //adc��START�ӿ�
sbit ADC_OE   = P2^5; //adc��OE�ӿ�
sbit ADC_EOC  = P2^6; //adc��EOC�ӿ�
sbit ADC_CLOCK  = P2^7; //adc��CLOCK�ӿ�

sbit ADC_adda = P3^4;//adc�ĵ�ַA	
sbit ADC_addb = P3^5;//adc�ĵ�ַB
sbit ADC_addc = P3^6;//adc�ĵ�ַC

sbit Data=P2^3;   //DHT11����������
sbit MagnetSwitch=P2^4;   //���������
/*******************************************************************************
*˵��:DHT11����
*******************************************************************************/
typedef struct _DHT11Data{
		uint8_t RH;//ʪ��
		uint8_t TH;//�¶�
}DHT11Data;
#endif