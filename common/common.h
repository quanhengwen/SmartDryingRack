#ifndef COMMON_H
#define COMMON_H
#include <reg52.h>
#include <assert.h>
#include <stdlib.h>
/*******************************************************************************
*说明:自定义一些宏定义
*******************************************************************************/
#define ALL_Module 0 //所有模块开启
#define ADC_Module 1 //adc模块开启
#define GSM_Module 2 //gsm模块开启
#define LCD_Module 3 //adc模块开启
#define MOTOR_Module 4 //电机模块开启

#define CURRENT_Module ALL_Module //默认测试

#define forever	while(1)

#define nullptr	((void*)0) //空指针

#define _public_	//公有
#define _private_ //私有

#define CHECK_PTR(ptr)	assert(ptr) 

#define true	(!0)
#define false	(!true)
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
	CLOSE=2,							 //关
}SwitchStatus;
#endif