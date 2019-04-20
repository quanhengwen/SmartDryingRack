#ifndef MOTORMANAGER_H
#define MOTORMANAGER_H
#include "../globalManager/globalManager.h"
#define MOTOR1SPEED	5 //���1���ٶȿ���,ֵԽС�ٶ�Խ��
#define MOTOR2SPEED	5 //���2���ٶȿ���,ֵԽС�ٶ�Խ��
/**
 * @brief Motor1ControlTurn�����1����ת��
 * @param direction:ת�ķ���true:��ת��false:��ת
 * @param circleNumber:ת��Ȧ��
 */
_public_ extern void Motor1ControlTurn(bool const direction,const uint32_t circleNumber);
/**
* @brief Motor1ControlStop:ֹͣ���1ת��
 */
_public_ extern void Motor1ControlStop();
 /**
 * @brief Motor1ControlTurn�����2����ת��
 * @param direction:ת�ķ���true:��ת��false:��ת
 * @param circleNumber:ת��Ȧ��
 */
_public_ extern void Motor2ControlTurn(bool const direction,const uint32_t circleNumber);
/**
* @brief Motor1ControlStop:ֹͣ���2ת��
 */
_public_ extern void Motor2ControlStop();
/*******************************************************************************
*˵��:������˽�в��ֺ���
*******************************************************************************/ 
_private_ static void Motor1MakeATurn(bool const direction,const uint32_t speed);
_private_ static void Motor2MakeATurn(bool const direction,const uint32_t speed);
#endif 