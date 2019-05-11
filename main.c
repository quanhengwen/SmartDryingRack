#include "./globalManager/globalManager.h"
/**
 * @brief mainDelay:延时1毫秒的函数
 * @param ms:毫秒数
 */
void mainDelay(uint16_t ms);
void main()
{
	int backCode=-1;
	bool isSendSmsInfo=false;
	
	//全局初始化函数
	g_initSystemParameter();
	//延时20秒让模块都初始化
	mainDelay(20000);	
//整个工程模块
#if CURRENT_Module==ALL_Module
			forever{
					mainDelay(500);//500毫秒
					g_getGlobalManagerObj().handleSensorDataFunc();
				}
#endif
//电机模块
#if CURRENT_Module==MOTOR_Module
		//电机1测试代码，正反转
//		g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Up);
//		mainDelay(2000);
//		g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Down);
//		mainDelay(2000);
			//电机2测试代码，正反转
//		g_getGlobalManagerObj().controlMotor2StatusFunc(Move_Down);
//		mainDelay(1000);	
	
		forever{
			//Motor3MakeATurn(true,5);
				//g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Up);		
//		g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Up);
//		mainDelay(5000);
//		g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Down);
//		mainDelay(5000);
//			
//			if(isSendSmsInfo){//发送温湿度短信(温度阈值达到)
//		//此时此刻电机已经收缩状态
////		if(CLOSE==byte_read(MotorStatusAddress))
////			return false;
////		if(isSendOk)
////			return false;
//		//控制电机1收衣服
//		g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Down);
////		sendThresholdToPhone("1");
//		//电磁铁开
////		this.handleControlMagnetFunc(true);
//		//控制电机2收遮雨布
		g_getGlobalManagerObj().controlMotor2StatusFunc(Move_Down);	
//		//电磁铁关
////		this.handleControlMagnetFunc(false);
//		//发送短信给手机
////		handleSendSmsInfo();
//		//保存电机状态
////		byte_write(MotorStatusAddress,CLOSE);
//		isSendSmsInfo=false;
////		sendThresholdToPhone("2");
//	}else{
//		//todo 去晒衣服	
//	//此时此刻电机已经晒衣服状态
////		if(OPEN==byte_read(MotorStatusAddress))
////			return false;
//		//电磁铁开
////		if(!isSendOk)
////			return false;
//		//sendThresholdToPhone("3");
////		this.handleControlMagnetFunc(true);		
//		//控制电机2晒衣服
//		g_getGlobalManagerObj().controlMotor2StatusFunc(Move_Up);
//		//电磁铁关
////		this.handleControlMagnetFunc(false);		
//		//控制电机1晒衣服
//		g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Up);
//		//发送短信给手机
////		handleSendSmsInfo();
//		//保存电机状态
////		byte_write(MotorStatusAddress,OPEN);
//		isSendSmsInfo=true;
		//sendThresholdToPhone("4");
//	}
		};
#endif
//GSM模块调试
#if CURRENT_Module==GSM_Module
	forever{
		g_delay(1);//1秒测试
		WarnLed=~WarnLed;	
		//g_getGlobalManagerObj().handleSendSmsInfoFunc();
	}
#endif
//ADC模块调试
#if CURRENT_Module==ADC_Module
	forever{
		mainDelay(500);//1秒测试
//		WarnLed=~WarnLed;	
//		MagnetSwitch=WarnLed;
		g_getGlobalManagerObj().handleSensorDataFunc();
	}
#endif
}
//延时1ms
void mainDelay(uint16_t ms)
{
  uint8_t count;
	for(;ms>0;ms--)
	{ 	
		for(count=0;count<27;count++);
	}
}