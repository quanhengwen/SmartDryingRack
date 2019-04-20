#ifndef MOTORMANAGER_H
#define MOTORMANAGER_H
#include "../globalManager/globalManager.h"
#define MOTOR1SPEED	5 //电机1的速度控制,值越小速度越快
#define MOTOR2SPEED	5 //电机2的速度控制,值越小速度越快
/**
 * @brief Motor1ControlTurn：电机1控制转向
 * @param direction:转的方向，true:正转，false:反转
 * @param circleNumber:转的圈数
 */
_public_ extern void Motor1ControlTurn(bool const direction,const uint32_t circleNumber);
/**
* @brief Motor1ControlStop:停止电机1转动
 */
_public_ extern void Motor1ControlStop();
 /**
 * @brief Motor1ControlTurn：电机2控制转向
 * @param direction:转的方向，true:正转，false:反转
 * @param circleNumber:转的圈数
 */
_public_ extern void Motor2ControlTurn(bool const direction,const uint32_t circleNumber);
/**
* @brief Motor1ControlStop:停止电机2转动
 */
_public_ extern void Motor2ControlStop();
/*******************************************************************************
*说明:以下是私有部分函数
*******************************************************************************/ 
_private_ static void Motor1MakeATurn(bool const direction,const uint32_t speed);
_private_ static void Motor2MakeATurn(bool const direction,const uint32_t speed);
#endif 