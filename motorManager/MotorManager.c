#include "MotorManager.h"
/*******************************************************************************
*说明:电机1的8拍
*******************************************************************************/
code  uint8_t  motor1Table[]={0x05,0x01,0x09,0x08,0x0A,0x02,0x06,0x04};
//code  uint8_t  motor1Table[]={0x04,0x06,0x02,0x0A,0x08,0x09,0x01,0x05};
/*******************************************************************************
*说明:电机2的8拍
*******************************************************************************/
code  uint8_t  motor2Table[]={0x50,0x10,0x90,0x80,0xA0,0x20,0x60,0x40};
//code  uint8_t  motor2Table[]={0x40,0x60,0x20,0xA0,0x80,0x90,0x10,0x50};
void Motor1ControlTurn(bool const direction,const uint32_t circleNumber)
{
		uint32_t number=circleNumber;
		uint32_t index=0;
		forever{
				if(index>=circleNumber)
					break;
				++index;
				Motor1MakeATurn(direction,MOTOR1SPEED);
		}
		Motor1ControlStop();
		//todo把记录写入EEPROM
}
void Motor2ControlTurn(bool const direction,const uint32_t circleNumber)
{
		uint32_t number=circleNumber;
		uint32_t index=0;
		UART1_Send_Command_END("707070\r\n");	
		forever{
				if(index>=circleNumber)
					break;
				++index;
				Motor2MakeATurn(direction,MOTOR2SPEED);
		}
		UART1_Send_Command_END("606060\r\n");			
		Motor2ControlStop();
		//todo把记录写入EEPROM
}
void Motor1ControlStop()
{
	P1=0x00;
}
void Motor2ControlStop()
{
	P1=0x00;
}
static void Motor2MakeATurn(bool const direction,const uint32_t speed)
{
	uint8_t index=0;
	if(direction)
	{
		for(index=0; index<8; index++)
		{
			P1  =	motor2Table[index];
			g_delay(speed);
		}
	}else{
		for(index=7; index>0; --index)
		{
			P1 = motor2Table[index];
			g_delay(speed);
		}
	}
}
static void Motor1MakeATurn(bool const direction,const uint32_t speed)
{
	uint8_t index=0;
	if(direction)
	{
		for(index=0; index<8; index++)
		{
			P1  =	motor1Table[index];
			g_delay(speed);
		}
	}else{
		for(index=7; index>0; --index)
		{
			P1 = motor1Table[index];
			g_delay(speed);
		}
	}
}
static void delay(const uint32_t one_1ms)
{

  uint8_t i,count=one_1ms;
	for(;count>0;count--)
	{ 	
		for(i=0;i<27;i++);
	}
}