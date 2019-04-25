#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H
#include "../common/common.h"
#include "../motorManager/motorManager.h"
#include "../adcManager/adcManager.h"
#include "../gsmManager/gsmManager.h"
#include "./DH11.h"
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
/**
 * @brief handleSensorDataFunc:�жϸ����������Ƿ�ﵽ��ֵ
 * @return true:���·�,false:ɹ�·�
 */	
	const bool (*handleSensorDataFunc)(void);
/**
 * @brief handleSendSmsInfoFunc:���Ͷ��Ÿ�gsmģ��
 * @return true:�ɹ�:false:ʧ��
 */
	const bool (*handleSendSmsInfoFunc)(void);
	/**
 * @brief handleControlMagnet:���Ƶ�������غ���
 * @param isOpen:true:��,false:��
 * @return true:�ɹ�,false:ʧ��
 */
const bool (*handleControlMagnetFunc)(const bool isOpen);
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
* @param one_10us:1��10_us,��Ҫ��֤ADCģ������
 */
_public_ extern void g_delay(const uint32_t one_10us);
/*******************************************************************************
*˵��:������˽�в��ֺ���
*******************************************************************************/
_private_	static const bool controlMotor1Status(const MotorStatus status);
_private_	static const bool controlMotor2Status(const MotorStatus status);
_private_	static const bool handleSensorData(void);
_private_	static const bool handleSendSmsInfo(void);
_private_	static const bool handleControlMagnet(const bool isOpen);
/*******************************************************************************
*˵��:�������ڲ�ʹ�õĺ���
*******************************************************************************/
_private_	static void  interrupt1Init(); 
_private_ static void  uartInit();
/*******************************************************************************
*˵��:������˽�б���
*******************************************************************************/
_private_ static int32_t g_EndCount=0;
_private_ static int32_t g_CurrentCount=0;
#endif