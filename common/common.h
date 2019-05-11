#ifndef COMMON_H
#define COMMON_H
#include <reg52.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <intrins.h>
/*******************************************************************************
*说明:自定义一些宏定义
*******************************************************************************/
//#define RATE12   //使用晶振为12HZ
#define RATE110592   //使用晶振为110592HZ
//#define UseTest			//使用测试
//通道0最好不要用，因为它有一个电阻，然后出问题
#define Channel1		1 //光敏传感器
#define Channel2		2 //雨滴传感器
#define Channel3		3 //风速传感器
		
#define ALL_Module 0 //所有模块开启
#define ADC_Module 1 //adc模块开启
#define GSM_Module 2 //gsm模块开启
#define LCD_Module 3 //adc模块开启
#define MOTOR_Module 4 //电机模块开启
#define CURRENT_Module ALL_Module//默认测试
#define forever	while(1)
#define nullptr	((void*)0) //空指针
#define _public_	//公有
#define _private_ //私有
#define CHECK_PTR(ptr)	assert(ptr) 
#define true	(!0)
#define false	(!true)
	
#define MOTOR1SPEED	5 //电机1的速度控制,值越小速度越快(已经重新购买成功测试成功)
#define MOTOR2SPEED	5 //电机2的速度控制,值越小速度越快
//电机1转的圈数
#define MOTOR1CIRCLENUMBER 200
//电机2转的圈数
#define MOTOR2CIRCLENUMBER 700
//定义一些传感器的阈值（经过实际的测量使用0-100的比例，需要测试）
#define PhotosensitiveThreshold    79 //光敏阈值 (换算之后 0xc8*100/255)(0-100) 越小光越亮
#define RaindropThreshold    25 //雨滴阈值  (换算之后 0x29*100/255)(0-100) 越小雨越大
#define WindSpeedThreshold			2//风速阈值(换算之后 0x04*100/255)(0-100)  越大风越大
#define TemperatureThreshold    15 //温度阈值 越搞越大
#define HumidityThreshold    100 //湿度阈值 越大越大
//掉电不丢失的功能EEPROM的地址段
#define	MotorStatusAddress	0x2000	//1:表示此时此刻已经在晒衣服了，0:表示此时此刻已经收完衣服	
/*******************************************************************************
*说明:自定义的一些数据类型
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
*说明:一些返回结果的枚举
*******************************************************************************/
typedef enum _BackResult{
	Error_Result=-1,               //失败
	Success_Result=0,							 //成功
}BackResult;
/*******************************************************************************
*说明:电机状态的枚举
*******************************************************************************/
typedef enum _MotorStatus{
	Move_Up=1,               //正转
	Move_Down=2,							 //反转
	Move_Stop=3,							//停止
}MotorStatus;
/*******************************************************************************
*说明:开关枚举
*******************************************************************************/
typedef enum _SwitchStatus{
	OPEN=1,               //开
	CLOSE=0,							 //关
}SwitchStatus;
/*******************************************************************************
*说明:相关位的定义
*******************************************************************************/
sbit ADC_ST   = P3^2; //adc的START接口
sbit ADC_OE   = P2^5; //adc的OE接口
sbit ADC_EOC  = P2^6; //adc的EOC接口
sbit ADC_CLOCK  = P2^7; //adc的CLOCK接口

sbit ADC_adda = P3^4;//adc的地址A	
sbit ADC_addb = P3^5;//adc的地址B
sbit ADC_addc = P3^6;//adc的地址C

sbit Data=P2^3;   //DHT11定义数据线
sbit MagnetSwitch=P2^2;   //电磁铁开关
sbit WarnLed=P2^0;				//警告灯
sbit TestWarnLed=P2^1;				//警告灯
/*******************************************************************************
*说明:DHT11数据
*******************************************************************************/
typedef struct _DHT11Data{
		uint8_t RH;//湿度
		uint8_t TH;//温度
}DHT11Data;
#endif