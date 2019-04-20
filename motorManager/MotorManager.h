#ifndef MOTORMANAGER_H
#define MOTORMANAGER_H
#include "../globalManager/globalManager.h"
/**
 * @brief Motor1ControlTurn�����1����ת��
 * @param state:ת�ķ���true:��ת��false:��ת
 * @param var:�ٶ�
 */
_public_ extern void Motor1MakeATurn(uint8_t var, uint8_t state);
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
_private_ static void Motor2MakeATurn(bool const direction,const uint32_t speed);


#endif 