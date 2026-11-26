/**
  ******************************************************************************
  * �ļ��� ��   PAN312x_Driver.h
  * ����   ��   PAN312x RF Team
  * �汾   ��   V1.0.0
  * ʱ��   ��   
  * �ļ�������

 *******************************************************************************/

#ifndef PAN312x_DRIVER_H
#define PAN312x_DRIVER_H

#include "bsp.h"
#include "PAN312x_xsfr.h"


extern uint8_t TcxoControlByGpio;

#define RF_BUFFER_SIZE_MAX                          128
#define RF_BUFFER_SIZE                              80


#define FIRMWARE_ID                 0x0003
#define DCDC_ENABLE                 0




#if defined(__CC_ARM)
#pragma anon_unions
#endif


#define COMMAND_CALIBRATE       0x0d
#define COMMAND_OP_REGISTER     0x0f
#define COMMAND_START_TX        0x11
#define COMMAND_START_RX        0x13
#define COMMAND_TX_ACK          0x15
#define COMMAND_GO_SLEEP        0x17
#define COMMAND_GO_READY        0x19
#define COMMAND_GET_RXDATA      0x1b
#define COMMAND_SET_PROPERTY    0x1d
#define COMMAND_GET_PROPERTY    0x1f
#define COMMAND_GET_STATUS      0x21
#define COMMAND_CLEAR_STATUS    0x23
#define COMMAND_GET_FWID        0x25    //GET_FWID������0x25, �Ժ�汾����Ҳ������?x25
#define COMMAND_DUTY_CYCLE      0x27

/***************************************************************************************************
 * GROUP1 INDEX ����
 **************************************************************************************************/
#define PROPERTY_ADDR_CLK_CONFIG  0x0100 //һЩʱ������
#define PROPERTY_GROUP_CLK_CONFIG 0x01   //һЩʱ������
#define PROPERTY_INDEX_CLK_CONFIG 0x00   //һЩʱ������

#define PROPERTY_ADDR_IRQ_ENABLE  0x0101 //�ж�ʹ������
#define PROPERTY_GROUP_IRQ_ENABLE 0x01   //�ж�ʹ������
#define PROPERTY_INDEX_IRQ_ENABLE 0x01   //�ж�ʹ������


/***************************************************************************************************
 * GROUP2 INDEX ����
 **************************************************************************************************/
#define PROPERTY_ADDR_SYS_CTRL0            0x0200 //ϵͳ����
#define PROPERTY_GROUP_SYS_CTRL0           0x02   //ϵͳ����
#define PROPERTY_INDEX_SYS_CTRL0           0x00   //ϵͳ����

#define PROPERTY_ADDR_PACKET_FILTER_CTRL   0x0201 //�����˿���
#define PROPERTY_GROUP_PACKET_FILTER_CTRL  0x02   //�����˿���
#define PROPERTY_INDEX_PACKET_FILTER_CTRL  0x01   //�����˿���

#define PROPERTY_ADDR_NODE_ID_CONF         0x0202 //NODE ID����
#define PROPERTY_GROUP_NODE_ID_CONF        0x02   //NODE ID����
#define PROPERTY_INDEX_NODE_ID_CONF        0x02   //NODE ID����

#define PROPERTY_ADDR_TXPKT_CONF           0x0203 //�������ݰ�����
#define PROPERTY_GROUP_TXPKT_CONF          0x02   //�������ݰ�����
#define PROPERTY_INDEX_TXPKT_CONF          0x03   //�������ݰ�����

#define PROPERTY_ADDR_RXPKT_CONF           0x0204 //�������ݰ�����
#define PROPERTY_GROUP_RXPKT_CONF          0x02   //�������ݰ�����
#define PROPERTY_INDEX_RXPKT_CONF          0x04   //�������ݰ�����

#define PROPERTY_ADDR_RX_LENGTH_IN_PACKET  0x0205 //���ݰ��еĳ����ֶ�
#define PROPERTY_GROUP_RX_LENGTH_IN_PACKET 0x02   //���ݰ��еĳ����ֶ�
#define PROPERTY_INDEX_RX_LENGTH_IN_PACKET 0x05   //���ݰ��еĳ����ֶ�

#define PROPERTY_ADDR_RX_LENGTH_IN_FIFO    0x0207 //host���Դ�FIFO��ȡ�����ݳ���
#define PROPERTY_GROUP_RX_LENGTH_IN_FIFO   0x02   //host���Դ�FIFO��ȡ�����ݳ���
#define PROPERTY_INDEX_RX_LENGTH_IN_FIFO   0x07   //host���Դ�FIFO��ȡ�����ݳ���

#define PROPERTY_ADDR_RX_ACK_BYTE          0x0209 //����ACK�����ֽ�
#define PROPERTY_GROUP_RX_ACK_BYTE         0x02   //����ACK�����ֽ�
#define PROPERTY_INDEX_RX_ACK_BYTE         0x09   //����ACK�����ֽ�


/***************************************************************************************************
 * GROUP3 INDEX ����
 **************************************************************************************************/
#define PROPERTY_ADDR_ACK_TIMEOUT             0x0300 //ACK���ճ�ʱʱ��us
#define PROPERTY_GROUP_ACK_TIMEOUT            0x03   //ACK���ճ�ʱʱ��us
#define PROPERTY_INDEX_ACK_TIMEOUT            0x00   //ACK���ճ�ʱʱ��us

#define PROPERTY_ADDR_RX_TIMEOUT              0x0304 //���ճ�ʱʱ��us
#define PROPERTY_GROUP_RX_TIMEOUT             0x03   //���ճ�ʱʱ��us
#define PROPERTY_INDEX_RX_TIMEOUT             0x04   //���ճ�ʱʱ��us

#define PROPERTY_ADDR_SLEEP_BASE              0x0308 //���߻���ʱ�䵥λ
#define PROPERTY_GROUP_SLEEP_BASE             0x03   //���߻���ʱ�䵥λ
#define PROPERTY_INDEX_SLEEP_BASE             0x08   //���߻���ʱ�䵥λ

#define PROPERTY_ADDR_SLEEP_REPEAT            0x030b //�����ظ�����
#define PROPERTY_GROUP_SLEEP_REPEAT           0x03   //�����ظ�����
#define PROPERTY_INDEX_SLEEP_REPEAT           0x0b   //�����ظ�����

#define PROPERTY_ADDR_DUTY_CYCLE_BASE         0x030c //DutyCycle��׼ʱ��
#define PROPERTY_GROUP_DUTY_CYCLE_BASE        0x03   //DutyCycle��׼ʱ��
#define PROPERTY_INDEX_DUTY_CYCLE_BASE        0x0c   //DutyCycle��׼ʱ��

#define PROPERTY_ADDR_RCLTRIM_BASE            0x0310 //RCLУ׼������ʱ��λ
#define PROPERTY_GROUP_RCLTRIM_BASE           0x03   //RCLУ׼������ʱ��λ
#define PROPERTY_INDEX_RCLTRIM_BASE           0x10   //RCLУ׼������ʱ��λ

#define PROPERTY_ADDR_RCLTRIM_REPEAT          0x0311 //RCLУ׼��ʱ�ظ�����
#define PROPERTY_GROUP_RCLTRIM_REPEAT         0x03   //RCLУ׼��ʱ�ظ�����
#define PROPERTY_INDEX_RCLTRIM_REPEAT         0x11   //RCLУ׼��ʱ�ظ�����

#define PROPERTY_ADDR_PACKET_FILTER_MASK      0x0312 //����������
#define PROPERTY_GROUP_PACKET_FILTER_MASK     0x03   //����������
#define PROPERTY_INDEX_PACKET_FILTER_MASK     0x12   //����������

#define PROPERTY_ADDR_PACKET_FILTER_PAT1      0x0316 //����������1
#define PROPERTY_GROUP_PACKET_FILTER_PAT1     0x03   //����������1
#define PROPERTY_INDEX_PACKET_FILTER_PAT1     0x16   //����������1

#define PROPERTY_ADDR_PACKET_FILTER_PAT2      0x031a //����������2
#define PROPERTY_GROUP_PACKET_FILTER_PAT2     0x03   //����������2
#define PROPERTY_INDEX_PACKET_FILTER_PAT2     0x1a   //����������2

#define PROPERTY_ADDR_PACKET_FILTER_PAT3      0x031e //����������3
#define PROPERTY_GROUP_PACKET_FILTER_PAT3     0x03   //����������3
#define PROPERTY_INDEX_PACKET_FILTER_PAT3     0x1e   //����������3

#define PROPERTY_ADDR_RX_NODE_ID              0x0322 //����NODEID
#define PROPERTY_GROUP_RX_NODE_ID             0x03   //����NODEID
#define PROPERTY_INDEX_RX_NODE_ID             0x22   //����NODEID

#define PROPERTY_ADDR_RX_HEADER_CRC           0x0326 //NODEID��LENGTH���ֵ�CRC��ʹ���˼����ⲿ��CRC����Ч
#define PROPERTY_GROUP_RX_HEADER_CRC          0x03   //NODEID��LENGTH���ֵ�CRC��ʹ���˼����ⲿ��CRC����Ч
#define PROPERTY_INDEX_RX_HEADER_CRC          0x26   //NODEID��LENGTH���ֵ�CRC��ʹ���˼����ⲿ��CRC����Ч

#define PROPERTY_ADDR_TX_REPEAT_TIMES         0x032a //ÿ����������ʱ���ظ����ʹ���
#define PROPERTY_GROUP_TX_REPEAT_TIMES        0x03   //ÿ����������ʱ���ظ����ʹ���
#define PROPERTY_INDEX_TX_REPEAT_TIMES        0x2a   //ÿ����������ʱ���ظ����ʹ���

#define PROPERTY_ADDR_TX_PACKET_GAP           0x032b //���Ͱ�֮��ļ��ʱ�䣬��λus
#define PROPERTY_GROUP_TX_PACKET_GAP          0x03   //���Ͱ�֮��ļ��ʱ�䣬��λus
#define PROPERTY_INDEX_TX_PACKET_GAP          0x2b   //���Ͱ�֮��ļ��ʱ�䣬��λus

#define PROPERTY_ADDR_RX_TIMEOUT_EXIT_STATE   0x032d //���ճ�ʱʱ�˳�״̬
#define PROPERTY_GROUP_RX_TIMEOUT_EXIT_STATE  0x03   //���ճ�ʱʱ�˳�״̬
#define PROPERTY_INDEX_RX_TIMEOUT_EXIT_STATE  0x2d   //���ճ�ʱʱ�˳�״̬

#define PROPERTY_ADDR_RX_INVALID_EXIT_STATE   0x032e //�������ݲ��Ϸ���CRC ERROR��ʱ�˳�״̬
#define PROPERTY_GROUP_RX_INVALID_EXIT_STATE  0x03   //�������ݲ��Ϸ���CRC ERROR��ʱ�˳�״̬
#define PROPERTY_INDEX_RX_INVALID_EXIT_STATE  0x2e   //�������ݲ��Ϸ���CRC ERROR��ʱ�˳�״̬

#define PROPERTY_ADDR_RX_VALID_EXIT_STATE     0x032f //�������ݺϷ���RX DONE��ʱ�˳�״̬
#define PROPERTY_GROUP_RX_VALID_EXIT_STATE    0x03   //�������ݺϷ���RX DONE��ʱ�˳�״̬
#define PROPERTY_INDEX_RX_VALID_EXIT_STATE    0x2f   //�������ݺϷ���RX DONE��ʱ�˳�״̬

#define PROPERTY_ADDR_ACK_TIMEOUT_EXIT_STATE  0x0330 //����ACK��ʱʱ�˳�״̬
#define PROPERTY_GROUP_ACK_TIMEOUT_EXIT_STATE 0x03   //����ACK��ʱʱ�˳�״̬
#define PROPERTY_INDEX_ACK_TIMEOUT_EXIT_STATE 0x30   //����ACK��ʱʱ�˳�״̬

#define PROPERTY_ADDR_TX_OK_EXIT_STATE        0x0331 //���ͳɹ�ʱ�˳�״̬
#define PROPERTY_GROUP_TX_OK_EXIT_STATE       0x03   //���ͳɹ�ʱ�˳�״̬
#define PROPERTY_INDEX_TX_OK_EXIT_STATE       0x31   //���ͳɹ�ʱ�˳�״̬

#define PROPERTY_ADDR_ACK_ERROR_EXIT_STATE    0x0332 //ACK�����ֽ�У������˳�״�?
#define PROPERTY_GROUP_ACK_ERROR_EXIT_STATE   0x03   //ACK�����ֽ�У������˳�״�?
#define PROPERTY_INDEX_ACK_ERROR_EXIT_STATE   0x32   //ACK�����ֽ�У������˳�״�?

#define PROPERTY_ADDR_ACK_CHECK_BYTE          0x0333 //�������յ���ACK_BYTE����У��
#define PROPERTY_GROUP_ACK_CHECK_BYTE         0x03   //�������յ���ACK_BYTE����У��
#define PROPERTY_INDEX_ACK_CHECK_BYTE         0x33   //�������յ���ACK_BYTE����У��

#define PROPERTY_ADDR_TX_ACK_BYTE             0x0334 //����ACK�����ֽ�
#define PROPERTY_GROUP_TX_ACK_BYTE            0x03   //����ACK�����ֽ�
#define PROPERTY_INDEX_TX_ACK_BYTE            0x34   //����ACK�����ֽ�

#define PROPERTY_ADDR_ACK_TX_DELAY1           0x0335 //ACK�����Ӻ�ʱ��1����λ10us
#define PROPERTY_GROUP_ACK_TX_DELAY1          0x03   //ACK�����Ӻ�ʱ��1����λ10us
#define PROPERTY_INDEX_ACK_TX_DELAY1          0x35   //ACK�����Ӻ�ʱ��1����λ10us

#define PROPERTY_ADDR_ACK_TX_DELAY2           0x0336 //ACK�����Ӻ�ʱ��2����λus
#define PROPERTY_GROUP_ACK_TX_DELAY2          0x03   //ACK�����Ӻ�ʱ��2����λus
#define PROPERTY_INDEX_ACK_TX_DELAY2          0x36   //ACK�����Ӻ�ʱ��2����λus


/***************************************************************************************************
 * GROUP4 ����
 **************************************************************************************************/
#define PROPERTY_ADDR_R106                          (0x0400 | (0x106 - 0x106))
#define PROPERTY_GROUP_R106                         0x04
#define PROPERTY_INDEX_R106                         (0x106 - 0x106)

#define PROPERTY_POS_R106_REG_HAMMING_MODE          7
#define PROPERTY_MSK_R106_REG_HAMMING_MODE          (0x01 << PROPERTY_POS_R106_REG_HAMMING_MODE)

#define PROPERTY_POS_R106_REG_MBUS_MSB_OUT_SEL      6
#define PROPERTY_MSK_R106_REG_MBUS_MSB_OUT_SEL      (0x01 << PROPERTY_POS_R106_REG_MBUS_MSB_OUT_SEL)

#define PROPERTY_POS_R106_REG_INT_EN                5
#define PROPERTY_MSK_R106_REG_INT_EN                (0x01 << PROPERTY_POS_R106_REG_INT_EN)

#define PROPERTY_POS_R106_REG_FEC_TYPE              3
#define PROPERTY_MSK_R106_REG_FEC_TYPE              (0x03 << PROPERTY_POS_R106_REG_FEC_TYPE)

#define PROPERTY_POS_R106_REG_HAMMING_EN            2
#define PROPERTY_MSK_R106_REG_HAMMING_EN            (0x01 << PROPERTY_POS_R106_REG_HAMMING_EN)

#define PROPERTY_POS_R106_REG_AFC_VLD               1
#define PROPERTY_MSK_R106_REG_AFC_VLD               (0x01 << PROPERTY_POS_R106_REG_AFC_VLD)

#define PROPERTY_POS_R106_M802_CRC_MANUE            0
#define PROPERTY_MSK_R106_M802_CRC_MANUE            (0x01 << PROPERTY_POS_R106_M802_CRC_MANUE)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R107                          (0x0400 | (0x107 - 0x106))
#define PROPERTY_GROUP_R107                         0x04
#define PROPERTY_INDEX_R107                         (0x107 - 0x106)

#define PROPERTY_POS_R107_REG_DIRECT_RX_EN          7
#define PROPERTY_MSK_R107_REG_DIRECT_RX_EN          (0x01 << PROPERTY_POS_R107_REG_DIRECT_RX_EN)

#define PROPERTY_POS_R107_REG_DIRECT_TX_EN          6
#define PROPERTY_MSK_R107_REG_DIRECT_TX_EN          (0x01 << PROPERTY_POS_R107_REG_DIRECT_TX_EN)

#define PROPERTY_POS_R107_REG_DIRECT_MODE           5
#define PROPERTY_MSK_R107_REG_DIRECT_MODE           (0x01 << PROPERTY_POS_R107_REG_DIRECT_MODE)

#define PROPERTY_POS_R107_REG_PRE_BIT_MODE          4
#define PROPERTY_MSK_R107_REG_PRE_BIT_MODE          (0x01 << PROPERTY_POS_R107_REG_PRE_BIT_MODE)

#define PROPERTY_POS_R107_REG_PRE_SEL               2
#define PROPERTY_MSK_R107_REG_PRE_SEL               (0x03 << PROPERTY_POS_R107_REG_PRE_SEL)

#define PROPERTY_POS_R107_REG_PRE_MAN_MODE          1
#define PROPERTY_MSK_R107_REG_PRE_MAN_MODE          (0x01 << PROPERTY_POS_R107_REG_PRE_MAN_MODE)

#define PROPERTY_POS_R107_REG_PRE_MAN_EN            0
#define PROPERTY_MSK_R107_REG_PRE_MAN_EN            (0x01 << PROPERTY_POS_R107_REG_PRE_MAN_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R108_REG_PRE_PAT_L1           (0x0400 | (0x108 - 0x106))
#define PROPERTY_GROUP_R108_REG_PRE_PAT_L1          0x04
#define PROPERTY_INDEX_R108_REG_PRE_PAT_L1          (0x108 - 0x106)

#define PROPERTY_ADDR_R108                          (0x0400 | (0x108 - 0x106))
#define PROPERTY_GROUP_R108                         0x04
#define PROPERTY_INDEX_R108                         (0x108 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R109_REG_PRE_PAT_L2           (0x0400 | (0x109 - 0x106))
#define PROPERTY_GROUP_R109_REG_PRE_PAT_L2          0x04
#define PROPERTY_INDEX_R109_REG_PRE_PAT_L2          (0x109 - 0x106)

#define PROPERTY_ADDR_R109                          (0x0400 | (0x109 - 0x106))
#define PROPERTY_GROUP_R109                         0x04
#define PROPERTY_INDEX_R109                         (0x109 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R10A_REG_PRE_PAT_L3           (0x0400 | (0x10a - 0x106))
#define PROPERTY_GROUP_R10A_REG_PRE_PAT_L3          0x04
#define PROPERTY_INDEX_R10A_REG_PRE_PAT_L3          (0x10a - 0x106)

#define PROPERTY_ADDR_R10A                          (0x0400 | (0x10a - 0x106))
#define PROPERTY_GROUP_R10A                         0x04
#define PROPERTY_INDEX_R10A                         (0x10a - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R10B_REG_PRE_PAT_H            (0x0400 | (0x10b - 0x106))
#define PROPERTY_GROUP_R10B_REG_PRE_PAT_H           0x04
#define PROPERTY_INDEX_R10B_REG_PRE_PAT_H           (0x10b - 0x106)

#define PROPERTY_ADDR_R10B                          (0x0400 | (0x10b - 0x106))
#define PROPERTY_GROUP_R10B                         0x04
#define PROPERTY_INDEX_R10B                         (0x10b - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R10C_REG_PREAMBLE_LEN         (0x0400 | (0x10c - 0x106))
#define PROPERTY_GROUP_R10C_REG_PREAMBLE_LEN        0x04
#define PROPERTY_INDEX_R10C_REG_PREAMBLE_LEN        (0x10c - 0x106)

#define PROPERTY_ADDR_R10C                          (0x0400 | (0x10c - 0x106))
#define PROPERTY_GROUP_R10C                         0x04
#define PROPERTY_INDEX_R10C                         (0x10c - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R10D                          (0x0400 | (0x10d - 0x106))
#define PROPERTY_GROUP_R10D                         0x04
#define PROPERTY_INDEX_R10D                         (0x10d - 0x106)

#define PROPERTY_POS_R10D_REG_PAYLOAD_ENDIAN        7
#define PROPERTY_MSK_R10D_REG_PAYLOAD_ENDIAN        (0x01 << PROPERTY_POS_R10D_REG_PAYLOAD_ENDIAN)

#define PROPERTY_POS_R10D_REG_CRC_ENDIAN            6
#define PROPERTY_MSK_R10D_REG_CRC_ENDIAN            (0x01 << PROPERTY_POS_R10D_REG_CRC_ENDIAN)

#define PROPERTY_POS_R10D_REG_SYNC_BIT_MODE         5
#define PROPERTY_MSK_R10D_REG_SYNC_BIT_MODE         (0x01 << PROPERTY_POS_R10D_REG_SYNC_BIT_MODE)

#define PROPERTY_POS_R10D_REG_SYNC_MAN_MODE         4
#define PROPERTY_MSK_R10D_REG_SYNC_MAN_MODE         (0x01 << PROPERTY_POS_R10D_REG_SYNC_MAN_MODE)

#define PROPERTY_POS_R10D_REG_SYNC_MAN_EN           3
#define PROPERTY_MSK_R10D_REG_SYNC_MAN_EN           (0x01 << PROPERTY_POS_R10D_REG_SYNC_MAN_EN)

#define PROPERTY_POS_R10D_REG_SYNC_LEN              0
#define PROPERTY_MSK_R10D_REG_SYNC_LEN              (0x07 << PROPERTY_POS_R10D_REG_SYNC_LEN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R10E_REG_CRC_POLY_L1          (0x0400 | (0x10e - 0x106))
#define PROPERTY_GROUP_R10E_REG_CRC_POLY_L1         0x04
#define PROPERTY_INDEX_R10E_REG_CRC_POLY_L1         (0x10e - 0x106)

#define PROPERTY_ADDR_R10E                          (0x0400 | (0x10e - 0x106))
#define PROPERTY_GROUP_R10E                         0x04
#define PROPERTY_INDEX_R10E                         (0x10e - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R10F_REG_CRC_POLY_L2          (0x0400 | (0x10f - 0x106))
#define PROPERTY_GROUP_R10F_REG_CRC_POLY_L2         0x04
#define PROPERTY_INDEX_R10F_REG_CRC_POLY_L2         (0x10f - 0x106)

#define PROPERTY_ADDR_R10F                          (0x0400 | (0x10f - 0x106))
#define PROPERTY_GROUP_R10F                         0x04
#define PROPERTY_INDEX_R10F                         (0x10f - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R110_REG_CRC_POLY_L3          (0x0400 | (0x110 - 0x106))
#define PROPERTY_GROUP_R110_REG_CRC_POLY_L3         0x04
#define PROPERTY_INDEX_R110_REG_CRC_POLY_L3         (0x110 - 0x106)

#define PROPERTY_ADDR_R110                          (0x0400 | (0x110 - 0x106))
#define PROPERTY_GROUP_R110                         0x04
#define PROPERTY_INDEX_R110                         (0x110 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R111_REG_CRC_POLY_H           (0x0400 | (0x111 - 0x106))
#define PROPERTY_GROUP_R111_REG_CRC_POLY_H          0x04
#define PROPERTY_INDEX_R111_REG_CRC_POLY_H          (0x111 - 0x106)

#define PROPERTY_ADDR_R111                          (0x0400 | (0x111 - 0x106))
#define PROPERTY_GROUP_R111                         0x04
#define PROPERTY_INDEX_R111                         (0x111 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R112_REG_CRC_SEED_L1          (0x0400 | (0x112 - 0x106))
#define PROPERTY_GROUP_R112_REG_CRC_SEED_L1         0x04
#define PROPERTY_INDEX_R112_REG_CRC_SEED_L1         (0x112 - 0x106)

#define PROPERTY_ADDR_R112                          (0x0400 | (0x112 - 0x106))
#define PROPERTY_GROUP_R112                         0x04
#define PROPERTY_INDEX_R112                         (0x112 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R113_REG_CRC_SEED_L2          (0x0400 | (0x113 - 0x106))
#define PROPERTY_GROUP_R113_REG_CRC_SEED_L2         0x04
#define PROPERTY_INDEX_R113_REG_CRC_SEED_L2         (0x113 - 0x106)

#define PROPERTY_ADDR_R113                          (0x0400 | (0x113 - 0x106))
#define PROPERTY_GROUP_R113                         0x04
#define PROPERTY_INDEX_R113                         (0x113 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R114_REG_CRC_SEED_L3          (0x0400 | (0x114 - 0x106))
#define PROPERTY_GROUP_R114_REG_CRC_SEED_L3         0x04
#define PROPERTY_INDEX_R114_REG_CRC_SEED_L3         (0x114 - 0x106)

#define PROPERTY_ADDR_R114                          (0x0400 | (0x114 - 0x106))
#define PROPERTY_GROUP_R114                         0x04
#define PROPERTY_INDEX_R114                         (0x114 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R115_REG_CRC_SEED_H           (0x0400 | (0x115 - 0x106))
#define PROPERTY_GROUP_R115_REG_CRC_SEED_H          0x04
#define PROPERTY_INDEX_R115_REG_CRC_SEED_H          (0x115 - 0x106)

#define PROPERTY_ADDR_R115                          (0x0400 | (0x115 - 0x106))
#define PROPERTY_GROUP_R115                         0x04
#define PROPERTY_INDEX_R115                         (0x115 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R116                          (0x0400 | (0x116 - 0x106))
#define PROPERTY_GROUP_R116                         0x04
#define PROPERTY_INDEX_R116                         (0x116 - 0x106)

#define PROPERTY_POS_R116_REG_WHITEN_OUT_SEL        4
#define PROPERTY_MSK_R116_REG_WHITEN_OUT_SEL        (0x0f << PROPERTY_POS_R116_REG_WHITEN_OUT_SEL)

#define PROPERTY_POS_R116_REG_WHITEN_SEL            3
#define PROPERTY_MSK_R116_REG_WHITEN_SEL            (0x01 << PROPERTY_POS_R116_REG_WHITEN_SEL)

#define PROPERTY_POS_R116_REG_CRC_NOT_SEL           2
#define PROPERTY_MSK_R116_REG_CRC_NOT_SEL           (0x01 << PROPERTY_POS_R116_REG_CRC_NOT_SEL)

#define PROPERTY_POS_R116_REG_CRC_MODE              0
#define PROPERTY_MSK_R116_REG_CRC_MODE              (0x03 << PROPERTY_POS_R116_REG_CRC_MODE)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R117                          (0x0400 | (0x117 - 0x106))
#define PROPERTY_GROUP_R117                         0x04
#define PROPERTY_INDEX_R117                         (0x117 - 0x106)

#define PROPERTY_POS_R117_REG_WHITEN_XOR2_SEL       4
#define PROPERTY_MSK_R117_REG_WHITEN_XOR2_SEL       (0x0f << PROPERTY_POS_R117_REG_WHITEN_XOR2_SEL)

#define PROPERTY_POS_R117_REG_WHITEN_XOR1_SEL       0
#define PROPERTY_MSK_R117_REG_WHITEN_XOR1_SEL       (0x0f << PROPERTY_POS_R117_REG_WHITEN_XOR1_SEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R118_REG_WHITEN_SEED_L        (0x0400 | (0x118 - 0x106))
#define PROPERTY_GROUP_R118_REG_WHITEN_SEED_L       0x04
#define PROPERTY_INDEX_R118_REG_WHITEN_SEED_L       (0x118 - 0x106)

#define PROPERTY_ADDR_R118                          (0x0400 | (0x118 - 0x106))
#define PROPERTY_GROUP_R118                         0x04
#define PROPERTY_INDEX_R118                         (0x118 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R119_REG_WHITEN_SEED_H        (0x0400 | (0x119 - 0x106))
#define PROPERTY_GROUP_R119_REG_WHITEN_SEED_H       0x04
#define PROPERTY_INDEX_R119_REG_WHITEN_SEED_H       (0x119 - 0x106)

#define PROPERTY_ADDR_R119                          (0x0400 | (0x119 - 0x106))
#define PROPERTY_GROUP_R119                         0x04
#define PROPERTY_INDEX_R119                         (0x119 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R11A                          (0x0400 | (0x11a - 0x106))
#define PROPERTY_GROUP_R11A                         0x04
#define PROPERTY_INDEX_R11A                         (0x11a - 0x106)

#define PROPERTY_POS_R11A_REG_WHITEN_PN13_SEL       7
#define PROPERTY_MSK_R11A_REG_WHITEN_PN13_SEL       (0x01 << PROPERTY_POS_R11A_REG_WHITEN_PN13_SEL)

#define PROPERTY_POS_R11A_M802_PHR_MODE             6
#define PROPERTY_MSK_R11A_M802_PHR_MODE             (0x01 << PROPERTY_POS_R11A_M802_PHR_MODE)

#define PROPERTY_POS_R11A_REG_PAYLOAD_SEL           5
#define PROPERTY_MSK_R11A_REG_PAYLOAD_SEL           (0x01 << PROPERTY_POS_R11A_REG_PAYLOAD_SEL)

#define PROPERTY_POS_R11A_REG_PL_MAN_MODE           4
#define PROPERTY_MSK_R11A_REG_PL_MAN_MODE           (0x01 << PROPERTY_POS_R11A_REG_PL_MAN_MODE)

#define PROPERTY_POS_R11A_REG_WHITEN_LENGTH         0
#define PROPERTY_MSK_R11A_REG_WHITEN_LENGTH         (0x0f << PROPERTY_POS_R11A_REG_WHITEN_LENGTH)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R11B                          (0x0400 | (0x11b - 0x106))
#define PROPERTY_GROUP_R11B                         0x04
#define PROPERTY_INDEX_R11B                         (0x11b - 0x106)

#define PROPERTY_POS_R11B_REG_VIA_LENGTH_LEN        7
#define PROPERTY_MSK_R11B_REG_VIA_LENGTH_LEN        (0x01 << PROPERTY_POS_R11B_REG_VIA_LENGTH_LEN)

#define PROPERTY_POS_R11B_REG_M802_FCS              6
#define PROPERTY_MSK_R11B_REG_M802_FCS              (0x01 << PROPERTY_POS_R11B_REG_M802_FCS)

#define PROPERTY_POS_R11B_REG_NODE_MODE             5
#define PROPERTY_MSK_R11B_REG_NODE_MODE             (0x01 << PROPERTY_POS_R11B_REG_NODE_MODE)

#define PROPERTY_POS_R11B_REG_NODE_LENGTH           2
#define PROPERTY_MSK_R11B_REG_NODE_LENGTH           (0x07 << PROPERTY_POS_R11B_REG_NODE_LENGTH)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R11C_REG_NODE_ID_L1           (0x0400 | (0x11c - 0x106))
#define PROPERTY_GROUP_R11C_REG_NODE_ID_L1          0x04
#define PROPERTY_INDEX_R11C_REG_NODE_ID_L1          (0x11c - 0x106)

#define PROPERTY_ADDR_R11C                          (0x0400 | (0x11c - 0x106))
#define PROPERTY_GROUP_R11C                         0x04
#define PROPERTY_INDEX_R11C                         (0x11c - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R11D_REG_NODE_ID_L2           (0x0400 | (0x11d - 0x106))
#define PROPERTY_GROUP_R11D_REG_NODE_ID_L2          0x04
#define PROPERTY_INDEX_R11D_REG_NODE_ID_L2          (0x11d - 0x106)

#define PROPERTY_ADDR_R11D                          (0x0400 | (0x11d - 0x106))
#define PROPERTY_GROUP_R11D                         0x04
#define PROPERTY_INDEX_R11D                         (0x11d - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R11E_REG_NODE_ID_L3           (0x0400 | (0x11e - 0x106))
#define PROPERTY_GROUP_R11E_REG_NODE_ID_L3          0x04
#define PROPERTY_INDEX_R11E_REG_NODE_ID_L3          (0x11e - 0x106)

#define PROPERTY_ADDR_R11E                          (0x0400 | (0x11e - 0x106))
#define PROPERTY_GROUP_R11E                         0x04
#define PROPERTY_INDEX_R11E                         (0x11e - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R11F_REG_NODE_ID_H            (0x0400 | (0x11f - 0x106))
#define PROPERTY_GROUP_R11F_REG_NODE_ID_H           0x04
#define PROPERTY_INDEX_R11F_REG_NODE_ID_H           (0x11f - 0x106)

#define PROPERTY_ADDR_R11F                          (0x0400 | (0x11f - 0x106))
#define PROPERTY_GROUP_R11F                         0x04
#define PROPERTY_INDEX_R11F                         (0x11f - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R120                          (0x0400 | (0x120 - 0x106))
#define PROPERTY_GROUP_R120                         0x04
#define PROPERTY_INDEX_R120                         (0x120 - 0x106)

#define PROPERTY_POS_R120_REG_VIA_CRC_MODE          7
#define PROPERTY_MSK_R120_REG_VIA_CRC_MODE          (0x01 << PROPERTY_POS_R120_REG_VIA_CRC_MODE)

#define PROPERTY_POS_R120_REG_POSTAMBLE_LEN         0
#define PROPERTY_MSK_R120_REG_POSTAMBLE_LEN         (0x7f << PROPERTY_POS_R120_REG_POSTAMBLE_LEN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R121_REG_POST_PAT_L1          (0x0400 | (0x121 - 0x106))
#define PROPERTY_GROUP_R121_REG_POST_PAT_L1         0x04
#define PROPERTY_INDEX_R121_REG_POST_PAT_L1         (0x121 - 0x106)

#define PROPERTY_ADDR_R121                          (0x0400 | (0x121 - 0x106))
#define PROPERTY_GROUP_R121                         0x04
#define PROPERTY_INDEX_R121                         (0x121 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R122_REG_POST_PAT_L2          (0x0400 | (0x122 - 0x106))
#define PROPERTY_GROUP_R122_REG_POST_PAT_L2         0x04
#define PROPERTY_INDEX_R122_REG_POST_PAT_L2         (0x122 - 0x106)

#define PROPERTY_ADDR_R122                          (0x0400 | (0x122 - 0x106))
#define PROPERTY_GROUP_R122                         0x04
#define PROPERTY_INDEX_R122                         (0x122 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R123_REG_POST_PAT_L3          (0x0400 | (0x123 - 0x106))
#define PROPERTY_GROUP_R123_REG_POST_PAT_L3         0x04
#define PROPERTY_INDEX_R123_REG_POST_PAT_L3         (0x123 - 0x106)

#define PROPERTY_ADDR_R123                          (0x0400 | (0x123 - 0x106))
#define PROPERTY_GROUP_R123                         0x04
#define PROPERTY_INDEX_R123                         (0x123 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R124_REG_POST_PAT_H           (0x0400 | (0x124 - 0x106))
#define PROPERTY_GROUP_R124_REG_POST_PAT_H          0x04
#define PROPERTY_INDEX_R124_REG_POST_PAT_H          (0x124 - 0x106)

#define PROPERTY_ADDR_R124                          (0x0400 | (0x124 - 0x106))
#define PROPERTY_GROUP_R124                         0x04
#define PROPERTY_INDEX_R124                         (0x124 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R125                          (0x0400 | (0x125 - 0x106))
#define PROPERTY_GROUP_R125                         0x04
#define PROPERTY_INDEX_R125                         (0x125 - 0x106)

#define PROPERTY_POS_R125_REG_POST_BIT_MODE         1
#define PROPERTY_MSK_R125_REG_POST_BIT_MODE         (0x01 << PROPERTY_POS_R125_REG_POST_BIT_MODE)

#define PROPERTY_POS_R125_REG_POST_EN               0
#define PROPERTY_MSK_R125_REG_POST_EN               (0x01 << PROPERTY_POS_R125_REG_POST_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R126                          (0x0400 | (0x126 - 0x106))
#define PROPERTY_GROUP_R126                         0x04
#define PROPERTY_INDEX_R126                         (0x126 - 0x106)

#define PROPERTY_POS_R126_REG_BUF_SIZE_SEL          7
#define PROPERTY_MSK_R126_REG_BUF_SIZE_SEL          (0x01 << PROPERTY_POS_R126_REG_BUF_SIZE_SEL)

#define PROPERTY_POS_R126_REG_BUF_SIZE              0
#define PROPERTY_MSK_R126_REG_BUF_SIZE              (0x7f << PROPERTY_POS_R126_REG_BUF_SIZE)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R12B                          (0x0400 | (0x12b - 0x106))
#define PROPERTY_GROUP_R12B                         0x04
#define PROPERTY_INDEX_R12B                         (0x12b - 0x106)

#define PROPERTY_POS_R12B_NRNSC_NOT_SEL             7
#define PROPERTY_MSK_R12B_NRNSC_NOT_SEL             (0x01 << PROPERTY_POS_R12B_NRNSC_NOT_SEL)

#define PROPERTY_POS_R12B_CRC_BYTE_ENDIAN           6
#define PROPERTY_MSK_R12B_CRC_BYTE_ENDIAN           (0x01 << PROPERTY_POS_R12B_CRC_BYTE_ENDIAN)

#define PROPERTY_POS_R12B_REG_VIA_LEN_ENDIAN        5
#define PROPERTY_MSK_R12B_REG_VIA_LEN_ENDIAN        (0x01 << PROPERTY_POS_R12B_REG_VIA_LEN_ENDIAN)

#define PROPERTY_POS_R12B_REG_WHITEN_PN9_SEL        4
#define PROPERTY_MSK_R12B_REG_WHITEN_PN9_SEL        (0x01 << PROPERTY_POS_R12B_REG_WHITEN_PN9_SEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R12C                          (0x0400 | (0x12c - 0x106))
#define PROPERTY_GROUP_R12C                         0x04
#define PROPERTY_INDEX_R12C                         (0x12c - 0x106)

#define PROPERTY_POS_R12C_REG_DEV_MODE              6
#define PROPERTY_MSK_R12C_REG_DEV_MODE              (0x03 << PROPERTY_POS_R12C_REG_DEV_MODE)

#define PROPERTY_POS_R12C_REG_VIA_FIELD_NUM         3
#define PROPERTY_MSK_R12C_REG_VIA_FIELD_NUM         (0x07 << PROPERTY_POS_R12C_REG_VIA_FIELD_NUM)

#define PROPERTY_POS_R12C_REG_LENGTH_FIELD_NUM      0
#define PROPERTY_MSK_R12C_REG_LENGTH_FIELD_NUM      (0x07 << PROPERTY_POS_R12C_REG_LENGTH_FIELD_NUM)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R12D                          (0x0400 | (0x12d - 0x106))
#define PROPERTY_GROUP_R12D                         0x04
#define PROPERTY_INDEX_R12D                         (0x12d - 0x106)

#define PROPERTY_POS_R12D_VIA_MFIELD_EN             3
#define PROPERTY_MSK_R12D_VIA_MFIELD_EN             (0x01 << PROPERTY_POS_R12D_VIA_MFIELD_EN)

#define PROPERTY_POS_R12D_FIELD_NUM                 0
#define PROPERTY_MSK_R12D_FIELD_NUM                 (0x07 << PROPERTY_POS_R12D_FIELD_NUM)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R12E                          (0x0400 | (0x12e - 0x106))
#define PROPERTY_GROUP_R12E                         0x04
#define PROPERTY_INDEX_R12E                         (0x12e - 0x106)

#define PROPERTY_POS_R12E_FIELD1_MAN_EN             5
#define PROPERTY_MSK_R12E_FIELD1_MAN_EN             (0x01 << PROPERTY_POS_R12E_FIELD1_MAN_EN)

#define PROPERTY_POS_R12E_FIELD1_CRC_IN             4
#define PROPERTY_MSK_R12E_FIELD1_CRC_IN             (0x01 << PROPERTY_POS_R12E_FIELD1_CRC_IN)

#define PROPERTY_POS_R12E_FIELD1_CRC_EN             3
#define PROPERTY_MSK_R12E_FIELD1_CRC_EN             (0x01 << PROPERTY_POS_R12E_FIELD1_CRC_EN)

#define PROPERTY_POS_R12E_FIELD1_CRC_SET            2
#define PROPERTY_MSK_R12E_FIELD1_CRC_SET            (0x01 << PROPERTY_POS_R12E_FIELD1_CRC_SET)

#define PROPERTY_POS_R12E_FIELD1_WHITE_EN           1
#define PROPERTY_MSK_R12E_FIELD1_WHITE_EN           (0x01 << PROPERTY_POS_R12E_FIELD1_WHITE_EN)

#define PROPERTY_POS_R12E_FIELD1_WHITE_SET          0
#define PROPERTY_MSK_R12E_FIELD1_WHITE_SET          (0x01 << PROPERTY_POS_R12E_FIELD1_WHITE_SET)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R12F_FIELD2_LENGTH_L          (0x0400 | (0x12f - 0x106))
#define PROPERTY_GROUP_R12F_FIELD2_LENGTH_L         0x04
#define PROPERTY_INDEX_R12F_FIELD2_LENGTH_L         (0x12f - 0x106)

#define PROPERTY_ADDR_R12F                          (0x0400 | (0x12f - 0x106))
#define PROPERTY_GROUP_R12F                         0x04
#define PROPERTY_INDEX_R12F                         (0x12f - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R130_FIELD2_LENGTH_H          (0x0400 | (0x130 - 0x106))
#define PROPERTY_GROUP_R130_FIELD2_LENGTH_H         0x04
#define PROPERTY_INDEX_R130_FIELD2_LENGTH_H         (0x130 - 0x106)

#define PROPERTY_ADDR_R130                          (0x0400 | (0x130 - 0x106))
#define PROPERTY_GROUP_R130                         0x04
#define PROPERTY_INDEX_R130                         (0x130 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R131                          (0x0400 | (0x131 - 0x106))
#define PROPERTY_GROUP_R131                         0x04
#define PROPERTY_INDEX_R131                         (0x131 - 0x106)

#define PROPERTY_POS_R131_FIELD2_MAN_EN             5
#define PROPERTY_MSK_R131_FIELD2_MAN_EN             (0x01 << PROPERTY_POS_R131_FIELD2_MAN_EN)

#define PROPERTY_POS_R131_FIELD2_CRC_IN             4
#define PROPERTY_MSK_R131_FIELD2_CRC_IN             (0x01 << PROPERTY_POS_R131_FIELD2_CRC_IN)

#define PROPERTY_POS_R131_FIELD2_CRC_EN             3
#define PROPERTY_MSK_R131_FIELD2_CRC_EN             (0x01 << PROPERTY_POS_R131_FIELD2_CRC_EN)

#define PROPERTY_POS_R131_FIELD2_CRC_SET            2
#define PROPERTY_MSK_R131_FIELD2_CRC_SET            (0x01 << PROPERTY_POS_R131_FIELD2_CRC_SET)

#define PROPERTY_POS_R131_FIELD2_WHITE_EN           1
#define PROPERTY_MSK_R131_FIELD2_WHITE_EN           (0x01 << PROPERTY_POS_R131_FIELD2_WHITE_EN)

#define PROPERTY_POS_R131_FIELD2_WHITE_SET          0
#define PROPERTY_MSK_R131_FIELD2_WHITE_SET          (0x01 << PROPERTY_POS_R131_FIELD2_WHITE_SET)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R132_FIELD3_LENGTH_L          (0x0400 | (0x132 - 0x106))
#define PROPERTY_GROUP_R132_FIELD3_LENGTH_L         0x04
#define PROPERTY_INDEX_R132_FIELD3_LENGTH_L         (0x132 - 0x106)

#define PROPERTY_ADDR_R132                          (0x0400 | (0x132 - 0x106))
#define PROPERTY_GROUP_R132                         0x04
#define PROPERTY_INDEX_R132                         (0x132 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R133_FIELD3_LENGTH_H          (0x0400 | (0x133 - 0x106))
#define PROPERTY_GROUP_R133_FIELD3_LENGTH_H         0x04
#define PROPERTY_INDEX_R133_FIELD3_LENGTH_H         (0x133 - 0x106)

#define PROPERTY_ADDR_R133                          (0x0400 | (0x133 - 0x106))
#define PROPERTY_GROUP_R133                         0x04
#define PROPERTY_INDEX_R133                         (0x133 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R134                          (0x0400 | (0x134 - 0x106))
#define PROPERTY_GROUP_R134                         0x04
#define PROPERTY_INDEX_R134                         (0x134 - 0x106)

#define PROPERTY_POS_R134_FIELD3_MAN_EN             5
#define PROPERTY_MSK_R134_FIELD3_MAN_EN             (0x01 << PROPERTY_POS_R134_FIELD3_MAN_EN)

#define PROPERTY_POS_R134_FIELD3_CRC_IN             4
#define PROPERTY_MSK_R134_FIELD3_CRC_IN             (0x01 << PROPERTY_POS_R134_FIELD3_CRC_IN)

#define PROPERTY_POS_R134_FIELD3_CRC_EN             3
#define PROPERTY_MSK_R134_FIELD3_CRC_EN             (0x01 << PROPERTY_POS_R134_FIELD3_CRC_EN)

#define PROPERTY_POS_R134_FIELD3_CRC_SET            2
#define PROPERTY_MSK_R134_FIELD3_CRC_SET            (0x01 << PROPERTY_POS_R134_FIELD3_CRC_SET)

#define PROPERTY_POS_R134_FIELD3_WHITE_EN           1
#define PROPERTY_MSK_R134_FIELD3_WHITE_EN           (0x01 << PROPERTY_POS_R134_FIELD3_WHITE_EN)

#define PROPERTY_POS_R134_FIELD3_WHITE_SET          0
#define PROPERTY_MSK_R134_FIELD3_WHITE_SET          (0x01 << PROPERTY_POS_R134_FIELD3_WHITE_SET)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R135_FIELD4_LENGTH_L          (0x0400 | (0x135 - 0x106))
#define PROPERTY_GROUP_R135_FIELD4_LENGTH_L         0x04
#define PROPERTY_INDEX_R135_FIELD4_LENGTH_L         (0x135 - 0x106)

#define PROPERTY_ADDR_R135                          (0x0400 | (0x135 - 0x106))
#define PROPERTY_GROUP_R135                         0x04
#define PROPERTY_INDEX_R135                         (0x135 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R136_FIELD4_LENGTH_H          (0x0400 | (0x136 - 0x106))
#define PROPERTY_GROUP_R136_FIELD4_LENGTH_H         0x04
#define PROPERTY_INDEX_R136_FIELD4_LENGTH_H         (0x136 - 0x106)

#define PROPERTY_ADDR_R136                          (0x0400 | (0x136 - 0x106))
#define PROPERTY_GROUP_R136                         0x04
#define PROPERTY_INDEX_R136                         (0x136 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R137                          (0x0400 | (0x137 - 0x106))
#define PROPERTY_GROUP_R137                         0x04
#define PROPERTY_INDEX_R137                         (0x137 - 0x106)

#define PROPERTY_POS_R137_FIELD4_MAN_EN             5
#define PROPERTY_MSK_R137_FIELD4_MAN_EN             (0x01 << PROPERTY_POS_R137_FIELD4_MAN_EN)

#define PROPERTY_POS_R137_FIELD4_CRC_IN             4
#define PROPERTY_MSK_R137_FIELD4_CRC_IN             (0x01 << PROPERTY_POS_R137_FIELD4_CRC_IN)

#define PROPERTY_POS_R137_FIELD4_CRC_EN             3
#define PROPERTY_MSK_R137_FIELD4_CRC_EN             (0x01 << PROPERTY_POS_R137_FIELD4_CRC_EN)

#define PROPERTY_POS_R137_FIELD4_CRC_SET            2
#define PROPERTY_MSK_R137_FIELD4_CRC_SET            (0x01 << PROPERTY_POS_R137_FIELD4_CRC_SET)

#define PROPERTY_POS_R137_FIELD4_WHITE_EN           1
#define PROPERTY_MSK_R137_FIELD4_WHITE_EN           (0x01 << PROPERTY_POS_R137_FIELD4_WHITE_EN)

#define PROPERTY_POS_R137_FIELD4_WHITE_SET          0
#define PROPERTY_MSK_R137_FIELD4_WHITE_SET          (0x01 << PROPERTY_POS_R137_FIELD4_WHITE_SET)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R138_FIELD5_LENGTH_L          (0x0400 | (0x138 - 0x106))
#define PROPERTY_GROUP_R138_FIELD5_LENGTH_L         0x04
#define PROPERTY_INDEX_R138_FIELD5_LENGTH_L         (0x138 - 0x106)

#define PROPERTY_ADDR_R138                          (0x0400 | (0x138 - 0x106))
#define PROPERTY_GROUP_R138                         0x04
#define PROPERTY_INDEX_R138                         (0x138 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R139                          (0x0400 | (0x139 - 0x106))
#define PROPERTY_GROUP_R139                         0x04
#define PROPERTY_INDEX_R139                         (0x139 - 0x106)

#define PROPERTY_POS_R139_SYNC_4FSK_MODE            7
#define PROPERTY_MSK_R139_SYNC_4FSK_MODE            (0x01 << PROPERTY_POS_R139_SYNC_4FSK_MODE)

#define PROPERTY_POS_R139_SET_MODE                  6
#define PROPERTY_MSK_R139_SET_MODE                  (0x01 << PROPERTY_POS_R139_SET_MODE)

#define PROPERTY_POS_R139_FIELD5_LENGTH_H           0
#define PROPERTY_MSK_R139_FIELD5_LENGTH_H           (0x3f << PROPERTY_POS_R139_FIELD5_LENGTH_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R13A                          (0x0400 | (0x13a - 0x106))
#define PROPERTY_GROUP_R13A                         0x04
#define PROPERTY_INDEX_R13A                         (0x13a - 0x106)

#define PROPERTY_POS_R13A_FIELD5_MAN_EN             5
#define PROPERTY_MSK_R13A_FIELD5_MAN_EN             (0x01 << PROPERTY_POS_R13A_FIELD5_MAN_EN)

#define PROPERTY_POS_R13A_FIELD5_CRC_IN             4
#define PROPERTY_MSK_R13A_FIELD5_CRC_IN             (0x01 << PROPERTY_POS_R13A_FIELD5_CRC_IN)

#define PROPERTY_POS_R13A_FIELD5_CRC_EN             3
#define PROPERTY_MSK_R13A_FIELD5_CRC_EN             (0x01 << PROPERTY_POS_R13A_FIELD5_CRC_EN)

#define PROPERTY_POS_R13A_FIELD5_CRC_SET            2
#define PROPERTY_MSK_R13A_FIELD5_CRC_SET            (0x01 << PROPERTY_POS_R13A_FIELD5_CRC_SET)

#define PROPERTY_POS_R13A_FIELD5_WHITE_EN           1
#define PROPERTY_MSK_R13A_FIELD5_WHITE_EN           (0x01 << PROPERTY_POS_R13A_FIELD5_WHITE_EN)

#define PROPERTY_POS_R13A_FIELD5_WHITE_SET          0
#define PROPERTY_MSK_R13A_FIELD5_WHITE_SET          (0x01 << PROPERTY_POS_R13A_FIELD5_WHITE_SET)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R13B_REG_DRIFT_SPEED_L        (0x0400 | (0x13b - 0x106))
#define PROPERTY_GROUP_R13B_REG_DRIFT_SPEED_L       0x04
#define PROPERTY_INDEX_R13B_REG_DRIFT_SPEED_L       (0x13b - 0x106)

#define PROPERTY_ADDR_R13B                          (0x0400 | (0x13b - 0x106))
#define PROPERTY_GROUP_R13B                         0x04
#define PROPERTY_INDEX_R13B                         (0x13b - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R13C_REG_DRIFT_SPEED_H        (0x0400 | (0x13c - 0x106))
#define PROPERTY_GROUP_R13C_REG_DRIFT_SPEED_H       0x04
#define PROPERTY_INDEX_R13C_REG_DRIFT_SPEED_H       (0x13c - 0x106)

#define PROPERTY_ADDR_R13C                          (0x0400 | (0x13c - 0x106))
#define PROPERTY_GROUP_R13C                         0x04
#define PROPERTY_INDEX_R13C                         (0x13c - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R13D_REG_FLTR_DEV_L           (0x0400 | (0x13d - 0x106))
#define PROPERTY_GROUP_R13D_REG_FLTR_DEV_L          0x04
#define PROPERTY_INDEX_R13D_REG_FLTR_DEV_L          (0x13d - 0x106)

#define PROPERTY_ADDR_R13D                          (0x0400 | (0x13d - 0x106))
#define PROPERTY_GROUP_R13D                         0x04
#define PROPERTY_INDEX_R13D                         (0x13d - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R13E                          (0x0400 | (0x13e - 0x106))
#define PROPERTY_GROUP_R13E                         0x04
#define PROPERTY_INDEX_R13E                         (0x13e - 0x106)

#define PROPERTY_POS_R13E_ADC_CLK_INV               7
#define PROPERTY_MSK_R13E_ADC_CLK_INV               (0x01 << PROPERTY_POS_R13E_ADC_CLK_INV)

#define PROPERTY_POS_R13E_REG_SYNC_WORD2_EN         5
#define PROPERTY_MSK_R13E_REG_SYNC_WORD2_EN         (0x01 << PROPERTY_POS_R13E_REG_SYNC_WORD2_EN)

#define PROPERTY_POS_R13E_REG_FLTR_DEV_H            0
#define PROPERTY_MSK_R13E_REG_FLTR_DEV_H            (0x01 << PROPERTY_POS_R13E_REG_FLTR_DEV_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R13F_REG_MAX_AFC_FREQ_L       (0x0400 | (0x13f - 0x106))
#define PROPERTY_GROUP_R13F_REG_MAX_AFC_FREQ_L      0x04
#define PROPERTY_INDEX_R13F_REG_MAX_AFC_FREQ_L      (0x13f - 0x106)

#define PROPERTY_ADDR_R13F                          (0x0400 | (0x13f - 0x106))
#define PROPERTY_GROUP_R13F                         0x04
#define PROPERTY_INDEX_R13F                         (0x13f - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R140_REG_MAX_AFC_FREQ_H       (0x0400 | (0x140 - 0x106))
#define PROPERTY_GROUP_R140_REG_MAX_AFC_FREQ_H      0x04
#define PROPERTY_INDEX_R140_REG_MAX_AFC_FREQ_H      (0x140 - 0x106)

#define PROPERTY_ADDR_R140                          (0x0400 | (0x140 - 0x106))
#define PROPERTY_GROUP_R140                         0x04
#define PROPERTY_INDEX_R140                         (0x140 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R141_REG_AFC_FLS_TH           (0x0400 | (0x141 - 0x106))
#define PROPERTY_GROUP_R141_REG_AFC_FLS_TH          0x04
#define PROPERTY_INDEX_R141_REG_AFC_FLS_TH          (0x141 - 0x106)

#define PROPERTY_ADDR_R141                          (0x0400 | (0x141 - 0x106))
#define PROPERTY_GROUP_R141                         0x04
#define PROPERTY_INDEX_R141                         (0x141 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R142_REG_FSK_DEV              (0x0400 | (0x142 - 0x106))
#define PROPERTY_GROUP_R142_REG_FSK_DEV             0x04
#define PROPERTY_INDEX_R142_REG_FSK_DEV             (0x142 - 0x106)

#define PROPERTY_ADDR_R142                          (0x0400 | (0x142 - 0x106))
#define PROPERTY_GROUP_R142                         0x04
#define PROPERTY_INDEX_R142                         (0x142 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R143_REG_FSK_DEV_INNER        (0x0400 | (0x143 - 0x106))
#define PROPERTY_GROUP_R143_REG_FSK_DEV_INNER       0x04
#define PROPERTY_INDEX_R143_REG_FSK_DEV_INNER       (0x143 - 0x106)

#define PROPERTY_ADDR_R143                          (0x0400 | (0x143 - 0x106))
#define PROPERTY_GROUP_R143                         0x04
#define PROPERTY_INDEX_R143                         (0x143 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R144_REG_RX_4FSK_DEV_TH_L     (0x0400 | (0x144 - 0x106))
#define PROPERTY_GROUP_R144_REG_RX_4FSK_DEV_TH_L    0x04
#define PROPERTY_INDEX_R144_REG_RX_4FSK_DEV_TH_L    (0x144 - 0x106)

#define PROPERTY_ADDR_R144                          (0x0400 | (0x144 - 0x106))
#define PROPERTY_GROUP_R144                         0x04
#define PROPERTY_INDEX_R144                         (0x144 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R145_REG_RX_4FSK_DEV_TH_H     (0x0400 | (0x145 - 0x106))
#define PROPERTY_GROUP_R145_REG_RX_4FSK_DEV_TH_H    0x04
#define PROPERTY_INDEX_R145_REG_RX_4FSK_DEV_TH_H    (0x145 - 0x106)

#define PROPERTY_ADDR_R145                          (0x0400 | (0x145 - 0x106))
#define PROPERTY_GROUP_R145                         0x04
#define PROPERTY_INDEX_R145                         (0x145 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R146_REG_RX_TR_DEV_OUTER_L    (0x0400 | (0x146 - 0x106))
#define PROPERTY_GROUP_R146_REG_RX_TR_DEV_OUTER_L   0x04
#define PROPERTY_INDEX_R146_REG_RX_TR_DEV_OUTER_L   (0x146 - 0x106)

#define PROPERTY_ADDR_R146                          (0x0400 | (0x146 - 0x106))
#define PROPERTY_GROUP_R146                         0x04
#define PROPERTY_INDEX_R146                         (0x146 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R147_REG_RX_TR_DEV_OUTER_H    (0x0400 | (0x147 - 0x106))
#define PROPERTY_GROUP_R147_REG_RX_TR_DEV_OUTER_H   0x04
#define PROPERTY_INDEX_R147_REG_RX_TR_DEV_OUTER_H   (0x147 - 0x106)

#define PROPERTY_ADDR_R147                          (0x0400 | (0x147 - 0x106))
#define PROPERTY_GROUP_R147                         0x04
#define PROPERTY_INDEX_R147                         (0x147 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R148_REG_RX_TR_DEV_INNER_L    (0x0400 | (0x148 - 0x106))
#define PROPERTY_GROUP_R148_REG_RX_TR_DEV_INNER_L   0x04
#define PROPERTY_INDEX_R148_REG_RX_TR_DEV_INNER_L   (0x148 - 0x106)

#define PROPERTY_ADDR_R148                          (0x0400 | (0x148 - 0x106))
#define PROPERTY_GROUP_R148                         0x04
#define PROPERTY_INDEX_R148                         (0x148 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R149_REG_RX_TR_DEV_INNER_H    (0x0400 | (0x149 - 0x106))
#define PROPERTY_GROUP_R149_REG_RX_TR_DEV_INNER_H   0x04
#define PROPERTY_INDEX_R149_REG_RX_TR_DEV_INNER_H   (0x149 - 0x106)

#define PROPERTY_ADDR_R149                          (0x0400 | (0x149 - 0x106))
#define PROPERTY_GROUP_R149                         0x04
#define PROPERTY_INDEX_R149                         (0x149 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R14A_REG_FREQC_L              (0x0400 | (0x14a - 0x106))
#define PROPERTY_GROUP_R14A_REG_FREQC_L             0x04
#define PROPERTY_INDEX_R14A_REG_FREQC_L             (0x14a - 0x106)

#define PROPERTY_ADDR_R14A                          (0x0400 | (0x14a - 0x106))
#define PROPERTY_GROUP_R14A                         0x04
#define PROPERTY_INDEX_R14A                         (0x14a - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R14B                          (0x0400 | (0x14b - 0x106))
#define PROPERTY_GROUP_R14B                         0x04
#define PROPERTY_INDEX_R14B                         (0x14b - 0x106)

#define PROPERTY_POS_R14B_HIGH_DEV_DECIMAT_EN       6
#define PROPERTY_MSK_R14B_HIGH_DEV_DECIMAT_EN       (0x01 << PROPERTY_POS_R14B_HIGH_DEV_DECIMAT_EN)

#define PROPERTY_POS_R14B_HIGH_DEV_DECIMAT_NUM      2
#define PROPERTY_MSK_R14B_HIGH_DEV_DECIMAT_NUM      (0x0f << PROPERTY_POS_R14B_HIGH_DEV_DECIMAT_NUM)

#define PROPERTY_POS_R14B_REG_FREQC_H               0
#define PROPERTY_MSK_R14B_REG_FREQC_H               (0x03 << PROPERTY_POS_R14B_REG_FREQC_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R14C                          (0x0400 | (0x14c - 0x106))
#define PROPERTY_GROUP_R14C                         0x04
#define PROPERTY_INDEX_R14C                         (0x14c - 0x106)

#define PROPERTY_POS_R14C_REG_PA_OSIDE_EN           7
#define PROPERTY_MSK_R14C_REG_PA_OSIDE_EN           (0x01 << PROPERTY_POS_R14C_REG_PA_OSIDE_EN)

#define PROPERTY_POS_R14C_REG_PA_OSIDE_TIME         0
#define PROPERTY_MSK_R14C_REG_PA_OSIDE_TIME         (0x7f << PROPERTY_POS_R14C_REG_PA_OSIDE_TIME)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R14D                          (0x0400 | (0x14d - 0x106))
#define PROPERTY_GROUP_R14D                         0x04
#define PROPERTY_INDEX_R14D                         (0x14d - 0x106)

#define PROPERTY_POS_R14D_RX_ADC_IFSEL              5
#define PROPERTY_MSK_R14D_RX_ADC_IFSEL              (0x03 << PROPERTY_POS_R14D_RX_ADC_IFSEL)

#define PROPERTY_POS_R14D_RX_MIX_IQ_SEL             4
#define PROPERTY_MSK_R14D_RX_MIX_IQ_SEL             (0x01 << PROPERTY_POS_R14D_RX_MIX_IQ_SEL)

#define PROPERTY_POS_R14D_OCLK_500K_SEL             3
#define PROPERTY_MSK_R14D_OCLK_500K_SEL             (0x01 << PROPERTY_POS_R14D_OCLK_500K_SEL)

#define PROPERTY_POS_R14D_RX_TIA_CAPTUNE_SEL        2
#define PROPERTY_MSK_R14D_RX_TIA_CAPTUNE_SEL        (0x01 << PROPERTY_POS_R14D_RX_TIA_CAPTUNE_SEL)

#define PROPERTY_POS_R14D_PLL_VCO_TXCTK             0
#define PROPERTY_MSK_R14D_PLL_VCO_TXCTK             (0x03 << PROPERTY_POS_R14D_PLL_VCO_TXCTK)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R14E                          (0x0400 | (0x14e - 0x106))
#define PROPERTY_GROUP_R14E                         0x04
#define PROPERTY_INDEX_R14E                         (0x14e - 0x106)

#define PROPERTY_POS_R14E_RX_ADC_BWSEL              6
#define PROPERTY_MSK_R14E_RX_ADC_BWSEL              (0x03 << PROPERTY_POS_R14E_RX_ADC_BWSEL)

#define PROPERTY_POS_R14E_PA_2ND_RAMP               0
#define PROPERTY_MSK_R14E_PA_2ND_RAMP               (0x3f << PROPERTY_POS_R14E_PA_2ND_RAMP)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R14F_RX_ADC_CAPTUNE           (0x0400 | (0x14f - 0x106))
#define PROPERTY_GROUP_R14F_RX_ADC_CAPTUNE          0x04
#define PROPERTY_INDEX_R14F_RX_ADC_CAPTUNE          (0x14f - 0x106)

#define PROPERTY_ADDR_R14F                          (0x0400 | (0x14f - 0x106))
#define PROPERTY_GROUP_R14F                         0x04
#define PROPERTY_INDEX_R14F                         (0x14f - 0x106)

#define PROPERTY_POS_R14F_RX_ADC_CAPTUNE            0
#define PROPERTY_MSK_R14F_RX_ADC_CAPTUNE            (0x3f << PROPERTY_POS_R14F_RX_ADC_CAPTUNE)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R150                          (0x0400 | (0x150 - 0x106))
#define PROPERTY_GROUP_R150                         0x04
#define PROPERTY_INDEX_R150                         (0x150 - 0x106)

#define PROPERTY_POS_R150_REG_CHF_SEL               4
#define PROPERTY_MSK_R150_REG_CHF_SEL               (0x0f << PROPERTY_POS_R150_REG_CHF_SEL)

#define PROPERTY_POS_R150_OCLK_DIV_SEL              2
#define PROPERTY_MSK_R150_OCLK_DIV_SEL              (0x03 << PROPERTY_POS_R150_OCLK_DIV_SEL)

#define PROPERTY_POS_R150_OCLK_EN                   1
#define PROPERTY_MSK_R150_OCLK_EN                   (0x01 << PROPERTY_POS_R150_OCLK_EN)

#define PROPERTY_POS_R150_OCLK_SRC_SEL              0
#define PROPERTY_MSK_R150_OCLK_SRC_SEL              (0x01 << PROPERTY_POS_R150_OCLK_SRC_SEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R151_IF_L0                    (0x0400 | (0x151 - 0x106))
#define PROPERTY_GROUP_R151_IF_L0                   0x04
#define PROPERTY_INDEX_R151_IF_L0                   (0x151 - 0x106)

#define PROPERTY_ADDR_R151                          (0x0400 | (0x151 - 0x106))
#define PROPERTY_GROUP_R151                         0x04
#define PROPERTY_INDEX_R151                         (0x151 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R152_IF_L1                    (0x0400 | (0x152 - 0x106))
#define PROPERTY_GROUP_R152_IF_L1                   0x04
#define PROPERTY_INDEX_R152_IF_L1                   (0x152 - 0x106)

#define PROPERTY_ADDR_R152                          (0x0400 | (0x152 - 0x106))
#define PROPERTY_GROUP_R152                         0x04
#define PROPERTY_INDEX_R152                         (0x152 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R153                          (0x0400 | (0x153 - 0x106))
#define PROPERTY_GROUP_R153                         0x04
#define PROPERTY_INDEX_R153                         (0x153 - 0x106)

#define PROPERTY_POS_R153_REG_TX_CFG_MODE           6
#define PROPERTY_MSK_R153_REG_TX_CFG_MODE           (0x01 << PROPERTY_POS_R153_REG_TX_CFG_MODE)

#define PROPERTY_POS_R153_REG_RX_CFG_MODE           4
#define PROPERTY_MSK_R153_REG_RX_CFG_MODE           (0x03 << PROPERTY_POS_R153_REG_RX_CFG_MODE)

#define PROPERTY_POS_R153_IF_H                      0
#define PROPERTY_MSK_R153_IF_H                      (0x0f << PROPERTY_POS_R153_IF_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R154_REG_RX_TIMEOUT_L         (0x0400 | (0x154 - 0x106))
#define PROPERTY_GROUP_R154_REG_RX_TIMEOUT_L        0x04
#define PROPERTY_INDEX_R154_REG_RX_TIMEOUT_L        (0x154 - 0x106)

#define PROPERTY_ADDR_R154                          (0x0400 | (0x154 - 0x106))
#define PROPERTY_GROUP_R154                         0x04
#define PROPERTY_INDEX_R154                         (0x154 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R155_REG_RX_TIMEOUT_H         (0x0400 | (0x155 - 0x106))
#define PROPERTY_GROUP_R155_REG_RX_TIMEOUT_H        0x04
#define PROPERTY_INDEX_R155_REG_RX_TIMEOUT_H        (0x155 - 0x106)

#define PROPERTY_ADDR_R155                          (0x0400 | (0x155 - 0x106))
#define PROPERTY_GROUP_R155                         0x04
#define PROPERTY_INDEX_R155                         (0x155 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R156_TP_CODE_COVER_L          (0x0400 | (0x156 - 0x106))
#define PROPERTY_GROUP_R156_TP_CODE_COVER_L         0x04
#define PROPERTY_INDEX_R156_TP_CODE_COVER_L         (0x156 - 0x106)

#define PROPERTY_ADDR_R156                          (0x0400 | (0x156 - 0x106))
#define PROPERTY_GROUP_R156                         0x04
#define PROPERTY_INDEX_R156                         (0x156 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R157                          (0x0400 | (0x157 - 0x106))
#define PROPERTY_GROUP_R157                         0x04
#define PROPERTY_INDEX_R157                         (0x157 - 0x106)

#define PROPERTY_POS_R157_IB_ONLY                   7
#define PROPERTY_MSK_R157_IB_ONLY                   (0x01 << PROPERTY_POS_R157_IB_ONLY)

#define PROPERTY_POS_R157_TP_CODE_COVER_H           0
#define PROPERTY_MSK_R157_TP_CODE_COVER_H           (0x7f << PROPERTY_POS_R157_TP_CODE_COVER_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R158_OB_SCALING_L             (0x0400 | (0x158 - 0x106))
#define PROPERTY_GROUP_R158_OB_SCALING_L            0x04
#define PROPERTY_INDEX_R158_OB_SCALING_L            (0x158 - 0x106)

#define PROPERTY_ADDR_R158                          (0x0400 | (0x158 - 0x106))
#define PROPERTY_GROUP_R158                         0x04
#define PROPERTY_INDEX_R158                         (0x158 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R159                          (0x0400 | (0x159 - 0x106))
#define PROPERTY_GROUP_R159                         0x04
#define PROPERTY_INDEX_R159                         (0x159 - 0x106)

#define PROPERTY_POS_R159_TP_CODE_GROUP_SEL         3
#define PROPERTY_MSK_R159_TP_CODE_GROUP_SEL         (0x03 << PROPERTY_POS_R159_TP_CODE_GROUP_SEL)

#define PROPERTY_POS_R159_OB_SCALING_H              0
#define PROPERTY_MSK_R159_OB_SCALING_H              (0x07 << PROPERTY_POS_R159_OB_SCALING_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R15A_IB_SCL_CODE_L            (0x0400 | (0x15a - 0x106))
#define PROPERTY_GROUP_R15A_IB_SCL_CODE_L           0x04
#define PROPERTY_INDEX_R15A_IB_SCL_CODE_L           (0x15a - 0x106)

#define PROPERTY_ADDR_R15A                          (0x0400 | (0x15a - 0x106))
#define PROPERTY_GROUP_R15A                         0x04
#define PROPERTY_INDEX_R15A                         (0x15a - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R15B_IB_SCL_CODE_H            (0x0400 | (0x15b - 0x106))
#define PROPERTY_GROUP_R15B_IB_SCL_CODE_H           0x04
#define PROPERTY_INDEX_R15B_IB_SCL_CODE_H           (0x15b - 0x106)

#define PROPERTY_ADDR_R15B                          (0x0400 | (0x15b - 0x106))
#define PROPERTY_GROUP_R15B                         0x04
#define PROPERTY_INDEX_R15B                         (0x15b - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R15C_VCO_CODE_AUTO_RX         (0x0400 | (0x15c - 0x106))
#define PROPERTY_GROUP_R15C_VCO_CODE_AUTO_RX        0x04
#define PROPERTY_INDEX_R15C_VCO_CODE_AUTO_RX        (0x15c - 0x106)

#define PROPERTY_ADDR_R15C                          (0x0400 | (0x15c - 0x106))
#define PROPERTY_GROUP_R15C                         0x04
#define PROPERTY_INDEX_R15C                         (0x15c - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R15D_TIE0_BIT                 (0x0400 | (0x15d - 0x106))
#define PROPERTY_GROUP_R15D_TIE0_BIT                0x04
#define PROPERTY_INDEX_R15D_TIE0_BIT                (0x15d - 0x106)

#define PROPERTY_ADDR_R15D                          (0x0400 | (0x15d - 0x106))
#define PROPERTY_GROUP_R15D                         0x04
#define PROPERTY_INDEX_R15D                         (0x15d - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R15E                          (0x0400 | (0x15e - 0x106))
#define PROPERTY_GROUP_R15E                         0x04
#define PROPERTY_INDEX_R15E                         (0x15e - 0x106)

#define PROPERTY_POS_R15E_TWO_POINT_CAL_DONE        6
#define PROPERTY_MSK_R15E_TWO_POINT_CAL_DONE        (0x01 << PROPERTY_POS_R15E_TWO_POINT_CAL_DONE)

#define PROPERTY_POS_R15E_VCO_CAL_DONE              5
#define PROPERTY_MSK_R15E_VCO_CAL_DONE              (0x01 << PROPERTY_POS_R15E_VCO_CAL_DONE)

#define PROPERTY_POS_R15E_TWO_POINT_AUTO_CODE0      0
#define PROPERTY_MSK_R15E_TWO_POINT_AUTO_CODE0      (0x1f << PROPERTY_POS_R15E_TWO_POINT_AUTO_CODE0)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R15F                          (0x0400 | (0x15f - 0x106))
#define PROPERTY_GROUP_R15F                         0x04
#define PROPERTY_INDEX_R15F                         (0x15f - 0x106)

#define PROPERTY_POS_R15F_BUCK_ZERO_CAL_FINISH      7
#define PROPERTY_MSK_R15F_BUCK_ZERO_CAL_FINISH      (0x01 << PROPERTY_POS_R15F_BUCK_ZERO_CAL_FINISH)

#define PROPERTY_POS_R15F_BUCK_IMAX_CAL_FINISH      6
#define PROPERTY_MSK_R15F_BUCK_IMAX_CAL_FINISH      (0x01 << PROPERTY_POS_R15F_BUCK_IMAX_CAL_FINISH)

#define PROPERTY_POS_R15F_TWO_POINT_AUTO_CODE1      0
#define PROPERTY_MSK_R15F_TWO_POINT_AUTO_CODE1      (0x1f << PROPERTY_POS_R15F_TWO_POINT_AUTO_CODE1)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R160                          (0x0400 | (0x160 - 0x106))
#define PROPERTY_GROUP_R160                         0x04
#define PROPERTY_INDEX_R160                         (0x160 - 0x106)

#define PROPERTY_POS_R160_BUCK_CAL_FINISH           5
#define PROPERTY_MSK_R160_BUCK_CAL_FINISH           (0x01 << PROPERTY_POS_R160_BUCK_CAL_FINISH)

#define PROPERTY_POS_R160_TWO_POINT_AUTO_CODE2      0
#define PROPERTY_MSK_R160_TWO_POINT_AUTO_CODE2      (0x1f << PROPERTY_POS_R160_TWO_POINT_AUTO_CODE2)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R161_TWO_POINT_AUTO_CODE3     (0x0400 | (0x161 - 0x106))
#define PROPERTY_GROUP_R161_TWO_POINT_AUTO_CODE3    0x04
#define PROPERTY_INDEX_R161_TWO_POINT_AUTO_CODE3    (0x161 - 0x106)

#define PROPERTY_ADDR_R161                          (0x0400 | (0x161 - 0x106))
#define PROPERTY_GROUP_R161                         0x04
#define PROPERTY_INDEX_R161                         (0x161 - 0x106)

#define PROPERTY_POS_R161_TWO_POINT_AUTO_CODE3      0
#define PROPERTY_MSK_R161_TWO_POINT_AUTO_CODE3      (0x1f << PROPERTY_POS_R161_TWO_POINT_AUTO_CODE3)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R162_TP_CAL_CODE              (0x0400 | (0x162 - 0x106))
#define PROPERTY_GROUP_R162_TP_CAL_CODE             0x04
#define PROPERTY_INDEX_R162_TP_CAL_CODE             (0x162 - 0x106)

#define PROPERTY_ADDR_R162                          (0x0400 | (0x162 - 0x106))
#define PROPERTY_GROUP_R162                         0x04
#define PROPERTY_INDEX_R162                         (0x162 - 0x106)

#define PROPERTY_POS_R162_TP_CAL_CODE               0
#define PROPERTY_MSK_R162_TP_CAL_CODE               (0x1f << PROPERTY_POS_R162_TP_CAL_CODE)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R163_VCO_CODE_AUTO_TX         (0x0400 | (0x163 - 0x106))
#define PROPERTY_GROUP_R163_VCO_CODE_AUTO_TX        0x04
#define PROPERTY_INDEX_R163_VCO_CODE_AUTO_TX        (0x163 - 0x106)

#define PROPERTY_ADDR_R163                          (0x0400 | (0x163 - 0x106))
#define PROPERTY_GROUP_R163                         0x04
#define PROPERTY_INDEX_R163                         (0x163 - 0x106)

#define PROPERTY_POS_R163_VCO_CODE_AUTO_TX          0
#define PROPERTY_MSK_R163_VCO_CODE_AUTO_TX          (0x3f << PROPERTY_POS_R163_VCO_CODE_AUTO_TX)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R164                          (0x0400 | (0x164 - 0x106))
#define PROPERTY_GROUP_R164                         0x04
#define PROPERTY_INDEX_R164                         (0x164 - 0x106)

#define PROPERTY_POS_R164_TWO_POINT_CLK_EN          7
#define PROPERTY_MSK_R164_TWO_POINT_CLK_EN          (0x01 << PROPERTY_POS_R164_TWO_POINT_CLK_EN)

#define PROPERTY_POS_R164_EN_TWO_POINT_CAL          6
#define PROPERTY_MSK_R164_EN_TWO_POINT_CAL          (0x01 << PROPERTY_POS_R164_EN_TWO_POINT_CAL)

#define PROPERTY_POS_R164_EN_VCO_CAL                5
#define PROPERTY_MSK_R164_EN_VCO_CAL                (0x01 << PROPERTY_POS_R164_EN_VCO_CAL)

#define PROPERTY_POS_R164_TWO_POINT_SPI_TRIG        4
#define PROPERTY_MSK_R164_TWO_POINT_SPI_TRIG        (0x01 << PROPERTY_POS_R164_TWO_POINT_SPI_TRIG)

#define PROPERTY_POS_R164_SPI_CAL_TRIG              3
#define PROPERTY_MSK_R164_SPI_CAL_TRIG              (0x01 << PROPERTY_POS_R164_SPI_CAL_TRIG)

#define PROPERTY_POS_R164_CODE_OFFSET               0
#define PROPERTY_MSK_R164_CODE_OFFSET               (0x07 << PROPERTY_POS_R164_CODE_OFFSET)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R165_TWO_POINT_MANUL_CODE_IN0 (0x0400 | (0x165 - 0x106))
#define PROPERTY_GROUP_R165_TWO_POINT_MANUL_CODE_IN0 0x04
#define PROPERTY_INDEX_R165_TWO_POINT_MANUL_CODE_IN0 (0x165 - 0x106)

#define PROPERTY_ADDR_R165                          (0x0400 | (0x165 - 0x106))
#define PROPERTY_GROUP_R165                         0x04
#define PROPERTY_INDEX_R165                         (0x165 - 0x106)

#define PROPERTY_POS_R165_TWO_POINT_MANUL_CODE_IN0  0
#define PROPERTY_MSK_R165_TWO_POINT_MANUL_CODE_IN0  (0x1f << PROPERTY_POS_R165_TWO_POINT_MANUL_CODE_IN0)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R166_TWO_POINT_MANUL_CODE_IN1 (0x0400 | (0x166 - 0x106))
#define PROPERTY_GROUP_R166_TWO_POINT_MANUL_CODE_IN1 0x04
#define PROPERTY_INDEX_R166_TWO_POINT_MANUL_CODE_IN1 (0x166 - 0x106)

#define PROPERTY_ADDR_R166                          (0x0400 | (0x166 - 0x106))
#define PROPERTY_GROUP_R166                         0x04
#define PROPERTY_INDEX_R166                         (0x166 - 0x106)

#define PROPERTY_POS_R166_TWO_POINT_MANUL_CODE_IN1  0
#define PROPERTY_MSK_R166_TWO_POINT_MANUL_CODE_IN1  (0x1f << PROPERTY_POS_R166_TWO_POINT_MANUL_CODE_IN1)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R167_TWO_POINT_MANUL_CODE_IN2 (0x0400 | (0x167 - 0x106))
#define PROPERTY_GROUP_R167_TWO_POINT_MANUL_CODE_IN2 0x04
#define PROPERTY_INDEX_R167_TWO_POINT_MANUL_CODE_IN2 (0x167 - 0x106)

#define PROPERTY_ADDR_R167                          (0x0400 | (0x167 - 0x106))
#define PROPERTY_GROUP_R167                         0x04
#define PROPERTY_INDEX_R167                         (0x167 - 0x106)

#define PROPERTY_POS_R167_TWO_POINT_MANUL_CODE_IN2  0
#define PROPERTY_MSK_R167_TWO_POINT_MANUL_CODE_IN2  (0x1f << PROPERTY_POS_R167_TWO_POINT_MANUL_CODE_IN2)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R168                          (0x0400 | (0x168 - 0x106))
#define PROPERTY_GROUP_R168                         0x04
#define PROPERTY_INDEX_R168                         (0x168 - 0x106)

#define PROPERTY_POS_R168_AUTO_START_2P_CAL         7
#define PROPERTY_MSK_R168_AUTO_START_2P_CAL         (0x01 << PROPERTY_POS_R168_AUTO_START_2P_CAL)

#define PROPERTY_POS_R168_TWO_POINT_MANUL_CODE_IN3  0
#define PROPERTY_MSK_R168_TWO_POINT_MANUL_CODE_IN3  (0x1f << PROPERTY_POS_R168_TWO_POINT_MANUL_CODE_IN3)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R169_REF_DIFF_L               (0x0400 | (0x169 - 0x106))
#define PROPERTY_GROUP_R169_REF_DIFF_L              0x04
#define PROPERTY_INDEX_R169_REF_DIFF_L              (0x169 - 0x106)

#define PROPERTY_ADDR_R169                          (0x0400 | (0x169 - 0x106))
#define PROPERTY_GROUP_R169                         0x04
#define PROPERTY_INDEX_R169                         (0x169 - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R16A_REF_DIFF_H               (0x0400 | (0x16a - 0x106))
#define PROPERTY_GROUP_R16A_REF_DIFF_H              0x04
#define PROPERTY_INDEX_R16A_REF_DIFF_H              (0x16a - 0x106)

#define PROPERTY_ADDR_R16A                          (0x0400 | (0x16a - 0x106))
#define PROPERTY_GROUP_R16A                         0x04
#define PROPERTY_INDEX_R16A                         (0x16a - 0x106)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R16B                          (0x0400 | (0x16b - 0x106))
#define PROPERTY_GROUP_R16B                         0x04
#define PROPERTY_INDEX_R16B                         (0x16b - 0x106)

#define PROPERTY_POS_R16B_FIFO_MODE                 1
#define PROPERTY_MSK_R16B_FIFO_MODE                 (0x03 << PROPERTY_POS_R16B_FIFO_MODE)

#define PROPERTY_POS_R16B_FIFO_ENDIAN               0
#define PROPERTY_MSK_R16B_FIFO_ENDIAN               (0x01 << PROPERTY_POS_R16B_FIFO_ENDIAN)

/***************************************************************************************************
 * GROUP5 ����
 **************************************************************************************************/
#define PROPERTY_ADDR_R186                          (0x0500 | (0x186 - 0x186))
#define PROPERTY_GROUP_R186                         0x05
#define PROPERTY_INDEX_R186                         (0x186 - 0x186)

#define PROPERTY_POS_R186_REG_SYMBRATE_B            4
#define PROPERTY_MSK_R186_REG_SYMBRATE_B            (0x0f << PROPERTY_POS_R186_REG_SYMBRATE_B)

#define PROPERTY_POS_R186_REG_MODTYPE               2
#define PROPERTY_MSK_R186_REG_MODTYPE               (0x03 << PROPERTY_POS_R186_REG_MODTYPE)

#define PROPERTY_POS_R186_REG_SYMB_AB_SEL           0
#define PROPERTY_MSK_R186_REG_SYMB_AB_SEL           (0x01 << PROPERTY_POS_R186_REG_SYMB_AB_SEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R187_REG_SYMBRATE_A_L         (0x0500 | (0x187 - 0x186))
#define PROPERTY_GROUP_R187_REG_SYMBRATE_A_L        0x05
#define PROPERTY_INDEX_R187_REG_SYMBRATE_A_L        (0x187 - 0x186)

#define PROPERTY_ADDR_R187                          (0x0500 | (0x187 - 0x186))
#define PROPERTY_GROUP_R187                         0x05
#define PROPERTY_INDEX_R187                         (0x187 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R188                          (0x0500 | (0x188 - 0x186))
#define PROPERTY_GROUP_R188                         0x05
#define PROPERTY_INDEX_R188                         (0x188 - 0x186)

#define PROPERTY_POS_R188_SYNCWORD2_FEC_EN          4
#define PROPERTY_MSK_R188_SYNCWORD2_FEC_EN          (0x01 << PROPERTY_POS_R188_SYNCWORD2_FEC_EN)

#define PROPERTY_POS_R188_PREAMBLE_TRIG_SEL         3
#define PROPERTY_MSK_R188_PREAMBLE_TRIG_SEL         (0x01 << PROPERTY_POS_R188_PREAMBLE_TRIG_SEL)

#define PROPERTY_POS_R188_REG_PACKET_MODE           1
#define PROPERTY_MSK_R188_REG_PACKET_MODE           (0x03 << PROPERTY_POS_R188_REG_PACKET_MODE)

#define PROPERTY_POS_R188_REG_SYMBRATE_A_H          0
#define PROPERTY_MSK_R188_REG_SYMBRATE_A_H          (0x01 << PROPERTY_POS_R188_REG_SYMBRATE_A_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R189_REG_SYNC_WORD_L1         (0x0500 | (0x189 - 0x186))
#define PROPERTY_GROUP_R189_REG_SYNC_WORD_L1        0x05
#define PROPERTY_INDEX_R189_REG_SYNC_WORD_L1        (0x189 - 0x186)

#define PROPERTY_ADDR_R189                          (0x0500 | (0x189 - 0x186))
#define PROPERTY_GROUP_R189                         0x05
#define PROPERTY_INDEX_R189                         (0x189 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R18A_REG_SYNC_WORD_L2         (0x0500 | (0x18a - 0x186))
#define PROPERTY_GROUP_R18A_REG_SYNC_WORD_L2        0x05
#define PROPERTY_INDEX_R18A_REG_SYNC_WORD_L2        (0x18a - 0x186)

#define PROPERTY_ADDR_R18A                          (0x0500 | (0x18a - 0x186))
#define PROPERTY_GROUP_R18A                         0x05
#define PROPERTY_INDEX_R18A                         (0x18a - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R18B_REG_SYNC_WORD_L3         (0x0500 | (0x18b - 0x186))
#define PROPERTY_GROUP_R18B_REG_SYNC_WORD_L3        0x05
#define PROPERTY_INDEX_R18B_REG_SYNC_WORD_L3        (0x18b - 0x186)

#define PROPERTY_ADDR_R18B                          (0x0500 | (0x18b - 0x186))
#define PROPERTY_GROUP_R18B                         0x05
#define PROPERTY_INDEX_R18B                         (0x18b - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R18C_REG_SYNC_WORD_H          (0x0500 | (0x18c - 0x186))
#define PROPERTY_GROUP_R18C_REG_SYNC_WORD_H         0x05
#define PROPERTY_INDEX_R18C_REG_SYNC_WORD_H         (0x18c - 0x186)

#define PROPERTY_ADDR_R18C                          (0x0500 | (0x18c - 0x186))
#define PROPERTY_GROUP_R18C                         0x05
#define PROPERTY_INDEX_R18C                         (0x18c - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R18D_REG_SYNC_WORD2_L1        (0x0500 | (0x18d - 0x186))
#define PROPERTY_GROUP_R18D_REG_SYNC_WORD2_L1       0x05
#define PROPERTY_INDEX_R18D_REG_SYNC_WORD2_L1       (0x18d - 0x186)

#define PROPERTY_ADDR_R18D                          (0x0500 | (0x18d - 0x186))
#define PROPERTY_GROUP_R18D                         0x05
#define PROPERTY_INDEX_R18D                         (0x18d - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R18E_REG_SYNC_WORD2_L2        (0x0500 | (0x18e - 0x186))
#define PROPERTY_GROUP_R18E_REG_SYNC_WORD2_L2       0x05
#define PROPERTY_INDEX_R18E_REG_SYNC_WORD2_L2       (0x18e - 0x186)

#define PROPERTY_ADDR_R18E                          (0x0500 | (0x18e - 0x186))
#define PROPERTY_GROUP_R18E                         0x05
#define PROPERTY_INDEX_R18E                         (0x18e - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R18F_REG_SYNC_WORD2_L3        (0x0500 | (0x18f - 0x186))
#define PROPERTY_GROUP_R18F_REG_SYNC_WORD2_L3       0x05
#define PROPERTY_INDEX_R18F_REG_SYNC_WORD2_L3       (0x18f - 0x186)

#define PROPERTY_ADDR_R18F                          (0x0500 | (0x18f - 0x186))
#define PROPERTY_GROUP_R18F                         0x05
#define PROPERTY_INDEX_R18F                         (0x18f - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R190_REG_SYNC_WORD2_H         (0x0500 | (0x190 - 0x186))
#define PROPERTY_GROUP_R190_REG_SYNC_WORD2_H        0x05
#define PROPERTY_INDEX_R190_REG_SYNC_WORD2_H        (0x190 - 0x186)

#define PROPERTY_ADDR_R190                          (0x0500 | (0x190 - 0x186))
#define PROPERTY_GROUP_R190                         0x05
#define PROPERTY_INDEX_R190                         (0x190 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R191_REG_FREQ_STEP_L          (0x0500 | (0x191 - 0x186))
#define PROPERTY_GROUP_R191_REG_FREQ_STEP_L         0x05
#define PROPERTY_INDEX_R191_REG_FREQ_STEP_L         (0x191 - 0x186)

#define PROPERTY_ADDR_R191                          (0x0500 | (0x191 - 0x186))
#define PROPERTY_GROUP_R191                         0x05
#define PROPERTY_INDEX_R191                         (0x191 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R192_REG_FREQ_STEP_H          (0x0500 | (0x192 - 0x186))
#define PROPERTY_GROUP_R192_REG_FREQ_STEP_H         0x05
#define PROPERTY_INDEX_R192_REG_FREQ_STEP_H         (0x192 - 0x186)

#define PROPERTY_ADDR_R192                          (0x0500 | (0x192 - 0x186))
#define PROPERTY_GROUP_R192                         0x05
#define PROPERTY_INDEX_R192                         (0x192 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R193_REG_CHANNEL_NUM_L        (0x0500 | (0x193 - 0x186))
#define PROPERTY_GROUP_R193_REG_CHANNEL_NUM_L       0x05
#define PROPERTY_INDEX_R193_REG_CHANNEL_NUM_L       (0x193 - 0x186)

#define PROPERTY_ADDR_R193                          (0x0500 | (0x193 - 0x186))
#define PROPERTY_GROUP_R193                         0x05
#define PROPERTY_INDEX_R193                         (0x193 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R194_REG_CHANNEL_NUM_H        (0x0500 | (0x194 - 0x186))
#define PROPERTY_GROUP_R194_REG_CHANNEL_NUM_H       0x05
#define PROPERTY_INDEX_R194_REG_CHANNEL_NUM_H       (0x194 - 0x186)

#define PROPERTY_ADDR_R194                          (0x0500 | (0x194 - 0x186))
#define PROPERTY_GROUP_R194                         0x05
#define PROPERTY_INDEX_R194                         (0x194 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R195_REG_BASE_FREQ_L1         (0x0500 | (0x195 - 0x186))
#define PROPERTY_GROUP_R195_REG_BASE_FREQ_L1        0x05
#define PROPERTY_INDEX_R195_REG_BASE_FREQ_L1        (0x195 - 0x186)

#define PROPERTY_ADDR_R195                          (0x0500 | (0x195 - 0x186))
#define PROPERTY_GROUP_R195                         0x05
#define PROPERTY_INDEX_R195                         (0x195 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R196_REG_BASE_FREQ_L2         (0x0500 | (0x196 - 0x186))
#define PROPERTY_GROUP_R196_REG_BASE_FREQ_L2        0x05
#define PROPERTY_INDEX_R196_REG_BASE_FREQ_L2        (0x196 - 0x186)

#define PROPERTY_ADDR_R196                          (0x0500 | (0x196 - 0x186))
#define PROPERTY_GROUP_R196                         0x05
#define PROPERTY_INDEX_R196                         (0x196 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R197_REG_BASE_FREQ_L3         (0x0500 | (0x197 - 0x186))
#define PROPERTY_GROUP_R197_REG_BASE_FREQ_L3        0x05
#define PROPERTY_INDEX_R197_REG_BASE_FREQ_L3        (0x197 - 0x186)

#define PROPERTY_ADDR_R197                          (0x0500 | (0x197 - 0x186))
#define PROPERTY_GROUP_R197                         0x05
#define PROPERTY_INDEX_R197                         (0x197 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R198_REG_BASE_FREQ_H          (0x0500 | (0x198 - 0x186))
#define PROPERTY_GROUP_R198_REG_BASE_FREQ_H         0x05
#define PROPERTY_INDEX_R198_REG_BASE_FREQ_H         (0x198 - 0x186)

#define PROPERTY_ADDR_R198                          (0x0500 | (0x198 - 0x186))
#define PROPERTY_GROUP_R198                         0x05
#define PROPERTY_INDEX_R198                         (0x198 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R199_REG_RX_ADJUST_L1         (0x0500 | (0x199 - 0x186))
#define PROPERTY_GROUP_R199_REG_RX_ADJUST_L1        0x05
#define PROPERTY_INDEX_R199_REG_RX_ADJUST_L1        (0x199 - 0x186)

#define PROPERTY_ADDR_R199                          (0x0500 | (0x199 - 0x186))
#define PROPERTY_GROUP_R199                         0x05
#define PROPERTY_INDEX_R199                         (0x199 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R19A_REG_RX_ADJUST_L2         (0x0500 | (0x19a - 0x186))
#define PROPERTY_GROUP_R19A_REG_RX_ADJUST_L2        0x05
#define PROPERTY_INDEX_R19A_REG_RX_ADJUST_L2        (0x19a - 0x186)

#define PROPERTY_ADDR_R19A                          (0x0500 | (0x19a - 0x186))
#define PROPERTY_GROUP_R19A                         0x05
#define PROPERTY_INDEX_R19A                         (0x19a - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R19B_REG_RX_ADJUST_H          (0x0500 | (0x19b - 0x186))
#define PROPERTY_GROUP_R19B_REG_RX_ADJUST_H         0x05
#define PROPERTY_INDEX_R19B_REG_RX_ADJUST_H         (0x19b - 0x186)

#define PROPERTY_ADDR_R19B                          (0x0500 | (0x19b - 0x186))
#define PROPERTY_GROUP_R19B                         0x05
#define PROPERTY_INDEX_R19B                         (0x19b - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R19C_FIELD1_LENGTH_L          (0x0500 | (0x19c - 0x186))
#define PROPERTY_GROUP_R19C_FIELD1_LENGTH_L         0x05
#define PROPERTY_INDEX_R19C_FIELD1_LENGTH_L         (0x19c - 0x186)

#define PROPERTY_ADDR_R19C                          (0x0500 | (0x19c - 0x186))
#define PROPERTY_GROUP_R19C                         0x05
#define PROPERTY_INDEX_R19C                         (0x19c - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R19D_FIELD1_LENGTH_H          (0x0500 | (0x19d - 0x186))
#define PROPERTY_GROUP_R19D_FIELD1_LENGTH_H         0x05
#define PROPERTY_INDEX_R19D_FIELD1_LENGTH_H         (0x19d - 0x186)

#define PROPERTY_ADDR_R19D                          (0x0500 | (0x19d - 0x186))
#define PROPERTY_GROUP_R19D                         0x05
#define PROPERTY_INDEX_R19D                         (0x19d - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R19E                          (0x0500 | (0x19e - 0x186))
#define PROPERTY_GROUP_R19E                         0x05
#define PROPERTY_INDEX_R19E                         (0x19e - 0x186)

#define PROPERTY_POS_R19E_REG_RX_TIMEOUT_IMMED      7
#define PROPERTY_MSK_R19E_REG_RX_TIMEOUT_IMMED      (0x01 << PROPERTY_POS_R19E_REG_RX_TIMEOUT_IMMED)

#define PROPERTY_POS_R19E_REG_RX_PRE_TIMEOUT_MASK   6
#define PROPERTY_MSK_R19E_REG_RX_PRE_TIMEOUT_MASK   (0x01 << PROPERTY_POS_R19E_REG_RX_PRE_TIMEOUT_MASK)

#define PROPERTY_POS_R19E_REG_RX_SYNC_DONE_MASK     5
#define PROPERTY_MSK_R19E_REG_RX_SYNC_DONE_MASK     (0x01 << PROPERTY_POS_R19E_REG_RX_SYNC_DONE_MASK)

#define PROPERTY_POS_R19E_REG_RX_PRE_DONE_MASK      4
#define PROPERTY_MSK_R19E_REG_RX_PRE_DONE_MASK      (0x01 << PROPERTY_POS_R19E_REG_RX_PRE_DONE_MASK)

#define PROPERTY_POS_R19E_REG_RX_DONE_MASK          3
#define PROPERTY_MSK_R19E_REG_RX_DONE_MASK          (0x01 << PROPERTY_POS_R19E_REG_RX_DONE_MASK)

#define PROPERTY_POS_R19E_REG_RX_PL_CRC_ERR_MASK    2
#define PROPERTY_MSK_R19E_REG_RX_PL_CRC_ERR_MASK    (0x01 << PROPERTY_POS_R19E_REG_RX_PL_CRC_ERR_MASK)

#define PROPERTY_POS_R19E_REG_RX_TIMEOUT_MASK       1
#define PROPERTY_MSK_R19E_REG_RX_TIMEOUT_MASK       (0x01 << PROPERTY_POS_R19E_REG_RX_TIMEOUT_MASK)

#define PROPERTY_POS_R19E_REG_TX_DONE_MASK          0
#define PROPERTY_MSK_R19E_REG_TX_DONE_MASK          (0x01 << PROPERTY_POS_R19E_REG_TX_DONE_MASK)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R19F                          (0x0500 | (0x19f - 0x186))
#define PROPERTY_GROUP_R19F                         0x05
#define PROPERTY_INDEX_R19F                         (0x19f - 0x186)

#define PROPERTY_POS_R19F_REG_F5_DONE_MASK          7
#define PROPERTY_MSK_R19F_REG_F5_DONE_MASK          (0x01 << PROPERTY_POS_R19F_REG_F5_DONE_MASK)

#define PROPERTY_POS_R19F_REG_F4_DONE_MASK          6
#define PROPERTY_MSK_R19F_REG_F4_DONE_MASK          (0x01 << PROPERTY_POS_R19F_REG_F4_DONE_MASK)

#define PROPERTY_POS_R19F_REG_F3_DONE_MASK          5
#define PROPERTY_MSK_R19F_REG_F3_DONE_MASK          (0x01 << PROPERTY_POS_R19F_REG_F3_DONE_MASK)

#define PROPERTY_POS_R19F_REG_F2_DONE_MASK          4
#define PROPERTY_MSK_R19F_REG_F2_DONE_MASK          (0x01 << PROPERTY_POS_R19F_REG_F2_DONE_MASK)

#define PROPERTY_POS_R19F_REG_RX_RSSI_VLD_MASK      3
#define PROPERTY_MSK_R19F_REG_RX_RSSI_VLD_MASK      (0x01 << PROPERTY_POS_R19F_REG_RX_RSSI_VLD_MASK)

#define PROPERTY_POS_R19F_REG_M802_WHITEN_ERR_MASK  2
#define PROPERTY_MSK_R19F_REG_M802_WHITEN_ERR_MASK  (0x01 << PROPERTY_POS_R19F_REG_M802_WHITEN_ERR_MASK)

#define PROPERTY_POS_R19F_REG_TRX_SWITCH_MODE       1
#define PROPERTY_MSK_R19F_REG_TRX_SWITCH_MODE       (0x01 << PROPERTY_POS_R19F_REG_TRX_SWITCH_MODE)

#define PROPERTY_POS_R19F_REG_RX_SYNC_TIMEOUT_MASK  0
#define PROPERTY_MSK_R19F_REG_RX_SYNC_TIMEOUT_MASK  (0x01 << PROPERTY_POS_R19F_REG_RX_SYNC_TIMEOUT_MASK)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1A0                          (0x0500 | (0x1a0 - 0x186))
#define PROPERTY_GROUP_R1A0                         0x05
#define PROPERTY_INDEX_R1A0                         (0x1a0 - 0x186)

#define PROPERTY_POS_R1A0_REG_RSSI_TIMEOUT_MASK     6
#define PROPERTY_MSK_R1A0_REG_RSSI_TIMEOUT_MASK     (0x01 << PROPERTY_POS_R1A0_REG_RSSI_TIMEOUT_MASK)

#define PROPERTY_POS_R1A0_REG_IRQ_PULSE_CHECK_MODE  5
#define PROPERTY_MSK_R1A0_REG_IRQ_PULSE_CHECK_MODE  (0x01 << PROPERTY_POS_R1A0_REG_IRQ_PULSE_CHECK_MODE)

#define PROPERTY_POS_R1A0_RX_REMPTY_MASK            4
#define PROPERTY_MSK_R1A0_RX_REMPTY_MASK            (0x01 << PROPERTY_POS_R1A0_RX_REMPTY_MASK)

#define PROPERTY_POS_R1A0_RX_WFULL_MASK             3
#define PROPERTY_MSK_R1A0_RX_WFULL_MASK             (0x01 << PROPERTY_POS_R1A0_RX_WFULL_MASK)

#define PROPERTY_POS_R1A0_TX_REMPTY_MASK            2
#define PROPERTY_MSK_R1A0_TX_REMPTY_MASK            (0x01 << PROPERTY_POS_R1A0_TX_REMPTY_MASK)

#define PROPERTY_POS_R1A0_TX_WFULL_MASK             1
#define PROPERTY_MSK_R1A0_TX_WFULL_MASK             (0x01 << PROPERTY_POS_R1A0_TX_WFULL_MASK)

#define PROPERTY_POS_R1A0_REG_NODE_ID_VLD_MASK      0
#define PROPERTY_MSK_R1A0_REG_NODE_ID_VLD_MASK      (0x01 << PROPERTY_POS_R1A0_REG_NODE_ID_VLD_MASK)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1A1                          (0x0500 | (0x1a1 - 0x186))
#define PROPERTY_GROUP_R1A1                         0x05
#define PROPERTY_INDEX_R1A1                         (0x1a1 - 0x186)

#define PROPERTY_POS_R1A1_REG_SYNC_TIMEOUT_IRQ      7
#define PROPERTY_MSK_R1A1_REG_SYNC_TIMEOUT_IRQ      (0x01 << PROPERTY_POS_R1A1_REG_SYNC_TIMEOUT_IRQ)

#define PROPERTY_POS_R1A1_REG_PRE_TIMEOUT_IRQ       6
#define PROPERTY_MSK_R1A1_REG_PRE_TIMEOUT_IRQ       (0x01 << PROPERTY_POS_R1A1_REG_PRE_TIMEOUT_IRQ)

#define PROPERTY_POS_R1A1_REG_RX_SYNC_DONE_IRQ      5
#define PROPERTY_MSK_R1A1_REG_RX_SYNC_DONE_IRQ      (0x01 << PROPERTY_POS_R1A1_REG_RX_SYNC_DONE_IRQ)

#define PROPERTY_POS_R1A1_REG_RX_PRE_DONE_IRQ       4
#define PROPERTY_MSK_R1A1_REG_RX_PRE_DONE_IRQ       (0x01 << PROPERTY_POS_R1A1_REG_RX_PRE_DONE_IRQ)

#define PROPERTY_POS_R1A1_REG_RX_DONE_IRQ           3
#define PROPERTY_MSK_R1A1_REG_RX_DONE_IRQ           (0x01 << PROPERTY_POS_R1A1_REG_RX_DONE_IRQ)

#define PROPERTY_POS_R1A1_REG_RX_PL_CRC_ERR_IRQ     2
#define PROPERTY_MSK_R1A1_REG_RX_PL_CRC_ERR_IRQ     (0x01 << PROPERTY_POS_R1A1_REG_RX_PL_CRC_ERR_IRQ)

#define PROPERTY_POS_R1A1_REG_RX_TIMEOUT_IRQ        1
#define PROPERTY_MSK_R1A1_REG_RX_TIMEOUT_IRQ        (0x01 << PROPERTY_POS_R1A1_REG_RX_TIMEOUT_IRQ)

#define PROPERTY_POS_R1A1_REG_TX_DONE_IRQ           0
#define PROPERTY_MSK_R1A1_REG_TX_DONE_IRQ           (0x01 << PROPERTY_POS_R1A1_REG_TX_DONE_IRQ)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1A2                          (0x0500 | (0x1a2 - 0x186))
#define PROPERTY_GROUP_R1A2                         0x05
#define PROPERTY_INDEX_R1A2                         (0x1a2 - 0x186)

#define PROPERTY_POS_R1A2_RX_F5_CRC_ERR_IRQ         7
#define PROPERTY_MSK_R1A2_RX_F5_CRC_ERR_IRQ         (0x01 << PROPERTY_POS_R1A2_RX_F5_CRC_ERR_IRQ)

#define PROPERTY_POS_R1A2_RX_F4_CRC_ERR_IRQ         6
#define PROPERTY_MSK_R1A2_RX_F4_CRC_ERR_IRQ         (0x01 << PROPERTY_POS_R1A2_RX_F4_CRC_ERR_IRQ)

#define PROPERTY_POS_R1A2_RX_F3_CRC_ERR_IRQ         5
#define PROPERTY_MSK_R1A2_RX_F3_CRC_ERR_IRQ         (0x01 << PROPERTY_POS_R1A2_RX_F3_CRC_ERR_IRQ)

#define PROPERTY_POS_R1A2_RX_F2_CRC_ERR_IRQ         4
#define PROPERTY_MSK_R1A2_RX_F2_CRC_ERR_IRQ         (0x01 << PROPERTY_POS_R1A2_RX_F2_CRC_ERR_IRQ)

#define PROPERTY_POS_R1A2_RX_F5_DONE_IRQ            3
#define PROPERTY_MSK_R1A2_RX_F5_DONE_IRQ            (0x01 << PROPERTY_POS_R1A2_RX_F5_DONE_IRQ)

#define PROPERTY_POS_R1A2_RX_F4_DONE_IRQ            2
#define PROPERTY_MSK_R1A2_RX_F4_DONE_IRQ            (0x01 << PROPERTY_POS_R1A2_RX_F4_DONE_IRQ)

#define PROPERTY_POS_R1A2_RX_F3_DONE_IRQ            1
#define PROPERTY_MSK_R1A2_RX_F3_DONE_IRQ            (0x01 << PROPERTY_POS_R1A2_RX_F3_DONE_IRQ)

#define PROPERTY_POS_R1A2_RX_F2_DONE_IRQ            0
#define PROPERTY_MSK_R1A2_RX_F2_DONE_IRQ            (0x01 << PROPERTY_POS_R1A2_RX_F2_DONE_IRQ)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1A3                          (0x0500 | (0x1a3 - 0x186))
#define PROPERTY_GROUP_R1A3                         0x05
#define PROPERTY_INDEX_R1A3                         (0x1a3 - 0x186)

#define PROPERTY_POS_R1A3_REG_RSSI_TIMEOUT_IRQ      7
#define PROPERTY_MSK_R1A3_REG_RSSI_TIMEOUT_IRQ      (0x01 << PROPERTY_POS_R1A3_REG_RSSI_TIMEOUT_IRQ)

#define PROPERTY_POS_R1A3_RX_REMPTY_IRQ             6
#define PROPERTY_MSK_R1A3_RX_REMPTY_IRQ             (0x01 << PROPERTY_POS_R1A3_RX_REMPTY_IRQ)

#define PROPERTY_POS_R1A3_RX_WFULL_IRQ              5
#define PROPERTY_MSK_R1A3_RX_WFULL_IRQ              (0x01 << PROPERTY_POS_R1A3_RX_WFULL_IRQ)

#define PROPERTY_POS_R1A3_TX_REMPTY_IRQ             4
#define PROPERTY_MSK_R1A3_TX_REMPTY_IRQ             (0x01 << PROPERTY_POS_R1A3_TX_REMPTY_IRQ)

#define PROPERTY_POS_R1A3_TX_WFULL_IRQ              3
#define PROPERTY_MSK_R1A3_TX_WFULL_IRQ              (0x01 << PROPERTY_POS_R1A3_TX_WFULL_IRQ)

#define PROPERTY_POS_R1A3_RX_M802_WHIT_ERR_IRQ      2
#define PROPERTY_MSK_R1A3_RX_M802_WHIT_ERR_IRQ      (0x01 << PROPERTY_POS_R1A3_RX_M802_WHIT_ERR_IRQ)

#define PROPERTY_POS_R1A3_NODE_ID_VLD_IRQ           1
#define PROPERTY_MSK_R1A3_NODE_ID_VLD_IRQ           (0x01 << PROPERTY_POS_R1A3_NODE_ID_VLD_IRQ)

#define PROPERTY_POS_R1A3_RX_RSSI_VLD_IRQ           0
#define PROPERTY_MSK_R1A3_RX_RSSI_VLD_IRQ           (0x01 << PROPERTY_POS_R1A3_RX_RSSI_VLD_IRQ)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1A4                          (0x0500 | (0x1a4 - 0x186))
#define PROPERTY_GROUP_R1A4                         0x05
#define PROPERTY_INDEX_R1A4                         (0x1a4 - 0x186)

#define PROPERTY_POS_R1A4_REG_TIMEOUT_EN            7
#define PROPERTY_MSK_R1A4_REG_TIMEOUT_EN            (0x01 << PROPERTY_POS_R1A4_REG_TIMEOUT_EN)

#define PROPERTY_POS_R1A4_REG_TX_FIFO_FULL          6
#define PROPERTY_MSK_R1A4_REG_TX_FIFO_FULL          (0x01 << PROPERTY_POS_R1A4_REG_TX_FIFO_FULL)

#define PROPERTY_POS_R1A4_REG_GPIO_RX_MODE          5
#define PROPERTY_MSK_R1A4_REG_GPIO_RX_MODE          (0x01 << PROPERTY_POS_R1A4_REG_GPIO_RX_MODE)

#define PROPERTY_POS_R1A4_REG_GPIO_TX_MODE          4
#define PROPERTY_MSK_R1A4_REG_GPIO_TX_MODE          (0x01 << PROPERTY_POS_R1A4_REG_GPIO_TX_MODE)

#define PROPERTY_POS_R1A4_REG_RX_DONE_RST_TEST      3
#define PROPERTY_MSK_R1A4_REG_RX_DONE_RST_TEST      (0x01 << PROPERTY_POS_R1A4_REG_RX_DONE_RST_TEST)

#define PROPERTY_POS_R1A4_REG_RX_CRC_ERR_RST        2
#define PROPERTY_MSK_R1A4_REG_RX_CRC_ERR_RST        (0x01 << PROPERTY_POS_R1A4_REG_RX_CRC_ERR_RST)

#define PROPERTY_POS_R1A4_REG_2POINT_CAL_EN         0
#define PROPERTY_MSK_R1A4_REG_2POINT_CAL_EN         (0x01 << PROPERTY_POS_R1A4_REG_2POINT_CAL_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1A5_PREAMBLE_TIMEOUT_TH_L    (0x0500 | (0x1a5 - 0x186))
#define PROPERTY_GROUP_R1A5_PREAMBLE_TIMEOUT_TH_L   0x05
#define PROPERTY_INDEX_R1A5_PREAMBLE_TIMEOUT_TH_L   (0x1a5 - 0x186)

#define PROPERTY_ADDR_R1A5                          (0x0500 | (0x1a5 - 0x186))
#define PROPERTY_GROUP_R1A5                         0x05
#define PROPERTY_INDEX_R1A5                         (0x1a5 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1A6_PREAMBLE_TIMEOUT_TH_H    (0x0500 | (0x1a6 - 0x186))
#define PROPERTY_GROUP_R1A6_PREAMBLE_TIMEOUT_TH_H   0x05
#define PROPERTY_INDEX_R1A6_PREAMBLE_TIMEOUT_TH_H   (0x1a6 - 0x186)

#define PROPERTY_ADDR_R1A6                          (0x0500 | (0x1a6 - 0x186))
#define PROPERTY_GROUP_R1A6                         0x05
#define PROPERTY_INDEX_R1A6                         (0x1a6 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1A7_SYNCWORD_TIMEOUT_TH_L    (0x0500 | (0x1a7 - 0x186))
#define PROPERTY_GROUP_R1A7_SYNCWORD_TIMEOUT_TH_L   0x05
#define PROPERTY_INDEX_R1A7_SYNCWORD_TIMEOUT_TH_L   (0x1a7 - 0x186)

#define PROPERTY_ADDR_R1A7                          (0x0500 | (0x1a7 - 0x186))
#define PROPERTY_GROUP_R1A7                         0x05
#define PROPERTY_INDEX_R1A7                         (0x1a7 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1A8_SYNCWORD_TIMEOUT_TH_H    (0x0500 | (0x1a8 - 0x186))
#define PROPERTY_GROUP_R1A8_SYNCWORD_TIMEOUT_TH_H   0x05
#define PROPERTY_INDEX_R1A8_SYNCWORD_TIMEOUT_TH_H   (0x1a8 - 0x186)

#define PROPERTY_ADDR_R1A8                          (0x0500 | (0x1a8 - 0x186))
#define PROPERTY_GROUP_R1A8                         0x05
#define PROPERTY_INDEX_R1A8                         (0x1a8 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1A9_RSSI_TIMEOUT_TH_L        (0x0500 | (0x1a9 - 0x186))
#define PROPERTY_GROUP_R1A9_RSSI_TIMEOUT_TH_L       0x05
#define PROPERTY_INDEX_R1A9_RSSI_TIMEOUT_TH_L       (0x1a9 - 0x186)

#define PROPERTY_ADDR_R1A9                          (0x0500 | (0x1a9 - 0x186))
#define PROPERTY_GROUP_R1A9                         0x05
#define PROPERTY_INDEX_R1A9                         (0x1a9 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1AA_RSSI_TIMEOUT_TH_H        (0x0500 | (0x1aa - 0x186))
#define PROPERTY_GROUP_R1AA_RSSI_TIMEOUT_TH_H       0x05
#define PROPERTY_INDEX_R1AA_RSSI_TIMEOUT_TH_H       (0x1aa - 0x186)

#define PROPERTY_ADDR_R1AA                          (0x0500 | (0x1aa - 0x186))
#define PROPERTY_GROUP_R1AA                         0x05
#define PROPERTY_INDEX_R1AA                         (0x1aa - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1AB_RSSI_WIDTH_TH            (0x0500 | (0x1ab - 0x186))
#define PROPERTY_GROUP_R1AB_RSSI_WIDTH_TH           0x05
#define PROPERTY_INDEX_R1AB_RSSI_WIDTH_TH           (0x1ab - 0x186)

#define PROPERTY_ADDR_R1AB                          (0x0500 | (0x1ab - 0x186))
#define PROPERTY_GROUP_R1AB                         0x05
#define PROPERTY_INDEX_R1AB                         (0x1ab - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1AC_RSSI_BUSY_THRE           (0x0500 | (0x1ac - 0x186))
#define PROPERTY_GROUP_R1AC_RSSI_BUSY_THRE          0x05
#define PROPERTY_INDEX_R1AC_RSSI_BUSY_THRE          (0x1ac - 0x186)

#define PROPERTY_ADDR_R1AC                          (0x0500 | (0x1ac - 0x186))
#define PROPERTY_GROUP_R1AC                         0x05
#define PROPERTY_INDEX_R1AC                         (0x1ac - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1AD_RX_PL_LENGTH_L           (0x0500 | (0x1ad - 0x186))
#define PROPERTY_GROUP_R1AD_RX_PL_LENGTH_L          0x05
#define PROPERTY_INDEX_R1AD_RX_PL_LENGTH_L          (0x1ad - 0x186)

#define PROPERTY_ADDR_R1AD                          (0x0500 | (0x1ad - 0x186))
#define PROPERTY_GROUP_R1AD                         0x05
#define PROPERTY_INDEX_R1AD                         (0x1ad - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1AE_RX_PL_LENGTH_H           (0x0500 | (0x1ae - 0x186))
#define PROPERTY_GROUP_R1AE_RX_PL_LENGTH_H          0x05
#define PROPERTY_INDEX_R1AE_RX_PL_LENGTH_H          (0x1ae - 0x186)

#define PROPERTY_ADDR_R1AE                          (0x0500 | (0x1ae - 0x186))
#define PROPERTY_GROUP_R1AE                         0x05
#define PROPERTY_INDEX_R1AE                         (0x1ae - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1AF                          (0x0500 | (0x1af - 0x186))
#define PROPERTY_GROUP_R1AF                         0x05
#define PROPERTY_INDEX_R1AF                         (0x1af - 0x186)

#define PROPERTY_POS_R1AF_VPP_MUX                   6
#define PROPERTY_MSK_R1AF_VPP_MUX                   (0x01 << PROPERTY_POS_R1AF_VPP_MUX)

#define PROPERTY_POS_R1AF_GPIO2_PDEN                5
#define PROPERTY_MSK_R1AF_GPIO2_PDEN                (0x01 << PROPERTY_POS_R1AF_GPIO2_PDEN)

#define PROPERTY_POS_R1AF_GPIO1_PDEN                4
#define PROPERTY_MSK_R1AF_GPIO1_PDEN                (0x01 << PROPERTY_POS_R1AF_GPIO1_PDEN)

#define PROPERTY_POS_R1AF_GPIO0_PDEN                3
#define PROPERTY_MSK_R1AF_GPIO0_PDEN                (0x01 << PROPERTY_POS_R1AF_GPIO0_PDEN)

#define PROPERTY_POS_R1AF_GPIO2_PUEN                2
#define PROPERTY_MSK_R1AF_GPIO2_PUEN                (0x01 << PROPERTY_POS_R1AF_GPIO2_PUEN)

#define PROPERTY_POS_R1AF_GPIO1_PUEN                1
#define PROPERTY_MSK_R1AF_GPIO1_PUEN                (0x01 << PROPERTY_POS_R1AF_GPIO1_PUEN)

#define PROPERTY_POS_R1AF_GPIO0_PUEN                0
#define PROPERTY_MSK_R1AF_GPIO0_PUEN                (0x01 << PROPERTY_POS_R1AF_GPIO0_PUEN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1B0                          (0x0500 | (0x1b0 - 0x186))
#define PROPERTY_GROUP_R1B0                         0x05
#define PROPERTY_INDEX_R1B0                         (0x1b0 - 0x186)

#define PROPERTY_POS_R1B0_VPP_OE                    7
#define PROPERTY_MSK_R1B0_VPP_OE                    (0x01 << PROPERTY_POS_R1B0_VPP_OE)

#define PROPERTY_POS_R1B0_GPIO2_OE                  6
#define PROPERTY_MSK_R1B0_GPIO2_OE                  (0x01 << PROPERTY_POS_R1B0_GPIO2_OE)

#define PROPERTY_POS_R1B0_GPIO1_OE                  5
#define PROPERTY_MSK_R1B0_GPIO1_OE                  (0x01 << PROPERTY_POS_R1B0_GPIO1_OE)

#define PROPERTY_POS_R1B0_GPIO0_OE                  4
#define PROPERTY_MSK_R1B0_GPIO0_OE                  (0x01 << PROPERTY_POS_R1B0_GPIO0_OE)

#define PROPERTY_POS_R1B0_VPP_DIEN                  3
#define PROPERTY_MSK_R1B0_VPP_DIEN                  (0x01 << PROPERTY_POS_R1B0_VPP_DIEN)

#define PROPERTY_POS_R1B0_GPIO2_DIEN                2
#define PROPERTY_MSK_R1B0_GPIO2_DIEN                (0x01 << PROPERTY_POS_R1B0_GPIO2_DIEN)

#define PROPERTY_POS_R1B0_GPIO1_DIEN                1
#define PROPERTY_MSK_R1B0_GPIO1_DIEN                (0x01 << PROPERTY_POS_R1B0_GPIO1_DIEN)

#define PROPERTY_POS_R1B0_GPIO0_DIEN                0
#define PROPERTY_MSK_R1B0_GPIO0_DIEN                (0x01 << PROPERTY_POS_R1B0_GPIO0_DIEN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1B1                          (0x0500 | (0x1b1 - 0x186))
#define PROPERTY_GROUP_R1B1                         0x05
#define PROPERTY_INDEX_R1B1                         (0x1b1 - 0x186)

#define PROPERTY_POS_R1B1_GPIO2_MUX                 4
#define PROPERTY_MSK_R1B1_GPIO2_MUX                 (0x0f << PROPERTY_POS_R1B1_GPIO2_MUX)

#define PROPERTY_POS_R1B1_GPIO1_MUX                 0
#define PROPERTY_MSK_R1B1_GPIO1_MUX                 (0x0f << PROPERTY_POS_R1B1_GPIO1_MUX)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1B2                          (0x0500 | (0x1b2 - 0x186))
#define PROPERTY_GROUP_R1B2                         0x05
#define PROPERTY_INDEX_R1B2                         (0x1b2 - 0x186)

#define PROPERTY_POS_R1B2_GPIO0_MUX                 4
#define PROPERTY_MSK_R1B2_GPIO0_MUX                 (0x0f << PROPERTY_POS_R1B2_GPIO0_MUX)

#define PROPERTY_POS_R1B2_GPIO11_REG                3
#define PROPERTY_MSK_R1B2_GPIO11_REG                (0x01 << PROPERTY_POS_R1B2_GPIO11_REG)

#define PROPERTY_POS_R1B2_GPIO2_REG                 2
#define PROPERTY_MSK_R1B2_GPIO2_REG                 (0x01 << PROPERTY_POS_R1B2_GPIO2_REG)

#define PROPERTY_POS_R1B2_GPIO1_REG                 1
#define PROPERTY_MSK_R1B2_GPIO1_REG                 (0x01 << PROPERTY_POS_R1B2_GPIO1_REG)

#define PROPERTY_POS_R1B2_GPIO0_REG                 0
#define PROPERTY_MSK_R1B2_GPIO0_REG                 (0x01 << PROPERTY_POS_R1B2_GPIO0_REG)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1B3                          (0x0500 | (0x1b3 - 0x186))
#define PROPERTY_GROUP_R1B3                         0x05
#define PROPERTY_INDEX_R1B3                         (0x1b3 - 0x186)

#define PROPERTY_POS_R1B3_REG_RSSI_PRE_RD           3
#define PROPERTY_MSK_R1B3_REG_RSSI_PRE_RD           (0x01 << PROPERTY_POS_R1B3_REG_RSSI_PRE_RD)

#define PROPERTY_POS_R1B3_LO_MUX_SEL                0
#define PROPERTY_MSK_R1B3_LO_MUX_SEL                (0x07 << PROPERTY_POS_R1B3_LO_MUX_SEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1B4_SIG_PWR_L                (0x0500 | (0x1b4 - 0x186))
#define PROPERTY_GROUP_R1B4_SIG_PWR_L               0x05
#define PROPERTY_INDEX_R1B4_SIG_PWR_L               (0x1b4 - 0x186)

#define PROPERTY_ADDR_R1B4                          (0x0500 | (0x1b4 - 0x186))
#define PROPERTY_GROUP_R1B4                         0x05
#define PROPERTY_INDEX_R1B4                         (0x1b4 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1B5_SIG_PWR_H                (0x0500 | (0x1b5 - 0x186))
#define PROPERTY_GROUP_R1B5_SIG_PWR_H               0x05
#define PROPERTY_INDEX_R1B5_SIG_PWR_H               (0x1b5 - 0x186)

#define PROPERTY_ADDR_R1B5                          (0x0500 | (0x1b5 - 0x186))
#define PROPERTY_GROUP_R1B5                         0x05
#define PROPERTY_INDEX_R1B5                         (0x1b5 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1B6_NOISE_PWR_L              (0x0500 | (0x1b6 - 0x186))
#define PROPERTY_GROUP_R1B6_NOISE_PWR_L             0x05
#define PROPERTY_INDEX_R1B6_NOISE_PWR_L             (0x1b6 - 0x186)

#define PROPERTY_ADDR_R1B6                          (0x0500 | (0x1b6 - 0x186))
#define PROPERTY_GROUP_R1B6                         0x05
#define PROPERTY_INDEX_R1B6                         (0x1b6 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1B7_NOISE_PWR_H              (0x0500 | (0x1b7 - 0x186))
#define PROPERTY_GROUP_R1B7_NOISE_PWR_H             0x05
#define PROPERTY_INDEX_R1B7_NOISE_PWR_H             (0x1b7 - 0x186)

#define PROPERTY_ADDR_R1B7                          (0x0500 | (0x1b7 - 0x186))
#define PROPERTY_GROUP_R1B7                         0x05
#define PROPERTY_INDEX_R1B7                         (0x1b7 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1B8_NODE_ID_DEC_L1           (0x0500 | (0x1b8 - 0x186))
#define PROPERTY_GROUP_R1B8_NODE_ID_DEC_L1          0x05
#define PROPERTY_INDEX_R1B8_NODE_ID_DEC_L1          (0x1b8 - 0x186)

#define PROPERTY_ADDR_R1B8                          (0x0500 | (0x1b8 - 0x186))
#define PROPERTY_GROUP_R1B8                         0x05
#define PROPERTY_INDEX_R1B8                         (0x1b8 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1B9_NODE_ID_DEC_L2           (0x0500 | (0x1b9 - 0x186))
#define PROPERTY_GROUP_R1B9_NODE_ID_DEC_L2          0x05
#define PROPERTY_INDEX_R1B9_NODE_ID_DEC_L2          (0x1b9 - 0x186)

#define PROPERTY_ADDR_R1B9                          (0x0500 | (0x1b9 - 0x186))
#define PROPERTY_GROUP_R1B9                         0x05
#define PROPERTY_INDEX_R1B9                         (0x1b9 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1BA_NODE_ID_DEC_L3           (0x0500 | (0x1ba - 0x186))
#define PROPERTY_GROUP_R1BA_NODE_ID_DEC_L3          0x05
#define PROPERTY_INDEX_R1BA_NODE_ID_DEC_L3          (0x1ba - 0x186)

#define PROPERTY_ADDR_R1BA                          (0x0500 | (0x1ba - 0x186))
#define PROPERTY_GROUP_R1BA                         0x05
#define PROPERTY_INDEX_R1BA                         (0x1ba - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1BB_NODE_ID_DEC_H            (0x0500 | (0x1bb - 0x186))
#define PROPERTY_GROUP_R1BB_NODE_ID_DEC_H           0x05
#define PROPERTY_INDEX_R1BB_NODE_ID_DEC_H           (0x1bb - 0x186)

#define PROPERTY_ADDR_R1BB                          (0x0500 | (0x1bb - 0x186))
#define PROPERTY_GROUP_R1BB                         0x05
#define PROPERTY_INDEX_R1BB                         (0x1bb - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1BC_RSSI_R32_HOLD            (0x0500 | (0x1bc - 0x186))
#define PROPERTY_GROUP_R1BC_RSSI_R32_HOLD           0x05
#define PROPERTY_INDEX_R1BC_RSSI_R32_HOLD           (0x1bc - 0x186)

#define PROPERTY_ADDR_R1BC                          (0x0500 | (0x1bc - 0x186))
#define PROPERTY_GROUP_R1BC                         0x05
#define PROPERTY_INDEX_R1BC                         (0x1bc - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1BD_RSSI_RBW_HOLD            (0x0500 | (0x1bd - 0x186))
#define PROPERTY_GROUP_R1BD_RSSI_RBW_HOLD           0x05
#define PROPERTY_INDEX_R1BD_RSSI_RBW_HOLD           (0x1bd - 0x186)

#define PROPERTY_ADDR_R1BD                          (0x0500 | (0x1bd - 0x186))
#define PROPERTY_GROUP_R1BD                         0x05
#define PROPERTY_INDEX_R1BD                         (0x1bd - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1BE_RSSI_R32_CHG             (0x0500 | (0x1be - 0x186))
#define PROPERTY_GROUP_R1BE_RSSI_R32_CHG            0x05
#define PROPERTY_INDEX_R1BE_RSSI_R32_CHG            (0x1be - 0x186)

#define PROPERTY_ADDR_R1BE                          (0x0500 | (0x1be - 0x186))
#define PROPERTY_GROUP_R1BE                         0x05
#define PROPERTY_INDEX_R1BE                         (0x1be - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1BF_RSSI_RBW_CHG             (0x0500 | (0x1bf - 0x186))
#define PROPERTY_GROUP_R1BF_RSSI_RBW_CHG            0x05
#define PROPERTY_INDEX_R1BF_RSSI_RBW_CHG            (0x1bf - 0x186)

#define PROPERTY_ADDR_R1BF                          (0x0500 | (0x1bf - 0x186))
#define PROPERTY_GROUP_R1BF                         0x05
#define PROPERTY_INDEX_R1BF                         (0x1bf - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1C0                          (0x0500 | (0x1c0 - 0x186))
#define PROPERTY_GROUP_R1C0                         0x05
#define PROPERTY_INDEX_R1C0                         (0x1c0 - 0x186)

#define PROPERTY_POS_R1C0_FIFO0_RADDR_SET           3
#define PROPERTY_MSK_R1C0_FIFO0_RADDR_SET           (0x01 << PROPERTY_POS_R1C0_FIFO0_RADDR_SET)

#define PROPERTY_POS_R1C0_FIFO0_RADDR_CLR           2
#define PROPERTY_MSK_R1C0_FIFO0_RADDR_CLR           (0x01 << PROPERTY_POS_R1C0_FIFO0_RADDR_CLR)

#define PROPERTY_POS_R1C0_FIFO0_WADDR_SET           1
#define PROPERTY_MSK_R1C0_FIFO0_WADDR_SET           (0x01 << PROPERTY_POS_R1C0_FIFO0_WADDR_SET)

#define PROPERTY_POS_R1C0_FIFO0_WADDR_CLR           0
#define PROPERTY_MSK_R1C0_FIFO0_WADDR_CLR           (0x01 << PROPERTY_POS_R1C0_FIFO0_WADDR_CLR)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1C1                          (0x0500 | (0x1c1 - 0x186))
#define PROPERTY_GROUP_R1C1                         0x05
#define PROPERTY_INDEX_R1C1                         (0x1c1 - 0x186)

#define PROPERTY_POS_R1C1_FIFO1_RADDR_SET           3
#define PROPERTY_MSK_R1C1_FIFO1_RADDR_SET           (0x01 << PROPERTY_POS_R1C1_FIFO1_RADDR_SET)

#define PROPERTY_POS_R1C1_FIFO1_RADDR_CLR           2
#define PROPERTY_MSK_R1C1_FIFO1_RADDR_CLR           (0x01 << PROPERTY_POS_R1C1_FIFO1_RADDR_CLR)

#define PROPERTY_POS_R1C1_FIFO1_WADDR_SET           1
#define PROPERTY_MSK_R1C1_FIFO1_WADDR_SET           (0x01 << PROPERTY_POS_R1C1_FIFO1_WADDR_SET)

#define PROPERTY_POS_R1C1_FIFO1_WADDR_CLR           0
#define PROPERTY_MSK_R1C1_FIFO1_WADDR_CLR           (0x01 << PROPERTY_POS_R1C1_FIFO1_WADDR_CLR)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1C2_FIFO0_ADDR_INI           (0x0500 | (0x1c2 - 0x186))
#define PROPERTY_GROUP_R1C2_FIFO0_ADDR_INI          0x05
#define PROPERTY_INDEX_R1C2_FIFO0_ADDR_INI          (0x1c2 - 0x186)

#define PROPERTY_ADDR_R1C2                          (0x0500 | (0x1c2 - 0x186))
#define PROPERTY_GROUP_R1C2                         0x05
#define PROPERTY_INDEX_R1C2                         (0x1c2 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1C3_FIFO1_ADDR_INI           (0x0500 | (0x1c3 - 0x186))
#define PROPERTY_GROUP_R1C3_FIFO1_ADDR_INI          0x05
#define PROPERTY_INDEX_R1C3_FIFO1_ADDR_INI          (0x1c3 - 0x186)

#define PROPERTY_ADDR_R1C3                          (0x0500 | (0x1c3 - 0x186))
#define PROPERTY_GROUP_R1C3                         0x05
#define PROPERTY_INDEX_R1C3                         (0x1c3 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1C4_FIFO0_WFULL_TH           (0x0500 | (0x1c4 - 0x186))
#define PROPERTY_GROUP_R1C4_FIFO0_WFULL_TH          0x05
#define PROPERTY_INDEX_R1C4_FIFO0_WFULL_TH          (0x1c4 - 0x186)

#define PROPERTY_ADDR_R1C4                          (0x0500 | (0x1c4 - 0x186))
#define PROPERTY_GROUP_R1C4                         0x05
#define PROPERTY_INDEX_R1C4                         (0x1c4 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1C5_FIFO0_REMPTY_TH          (0x0500 | (0x1c5 - 0x186))
#define PROPERTY_GROUP_R1C5_FIFO0_REMPTY_TH         0x05
#define PROPERTY_INDEX_R1C5_FIFO0_REMPTY_TH         (0x1c5 - 0x186)

#define PROPERTY_ADDR_R1C5                          (0x0500 | (0x1c5 - 0x186))
#define PROPERTY_GROUP_R1C5                         0x05
#define PROPERTY_INDEX_R1C5                         (0x1c5 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1C6_FIFO1_WFULL_TH           (0x0500 | (0x1c6 - 0x186))
#define PROPERTY_GROUP_R1C6_FIFO1_WFULL_TH          0x05
#define PROPERTY_INDEX_R1C6_FIFO1_WFULL_TH          (0x1c6 - 0x186)

#define PROPERTY_ADDR_R1C6                          (0x0500 | (0x1c6 - 0x186))
#define PROPERTY_GROUP_R1C6                         0x05
#define PROPERTY_INDEX_R1C6                         (0x1c6 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1C7_FIFO1_REMPTY_TH          (0x0500 | (0x1c7 - 0x186))
#define PROPERTY_GROUP_R1C7_FIFO1_REMPTY_TH         0x05
#define PROPERTY_INDEX_R1C7_FIFO1_REMPTY_TH         (0x1c7 - 0x186)

#define PROPERTY_ADDR_R1C7                          (0x0500 | (0x1c7 - 0x186))
#define PROPERTY_GROUP_R1C7                         0x05
#define PROPERTY_INDEX_R1C7                         (0x1c7 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1C8_FIFO0_NUM                (0x0500 | (0x1c8 - 0x186))
#define PROPERTY_GROUP_R1C8_FIFO0_NUM               0x05
#define PROPERTY_INDEX_R1C8_FIFO0_NUM               (0x1c8 - 0x186)

#define PROPERTY_ADDR_R1C8                          (0x0500 | (0x1c8 - 0x186))
#define PROPERTY_GROUP_R1C8                         0x05
#define PROPERTY_INDEX_R1C8                         (0x1c8 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1C9_FIFO1_NUM                (0x0500 | (0x1c9 - 0x186))
#define PROPERTY_GROUP_R1C9_FIFO1_NUM               0x05
#define PROPERTY_INDEX_R1C9_FIFO1_NUM               (0x1c9 - 0x186)

#define PROPERTY_ADDR_R1C9                          (0x0500 | (0x1c9 - 0x186))
#define PROPERTY_GROUP_R1C9                         0x05
#define PROPERTY_INDEX_R1C9                         (0x1c9 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1CA                          (0x0500 | (0x1ca - 0x186))
#define PROPERTY_GROUP_R1CA                         0x05
#define PROPERTY_INDEX_R1CA                         (0x1ca - 0x186)

#define PROPERTY_POS_R1CA_TX_WFULL                  7
#define PROPERTY_MSK_R1CA_TX_WFULL                  (0x01 << PROPERTY_POS_R1CA_TX_WFULL)

#define PROPERTY_POS_R1CA_TX_REMPTY                 6
#define PROPERTY_MSK_R1CA_TX_REMPTY                 (0x01 << PROPERTY_POS_R1CA_TX_REMPTY)

#define PROPERTY_POS_R1CA_RX_WFULL                  5
#define PROPERTY_MSK_R1CA_RX_WFULL                  (0x01 << PROPERTY_POS_R1CA_RX_WFULL)

#define PROPERTY_POS_R1CA_RX_REMPTY                 4
#define PROPERTY_MSK_R1CA_RX_REMPTY                 (0x01 << PROPERTY_POS_R1CA_RX_REMPTY)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1CB                          (0x0500 | (0x1cb - 0x186))
#define PROPERTY_GROUP_R1CB                         0x05
#define PROPERTY_INDEX_R1CB                         (0x1cb - 0x186)

#define PROPERTY_POS_R1CB_PSDOR_SEQ_VLD             7
#define PROPERTY_MSK_R1CB_PSDOR_SEQ_VLD             (0x01 << PROPERTY_POS_R1CB_PSDOR_SEQ_VLD)

#define PROPERTY_POS_R1CB_RSSI_BUSY_MASK            6
#define PROPERTY_MSK_R1CB_RSSI_BUSY_MASK            (0x01 << PROPERTY_POS_R1CB_RSSI_BUSY_MASK)

#define PROPERTY_POS_R1CB_SW_BUSY_MASK              5
#define PROPERTY_MSK_R1CB_SW_BUSY_MASK              (0x01 << PROPERTY_POS_R1CB_SW_BUSY_MASK)

#define PROPERTY_POS_R1CB_PRE_BUSY_MASK             4
#define PROPERTY_MSK_R1CB_PRE_BUSY_MASK             (0x01 << PROPERTY_POS_R1CB_PRE_BUSY_MASK)

#define PROPERTY_POS_R1CB_REG_MDM_TRIG_SEL2         2
#define PROPERTY_MSK_R1CB_REG_MDM_TRIG_SEL2         (0x03 << PROPERTY_POS_R1CB_REG_MDM_TRIG_SEL2)

#define PROPERTY_POS_R1CB_REG_MDM_TRIG_SEL1         0
#define PROPERTY_MSK_R1CB_REG_MDM_TRIG_SEL1         (0x03 << PROPERTY_POS_R1CB_REG_MDM_TRIG_SEL1)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1CC_REG_MAX_PL_LEN_L         (0x0500 | (0x1cc - 0x186))
#define PROPERTY_GROUP_R1CC_REG_MAX_PL_LEN_L        0x05
#define PROPERTY_INDEX_R1CC_REG_MAX_PL_LEN_L        (0x1cc - 0x186)

#define PROPERTY_ADDR_R1CC                          (0x0500 | (0x1cc - 0x186))
#define PROPERTY_GROUP_R1CC                         0x05
#define PROPERTY_INDEX_R1CC                         (0x1cc - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1CD_REG_MAX_PL_LEN_H         (0x0500 | (0x1cd - 0x186))
#define PROPERTY_GROUP_R1CD_REG_MAX_PL_LEN_H        0x05
#define PROPERTY_INDEX_R1CD_REG_MAX_PL_LEN_H        (0x1cd - 0x186)

#define PROPERTY_ADDR_R1CD                          (0x0500 | (0x1cd - 0x186))
#define PROPERTY_GROUP_R1CD                         0x05
#define PROPERTY_INDEX_R1CD                         (0x1cd - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1CE_PSDOR_SEQ_L0             (0x0500 | (0x1ce - 0x186))
#define PROPERTY_GROUP_R1CE_PSDOR_SEQ_L0            0x05
#define PROPERTY_INDEX_R1CE_PSDOR_SEQ_L0            (0x1ce - 0x186)

#define PROPERTY_ADDR_R1CE                          (0x0500 | (0x1ce - 0x186))
#define PROPERTY_GROUP_R1CE                         0x05
#define PROPERTY_INDEX_R1CE                         (0x1ce - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1CF_PSDOR_SEQ_L1             (0x0500 | (0x1cf - 0x186))
#define PROPERTY_GROUP_R1CF_PSDOR_SEQ_L1            0x05
#define PROPERTY_INDEX_R1CF_PSDOR_SEQ_L1            (0x1cf - 0x186)

#define PROPERTY_ADDR_R1CF                          (0x0500 | (0x1cf - 0x186))
#define PROPERTY_GROUP_R1CF                         0x05
#define PROPERTY_INDEX_R1CF                         (0x1cf - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1D0_PSDOR_SEQ_L2             (0x0500 | (0x1d0 - 0x186))
#define PROPERTY_GROUP_R1D0_PSDOR_SEQ_L2            0x05
#define PROPERTY_INDEX_R1D0_PSDOR_SEQ_L2            (0x1d0 - 0x186)

#define PROPERTY_ADDR_R1D0                          (0x0500 | (0x1d0 - 0x186))
#define PROPERTY_GROUP_R1D0                         0x05
#define PROPERTY_INDEX_R1D0                         (0x1d0 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1D1_PSDOR_SEQ_H              (0x0500 | (0x1d1 - 0x186))
#define PROPERTY_GROUP_R1D1_PSDOR_SEQ_H             0x05
#define PROPERTY_INDEX_R1D1_PSDOR_SEQ_H             (0x1d1 - 0x186)

#define PROPERTY_ADDR_R1D1                          (0x0500 | (0x1d1 - 0x186))
#define PROPERTY_GROUP_R1D1                         0x05
#define PROPERTY_INDEX_R1D1                         (0x1d1 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1D2_PIC_RESTART_FLAG_L       (0x0500 | (0x1d2 - 0x186))
#define PROPERTY_GROUP_R1D2_PIC_RESTART_FLAG_L      0x05
#define PROPERTY_INDEX_R1D2_PIC_RESTART_FLAG_L      (0x1d2 - 0x186)

#define PROPERTY_ADDR_R1D2                          (0x0500 | (0x1d2 - 0x186))
#define PROPERTY_GROUP_R1D2                         0x05
#define PROPERTY_INDEX_R1D2                         (0x1d2 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1D3_PIC_RESTART_FLAG_H       (0x0500 | (0x1d3 - 0x186))
#define PROPERTY_GROUP_R1D3_PIC_RESTART_FLAG_H      0x05
#define PROPERTY_INDEX_R1D3_PIC_RESTART_FLAG_H      (0x1d3 - 0x186)

#define PROPERTY_ADDR_R1D3                          (0x0500 | (0x1d3 - 0x186))
#define PROPERTY_GROUP_R1D3                         0x05
#define PROPERTY_INDEX_R1D3                         (0x1d3 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1D4                          (0x0500 | (0x1d4 - 0x186))
#define PROPERTY_GROUP_R1D4                         0x05
#define PROPERTY_INDEX_R1D4                         (0x1d4 - 0x186)

#define PROPERTY_POS_R1D4_GPIO_DRV_SEL              1
#define PROPERTY_MSK_R1D4_GPIO_DRV_SEL              (0x03 << PROPERTY_POS_R1D4_GPIO_DRV_SEL)

#define PROPERTY_POS_R1D4_TEMP_EN                   0
#define PROPERTY_MSK_R1D4_TEMP_EN                   (0x01 << PROPERTY_POS_R1D4_TEMP_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1D5_SYNCWORD_LAST_BYTE_MASK  (0x0500 | (0x1d5 - 0x186))
#define PROPERTY_GROUP_R1D5_SYNCWORD_LAST_BYTE_MASK 0x05
#define PROPERTY_INDEX_R1D5_SYNCWORD_LAST_BYTE_MASK (0x1d5 - 0x186)

#define PROPERTY_ADDR_R1D5                          (0x0500 | (0x1d5 - 0x186))
#define PROPERTY_GROUP_R1D5                         0x05
#define PROPERTY_INDEX_R1D5                         (0x1d5 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1D6_PREAMBLE_LAST_BYTE_MASK  (0x0500 | (0x1d6 - 0x186))
#define PROPERTY_GROUP_R1D6_PREAMBLE_LAST_BYTE_MASK 0x05
#define PROPERTY_INDEX_R1D6_PREAMBLE_LAST_BYTE_MASK (0x1d6 - 0x186)

#define PROPERTY_ADDR_R1D6                          (0x0500 | (0x1d6 - 0x186))
#define PROPERTY_GROUP_R1D6                         0x05
#define PROPERTY_INDEX_R1D6                         (0x1d6 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1D7_SYNCWORD_LAST_BYTE       (0x0500 | (0x1d7 - 0x186))
#define PROPERTY_GROUP_R1D7_SYNCWORD_LAST_BYTE      0x05
#define PROPERTY_INDEX_R1D7_SYNCWORD_LAST_BYTE      (0x1d7 - 0x186)

#define PROPERTY_ADDR_R1D7                          (0x0500 | (0x1d7 - 0x186))
#define PROPERTY_GROUP_R1D7                         0x05
#define PROPERTY_INDEX_R1D7                         (0x1d7 - 0x186)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R1D8_PREAMBLE_LAST_BYTE       (0x0500 | (0x1d8 - 0x186))
#define PROPERTY_GROUP_R1D8_PREAMBLE_LAST_BYTE      0x05
#define PROPERTY_INDEX_R1D8_PREAMBLE_LAST_BYTE      (0x1d8 - 0x186)

#define PROPERTY_ADDR_R1D8                          (0x0500 | (0x1d8 - 0x186))
#define PROPERTY_GROUP_R1D8                         0x05
#define PROPERTY_INDEX_R1D8                         (0x1d8 - 0x186)

/***************************************************************************************************
 * GROUP6 ����
 **************************************************************************************************/
#define PROPERTY_ADDR_R206                          (0x0600 | (0x206 - 0x206))
#define PROPERTY_GROUP_R206                         0x06
#define PROPERTY_INDEX_R206                         (0x206 - 0x206)

#define PROPERTY_POS_R206_REG_AGC_MODE              2
#define PROPERTY_MSK_R206_REG_AGC_MODE              (0x01 << PROPERTY_POS_R206_REG_AGC_MODE)

#define PROPERTY_POS_R206_REG_AGC_SEL               1
#define PROPERTY_MSK_R206_REG_AGC_SEL               (0x01 << PROPERTY_POS_R206_REG_AGC_SEL)

#define PROPERTY_POS_R206_REG_AGC_MANU_EN           0
#define PROPERTY_MSK_R206_REG_AGC_MANU_EN           (0x01 << PROPERTY_POS_R206_REG_AGC_MANU_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R207_REG_AGC_MANU_L           (0x0600 | (0x207 - 0x206))
#define PROPERTY_GROUP_R207_REG_AGC_MANU_L          0x06
#define PROPERTY_INDEX_R207_REG_AGC_MANU_L          (0x207 - 0x206)

#define PROPERTY_ADDR_R207                          (0x0600 | (0x207 - 0x206))
#define PROPERTY_GROUP_R207                         0x06
#define PROPERTY_INDEX_R207                         (0x207 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R208_REG_AGC_MANU_H           (0x0600 | (0x208 - 0x206))
#define PROPERTY_GROUP_R208_REG_AGC_MANU_H          0x06
#define PROPERTY_INDEX_R208_REG_AGC_MANU_H          (0x208 - 0x206)

#define PROPERTY_ADDR_R208                          (0x0600 | (0x208 - 0x206))
#define PROPERTY_GROUP_R208                         0x06
#define PROPERTY_INDEX_R208                         (0x208 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R209_REG_AGC_GAIN_MANU        (0x0600 | (0x209 - 0x206))
#define PROPERTY_GROUP_R209_REG_AGC_GAIN_MANU       0x06
#define PROPERTY_INDEX_R209_REG_AGC_GAIN_MANU       (0x209 - 0x206)

#define PROPERTY_ADDR_R209                          (0x0600 | (0x209 - 0x206))
#define PROPERTY_GROUP_R209                         0x06
#define PROPERTY_INDEX_R209                         (0x209 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R20A                          (0x0600 | (0x20a - 0x206))
#define PROPERTY_GROUP_R20A                         0x06
#define PROPERTY_INDEX_R20A                         (0x20a - 0x206)

#define PROPERTY_POS_R20A_REG_CMP_SEL               4
#define PROPERTY_MSK_R20A_REG_CMP_SEL               (0x07 << PROPERTY_POS_R20A_REG_CMP_SEL)

#define PROPERTY_POS_R20A_REG_CMP_SEL2              0
#define PROPERTY_MSK_R20A_REG_CMP_SEL2              (0x07 << PROPERTY_POS_R20A_REG_CMP_SEL2)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R20B_REG_AGC_SET01_L          (0x0600 | (0x20b - 0x206))
#define PROPERTY_GROUP_R20B_REG_AGC_SET01_L         0x06
#define PROPERTY_INDEX_R20B_REG_AGC_SET01_L         (0x20b - 0x206)

#define PROPERTY_ADDR_R20B                          (0x0600 | (0x20b - 0x206))
#define PROPERTY_GROUP_R20B                         0x06
#define PROPERTY_INDEX_R20B                         (0x20b - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R20C_REG_AGC_SET01_H          (0x0600 | (0x20c - 0x206))
#define PROPERTY_GROUP_R20C_REG_AGC_SET01_H         0x06
#define PROPERTY_INDEX_R20C_REG_AGC_SET01_H         (0x20c - 0x206)

#define PROPERTY_ADDR_R20C                          (0x0600 | (0x20c - 0x206))
#define PROPERTY_GROUP_R20C                         0x06
#define PROPERTY_INDEX_R20C                         (0x20c - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R20D_REG_AGC_GAIN01           (0x0600 | (0x20d - 0x206))
#define PROPERTY_GROUP_R20D_REG_AGC_GAIN01          0x06
#define PROPERTY_INDEX_R20D_REG_AGC_GAIN01          (0x20d - 0x206)

#define PROPERTY_ADDR_R20D                          (0x0600 | (0x20d - 0x206))
#define PROPERTY_GROUP_R20D                         0x06
#define PROPERTY_INDEX_R20D                         (0x20d - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R20E_REG_AGC_TH02             (0x0600 | (0x20e - 0x206))
#define PROPERTY_GROUP_R20E_REG_AGC_TH02            0x06
#define PROPERTY_INDEX_R20E_REG_AGC_TH02            (0x20e - 0x206)

#define PROPERTY_ADDR_R20E                          (0x0600 | (0x20e - 0x206))
#define PROPERTY_GROUP_R20E                         0x06
#define PROPERTY_INDEX_R20E                         (0x20e - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R20F_REG_AGC_SET02_L          (0x0600 | (0x20f - 0x206))
#define PROPERTY_GROUP_R20F_REG_AGC_SET02_L         0x06
#define PROPERTY_INDEX_R20F_REG_AGC_SET02_L         (0x20f - 0x206)

#define PROPERTY_ADDR_R20F                          (0x0600 | (0x20f - 0x206))
#define PROPERTY_GROUP_R20F                         0x06
#define PROPERTY_INDEX_R20F                         (0x20f - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R210_REG_AGC_SET02_H          (0x0600 | (0x210 - 0x206))
#define PROPERTY_GROUP_R210_REG_AGC_SET02_H         0x06
#define PROPERTY_INDEX_R210_REG_AGC_SET02_H         (0x210 - 0x206)

#define PROPERTY_ADDR_R210                          (0x0600 | (0x210 - 0x206))
#define PROPERTY_GROUP_R210                         0x06
#define PROPERTY_INDEX_R210                         (0x210 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R211_REG_AGC_GAIN02           (0x0600 | (0x211 - 0x206))
#define PROPERTY_GROUP_R211_REG_AGC_GAIN02          0x06
#define PROPERTY_INDEX_R211_REG_AGC_GAIN02          (0x211 - 0x206)

#define PROPERTY_ADDR_R211                          (0x0600 | (0x211 - 0x206))
#define PROPERTY_GROUP_R211                         0x06
#define PROPERTY_INDEX_R211                         (0x211 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R212_REG_AGC_TH03             (0x0600 | (0x212 - 0x206))
#define PROPERTY_GROUP_R212_REG_AGC_TH03            0x06
#define PROPERTY_INDEX_R212_REG_AGC_TH03            (0x212 - 0x206)

#define PROPERTY_ADDR_R212                          (0x0600 | (0x212 - 0x206))
#define PROPERTY_GROUP_R212                         0x06
#define PROPERTY_INDEX_R212                         (0x212 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R213_REG_AGC_SET03_L          (0x0600 | (0x213 - 0x206))
#define PROPERTY_GROUP_R213_REG_AGC_SET03_L         0x06
#define PROPERTY_INDEX_R213_REG_AGC_SET03_L         (0x213 - 0x206)

#define PROPERTY_ADDR_R213                          (0x0600 | (0x213 - 0x206))
#define PROPERTY_GROUP_R213                         0x06
#define PROPERTY_INDEX_R213                         (0x213 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R214_REG_AGC_SET03_H          (0x0600 | (0x214 - 0x206))
#define PROPERTY_GROUP_R214_REG_AGC_SET03_H         0x06
#define PROPERTY_INDEX_R214_REG_AGC_SET03_H         (0x214 - 0x206)

#define PROPERTY_ADDR_R214                          (0x0600 | (0x214 - 0x206))
#define PROPERTY_GROUP_R214                         0x06
#define PROPERTY_INDEX_R214                         (0x214 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R215_REG_AGC_GAIN03           (0x0600 | (0x215 - 0x206))
#define PROPERTY_GROUP_R215_REG_AGC_GAIN03          0x06
#define PROPERTY_INDEX_R215_REG_AGC_GAIN03          (0x215 - 0x206)

#define PROPERTY_ADDR_R215                          (0x0600 | (0x215 - 0x206))
#define PROPERTY_GROUP_R215                         0x06
#define PROPERTY_INDEX_R215                         (0x215 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R216_REG_AGC_TH04             (0x0600 | (0x216 - 0x206))
#define PROPERTY_GROUP_R216_REG_AGC_TH04            0x06
#define PROPERTY_INDEX_R216_REG_AGC_TH04            (0x216 - 0x206)

#define PROPERTY_ADDR_R216                          (0x0600 | (0x216 - 0x206))
#define PROPERTY_GROUP_R216                         0x06
#define PROPERTY_INDEX_R216                         (0x216 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R217_REG_AGC_SET04_L          (0x0600 | (0x217 - 0x206))
#define PROPERTY_GROUP_R217_REG_AGC_SET04_L         0x06
#define PROPERTY_INDEX_R217_REG_AGC_SET04_L         (0x217 - 0x206)

#define PROPERTY_ADDR_R217                          (0x0600 | (0x217 - 0x206))
#define PROPERTY_GROUP_R217                         0x06
#define PROPERTY_INDEX_R217                         (0x217 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R218_REG_AGC_SET04_H          (0x0600 | (0x218 - 0x206))
#define PROPERTY_GROUP_R218_REG_AGC_SET04_H         0x06
#define PROPERTY_INDEX_R218_REG_AGC_SET04_H         (0x218 - 0x206)

#define PROPERTY_ADDR_R218                          (0x0600 | (0x218 - 0x206))
#define PROPERTY_GROUP_R218                         0x06
#define PROPERTY_INDEX_R218                         (0x218 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R219_REG_AGC_GAIN04           (0x0600 | (0x219 - 0x206))
#define PROPERTY_GROUP_R219_REG_AGC_GAIN04          0x06
#define PROPERTY_INDEX_R219_REG_AGC_GAIN04          (0x219 - 0x206)

#define PROPERTY_ADDR_R219                          (0x0600 | (0x219 - 0x206))
#define PROPERTY_GROUP_R219                         0x06
#define PROPERTY_INDEX_R219                         (0x219 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R21A_REG_AGC_TH05             (0x0600 | (0x21a - 0x206))
#define PROPERTY_GROUP_R21A_REG_AGC_TH05            0x06
#define PROPERTY_INDEX_R21A_REG_AGC_TH05            (0x21a - 0x206)

#define PROPERTY_ADDR_R21A                          (0x0600 | (0x21a - 0x206))
#define PROPERTY_GROUP_R21A                         0x06
#define PROPERTY_INDEX_R21A                         (0x21a - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R21B_REG_AGC_SET05_L          (0x0600 | (0x21b - 0x206))
#define PROPERTY_GROUP_R21B_REG_AGC_SET05_L         0x06
#define PROPERTY_INDEX_R21B_REG_AGC_SET05_L         (0x21b - 0x206)

#define PROPERTY_ADDR_R21B                          (0x0600 | (0x21b - 0x206))
#define PROPERTY_GROUP_R21B                         0x06
#define PROPERTY_INDEX_R21B                         (0x21b - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R21C_REG_AGC_SET05_H          (0x0600 | (0x21c - 0x206))
#define PROPERTY_GROUP_R21C_REG_AGC_SET05_H         0x06
#define PROPERTY_INDEX_R21C_REG_AGC_SET05_H         (0x21c - 0x206)

#define PROPERTY_ADDR_R21C                          (0x0600 | (0x21c - 0x206))
#define PROPERTY_GROUP_R21C                         0x06
#define PROPERTY_INDEX_R21C                         (0x21c - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R21D_REG_AGC_GAIN05           (0x0600 | (0x21d - 0x206))
#define PROPERTY_GROUP_R21D_REG_AGC_GAIN05          0x06
#define PROPERTY_INDEX_R21D_REG_AGC_GAIN05          (0x21d - 0x206)

#define PROPERTY_ADDR_R21D                          (0x0600 | (0x21d - 0x206))
#define PROPERTY_GROUP_R21D                         0x06
#define PROPERTY_INDEX_R21D                         (0x21d - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R21E_REG_AGC_TH06             (0x0600 | (0x21e - 0x206))
#define PROPERTY_GROUP_R21E_REG_AGC_TH06            0x06
#define PROPERTY_INDEX_R21E_REG_AGC_TH06            (0x21e - 0x206)

#define PROPERTY_ADDR_R21E                          (0x0600 | (0x21e - 0x206))
#define PROPERTY_GROUP_R21E                         0x06
#define PROPERTY_INDEX_R21E                         (0x21e - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R21F_REG_AGC_SET06_L          (0x0600 | (0x21f - 0x206))
#define PROPERTY_GROUP_R21F_REG_AGC_SET06_L         0x06
#define PROPERTY_INDEX_R21F_REG_AGC_SET06_L         (0x21f - 0x206)

#define PROPERTY_ADDR_R21F                          (0x0600 | (0x21f - 0x206))
#define PROPERTY_GROUP_R21F                         0x06
#define PROPERTY_INDEX_R21F                         (0x21f - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R220_REG_AGC_SET06_H          (0x0600 | (0x220 - 0x206))
#define PROPERTY_GROUP_R220_REG_AGC_SET06_H         0x06
#define PROPERTY_INDEX_R220_REG_AGC_SET06_H         (0x220 - 0x206)

#define PROPERTY_ADDR_R220                          (0x0600 | (0x220 - 0x206))
#define PROPERTY_GROUP_R220                         0x06
#define PROPERTY_INDEX_R220                         (0x220 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R221_REG_AGC_GAIN06           (0x0600 | (0x221 - 0x206))
#define PROPERTY_GROUP_R221_REG_AGC_GAIN06          0x06
#define PROPERTY_INDEX_R221_REG_AGC_GAIN06          (0x221 - 0x206)

#define PROPERTY_ADDR_R221                          (0x0600 | (0x221 - 0x206))
#define PROPERTY_GROUP_R221                         0x06
#define PROPERTY_INDEX_R221                         (0x221 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R222_REG_AGC_TH07             (0x0600 | (0x222 - 0x206))
#define PROPERTY_GROUP_R222_REG_AGC_TH07            0x06
#define PROPERTY_INDEX_R222_REG_AGC_TH07            (0x222 - 0x206)

#define PROPERTY_ADDR_R222                          (0x0600 | (0x222 - 0x206))
#define PROPERTY_GROUP_R222                         0x06
#define PROPERTY_INDEX_R222                         (0x222 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R223_REG_AGC_SET07_L          (0x0600 | (0x223 - 0x206))
#define PROPERTY_GROUP_R223_REG_AGC_SET07_L         0x06
#define PROPERTY_INDEX_R223_REG_AGC_SET07_L         (0x223 - 0x206)

#define PROPERTY_ADDR_R223                          (0x0600 | (0x223 - 0x206))
#define PROPERTY_GROUP_R223                         0x06
#define PROPERTY_INDEX_R223                         (0x223 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R224_REG_AGC_SET07_H          (0x0600 | (0x224 - 0x206))
#define PROPERTY_GROUP_R224_REG_AGC_SET07_H         0x06
#define PROPERTY_INDEX_R224_REG_AGC_SET07_H         (0x224 - 0x206)

#define PROPERTY_ADDR_R224                          (0x0600 | (0x224 - 0x206))
#define PROPERTY_GROUP_R224                         0x06
#define PROPERTY_INDEX_R224                         (0x224 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R225_REG_AGC_GAIN07           (0x0600 | (0x225 - 0x206))
#define PROPERTY_GROUP_R225_REG_AGC_GAIN07          0x06
#define PROPERTY_INDEX_R225_REG_AGC_GAIN07          (0x225 - 0x206)

#define PROPERTY_ADDR_R225                          (0x0600 | (0x225 - 0x206))
#define PROPERTY_GROUP_R225                         0x06
#define PROPERTY_INDEX_R225                         (0x225 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R226_REG_AGC_TH08             (0x0600 | (0x226 - 0x206))
#define PROPERTY_GROUP_R226_REG_AGC_TH08            0x06
#define PROPERTY_INDEX_R226_REG_AGC_TH08            (0x226 - 0x206)

#define PROPERTY_ADDR_R226                          (0x0600 | (0x226 - 0x206))
#define PROPERTY_GROUP_R226                         0x06
#define PROPERTY_INDEX_R226                         (0x226 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R227_REG_AGC_SET08_L          (0x0600 | (0x227 - 0x206))
#define PROPERTY_GROUP_R227_REG_AGC_SET08_L         0x06
#define PROPERTY_INDEX_R227_REG_AGC_SET08_L         (0x227 - 0x206)

#define PROPERTY_ADDR_R227                          (0x0600 | (0x227 - 0x206))
#define PROPERTY_GROUP_R227                         0x06
#define PROPERTY_INDEX_R227                         (0x227 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R228_REG_AGC_SET08_H          (0x0600 | (0x228 - 0x206))
#define PROPERTY_GROUP_R228_REG_AGC_SET08_H         0x06
#define PROPERTY_INDEX_R228_REG_AGC_SET08_H         (0x228 - 0x206)

#define PROPERTY_ADDR_R228                          (0x0600 | (0x228 - 0x206))
#define PROPERTY_GROUP_R228                         0x06
#define PROPERTY_INDEX_R228                         (0x228 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R229_REG_AGC_GAIN08           (0x0600 | (0x229 - 0x206))
#define PROPERTY_GROUP_R229_REG_AGC_GAIN08          0x06
#define PROPERTY_INDEX_R229_REG_AGC_GAIN08          (0x229 - 0x206)

#define PROPERTY_ADDR_R229                          (0x0600 | (0x229 - 0x206))
#define PROPERTY_GROUP_R229                         0x06
#define PROPERTY_INDEX_R229                         (0x229 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R22A_REG_BAS_GAIN_STEP        (0x0600 | (0x22a - 0x206))
#define PROPERTY_GROUP_R22A_REG_BAS_GAIN_STEP       0x06
#define PROPERTY_INDEX_R22A_REG_BAS_GAIN_STEP       (0x22a - 0x206)

#define PROPERTY_ADDR_R22A                          (0x0600 | (0x22a - 0x206))
#define PROPERTY_GROUP_R22A                         0x06
#define PROPERTY_INDEX_R22A                         (0x22a - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R22B                          (0x0600 | (0x22b - 0x206))
#define PROPERTY_GROUP_R22B                         0x06
#define PROPERTY_INDEX_R22B                         (0x22b - 0x206)

#define PROPERTY_POS_R22B_REG_UP_CNT_TH             4
#define PROPERTY_MSK_R22B_REG_UP_CNT_TH             (0x0f << PROPERTY_POS_R22B_REG_UP_CNT_TH)

#define PROPERTY_POS_R22B_REG_DOWN_CNT_TH           0
#define PROPERTY_MSK_R22B_REG_DOWN_CNT_TH           (0x0f << PROPERTY_POS_R22B_REG_DOWN_CNT_TH)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R22C_REG_GAIN_GAP             (0x0600 | (0x22c - 0x206))
#define PROPERTY_GROUP_R22C_REG_GAIN_GAP            0x06
#define PROPERTY_INDEX_R22C_REG_GAIN_GAP            (0x22c - 0x206)

#define PROPERTY_ADDR_R22C                          (0x0600 | (0x22c - 0x206))
#define PROPERTY_GROUP_R22C                         0x06
#define PROPERTY_INDEX_R22C                         (0x22c - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R22D                          (0x0600 | (0x22d - 0x206))
#define PROPERTY_GROUP_R22D                         0x06
#define PROPERTY_INDEX_R22D                         (0x22d - 0x206)

#define PROPERTY_POS_R22D_REG_AFC_END_LOCK_AGC_VLD  7
#define PROPERTY_MSK_R22D_REG_AFC_END_LOCK_AGC_VLD  (0x01 << PROPERTY_POS_R22D_REG_AFC_END_LOCK_AGC_VLD)

#define PROPERTY_POS_R22D_AGC_GAIN_CHG_VLD          6
#define PROPERTY_MSK_R22D_AGC_GAIN_CHG_VLD          (0x01 << PROPERTY_POS_R22D_AGC_GAIN_CHG_VLD)

#define PROPERTY_POS_R22D_AGC_GAIN_CHG_LEN          0
#define PROPERTY_MSK_R22D_AGC_GAIN_CHG_LEN          (0x3f << PROPERTY_POS_R22D_AGC_GAIN_CHG_LEN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R22E_ALPH_RBW                 (0x0600 | (0x22e - 0x206))
#define PROPERTY_GROUP_R22E_ALPH_RBW                0x06
#define PROPERTY_INDEX_R22E_ALPH_RBW                (0x22e - 0x206)

#define PROPERTY_ADDR_R22E                          (0x0600 | (0x22e - 0x206))
#define PROPERTY_GROUP_R22E                         0x06
#define PROPERTY_INDEX_R22E                         (0x22e - 0x206)

#define PROPERTY_POS_R22E_ALPH_RBW                  0
#define PROPERTY_MSK_R22E_ALPH_RBW                  (0x0f << PROPERTY_POS_R22E_ALPH_RBW)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R22F                          (0x0600 | (0x22f - 0x206))
#define PROPERTY_GROUP_R22F                         0x06
#define PROPERTY_INDEX_R22F                         (0x22f - 0x206)

#define PROPERTY_POS_R22F_ALPH_PARA1                4
#define PROPERTY_MSK_R22F_ALPH_PARA1                (0x0f << PROPERTY_POS_R22F_ALPH_PARA1)

#define PROPERTY_POS_R22F_ALPH_PARA2                0
#define PROPERTY_MSK_R22F_ALPH_PARA2                (0x0f << PROPERTY_POS_R22F_ALPH_PARA2)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R230_IIR_VLD_TIME_REG         (0x0600 | (0x230 - 0x206))
#define PROPERTY_GROUP_R230_IIR_VLD_TIME_REG        0x06
#define PROPERTY_INDEX_R230_IIR_VLD_TIME_REG        (0x230 - 0x206)

#define PROPERTY_ADDR_R230                          (0x0600 | (0x230 - 0x206))
#define PROPERTY_GROUP_R230                         0x06
#define PROPERTY_INDEX_R230                         (0x230 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R231_REG_PE_0DB               (0x0600 | (0x231 - 0x206))
#define PROPERTY_GROUP_R231_REG_PE_0DB              0x06
#define PROPERTY_INDEX_R231_REG_PE_0DB              (0x231 - 0x206)

#define PROPERTY_ADDR_R231                          (0x0600 | (0x231 - 0x206))
#define PROPERTY_GROUP_R231                         0x06
#define PROPERTY_INDEX_R231                         (0x231 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R232_REG_GAIN_VLD_TIME_L1     (0x0600 | (0x232 - 0x206))
#define PROPERTY_GROUP_R232_REG_GAIN_VLD_TIME_L1    0x06
#define PROPERTY_INDEX_R232_REG_GAIN_VLD_TIME_L1    (0x232 - 0x206)

#define PROPERTY_ADDR_R232                          (0x0600 | (0x232 - 0x206))
#define PROPERTY_GROUP_R232                         0x06
#define PROPERTY_INDEX_R232                         (0x232 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R233_REG_GAIN_VLD_TIME_L2     (0x0600 | (0x233 - 0x206))
#define PROPERTY_GROUP_R233_REG_GAIN_VLD_TIME_L2    0x06
#define PROPERTY_INDEX_R233_REG_GAIN_VLD_TIME_L2    (0x233 - 0x206)

#define PROPERTY_ADDR_R233                          (0x0600 | (0x233 - 0x206))
#define PROPERTY_GROUP_R233                         0x06
#define PROPERTY_INDEX_R233                         (0x233 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R234_REG_GAIN_VLD_TIME_L3     (0x0600 | (0x234 - 0x206))
#define PROPERTY_GROUP_R234_REG_GAIN_VLD_TIME_L3    0x06
#define PROPERTY_INDEX_R234_REG_GAIN_VLD_TIME_L3    (0x234 - 0x206)

#define PROPERTY_ADDR_R234                          (0x0600 | (0x234 - 0x206))
#define PROPERTY_GROUP_R234                         0x06
#define PROPERTY_INDEX_R234                         (0x234 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R235_REG_GAIN_VLD_TIME_H      (0x0600 | (0x235 - 0x206))
#define PROPERTY_GROUP_R235_REG_GAIN_VLD_TIME_H     0x06
#define PROPERTY_INDEX_R235_REG_GAIN_VLD_TIME_H     (0x235 - 0x206)

#define PROPERTY_ADDR_R235                          (0x0600 | (0x235 - 0x206))
#define PROPERTY_GROUP_R235                         0x06
#define PROPERTY_INDEX_R235                         (0x235 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R236                          (0x0600 | (0x236 - 0x206))
#define PROPERTY_GROUP_R236                         0x06
#define PROPERTY_INDEX_R236                         (0x236 - 0x206)

#define PROPERTY_POS_R236_DSM_FIFO_BYPASS           7
#define PROPERTY_MSK_R236_DSM_FIFO_BYPASS           (0x01 << PROPERTY_POS_R236_DSM_FIFO_BYPASS)

#define PROPERTY_POS_R236_DAC_CLK_INV_SEL           6
#define PROPERTY_MSK_R236_DAC_CLK_INV_SEL           (0x01 << PROPERTY_POS_R236_DAC_CLK_INV_SEL)

#define PROPERTY_POS_R236_PLL_DIG_EN                5
#define PROPERTY_MSK_R236_PLL_DIG_EN                (0x01 << PROPERTY_POS_R236_PLL_DIG_EN)

#define PROPERTY_POS_R236_CLK32M_GATE_BYPASS        4
#define PROPERTY_MSK_R236_CLK32M_GATE_BYPASS        (0x01 << PROPERTY_POS_R236_CLK32M_GATE_BYPASS)

#define PROPERTY_POS_R236_HI_LO_SET                 3
#define PROPERTY_MSK_R236_HI_LO_SET                 (0x01 << PROPERTY_POS_R236_HI_LO_SET)

#define PROPERTY_POS_R236_DLY_GATE_BYPASS           2
#define PROPERTY_MSK_R236_DLY_GATE_BYPASS           (0x01 << PROPERTY_POS_R236_DLY_GATE_BYPASS)

#define PROPERTY_POS_R236_LOCK_REG_EN               1
#define PROPERTY_MSK_R236_LOCK_REG_EN               (0x01 << PROPERTY_POS_R236_LOCK_REG_EN)

#define PROPERTY_POS_R236_DAC_MODE                  0
#define PROPERTY_MSK_R236_DAC_MODE                  (0x01 << PROPERTY_POS_R236_DAC_MODE)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R237                          (0x0600 | (0x237 - 0x206))
#define PROPERTY_GROUP_R237                         0x06
#define PROPERTY_INDEX_R237                         (0x237 - 0x206)

#define PROPERTY_POS_R237_FBDIV_RSTN_DLY_SEL        6
#define PROPERTY_MSK_R237_FBDIV_RSTN_DLY_SEL        (0x03 << PROPERTY_POS_R237_FBDIV_RSTN_DLY_SEL)

#define PROPERTY_POS_R237_DAC_BASL                  0
#define PROPERTY_MSK_R237_DAC_BASL                  (0x3f << PROPERTY_POS_R237_DAC_BASL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R238                          (0x0600 | (0x238 - 0x206))
#define PROPERTY_GROUP_R238                         0x06
#define PROPERTY_INDEX_R238                         (0x238 - 0x206)

#define PROPERTY_POS_R238_FBDIV_EN_OVRD_SEL         7
#define PROPERTY_MSK_R238_FBDIV_EN_OVRD_SEL         (0x01 << PROPERTY_POS_R238_FBDIV_EN_OVRD_SEL)

#define PROPERTY_POS_R238_FBDIV_EN_OVRD             6
#define PROPERTY_MSK_R238_FBDIV_EN_OVRD             (0x01 << PROPERTY_POS_R238_FBDIV_EN_OVRD)

#define PROPERTY_POS_R238_FBDIV_RSTN_OVRD_SEL       5
#define PROPERTY_MSK_R238_FBDIV_RSTN_OVRD_SEL       (0x01 << PROPERTY_POS_R238_FBDIV_RSTN_OVRD_SEL)

#define PROPERTY_POS_R238_FBDIV_RSTN_OVRD           4
#define PROPERTY_MSK_R238_FBDIV_RSTN_OVRD           (0x01 << PROPERTY_POS_R238_FBDIV_RSTN_OVRD)

#define PROPERTY_POS_R238_CALDIV_OVRD_SEL           3
#define PROPERTY_MSK_R238_CALDIV_OVRD_SEL           (0x01 << PROPERTY_POS_R238_CALDIV_OVRD_SEL)

#define PROPERTY_POS_R238_CAL_DIV_OVRD              2
#define PROPERTY_MSK_R238_CAL_DIV_OVRD              (0x01 << PROPERTY_POS_R238_CAL_DIV_OVRD)

#define PROPERTY_POS_R238_VCO_MAXCNT_SEL            0
#define PROPERTY_MSK_R238_VCO_MAXCNT_SEL            (0x03 << PROPERTY_POS_R238_VCO_MAXCNT_SEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R239                          (0x0600 | (0x239 - 0x206))
#define PROPERTY_GROUP_R239                         0x06
#define PROPERTY_INDEX_R239                         (0x239 - 0x206)

#define PROPERTY_POS_R239_CTL_DITHER_LSB            2
#define PROPERTY_MSK_R239_CTL_DITHER_LSB            (0x07 << PROPERTY_POS_R239_CTL_DITHER_LSB)

#define PROPERTY_POS_R239_CTL_DITHER_SHAPE          1
#define PROPERTY_MSK_R239_CTL_DITHER_SHAPE          (0x01 << PROPERTY_POS_R239_CTL_DITHER_SHAPE)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R23A_INT_MODE_EN              (0x0600 | (0x23a - 0x206))
#define PROPERTY_GROUP_R23A_INT_MODE_EN             0x06
#define PROPERTY_INDEX_R23A_INT_MODE_EN             (0x23a - 0x206)

#define PROPERTY_ADDR_R23A                          (0x0600 | (0x23a - 0x206))
#define PROPERTY_GROUP_R23A                         0x06
#define PROPERTY_INDEX_R23A                         (0x23a - 0x206)

#define PROPERTY_POS_R23A_INT_MODE_EN               0
#define PROPERTY_MSK_R23A_INT_MODE_EN               (0x01 << PROPERTY_POS_R23A_INT_MODE_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R23B                          (0x0600 | (0x23b - 0x206))
#define PROPERTY_GROUP_R23B                         0x06
#define PROPERTY_INDEX_R23B                         (0x23b - 0x206)

#define PROPERTY_POS_R23B_CLK_EN                    6
#define PROPERTY_MSK_R23B_CLK_EN                    (0x01 << PROPERTY_POS_R23B_CLK_EN)

#define PROPERTY_POS_R23B_DIV2_EN                   5
#define PROPERTY_MSK_R23B_DIV2_EN                   (0x01 << PROPERTY_POS_R23B_DIV2_EN)

#define PROPERTY_POS_R23B_DS_SHIFT                  4
#define PROPERTY_MSK_R23B_DS_SHIFT                  (0x01 << PROPERTY_POS_R23B_DS_SHIFT)

#define PROPERTY_POS_R23B_INV_CLK_EN                3
#define PROPERTY_MSK_R23B_INV_CLK_EN                (0x01 << PROPERTY_POS_R23B_INV_CLK_EN)

#define PROPERTY_POS_R23B_MASH2_MODE                2
#define PROPERTY_MSK_R23B_MASH2_MODE                (0x01 << PROPERTY_POS_R23B_MASH2_MODE)

#define PROPERTY_POS_R23B_SHIFT_OFFSET              1
#define PROPERTY_MSK_R23B_SHIFT_OFFSET              (0x01 << PROPERTY_POS_R23B_SHIFT_OFFSET)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R23C                          (0x0600 | (0x23c - 0x206))
#define PROPERTY_GROUP_R23C                         0x06
#define PROPERTY_INDEX_R23C                         (0x23c - 0x206)

#define PROPERTY_POS_R23C_PHASE_ADJ                 1
#define PROPERTY_MSK_R23C_PHASE_ADJ                 (0x01 << PROPERTY_POS_R23C_PHASE_ADJ)

#define PROPERTY_POS_R23C_IB_OB_DELAY_SEL           0
#define PROPERTY_MSK_R23C_IB_OB_DELAY_SEL           (0x01 << PROPERTY_POS_R23C_IB_OB_DELAY_SEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R23D_DELAY_LEN                (0x0600 | (0x23d - 0x206))
#define PROPERTY_GROUP_R23D_DELAY_LEN               0x06
#define PROPERTY_INDEX_R23D_DELAY_LEN               (0x23d - 0x206)

#define PROPERTY_ADDR_R23D                          (0x0600 | (0x23d - 0x206))
#define PROPERTY_GROUP_R23D                         0x06
#define PROPERTY_INDEX_R23D                         (0x23d - 0x206)

#define PROPERTY_POS_R23D_DELAY_LEN                 0
#define PROPERTY_MSK_R23D_DELAY_LEN                 (0x1f << PROPERTY_POS_R23D_DELAY_LEN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R23E                          (0x0600 | (0x23e - 0x206))
#define PROPERTY_GROUP_R23E                         0x06
#define PROPERTY_INDEX_R23E                         (0x23e - 0x206)

#define PROPERTY_POS_R23E_NDIV_OVRD_SEL             7
#define PROPERTY_MSK_R23E_NDIV_OVRD_SEL             (0x01 << PROPERTY_POS_R23E_NDIV_OVRD_SEL)

#define PROPERTY_POS_R23E_NDIV_OVRD                 0
#define PROPERTY_MSK_R23E_NDIV_OVRD                 (0x3f << PROPERTY_POS_R23E_NDIV_OVRD)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R23F                          (0x0600 | (0x23f - 0x206))
#define PROPERTY_GROUP_R23F                         0x06
#define PROPERTY_INDEX_R23F                         (0x23f - 0x206)

#define PROPERTY_POS_R23F_VCO_CODE_MANUL_RX_H       6
#define PROPERTY_MSK_R23F_VCO_CODE_MANUL_RX_H       (0x03 << PROPERTY_POS_R23F_VCO_CODE_MANUL_RX_H)

#define PROPERTY_POS_R23F_VCO_CODE_MANUL_TX         0
#define PROPERTY_MSK_R23F_VCO_CODE_MANUL_TX         (0x3f << PROPERTY_POS_R23F_VCO_CODE_MANUL_TX)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R240                          (0x0600 | (0x240 - 0x206))
#define PROPERTY_GROUP_R240                         0x06
#define PROPERTY_INDEX_R240                         (0x240 - 0x206)

#define PROPERTY_POS_R240_VCO_CODE_MANUL_RX         4
#define PROPERTY_MSK_R240_VCO_CODE_MANUL_RX         (0x0f << PROPERTY_POS_R240_VCO_CODE_MANUL_RX)

#define PROPERTY_POS_R240_VCO_CODE_MANUL_SEL        3
#define PROPERTY_MSK_R240_VCO_CODE_MANUL_SEL        (0x01 << PROPERTY_POS_R240_VCO_CODE_MANUL_SEL)

#define PROPERTY_POS_R240_VCO_DLY_SEL               1
#define PROPERTY_MSK_R240_VCO_DLY_SEL               (0x03 << PROPERTY_POS_R240_VCO_DLY_SEL)

#define PROPERTY_POS_R240_VCO_NO_DLY                0
#define PROPERTY_MSK_R240_VCO_NO_DLY                (0x01 << PROPERTY_POS_R240_VCO_NO_DLY)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R241                          (0x0600 | (0x241 - 0x206))
#define PROPERTY_GROUP_R241                         0x06
#define PROPERTY_INDEX_R241                         (0x241 - 0x206)

#define PROPERTY_POS_R241_CAL_DONE_FPGA             7
#define PROPERTY_MSK_R241_CAL_DONE_FPGA             (0x01 << PROPERTY_POS_R241_CAL_DONE_FPGA)

#define PROPERTY_POS_R241_PLL_RSTN_FPGA             6
#define PROPERTY_MSK_R241_PLL_RSTN_FPGA             (0x01 << PROPERTY_POS_R241_PLL_RSTN_FPGA)

#define PROPERTY_POS_R241_FRACN_OUT_SEL             5
#define PROPERTY_MSK_R241_FRACN_OUT_SEL             (0x01 << PROPERTY_POS_R241_FRACN_OUT_SEL)

#define PROPERTY_POS_R241_DA_IN_SEL                 4
#define PROPERTY_MSK_R241_DA_IN_SEL                 (0x01 << PROPERTY_POS_R241_DA_IN_SEL)

#define PROPERTY_POS_R241_PCLK_TEST_SEL             3
#define PROPERTY_MSK_R241_PCLK_TEST_SEL             (0x01 << PROPERTY_POS_R241_PCLK_TEST_SEL)

#define PROPERTY_POS_R241_CHIRP_DATA_SEL            2
#define PROPERTY_MSK_R241_CHIRP_DATA_SEL            (0x01 << PROPERTY_POS_R241_CHIRP_DATA_SEL)

#define PROPERTY_POS_R241_PLL_RSTN_SEL              1
#define PROPERTY_MSK_R241_PLL_RSTN_SEL              (0x01 << PROPERTY_POS_R241_PLL_RSTN_SEL)

#define PROPERTY_POS_R241_CAL_DONE_SEL              0
#define PROPERTY_MSK_R241_CAL_DONE_SEL              (0x01 << PROPERTY_POS_R241_CAL_DONE_SEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R242_CH_INT_NUM_SPI_L         (0x0600 | (0x242 - 0x206))
#define PROPERTY_GROUP_R242_CH_INT_NUM_SPI_L        0x06
#define PROPERTY_INDEX_R242_CH_INT_NUM_SPI_L        (0x242 - 0x206)

#define PROPERTY_ADDR_R242                          (0x0600 | (0x242 - 0x206))
#define PROPERTY_GROUP_R242                         0x06
#define PROPERTY_INDEX_R242                         (0x242 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R243_CH_INT_NUM_SPI_H         (0x0600 | (0x243 - 0x206))
#define PROPERTY_GROUP_R243_CH_INT_NUM_SPI_H        0x06
#define PROPERTY_INDEX_R243_CH_INT_NUM_SPI_H        (0x243 - 0x206)

#define PROPERTY_ADDR_R243                          (0x0600 | (0x243 - 0x206))
#define PROPERTY_GROUP_R243                         0x06
#define PROPERTY_INDEX_R243                         (0x243 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R244_CH_FRA_NUM_SPI_L1        (0x0600 | (0x244 - 0x206))
#define PROPERTY_GROUP_R244_CH_FRA_NUM_SPI_L1       0x06
#define PROPERTY_INDEX_R244_CH_FRA_NUM_SPI_L1       (0x244 - 0x206)

#define PROPERTY_ADDR_R244                          (0x0600 | (0x244 - 0x206))
#define PROPERTY_GROUP_R244                         0x06
#define PROPERTY_INDEX_R244                         (0x244 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R245_CH_FRA_NUM_SPI_L2        (0x0600 | (0x245 - 0x206))
#define PROPERTY_GROUP_R245_CH_FRA_NUM_SPI_L2       0x06
#define PROPERTY_INDEX_R245_CH_FRA_NUM_SPI_L2       (0x245 - 0x206)

#define PROPERTY_ADDR_R245                          (0x0600 | (0x245 - 0x206))
#define PROPERTY_GROUP_R245                         0x06
#define PROPERTY_INDEX_R245                         (0x245 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R246                          (0x0600 | (0x246 - 0x206))
#define PROPERTY_GROUP_R246                         0x06
#define PROPERTY_INDEX_R246                         (0x246 - 0x206)

#define PROPERTY_POS_R246_CHAN_DEC_MUX              7
#define PROPERTY_MSK_R246_CHAN_DEC_MUX              (0x01 << PROPERTY_POS_R246_CHAN_DEC_MUX)

#define PROPERTY_POS_R246_CH_FRA_NUM_SPI_H          0
#define PROPERTY_MSK_R246_CH_FRA_NUM_SPI_H          (0x7f << PROPERTY_POS_R246_CH_FRA_NUM_SPI_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R247                          (0x0600 | (0x247 - 0x206))
#define PROPERTY_GROUP_R247                         0x06
#define PROPERTY_INDEX_R247                         (0x247 - 0x206)

#define PROPERTY_POS_R247_DCDC_SOFT_EN              7
#define PROPERTY_MSK_R247_DCDC_SOFT_EN              (0x01 << PROPERTY_POS_R247_DCDC_SOFT_EN)

#define PROPERTY_POS_R247_BUCK_CAL_START_DELAY      5
#define PROPERTY_MSK_R247_BUCK_CAL_START_DELAY      (0x03 << PROPERTY_POS_R247_BUCK_CAL_START_DELAY)

#define PROPERTY_POS_R247_BUCK_CAL_LOOP_DELAY       3
#define PROPERTY_MSK_R247_BUCK_CAL_LOOP_DELAY       (0x03 << PROPERTY_POS_R247_BUCK_CAL_LOOP_DELAY)

#define PROPERTY_POS_R247_DCDC_EN                   2
#define PROPERTY_MSK_R247_DCDC_EN                   (0x01 << PROPERTY_POS_R247_DCDC_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R248_REG_DIG2_TX_DLY          (0x0600 | (0x248 - 0x206))
#define PROPERTY_GROUP_R248_REG_DIG2_TX_DLY         0x06
#define PROPERTY_INDEX_R248_REG_DIG2_TX_DLY         (0x248 - 0x206)

#define PROPERTY_ADDR_R248                          (0x0600 | (0x248 - 0x206))
#define PROPERTY_GROUP_R248                         0x06
#define PROPERTY_INDEX_R248                         (0x248 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R249_AGC_GAIN_GRID            (0x0600 | (0x249 - 0x206))
#define PROPERTY_GROUP_R249_AGC_GAIN_GRID           0x06
#define PROPERTY_INDEX_R249_AGC_GAIN_GRID           (0x249 - 0x206)

#define PROPERTY_ADDR_R249                          (0x0600 | (0x249 - 0x206))
#define PROPERTY_GROUP_R249                         0x06
#define PROPERTY_INDEX_R249                         (0x249 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R24A_AGC_SET_L                (0x0600 | (0x24a - 0x206))
#define PROPERTY_GROUP_R24A_AGC_SET_L               0x06
#define PROPERTY_INDEX_R24A_AGC_SET_L               (0x24a - 0x206)

#define PROPERTY_ADDR_R24A                          (0x0600 | (0x24a - 0x206))
#define PROPERTY_GROUP_R24A                         0x06
#define PROPERTY_INDEX_R24A                         (0x24a - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R24B_AGC_SET_H                (0x0600 | (0x24b - 0x206))
#define PROPERTY_GROUP_R24B_AGC_SET_H               0x06
#define PROPERTY_INDEX_R24B_AGC_SET_H               (0x24b - 0x206)

#define PROPERTY_ADDR_R24B                          (0x0600 | (0x24b - 0x206))
#define PROPERTY_GROUP_R24B                         0x06
#define PROPERTY_INDEX_R24B                         (0x24b - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R24C_REG_PR_MATCH_LOCK_AGC_TH (0x0600 | (0x24c - 0x206))
#define PROPERTY_GROUP_R24C_REG_PR_MATCH_LOCK_AGC_TH 0x06
#define PROPERTY_INDEX_R24C_REG_PR_MATCH_LOCK_AGC_TH (0x24c - 0x206)

#define PROPERTY_ADDR_R24C                          (0x0600 | (0x24c - 0x206))
#define PROPERTY_GROUP_R24C                         0x06
#define PROPERTY_INDEX_R24C                         (0x24c - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R24D_REG_TH_OFST              (0x0600 | (0x24d - 0x206))
#define PROPERTY_GROUP_R24D_REG_TH_OFST             0x06
#define PROPERTY_INDEX_R24D_REG_TH_OFST             (0x24d - 0x206)

#define PROPERTY_ADDR_R24D                          (0x0600 | (0x24d - 0x206))
#define PROPERTY_GROUP_R24D                         0x06
#define PROPERTY_INDEX_R24D                         (0x24d - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R24E_DECIMAT_1ST_MANU_NUM_L1  (0x0600 | (0x24e - 0x206))
#define PROPERTY_GROUP_R24E_DECIMAT_1ST_MANU_NUM_L1 0x06
#define PROPERTY_INDEX_R24E_DECIMAT_1ST_MANU_NUM_L1 (0x24e - 0x206)

#define PROPERTY_ADDR_R24E                          (0x0600 | (0x24e - 0x206))
#define PROPERTY_GROUP_R24E                         0x06
#define PROPERTY_INDEX_R24E                         (0x24e - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R24F_DECIMAT_1ST_MANU_NUM_L2  (0x0600 | (0x24f - 0x206))
#define PROPERTY_GROUP_R24F_DECIMAT_1ST_MANU_NUM_L2 0x06
#define PROPERTY_INDEX_R24F_DECIMAT_1ST_MANU_NUM_L2 (0x24f - 0x206)

#define PROPERTY_ADDR_R24F                          (0x0600 | (0x24f - 0x206))
#define PROPERTY_GROUP_R24F                         0x06
#define PROPERTY_INDEX_R24F                         (0x24f - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R250_DECIMAT_LAST_MANU_NUM_L1 (0x0600 | (0x250 - 0x206))
#define PROPERTY_GROUP_R250_DECIMAT_LAST_MANU_NUM_L1 0x06
#define PROPERTY_INDEX_R250_DECIMAT_LAST_MANU_NUM_L1 (0x250 - 0x206)

#define PROPERTY_ADDR_R250                          (0x0600 | (0x250 - 0x206))
#define PROPERTY_GROUP_R250                         0x06
#define PROPERTY_INDEX_R250                         (0x250 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R251_DECIMAT_LAST_MANU_NUM_L2 (0x0600 | (0x251 - 0x206))
#define PROPERTY_GROUP_R251_DECIMAT_LAST_MANU_NUM_L2 0x06
#define PROPERTY_INDEX_R251_DECIMAT_LAST_MANU_NUM_L2 (0x251 - 0x206)

#define PROPERTY_ADDR_R251                          (0x0600 | (0x251 - 0x206))
#define PROPERTY_GROUP_R251                         0x06
#define PROPERTY_INDEX_R251                         (0x251 - 0x206)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R252                          (0x0600 | (0x252 - 0x206))
#define PROPERTY_GROUP_R252                         0x06
#define PROPERTY_INDEX_R252                         (0x252 - 0x206)

#define PROPERTY_POS_R252_DECIMAT_1ST_MANU_EN       7
#define PROPERTY_MSK_R252_DECIMAT_1ST_MANU_EN       (0x01 << PROPERTY_POS_R252_DECIMAT_1ST_MANU_EN)

#define PROPERTY_POS_R252_DECIMAT_LAST_MANU_EN      6
#define PROPERTY_MSK_R252_DECIMAT_LAST_MANU_EN      (0x01 << PROPERTY_POS_R252_DECIMAT_LAST_MANU_EN)

#define PROPERTY_POS_R252_DECIMAT_1ST_MANU_NUM_H    3
#define PROPERTY_MSK_R252_DECIMAT_1ST_MANU_NUM_H    (0x07 << PROPERTY_POS_R252_DECIMAT_1ST_MANU_NUM_H)

#define PROPERTY_POS_R252_DECIMAT_LAST_MANU_NUM_H   0
#define PROPERTY_MSK_R252_DECIMAT_LAST_MANU_NUM_H   (0x07 << PROPERTY_POS_R252_DECIMAT_LAST_MANU_NUM_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R253_DCDC_IMAX_CAL_CODE       (0x0600 | (0x253 - 0x206))
#define PROPERTY_GROUP_R253_DCDC_IMAX_CAL_CODE      0x06
#define PROPERTY_INDEX_R253_DCDC_IMAX_CAL_CODE      (0x253 - 0x206)

#define PROPERTY_ADDR_R253                          (0x0600 | (0x253 - 0x206))
#define PROPERTY_GROUP_R253                         0x06
#define PROPERTY_INDEX_R253                         (0x253 - 0x206)

#define PROPERTY_POS_R253_DCDC_IMAX_CAL_CODE        0
#define PROPERTY_MSK_R253_DCDC_IMAX_CAL_CODE        (0x1f << PROPERTY_POS_R253_DCDC_IMAX_CAL_CODE)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R254_DCDC_ZERO_CAL_CODE       (0x0600 | (0x254 - 0x206))
#define PROPERTY_GROUP_R254_DCDC_ZERO_CAL_CODE      0x06
#define PROPERTY_INDEX_R254_DCDC_ZERO_CAL_CODE      (0x254 - 0x206)

#define PROPERTY_ADDR_R254                          (0x0600 | (0x254 - 0x206))
#define PROPERTY_GROUP_R254                         0x06
#define PROPERTY_INDEX_R254                         (0x254 - 0x206)

#define PROPERTY_POS_R254_DCDC_ZERO_CAL_CODE        0
#define PROPERTY_MSK_R254_DCDC_ZERO_CAL_CODE        (0x1f << PROPERTY_POS_R254_DCDC_ZERO_CAL_CODE)

/***************************************************************************************************
 * GROUP7 ����
 **************************************************************************************************/
#define PROPERTY_ADDR_R286_REG_FLTR_5TH_COEF0_L     (0x0700 | (0x286 - 0x286))
#define PROPERTY_GROUP_R286_REG_FLTR_5TH_COEF0_L    0x07
#define PROPERTY_INDEX_R286_REG_FLTR_5TH_COEF0_L    (0x286 - 0x286)

#define PROPERTY_ADDR_R286                          (0x0700 | (0x286 - 0x286))
#define PROPERTY_GROUP_R286                         0x07
#define PROPERTY_INDEX_R286                         (0x286 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R287_REG_FLTR_5TH_COEF0_H     (0x0700 | (0x287 - 0x286))
#define PROPERTY_GROUP_R287_REG_FLTR_5TH_COEF0_H    0x07
#define PROPERTY_INDEX_R287_REG_FLTR_5TH_COEF0_H    (0x287 - 0x286)

#define PROPERTY_ADDR_R287                          (0x0700 | (0x287 - 0x286))
#define PROPERTY_GROUP_R287                         0x07
#define PROPERTY_INDEX_R287                         (0x287 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R288_REG_FLTR_5TH_COEF1_L     (0x0700 | (0x288 - 0x286))
#define PROPERTY_GROUP_R288_REG_FLTR_5TH_COEF1_L    0x07
#define PROPERTY_INDEX_R288_REG_FLTR_5TH_COEF1_L    (0x288 - 0x286)

#define PROPERTY_ADDR_R288                          (0x0700 | (0x288 - 0x286))
#define PROPERTY_GROUP_R288                         0x07
#define PROPERTY_INDEX_R288                         (0x288 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R289_REG_FLTR_5TH_COEF1_H     (0x0700 | (0x289 - 0x286))
#define PROPERTY_GROUP_R289_REG_FLTR_5TH_COEF1_H    0x07
#define PROPERTY_INDEX_R289_REG_FLTR_5TH_COEF1_H    (0x289 - 0x286)

#define PROPERTY_ADDR_R289                          (0x0700 | (0x289 - 0x286))
#define PROPERTY_GROUP_R289                         0x07
#define PROPERTY_INDEX_R289                         (0x289 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R28A_REG_FLTR_5TH_COEF2_L     (0x0700 | (0x28a - 0x286))
#define PROPERTY_GROUP_R28A_REG_FLTR_5TH_COEF2_L    0x07
#define PROPERTY_INDEX_R28A_REG_FLTR_5TH_COEF2_L    (0x28a - 0x286)

#define PROPERTY_ADDR_R28A                          (0x0700 | (0x28a - 0x286))
#define PROPERTY_GROUP_R28A                         0x07
#define PROPERTY_INDEX_R28A                         (0x28a - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R28B_REG_FLTR_5TH_COEF2_H     (0x0700 | (0x28b - 0x286))
#define PROPERTY_GROUP_R28B_REG_FLTR_5TH_COEF2_H    0x07
#define PROPERTY_INDEX_R28B_REG_FLTR_5TH_COEF2_H    (0x28b - 0x286)

#define PROPERTY_ADDR_R28B                          (0x0700 | (0x28b - 0x286))
#define PROPERTY_GROUP_R28B                         0x07
#define PROPERTY_INDEX_R28B                         (0x28b - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R28C_REG_FLTR_5TH_COEF3_L     (0x0700 | (0x28c - 0x286))
#define PROPERTY_GROUP_R28C_REG_FLTR_5TH_COEF3_L    0x07
#define PROPERTY_INDEX_R28C_REG_FLTR_5TH_COEF3_L    (0x28c - 0x286)

#define PROPERTY_ADDR_R28C                          (0x0700 | (0x28c - 0x286))
#define PROPERTY_GROUP_R28C                         0x07
#define PROPERTY_INDEX_R28C                         (0x28c - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R28D_REG_FLTR_5TH_COEF3_H     (0x0700 | (0x28d - 0x286))
#define PROPERTY_GROUP_R28D_REG_FLTR_5TH_COEF3_H    0x07
#define PROPERTY_INDEX_R28D_REG_FLTR_5TH_COEF3_H    (0x28d - 0x286)

#define PROPERTY_ADDR_R28D                          (0x0700 | (0x28d - 0x286))
#define PROPERTY_GROUP_R28D                         0x07
#define PROPERTY_INDEX_R28D                         (0x28d - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R28E_REG_FLTR_5TH_COEF4_L     (0x0700 | (0x28e - 0x286))
#define PROPERTY_GROUP_R28E_REG_FLTR_5TH_COEF4_L    0x07
#define PROPERTY_INDEX_R28E_REG_FLTR_5TH_COEF4_L    (0x28e - 0x286)

#define PROPERTY_ADDR_R28E                          (0x0700 | (0x28e - 0x286))
#define PROPERTY_GROUP_R28E                         0x07
#define PROPERTY_INDEX_R28E                         (0x28e - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R28F_REG_FLTR_5TH_COEF4_H     (0x0700 | (0x28f - 0x286))
#define PROPERTY_GROUP_R28F_REG_FLTR_5TH_COEF4_H    0x07
#define PROPERTY_INDEX_R28F_REG_FLTR_5TH_COEF4_H    (0x28f - 0x286)

#define PROPERTY_ADDR_R28F                          (0x0700 | (0x28f - 0x286))
#define PROPERTY_GROUP_R28F                         0x07
#define PROPERTY_INDEX_R28F                         (0x28f - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R290_REG_FLTR_5TH_COEF5_L     (0x0700 | (0x290 - 0x286))
#define PROPERTY_GROUP_R290_REG_FLTR_5TH_COEF5_L    0x07
#define PROPERTY_INDEX_R290_REG_FLTR_5TH_COEF5_L    (0x290 - 0x286)

#define PROPERTY_ADDR_R290                          (0x0700 | (0x290 - 0x286))
#define PROPERTY_GROUP_R290                         0x07
#define PROPERTY_INDEX_R290                         (0x290 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R291_REG_FLTR_5TH_COEF5_H     (0x0700 | (0x291 - 0x286))
#define PROPERTY_GROUP_R291_REG_FLTR_5TH_COEF5_H    0x07
#define PROPERTY_INDEX_R291_REG_FLTR_5TH_COEF5_H    (0x291 - 0x286)

#define PROPERTY_ADDR_R291                          (0x0700 | (0x291 - 0x286))
#define PROPERTY_GROUP_R291                         0x07
#define PROPERTY_INDEX_R291                         (0x291 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R292_REG_FLTR_5TH_COEF6_L     (0x0700 | (0x292 - 0x286))
#define PROPERTY_GROUP_R292_REG_FLTR_5TH_COEF6_L    0x07
#define PROPERTY_INDEX_R292_REG_FLTR_5TH_COEF6_L    (0x292 - 0x286)

#define PROPERTY_ADDR_R292                          (0x0700 | (0x292 - 0x286))
#define PROPERTY_GROUP_R292                         0x07
#define PROPERTY_INDEX_R292                         (0x292 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R293_REG_FLTR_5TH_COEF6_H     (0x0700 | (0x293 - 0x286))
#define PROPERTY_GROUP_R293_REG_FLTR_5TH_COEF6_H    0x07
#define PROPERTY_INDEX_R293_REG_FLTR_5TH_COEF6_H    (0x293 - 0x286)

#define PROPERTY_ADDR_R293                          (0x0700 | (0x293 - 0x286))
#define PROPERTY_GROUP_R293                         0x07
#define PROPERTY_INDEX_R293                         (0x293 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R294_REG_FLTR_5TH_COEF7_L     (0x0700 | (0x294 - 0x286))
#define PROPERTY_GROUP_R294_REG_FLTR_5TH_COEF7_L    0x07
#define PROPERTY_INDEX_R294_REG_FLTR_5TH_COEF7_L    (0x294 - 0x286)

#define PROPERTY_ADDR_R294                          (0x0700 | (0x294 - 0x286))
#define PROPERTY_GROUP_R294                         0x07
#define PROPERTY_INDEX_R294                         (0x294 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R295_REG_FLTR_5TH_COEF7_H     (0x0700 | (0x295 - 0x286))
#define PROPERTY_GROUP_R295_REG_FLTR_5TH_COEF7_H    0x07
#define PROPERTY_INDEX_R295_REG_FLTR_5TH_COEF7_H    (0x295 - 0x286)

#define PROPERTY_ADDR_R295                          (0x0700 | (0x295 - 0x286))
#define PROPERTY_GROUP_R295                         0x07
#define PROPERTY_INDEX_R295                         (0x295 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R296_REG_FLTR_5TH_COEF8_L     (0x0700 | (0x296 - 0x286))
#define PROPERTY_GROUP_R296_REG_FLTR_5TH_COEF8_L    0x07
#define PROPERTY_INDEX_R296_REG_FLTR_5TH_COEF8_L    (0x296 - 0x286)

#define PROPERTY_ADDR_R296                          (0x0700 | (0x296 - 0x286))
#define PROPERTY_GROUP_R296                         0x07
#define PROPERTY_INDEX_R296                         (0x296 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R297_REG_FLTR_5TH_COEF8_H     (0x0700 | (0x297 - 0x286))
#define PROPERTY_GROUP_R297_REG_FLTR_5TH_COEF8_H    0x07
#define PROPERTY_INDEX_R297_REG_FLTR_5TH_COEF8_H    (0x297 - 0x286)

#define PROPERTY_ADDR_R297                          (0x0700 | (0x297 - 0x286))
#define PROPERTY_GROUP_R297                         0x07
#define PROPERTY_INDEX_R297                         (0x297 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R298_REG_FLTR_5TH_COEF9_L     (0x0700 | (0x298 - 0x286))
#define PROPERTY_GROUP_R298_REG_FLTR_5TH_COEF9_L    0x07
#define PROPERTY_INDEX_R298_REG_FLTR_5TH_COEF9_L    (0x298 - 0x286)

#define PROPERTY_ADDR_R298                          (0x0700 | (0x298 - 0x286))
#define PROPERTY_GROUP_R298                         0x07
#define PROPERTY_INDEX_R298                         (0x298 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R299_REG_FLTR_5TH_COEF9_H     (0x0700 | (0x299 - 0x286))
#define PROPERTY_GROUP_R299_REG_FLTR_5TH_COEF9_H    0x07
#define PROPERTY_INDEX_R299_REG_FLTR_5TH_COEF9_H    (0x299 - 0x286)

#define PROPERTY_ADDR_R299                          (0x0700 | (0x299 - 0x286))
#define PROPERTY_GROUP_R299                         0x07
#define PROPERTY_INDEX_R299                         (0x299 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R29A_REG_FLTR_5TH_COEF10_L    (0x0700 | (0x29a - 0x286))
#define PROPERTY_GROUP_R29A_REG_FLTR_5TH_COEF10_L   0x07
#define PROPERTY_INDEX_R29A_REG_FLTR_5TH_COEF10_L   (0x29a - 0x286)

#define PROPERTY_ADDR_R29A                          (0x0700 | (0x29a - 0x286))
#define PROPERTY_GROUP_R29A                         0x07
#define PROPERTY_INDEX_R29A                         (0x29a - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R29B_REG_FLTR_5TH_COEF10_H    (0x0700 | (0x29b - 0x286))
#define PROPERTY_GROUP_R29B_REG_FLTR_5TH_COEF10_H   0x07
#define PROPERTY_INDEX_R29B_REG_FLTR_5TH_COEF10_H   (0x29b - 0x286)

#define PROPERTY_ADDR_R29B                          (0x0700 | (0x29b - 0x286))
#define PROPERTY_GROUP_R29B                         0x07
#define PROPERTY_INDEX_R29B                         (0x29b - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R29C_REG_FLTR_5TH_COEF11_L    (0x0700 | (0x29c - 0x286))
#define PROPERTY_GROUP_R29C_REG_FLTR_5TH_COEF11_L   0x07
#define PROPERTY_INDEX_R29C_REG_FLTR_5TH_COEF11_L   (0x29c - 0x286)

#define PROPERTY_ADDR_R29C                          (0x0700 | (0x29c - 0x286))
#define PROPERTY_GROUP_R29C                         0x07
#define PROPERTY_INDEX_R29C                         (0x29c - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R29D_REG_FLTR_5TH_COEF11_H    (0x0700 | (0x29d - 0x286))
#define PROPERTY_GROUP_R29D_REG_FLTR_5TH_COEF11_H   0x07
#define PROPERTY_INDEX_R29D_REG_FLTR_5TH_COEF11_H   (0x29d - 0x286)

#define PROPERTY_ADDR_R29D                          (0x0700 | (0x29d - 0x286))
#define PROPERTY_GROUP_R29D                         0x07
#define PROPERTY_INDEX_R29D                         (0x29d - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R29E_REG_FLTR_5TH_COEF12_L    (0x0700 | (0x29e - 0x286))
#define PROPERTY_GROUP_R29E_REG_FLTR_5TH_COEF12_L   0x07
#define PROPERTY_INDEX_R29E_REG_FLTR_5TH_COEF12_L   (0x29e - 0x286)

#define PROPERTY_ADDR_R29E                          (0x0700 | (0x29e - 0x286))
#define PROPERTY_GROUP_R29E                         0x07
#define PROPERTY_INDEX_R29E                         (0x29e - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R29F_REG_FLTR_5TH_COEF12_H    (0x0700 | (0x29f - 0x286))
#define PROPERTY_GROUP_R29F_REG_FLTR_5TH_COEF12_H   0x07
#define PROPERTY_INDEX_R29F_REG_FLTR_5TH_COEF12_H   (0x29f - 0x286)

#define PROPERTY_ADDR_R29F                          (0x0700 | (0x29f - 0x286))
#define PROPERTY_GROUP_R29F                         0x07
#define PROPERTY_INDEX_R29F                         (0x29f - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2A0_REG_FLTR_5TH_COEF13_L    (0x0700 | (0x2a0 - 0x286))
#define PROPERTY_GROUP_R2A0_REG_FLTR_5TH_COEF13_L   0x07
#define PROPERTY_INDEX_R2A0_REG_FLTR_5TH_COEF13_L   (0x2a0 - 0x286)

#define PROPERTY_ADDR_R2A0                          (0x0700 | (0x2a0 - 0x286))
#define PROPERTY_GROUP_R2A0                         0x07
#define PROPERTY_INDEX_R2A0                         (0x2a0 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2A1_REG_FLTR_5TH_COEF13_H    (0x0700 | (0x2a1 - 0x286))
#define PROPERTY_GROUP_R2A1_REG_FLTR_5TH_COEF13_H   0x07
#define PROPERTY_INDEX_R2A1_REG_FLTR_5TH_COEF13_H   (0x2a1 - 0x286)

#define PROPERTY_ADDR_R2A1                          (0x0700 | (0x2a1 - 0x286))
#define PROPERTY_GROUP_R2A1                         0x07
#define PROPERTY_INDEX_R2A1                         (0x2a1 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2A2_REG_FLTR_5TH_COEF14_L    (0x0700 | (0x2a2 - 0x286))
#define PROPERTY_GROUP_R2A2_REG_FLTR_5TH_COEF14_L   0x07
#define PROPERTY_INDEX_R2A2_REG_FLTR_5TH_COEF14_L   (0x2a2 - 0x286)

#define PROPERTY_ADDR_R2A2                          (0x0700 | (0x2a2 - 0x286))
#define PROPERTY_GROUP_R2A2                         0x07
#define PROPERTY_INDEX_R2A2                         (0x2a2 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2A3_REG_FLTR_5TH_COEF14_H    (0x0700 | (0x2a3 - 0x286))
#define PROPERTY_GROUP_R2A3_REG_FLTR_5TH_COEF14_H   0x07
#define PROPERTY_INDEX_R2A3_REG_FLTR_5TH_COEF14_H   (0x2a3 - 0x286)

#define PROPERTY_ADDR_R2A3                          (0x0700 | (0x2a3 - 0x286))
#define PROPERTY_GROUP_R2A3                         0x07
#define PROPERTY_INDEX_R2A3                         (0x2a3 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2A4_REG_FLTR_5TH_COEF15_L    (0x0700 | (0x2a4 - 0x286))
#define PROPERTY_GROUP_R2A4_REG_FLTR_5TH_COEF15_L   0x07
#define PROPERTY_INDEX_R2A4_REG_FLTR_5TH_COEF15_L   (0x2a4 - 0x286)

#define PROPERTY_ADDR_R2A4                          (0x0700 | (0x2a4 - 0x286))
#define PROPERTY_GROUP_R2A4                         0x07
#define PROPERTY_INDEX_R2A4                         (0x2a4 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2A5_REG_FLTR_5TH_COEF15_H    (0x0700 | (0x2a5 - 0x286))
#define PROPERTY_GROUP_R2A5_REG_FLTR_5TH_COEF15_H   0x07
#define PROPERTY_INDEX_R2A5_REG_FLTR_5TH_COEF15_H   (0x2a5 - 0x286)

#define PROPERTY_ADDR_R2A5                          (0x0700 | (0x2a5 - 0x286))
#define PROPERTY_GROUP_R2A5                         0x07
#define PROPERTY_INDEX_R2A5                         (0x2a5 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2A6_REG_FLTR_5TH_COEF16_L    (0x0700 | (0x2a6 - 0x286))
#define PROPERTY_GROUP_R2A6_REG_FLTR_5TH_COEF16_L   0x07
#define PROPERTY_INDEX_R2A6_REG_FLTR_5TH_COEF16_L   (0x2a6 - 0x286)

#define PROPERTY_ADDR_R2A6                          (0x0700 | (0x2a6 - 0x286))
#define PROPERTY_GROUP_R2A6                         0x07
#define PROPERTY_INDEX_R2A6                         (0x2a6 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2A7_REG_FLTR_5TH_COEF16_H    (0x0700 | (0x2a7 - 0x286))
#define PROPERTY_GROUP_R2A7_REG_FLTR_5TH_COEF16_H   0x07
#define PROPERTY_INDEX_R2A7_REG_FLTR_5TH_COEF16_H   (0x2a7 - 0x286)

#define PROPERTY_ADDR_R2A7                          (0x0700 | (0x2a7 - 0x286))
#define PROPERTY_GROUP_R2A7                         0x07
#define PROPERTY_INDEX_R2A7                         (0x2a7 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2A8_REG_FLTR_5TH_COEF17_L    (0x0700 | (0x2a8 - 0x286))
#define PROPERTY_GROUP_R2A8_REG_FLTR_5TH_COEF17_L   0x07
#define PROPERTY_INDEX_R2A8_REG_FLTR_5TH_COEF17_L   (0x2a8 - 0x286)

#define PROPERTY_ADDR_R2A8                          (0x0700 | (0x2a8 - 0x286))
#define PROPERTY_GROUP_R2A8                         0x07
#define PROPERTY_INDEX_R2A8                         (0x2a8 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2A9_REG_FLTR_5TH_COEF17_H    (0x0700 | (0x2a9 - 0x286))
#define PROPERTY_GROUP_R2A9_REG_FLTR_5TH_COEF17_H   0x07
#define PROPERTY_INDEX_R2A9_REG_FLTR_5TH_COEF17_H   (0x2a9 - 0x286)

#define PROPERTY_ADDR_R2A9                          (0x0700 | (0x2a9 - 0x286))
#define PROPERTY_GROUP_R2A9                         0x07
#define PROPERTY_INDEX_R2A9                         (0x2a9 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2AA_REG_FLTR_5TH_COEF18_L    (0x0700 | (0x2aa - 0x286))
#define PROPERTY_GROUP_R2AA_REG_FLTR_5TH_COEF18_L   0x07
#define PROPERTY_INDEX_R2AA_REG_FLTR_5TH_COEF18_L   (0x2aa - 0x286)

#define PROPERTY_ADDR_R2AA                          (0x0700 | (0x2aa - 0x286))
#define PROPERTY_GROUP_R2AA                         0x07
#define PROPERTY_INDEX_R2AA                         (0x2aa - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2AB_REG_FLTR_5TH_COEF18_H    (0x0700 | (0x2ab - 0x286))
#define PROPERTY_GROUP_R2AB_REG_FLTR_5TH_COEF18_H   0x07
#define PROPERTY_INDEX_R2AB_REG_FLTR_5TH_COEF18_H   (0x2ab - 0x286)

#define PROPERTY_ADDR_R2AB                          (0x0700 | (0x2ab - 0x286))
#define PROPERTY_GROUP_R2AB                         0x07
#define PROPERTY_INDEX_R2AB                         (0x2ab - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2AC_REG_FLTR_5TH_COEF19_L    (0x0700 | (0x2ac - 0x286))
#define PROPERTY_GROUP_R2AC_REG_FLTR_5TH_COEF19_L   0x07
#define PROPERTY_INDEX_R2AC_REG_FLTR_5TH_COEF19_L   (0x2ac - 0x286)

#define PROPERTY_ADDR_R2AC                          (0x0700 | (0x2ac - 0x286))
#define PROPERTY_GROUP_R2AC                         0x07
#define PROPERTY_INDEX_R2AC                         (0x2ac - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2AD_REG_FLTR_5TH_COEF19_H    (0x0700 | (0x2ad - 0x286))
#define PROPERTY_GROUP_R2AD_REG_FLTR_5TH_COEF19_H   0x07
#define PROPERTY_INDEX_R2AD_REG_FLTR_5TH_COEF19_H   (0x2ad - 0x286)

#define PROPERTY_ADDR_R2AD                          (0x0700 | (0x2ad - 0x286))
#define PROPERTY_GROUP_R2AD                         0x07
#define PROPERTY_INDEX_R2AD                         (0x2ad - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2AE_REG_FLTR_5TH_COEF20_L    (0x0700 | (0x2ae - 0x286))
#define PROPERTY_GROUP_R2AE_REG_FLTR_5TH_COEF20_L   0x07
#define PROPERTY_INDEX_R2AE_REG_FLTR_5TH_COEF20_L   (0x2ae - 0x286)

#define PROPERTY_ADDR_R2AE                          (0x0700 | (0x2ae - 0x286))
#define PROPERTY_GROUP_R2AE                         0x07
#define PROPERTY_INDEX_R2AE                         (0x2ae - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2AF_REG_FLTR_5TH_COEF20_H    (0x0700 | (0x2af - 0x286))
#define PROPERTY_GROUP_R2AF_REG_FLTR_5TH_COEF20_H   0x07
#define PROPERTY_INDEX_R2AF_REG_FLTR_5TH_COEF20_H   (0x2af - 0x286)

#define PROPERTY_ADDR_R2AF                          (0x0700 | (0x2af - 0x286))
#define PROPERTY_GROUP_R2AF                         0x07
#define PROPERTY_INDEX_R2AF                         (0x2af - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2B0_REG_FLTR_5TH_COEF21_L    (0x0700 | (0x2b0 - 0x286))
#define PROPERTY_GROUP_R2B0_REG_FLTR_5TH_COEF21_L   0x07
#define PROPERTY_INDEX_R2B0_REG_FLTR_5TH_COEF21_L   (0x2b0 - 0x286)

#define PROPERTY_ADDR_R2B0                          (0x0700 | (0x2b0 - 0x286))
#define PROPERTY_GROUP_R2B0                         0x07
#define PROPERTY_INDEX_R2B0                         (0x2b0 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2B1_REG_FLTR_5TH_COEF21_H    (0x0700 | (0x2b1 - 0x286))
#define PROPERTY_GROUP_R2B1_REG_FLTR_5TH_COEF21_H   0x07
#define PROPERTY_INDEX_R2B1_REG_FLTR_5TH_COEF21_H   (0x2b1 - 0x286)

#define PROPERTY_ADDR_R2B1                          (0x0700 | (0x2b1 - 0x286))
#define PROPERTY_GROUP_R2B1                         0x07
#define PROPERTY_INDEX_R2B1                         (0x2b1 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2B2                          (0x0700 | (0x2b2 - 0x286))
#define PROPERTY_GROUP_R2B2                         0x07
#define PROPERTY_INDEX_R2B2                         (0x2b2 - 0x286)

#define PROPERTY_POS_R2B2_VDD_PA_TRIM               3
#define PROPERTY_MSK_R2B2_VDD_PA_TRIM               (0x1f << PROPERTY_POS_R2B2_VDD_PA_TRIM)

#define PROPERTY_POS_R2B2_PMU_IPOLY_TRIM            0
#define PROPERTY_MSK_R2B2_PMU_IPOLY_TRIM            (0x07 << PROPERTY_POS_R2B2_PMU_IPOLY_TRIM)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2B3_DCDC_IMAX_CAL            (0x0700 | (0x2b3 - 0x286))
#define PROPERTY_GROUP_R2B3_DCDC_IMAX_CAL           0x07
#define PROPERTY_INDEX_R2B3_DCDC_IMAX_CAL           (0x2b3 - 0x286)

#define PROPERTY_ADDR_R2B3                          (0x0700 | (0x2b3 - 0x286))
#define PROPERTY_GROUP_R2B3                         0x07
#define PROPERTY_INDEX_R2B3                         (0x2b3 - 0x286)

#define PROPERTY_POS_R2B3_DCDC_IMAX_CAL             0
#define PROPERTY_MSK_R2B3_DCDC_IMAX_CAL             (0x1f << PROPERTY_POS_R2B3_DCDC_IMAX_CAL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2B4_DCDC_VOUT_TRIM           (0x0700 | (0x2b4 - 0x286))
#define PROPERTY_GROUP_R2B4_DCDC_VOUT_TRIM          0x07
#define PROPERTY_INDEX_R2B4_DCDC_VOUT_TRIM          (0x2b4 - 0x286)

#define PROPERTY_ADDR_R2B4                          (0x0700 | (0x2b4 - 0x286))
#define PROPERTY_GROUP_R2B4                         0x07
#define PROPERTY_INDEX_R2B4                         (0x2b4 - 0x286)

#define PROPERTY_POS_R2B4_DCDC_VOUT_TRIM            0
#define PROPERTY_MSK_R2B4_DCDC_VOUT_TRIM            (0x1f << PROPERTY_POS_R2B4_DCDC_VOUT_TRIM)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2B5                          (0x0700 | (0x2b5 - 0x286))
#define PROPERTY_GROUP_R2B5                         0x07
#define PROPERTY_INDEX_R2B5                         (0x2b5 - 0x286)

#define PROPERTY_POS_R2B5_PMU_PTAT_VTRIM            5
#define PROPERTY_MSK_R2B5_PMU_PTAT_VTRIM            (0x07 << PROPERTY_POS_R2B5_PMU_PTAT_VTRIM)

#define PROPERTY_POS_R2B5_DCDC_ZERO_CAL             0
#define PROPERTY_MSK_R2B5_DCDC_ZERO_CAL             (0x1f << PROPERTY_POS_R2B5_DCDC_ZERO_CAL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2B6                          (0x0700 | (0x2b6 - 0x286))
#define PROPERTY_GROUP_R2B6                         0x07
#define PROPERTY_INDEX_R2B6                         (0x2b6 - 0x286)

#define PROPERTY_POS_R2B6_VDD_RFE_TRIM_TX           4
#define PROPERTY_MSK_R2B6_VDD_RFE_TRIM_TX           (0x0f << PROPERTY_POS_R2B6_VDD_RFE_TRIM_TX)

#define PROPERTY_POS_R2B6_VDD_RFE_TRIM              0
#define PROPERTY_MSK_R2B6_VDD_RFE_TRIM              (0x0f << PROPERTY_POS_R2B6_VDD_RFE_TRIM)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2B7                          (0x0700 | (0x2b7 - 0x286))
#define PROPERTY_GROUP_R2B7                         0x07
#define PROPERTY_INDEX_R2B7                         (0x2b7 - 0x286)

#define PROPERTY_POS_R2B7_VDD_FSYN_TRIM             4
#define PROPERTY_MSK_R2B7_VDD_FSYN_TRIM             (0x0f << PROPERTY_POS_R2B7_VDD_FSYN_TRIM)

#define PROPERTY_POS_R2B7_VDD_IF_TRIM               0
#define PROPERTY_MSK_R2B7_VDD_IF_TRIM               (0x0f << PROPERTY_POS_R2B7_VDD_IF_TRIM)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2B8                          (0x0700 | (0x2b8 - 0x286))
#define PROPERTY_GROUP_R2B8                         0x07
#define PROPERTY_INDEX_R2B8                         (0x2b8 - 0x286)

#define PROPERTY_POS_R2B8_VDD_ADC_TRIM              4
#define PROPERTY_MSK_R2B8_VDD_ADC_TRIM              (0x0f << PROPERTY_POS_R2B8_VDD_ADC_TRIM)

#define PROPERTY_POS_R2B8_VDD_VCO_TRIM              0
#define PROPERTY_MSK_R2B8_VDD_VCO_TRIM              (0x0f << PROPERTY_POS_R2B8_VDD_VCO_TRIM)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2B9                          (0x0700 | (0x2b9 - 0x286))
#define PROPERTY_GROUP_R2B9                         0x07
#define PROPERTY_INDEX_R2B9                         (0x2b9 - 0x286)

#define PROPERTY_POS_R2B9_VDD_LO_TRIM               4
#define PROPERTY_MSK_R2B9_VDD_LO_TRIM               (0x0f << PROPERTY_POS_R2B9_VDD_LO_TRIM)

#define PROPERTY_POS_R2B9_LDO_HP_TRIM               0
#define PROPERTY_MSK_R2B9_LDO_HP_TRIM               (0x0f << PROPERTY_POS_R2B9_LDO_HP_TRIM)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2BA_RCH_FREQ_FINE            (0x0700 | (0x2ba - 0x286))
#define PROPERTY_GROUP_R2BA_RCH_FREQ_FINE           0x07
#define PROPERTY_INDEX_R2BA_RCH_FREQ_FINE           (0x2ba - 0x286)

#define PROPERTY_ADDR_R2BA                          (0x0700 | (0x2ba - 0x286))
#define PROPERTY_GROUP_R2BA                         0x07
#define PROPERTY_INDEX_R2BA                         (0x2ba - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2BB                          (0x0700 | (0x2bb - 0x286))
#define PROPERTY_GROUP_R2BB                         0x07
#define PROPERTY_INDEX_R2BB                         (0x2bb - 0x286)

#define PROPERTY_POS_R2BB_RX_ADC_OUTSEL             7
#define PROPERTY_MSK_R2BB_RX_ADC_OUTSEL             (0x01 << PROPERTY_POS_R2BB_RX_ADC_OUTSEL)

#define PROPERTY_POS_R2BB_RX_ADC_DAC_RSTSEL         4
#define PROPERTY_MSK_R2BB_RX_ADC_DAC_RSTSEL         (0x01 << PROPERTY_POS_R2BB_RX_ADC_DAC_RSTSEL)

#define PROPERTY_POS_R2BB_EN_RX_ADC_TIA             3
#define PROPERTY_MSK_R2BB_EN_RX_ADC_TIA             (0x01 << PROPERTY_POS_R2BB_EN_RX_ADC_TIA)

#define PROPERTY_POS_R2BB_EN_RX_TIA                 2
#define PROPERTY_MSK_R2BB_EN_RX_TIA                 (0x01 << PROPERTY_POS_R2BB_EN_RX_TIA)

#define PROPERTY_POS_R2BB_PLL_LPF_VSEL              0
#define PROPERTY_MSK_R2BB_PLL_LPF_VSEL              (0x03 << PROPERTY_POS_R2BB_PLL_LPF_VSEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2BC                          (0x0700 | (0x2bc - 0x286))
#define PROPERTY_GROUP_R2BC                         0x07
#define PROPERTY_INDEX_R2BC                         (0x2bc - 0x286)

#define PROPERTY_POS_R2BC_PLL_PFD_DELAY             6
#define PROPERTY_MSK_R2BC_PLL_PFD_DELAY             (0x03 << PROPERTY_POS_R2BC_PLL_PFD_DELAY)

#define PROPERTY_POS_R2BC_EN_PLL_CP_FV              5
#define PROPERTY_MSK_R2BC_EN_PLL_CP_FV              (0x01 << PROPERTY_POS_R2BC_EN_PLL_CP_FV)

#define PROPERTY_POS_R2BC_EN_PLL_VCO_BUF            3
#define PROPERTY_MSK_R2BC_EN_PLL_VCO_BUF            (0x01 << PROPERTY_POS_R2BC_EN_PLL_VCO_BUF)

#define PROPERTY_POS_R2BC_PLL_LPF_C1                0
#define PROPERTY_MSK_R2BC_PLL_LPF_C1                (0x07 << PROPERTY_POS_R2BC_PLL_LPF_C1)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2BD                          (0x0700 | (0x2bd - 0x286))
#define PROPERTY_GROUP_R2BD                         0x07
#define PROPERTY_INDEX_R2BD                         (0x2bd - 0x286)

#define PROPERTY_POS_R2BD_PLL_LPF_C2                5
#define PROPERTY_MSK_R2BD_PLL_LPF_C2                (0x07 << PROPERTY_POS_R2BD_PLL_LPF_C2)

#define PROPERTY_POS_R2BD_PLL_LPF_C3                3
#define PROPERTY_MSK_R2BD_PLL_LPF_C3                (0x03 << PROPERTY_POS_R2BD_PLL_LPF_C3)

#define PROPERTY_POS_R2BD_PLL_LPF_R1                1
#define PROPERTY_MSK_R2BD_PLL_LPF_R1                (0x03 << PROPERTY_POS_R2BD_PLL_LPF_R1)

#define PROPERTY_POS_R2BD_PLL_BYP_FT                0
#define PROPERTY_MSK_R2BD_PLL_BYP_FT                (0x01 << PROPERTY_POS_R2BD_PLL_BYP_FT)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2BE                          (0x0700 | (0x2be - 0x286))
#define PROPERTY_GROUP_R2BE                         0x07
#define PROPERTY_INDEX_R2BE                         (0x2be - 0x286)

#define PROPERTY_POS_R2BE_PLL_LPF_R3                4
#define PROPERTY_MSK_R2BE_PLL_LPF_R3                (0x03 << PROPERTY_POS_R2BE_PLL_LPF_R3)

#define PROPERTY_POS_R2BE_PLL_VCO_ISEL              0
#define PROPERTY_MSK_R2BE_PLL_VCO_ISEL              (0x0f << PROPERTY_POS_R2BE_PLL_VCO_ISEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2C1                          (0x0700 | (0x2c1 - 0x286))
#define PROPERTY_GROUP_R2C1                         0x07
#define PROPERTY_INDEX_R2C1                         (0x2c1 - 0x286)

#define PROPERTY_POS_R2C1_PLL_TWO_POINT_VCTX_ENN    7
#define PROPERTY_MSK_R2C1_PLL_TWO_POINT_VCTX_ENN    (0x01 << PROPERTY_POS_R2C1_PLL_TWO_POINT_VCTX_ENN)

#define PROPERTY_POS_R2C1_XTH_HYS_EN                5
#define PROPERTY_MSK_R2C1_XTH_HYS_EN                (0x03 << PROPERTY_POS_R2C1_XTH_HYS_EN)

#define PROPERTY_POS_R2C1_PLL_FBDIV_TSTEN           3
#define PROPERTY_MSK_R2C1_PLL_FBDIV_TSTEN           (0x01 << PROPERTY_POS_R2C1_PLL_FBDIV_TSTEN)

#define PROPERTY_POS_R2C1_PLL_CALDIV                0
#define PROPERTY_MSK_R2C1_PLL_CALDIV                (0x03 << PROPERTY_POS_R2C1_PLL_CALDIV)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2C2                          (0x0700 | (0x2c2 - 0x286))
#define PROPERTY_GROUP_R2C2                         0x07
#define PROPERTY_INDEX_R2C2                         (0x2c2 - 0x286)

#define PROPERTY_POS_R2C2_PLL_CALTST_EN             7
#define PROPERTY_MSK_R2C2_PLL_CALTST_EN             (0x01 << PROPERTY_POS_R2C2_PLL_CALTST_EN)

#define PROPERTY_POS_R2C2_TST_BUF_BYP               6
#define PROPERTY_MSK_R2C2_TST_BUF_BYP               (0x01 << PROPERTY_POS_R2C2_TST_BUF_BYP)

#define PROPERTY_POS_R2C2_DAC_TST_SEL               4
#define PROPERTY_MSK_R2C2_DAC_TST_SEL               (0x01 << PROPERTY_POS_R2C2_DAC_TST_SEL)

#define PROPERTY_POS_R2C2_DAC_SEL_SW                2
#define PROPERTY_MSK_R2C2_DAC_SEL_SW                (0x03 << PROPERTY_POS_R2C2_DAC_SEL_SW)

#define PROPERTY_POS_R2C2_DAC_SG_SEL                1
#define PROPERTY_MSK_R2C2_DAC_SG_SEL                (0x01 << PROPERTY_POS_R2C2_DAC_SG_SEL)

#define PROPERTY_POS_R2C2_DAC_CLKINV                0
#define PROPERTY_MSK_R2C2_DAC_CLKINV                (0x01 << PROPERTY_POS_R2C2_DAC_CLKINV)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2C3                          (0x0700 | (0x2c3 - 0x286))
#define PROPERTY_GROUP_R2C3                         0x07
#define PROPERTY_INDEX_R2C3                         (0x2c3 - 0x286)

#define PROPERTY_POS_R2C3_EN_LO_MUX                 7
#define PROPERTY_MSK_R2C3_EN_LO_MUX                 (0x01 << PROPERTY_POS_R2C3_EN_LO_MUX)

#define PROPERTY_POS_R2C3_RX_TIA_DCOC_ENABLE        3
#define PROPERTY_MSK_R2C3_RX_TIA_DCOC_ENABLE        (0x01 << PROPERTY_POS_R2C3_RX_TIA_DCOC_ENABLE)

#define PROPERTY_POS_R2C3_RX_TIA_DCOC_BWSEL         2
#define PROPERTY_MSK_R2C3_RX_TIA_DCOC_BWSEL         (0x01 << PROPERTY_POS_R2C3_RX_TIA_DCOC_BWSEL)

#define PROPERTY_POS_R2C3_RX_TIA_DCOC_FAST          1
#define PROPERTY_MSK_R2C3_RX_TIA_DCOC_FAST          (0x01 << PROPERTY_POS_R2C3_RX_TIA_DCOC_FAST)

#define PROPERTY_POS_R2C3_RCH_XTH_TST_SEL           0
#define PROPERTY_MSK_R2C3_RCH_XTH_TST_SEL           (0x01 << PROPERTY_POS_R2C3_RCH_XTH_TST_SEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2C4                          (0x0700 | (0x2c4 - 0x286))
#define PROPERTY_GROUP_R2C4                         0x07
#define PROPERTY_INDEX_R2C4                         (0x2c4 - 0x286)

#define PROPERTY_POS_R2C4_DCDC_BUFSEL               5
#define PROPERTY_MSK_R2C4_DCDC_BUFSEL               (0x07 << PROPERTY_POS_R2C4_DCDC_BUFSEL)

#define PROPERTY_POS_R2C4_DCDC_RESSEL               2
#define PROPERTY_MSK_R2C4_DCDC_RESSEL               (0x07 << PROPERTY_POS_R2C4_DCDC_RESSEL)

#define PROPERTY_POS_R2C4_TRX_COMATCH_EN            1
#define PROPERTY_MSK_R2C4_TRX_COMATCH_EN            (0x01 << PROPERTY_POS_R2C4_TRX_COMATCH_EN)

#define PROPERTY_POS_R2C4_TXPA_900M_BUF             0
#define PROPERTY_MSK_R2C4_TXPA_900M_BUF             (0x01 << PROPERTY_POS_R2C4_TXPA_900M_BUF)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2C5                          (0x0700 | (0x2c5 - 0x286))
#define PROPERTY_GROUP_R2C5                         0x07
#define PROPERTY_INDEX_R2C5                         (0x2c5 - 0x286)

#define PROPERTY_POS_R2C5_DCDC_CAL_EN               6
#define PROPERTY_MSK_R2C5_DCDC_CAL_EN               (0x03 << PROPERTY_POS_R2C5_DCDC_CAL_EN)

#define PROPERTY_POS_R2C5_DCDC_IMAX                 3
#define PROPERTY_MSK_R2C5_DCDC_IMAX                 (0x07 << PROPERTY_POS_R2C5_DCDC_IMAX)

#define PROPERTY_POS_R2C5_DCDC_SSEN                 2
#define PROPERTY_MSK_R2C5_DCDC_SSEN                 (0x01 << PROPERTY_POS_R2C5_DCDC_SSEN)

#define PROPERTY_POS_R2C5_DCDC_MODE_SEL             1
#define PROPERTY_MSK_R2C5_DCDC_MODE_SEL             (0x01 << PROPERTY_POS_R2C5_DCDC_MODE_SEL)

#define PROPERTY_POS_R2C5_DCDC_LIMIT_EN             0
#define PROPERTY_MSK_R2C5_DCDC_LIMIT_EN             (0x01 << PROPERTY_POS_R2C5_DCDC_LIMIT_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2C6                          (0x0700 | (0x2c6 - 0x286))
#define PROPERTY_GROUP_R2C6                         0x07
#define PROPERTY_INDEX_R2C6                         (0x2c6 - 0x286)

#define PROPERTY_POS_R2C6_PA_LP_SEL                 7
#define PROPERTY_MSK_R2C6_PA_LP_SEL                 (0x01 << PROPERTY_POS_R2C6_PA_LP_SEL)

#define PROPERTY_POS_R2C6_LDO_HP_SEL                6
#define PROPERTY_MSK_R2C6_LDO_HP_SEL                (0x01 << PROPERTY_POS_R2C6_LDO_HP_SEL)

#define PROPERTY_POS_R2C6_RX_TIA_BWSEL              4
#define PROPERTY_MSK_R2C6_RX_TIA_BWSEL              (0x03 << PROPERTY_POS_R2C6_RX_TIA_BWSEL)

#define PROPERTY_POS_R2C6_VDD_PA_BYP                3
#define PROPERTY_MSK_R2C6_VDD_PA_BYP                (0x01 << PROPERTY_POS_R2C6_VDD_PA_BYP)

#define PROPERTY_POS_R2C6_XTH_TST_EN                2
#define PROPERTY_MSK_R2C6_XTH_TST_EN                (0x01 << PROPERTY_POS_R2C6_XTH_TST_EN)

#define PROPERTY_POS_R2C6_XTH_DEGLITCH_EN           0
#define PROPERTY_MSK_R2C6_XTH_DEGLITCH_EN           (0x01 << PROPERTY_POS_R2C6_XTH_DEGLITCH_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2C7                          (0x0700 | (0x2c7 - 0x286))
#define PROPERTY_GROUP_R2C7                         0x07
#define PROPERTY_INDEX_R2C7                         (0x2c7 - 0x286)

#define PROPERTY_POS_R2C7_XTH_CAP_TRIM              2
#define PROPERTY_MSK_R2C7_XTH_CAP_TRIM              (0x3f << PROPERTY_POS_R2C7_XTH_CAP_TRIM)

#define PROPERTY_POS_R2C7_XTH_RDY_SEL               1
#define PROPERTY_MSK_R2C7_XTH_RDY_SEL               (0x01 << PROPERTY_POS_R2C7_XTH_RDY_SEL)

#define PROPERTY_POS_R2C7_XTH_STARTUP_FAST          0
#define PROPERTY_MSK_R2C7_XTH_STARTUP_FAST          (0x01 << PROPERTY_POS_R2C7_XTH_STARTUP_FAST)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2C8                          (0x0700 | (0x2c8 - 0x286))
#define PROPERTY_GROUP_R2C8                         0x07
#define PROPERTY_INDEX_R2C8                         (0x2c8 - 0x286)

#define PROPERTY_POS_R2C8_XTH_AMP_SEL               7
#define PROPERTY_MSK_R2C8_XTH_AMP_SEL               (0x01 << PROPERTY_POS_R2C8_XTH_AMP_SEL)

#define PROPERTY_POS_R2C8_XTH_FB_EN                 6
#define PROPERTY_MSK_R2C8_XTH_FB_EN                 (0x01 << PROPERTY_POS_R2C8_XTH_FB_EN)

#define PROPERTY_POS_R2C8_XTH_FAST_DLY              5
#define PROPERTY_MSK_R2C8_XTH_FAST_DLY              (0x01 << PROPERTY_POS_R2C8_XTH_FAST_DLY)

#define PROPERTY_POS_R2C8_XTH_RES                   4
#define PROPERTY_MSK_R2C8_XTH_RES                   (0x01 << PROPERTY_POS_R2C8_XTH_RES)

#define PROPERTY_POS_R2C8_TST_LDO                   3
#define PROPERTY_MSK_R2C8_TST_LDO                   (0x01 << PROPERTY_POS_R2C8_TST_LDO)

#define PROPERTY_POS_R2C8_TST_RX_EN                 2
#define PROPERTY_MSK_R2C8_TST_RX_EN                 (0x01 << PROPERTY_POS_R2C8_TST_RX_EN)

#define PROPERTY_POS_R2C8_TST_LPF                   1
#define PROPERTY_MSK_R2C8_TST_LPF                   (0x01 << PROPERTY_POS_R2C8_TST_LPF)

#define PROPERTY_POS_R2C8_TST_DCDC                  0
#define PROPERTY_MSK_R2C8_TST_DCDC                  (0x01 << PROPERTY_POS_R2C8_TST_DCDC)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2C9                          (0x0700 | (0x2c9 - 0x286))
#define PROPERTY_GROUP_R2C9                         0x07
#define PROPERTY_INDEX_R2C9                         (0x2c9 - 0x286)

#define PROPERTY_POS_R2C9_TST_DAC                   7
#define PROPERTY_MSK_R2C9_TST_DAC                   (0x01 << PROPERTY_POS_R2C9_TST_DAC)

#define PROPERTY_POS_R2C9_TST_I_REG                 6
#define PROPERTY_MSK_R2C9_TST_I_REG                 (0x01 << PROPERTY_POS_R2C9_TST_I_REG)

#define PROPERTY_POS_R2C9_TST_V_REG                 2
#define PROPERTY_MSK_R2C9_TST_V_REG                 (0x0f << PROPERTY_POS_R2C9_TST_V_REG)

#define PROPERTY_POS_R2C9_TST_EN_DFT_I              1
#define PROPERTY_MSK_R2C9_TST_EN_DFT_I              (0x01 << PROPERTY_POS_R2C9_TST_EN_DFT_I)

#define PROPERTY_POS_R2C9_TST_EN_DFT_V              0
#define PROPERTY_MSK_R2C9_TST_EN_DFT_V              (0x01 << PROPERTY_POS_R2C9_TST_EN_DFT_V)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2CA                          (0x0700 | (0x2ca - 0x286))
#define PROPERTY_GROUP_R2CA                         0x07
#define PROPERTY_INDEX_R2CA                         (0x2ca - 0x286)

#define PROPERTY_POS_R2CA_TST_EN_BUF                7
#define PROPERTY_MSK_R2CA_TST_EN_BUF                (0x01 << PROPERTY_POS_R2CA_TST_EN_BUF)

#define PROPERTY_POS_R2CA_TST_EN_DFT_CLK            6
#define PROPERTY_MSK_R2CA_TST_EN_DFT_CLK            (0x01 << PROPERTY_POS_R2CA_TST_EN_DFT_CLK)

#define PROPERTY_POS_R2CA_TST_CLK_REG               3
#define PROPERTY_MSK_R2CA_TST_CLK_REG               (0x07 << PROPERTY_POS_R2CA_TST_CLK_REG)

#define PROPERTY_POS_R2CA_EN_LDO_PA                 2
#define PROPERTY_MSK_R2CA_EN_LDO_PA                 (0x01 << PROPERTY_POS_R2CA_EN_LDO_PA)

#define PROPERTY_POS_R2CA_EN_RX_LNA                 1
#define PROPERTY_MSK_R2CA_EN_RX_LNA                 (0x01 << PROPERTY_POS_R2CA_EN_RX_LNA)

#define PROPERTY_POS_R2CA_EN_RX_MIX                 0
#define PROPERTY_MSK_R2CA_EN_RX_MIX                 (0x01 << PROPERTY_POS_R2CA_EN_RX_MIX)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2CB                          (0x0700 | (0x2cb - 0x286))
#define PROPERTY_GROUP_R2CB                         0x07
#define PROPERTY_INDEX_R2CB                         (0x2cb - 0x286)

#define PROPERTY_POS_R2CB_EN_RX_ADC                 7
#define PROPERTY_MSK_R2CB_EN_RX_ADC                 (0x01 << PROPERTY_POS_R2CB_EN_RX_ADC)

#define PROPERTY_POS_R2CB_EN_PLL_PFD                6
#define PROPERTY_MSK_R2CB_EN_PLL_PFD                (0x01 << PROPERTY_POS_R2CB_EN_PLL_PFD)

#define PROPERTY_POS_R2CB_EN_PLL_CP                 5
#define PROPERTY_MSK_R2CB_EN_PLL_CP                 (0x01 << PROPERTY_POS_R2CB_EN_PLL_CP)

#define PROPERTY_POS_R2CB_EN_PLL_CPSHIFT            4
#define PROPERTY_MSK_R2CB_EN_PLL_CPSHIFT            (0x01 << PROPERTY_POS_R2CB_EN_PLL_CPSHIFT)

#define PROPERTY_POS_R2CB_EN_PLL_LPF                3
#define PROPERTY_MSK_R2CB_EN_PLL_LPF                (0x01 << PROPERTY_POS_R2CB_EN_PLL_LPF)

#define PROPERTY_POS_R2CB_EN_PLL_LPF_VCDN           2
#define PROPERTY_MSK_R2CB_EN_PLL_LPF_VCDN           (0x01 << PROPERTY_POS_R2CB_EN_PLL_LPF_VCDN)

#define PROPERTY_POS_R2CB_EN_PLL_VCO                1
#define PROPERTY_MSK_R2CB_EN_PLL_VCO                (0x01 << PROPERTY_POS_R2CB_EN_PLL_VCO)

#define PROPERTY_POS_R2CB_EN_TX_DAC                 0
#define PROPERTY_MSK_R2CB_EN_TX_DAC                 (0x01 << PROPERTY_POS_R2CB_EN_TX_DAC)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2CC                          (0x0700 | (0x2cc - 0x286))
#define PROPERTY_GROUP_R2CC                         0x07
#define PROPERTY_INDEX_R2CC                         (0x2cc - 0x286)

#define PROPERTY_POS_R2CC_EN_BOD_TST                5
#define PROPERTY_MSK_R2CC_EN_BOD_TST                (0x01 << PROPERTY_POS_R2CC_EN_BOD_TST)

#define PROPERTY_POS_R2CC_EN_LVR_TST                4
#define PROPERTY_MSK_R2CC_EN_LVR_TST                (0x01 << PROPERTY_POS_R2CC_EN_LVR_TST)

#define PROPERTY_POS_R2CC_EN_RCL_TST                3
#define PROPERTY_MSK_R2CC_EN_RCL_TST                (0x01 << PROPERTY_POS_R2CC_EN_RCL_TST)

#define PROPERTY_POS_R2CC_EN_RCH_TST                2
#define PROPERTY_MSK_R2CC_EN_RCH_TST                (0x01 << PROPERTY_POS_R2CC_EN_RCH_TST)

#define PROPERTY_POS_R2CC_RCH_RDY_TRIM              0
#define PROPERTY_MSK_R2CC_RCH_RDY_TRIM              (0x03 << PROPERTY_POS_R2CC_RCH_RDY_TRIM)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2CD                          (0x0700 | (0x2cd - 0x286))
#define PROPERTY_GROUP_R2CD                         0x07
#define PROPERTY_INDEX_R2CD                         (0x2cd - 0x286)

#define PROPERTY_POS_R2CD_EN_XTL_TST                7
#define PROPERTY_MSK_R2CD_EN_XTL_TST                (0x01 << PROPERTY_POS_R2CD_EN_XTL_TST)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2CE                          (0x0700 | (0x2ce - 0x286))
#define PROPERTY_GROUP_R2CE                         0x07
#define PROPERTY_INDEX_R2CE                         (0x2ce - 0x286)

#define PROPERTY_POS_R2CE_DCDC_CMP_OUT              6
#define PROPERTY_MSK_R2CE_DCDC_CMP_OUT              (0x01 << PROPERTY_POS_R2CE_DCDC_CMP_OUT)

#define PROPERTY_POS_R2CE_RCH_RDY                   5
#define PROPERTY_MSK_R2CE_RCH_RDY                   (0x01 << PROPERTY_POS_R2CE_RCH_RDY)

#define PROPERTY_POS_R2CE_XTH_CLKRDY_OUT            4
#define PROPERTY_MSK_R2CE_XTH_CLKRDY_OUT            (0x01 << PROPERTY_POS_R2CE_XTH_CLKRDY_OUT)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2CF                          (0x0700 | (0x2cf - 0x286))
#define PROPERTY_GROUP_R2CF                         0x07
#define PROPERTY_INDEX_R2CF                         (0x2cf - 0x286)

#define PROPERTY_POS_R2CF_RCCAL_DONE                6
#define PROPERTY_MSK_R2CF_RCCAL_DONE                (0x01 << PROPERTY_POS_R2CF_RCCAL_DONE)

#define PROPERTY_POS_R2CF_RCCAL_CAPTUNE             0
#define PROPERTY_MSK_R2CF_RCCAL_CAPTUNE             (0x3f << PROPERTY_POS_R2CF_RCCAL_CAPTUNE)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2D0                          (0x0700 | (0x2d0 - 0x286))
#define PROPERTY_GROUP_R2D0                         0x07
#define PROPERTY_INDEX_R2D0                         (0x2d0 - 0x286)

#define PROPERTY_POS_R2D0_RX_TIA_CAPTUNE            1
#define PROPERTY_MSK_R2D0_RX_TIA_CAPTUNE            (0x7f << PROPERTY_POS_R2D0_RX_TIA_CAPTUNE)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2D1                          (0x0700 | (0x2d1 - 0x286))
#define PROPERTY_GROUP_R2D1                         0x07
#define PROPERTY_INDEX_R2D1                         (0x2d1 - 0x286)

#define PROPERTY_POS_R2D1_RX_MIX_VCM                6
#define PROPERTY_MSK_R2D1_RX_MIX_VCM                (0x03 << PROPERTY_POS_R2D1_RX_MIX_VCM)

#define PROPERTY_POS_R2D1_RX_TIA_IBIAS              3
#define PROPERTY_MSK_R2D1_RX_TIA_IBIAS              (0x07 << PROPERTY_POS_R2D1_RX_TIA_IBIAS)

#define PROPERTY_POS_R2D1_RX_ADC_QUAN_VTRIM         0
#define PROPERTY_MSK_R2D1_RX_ADC_QUAN_VTRIM         (0x07 << PROPERTY_POS_R2D1_RX_ADC_QUAN_VTRIM)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2D2                          (0x0700 | (0x2d2 - 0x286))
#define PROPERTY_GROUP_R2D2                         0x07
#define PROPERTY_INDEX_R2D2                         (0x2d2 - 0x286)

#define PROPERTY_POS_R2D2_RX_ADC_IBSEL              6
#define PROPERTY_MSK_R2D2_RX_ADC_IBSEL              (0x03 << PROPERTY_POS_R2D2_RX_ADC_IBSEL)

#define PROPERTY_POS_R2D2_PLL_VCO_FCSEL             3
#define PROPERTY_MSK_R2D2_PLL_VCO_FCSEL             (0x07 << PROPERTY_POS_R2D2_PLL_VCO_FCSEL)

#define PROPERTY_POS_R2D2_PLL_CP_NSHIFT             0
#define PROPERTY_MSK_R2D2_PLL_CP_NSHIFT             (0x07 << PROPERTY_POS_R2D2_PLL_CP_NSHIFT)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2D3                          (0x0700 | (0x2d3 - 0x286))
#define PROPERTY_GROUP_R2D3                         0x07
#define PROPERTY_INDEX_R2D3                         (0x2d3 - 0x286)

#define PROPERTY_POS_R2D3_PLL_CP_ISEL               3
#define PROPERTY_MSK_R2D3_PLL_CP_ISEL               (0x0f << PROPERTY_POS_R2D3_PLL_CP_ISEL)

#define PROPERTY_POS_R2D3_PLL_CP_PSHIFT             0
#define PROPERTY_MSK_R2D3_PLL_CP_PSHIFT             (0x07 << PROPERTY_POS_R2D3_PLL_CP_PSHIFT)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2D4                          (0x0700 | (0x2d4 - 0x286))
#define PROPERTY_GROUP_R2D4                         0x07
#define PROPERTY_INDEX_R2D4                         (0x2d4 - 0x286)

#define PROPERTY_POS_R2D4_PMU_PTAT_TEMPTRIM         6
#define PROPERTY_MSK_R2D4_PMU_PTAT_TEMPTRIM         (0x03 << PROPERTY_POS_R2D4_PMU_PTAT_TEMPTRIM)

#define PROPERTY_POS_R2D4_PLL_VCO_IBGSEL            4
#define PROPERTY_MSK_R2D4_PLL_VCO_IBGSEL            (0x03 << PROPERTY_POS_R2D4_PLL_VCO_IBGSEL)

#define PROPERTY_POS_R2D4_PLL_VCO_IPTATSEL          2
#define PROPERTY_MSK_R2D4_PLL_VCO_IPTATSEL          (0x03 << PROPERTY_POS_R2D4_PLL_VCO_IPTATSEL)

#define PROPERTY_POS_R2D4_PLL_VCO_VD_SW             0
#define PROPERTY_MSK_R2D4_PLL_VCO_VD_SW             (0x03 << PROPERTY_POS_R2D4_PLL_VCO_VD_SW)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2D5                          (0x0700 | (0x2d5 - 0x286))
#define PROPERTY_GROUP_R2D5                         0x07
#define PROPERTY_INDEX_R2D5                         (0x2d5 - 0x286)

#define PROPERTY_POS_R2D5_XTH_ICORE_SEL             6
#define PROPERTY_MSK_R2D5_XTH_ICORE_SEL             (0x03 << PROPERTY_POS_R2D5_XTH_ICORE_SEL)

#define PROPERTY_POS_R2D5_PLL_VCO_BUF_BIASN         3
#define PROPERTY_MSK_R2D5_PLL_VCO_BUF_BIASN         (0x07 << PROPERTY_POS_R2D5_PLL_VCO_BUF_BIASN)

#define PROPERTY_POS_R2D5_PLL_VCO_BUF_BIASP         0
#define PROPERTY_MSK_R2D5_PLL_VCO_BUF_BIASP         (0x07 << PROPERTY_POS_R2D5_PLL_VCO_BUF_BIASP)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2D6                          (0x0700 | (0x2d6 - 0x286))
#define PROPERTY_GROUP_R2D6                         0x07
#define PROPERTY_INDEX_R2D6                         (0x2d6 - 0x286)

#define PROPERTY_POS_R2D6_PA_DCC_SEL                6
#define PROPERTY_MSK_R2D6_PA_DCC_SEL                (0x03 << PROPERTY_POS_R2D6_PA_DCC_SEL)

#define PROPERTY_POS_R2D6_DAC_VREF_SEL              0
#define PROPERTY_MSK_R2D6_DAC_VREF_SEL              (0x07 << PROPERTY_POS_R2D6_DAC_VREF_SEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2D7                          (0x0700 | (0x2d7 - 0x286))
#define PROPERTY_GROUP_R2D7                         0x07
#define PROPERTY_INDEX_R2D7                         (0x2d7 - 0x286)

#define PROPERTY_POS_R2D7_PA_BIAS_TRIM              4
#define PROPERTY_MSK_R2D7_PA_BIAS_TRIM              (0x0f << PROPERTY_POS_R2D7_PA_BIAS_TRIM)

#define PROPERTY_POS_R2D7_PA_RAMP_RC_TRIM           1
#define PROPERTY_MSK_R2D7_PA_RAMP_RC_TRIM           (0x07 << PROPERTY_POS_R2D7_PA_RAMP_RC_TRIM)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2D8                          (0x0700 | (0x2d8 - 0x286))
#define PROPERTY_GROUP_R2D8                         0x07
#define PROPERTY_INDEX_R2D8                         (0x2d8 - 0x286)

#define PROPERTY_POS_R2D8_DAC_ISEL                  4
#define PROPERTY_MSK_R2D8_DAC_ISEL                  (0x07 << PROPERTY_POS_R2D8_DAC_ISEL)

#define PROPERTY_POS_R2D8_RCH_FREQ_COARSE           0
#define PROPERTY_MSK_R2D8_RCH_FREQ_COARSE           (0x03 << PROPERTY_POS_R2D8_RCH_FREQ_COARSE)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2D9                          (0x0700 | (0x2d9 - 0x286))
#define PROPERTY_GROUP_R2D9                         0x07
#define PROPERTY_INDEX_R2D9                         (0x2d9 - 0x286)

#define PROPERTY_POS_R2D9_RX_LNA2_ICORE             4
#define PROPERTY_MSK_R2D9_RX_LNA2_ICORE             (0x0f << PROPERTY_POS_R2D9_RX_LNA2_ICORE)

#define PROPERTY_POS_R2D9_EN_RX_RCCAL               3
#define PROPERTY_MSK_R2D9_EN_RX_RCCAL               (0x01 << PROPERTY_POS_R2D9_EN_RX_RCCAL)

#define PROPERTY_POS_R2D9_RX_RCCAL_INV              2
#define PROPERTY_MSK_R2D9_RX_RCCAL_INV              (0x01 << PROPERTY_POS_R2D9_RX_RCCAL_INV)

#define PROPERTY_POS_R2D9_RX_RCCAL_RST              1
#define PROPERTY_MSK_R2D9_RX_RCCAL_RST              (0x01 << PROPERTY_POS_R2D9_RX_RCCAL_RST)

#define PROPERTY_POS_R2D9_RX_TIA_OUTCURRENT_SEL     0
#define PROPERTY_MSK_R2D9_RX_TIA_OUTCURRENT_SEL     (0x01 << PROPERTY_POS_R2D9_RX_TIA_OUTCURRENT_SEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2DA_GPIO_CHEN                (0x0700 | (0x2da - 0x286))
#define PROPERTY_GROUP_R2DA_GPIO_CHEN               0x07
#define PROPERTY_INDEX_R2DA_GPIO_CHEN               (0x2da - 0x286)

#define PROPERTY_ADDR_R2DA                          (0x0700 | (0x2da - 0x286))
#define PROPERTY_GROUP_R2DA                         0x07
#define PROPERTY_INDEX_R2DA                         (0x2da - 0x286)

#define PROPERTY_POS_R2DA_GPIO_CHEN                 0
#define PROPERTY_MSK_R2DA_GPIO_CHEN                 (0x07 << PROPERTY_POS_R2DA_GPIO_CHEN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2DB_RESERVED_L               (0x0700 | (0x2db - 0x286))
#define PROPERTY_GROUP_R2DB_RESERVED_L              0x07
#define PROPERTY_INDEX_R2DB_RESERVED_L              (0x2db - 0x286)

#define PROPERTY_ADDR_R2DB                          (0x0700 | (0x2db - 0x286))
#define PROPERTY_GROUP_R2DB                         0x07
#define PROPERTY_INDEX_R2DB                         (0x2db - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R2DC_RESERVED_H               (0x0700 | (0x2dc - 0x286))
#define PROPERTY_GROUP_R2DC_RESERVED_H              0x07
#define PROPERTY_INDEX_R2DC_RESERVED_H              (0x2dc - 0x286)

#define PROPERTY_ADDR_R2DC                          (0x0700 | (0x2dc - 0x286))
#define PROPERTY_GROUP_R2DC                         0x07
#define PROPERTY_INDEX_R2DC                         (0x2dc - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R306_XCORR_SUM_TH             (0x0700 | (0x306 - 0x286))
#define PROPERTY_GROUP_R306_XCORR_SUM_TH            0x07
#define PROPERTY_INDEX_R306_XCORR_SUM_TH            (0x306 - 0x286)

#define PROPERTY_ADDR_R306                          (0x0700 | (0x306 - 0x286))
#define PROPERTY_GROUP_R306                         0x07
#define PROPERTY_INDEX_R306                         (0x306 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R307                          (0x0700 | (0x307 - 0x286))
#define PROPERTY_GROUP_R307                         0x07
#define PROPERTY_INDEX_R307                         (0x307 - 0x286)

#define PROPERTY_POS_R307_XCORR_SUM_FAKE_TH         4
#define PROPERTY_MSK_R307_XCORR_SUM_FAKE_TH         (0x0f << PROPERTY_POS_R307_XCORR_SUM_FAKE_TH)

#define PROPERTY_POS_R307_XCORR_SUM_DEL_TH          0
#define PROPERTY_MSK_R307_XCORR_SUM_DEL_TH          (0x0f << PROPERTY_POS_R307_XCORR_SUM_DEL_TH)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R308                          (0x0700 | (0x308 - 0x286))
#define PROPERTY_GROUP_R308                         0x07
#define PROPERTY_INDEX_R308                         (0x308 - 0x286)

#define PROPERTY_POS_R308_REG_SOFT_DEC              7
#define PROPERTY_MSK_R308_REG_SOFT_DEC              (0x01 << PROPERTY_POS_R308_REG_SOFT_DEC)

#define PROPERTY_POS_R308_IQ_SWITCH_IN_REG          6
#define PROPERTY_MSK_R308_IQ_SWITCH_IN_REG          (0x01 << PROPERTY_POS_R308_IQ_SWITCH_IN_REG)

#define PROPERTY_POS_R308_REG_MANU_FREQ_DIR         5
#define PROPERTY_MSK_R308_REG_MANU_FREQ_DIR         (0x01 << PROPERTY_POS_R308_REG_MANU_FREQ_DIR)

#define PROPERTY_POS_R308_REG_MANU_FREQ_DIR_EN      4
#define PROPERTY_MSK_R308_REG_MANU_FREQ_DIR_EN      (0x01 << PROPERTY_POS_R308_REG_MANU_FREQ_DIR_EN)

#define PROPERTY_POS_R308_IQ_COMP_CLK_MASK          3
#define PROPERTY_MSK_R308_IQ_COMP_CLK_MASK          (0x01 << PROPERTY_POS_R308_IQ_COMP_CLK_MASK)

#define PROPERTY_POS_R308_REG_MANU_CFO_DIR          2
#define PROPERTY_MSK_R308_REG_MANU_CFO_DIR          (0x01 << PROPERTY_POS_R308_REG_MANU_CFO_DIR)

#define PROPERTY_POS_R308_SIGN_SWITCH_IN_REG        1
#define PROPERTY_MSK_R308_SIGN_SWITCH_IN_REG        (0x01 << PROPERTY_POS_R308_SIGN_SWITCH_IN_REG)

#define PROPERTY_POS_R308_SYNC_TIMEOUT_RST_VLD      0
#define PROPERTY_MSK_R308_SYNC_TIMEOUT_RST_VLD      (0x01 << PROPERTY_POS_R308_SYNC_TIMEOUT_RST_VLD)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R309_REG_SW_MATCH_IN_TH       (0x0700 | (0x309 - 0x286))
#define PROPERTY_GROUP_R309_REG_SW_MATCH_IN_TH      0x07
#define PROPERTY_INDEX_R309_REG_SW_MATCH_IN_TH      (0x309 - 0x286)

#define PROPERTY_ADDR_R309                          (0x0700 | (0x309 - 0x286))
#define PROPERTY_GROUP_R309                         0x07
#define PROPERTY_INDEX_R309                         (0x309 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R30A_REG_SW_MATCH_OUT_TH      (0x0700 | (0x30a - 0x286))
#define PROPERTY_GROUP_R30A_REG_SW_MATCH_OUT_TH     0x07
#define PROPERTY_INDEX_R30A_REG_SW_MATCH_OUT_TH     (0x30a - 0x286)

#define PROPERTY_ADDR_R30A                          (0x0700 | (0x30a - 0x286))
#define PROPERTY_GROUP_R30A                         0x07
#define PROPERTY_INDEX_R30A                         (0x30a - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R30B                          (0x0700 | (0x30b - 0x286))
#define PROPERTY_GROUP_R30B                         0x07
#define PROPERTY_INDEX_R30B                         (0x30b - 0x286)

#define PROPERTY_POS_R30B_REG_BL_FREQ_TR_BETA       4
#define PROPERTY_MSK_R30B_REG_BL_FREQ_TR_BETA       (0x0f << PROPERTY_POS_R30B_REG_BL_FREQ_TR_BETA)

#define PROPERTY_POS_R30B_REG_BL_FREQ_TR_ALPH       0
#define PROPERTY_MSK_R30B_REG_BL_FREQ_TR_ALPH       (0x0f << PROPERTY_POS_R30B_REG_BL_FREQ_TR_ALPH)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R30C                          (0x0700 | (0x30c - 0x286))
#define PROPERTY_GROUP_R30C                         0x07
#define PROPERTY_INDEX_R30C                         (0x30c - 0x286)

#define PROPERTY_POS_R30C_REG_BL_FSK_SYNC_KI        4
#define PROPERTY_MSK_R30C_REG_BL_FSK_SYNC_KI        (0x0f << PROPERTY_POS_R30C_REG_BL_FSK_SYNC_KI)

#define PROPERTY_POS_R30C_REG_BL_FSK_SYNC_KP        0
#define PROPERTY_MSK_R30C_REG_BL_FSK_SYNC_KP        (0x0f << PROPERTY_POS_R30C_REG_BL_FSK_SYNC_KP)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R30D                          (0x0700 | (0x30d - 0x286))
#define PROPERTY_GROUP_R30D                         0x07
#define PROPERTY_INDEX_R30D                         (0x30d - 0x286)

#define PROPERTY_POS_R30D_REG_FD_FREQ_TR_ALPH2      4
#define PROPERTY_MSK_R30D_REG_FD_FREQ_TR_ALPH2      (0x0f << PROPERTY_POS_R30D_REG_FD_FREQ_TR_ALPH2)

#define PROPERTY_POS_R30D_REG_FD_FREQ_TR_ALPH1      0
#define PROPERTY_MSK_R30D_REG_FD_FREQ_TR_ALPH1      (0x0f << PROPERTY_POS_R30D_REG_FD_FREQ_TR_ALPH1)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R30E                          (0x0700 | (0x30e - 0x286))
#define PROPERTY_GROUP_R30E                         0x07
#define PROPERTY_INDEX_R30E                         (0x30e - 0x286)

#define PROPERTY_POS_R30E_REG_FD_EQU_EN             7
#define PROPERTY_MSK_R30E_REG_FD_EQU_EN             (0x01 << PROPERTY_POS_R30E_REG_FD_EQU_EN)

#define PROPERTY_POS_R30E_REG_BL_FSK_SYNC_EN        6
#define PROPERTY_MSK_R30E_REG_BL_FSK_SYNC_EN        (0x01 << PROPERTY_POS_R30E_REG_BL_FSK_SYNC_EN)

#define PROPERTY_POS_R30E_REG_BL_FREQ_TR_EN         5
#define PROPERTY_MSK_R30E_REG_BL_FREQ_TR_EN         (0x01 << PROPERTY_POS_R30E_REG_BL_FREQ_TR_EN)

#define PROPERTY_POS_R30E_REG_FD_SYNC_VLD           4
#define PROPERTY_MSK_R30E_REG_FD_SYNC_VLD           (0x01 << PROPERTY_POS_R30E_REG_FD_SYNC_VLD)

#define PROPERTY_POS_R30E_FALSE_SYNC_TIMEOUT_VLD    3
#define PROPERTY_MSK_R30E_FALSE_SYNC_TIMEOUT_VLD    (0x01 << PROPERTY_POS_R30E_FALSE_SYNC_TIMEOUT_VLD)

#define PROPERTY_POS_R30E_DIRECT_BYPASS_MODE        2
#define PROPERTY_MSK_R30E_DIRECT_BYPASS_MODE        (0x01 << PROPERTY_POS_R30E_DIRECT_BYPASS_MODE)

#define PROPERTY_POS_R30E_REG_SLOPE_FREQ_VLD        1
#define PROPERTY_MSK_R30E_REG_SLOPE_FREQ_VLD        (0x01 << PROPERTY_POS_R30E_REG_SLOPE_FREQ_VLD)

#define PROPERTY_POS_R30E_REG_FD_FREQ_TR_EN         0
#define PROPERTY_MSK_R30E_REG_FD_FREQ_TR_EN         (0x01 << PROPERTY_POS_R30E_REG_FD_FREQ_TR_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R30F_REG_FD_EQU_FFE_COEF1     (0x0700 | (0x30f - 0x286))
#define PROPERTY_GROUP_R30F_REG_FD_EQU_FFE_COEF1    0x07
#define PROPERTY_INDEX_R30F_REG_FD_EQU_FFE_COEF1    (0x30f - 0x286)

#define PROPERTY_ADDR_R30F                          (0x0700 | (0x30f - 0x286))
#define PROPERTY_GROUP_R30F                         0x07
#define PROPERTY_INDEX_R30F                         (0x30f - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R310_REG_FD_EQU_FFE_COEF2     (0x0700 | (0x310 - 0x286))
#define PROPERTY_GROUP_R310_REG_FD_EQU_FFE_COEF2    0x07
#define PROPERTY_INDEX_R310_REG_FD_EQU_FFE_COEF2    (0x310 - 0x286)

#define PROPERTY_ADDR_R310                          (0x0700 | (0x310 - 0x286))
#define PROPERTY_GROUP_R310                         0x07
#define PROPERTY_INDEX_R310                         (0x310 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R311_REG_FD_EQU_FFE_COEF3     (0x0700 | (0x311 - 0x286))
#define PROPERTY_GROUP_R311_REG_FD_EQU_FFE_COEF3    0x07
#define PROPERTY_INDEX_R311_REG_FD_EQU_FFE_COEF3    (0x311 - 0x286)

#define PROPERTY_ADDR_R311                          (0x0700 | (0x311 - 0x286))
#define PROPERTY_GROUP_R311                         0x07
#define PROPERTY_INDEX_R311                         (0x311 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R312_REG_FD_EQU_DFE_COEF1     (0x0700 | (0x312 - 0x286))
#define PROPERTY_GROUP_R312_REG_FD_EQU_DFE_COEF1    0x07
#define PROPERTY_INDEX_R312_REG_FD_EQU_DFE_COEF1    (0x312 - 0x286)

#define PROPERTY_ADDR_R312                          (0x0700 | (0x312 - 0x286))
#define PROPERTY_GROUP_R312                         0x07
#define PROPERTY_INDEX_R312                         (0x312 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R313_REG_FD_EQU_DFE_COEF2     (0x0700 | (0x313 - 0x286))
#define PROPERTY_GROUP_R313_REG_FD_EQU_DFE_COEF2    0x07
#define PROPERTY_INDEX_R313_REG_FD_EQU_DFE_COEF2    (0x313 - 0x286)

#define PROPERTY_ADDR_R313                          (0x0700 | (0x313 - 0x286))
#define PROPERTY_GROUP_R313                         0x07
#define PROPERTY_INDEX_R313                         (0x313 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R314_REG_SNR_POW_TH           (0x0700 | (0x314 - 0x286))
#define PROPERTY_GROUP_R314_REG_SNR_POW_TH          0x07
#define PROPERTY_INDEX_R314_REG_SNR_POW_TH          (0x314 - 0x286)

#define PROPERTY_ADDR_R314                          (0x0700 | (0x314 - 0x286))
#define PROPERTY_GROUP_R314                         0x07
#define PROPERTY_INDEX_R314                         (0x314 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R315                          (0x0700 | (0x315 - 0x286))
#define PROPERTY_GROUP_R315                         0x07
#define PROPERTY_INDEX_R315                         (0x315 - 0x286)

#define PROPERTY_POS_R315_REG_SNR_POW_PARA1         4
#define PROPERTY_MSK_R315_REG_SNR_POW_PARA1         (0x0f << PROPERTY_POS_R315_REG_SNR_POW_PARA1)

#define PROPERTY_POS_R315_REG_SNR_POW_PARA2         0
#define PROPERTY_MSK_R315_REG_SNR_POW_PARA2         (0x0f << PROPERTY_POS_R315_REG_SNR_POW_PARA2)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R316                          (0x0700 | (0x316 - 0x286))
#define PROPERTY_GROUP_R316                         0x07
#define PROPERTY_INDEX_R316                         (0x316 - 0x286)

#define PROPERTY_POS_R316_REG_SPE_XCORR_SEL         7
#define PROPERTY_MSK_R316_REG_SPE_XCORR_SEL         (0x01 << PROPERTY_POS_R316_REG_SPE_XCORR_SEL)

#define PROPERTY_POS_R316_REG_SPE_PRE_SEL           4
#define PROPERTY_MSK_R316_REG_SPE_PRE_SEL           (0x07 << PROPERTY_POS_R316_REG_SPE_PRE_SEL)

#define PROPERTY_POS_R316_REG_DC_CAL_TRIG           3
#define PROPERTY_MSK_R316_REG_DC_CAL_TRIG           (0x01 << PROPERTY_POS_R316_REG_DC_CAL_TRIG)

#define PROPERTY_POS_R316_REG_AGC_IN_MODE           2
#define PROPERTY_MSK_R316_REG_AGC_IN_MODE           (0x01 << PROPERTY_POS_R316_REG_AGC_IN_MODE)

#define PROPERTY_POS_R316_REG_DAGC_MANU_EN          1
#define PROPERTY_MSK_R316_REG_DAGC_MANU_EN          (0x01 << PROPERTY_POS_R316_REG_DAGC_MANU_EN)

#define PROPERTY_POS_R316_REG_DAGC_EN               0
#define PROPERTY_MSK_R316_REG_DAGC_EN               (0x01 << PROPERTY_POS_R316_REG_DAGC_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R317_REG_DAGC_TARGET_POW      (0x0700 | (0x317 - 0x286))
#define PROPERTY_GROUP_R317_REG_DAGC_TARGET_POW     0x07
#define PROPERTY_INDEX_R317_REG_DAGC_TARGET_POW     (0x317 - 0x286)

#define PROPERTY_ADDR_R317                          (0x0700 | (0x317 - 0x286))
#define PROPERTY_GROUP_R317                         0x07
#define PROPERTY_INDEX_R317                         (0x317 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R318                          (0x0700 | (0x318 - 0x286))
#define PROPERTY_GROUP_R318                         0x07
#define PROPERTY_INDEX_R318                         (0x318 - 0x286)

#define PROPERTY_POS_R318_REG_DAGC_ALPH2            4
#define PROPERTY_MSK_R318_REG_DAGC_ALPH2            (0x0f << PROPERTY_POS_R318_REG_DAGC_ALPH2)

#define PROPERTY_POS_R318_REG_DAGC_ALPH1            0
#define PROPERTY_MSK_R318_REG_DAGC_ALPH1            (0x0f << PROPERTY_POS_R318_REG_DAGC_ALPH1)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R319_REG_DAGC_PARA_SW_TH      (0x0700 | (0x319 - 0x286))
#define PROPERTY_GROUP_R319_REG_DAGC_PARA_SW_TH     0x07
#define PROPERTY_INDEX_R319_REG_DAGC_PARA_SW_TH     (0x319 - 0x286)

#define PROPERTY_ADDR_R319                          (0x0700 | (0x319 - 0x286))
#define PROPERTY_GROUP_R319                         0x07
#define PROPERTY_INDEX_R319                         (0x319 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R31A_REG_DAGC_GAIN_MANU       (0x0700 | (0x31a - 0x286))
#define PROPERTY_GROUP_R31A_REG_DAGC_GAIN_MANU      0x07
#define PROPERTY_INDEX_R31A_REG_DAGC_GAIN_MANU      (0x31a - 0x286)

#define PROPERTY_ADDR_R31A                          (0x0700 | (0x31a - 0x286))
#define PROPERTY_GROUP_R31A                         0x07
#define PROPERTY_INDEX_R31A                         (0x31a - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R31B_REG_FD_END_TH_L          (0x0700 | (0x31b - 0x286))
#define PROPERTY_GROUP_R31B_REG_FD_END_TH_L         0x07
#define PROPERTY_INDEX_R31B_REG_FD_END_TH_L         (0x31b - 0x286)

#define PROPERTY_ADDR_R31B                          (0x0700 | (0x31b - 0x286))
#define PROPERTY_GROUP_R31B                         0x07
#define PROPERTY_INDEX_R31B                         (0x31b - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R31C                          (0x0700 | (0x31c - 0x286))
#define PROPERTY_GROUP_R31C                         0x07
#define PROPERTY_INDEX_R31C                         (0x31c - 0x286)

#define PROPERTY_POS_R31C_REG_FD_END_TH_H           7
#define PROPERTY_MSK_R31C_REG_FD_END_TH_H           (0x01 << PROPERTY_POS_R31C_REG_FD_END_TH_H)

#define PROPERTY_POS_R31C_REG_MAX_VLD               6
#define PROPERTY_MSK_R31C_REG_MAX_VLD               (0x01 << PROPERTY_POS_R31C_REG_MAX_VLD)

#define PROPERTY_POS_R31C_REG_FLTR_COEF_MUX         5
#define PROPERTY_MSK_R31C_REG_FLTR_COEF_MUX         (0x01 << PROPERTY_POS_R31C_REG_FLTR_COEF_MUX)

#define PROPERTY_POS_R31C_REG_PULSE_SYNC_MUX        4
#define PROPERTY_MSK_R31C_REG_PULSE_SYNC_MUX        (0x01 << PROPERTY_POS_R31C_REG_PULSE_SYNC_MUX)

#define PROPERTY_POS_R31C_PRE_CMP_LEN               1
#define PROPERTY_MSK_R31C_PRE_CMP_LEN               (0x07 << PROPERTY_POS_R31C_PRE_CMP_LEN)

#define PROPERTY_POS_R31C_SYNC_SRC_SEL              0
#define PROPERTY_MSK_R31C_SYNC_SRC_SEL              (0x01 << PROPERTY_POS_R31C_SYNC_SRC_SEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R31D_REG_FD_SYNC_TH           (0x0700 | (0x31d - 0x286))
#define PROPERTY_GROUP_R31D_REG_FD_SYNC_TH          0x07
#define PROPERTY_INDEX_R31D_REG_FD_SYNC_TH          (0x31d - 0x286)

#define PROPERTY_ADDR_R31D                          (0x0700 | (0x31d - 0x286))
#define PROPERTY_GROUP_R31D                         0x07
#define PROPERTY_INDEX_R31D                         (0x31d - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R31E                          (0x0700 | (0x31e - 0x286))
#define PROPERTY_GROUP_R31E                         0x07
#define PROPERTY_INDEX_R31E                         (0x31e - 0x286)

#define PROPERTY_POS_R31E_REG_FD_AFC_DATA_KP        4
#define PROPERTY_MSK_R31E_REG_FD_AFC_DATA_KP        (0x0f << PROPERTY_POS_R31E_REG_FD_AFC_DATA_KP)

#define PROPERTY_POS_R31E_REG_FD_AFC_DATA_KI        0
#define PROPERTY_MSK_R31E_REG_FD_AFC_DATA_KI        (0x0f << PROPERTY_POS_R31E_REG_FD_AFC_DATA_KI)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R31F_FALSE_SYNC_TIMEOUT_TH    (0x0700 | (0x31f - 0x286))
#define PROPERTY_GROUP_R31F_FALSE_SYNC_TIMEOUT_TH   0x07
#define PROPERTY_INDEX_R31F_FALSE_SYNC_TIMEOUT_TH   (0x31f - 0x286)

#define PROPERTY_ADDR_R31F                          (0x0700 | (0x31f - 0x286))
#define PROPERTY_GROUP_R31F                         0x07
#define PROPERTY_INDEX_R31F                         (0x31f - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R320_REG_PR_MATCH_IN_TH       (0x0700 | (0x320 - 0x286))
#define PROPERTY_GROUP_R320_REG_PR_MATCH_IN_TH      0x07
#define PROPERTY_INDEX_R320_REG_PR_MATCH_IN_TH      (0x320 - 0x286)

#define PROPERTY_ADDR_R320                          (0x0700 | (0x320 - 0x286))
#define PROPERTY_GROUP_R320                         0x07
#define PROPERTY_INDEX_R320                         (0x320 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R321_REG_PR_MATCH_OUT_TH      (0x0700 | (0x321 - 0x286))
#define PROPERTY_GROUP_R321_REG_PR_MATCH_OUT_TH     0x07
#define PROPERTY_INDEX_R321_REG_PR_MATCH_OUT_TH     (0x321 - 0x286)

#define PROPERTY_ADDR_R321                          (0x0700 | (0x321 - 0x286))
#define PROPERTY_GROUP_R321                         0x07
#define PROPERTY_INDEX_R321                         (0x321 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R322                          (0x0700 | (0x322 - 0x286))
#define PROPERTY_GROUP_R322                         0x07
#define PROPERTY_INDEX_R322                         (0x322 - 0x286)

#define PROPERTY_POS_R322_REG_PPM_DIR_EN            7
#define PROPERTY_MSK_R322_REG_PPM_DIR_EN            (0x01 << PROPERTY_POS_R322_REG_PPM_DIR_EN)

#define PROPERTY_POS_R322_REG_PPM_ENABLE            6
#define PROPERTY_MSK_R322_REG_PPM_ENABLE            (0x01 << PROPERTY_POS_R322_REG_PPM_ENABLE)

#define PROPERTY_POS_R322_SINC5_4_CLK_MANUE         5
#define PROPERTY_MSK_R322_SINC5_4_CLK_MANUE         (0x01 << PROPERTY_POS_R322_SINC5_4_CLK_MANUE)

#define PROPERTY_POS_R322_SINC5_4_CLK_MANUE_EN      4
#define PROPERTY_MSK_R322_SINC5_4_CLK_MANUE_EN      (0x01 << PROPERTY_POS_R322_SINC5_4_CLK_MANUE_EN)

#define PROPERTY_POS_R322_TX_PRE_ABA_SEL            3
#define PROPERTY_MSK_R322_TX_PRE_ABA_SEL            (0x01 << PROPERTY_POS_R322_TX_PRE_ABA_SEL)

#define PROPERTY_POS_R322_AGC_LOCK_SEL              2
#define PROPERTY_MSK_R322_AGC_LOCK_SEL              (0x01 << PROPERTY_POS_R322_AGC_LOCK_SEL)

#define PROPERTY_POS_R322_SLOPE_NUM_SEL             0
#define PROPERTY_MSK_R322_SLOPE_NUM_SEL             (0x03 << PROPERTY_POS_R322_SLOPE_NUM_SEL)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R323_MANU_PREAMBLE_CFO_L1     (0x0700 | (0x323 - 0x286))
#define PROPERTY_GROUP_R323_MANU_PREAMBLE_CFO_L1    0x07
#define PROPERTY_INDEX_R323_MANU_PREAMBLE_CFO_L1    (0x323 - 0x286)

#define PROPERTY_ADDR_R323                          (0x0700 | (0x323 - 0x286))
#define PROPERTY_GROUP_R323                         0x07
#define PROPERTY_INDEX_R323                         (0x323 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R324_MANU_PREAMBLE_CFO_L2     (0x0700 | (0x324 - 0x286))
#define PROPERTY_GROUP_R324_MANU_PREAMBLE_CFO_L2    0x07
#define PROPERTY_INDEX_R324_MANU_PREAMBLE_CFO_L2    (0x324 - 0x286)

#define PROPERTY_ADDR_R324                          (0x0700 | (0x324 - 0x286))
#define PROPERTY_GROUP_R324                         0x07
#define PROPERTY_INDEX_R324                         (0x324 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R325                          (0x0700 | (0x325 - 0x286))
#define PROPERTY_GROUP_R325                         0x07
#define PROPERTY_INDEX_R325                         (0x325 - 0x286)

#define PROPERTY_POS_R325_AFC_TR_FREQ_NVLD          7
#define PROPERTY_MSK_R325_AFC_TR_FREQ_NVLD          (0x01 << PROPERTY_POS_R325_AFC_TR_FREQ_NVLD)

#define PROPERTY_POS_R325_MANU_PREAMBLE_CFO_EN      6
#define PROPERTY_MSK_R325_MANU_PREAMBLE_CFO_EN      (0x01 << PROPERTY_POS_R325_MANU_PREAMBLE_CFO_EN)

#define PROPERTY_POS_R325_MANU_PREAMBLE_CFO_H       0
#define PROPERTY_MSK_R325_MANU_PREAMBLE_CFO_H       (0x3f << PROPERTY_POS_R325_MANU_PREAMBLE_CFO_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R326                          (0x0700 | (0x326 - 0x286))
#define PROPERTY_GROUP_R326                         0x07
#define PROPERTY_INDEX_R326                         (0x326 - 0x286)

#define PROPERTY_POS_R326_REG_AFC_POW_PARA1         4
#define PROPERTY_MSK_R326_REG_AFC_POW_PARA1         (0x0f << PROPERTY_POS_R326_REG_AFC_POW_PARA1)

#define PROPERTY_POS_R326_REG_AFC_POW_PARA2         0
#define PROPERTY_MSK_R326_REG_AFC_POW_PARA2         (0x0f << PROPERTY_POS_R326_REG_AFC_POW_PARA2)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R327                          (0x0700 | (0x327 - 0x286))
#define PROPERTY_GROUP_R327                         0x07
#define PROPERTY_INDEX_R327                         (0x327 - 0x286)

#define PROPERTY_POS_R327_REG_GAUSS_COEF_MUX        7
#define PROPERTY_MSK_R327_REG_GAUSS_COEF_MUX        (0x01 << PROPERTY_POS_R327_REG_GAUSS_COEF_MUX)

#define PROPERTY_POS_R327_REG_FIFO_THRE             0
#define PROPERTY_MSK_R327_REG_FIFO_THRE             (0x7f << PROPERTY_POS_R327_REG_FIFO_THRE)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R328_REG_AFC_POW_TH           (0x0700 | (0x328 - 0x286))
#define PROPERTY_GROUP_R328_REG_AFC_POW_TH          0x07
#define PROPERTY_INDEX_R328_REG_AFC_POW_TH          (0x328 - 0x286)

#define PROPERTY_ADDR_R328                          (0x0700 | (0x328 - 0x286))
#define PROPERTY_GROUP_R328                         0x07
#define PROPERTY_INDEX_R328                         (0x328 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R329_FD_AFC_FREQ_L0           (0x0700 | (0x329 - 0x286))
#define PROPERTY_GROUP_R329_FD_AFC_FREQ_L0          0x07
#define PROPERTY_INDEX_R329_FD_AFC_FREQ_L0          (0x329 - 0x286)

#define PROPERTY_ADDR_R329                          (0x0700 | (0x329 - 0x286))
#define PROPERTY_GROUP_R329                         0x07
#define PROPERTY_INDEX_R329                         (0x329 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R32A_FD_AFC_FREQ_L1           (0x0700 | (0x32a - 0x286))
#define PROPERTY_GROUP_R32A_FD_AFC_FREQ_L1          0x07
#define PROPERTY_INDEX_R32A_FD_AFC_FREQ_L1          (0x32a - 0x286)

#define PROPERTY_ADDR_R32A                          (0x0700 | (0x32a - 0x286))
#define PROPERTY_GROUP_R32A                         0x07
#define PROPERTY_INDEX_R32A                         (0x32a - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R32B_FD_AFC_FREQ_H            (0x0700 | (0x32b - 0x286))
#define PROPERTY_GROUP_R32B_FD_AFC_FREQ_H           0x07
#define PROPERTY_INDEX_R32B_FD_AFC_FREQ_H           (0x32b - 0x286)

#define PROPERTY_ADDR_R32B                          (0x0700 | (0x32b - 0x286))
#define PROPERTY_GROUP_R32B                         0x07
#define PROPERTY_INDEX_R32B                         (0x32b - 0x286)

#define PROPERTY_POS_R32B_FD_AFC_FREQ_H             0
#define PROPERTY_MSK_R32B_FD_AFC_FREQ_H             (0x3f << PROPERTY_POS_R32B_FD_AFC_FREQ_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R32C_AFC_FREQ_L0              (0x0700 | (0x32c - 0x286))
#define PROPERTY_GROUP_R32C_AFC_FREQ_L0             0x07
#define PROPERTY_INDEX_R32C_AFC_FREQ_L0             (0x32c - 0x286)

#define PROPERTY_ADDR_R32C                          (0x0700 | (0x32c - 0x286))
#define PROPERTY_GROUP_R32C                         0x07
#define PROPERTY_INDEX_R32C                         (0x32c - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R32D_AFC_FREQ_L1              (0x0700 | (0x32d - 0x286))
#define PROPERTY_GROUP_R32D_AFC_FREQ_L1             0x07
#define PROPERTY_INDEX_R32D_AFC_FREQ_L1             (0x32d - 0x286)

#define PROPERTY_ADDR_R32D                          (0x0700 | (0x32d - 0x286))
#define PROPERTY_GROUP_R32D                         0x07
#define PROPERTY_INDEX_R32D                         (0x32d - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R32E_AFC_FREQ_H               (0x0700 | (0x32e - 0x286))
#define PROPERTY_GROUP_R32E_AFC_FREQ_H              0x07
#define PROPERTY_INDEX_R32E_AFC_FREQ_H              (0x32e - 0x286)

#define PROPERTY_ADDR_R32E                          (0x0700 | (0x32e - 0x286))
#define PROPERTY_GROUP_R32E                         0x07
#define PROPERTY_INDEX_R32E                         (0x32e - 0x286)

#define PROPERTY_POS_R32E_AFC_FREQ_H                0
#define PROPERTY_MSK_R32E_AFC_FREQ_H                (0x3f << PROPERTY_POS_R32E_AFC_FREQ_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R32F_PREAMBLE_CFO_L0          (0x0700 | (0x32f - 0x286))
#define PROPERTY_GROUP_R32F_PREAMBLE_CFO_L0         0x07
#define PROPERTY_INDEX_R32F_PREAMBLE_CFO_L0         (0x32f - 0x286)

#define PROPERTY_ADDR_R32F                          (0x0700 | (0x32f - 0x286))
#define PROPERTY_GROUP_R32F                         0x07
#define PROPERTY_INDEX_R32F                         (0x32f - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R330_PREAMBLE_CFO_L1          (0x0700 | (0x330 - 0x286))
#define PROPERTY_GROUP_R330_PREAMBLE_CFO_L1         0x07
#define PROPERTY_INDEX_R330_PREAMBLE_CFO_L1         (0x330 - 0x286)

#define PROPERTY_ADDR_R330                          (0x0700 | (0x330 - 0x286))
#define PROPERTY_GROUP_R330                         0x07
#define PROPERTY_INDEX_R330                         (0x330 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R331_PREAMBLE_CFO_H           (0x0700 | (0x331 - 0x286))
#define PROPERTY_GROUP_R331_PREAMBLE_CFO_H          0x07
#define PROPERTY_INDEX_R331_PREAMBLE_CFO_H          (0x331 - 0x286)

#define PROPERTY_ADDR_R331                          (0x0700 | (0x331 - 0x286))
#define PROPERTY_GROUP_R331                         0x07
#define PROPERTY_INDEX_R331                         (0x331 - 0x286)

#define PROPERTY_POS_R331_PREAMBLE_CFO_H            0
#define PROPERTY_MSK_R331_PREAMBLE_CFO_H            (0x3f << PROPERTY_POS_R331_PREAMBLE_CFO_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R332                          (0x0700 | (0x332 - 0x286))
#define PROPERTY_GROUP_R332                         0x07
#define PROPERTY_INDEX_R332                         (0x332 - 0x286)

#define PROPERTY_POS_R332_REG_CLK_GATED_TEST        7
#define PROPERTY_MSK_R332_REG_CLK_GATED_TEST        (0x01 << PROPERTY_POS_R332_REG_CLK_GATED_TEST)

#define PROPERTY_POS_R332_REG_CLK_LP_EN             6
#define PROPERTY_MSK_R332_REG_CLK_LP_EN             (0x01 << PROPERTY_POS_R332_REG_CLK_LP_EN)

#define PROPERTY_POS_R332_REG_CLK_MDM_TX_EN         5
#define PROPERTY_MSK_R332_REG_CLK_MDM_TX_EN         (0x01 << PROPERTY_POS_R332_REG_CLK_MDM_TX_EN)

#define PROPERTY_POS_R332_REG_CLK_MDM_RX_EN         4
#define PROPERTY_MSK_R332_REG_CLK_MDM_RX_EN         (0x01 << PROPERTY_POS_R332_REG_CLK_MDM_RX_EN)

#define PROPERTY_POS_R332_REG_CLK_MAC_EN            3
#define PROPERTY_MSK_R332_REG_CLK_MAC_EN            (0x01 << PROPERTY_POS_R332_REG_CLK_MAC_EN)

#define PROPERTY_POS_R332_REG_CLK_FIFO_SEL          2
#define PROPERTY_MSK_R332_REG_CLK_FIFO_SEL          (0x01 << PROPERTY_POS_R332_REG_CLK_FIFO_SEL)

#define PROPERTY_POS_R332_REG_CLK_DEBUG_INF_EN      1
#define PROPERTY_MSK_R332_REG_CLK_DEBUG_INF_EN      (0x01 << PROPERTY_POS_R332_REG_CLK_DEBUG_INF_EN)

#define PROPERTY_POS_R332_REG_POWER_GATE_EN         0
#define PROPERTY_MSK_R332_REG_POWER_GATE_EN         (0x01 << PROPERTY_POS_R332_REG_POWER_GATE_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R333_REG_OSC_SETUP_TIME       (0x0700 | (0x333 - 0x286))
#define PROPERTY_GROUP_R333_REG_OSC_SETUP_TIME      0x07
#define PROPERTY_INDEX_R333_REG_OSC_SETUP_TIME      (0x333 - 0x286)

#define PROPERTY_ADDR_R333                          (0x0700 | (0x333 - 0x286))
#define PROPERTY_GROUP_R333                         0x07
#define PROPERTY_INDEX_R333                         (0x333 - 0x286)

#define PROPERTY_POS_R333_REG_OSC_SETUP_TIME        0
#define PROPERTY_MSK_R333_REG_OSC_SETUP_TIME        (0x0f << PROPERTY_POS_R333_REG_OSC_SETUP_TIME)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R334_REG_LDO_ANA_SETUP_TIME   (0x0700 | (0x334 - 0x286))
#define PROPERTY_GROUP_R334_REG_LDO_ANA_SETUP_TIME  0x07
#define PROPERTY_INDEX_R334_REG_LDO_ANA_SETUP_TIME  (0x334 - 0x286)

#define PROPERTY_ADDR_R334                          (0x0700 | (0x334 - 0x286))
#define PROPERTY_GROUP_R334                         0x07
#define PROPERTY_INDEX_R334                         (0x334 - 0x286)

#define PROPERTY_POS_R334_REG_LDO_ANA_SETUP_TIME    0
#define PROPERTY_MSK_R334_REG_LDO_ANA_SETUP_TIME    (0x1f << PROPERTY_POS_R334_REG_LDO_ANA_SETUP_TIME)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R335_REG_LDO_ANA_CLOSE_TIME   (0x0700 | (0x335 - 0x286))
#define PROPERTY_GROUP_R335_REG_LDO_ANA_CLOSE_TIME  0x07
#define PROPERTY_INDEX_R335_REG_LDO_ANA_CLOSE_TIME  (0x335 - 0x286)

#define PROPERTY_ADDR_R335                          (0x0700 | (0x335 - 0x286))
#define PROPERTY_GROUP_R335                         0x07
#define PROPERTY_INDEX_R335                         (0x335 - 0x286)

#define PROPERTY_POS_R335_REG_LDO_ANA_CLOSE_TIME    0
#define PROPERTY_MSK_R335_REG_LDO_ANA_CLOSE_TIME    (0x07 << PROPERTY_POS_R335_REG_LDO_ANA_CLOSE_TIME)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R336_REG_TX_RFPLL_SETUP_TIME  (0x0700 | (0x336 - 0x286))
#define PROPERTY_GROUP_R336_REG_TX_RFPLL_SETUP_TIME 0x07
#define PROPERTY_INDEX_R336_REG_TX_RFPLL_SETUP_TIME (0x336 - 0x286)

#define PROPERTY_ADDR_R336                          (0x0700 | (0x336 - 0x286))
#define PROPERTY_GROUP_R336                         0x07
#define PROPERTY_INDEX_R336                         (0x336 - 0x286)

#define PROPERTY_POS_R336_REG_TX_RFPLL_SETUP_TIME   0
#define PROPERTY_MSK_R336_REG_TX_RFPLL_SETUP_TIME   (0x0f << PROPERTY_POS_R336_REG_TX_RFPLL_SETUP_TIME)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R337_REG_TX_RFPLL_CLOSE_TIME  (0x0700 | (0x337 - 0x286))
#define PROPERTY_GROUP_R337_REG_TX_RFPLL_CLOSE_TIME 0x07
#define PROPERTY_INDEX_R337_REG_TX_RFPLL_CLOSE_TIME (0x337 - 0x286)

#define PROPERTY_ADDR_R337                          (0x0700 | (0x337 - 0x286))
#define PROPERTY_GROUP_R337                         0x07
#define PROPERTY_INDEX_R337                         (0x337 - 0x286)

#define PROPERTY_POS_R337_REG_TX_RFPLL_CLOSE_TIME   0
#define PROPERTY_MSK_R337_REG_TX_RFPLL_CLOSE_TIME   (0x07 << PROPERTY_POS_R337_REG_TX_RFPLL_CLOSE_TIME)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R338_REG_TX_ANA_SETUP_TIME_L  (0x0700 | (0x338 - 0x286))
#define PROPERTY_GROUP_R338_REG_TX_ANA_SETUP_TIME_L 0x07
#define PROPERTY_INDEX_R338_REG_TX_ANA_SETUP_TIME_L (0x338 - 0x286)

#define PROPERTY_ADDR_R338                          (0x0700 | (0x338 - 0x286))
#define PROPERTY_GROUP_R338                         0x07
#define PROPERTY_INDEX_R338                         (0x338 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R339                          (0x0700 | (0x339 - 0x286))
#define PROPERTY_GROUP_R339                         0x07
#define PROPERTY_INDEX_R339                         (0x339 - 0x286)

#define PROPERTY_POS_R339_REG_FIFO_CLK_EN           7
#define PROPERTY_MSK_R339_REG_FIFO_CLK_EN           (0x01 << PROPERTY_POS_R339_REG_FIFO_CLK_EN)

#define PROPERTY_POS_R339_REG_TX_ANA_CLOSE_TIME     4
#define PROPERTY_MSK_R339_REG_TX_ANA_CLOSE_TIME     (0x07 << PROPERTY_POS_R339_REG_TX_ANA_CLOSE_TIME)

#define PROPERTY_POS_R339_REG_TX_ANA_SETUP_TIME_H   0
#define PROPERTY_MSK_R339_REG_TX_ANA_SETUP_TIME_H   (0x01 << PROPERTY_POS_R339_REG_TX_ANA_SETUP_TIME_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R33A_REG_RX_RFPLL_SETUP_TIME  (0x0700 | (0x33a - 0x286))
#define PROPERTY_GROUP_R33A_REG_RX_RFPLL_SETUP_TIME 0x07
#define PROPERTY_INDEX_R33A_REG_RX_RFPLL_SETUP_TIME (0x33a - 0x286)

#define PROPERTY_ADDR_R33A                          (0x0700 | (0x33a - 0x286))
#define PROPERTY_GROUP_R33A                         0x07
#define PROPERTY_INDEX_R33A                         (0x33a - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R33B_REG_RX_RFPLL_CLOSE_TIME  (0x0700 | (0x33b - 0x286))
#define PROPERTY_GROUP_R33B_REG_RX_RFPLL_CLOSE_TIME 0x07
#define PROPERTY_INDEX_R33B_REG_RX_RFPLL_CLOSE_TIME (0x33b - 0x286)

#define PROPERTY_ADDR_R33B                          (0x0700 | (0x33b - 0x286))
#define PROPERTY_GROUP_R33B                         0x07
#define PROPERTY_INDEX_R33B                         (0x33b - 0x286)

#define PROPERTY_POS_R33B_REG_RX_RFPLL_CLOSE_TIME   0
#define PROPERTY_MSK_R33B_REG_RX_RFPLL_CLOSE_TIME   (0x07 << PROPERTY_POS_R33B_REG_RX_RFPLL_CLOSE_TIME)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R33C_REG_RX_ANA_SETUP_TIME    (0x0700 | (0x33c - 0x286))
#define PROPERTY_GROUP_R33C_REG_RX_ANA_SETUP_TIME   0x07
#define PROPERTY_INDEX_R33C_REG_RX_ANA_SETUP_TIME   (0x33c - 0x286)

#define PROPERTY_ADDR_R33C                          (0x0700 | (0x33c - 0x286))
#define PROPERTY_GROUP_R33C                         0x07
#define PROPERTY_INDEX_R33C                         (0x33c - 0x286)

#define PROPERTY_POS_R33C_REG_RX_ANA_SETUP_TIME     0
#define PROPERTY_MSK_R33C_REG_RX_ANA_SETUP_TIME     (0x1f << PROPERTY_POS_R33C_REG_RX_ANA_SETUP_TIME)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R33D_REG_RX_ANA_CLOSE_TIME    (0x0700 | (0x33d - 0x286))
#define PROPERTY_GROUP_R33D_REG_RX_ANA_CLOSE_TIME   0x07
#define PROPERTY_INDEX_R33D_REG_RX_ANA_CLOSE_TIME   (0x33d - 0x286)

#define PROPERTY_ADDR_R33D                          (0x0700 | (0x33d - 0x286))
#define PROPERTY_GROUP_R33D                         0x07
#define PROPERTY_INDEX_R33D                         (0x33d - 0x286)

#define PROPERTY_POS_R33D_REG_RX_ANA_CLOSE_TIME     0
#define PROPERTY_MSK_R33D_REG_RX_ANA_CLOSE_TIME     (0x07 << PROPERTY_POS_R33D_REG_RX_ANA_CLOSE_TIME)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R33E                          (0x0700 | (0x33e - 0x286))
#define PROPERTY_GROUP_R33E                         0x07
#define PROPERTY_INDEX_R33E                         (0x33e - 0x286)

#define PROPERTY_POS_R33E_REG_LP_TEST_MODE          7
#define PROPERTY_MSK_R33E_REG_LP_TEST_MODE          (0x01 << PROPERTY_POS_R33E_REG_LP_TEST_MODE)

#define PROPERTY_POS_R33E_REG_OSC_BUF_EN            4
#define PROPERTY_MSK_R33E_REG_OSC_BUF_EN            (0x01 << PROPERTY_POS_R33E_REG_OSC_BUF_EN)

#define PROPERTY_POS_R33E_REG_LDO_ANA_EN            3
#define PROPERTY_MSK_R33E_REG_LDO_ANA_EN            (0x01 << PROPERTY_POS_R33E_REG_LDO_ANA_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R33F                          (0x0700 | (0x33f - 0x286))
#define PROPERTY_GROUP_R33F                         0x07
#define PROPERTY_INDEX_R33F                         (0x33f - 0x286)

#define PROPERTY_POS_R33F_REG_TX_EN_DIG             7
#define PROPERTY_MSK_R33F_REG_TX_EN_DIG             (0x01 << PROPERTY_POS_R33F_REG_TX_EN_DIG)

#define PROPERTY_POS_R33F_REG_RX_EN_DIG             6
#define PROPERTY_MSK_R33F_REG_RX_EN_DIG             (0x01 << PROPERTY_POS_R33F_REG_RX_EN_DIG)

#define PROPERTY_POS_R33F_REG_TX_RFPLL_EN           5
#define PROPERTY_MSK_R33F_REG_TX_RFPLL_EN           (0x01 << PROPERTY_POS_R33F_REG_TX_RFPLL_EN)

#define PROPERTY_POS_R33F_REG_RX_RFPLL_EN           4
#define PROPERTY_MSK_R33F_REG_RX_RFPLL_EN           (0x01 << PROPERTY_POS_R33F_REG_RX_RFPLL_EN)

#define PROPERTY_POS_R33F_REG_TX_EN_ANA             3
#define PROPERTY_MSK_R33F_REG_TX_EN_ANA             (0x01 << PROPERTY_POS_R33F_REG_TX_EN_ANA)

#define PROPERTY_POS_R33F_REG_RX_EN_ANA             2
#define PROPERTY_MSK_R33F_REG_RX_EN_ANA             (0x01 << PROPERTY_POS_R33F_REG_RX_EN_ANA)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R340_REG_PA2_DLY_TIME_UP      (0x0700 | (0x340 - 0x286))
#define PROPERTY_GROUP_R340_REG_PA2_DLY_TIME_UP     0x07
#define PROPERTY_INDEX_R340_REG_PA2_DLY_TIME_UP     (0x340 - 0x286)

#define PROPERTY_ADDR_R340                          (0x0700 | (0x340 - 0x286))
#define PROPERTY_GROUP_R340                         0x07
#define PROPERTY_INDEX_R340                         (0x340 - 0x286)

#define PROPERTY_POS_R340_REG_PA2_DLY_TIME_UP       0
#define PROPERTY_MSK_R340_REG_PA2_DLY_TIME_UP       (0x3f << PROPERTY_POS_R340_REG_PA2_DLY_TIME_UP)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R341_REG_RAMP_DLY_TIME_UP     (0x0700 | (0x341 - 0x286))
#define PROPERTY_GROUP_R341_REG_RAMP_DLY_TIME_UP    0x07
#define PROPERTY_INDEX_R341_REG_RAMP_DLY_TIME_UP    (0x341 - 0x286)

#define PROPERTY_ADDR_R341                          (0x0700 | (0x341 - 0x286))
#define PROPERTY_GROUP_R341                         0x07
#define PROPERTY_INDEX_R341                         (0x341 - 0x286)

#define PROPERTY_POS_R341_REG_RAMP_DLY_TIME_UP      0
#define PROPERTY_MSK_R341_REG_RAMP_DLY_TIME_UP      (0x3f << PROPERTY_POS_R341_REG_RAMP_DLY_TIME_UP)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R342_REG_RAMP_DLY_TIME_DN     (0x0700 | (0x342 - 0x286))
#define PROPERTY_GROUP_R342_REG_RAMP_DLY_TIME_DN    0x07
#define PROPERTY_INDEX_R342_REG_RAMP_DLY_TIME_DN    (0x342 - 0x286)

#define PROPERTY_ADDR_R342                          (0x0700 | (0x342 - 0x286))
#define PROPERTY_GROUP_R342                         0x07
#define PROPERTY_INDEX_R342                         (0x342 - 0x286)

#define PROPERTY_POS_R342_REG_RAMP_DLY_TIME_DN      0
#define PROPERTY_MSK_R342_REG_RAMP_DLY_TIME_DN      (0x3f << PROPERTY_POS_R342_REG_RAMP_DLY_TIME_DN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R343_REG_PA2_DLY_TIME_DN      (0x0700 | (0x343 - 0x286))
#define PROPERTY_GROUP_R343_REG_PA2_DLY_TIME_DN     0x07
#define PROPERTY_INDEX_R343_REG_PA2_DLY_TIME_DN     (0x343 - 0x286)

#define PROPERTY_ADDR_R343                          (0x0700 | (0x343 - 0x286))
#define PROPERTY_GROUP_R343                         0x07
#define PROPERTY_INDEX_R343                         (0x343 - 0x286)

#define PROPERTY_POS_R343_REG_PA2_DLY_TIME_DN       0
#define PROPERTY_MSK_R343_REG_PA2_DLY_TIME_DN       (0x3f << PROPERTY_POS_R343_REG_PA2_DLY_TIME_DN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R344_REG_RAMP_STEP_UP         (0x0700 | (0x344 - 0x286))
#define PROPERTY_GROUP_R344_REG_RAMP_STEP_UP        0x07
#define PROPERTY_INDEX_R344_REG_RAMP_STEP_UP        (0x344 - 0x286)

#define PROPERTY_ADDR_R344                          (0x0700 | (0x344 - 0x286))
#define PROPERTY_GROUP_R344                         0x07
#define PROPERTY_INDEX_R344                         (0x344 - 0x286)

#define PROPERTY_POS_R344_REG_RAMP_STEP_UP          0
#define PROPERTY_MSK_R344_REG_RAMP_STEP_UP          (0x07 << PROPERTY_POS_R344_REG_RAMP_STEP_UP)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R345_REG_RAMP_STEP_DN         (0x0700 | (0x345 - 0x286))
#define PROPERTY_GROUP_R345_REG_RAMP_STEP_DN        0x07
#define PROPERTY_INDEX_R345_REG_RAMP_STEP_DN        (0x345 - 0x286)

#define PROPERTY_ADDR_R345                          (0x0700 | (0x345 - 0x286))
#define PROPERTY_GROUP_R345                         0x07
#define PROPERTY_INDEX_R345                         (0x345 - 0x286)

#define PROPERTY_POS_R345_REG_RAMP_STEP_DN          0
#define PROPERTY_MSK_R345_REG_RAMP_STEP_DN          (0x07 << PROPERTY_POS_R345_REG_RAMP_STEP_DN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R346                          (0x0700 | (0x346 - 0x286))
#define PROPERTY_GROUP_R346                         0x07
#define PROPERTY_INDEX_R346                         (0x346 - 0x286)

#define PROPERTY_POS_R346_REG_EN_RAMP               3
#define PROPERTY_MSK_R346_REG_EN_RAMP               (0x01 << PROPERTY_POS_R346_REG_EN_RAMP)

#define PROPERTY_POS_R346_REG_EN_PA_2ND             2
#define PROPERTY_MSK_R346_REG_EN_PA_2ND             (0x01 << PROPERTY_POS_R346_REG_EN_PA_2ND)

#define PROPERTY_POS_R346_REG_EN_PA_BUF             0
#define PROPERTY_MSK_R346_REG_EN_PA_BUF             (0x01 << PROPERTY_POS_R346_REG_EN_PA_BUF)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R347                          (0x0700 | (0x347 - 0x286))
#define PROPERTY_GROUP_R347                         0x07
#define PROPERTY_INDEX_R347                         (0x347 - 0x286)

#define PROPERTY_POS_R347_PAD_TEST_MODE             1
#define PROPERTY_MSK_R347_PAD_TEST_MODE             (0x0f << PROPERTY_POS_R347_PAD_TEST_MODE)

#define PROPERTY_POS_R347_PAD_TEST_MODE_EN          0
#define PROPERTY_MSK_R347_PAD_TEST_MODE_EN          (0x01 << PROPERTY_POS_R347_PAD_TEST_MODE_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R348                          (0x0700 | (0x348 - 0x286))
#define PROPERTY_GROUP_R348                         0x07
#define PROPERTY_INDEX_R348                         (0x348 - 0x286)

#define PROPERTY_POS_R348_IQMISMATCH_START_CAL      2
#define PROPERTY_MSK_R348_IQMISMATCH_START_CAL      (0x01 << PROPERTY_POS_R348_IQMISMATCH_START_CAL)

#define PROPERTY_POS_R348_IQMISMATCH_PHSERR_CAL_EN  1
#define PROPERTY_MSK_R348_IQMISMATCH_PHSERR_CAL_EN  (0x01 << PROPERTY_POS_R348_IQMISMATCH_PHSERR_CAL_EN)

#define PROPERTY_POS_R348_IQMISMATCH_COMPENSATE_EN  0
#define PROPERTY_MSK_R348_IQMISMATCH_COMPENSATE_EN  (0x01 << PROPERTY_POS_R348_IQMISMATCH_COMPENSATE_EN)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R349_IQMISMATCH_COMPENSATE_COSG0_L (0x0700 | (0x349 - 0x286))
#define PROPERTY_GROUP_R349_IQMISMATCH_COMPENSATE_COSG0_L 0x07
#define PROPERTY_INDEX_R349_IQMISMATCH_COMPENSATE_COSG0_L (0x349 - 0x286)

#define PROPERTY_ADDR_R349                          (0x0700 | (0x349 - 0x286))
#define PROPERTY_GROUP_R349                         0x07
#define PROPERTY_INDEX_R349                         (0x349 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R34A_IQMISMATCH_COMPENSATE_COSG0_H (0x0700 | (0x34a - 0x286))
#define PROPERTY_GROUP_R34A_IQMISMATCH_COMPENSATE_COSG0_H 0x07
#define PROPERTY_INDEX_R34A_IQMISMATCH_COMPENSATE_COSG0_H (0x34a - 0x286)

#define PROPERTY_ADDR_R34A                          (0x0700 | (0x34a - 0x286))
#define PROPERTY_GROUP_R34A                         0x07
#define PROPERTY_INDEX_R34A                         (0x34a - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R34B_IQMISMATCH_COMPENSATE_SING0_L (0x0700 | (0x34b - 0x286))
#define PROPERTY_GROUP_R34B_IQMISMATCH_COMPENSATE_SING0_L 0x07
#define PROPERTY_INDEX_R34B_IQMISMATCH_COMPENSATE_SING0_L (0x34b - 0x286)

#define PROPERTY_ADDR_R34B                          (0x0700 | (0x34b - 0x286))
#define PROPERTY_GROUP_R34B                         0x07
#define PROPERTY_INDEX_R34B                         (0x34b - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R34C_IQMISMATCH_COMPENSATE_SING0_H (0x0700 | (0x34c - 0x286))
#define PROPERTY_GROUP_R34C_IQMISMATCH_COMPENSATE_SING0_H 0x07
#define PROPERTY_INDEX_R34C_IQMISMATCH_COMPENSATE_SING0_H (0x34c - 0x286)

#define PROPERTY_ADDR_R34C                          (0x0700 | (0x34c - 0x286))
#define PROPERTY_GROUP_R34C                         0x07
#define PROPERTY_INDEX_R34C                         (0x34c - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R34D_IQMISMATCH_COMPENSATE_COSG1_L (0x0700 | (0x34d - 0x286))
#define PROPERTY_GROUP_R34D_IQMISMATCH_COMPENSATE_COSG1_L 0x07
#define PROPERTY_INDEX_R34D_IQMISMATCH_COMPENSATE_COSG1_L (0x34d - 0x286)

#define PROPERTY_ADDR_R34D                          (0x0700 | (0x34d - 0x286))
#define PROPERTY_GROUP_R34D                         0x07
#define PROPERTY_INDEX_R34D                         (0x34d - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R34E_IQMISMATCH_COMPENSATE_COSG1_H (0x0700 | (0x34e - 0x286))
#define PROPERTY_GROUP_R34E_IQMISMATCH_COMPENSATE_COSG1_H 0x07
#define PROPERTY_INDEX_R34E_IQMISMATCH_COMPENSATE_COSG1_H (0x34e - 0x286)

#define PROPERTY_ADDR_R34E                          (0x0700 | (0x34e - 0x286))
#define PROPERTY_GROUP_R34E                         0x07
#define PROPERTY_INDEX_R34E                         (0x34e - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R34F_IQMISMATCH_COMPENSATE_SING1_L (0x0700 | (0x34f - 0x286))
#define PROPERTY_GROUP_R34F_IQMISMATCH_COMPENSATE_SING1_L 0x07
#define PROPERTY_INDEX_R34F_IQMISMATCH_COMPENSATE_SING1_L (0x34f - 0x286)

#define PROPERTY_ADDR_R34F                          (0x0700 | (0x34f - 0x286))
#define PROPERTY_GROUP_R34F                         0x07
#define PROPERTY_INDEX_R34F                         (0x34f - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R350_IQMISMATCH_COMPENSATE_SING1_H (0x0700 | (0x350 - 0x286))
#define PROPERTY_GROUP_R350_IQMISMATCH_COMPENSATE_SING1_H 0x07
#define PROPERTY_INDEX_R350_IQMISMATCH_COMPENSATE_SING1_H (0x350 - 0x286)

#define PROPERTY_ADDR_R350                          (0x0700 | (0x350 - 0x286))
#define PROPERTY_GROUP_R350                         0x07
#define PROPERTY_INDEX_R350                         (0x350 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R351_IQMISMATCH_COMPENSATE_COSG2_L (0x0700 | (0x351 - 0x286))
#define PROPERTY_GROUP_R351_IQMISMATCH_COMPENSATE_COSG2_L 0x07
#define PROPERTY_INDEX_R351_IQMISMATCH_COMPENSATE_COSG2_L (0x351 - 0x286)

#define PROPERTY_ADDR_R351                          (0x0700 | (0x351 - 0x286))
#define PROPERTY_GROUP_R351                         0x07
#define PROPERTY_INDEX_R351                         (0x351 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R352_IQMISMATCH_COMPENSATE_COSG2_H (0x0700 | (0x352 - 0x286))
#define PROPERTY_GROUP_R352_IQMISMATCH_COMPENSATE_COSG2_H 0x07
#define PROPERTY_INDEX_R352_IQMISMATCH_COMPENSATE_COSG2_H (0x352 - 0x286)

#define PROPERTY_ADDR_R352                          (0x0700 | (0x352 - 0x286))
#define PROPERTY_GROUP_R352                         0x07
#define PROPERTY_INDEX_R352                         (0x352 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R353_IQMISMATCH_COMPENSATE_SING2_L (0x0700 | (0x353 - 0x286))
#define PROPERTY_GROUP_R353_IQMISMATCH_COMPENSATE_SING2_L 0x07
#define PROPERTY_INDEX_R353_IQMISMATCH_COMPENSATE_SING2_L (0x353 - 0x286)

#define PROPERTY_ADDR_R353                          (0x0700 | (0x353 - 0x286))
#define PROPERTY_GROUP_R353                         0x07
#define PROPERTY_INDEX_R353                         (0x353 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R354_IQMISMATCH_COMPENSATE_SING2_H (0x0700 | (0x354 - 0x286))
#define PROPERTY_GROUP_R354_IQMISMATCH_COMPENSATE_SING2_H 0x07
#define PROPERTY_INDEX_R354_IQMISMATCH_COMPENSATE_SING2_H (0x354 - 0x286)

#define PROPERTY_ADDR_R354                          (0x0700 | (0x354 - 0x286))
#define PROPERTY_GROUP_R354                         0x07
#define PROPERTY_INDEX_R354                         (0x354 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R355_IQMISMATCH_COMPENSATE_COSG3_L (0x0700 | (0x355 - 0x286))
#define PROPERTY_GROUP_R355_IQMISMATCH_COMPENSATE_COSG3_L 0x07
#define PROPERTY_INDEX_R355_IQMISMATCH_COMPENSATE_COSG3_L (0x355 - 0x286)

#define PROPERTY_ADDR_R355                          (0x0700 | (0x355 - 0x286))
#define PROPERTY_GROUP_R355                         0x07
#define PROPERTY_INDEX_R355                         (0x355 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R356_IQMISMATCH_COMPENSATE_COSG3_H (0x0700 | (0x356 - 0x286))
#define PROPERTY_GROUP_R356_IQMISMATCH_COMPENSATE_COSG3_H 0x07
#define PROPERTY_INDEX_R356_IQMISMATCH_COMPENSATE_COSG3_H (0x356 - 0x286)

#define PROPERTY_ADDR_R356                          (0x0700 | (0x356 - 0x286))
#define PROPERTY_GROUP_R356                         0x07
#define PROPERTY_INDEX_R356                         (0x356 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R357_IQMISMATCH_COMPENSATE_SING3_L (0x0700 | (0x357 - 0x286))
#define PROPERTY_GROUP_R357_IQMISMATCH_COMPENSATE_SING3_L 0x07
#define PROPERTY_INDEX_R357_IQMISMATCH_COMPENSATE_SING3_L (0x357 - 0x286)

#define PROPERTY_ADDR_R357                          (0x0700 | (0x357 - 0x286))
#define PROPERTY_GROUP_R357                         0x07
#define PROPERTY_INDEX_R357                         (0x357 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R358_IQMISMATCH_COMPENSATE_SING3_H (0x0700 | (0x358 - 0x286))
#define PROPERTY_GROUP_R358_IQMISMATCH_COMPENSATE_SING3_H 0x07
#define PROPERTY_INDEX_R358_IQMISMATCH_COMPENSATE_SING3_H (0x358 - 0x286)

#define PROPERTY_ADDR_R358                          (0x0700 | (0x358 - 0x286))
#define PROPERTY_GROUP_R358                         0x07
#define PROPERTY_INDEX_R358                         (0x358 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R359_IQMISMATCH_GAIN_I_L0     (0x0700 | (0x359 - 0x286))
#define PROPERTY_GROUP_R359_IQMISMATCH_GAIN_I_L0    0x07
#define PROPERTY_INDEX_R359_IQMISMATCH_GAIN_I_L0    (0x359 - 0x286)

#define PROPERTY_ADDR_R359                          (0x0700 | (0x359 - 0x286))
#define PROPERTY_GROUP_R359                         0x07
#define PROPERTY_INDEX_R359                         (0x359 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R35A_IQMISMATCH_GAIN_I_L1     (0x0700 | (0x35a - 0x286))
#define PROPERTY_GROUP_R35A_IQMISMATCH_GAIN_I_L1    0x07
#define PROPERTY_INDEX_R35A_IQMISMATCH_GAIN_I_L1    (0x35a - 0x286)

#define PROPERTY_ADDR_R35A                          (0x0700 | (0x35a - 0x286))
#define PROPERTY_GROUP_R35A                         0x07
#define PROPERTY_INDEX_R35A                         (0x35a - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R35B_IQMISMATCH_GAIN_I_L2     (0x0700 | (0x35b - 0x286))
#define PROPERTY_GROUP_R35B_IQMISMATCH_GAIN_I_L2    0x07
#define PROPERTY_INDEX_R35B_IQMISMATCH_GAIN_I_L2    (0x35b - 0x286)

#define PROPERTY_ADDR_R35B                          (0x0700 | (0x35b - 0x286))
#define PROPERTY_GROUP_R35B                         0x07
#define PROPERTY_INDEX_R35B                         (0x35b - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R35C_IQMISMATCH_GAIN_I_L3     (0x0700 | (0x35c - 0x286))
#define PROPERTY_GROUP_R35C_IQMISMATCH_GAIN_I_L3    0x07
#define PROPERTY_INDEX_R35C_IQMISMATCH_GAIN_I_L3    (0x35c - 0x286)

#define PROPERTY_ADDR_R35C                          (0x0700 | (0x35c - 0x286))
#define PROPERTY_GROUP_R35C                         0x07
#define PROPERTY_INDEX_R35C                         (0x35c - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R35D_IQMISMATCH_GAIN_I_L4     (0x0700 | (0x35d - 0x286))
#define PROPERTY_GROUP_R35D_IQMISMATCH_GAIN_I_L4    0x07
#define PROPERTY_INDEX_R35D_IQMISMATCH_GAIN_I_L4    (0x35d - 0x286)

#define PROPERTY_ADDR_R35D                          (0x0700 | (0x35d - 0x286))
#define PROPERTY_GROUP_R35D                         0x07
#define PROPERTY_INDEX_R35D                         (0x35d - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R35E_IQMISMATCH_GAIN_I_L5     (0x0700 | (0x35e - 0x286))
#define PROPERTY_GROUP_R35E_IQMISMATCH_GAIN_I_L5    0x07
#define PROPERTY_INDEX_R35E_IQMISMATCH_GAIN_I_L5    (0x35e - 0x286)

#define PROPERTY_ADDR_R35E                          (0x0700 | (0x35e - 0x286))
#define PROPERTY_GROUP_R35E                         0x07
#define PROPERTY_INDEX_R35E                         (0x35e - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R35F                          (0x0700 | (0x35f - 0x286))
#define PROPERTY_GROUP_R35F                         0x07
#define PROPERTY_INDEX_R35F                         (0x35f - 0x286)

#define PROPERTY_POS_R35F_IQMISMATCH_GAIN_CALDONE   3
#define PROPERTY_MSK_R35F_IQMISMATCH_GAIN_CALDONE   (0x01 << PROPERTY_POS_R35F_IQMISMATCH_GAIN_CALDONE)

#define PROPERTY_POS_R35F_IQMISMATCH_PHSERR_CALDONE 2
#define PROPERTY_MSK_R35F_IQMISMATCH_PHSERR_CALDONE (0x01 << PROPERTY_POS_R35F_IQMISMATCH_PHSERR_CALDONE)

#define PROPERTY_POS_R35F_IQMISMATCH_GAIN_I_H       0
#define PROPERTY_MSK_R35F_IQMISMATCH_GAIN_I_H       (0x03 << PROPERTY_POS_R35F_IQMISMATCH_GAIN_I_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R360_IQMISMATCH_GAIN_Q_L0     (0x0700 | (0x360 - 0x286))
#define PROPERTY_GROUP_R360_IQMISMATCH_GAIN_Q_L0    0x07
#define PROPERTY_INDEX_R360_IQMISMATCH_GAIN_Q_L0    (0x360 - 0x286)

#define PROPERTY_ADDR_R360                          (0x0700 | (0x360 - 0x286))
#define PROPERTY_GROUP_R360                         0x07
#define PROPERTY_INDEX_R360                         (0x360 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R361_IQMISMATCH_GAIN_Q_L1     (0x0700 | (0x361 - 0x286))
#define PROPERTY_GROUP_R361_IQMISMATCH_GAIN_Q_L1    0x07
#define PROPERTY_INDEX_R361_IQMISMATCH_GAIN_Q_L1    (0x361 - 0x286)

#define PROPERTY_ADDR_R361                          (0x0700 | (0x361 - 0x286))
#define PROPERTY_GROUP_R361                         0x07
#define PROPERTY_INDEX_R361                         (0x361 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R362_IQMISMATCH_GAIN_Q_L2     (0x0700 | (0x362 - 0x286))
#define PROPERTY_GROUP_R362_IQMISMATCH_GAIN_Q_L2    0x07
#define PROPERTY_INDEX_R362_IQMISMATCH_GAIN_Q_L2    (0x362 - 0x286)

#define PROPERTY_ADDR_R362                          (0x0700 | (0x362 - 0x286))
#define PROPERTY_GROUP_R362                         0x07
#define PROPERTY_INDEX_R362                         (0x362 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R363_IQMISMATCH_GAIN_Q_L3     (0x0700 | (0x363 - 0x286))
#define PROPERTY_GROUP_R363_IQMISMATCH_GAIN_Q_L3    0x07
#define PROPERTY_INDEX_R363_IQMISMATCH_GAIN_Q_L3    (0x363 - 0x286)

#define PROPERTY_ADDR_R363                          (0x0700 | (0x363 - 0x286))
#define PROPERTY_GROUP_R363                         0x07
#define PROPERTY_INDEX_R363                         (0x363 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R364_IQMISMATCH_GAIN_Q_L4     (0x0700 | (0x364 - 0x286))
#define PROPERTY_GROUP_R364_IQMISMATCH_GAIN_Q_L4    0x07
#define PROPERTY_INDEX_R364_IQMISMATCH_GAIN_Q_L4    (0x364 - 0x286)

#define PROPERTY_ADDR_R364                          (0x0700 | (0x364 - 0x286))
#define PROPERTY_GROUP_R364                         0x07
#define PROPERTY_INDEX_R364                         (0x364 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R365_IQMISMATCH_GAIN_Q_L5     (0x0700 | (0x365 - 0x286))
#define PROPERTY_GROUP_R365_IQMISMATCH_GAIN_Q_L5    0x07
#define PROPERTY_INDEX_R365_IQMISMATCH_GAIN_Q_L5    (0x365 - 0x286)

#define PROPERTY_ADDR_R365                          (0x0700 | (0x365 - 0x286))
#define PROPERTY_GROUP_R365                         0x07
#define PROPERTY_INDEX_R365                         (0x365 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R366_IQMISMATCH_GAIN_Q_H      (0x0700 | (0x366 - 0x286))
#define PROPERTY_GROUP_R366_IQMISMATCH_GAIN_Q_H     0x07
#define PROPERTY_INDEX_R366_IQMISMATCH_GAIN_Q_H     (0x366 - 0x286)

#define PROPERTY_ADDR_R366                          (0x0700 | (0x366 - 0x286))
#define PROPERTY_GROUP_R366                         0x07
#define PROPERTY_INDEX_R366                         (0x366 - 0x286)

#define PROPERTY_POS_R366_IQMISMATCH_GAIN_Q_H       0
#define PROPERTY_MSK_R366_IQMISMATCH_GAIN_Q_H       (0x03 << PROPERTY_POS_R366_IQMISMATCH_GAIN_Q_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R367_IQMISMATCH_IQ_DC_L0      (0x0700 | (0x367 - 0x286))
#define PROPERTY_GROUP_R367_IQMISMATCH_IQ_DC_L0     0x07
#define PROPERTY_INDEX_R367_IQMISMATCH_IQ_DC_L0     (0x367 - 0x286)

#define PROPERTY_ADDR_R367                          (0x0700 | (0x367 - 0x286))
#define PROPERTY_GROUP_R367                         0x07
#define PROPERTY_INDEX_R367                         (0x367 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R368_IQMISMATCH_IQ_DC_L1      (0x0700 | (0x368 - 0x286))
#define PROPERTY_GROUP_R368_IQMISMATCH_IQ_DC_L1     0x07
#define PROPERTY_INDEX_R368_IQMISMATCH_IQ_DC_L1     (0x368 - 0x286)

#define PROPERTY_ADDR_R368                          (0x0700 | (0x368 - 0x286))
#define PROPERTY_GROUP_R368                         0x07
#define PROPERTY_INDEX_R368                         (0x368 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R369_IQMISMATCH_IQ_DC_L2      (0x0700 | (0x369 - 0x286))
#define PROPERTY_GROUP_R369_IQMISMATCH_IQ_DC_L2     0x07
#define PROPERTY_INDEX_R369_IQMISMATCH_IQ_DC_L2     (0x369 - 0x286)

#define PROPERTY_ADDR_R369                          (0x0700 | (0x369 - 0x286))
#define PROPERTY_GROUP_R369                         0x07
#define PROPERTY_INDEX_R369                         (0x369 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R36A_IQMISMATCH_IQ_DC_L3      (0x0700 | (0x36a - 0x286))
#define PROPERTY_GROUP_R36A_IQMISMATCH_IQ_DC_L3     0x07
#define PROPERTY_INDEX_R36A_IQMISMATCH_IQ_DC_L3     (0x36a - 0x286)

#define PROPERTY_ADDR_R36A                          (0x0700 | (0x36a - 0x286))
#define PROPERTY_GROUP_R36A                         0x07
#define PROPERTY_INDEX_R36A                         (0x36a - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R36B_IQMISMATCH_IQ_DC_L4      (0x0700 | (0x36b - 0x286))
#define PROPERTY_GROUP_R36B_IQMISMATCH_IQ_DC_L4     0x07
#define PROPERTY_INDEX_R36B_IQMISMATCH_IQ_DC_L4     (0x36b - 0x286)

#define PROPERTY_ADDR_R36B                          (0x0700 | (0x36b - 0x286))
#define PROPERTY_GROUP_R36B                         0x07
#define PROPERTY_INDEX_R36B                         (0x36b - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R36C_IQMISMATCH_IQ_DC_L5      (0x0700 | (0x36c - 0x286))
#define PROPERTY_GROUP_R36C_IQMISMATCH_IQ_DC_L5     0x07
#define PROPERTY_INDEX_R36C_IQMISMATCH_IQ_DC_L5     (0x36c - 0x286)

#define PROPERTY_ADDR_R36C                          (0x0700 | (0x36c - 0x286))
#define PROPERTY_GROUP_R36C                         0x07
#define PROPERTY_INDEX_R36C                         (0x36c - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R36D_IQMISMATCH_IQ_DC_H       (0x0700 | (0x36d - 0x286))
#define PROPERTY_GROUP_R36D_IQMISMATCH_IQ_DC_H      0x07
#define PROPERTY_INDEX_R36D_IQMISMATCH_IQ_DC_H      (0x36d - 0x286)

#define PROPERTY_ADDR_R36D                          (0x0700 | (0x36d - 0x286))
#define PROPERTY_GROUP_R36D                         0x07
#define PROPERTY_INDEX_R36D                         (0x36d - 0x286)

#define PROPERTY_POS_R36D_IQMISMATCH_IQ_DC_H        0
#define PROPERTY_MSK_R36D_IQMISMATCH_IQ_DC_H        (0x03 << PROPERTY_POS_R36D_IQMISMATCH_IQ_DC_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R36E_NOTCHFLTRCOEFF_L         (0x0700 | (0x36e - 0x286))
#define PROPERTY_GROUP_R36E_NOTCHFLTRCOEFF_L        0x07
#define PROPERTY_INDEX_R36E_NOTCHFLTRCOEFF_L        (0x36e - 0x286)

#define PROPERTY_ADDR_R36E                          (0x0700 | (0x36e - 0x286))
#define PROPERTY_GROUP_R36E                         0x07
#define PROPERTY_INDEX_R36E                         (0x36e - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R36F                          (0x0700 | (0x36f - 0x286))
#define PROPERTY_GROUP_R36F                         0x07
#define PROPERTY_INDEX_R36F                         (0x36f - 0x286)

#define PROPERTY_POS_R36F_DC_CLK_EN                 4
#define PROPERTY_MSK_R36F_DC_CLK_EN                 (0x01 << PROPERTY_POS_R36F_DC_CLK_EN)

#define PROPERTY_POS_R36F_NOTCHFLTRCOEFF_H          0
#define PROPERTY_MSK_R36F_NOTCHFLTRCOEFF_H          (0x0f << PROPERTY_POS_R36F_NOTCHFLTRCOEFF_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R370_NOTCHFLTRGAIN_L          (0x0700 | (0x370 - 0x286))
#define PROPERTY_GROUP_R370_NOTCHFLTRGAIN_L         0x07
#define PROPERTY_INDEX_R370_NOTCHFLTRGAIN_L         (0x370 - 0x286)

#define PROPERTY_ADDR_R370                          (0x0700 | (0x370 - 0x286))
#define PROPERTY_GROUP_R370                         0x07
#define PROPERTY_INDEX_R370                         (0x370 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R371_NOTCHFLTRGAIN_H          (0x0700 | (0x371 - 0x286))
#define PROPERTY_GROUP_R371_NOTCHFLTRGAIN_H         0x07
#define PROPERTY_INDEX_R371_NOTCHFLTRGAIN_H         (0x371 - 0x286)

#define PROPERTY_ADDR_R371                          (0x0700 | (0x371 - 0x286))
#define PROPERTY_GROUP_R371                         0x07
#define PROPERTY_INDEX_R371                         (0x371 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R372                          (0x0700 | (0x372 - 0x286))
#define PROPERTY_GROUP_R372                         0x07
#define PROPERTY_INDEX_R372                         (0x372 - 0x286)

#define PROPERTY_POS_R372_REG_BL_FREQ_TR_BETA1      4
#define PROPERTY_MSK_R372_REG_BL_FREQ_TR_BETA1      (0x0f << PROPERTY_POS_R372_REG_BL_FREQ_TR_BETA1)

#define PROPERTY_POS_R372_REG_BL_FREQ_TR_ALPH1      0
#define PROPERTY_MSK_R372_REG_BL_FREQ_TR_ALPH1      (0x0f << PROPERTY_POS_R372_REG_BL_FREQ_TR_ALPH1)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R373_REG_BL_COEF_SW_TH        (0x0700 | (0x373 - 0x286))
#define PROPERTY_GROUP_R373_REG_BL_COEF_SW_TH       0x07
#define PROPERTY_INDEX_R373_REG_BL_COEF_SW_TH       (0x373 - 0x286)

#define PROPERTY_ADDR_R373                          (0x0700 | (0x373 - 0x286))
#define PROPERTY_GROUP_R373                         0x07
#define PROPERTY_INDEX_R373                         (0x373 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R374_O_DC_OUT_I_L             (0x0700 | (0x374 - 0x286))
#define PROPERTY_GROUP_R374_O_DC_OUT_I_L            0x07
#define PROPERTY_INDEX_R374_O_DC_OUT_I_L            (0x374 - 0x286)

#define PROPERTY_ADDR_R374                          (0x0700 | (0x374 - 0x286))
#define PROPERTY_GROUP_R374                         0x07
#define PROPERTY_INDEX_R374                         (0x374 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R375_O_DC_OUT_Q_L             (0x0700 | (0x375 - 0x286))
#define PROPERTY_GROUP_R375_O_DC_OUT_Q_L            0x07
#define PROPERTY_INDEX_R375_O_DC_OUT_Q_L            (0x375 - 0x286)

#define PROPERTY_ADDR_R375                          (0x0700 | (0x375 - 0x286))
#define PROPERTY_GROUP_R375                         0x07
#define PROPERTY_INDEX_R375                         (0x375 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R376                          (0x0700 | (0x376 - 0x286))
#define PROPERTY_GROUP_R376                         0x07
#define PROPERTY_INDEX_R376                         (0x376 - 0x286)

#define PROPERTY_POS_R376_O_DC_OUT_I_H              4
#define PROPERTY_MSK_R376_O_DC_OUT_I_H              (0x0f << PROPERTY_POS_R376_O_DC_OUT_I_H)

#define PROPERTY_POS_R376_O_DC_OUT_Q_H              0
#define PROPERTY_MSK_R376_O_DC_OUT_Q_H              (0x0f << PROPERTY_POS_R376_O_DC_OUT_Q_H)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R377_REG_XCORR_2ND_TH         (0x0700 | (0x377 - 0x286))
#define PROPERTY_GROUP_R377_REG_XCORR_2ND_TH        0x07
#define PROPERTY_INDEX_R377_REG_XCORR_2ND_TH        (0x377 - 0x286)

#define PROPERTY_ADDR_R377                          (0x0700 | (0x377 - 0x286))
#define PROPERTY_GROUP_R377                         0x07
#define PROPERTY_INDEX_R377                         (0x377 - 0x286)
//--------------------------------------------------------------------------------------------------
#define PROPERTY_ADDR_R378                          (0x0700 | (0x378 - 0x286))
#define PROPERTY_GROUP_R378                         0x07
#define PROPERTY_INDEX_R378                         (0x378 - 0x286)

#define PROPERTY_POS_R378_PRE_SPE_CNT_VLD           7
#define PROPERTY_MSK_R378_PRE_SPE_CNT_VLD           (0x01 << PROPERTY_POS_R378_PRE_SPE_CNT_VLD)

#define PROPERTY_POS_R378_PRE_SPE_CNT_TH            0
#define PROPERTY_MSK_R378_PRE_SPE_CNT_TH            (0x7f << PROPERTY_POS_R378_PRE_SPE_CNT_TH)

typedef enum {
	S_DISABLE = 0,
	S_ENABLE = !S_DISABLE
}SFunctionalState;


/**
 * @brief  PAN312x Flag status. Used to control the state of a flag.
 */
typedef enum {
	S_RESET = 0,
	S_SET = !S_RESET
}SFlagStatus;


/**
 * @brief  boolean type enumeration.
 */
typedef enum {
	S_FALSE = 0,
	S_TRUE  = !S_FALSE
}SBool;


typedef struct {                                                         
	union{
		uint8_t IRQ_STATUS0;
		struct{
			SFlagStatus  IRQ_TX_DONE:1;           
			SFlagStatus  IRQ_RX_DONE:1;          
			SFlagStatus  IRQ_RX_COMPLETE:1;
			SFlagStatus  IRQ_RX_CRC_ERROR:1;           
			SFlagStatus  IRQ_RX_TIMEOUT:1;    
			SFlagStatus  IRQ_RX_NODEID_ERROR:1;    
			SFlagStatus  IRQ_RX_LENGTH_DONE:1;    
			SFlagStatus  IRQ_RX_NODEID_DONE:1;
		}IRQ_STATUS0_F;
	}u0;
	union{
		uint8_t IRQ_STATUS1;
		struct{
			SFlagStatus  :1;/* Reserved bit */          
			SFlagStatus  :1;/* Reserved bit */          
			SFlagStatus  :1;
			SFlagStatus  IRQ_RX_HEADER_CRC_DONE:1;           
			SFlagStatus  IRQ_WAKEUP:1;    
			SFlagStatus  IRQ_ACK_TIMEOUT:1;    
			SFlagStatus  IRQ_ACK_ERROR:1;    
			SFlagStatus  IRQ_LOW_BATTERY:1;/* Reserved bit */
		}IRQ_STATUS1_F;
	}u1;
	union{
		uint8_t IRQ_STATUS2;
		struct{			    	  
			SFlagStatus  IRQ_RX_RSSI_VALID:1;  
			SFlagStatus  :1;/* ��ʱ�ر�`TX_FIFO_TH`���������ݰ�������Ч */
			SFlagStatus  :1;/* Reserved bit */
			SFlagStatus  :1;/* Reserved bit */
 			SFlagStatus  IRQ_TX_FIFO_TH:1;
			SFlagStatus  IRQ_RX_FIFO_TH:1;
			SFlagStatus  :1;/* Reserved bit */
			SFlagStatus  IRQ_RX_RSSI_TIMEOUT:1;
		}IRQ_STATUS2_F;
	}u2;
	union{
		uint8_t IRQ_STATUS3;
		struct{
			SFlagStatus  :1;/* Reserved bit */ 
			SFlagStatus  :1;/* Reserved bit */
			SFlagStatus  :1;/* Reserved bit */
			SFlagStatus  :1;/* Reserved bit */
			SFlagStatus  IRQ_RX_PREAMBLE_DONE:1;
			SFlagStatus  IRQ_RX_SYNCWORD_DONE:1;
			SFlagStatus  IRQ_RX_PREAMBLE_TIMEOUT:1;
			SFlagStatus  IRQ_RX_SYNCWORD_TIMEOUT:1; 
		}IRQ_STATUS3_F;
	}u3;
}PAN312xIrqs;  



typedef enum{
	IRQ_MASK_TX_DONE 			= 0x00000001,                   
	IRQ_MASK_RX_DONE 			= 0x00000002,         
	IRQ_MASK_RX_COMPLETE 		= 0x00000004,            
	IRQ_MASK_RX_CRC_ERROR 		= 0x00000008,                     
	IRQ_MASK_RX_TIMEOUT 		= 0x00000010, 
	IRQ_MASK_RX_NODEID_ERROR 	= 0x00000020,
	IRQ_MASK_RX_LENGTH_DONE  	= 0x00000040, 
	IRQ_MASK_RX_NODEID_DONE 	= 0x00000080,

	IRQ_MASK_RX_HEADER_CRC_DONE	= 0x00000800,        
	IRQ_MASK_WAKEUP		    	= 0x00001000,          
	IRQ_MASK_ACK_TIMEOUT		= 0x00002000,
    IRQ_MASK_ACK_ERROR  		= 0x00004000,     
	IRQ_MASK_LOW_BATTERY		= 0x00008000, 
	
	ALL_IRQ = 0xF8FF
}PAN312xIrqList;
/* bit16~bit23 exceed C51 16-bit int enum range; unused by firmware.
   Replaced with unsigned long macros to clear C219 truncation warning. */
#define IRQ_MASK_RX_SYNCWORD_TIMEOUT   0x00010000UL
#define IRQ_MASK_TX_FIFO_TH            0x00020000UL
#define IRQ_MASK_RX_FIFO_TH            0x00040000UL
#define IRQ_MASK_RX_RSSI_VALID         0x00080000UL
#define IRQ_MASK_RX_PREAMBLE_DONE      0x00100000UL
#define IRQ_MASK_RX_SYNCWORD_DONE      0x00200000UL
#define IRQ_MASK_RX_PREAMBLE_TIMEOUT   0x00400000UL
#define IRQ_MASK_RX_RSSI_TIMEOUT       0x00800000UL


#if defined(POWER_DCDC_0402) || defined(POWER_DCDC_0603)
typedef enum{
    POWER_1dBm = 0x01060c15,
    POWER_0dBm = 0x01050c14,
    POWER_N1dBm = 0x00040c13,
    POWER_N2dBm = 0x01030c12,
    POWER_N3dBm = 0x07020c11,
    POWER_N4dBm = 0x01020c10,
    POWER_N5dBm = 0x0e010c0f,
    POWER_N6dBm = 0x07010c0e,
    POWER_N7dBm = 0x01010c0d,
    POWER_N8dBm = 0x1f000f0c,
    POWER_N9dBm = 0x1d000c0b,
    POWER_N10dBm = 0x12000c0a,
    POWER_N11dBm = 0x0a000c09,
    POWER_N12dBm = 0x04000c08,
    POWER_N13dBm = 0x00000b07,
    POWER_N14dBm = 0x00000806,
    POWER_N15dBm = 0x18080105,
    POWER_N16dBm = 0x18070104,
    POWER_N17dBm = 0x18060103,
    POWER_N18dBm = 0x00130002,
    POWER_N19dBm = 0x00050101,
    POWER_N20dBm = 0x00040100
}PAN312xPowerdBm;

#else
typedef enum{
    POWER_20dBm  = 0x28,
    POWER_19dBm  = 0x27,
    POWER_18dBm  = 0x26,
    POWER_17dBm  = 0x25,
    POWER_16dBm  = 0x24,
    POWER_15dBm  = 0x23,
    POWER_14dBm  = 0x22,
    POWER_13dBm  = 0x21,
    POWER_12dBm  = 0x20,
    POWER_11dBm  = 0x1f,
    POWER_10dBm  = 0x1e,
    POWER_9dBm   = 0x1d,
    POWER_8dBm   = 0x1c,
    POWER_7dBm   = 0x1b,    
    POWER_6dBm   = 0x1a,
    POWER_5dBm   = 0x19,
    POWER_4dBm   = 0x18,
    POWER_3dBm   = 0x17,
    POWER_2dBm   = 0x16,
    POWER_1dBm   = 0x15,
    POWER_0dBm   = 0x14,
    POWER_N1dBm  = 0x13,
    POWER_N2dBm  = 0x12,
    POWER_N3dBm  = 0x11,
    POWER_N4dBm  = 0x10,
    POWER_N5dBm  = 0x0f,
    POWER_N6dBm  = 0x0e,
    POWER_N7dBm  = 0x0d,
    POWER_N8dBm  = 0x0c,
    POWER_N9dBm  = 0x0b,
    POWER_N10dBm = 0x0a,
    POWER_N11dBm = 0x09,
    POWER_N12dBm = 0x08,
    POWER_N13dBm = 0x07,
    POWER_N14dBm = 0x06,
    POWER_N15dBm = 0x05,
    POWER_N16dBm = 0x04,
    POWER_N17dBm = 0x03,
    POWER_N18dBm = 0x02,
    POWER_N19dBm = 0x01,
    POWER_N20dBm = 0x00
}PAN312xPowerdBm;

#endif




typedef enum{
    POWER_LDO_0402 = 0,
    POWER_LDO_0603 = 1,
    POWER_DCDC_0402 = 2,
    POWER_DCDC_0603 = 3
}PAN312xPowerSelect;



typedef enum{
    WHITENING_DISABLE       = 0,
    WHITENING_PN6           = 1,
    WHITENING_PN7           = 2,
    WHITENING_PN9           = 3,
    WHITENING_PN9_IBM       = 4,
    WHITENING_IEEE_802154g  = 5,
    WHITENING_PN9_CCITT     = 6,
    WHITENING_PN11          = 7,
    WHITENING_PN13          = 8,
    WHITENING_PN15          = 9
}PAN312xWhiteningPattern;



typedef enum {
    PAN312x_OK = 0,
    PAN312x_ERROR = -1,
    PAN312x_IO_ERROR = -2,
    PAN312x_TIMEOUT = -3,
    PAN312x_CTS_ERROR = -10,
}PAN312xError;


typedef enum {
    OP_REG_FLAG_INC_ADDR    = 1u << 7,
    OP_REG_FLAG_READ_INFO   = 1u << 6,
    OP_REG_FLAG_READ        = 0u,
    OP_REG_FLAG_WRITE       = 1u << 5,
    OP_REG_FLAG_DATA        = 0u,
    OP_REG_FLAG_XDATA       = 1u << 4,
} PAN312xOpRegFlag;



typedef enum {
    START_COND_ENABLE_TIMEOUT   = 1u << 4,
    START_COND_DISABLE_TIMEOUT  = 0u,
    START_COND_ENABLE_CHANNEL   = 1u << 3,
    START_COND_DISABLE_CHANNEL  = 0u,
    START_COND_ENABLE_ACK       = 1u << 2,
    START_COND_DISABLE_ACK      = 0u,
    START_COND_START_DELAYED    = 1u << 0,
    START_COND_START_NOW        = 0u,
} PAN312xStartCond;

typedef enum {
    SLEEP_MODE   = 0,
    DEEP_SLEEP_MODE    = 1,
} PAN312xSleepMode;

typedef enum {
    WAKE_UP_STATE_READY  = 0,
    WAKE_UP_STATE_TX     = 1,
    WAKE_UP_STATE_RX     = 2,
} PAN312xWakeUpState;

typedef enum{
    IRQ_STATUS_TX_DONE          = 1 << 0,
    IRQ_STATUS_RX_DONE          = 1 << 1,
    IRQ_STATUS_RX_COMPLETE      = 1 << 2,
    IRQ_STATUS_CRC_ERROR        = 1 << 3,
    IRQ_STATUS_RX_TIMEOUT       = 1 << 4,
    IRQ_STATUS_NODEID_ERROR     = 1 << 5,
    IRQ_STATUS_LENGTH_DONE      = 1 << 6,
    IRQ_STATUS_NODEID_DONE      = 1 << 7,
    IRQ_STATUS_FW_STATE         = 7 << (8 + 0),
    IRQ_STATUS_HEADER_CRC_DONE  = 1 << (8 + 3),
    IRQ_STATUS_WAKEUP           = 1 << (8 + 4),
    IRQ_STATUS_ACK_TIMEOUT      = 1 << (8 + 5),
    IRQ_STATUS_ACK_ERROR        = 1 << (8 + 6),
    IRQ_STATUS_RSSI_VALID       = 1 << (16 + 0),
    IRQ_STATUS_TX_FIFO_OFF      = 1 << (16 + 1),
    IRQ_STATUS_DUTYCYCLE_FLAG   = 1 << (16 + 2),
    IRQ_STATUS_TX_FIFO          = 1 << (16 + 4),
    IRQ_STATUS_RX_FIFO          = 1 << (16 + 5),
    IRQ_STATUS_RSSI_TIMEOUT     = 1 << (16 + 7),
    IRQ_STATUS_PREAMBLE_DONE    = 1 << (24 + 4),
    IRQ_STATUS_SYNCWORD_DONE    = 1 << (24 + 5),
    IRQ_STATUS_PREAMBLE_TIMEOUT = 1 << (24 + 6),
    IRQ_STATUS_SYNCWORD_TIMEOUT = (int)0x80000000u,
} PAN312xIrqStatus;



typedef enum{
    SYS_CTRL_IDLE_IF_POSSIBLE = 1 << 7,
    SYS_CTRL_SLEEP_TIMER_ENABLE = 1 << 6,
    SYS_CTRL_AUTO_CLEAR_STATUS = 1 << 5
} PAN312xSysCtrl;


typedef enum{
    PACKET_FILTER_CTRL_ERROR_IRQ_ENABLE = 1 << 7,
    PACKET_FILTER_CTRL_PATTERN3_ENABLE = 1 << 6,
    PACKET_FILTER_CTRL_PATTERN2_ENABLE = 1 << 5,
    PACKET_FILTER_CTRL_PATTERN1_ENABLE = 1 << 4,
    PACKET_FILTER_CTRL_RESET_ON_ERROR = 1 << 3
}PAN312xPacketFilterCtrl;

typedef enum{
    NODE_ID_POSITION_BEFORE_LENGHT = 0,
    NODE_ID_POSITION_AFTER_LENGTH = 1
}PAN312xNodeIdPosition;



typedef enum{
	TxFixedPackedCrcEnable = 0x20,
	TxFixedPackedCrcDisable = 0x00,
	TxVariablePackedCrcEnable = 0x21,
	TxVariablePackedCrcDisable = 0x01,
    Tx802154PacketCrcEnable = 0x29,
}PAN312xTxPacketConfig;

typedef enum{
    PACKET_TYPE_FIXED_LENGTH = 0,
    PACKET_TYPE_VARIABLE_LENGTH = 1
}PAN312xPacketType;



typedef enum{
	RxFixedPackedCrcEnable = 0x60,
    RxFixedPackedCrcBitInvCrcEnable = 0x20,
	RxFixedPackedCrcDisable = 0x00,
	RxVariablePackedCrcEnable = 0x61,
    RxVariablePackedCrcBitInvCrcEnable = 0x22,
	RxVariablePackedCrcDisable = 0x01,
    Rx802154PacketCrcEnable = 0x69,
}PAN312xRxPacketConfig;

typedef enum{
    RX_PACKET_CRC_CAL_BY_FIRMWARE = 0,
    RX_PACKET_CRC_CAL_BY_HARDWARE = 1,
    RX_PACKET_CRC_CAL_BY_HOST = 2,
}PAN312xRxPacketCrcCal;


typedef enum{
    EXIT_STATE_COND_RX_TIMEOUT = PROPERTY_ADDR_RX_TIMEOUT_EXIT_STATE,
    EXIT_STATE_COND_RX_INVALID = PROPERTY_ADDR_RX_INVALID_EXIT_STATE,
    EXIT_STATE_COND_RX_VALID = PROPERTY_ADDR_RX_VALID_EXIT_STATE,
    EXIT_STATE_COND_ACK_TIMEOUT = PROPERTY_ADDR_ACK_TIMEOUT_EXIT_STATE,
    EXIT_STATE_COND_TX_OK = PROPERTY_ADDR_TX_OK_EXIT_STATE
} PAN312xExitStateCond;


typedef enum{
    STATE_READY = 0,
    STATE_TX = 1,
    STATE_RX = 2,
    STATE_SLEEP = 3
} PAN312xState;


typedef enum {
    CRC_MODE_8_BIT  = 0,
    CRC_MODE_16_BIT = 1,
    CRC_MODE_24_BIT = 2,
    CRC_MODE_32_BIT = 3,
}PAN312xCrcMode;


typedef enum{
	CRC_BIT_ORDER_MSB_FIRST = 0,
	CRC_BIT_ORDER_LSB_FIRST = 1,
}PAN312xCrcBitOrder;

typedef enum{
	CRC_BYTE_MSB_FIRST = 0,
	CRC_BYTE_LSB_FIRST = 1,
}PAN312xCrcByteSwap;


typedef enum{
	CRC_RANGE_WHOLE_PAYLOAD = 0,
	CRC_RANGE_DATA_ONLY = 1,
}PAN312xCrcRange;

typedef enum{
	CRC_DISABLE = 0,
	CRC_ENABLE = 1,
}PAN312xCrcState;



typedef enum {
    ENDIAN_BIG = 0,
    ENDIAN_LITTLE = 1,
}PAN312xEndian;

typedef enum {
	MANCHESTER_ZeroToTwo = 0,
	MANCHESTER_ZeroToOne = 1,
}PAN312xManchesterMode;


typedef enum{
	MOD_2FSK  = 0,
    MOD_4FSK  = 1,
    MOD_2GFSK = 2,
    MOD_4GFSK = 3,
	MOD_MSK  = 4,
    MOD_GMSK = 5,
}PAN312xModulationSelect;

typedef enum{
	FIXED_PACKET_MODE = 0,
	VARIABLE_PACKET_MODE = 1,
}PAN312xPacketMode;


typedef enum{
	PREAMBLE_NON_STANDARD = 0,
	PREAMBLE_0101 = 1,
	PREAMBLE_1010 = 2,
}PAN312xPreambleSelect;

typedef enum{
	FEC_HAMING_DISABLE  = 0,
	FEC_HAMING_X3_X_1 	= 1,
	FEC_HAMING_X3_X2_1 	= 2,
}PAN312xFecEncoding;

typedef enum{
	DATA_MODE_PACKET = 0,
	DATA_MODE_DIRECT = 1,
}PAN312xDataMode;

typedef struct{
	PAN312xCrcMode CrcMode;
	uint32_t CrcPolynomial;
	uint32_t CrcSeed;
	PAN312xCrcBitOrder CrcBitOrder;
	PAN312xCrcByteSwap CrcByteSwap;
	PAN312xCrcRange CrcRange;
	SFunctionalState CrcBitInv;
}PAN312xCrcInit;


typedef struct{
	uint32_t FrequencyBase;
	uint32_t FrequencyStep;
	uint16_t FrequencyChannelNumber;
	PAN312xModulationSelect ModulationSelect;
	uint32_t DataRate;
	uint32_t TxDeviation;
	uint32_t RxDeviation;
    PAN312xPowerSelect PowerSelect;
	PAN312xPowerdBm Power;
}PAN312xRadioInit;



typedef struct{
	uint8_t PreambleLength;
	PAN312xPreambleSelect PreambleSeclect;
	uint32_t NonStandardPreamblePattern;
	uint8_t SyncwordLength;
	uint32_t SyncwordPattern;
	PAN312xManchesterMode PreambleManchesterMode;
	SFunctionalState PreambleManchester;
	PAN312xManchesterMode SyncwordManchesterMode;
	SFunctionalState SyncwordManchester;
	PAN312xManchesterMode PayloadManchesterMode;
	SFunctionalState PayloadManchester;
	PAN312xFecEncoding FecEncoding;
	PAN312xWhiteningPattern WhiteningPattern;
	PAN312xDataMode DataMode;
}PAN321xPacketInit;

typedef enum{
    GPIO_OUTPUT_CLK_16Mhz = 0,
    GPIO_OUTPUT_CLK_8Mhz = 1,
    GPIO_OUTPUT_CLK_4Mhz = 2,
    GPIO_OUTPUT_CLK_2Mhz = 3,
    GPIO_OUTPUT_CLK_500Khz = 4,
}PAN312xGpioOutputClk;




//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO0_F_MASK              (0x0f << 4)
#define IOMUX_GPIO0_F_PIC_PCL           (0 << 4)
#define IOMUX_GPIO0_F_GPIO              (1 << 4)
#define IOMUX_GPIO0_F_GPIO_TXCMD        (2 << 4)
#define IOMUX_GPIO0_F_GPIO_RXCMD        (3 << 4)
#define IOMUX_GPIO0_F_UART_TX           (4 << 4)
#define IOMUX_GPIO0_F_UART_RX           (5 << 4)
#define IOMUX_GPIO0_F_DIRECT_TX         (6 << 4)
#define IOMUX_GPIO0_F_DIRECT_RX         (7 << 4)
#define IOMUX_GPIO0_F_DIRECT_CLK        (8 << 4)
#define IOMUX_GPIO0_F_CAD_IND           (9 << 4)
#define IOMUX_GPIO0_F_PAEN_OUTEN        (10 << 4)
#define IOMUX_GPIO0_F_OCLK              (11 << 4)
#define IOMUX_GPIO0_F_TRX_SWITCH        (12 << 4)
#define IOMUX_GPIO0_F_CTS_GPIO          (13 << 4)
#define IOMUX_GPIO0_F_DEBUG_DIG0        (14 << 4)
#define IOMUX_GPIO0_F_IRQ               (15 << 4)
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO1_F_MASK              0x0f
#define IOMUX_GPIO1_F_PIC_PDA           0
#define IOMUX_GPIO1_F_GPIO              1
#define IOMUX_GPIO1_F_GPIO_TXCMD        2
#define IOMUX_GPIO1_F_GPIO_RXCMD        3
#define IOMUX_GPIO1_F_UART_TX           4
#define IOMUX_GPIO1_F_UART_RX           5
#define IOMUX_GPIO1_F_DIRECT_TX         6
#define IOMUX_GPIO1_F_DIRECT_RX         7
#define IOMUX_GPIO1_F_DIRECT_CLK        8
#define IOMUX_GPIO1_F_CAD_IND           9
#define IOMUX_GPIO1_F_PAEN_OUTEN        10
#define IOMUX_GPIO1_F_OCLK              11
#define IOMUX_GPIO1_F_TRX_SWITCH        12
#define IOMUX_GPIO1_F_CTS_GPIO          13
#define IOMUX_GPIO1_F_DEBUG_DIG1        14
#define IOMUX_GPIO1_F_RCH_XTH_RDY       15
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO2_F_MASK              (0x0f << 4)
#define IOMUX_GPIO2_F_GPIO              (0 << 4)
#define IOMUX_GPIO2_F_GPIO_TXCMD        (2 << 4)
#define IOMUX_GPIO2_F_GPIO_RXCMD        (3 << 4)
#define IOMUX_GPIO2_F_UART_TX           (4 << 4)
#define IOMUX_GPIO2_F_UART_RX           (5 << 4)
#define IOMUX_GPIO2_F_DIRECT_TX         (6 << 4)
#define IOMUX_GPIO2_F_DIRECT_RX         (7 << 4)
#define IOMUX_GPIO2_F_DIRECT_CLK        (8 << 4)
#define IOMUX_GPIO2_F_CAD_IND           (9 << 4)
#define IOMUX_GPIO2_F_PAEN_OUTEN        (10 << 4)
#define IOMUX_GPIO2_F_OCLK              (11 << 4)
#define IOMUX_GPIO2_F_TRX_SWITCH        (12 << 4)
#define IOMUX_GPIO2_F_CTS_GPIO          (13 << 4)
#define IOMUX_GPIO2_F_DEBUG_DIG2        (14 << 4)
#define IOMUX_GPIO2_F_RCH_XTH           (15 << 4)
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO3_F_MASK              0x0f
#define IOMUX_GPIO3_F_PAD_NRST          0
#define IOMUX_GPIO3_F_GPIO              1
#define IOMUX_GPIO3_F_GPIO_TXCMD        2
#define IOMUX_GPIO3_F_GPIO_RXCMD        3
#define IOMUX_GPIO3_F_UART_TX           4
#define IOMUX_GPIO3_F_UART_RX           5
#define IOMUX_GPIO3_F_DIRECT_TX         6
#define IOMUX_GPIO3_F_DIRECT_RX         7
#define IOMUX_GPIO3_F_DIRECT_CLK        8
#define IOMUX_GPIO3_F_CAD_IND           9
#define IOMUX_GPIO3_F_PAEN_OUTEN        10
#define IOMUX_GPIO3_F_OCLK              11
#define IOMUX_GPIO3_F_TRX_SWITCH        12
#define IOMUX_GPIO3_F_CTS_GPIO          13
#define IOMUX_GPIO3_F_DEBUG_DIG3        14
#define IOMUX_GPIO3_F_BOD_LVR_RCL_XTH   15
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO4_F_MASK              (0x07 << 4)
#define IOMUX_GPIO4_F_CSK               (0 << 4)
#define IOMUX_GPIO4_F_GPIO              (1 << 4)
#define IOMUX_GPIO4_F_WAKEUP            (2 << 4)
#define IOMUX_GPIO4_F_UART_TX           (3 << 4)
#define IOMUX_GPIO4_F_UART_RX           (4 << 4)
#define IOMUX_GPIO4_F_DEBUG_DIG4        (5 << 4)
#define IOMUX_GPIO4_F_DEBUG_ANA         (6 << 4)
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO5_F_MASK              (0x07 << 3)
#define IOMUX_GPIO5_F_CSN               (0 << 3)
#define IOMUX_GPIO5_F_GPIO              (1 << 3)
#define IOMUX_GPIO5_F_UART_TX           (3 << 3)
#define IOMUX_GPIO5_F_UART_RX           (4 << 3)
#define IOMUX_GPIO5_F_DEBUG_DIG5        (5 << 3)
#define IOMUX_GPIO5_F_DEBUG_ANA         (6 << 3)
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO6_F_MASK              0x07
#define IOMUX_GPIO6_F_MOSI              0
#define IOMUX_GPIO6_F_GPIO              1
#define IOMUX_GPIO6_F_UART_TX           3
#define IOMUX_GPIO6_F_UART_RX           4
#define IOMUX_GPIO6_F_DEBUG_DIG6        5
#define IOMUX_GPIO6_F_DEBUG_ANA         6
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO7_F_MASK              (0x07 << 3)
#define IOMUX_GPIO7_F_MISO              (0 << 3)
#define IOMUX_GPIO7_F_GPIO              (1 << 3)
#define IOMUX_GPIO7_F_UART_TX           (3 << 3)
#define IOMUX_GPIO7_F_UART_RX           (4 << 3)
#define IOMUX_GPIO7_F_DEBUG_DIG7        (5 << 3)
#define IOMUX_GPIO7_F_DEBUG_ANA         (6 << 3)
#define IOMUX_GPIO7_F_CTS_GPIO          (7 << 3)
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO8_F_MASK              0x07
#define IOMUX_GPIO8_F_IRQ               0
#define IOMUX_GPIO8_F_GPIO              1
#define IOMUX_GPIO8_F_RCL_RDY           2
#define IOMUX_GPIO8_F_UART_TX           3
#define IOMUX_GPIO8_F_UART_RX           4
#define IOMUX_GPIO8_F_DEBUG_DIG8        5
#define IOMUX_GPIO8_F_DEBUG_ANA         6
#define IOMUX_GPIO8_F_OCLK              7
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO9_F_MASK              (0x03 << 6)
#define IOMUX_GPIO9_F_GPIO9             (0 << 6)
#define IOMUX_GPIO9_F_XTL_32K_P         (1 << 6)
#define IOMUX_GPIO9_F_DEBUG_DIG9        (2 << 6)
#define IOMUX_GPIO9_F_OCLK              (3 << 6)
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO10_F_MASK             (0x03 << 6)
#define IOMUX_GPIO10_F_GPIO             (0 << 6)
#define IOMUX_GPIO10_F_XTL_32K_N        (1 << 6)
#define IOMUX_GPIO10_F_DEBUG_DIG10      (2 << 6)
#define IOMUX_GPIO10_F_OCLK             (3 << 6)
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO11_F_MASK             (0x01 << 6)
#define IOMUX_GPIO11_F_GPIO             (0 << 6)
#define IOMUX_GPIO11_F_DEBUG_DIG11      (1 << 6)
//--------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO0                     (R1B2   | (IOMUX_GPIO0_F_MASK  << 16))
#define IOMUX_GPIO1                     (R1B1   | (IOMUX_GPIO1_F_MASK  << 16))
#define IOMUX_GPIO2                     (R1B1   | (IOMUX_GPIO2_F_MASK  << 16))
#define IOMUX_GPIO3                     (R014   | (IOMUX_GPIO3_F_MASK  << 16))
#define IOMUX_GPIO4                     (R014   | (IOMUX_GPIO4_F_MASK  << 16))
#define IOMUX_GPIO5                     (R015 	| (IOMUX_GPIO5_F_MASK  << 16))
#define IOMUX_GPIO6                     (R015 	| (IOMUX_GPIO6_F_MASK  << 16))
#define IOMUX_GPIO7                     (R016	| (IOMUX_GPIO7_F_MASK  << 16))
#define IOMUX_GPIO8                     (R016	| (IOMUX_GPIO8_F_MASK  << 16))
#define IOMUX_GPIO9                     (R015 	| (IOMUX_GPIO9_F_MASK  << 16))
#define IOMUX_GPIO10                    (R016 	| (IOMUX_GPIO10_F_MASK << 16))
#define IOMUX_GPIO11                    (R1AF   | (IOMUX_GPIO11_F_MASK << 16))

//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO0_AS_PIC_PCL          (IOMUX_GPIO0 | (IOMUX_GPIO0_F_PIC_PCL << 24))
#define IOMUX_GPIO0_AS_GPIO             (IOMUX_GPIO0 | (IOMUX_GPIO0_F_GPIO << 24))
#define IOMUX_GPIO0_AS_GPIO_TXCMD       (IOMUX_GPIO0 | (IOMUX_GPIO0_F_GPIO_TXCMD << 24))
#define IOMUX_GPIO0_AS_GPIO_RXCMD       (IOMUX_GPIO0 | (IOMUX_GPIO0_F_GPIO_RXCMD << 24))
#define IOMUX_GPIO0_AS_UART_TX          (IOMUX_GPIO0 | (IOMUX_GPIO0_F_UART_TX << 24))
#define IOMUX_GPIO0_AS_UART_RX          (IOMUX_GPIO0 | (IOMUX_GPIO0_F_UART_RX << 24))
#define IOMUX_GPIO0_AS_DIRECT_TX        (IOMUX_GPIO0 | (IOMUX_GPIO0_F_DIRECT_TX << 24))
#define IOMUX_GPIO0_AS_DIRECT_RX        (IOMUX_GPIO0 | (IOMUX_GPIO0_F_DIRECT_RX << 24))
#define IOMUX_GPIO0_AS_DIRECT_CLK       (IOMUX_GPIO0 | (IOMUX_GPIO0_F_DIRECT_CLK << 24))
#define IOMUX_GPIO0_AS_CAD_IND          (IOMUX_GPIO0 | (IOMUX_GPIO0_F_CAD_IND << 24))
#define IOMUX_GPIO0_AS_PAEN_OUTEN       (IOMUX_GPIO0 | (IOMUX_GPIO0_F_PAEN_OUTEN << 24))
#define IOMUX_GPIO0_AS_OCLK             (IOMUX_GPIO0 | (IOMUX_GPIO0_F_OCLK << 24))
#define IOMUX_GPIO0_AS_TRX_SWITCH       (IOMUX_GPIO0 | (IOMUX_GPIO0_F_TRX_SWITCH << 24))
#define IOMUX_GPIO0_AS_CTS_GPIO         (IOMUX_GPIO0 | (IOMUX_GPIO0_F_CTS_GPIO << 24))
#define IOMUX_GPIO0_AS_DEBUG_DIG0       (IOMUX_GPIO0 | (IOMUX_GPIO0_F_DEBUG_DIG0 << 24))
#define IOMUX_GPIO0_AS_IRQ              (IOMUX_GPIO0 | (IOMUX_GPIO0_F_IRQ << 24))
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO1_AS_PIC_PDA          (IOMUX_GPIO1 | (IOMUX_GPIO1_F_PIC_PDA << 24))
#define IOMUX_GPIO1_AS_GPIO             (IOMUX_GPIO1 | (IOMUX_GPIO1_F_GPIO << 24))
#define IOMUX_GPIO1_AS_GPIO_TXCMD       (IOMUX_GPIO1 | (IOMUX_GPIO1_F_GPIO_TXCMD << 24))
#define IOMUX_GPIO1_AS_GPIO_RXCMD       (IOMUX_GPIO1 | (IOMUX_GPIO1_F_GPIO_RXCMD << 24))
#define IOMUX_GPIO1_AS_UART_TX          (IOMUX_GPIO1 | (IOMUX_GPIO1_F_UART_TX << 24))
#define IOMUX_GPIO1_AS_UART_RX          (IOMUX_GPIO1 | (IOMUX_GPIO1_F_UART_RX << 24))
#define IOMUX_GPIO1_AS_DIRECT_TX        (IOMUX_GPIO1 | (IOMUX_GPIO1_F_DIRECT_TX << 24))
#define IOMUX_GPIO1_AS_DIRECT_RX        (IOMUX_GPIO1 | (IOMUX_GPIO1_F_DIRECT_RX << 24))
#define IOMUX_GPIO1_AS_DIRECT_CLK       (IOMUX_GPIO1 | (IOMUX_GPIO1_F_DIRECT_CLK << 24))
#define IOMUX_GPIO1_AS_CAD_IND          (IOMUX_GPIO1 | (IOMUX_GPIO1_F_CAD_IND << 24))
#define IOMUX_GPIO1_AS_PAEN_OUTEN       (IOMUX_GPIO1 | (IOMUX_GPIO1_F_PAEN_OUTEN << 24))
#define IOMUX_GPIO1_AS_OCLK             (IOMUX_GPIO1 | (IOMUX_GPIO1_F_OCLK << 24))
#define IOMUX_GPIO1_AS_TRX_SWITCH       (IOMUX_GPIO1 | (IOMUX_GPIO1_F_TRX_SWITCH << 24))
#define IOMUX_GPIO1_AS_CTS_GPIO         (IOMUX_GPIO1 | (IOMUX_GPIO1_F_CTS_GPIO << 24))
#define IOMUX_GPIO1_AS_DEBUG_DIG1       (IOMUX_GPIO1 | (IOMUX_GPIO1_F_DEBUG_DIG1 << 24))
#define IOMUX_GPIO1_AS_RCH_XTH_RDY      (IOMUX_GPIO1 | (IOMUX_GPIO1_F_RCH_XTH_RDY << 24))
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO2_AS_GPIO             (IOMUX_GPIO2 | (IOMUX_GPIO2_F_GPIO << 24))
#define IOMUX_GPIO2_AS_GPIO_TXCMD       (IOMUX_GPIO2 | (IOMUX_GPIO2_F_GPIO_TXCMD << 24))
#define IOMUX_GPIO2_AS_GPIO_RXCMD       (IOMUX_GPIO2 | (IOMUX_GPIO2_F_GPIO_RXCMD << 24))
#define IOMUX_GPIO2_AS_UART_TX          (IOMUX_GPIO2 | (IOMUX_GPIO2_F_UART_TX << 24))
#define IOMUX_GPIO2_AS_UART_RX          (IOMUX_GPIO2 | (IOMUX_GPIO2_F_UART_RX << 24))
#define IOMUX_GPIO2_AS_DIRECT_TX        (IOMUX_GPIO2 | (IOMUX_GPIO2_F_DIRECT_TX << 24))
#define IOMUX_GPIO2_AS_DIRECT_RX        (IOMUX_GPIO2 | (IOMUX_GPIO2_F_DIRECT_RX << 24))
#define IOMUX_GPIO2_AS_DIRECT_CLK       (IOMUX_GPIO2 | (IOMUX_GPIO2_F_DIRECT_CLK << 24))
#define IOMUX_GPIO2_AS_CAD_IND          (IOMUX_GPIO2 | (IOMUX_GPIO2_F_CAD_IND << 24))
#define IOMUX_GPIO2_AS_PAEN_OUTEN       (IOMUX_GPIO2 | (IOMUX_GPIO2_F_PAEN_OUTEN << 24))
#define IOMUX_GPIO2_AS_OCLK             (IOMUX_GPIO2 | (IOMUX_GPIO2_F_OCLK << 24))
#define IOMUX_GPIO2_AS_TRX_SWITCH       (IOMUX_GPIO2 | (IOMUX_GPIO2_F_TRX_SWITCH << 24))
#define IOMUX_GPIO2_AS_CTS_GPIO         (IOMUX_GPIO2 | (IOMUX_GPIO2_F_CTS_GPIO << 24))
#define IOMUX_GPIO2_AS_DEBUG_DIG2       (IOMUX_GPIO2 | (IOMUX_GPIO2_F_DEBUG_DIG2 << 24))
#define IOMUX_GPIO2_AS_RCH_XTH          (IOMUX_GPIO2 | (IOMUX_GPIO2_F_RCH_XTH << 24))
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO3_AS_PAD_NRST         (IOMUX_GPIO3 | (IOMUX_GPIO3_F_PAD_NRST << 24))
#define IOMUX_GPIO3_AS_GPIO             (IOMUX_GPIO3 | (IOMUX_GPIO3_F_GPIO << 24))
#define IOMUX_GPIO3_AS_GPIO_TXCMD       (IOMUX_GPIO3 | (IOMUX_GPIO3_F_GPIO_TXCMD << 24))
#define IOMUX_GPIO3_AS_GPIO_RXCMD       (IOMUX_GPIO3 | (IOMUX_GPIO3_F_GPIO_RXCMD << 24))
#define IOMUX_GPIO3_AS_UART_TX          (IOMUX_GPIO3 | (IOMUX_GPIO3_F_UART_TX << 24))
#define IOMUX_GPIO3_AS_UART_RX          (IOMUX_GPIO3 | (IOMUX_GPIO3_F_UART_RX << 24))
#define IOMUX_GPIO3_AS_DIRECT_TX        (IOMUX_GPIO3 | (IOMUX_GPIO3_F_DIRECT_TX << 24))
#define IOMUX_GPIO3_AS_DIRECT_RX        (IOMUX_GPIO3 | (IOMUX_GPIO3_F_DIRECT_RX << 24))
#define IOMUX_GPIO3_AS_DIRECT_CLK       (IOMUX_GPIO3 | (IOMUX_GPIO3_F_DIRECT_CLK << 24))
#define IOMUX_GPIO3_AS_CAD_IND          (IOMUX_GPIO3 | (IOMUX_GPIO3_F_CAD_IND << 24))
#define IOMUX_GPIO3_AS_PAEN_OUTEN       (IOMUX_GPIO3 | (IOMUX_GPIO3_F_PAEN_OUTEN << 24))
#define IOMUX_GPIO3_AS_OCLK             (IOMUX_GPIO3 | (IOMUX_GPIO3_F_OCLK << 24))
#define IOMUX_GPIO3_AS_TRX_SWITCH       (IOMUX_GPIO3 | (IOMUX_GPIO3_F_TRX_SWITCH << 24))
#define IOMUX_GPIO3_AS_CTS_GPIO         (IOMUX_GPIO3 | (IOMUX_GPIO3_F_CTS_GPIO << 24))
#define IOMUX_GPIO3_AS_DEBUG_DIG3       (IOMUX_GPIO3 | (IOMUX_GPIO3_F_DEBUG_DIG3 << 24))
#define IOMUX_GPIO3_AS_BOD_LVR_RCL_XTL  (IOMUX_GPIO3 | (IOMUX_GPIO3_F_BOD_LVR_RCL_XTH << 24))
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO4_AS_CSK              (IOMUX_GPIO4 | (IOMUX_GPIO4_F_CSK << 24))
#define IOMUX_GPIO4_AS_GPIO             (IOMUX_GPIO4 | (IOMUX_GPIO4_F_GPIO << 24))
#define IOMUX_GPIO4_AS_WAKEUP           (IOMUX_GPIO4 | (IOMUX_GPIO4_F_WAKEUP << 24))
#define IOMUX_GPIO4_AS_UART_TX          (IOMUX_GPIO4 | (IOMUX_GPIO4_F_UART_TX << 24))
#define IOMUX_GPIO4_AS_UART_RX          (IOMUX_GPIO4 | (IOMUX_GPIO4_F_UART_RX << 24))
#define IOMUX_GPIO4_AS_DEBUG_DIG4       (IOMUX_GPIO4 | (IOMUX_GPIO4_F_DEBUG_DIG4 << 24))
#define IOMUX_GPIO4_AS_DEBUG_ANA        (IOMUX_GPIO4 | (IOMUX_GPIO4_F_DEBUG_ANA << 24))
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO5_AS_CSN              (IOMUX_GPIO5 | (IOMUX_GPIO5_F_CSN << 24))
#define IOMUX_GPIO5_AS_GPIO             (IOMUX_GPIO5 | (IOMUX_GPIO5_F_GPIO << 24))
#define IOMUX_GPIO5_AS_WAKEUP           (IOMUX_GPIO5 | (IOMUX_GPIO5_F_WAKEUP << 24))
#define IOMUX_GPIO5_AS_UART_TX          (IOMUX_GPIO5 | (IOMUX_GPIO5_F_UART_TX << 24))
#define IOMUX_GPIO5_AS_UART_RX          (IOMUX_GPIO5 | (IOMUX_GPIO5_F_UART_RX << 24))
#define IOMUX_GPIO5_AS_DEBUG_DIG5       (IOMUX_GPIO5 | (IOMUX_GPIO5_F_DEBUG_DIG5 << 24))
#define IOMUX_GPIO5_AS_DEBUG_ANA        (IOMUX_GPIO5 | (IOMUX_GPIO5_F_DEBUG_ANA << 24))
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO6_AS_MOSI             (IOMUX_GPIO6 | (IOMUX_GPIO6_F_MOSI << 24))
#define IOMUX_GPIO6_AS_GPIO             (IOMUX_GPIO6 | (IOMUX_GPIO6_F_GPIO << 24))
#define IOMUX_GPIO6_AS_WAKEUP           (IOMUX_GPIO6 | (IOMUX_GPIO6_F_WAKEUP << 24))
#define IOMUX_GPIO6_AS_UART_TX          (IOMUX_GPIO6 | (IOMUX_GPIO6_F_UART_TX << 24))
#define IOMUX_GPIO6_AS_UART_RX          (IOMUX_GPIO6 | (IOMUX_GPIO6_F_UART_RX << 24))
#define IOMUX_GPIO6_AS_DEBUG_DIG6       (IOMUX_GPIO6 | (IOMUX_GPIO6_F_DEBUG_DIG6 << 24))
#define IOMUX_GPIO6_AS_DEBUG_ANA        (IOMUX_GPIO6 | (IOMUX_GPIO6_F_DEBUG_ANA << 24))
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO7_AS_MISO             (IOMUX_GPIO7 | (IOMUX_GPIO7_F_MISO << 24))
#define IOMUX_GPIO7_AS_GPIO             (IOMUX_GPIO7 | (IOMUX_GPIO7_F_GPIO << 24))
#define IOMUX_GPIO7_AS_WAKEUP           (IOMUX_GPIO7 | (IOMUX_GPIO7_F_WAKEUP << 24))
#define IOMUX_GPIO7_AS_UART_TX          (IOMUX_GPIO7 | (IOMUX_GPIO7_F_UART_TX << 24))
#define IOMUX_GPIO7_AS_UART_RX          (IOMUX_GPIO7 | (IOMUX_GPIO7_F_UART_RX << 24))
#define IOMUX_GPIO7_AS_DEBUG_DIG7       (IOMUX_GPIO7 | (IOMUX_GPIO7_F_DEBUG_DIG7 << 24))
#define IOMUX_GPIO7_AS_DEBUG_ANA        (IOMUX_GPIO7 | (IOMUX_GPIO7_F_DEBUG_ANA << 24))
#define IOMUX_GPIO7_AS_CTS_GPIO         (IOMUX_GPIO7 | (IOMUX_GPIO7_F_CTS_GPIO << 24))
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO8_AS_IRQ              (IOMUX_GPIO8 | (IOMUX_GPIO8_F_IRQ << 24))
#define IOMUX_GPIO8_AS_GPIO             (IOMUX_GPIO8 | (IOMUX_GPIO8_F_GPIO << 24))
#define IOMUX_GPIO8_AS_WAKEUP           (IOMUX_GPIO8 | (IOMUX_GPIO8_F_WAKEUP << 24))
#define IOMUX_GPIO8_AS_UART_TX          (IOMUX_GPIO8 | (IOMUX_GPIO8_F_UART_TX << 24))
#define IOMUX_GPIO8_AS_UART_RX          (IOMUX_GPIO8 | (IOMUX_GPIO8_F_UART_RX << 24))
#define IOMUX_GPIO8_AS_DEBUG_DIG8       (IOMUX_GPIO8 | (IOMUX_GPIO8_F_DEBUG_DIG8 << 24))
#define IOMUX_GPIO8_AS_DEBUG_ANA        (IOMUX_GPIO8 | (IOMUX_GPIO8_F_DEBUG_ANA << 24))
#define IOMUX_GPIO8_AS_OCLK             (IOMUX_GPIO8 | (IOMUX_GPIO8_F_OCLK << 24))
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO9_AS_GPIO             (IOMUX_GPIO9 | (IOMUX_GPIO9_F_GPIO9 << 24))
#define IOMUX_GPIO9_AS_XTL_32K_P        (IOMUX_GPIO9 | (IOMUX_GPIO9_F_XTL_32K_P << 24))
#define IOMUX_GPIO9_AS_DEBUG_DIG9       (IOMUX_GPIO9 | (IOMUX_GPIO9_F_DEBUG_DIG9 << 24))
#define IOMUX_GPIO9_AS_OCLK             (IOMUX_GPIO9 | (IOMUX_GPIO9_F_OCLK << 24))
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO10_AS_GPIO            (IOMUX_GPIO10 | (IOMUX_GPIO10_F_GPIO << 24))
#define IOMUX_GPIO10_AS_XTL_32K_N       (IOMUX_GPIO10 | (IOMUX_GPIO10_F_XTL_32K_N << 24))
#define IOMUX_GPIO10_AS_DEBUG_DIG10     (IOMUX_GPIO10 | (IOMUX_GPIO10_F_DEBUG_DIG10 << 24))
#define IOMUX_GPIO10_AS_OCLK            (IOMUX_GPIO10 | (IOMUX_GPIO10_F_OCLK << 24))
//--------------------------------------------------------------------------------------------------
#define IOMUX_GPIO11_AS_GPIO            (IOMUX_GPIO11 | (IOMUX_GPIO11_F_GPIO << 24))
#define IOMUX_GPIO11_AS_DEBUG_DIG11     (IOMUX_GPIO11 | (IOMUX_GPIO11_F_DEBUG_DIG11 << 24))
//--------------------------------------------------------------------------------------------------

#define PAN312x_GPIO_PIN_0                  (1 << 0)
#define PAN312x_GPIO_PIN_1                  (1 << 1)
#define PAN312x_GPIO_PIN_2                  (1 << 2)
#define PAN312x_GPIO_PIN_11                 (1 << 3)
           
#define PAN312x_GPIO_PIN_3                  (1 << 8)
#define PAN312x_GPIO_PIN_4                  (1 << 9)
#define PAN312x_GPIO_PIN_5                  (1 << 10)
#define PAN312x_GPIO_PIN_6                  (1 << 11)
#define PAN312x_GPIO_PIN_7                  (1 << 12)
#define PAN312x_GPIO_PIN_8                  (1 << 13)
#define PAN312x_GPIO_PIN_9                  (1 << 14)
#define PAN312x_GPIO_PIN_10                 (1 << 15)


#define GPIO_OUTPUT_MODE					0x01
#define GPIO_INPUT_MODE						0x02


#define GPIO_WAKEUP_MODE_FALLING_EDGE		0x01
#define GPIO_WAKEUP_MODE_RISING_EDGE		0x02



int PAN312xRaw_Write(const void* buf, int len);
int PAN312xRaw_WriteAddr(uint8_t reg, const void* buf, int len);
int PAN312xRaw_WriteAddrB1(uint8_t reg, uint8_t val);
int PAN312xRaw_WriteAddrB2(uint8_t reg, uint16_t val);
int PAN312xRaw_WriteAddrB3(uint8_t reg, uint32_t val);
int PAN312xRaw_WriteAddrB4(uint8_t reg, uint32_t val);
int PAN312xRaw_ReadAddr(uint8_t reg, void* buf, int len);
int PAN312xRaw_ReadAddrB1(uint8_t reg);
int PAN312xRaw_ReadAddrB2(uint8_t reg);
int PAN312xRaw_ReadAddrB3(uint8_t reg);
uint32_t PAN312xRaw_ReadAddrB4(uint8_t reg);
//--------------------------------------------------------------------------------------------------
int PAN312xReg_Write(uint8_t reg, const void* buf, int len);
int PAN312xReg_WriteB1(uint8_t reg, uint8_t val);
int PAN312xReg_WriteB2(uint8_t reg, uint16_t val);
int PAN312xReg_WriteB3(uint8_t reg, uint32_t val);
int PAN312xReg_WriteB4(uint8_t reg, uint32_t val);
int PAN312xReg_Read(uint8_t reg, void* buf, int len);
int PAN312xReg_ReadB1(uint8_t reg);
int PAN312xReg_ReadB2(uint8_t reg);
int PAN312xReg_ReadB3(uint8_t reg);
uint32_t PAN312xReg_ReadB4(uint8_t reg);

void PAN312x_Write( uint8_t addr, uint8_t dat );
void PAN312x_Read( uint8_t addr, uint8_t *dat );

void PAN312x_Reset(void);
void PAN312x_InitIo(void);
void DIO8_EnableInterrupt(void);
void DIO8_DisableInterrupt(void);
GPIO_PinState DIO8_GetState(void);
int PAN312x_Trigger(void);
void PAN312x_Fsk_Init(void);
void PAN312x_RegMap_Init(void);
void PAN312x_WaitReady(void);
void PAN312x_ReadInvalidData(void);
int PAN312x_Get_FwId(uint16_t *fwid);
int PAN312x_OpRegister(uint8_t op_reg_flag, uint16_t addr, void* buf, int len);
int PAN312x_SetDatas(uint8_t addr, const void* buff, int len);
int PAN312x_SetData(uint8_t addr, uint8_t value);
int PAN312x_GetDatas(uint8_t addr, void* buff, int len);
int PAN312x_GetData(uint8_t addr);
int PAN312x_SetXdatas(uint16_t addr, const void* buff, int len);
int PAN312x_SetXdata(uint16_t addr, uint8_t value);
int PAN312x_GetXdatas(uint16_t addr, void* buff, int len);
int PAN312x_GetXdata(uint16_t addr);
int PAN312x_GetInfoDatas(uint8_t addr, void* buff, int len);
int PAN312x_GetInfoData(uint8_t addr);
int PAN312x_Enter_Tx(uint16_t channel, uint8_t condition, uint16_t tx_len);
int PAN312x_Enter_Rx(uint16_t channel, uint8_t condition, uint16_t rx_len);
int PAN312x_Tx_Ack(void);
int PAN312x_Enter_Sleep(PAN312xSleepMode sleep_mode, PAN312xWakeUpState wake_up_state);
int PAN312x_Enter_Ready(void);
int PAN312x_Set_Property(uint16_t group, uint8_t num_value, const void* value);
int PAN312x_Set_PropertyB1(uint16_t group, uint8_t value);
int PAN312x_Set_PropertyB2(uint16_t group, uint16_t value);
int PAN312x_Set_PropertyB3(uint16_t group, uint32_t value);
int PAN312x_Set_PropertyB4(uint16_t group, uint32_t value);
int PAN312x_Get_Property(uint16_t group, uint8_t num_value, void *value);
int PAN312x_Get_PropertyB1(uint16_t group);
int PAN312x_Get_PropertyB2(uint16_t group);
int PAN312x_Get_PropertyB3(uint16_t group);
uint32_t PAN312x_Get_PropertyB4(uint16_t group);
uint8_t PAN312x_Get_ChipState(void);
int PAN312x_Enter_DutyCycle(uint8_t sleep_now);
void PAN312x_Exit_DutyCycle(void);
int PAN312x_Irq_Get_Status(PAN312xIrqs* pIrqStatus);
int PAN312x_Irq_Clear_AllStatus(void);
int PAN312x_Irq_Clear_Status(PAN312xIrqs pIrqStatus);
//int PAN312x_Irq_Clear_TxFifo_Status(void);
int PAN312x_Irq_Clear_TxFifo_Status(PAN312xIrqs pIrqStatus);
int PAN312x_Irq_Clear_RxFifo_Status(void);
int PAN312x_Irq_Clear_RxDone_Status(void);
int PAN312x_Irq_Clear_RxCrcError_Status(void);
uint32_t PAN312x_Get_GpioIrq_EnableStatus(void);
void PAN312x_GpioIrq_EnableStatus(uint32_t status);
void PAN312x_GpioIrq_Config(PAN312xIrqList xIrq, SFunctionalState xNewState);
void PAN312x_Set_PacketFilter_Ctrl(uint8_t epat1, uint8_t epat2, uint8_t epat3,uint8_t inten, uint8_t reset);
void PAN312x_Set_PacketFilter_Mask(uint32_t pat_mask);
void PAN312x_Set_PacketFiter_Pat1Value(uint32_t pat1_value);
void PAN312x_Set_PacketFiter_Pat2Value(uint32_t pat2_value);
void PAN312x_Set_PacketFiter_Pat3Value(uint32_t pat3_value);
void PAN312x_Set_NodeId_Config(uint8_t nodeid_length, uint8_t nodeid_position);
void PAN312x_Set_Tx_NodeId_Value(uint32_t nodeid_value);
uint32_t PAN312x_Get_Rx_NodeId_Value(void);
void PAN312x_Set_TxPacket_Config(PAN312xTxPacketConfig TxPacketConfig);
void PAN312x_Set_TxPacket_ExtraNumber(uint8_t number);
void PAN312x_Set_TxPacket_Gap(uint16_t gap);
void PAN312x_Set_ExitState(PAN312xExitStateCond cond, PAN312xState state);
PAN312xState PAN312x_Get_ExitState(PAN312xExitStateCond cond);
void PAN312x_Set_TxOk_ExitState(PAN312xState state);
void PAN312x_Set_RxPacket_Config(PAN312xRxPacketConfig RxPacketConfig);
void PAN312x_Set_RxTimeOut(uint32_t rx_time_out);
void PAN312x_Set_RxTimeout_ExitState(PAN312xState state);
void PAN312x_Set_RxInvalid_ExitState(PAN312xState state);
void PAN312x_Set_RxValid_ExitState(PAN312xState state);
void PAN312x_Set_AckTimeOut(uint32_t ack_time_out);
void PAN312x_Set_AckTimeout_ExitState(PAN312xState state);
void PAN312x_Set_AckTxDelay1(uint8_t delay1);
void PAN312x_Set_AckTxDelay2(uint8_t delay2);
void PAN312x_Set_BaseDutyCycleTime(uint32_t BaseTime);
void PAN312x_Set_RepeatDutyCycleTimes(uint8_t DutyCycleTimes);
void PAN312x_System_Ctrl(PAN312xSysCtrl ctrl);
uint16_t PAN312x_Get_Rx_Length(void);
uint16_t PAN312x_Get_RxLengthInPacket(void);
uint16_t PAN312x_Get_RxLengthInFifo(void);
void PAN312x_Write_Fifo(const void *buffer, uint8_t size );
void PAN312x_Read_Fifo( uint8_t *buffer, uint8_t size );
int PAN312x_Get_RxDataByCmd(void *dat, uint8_t length);
void PAN312x_SetLengthFiled(uint8_t number_byte);
void PAN312x_SetLengthFiledEndian(uint8_t endian);
void PAN312x_Set_PayloadManchesterMode(PAN312xManchesterMode mode);
void PAN312x_PayloadManchesterEnable(void);
void PAN312x_PayloadManchesterDisable(void);
void PAN312x_Set_Payload_MsbFirst(void);
void PAN312x_Set_Payload_LsbFirst(void);
void PAN312x_Whitening_Enable(void);
void PAN312x_Whitening_Disable(void);
void PAN312x_Whitening_PN9IBM_Enable(void);
void PAN312x_Whitening_PN9IBM_Disable(void);
void PAN312x_Whitening_Cal_Reset(void);
void PAN312x_Whitening_Cal_NoReset(void);
void PAN312x_Set_Whitening_Length(uint8_t length);
void PAN312x_Set_Whitening_Mode(uint8_t mode);
void PAN312x_Set_Whitening_Seed(uint16_t seed);
void PAN312x_Set_Whitening_BitSel(uint8_t xor1_bit, uint8_t xor2_bit, uint8_t output_bit);
void PAN312x_Set_Payload_Whitening_Pattern(PAN312xWhiteningPattern WhiteningPattern);
void PAN312x_Set_CrcMode(PAN312xCrcMode CrcMode);
void PAN312x_Set_CrcSeed(uint32_t CrcSeed);
void PAN312x_Set_Crc_Polynomial(uint32_t CrcPolynomial);
void PAN312x_Set_CrcInvert(SFunctionalState xNewState);
void PAN312x_Set_CrcEndian(SFunctionalState xNewState);
void PAN312x_CrcInsertSelect(SFunctionalState xNewState);
void PAN312x_Set_CrcBitOrder(PAN312xCrcBitOrder CrcBitOrder);
void PAN312x_Set_CrcByteSwap(PAN312xCrcByteSwap CrcByteSwap);
void PAN312x_Crc_Enable(void);
void PAN312x_Crc_Disable(void);
void PAN312x_Set_Crc(uint8_t crc_index, uint32_t crc_Seed);
void PAN312x_Set_SyncWordPattern(uint32_t Syncwords, uint8_t SyncWordLength);
void PAN312x_Set_SyncWordLength(uint8_t SyncWordLength);
void PAN312x_Set_SyncwordManchesterMode(PAN312xManchesterMode SyncwordManchesterMode);
void PAN312x_SyncwordManchesterEnable(void);
void PAN312x_SyncwordManchesterDisable(void);
void PAN312x_Set_PreambleManchesterMode(PAN312xManchesterMode PreambleManchesterMode);
void PAN312x_PreambleManchesterEnable(void);
void PAN312x_PreambleManchesterDisable(void);
void PAN312x_Set_PreamblePattern(uint8_t PreamblePattern);
void PAN312x_Set_PreambleEndian(uint8_t PreambleEndian);
void PAN312x_Set_PreambleLength(uint8_t PreambleLength);
uint8_t PAN312x_Get_PreambleLength(void);
void PAN312x_Set_NonStandardPreamblePattern(uint32_t PreamblePattern);
uint32_t PAN312x_Get_NonStandardPreamblePattern(void);
void PAN312x_Set_Tx_Deviation(uint32_t tx_deviation);
void PAN312x_Set_Rx_Deviation(uint32_t rx_deviation);
void PAN312x_SynchoronousMode_GpioDirectTxInit(void);
void PAN312x_AsynchoronousMode_GpioDirectTxInit(void);
void PAN312x_SynchoronousMode_GpioDirectRxInit(void);
void PAN312x_AsynchoronousMode_GpioDirectRxInit(void);
void PAN312x_Gpio_Direct_Rx_Regmap_Init(void);
void PAN312x_GPIO_Direct_Tx_Enable(void);
void PAN312x_GPIO_Direct_Tx_Disable(void);
void PAN312x_GPIO_Direct_Rx_Enable(void);
void PAN312x_GPIO_Direct_Rx_Disable(void);
void PAN312x_Gpio_Direct_Asynchronous_Mode(void);
void PAN312x_Gpio_Direct_Synchronous_Mode(void);
void PAN312x_Gpio_Direct_RxByPass_Enable(void);
void PAN312x_Gpio_Direct_RxByPass_Disnable(void);
void PAN312x_Set_FecHamingEncoding(PAN312xFecEncoding HamingEncoding);

void PAN312x_SendLongPacket(uint8_t *txBuffer, uint8_t size);
void PAN312x_SendPacket(uint8_t *txBuffer, uint8_t size);

void PAN312x_Set_ModulationType(PAN312xModulationSelect ModType);

void PAN312x_Set_Frequency(uint32_t base_frequency, uint32_t frequency_step, uint16_t channel_number);
void PAN312x_Set_Frequency_Step(uint32_t frequency_step);
void PAN312x_Set_Frequency_Channel_Number(uint16_t channel_number);
int PAN312x_Wait_Ready(void);
int PAN312x_GetRSSI(void);
int PAN312x_GetChannelCheckRssi(void);
int PAN312x_GetSnr(void);
void PAN312x_Set_Frequency_b(uint32_t Frequency);
//void PAN312x_Set_Power(PAN312xPowerdBm PowerdBm);
void PAN312x_Set_Power(uint32_t Frequency, uint32_t FrequencyStep, uint16_t ChannelNumber, PAN312xPowerSelect PowerSelect, PAN312xPowerdBm PowerdBm);
void PAN312x_RC_Calibration(void);
void PAN312x_Two_Point_Calibration(uint8_t symbol_rate, uint32_t tx_deviation, uint16_t ref_diff);
void PAN312x_DCDC_Enable(void);
void PAN312x_DCDC_Disable(void);
void PAN312x_Iomux_Gpio(uint32_t IomuxGpio);
void PAN312x_Set_Gpio_Mode(uint16_t GpioPin, uint8_t Mode);
void PAN312x_Gpio_Write_Pin(uint16_t GpioPin, uint8_t PinState);
uint8_t PAN312x_Gpio_Read_Pin(uint16_t GpioPin);
void PAN312x_Gpio_DigitalInputEnable(uint16_t GpioPin);
void PAN312x_Enter_Carrier(uint32_t Frequency, uint32_t FrequencyStep, uint16_t ChannelNumber, PAN312xPowerSelect PowerSelect, PAN312xPowerdBm PowerdBm);
void PAN312x_WakeUp_BySpi(void);
void PAN312x_ClkRcl_Enable(void);
void PAN312x_ClkRcl_Disable(void);
void PAN312x_Set_OP_Reg(uint16_t addr, uint8_t num_value, const uint8_t *value);
void PAN312x_Get_OP_Reg(uint16_t addr, uint8_t num_value, uint8_t *value);
void PAN312x_Set_Symbol_RateA(uint16_t symbol_rate_a);
#if 0
void PAN312x_Set_Symbol_RateB(uint8_t symbol_rate_b);
#else
void PAN312x_Set_Symbol_RateB(uint32_t DataRate, uint32_t TxDeviation);
#endif 
void PAN312x_SyncwordLastByteIgnoreEnable(uint8_t SyncwordMask);
void PAN312x_PreambleLastByteIgnoreEnable(uint8_t PreambleMask);
uint8_t PAN312x_GetRealSyncwordLastByte(void);
uint8_t PAN312x_GetRealPreambleLastByte(void);


void PAN312x_GpioOutputOclk(uint32_t IomuxGpio, PAN312xGpioOutputClk ClkFrequency);

void PAN312x_RxMaxPayloadLimitDisable(void);
void PAN312x_RxMaxPayloadLimitEnable(void);
void PAN312x_Reset_Modem(void);
void PAN312x_Flush_RxFifo(void);
void PAN312x_Flush_TxFifo(void);

void PAN312x_PreambleCadIndEnable(void);
void PAN312x_PreambleCadIndDisable(void);
void PAN312x_SyncwordCadIndEnable(void);
void PAN312x_SyncwordCadIndDisable(void);
void PAN312x_RssiCadIndEnable(void);
void PAN312x_RssiCadIndDisable(void);
void PAN312x_SetRssiCadIndThreshold(uint8_t threshold);

void PAN312x_GpioCmdTxEnable(void);
void PAN312x_GpioCmdTxDisable(void);
void PAN312x_GpioCmdRxEnable(void);
void PAN312x_GpioCmdRxDisable(void);

void PAN312x_RadioInit(PAN312xRadioInit* pRadioInitStruct);
void PAN312x_PktInit(PAN321xPacketInit* pPktInitStruct);
void PAN312x_CrcInit(PAN312xCrcInit* pCrcInitStruct);
void PAN312x_Rx_Init(void);

void PAN312x_Iomux_Gpio_BySpi(uint32_t IomuxGpio);
void PAN312x_Set_Gpio_Mode_BySpi(uint16_t GpioPin, uint8_t Mode);
void PAN312x_Gpio_Write_Pin_BySpi(uint16_t GpioPin, uint8_t PinState);
void PAN312x_Software_Reset(void);
void PAN312x_SPI3wire_Enable(void);

void PAN312x_Set_XthCapTrim(uint8_t TrimCode);

void PAN312x_WutEnable(void);
void PAN312x_WutDisable(void);

void PAN312x_IomuxGpio3Rcl(void);

void PAN312x_Set_FcsType(uint8_t FcsType);

void PAN312x_TCXO_ControlByGpio(uint16_t GpioPin, uint8_t PinState);
void PAN312x_TRxSwitchGpioInit(void);
void PAN312x_TxSwitchOn(void);
void PAN312x_TxSwitchOff(void);
void PAN312x_RxSwitchOn(void);
void PAN312x_RxSwitchOff(void);

void PAN312x_Ctk_Two_Point_Calibration(uint32_t DataRate, uint32_t TxDeviation);
void PAN312x_CTK_Set_Power(uint32_t Frequency, uint8_t SupplyMode, uint32_t InductorPackage, int PowerdBm);

#include "PAN312x_RF_CTK_Setting.h"

#define __PAN312x_LOAD_CTKCONFIG()  {                                   \
    for(int i = 0; i < __CTK_ITEM_COUNT; i++){                          \
        const ctk_item_t* item = __CTK_ITEM_ARRAY[i];                   \
        if(item->addr & 0x8000){                                        \
            PAN312x_Set_OP_Reg(item->addr, item->size, item->dat);     \
        } else {                                                        \
            PAN312x_Set_Property(item->addr, item->size, item->dat);   \
        }                                                               \
    }                                                                   \
    if(CTK_CONF_DATA_RATE >= 200){                                      \
        PAN312x_Ctk_Two_Point_Calibration(CTK_DEF_DATA_RATE_KHZ * 1000, CTK_DEF_TX_DEVIATION);   \
    }                                                                   \
    PAN312x_CTK_Set_Power(CTK_DEF_FREQUENCY * 1000000, CTK_DEF_POWER_SUPPLY_MODE, CTK_DEF_INDUCTOR_PACKAGE, CTK_DEF_TX_POWER);\
}
#endif
/****** Copyright (C) 2025-2050 Shanghai Panchip Microelectronics Co., Ltd. All rights reserved. *******/
