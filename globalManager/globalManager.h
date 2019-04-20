#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H
#include "../common/common.h"
#include "../motorManager/motorManager.h"
/*******************************************************************************
*˵��:ȫ�ֹ���ṹ��
*******************************************************************************/
typedef struct _GlobalManager{
	/**
 * @brief ���Ƶ��1��ת��״̬��״ֵ̬,
 * @param status:�ο�MotorStatusö��
 * @return true:�ɹ�,false:ʧ��
 */
	const bool (*controlMotor1StatusFunc)(const MotorStatus status);
	/**
 * @brief ���Ƶ��2��ת��״̬��״ֵ̬,�ο�MotorStatusö��
 * @param status:�ο�MotorStatusö��
 * @return true:�ɹ�,false:ʧ��
 */
	const bool (*controlMotor2StatusFunc)(const MotorStatus status);
}GlobalManager;
/*******************************************************************************
*˵��:�����ǹ��е��ò��ֺ���
*******************************************************************************/
/**
 * @brief ��ȡȫ�ֹ������
 * @return ȫ�ֹ������
 */
_public_ extern const GlobalManager g_getGlobalManagerObj();
/**
 * @brief �ϵ��ʱ���ʼ��������Ƭ�����еĲ�������
 */
_public_ extern	void	g_initSystemParameter(); 
/**
* @brief :��ʱ����
* @param ms:����
 */
_public_ extern void g_delay(const uint32_t ms);

/*******************************************************************************
*˵��:������˽�в��ֺ���
*******************************************************************************/
_private_	static const bool controlMotor1Status(const MotorStatus status);
_private_	static const bool controlMotor2Status(const MotorStatus status);
/*******************************************************************************
*˵��:�������ڲ�ʹ�õĺ���
*******************************************************************************/
_private_	static void  interrupt1Init(); 
/*******************************************************************************
*˵��:������˽�б���
*******************************************************************************/
_private_ static int32_t g_EndCount=0;
_private_ static int32_t g_CurrentCount=0;
#endif