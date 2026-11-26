#ifndef _BSP_QUEUE_H_
#define _BSP_QUEUE_H_

#include "bsp.h"

#define QUEUE_SIZE 128 // 缓冲区大小需为2的幂（优化取模运算）

typedef struct {
    uint8_t buffer[QUEUE_SIZE];
    volatile uint16_t head; // 写入位置
    volatile uint16_t tail; // 读取位置
}CircularQueue;


// 初始化队列
void bsp_InitQueue(CircularQueue *q);
bool bsp_QueueIsEmpty(CircularQueue *q);
bool bsp_QueueIsFull(CircularQueue *q);
int bsp_QueuePush(CircularQueue *q, uint8_t data);
uint8_t bsp_QueuePop(CircularQueue *q);
uint16_t bsp_QueueCount(CircularQueue *q);

#endif
