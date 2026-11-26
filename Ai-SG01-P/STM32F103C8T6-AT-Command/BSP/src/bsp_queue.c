/**
  ******************************************************************************
  * 文件名 ：   bsp_uart.c
  * 作者   ：   PAN312x RF Team
  * 版本   ：   V1.0.0
  * 时间   ：   
  * 文件描述：

*******************************************************************************/
#include "bsp.h"




// 初始化队列
void bsp_InitQueue(CircularQueue *q) {
    q->head = 0;
    q->tail = 0;
}

// 判断队列是否为空
bool bsp_QueueIsEmpty(CircularQueue *q) {
    return (q->head == q->tail);
}

// 判断队列是否已满
bool bsp_QueueIsFull(CircularQueue *q) {
    return ((q->head + 1) & (QUEUE_SIZE-1)) == q->tail;
}

// 数据入队（返回剩余空间）
int bsp_QueuePush(CircularQueue *q, uint8_t data) {
    if(bsp_QueueIsFull(q)) return -1; // 队列已满
    
    q->buffer[q->head] = data;
    q->head = (q->head + 1) & (QUEUE_SIZE-1); // 位运算替代取模
    return QUEUE_SIZE - ((q->head - q->tail) & (QUEUE_SIZE-1)) -1;
}

// 数据出队
uint8_t bsp_QueuePop(CircularQueue *q) {
    uint8_t data = 0;
    if(!bsp_QueueIsEmpty(q)){
        data = q->buffer[q->tail];
        q->tail = (q->tail + 1) & (QUEUE_SIZE-1);
    }
    return data;
}

// 获取队列元素数量
uint16_t bsp_QueueCount(CircularQueue *q) {
    return (q->head - q->tail) & (QUEUE_SIZE-1);
}
