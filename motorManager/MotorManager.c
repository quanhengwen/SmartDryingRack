#include "MotorManager.h"
/*******************************************************************************
*说明:电机8拍
*******************************************************************************/
code uint8_t  motorTable[]={0x05,0x01,0x09,0x08,0x0A,0x02,0x06,0x04};
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
}
void Motor2ControlTurn(bool const direction,const uint32_t circleNumber)
{
		uint32_t number=circleNumber;
		uint32_t index=0;
		forever{
				if(index>=circleNumber)
					break;
				++index;
				Motor2MakeATurn(direction,MOTOR2SPEED);
		}
}
void Motor1ControlStop()
{
	P1=P1 & 0xf0;
}
void Motor2ControlStop()
{
	P1=P1 & 0x0f;
}
static void Motor1MakeATurn(bool const direction,const uint32_t speed)
{
	uint32_t index=0;
	uint8_t	 tempValue=0xf0;
	P1 &=tempValue;
	if(direction)
	{
		for(index=0; index<8; index++)
		{
			P1  =	P1 | motorTable[index];
			g_delay(speed);
		}
	}else{
		
		for(index=7; index>0; --index)
		{
			P1 =P1 | motorTable[index];
			g_delay(speed);
		}
	}
}
static void Motor2MakeATurn(bool const direction,const uint32_t speed)
{
	uint32_t index=0;
	uint8_t	 tempValue=0x0f;
	P1 &=tempValue;
	if(direction)
	{
		for(index=0; index<8; index++)
		{
			P1  =	P1 | (motorTable[index]<<4);
			g_delay(speed);
		}
	}else{
		for(index=7; index>0; --index)
		{
			P1 =P1 | (motorTable[index]<<4);
			g_delay(speed);
		}
	}
}