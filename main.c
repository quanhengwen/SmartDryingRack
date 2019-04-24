#include "./globalManager/globalManager.h"
void main()
{
	//全局初始化函数
	g_initSystemParameter();
//整个工程模块
#if CURRENT_Module==ALL_Module
			forever{
					g_getGlobalManagerObj().handleSensorDataFunc();
				
			
			}
#endif
//电机模块
#if CURRENT_Module==MOTOR_Module
		//电机1测试代码，正反转
		g_getGlobalManagerObj().controlMotor1StatusFunc(Move_Down);
			//电机2测试代码，正反转
		//g_getGlobalManagerObj().controlMotor2StatusFunc(Move_Up);
		forever{}
#endif
//GSM模块调试
#if CURRENT_Module==GSM_Module
	g_getGlobalManagerObj().handleSendSmsInfoFunc();
	forever{}
#endif
//ADC模块调试
#if CURRENT_Module==ADC_Module
	g_getGlobalManagerObj().handleSensorDataFunc();
	forever{}
#endif
}