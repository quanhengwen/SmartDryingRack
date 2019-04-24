#ifndef GSMMANAGER_H
#define GSMMANAGER_H

#include "../globalManager/globalManager.h"
/**
 * @brief sendThresholdToPhone:发送信息到手机
 * @param content:短信的内容
 * @return
 */
_public_ extern const bool sendThresholdToPhone(const uint8_t *content);
/**
 * @brief UART1_Send_AT_Command:发送命令给gsm模块
 * @param sendData:发送的数据
 * @param backData：反馈的数据
 * @param wait_time:次数
 * @param interval_time:间隔时间
 * @return true:发送成功,false:失败
 */
_private_ static const bool UART1_Send_AT_Command(uint8_t *sendData,uint8_t *backData,uint8_t wait_time, uint16_t interval_time);
/**
 * @brief UART1_Send_AT_Command:清空gsm返回的缓存
  */
_private_ static void CLR_Buf(void);
/**
 * @brief UART1_Send_Command:发送字符串给gsm
 * @param s:内容
 */
_private_ static void UART1_Send_Command(char *s);
/**
 * @brief UART1_SendData:发送一个字符
 * @param dat:字符
 */
_private_ static void UART1_SendData(uint8_t dat);
/**
 * @brief Find:查找gsm回复的信息
 * @param content:内容
 * @return :true:成功,false:失败
 */
_private_ static const bool Find(uint8_t *content);
#endif