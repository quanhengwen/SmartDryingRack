#include "MotorManager.h"
/*******************************************************************************
*说明:电机1的8拍
*******************************************************************************/
code  uint8_t  motor1Table[]={0x05,0x01,0x09,0x08,0x0A,0x02,0x06,0x04};
/*******************************************************************************
*说明:电机2的8拍
*******************************************************************************/
code  uint8_t  motor2Table[]={0x50,0x10,0x90,0x80,0xA0,0x20,0x60,0x40};
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
void Motor1MakeATurn(uint8_t var, uint8_t state)
{
		uint8_t i=0;

	if(!state)
	{
		for(i=0; i<8; i++)
		{
			P1=motor1Table[i];
			g_delay(var);
		}
	}else{
		for(i=7; i>0; --i)
		{
			P1=motor1Table[i];
			g_delay(var);
		}
	}
}