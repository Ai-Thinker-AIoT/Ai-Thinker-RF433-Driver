/* stdint.h — AI8051U / 长缨-I(C351) 32位 宽度类型垫片
 * C351 下：int=16bit, long=32bit, long long 不一定支持，
 * 故 64 位类型按 32 位降级定义（本工程固件未使用 64 位）。
 */
#ifndef __STDINT_H
#define __STDINT_H

typedef unsigned char  uint8_t;
typedef unsigned int   uint16_t;
typedef unsigned long  uint32_t;
typedef unsigned long  uint64_t;   /* 降级：C351 未必支持 long long */

typedef signed char    int8_t;
typedef signed int     int16_t;
typedef signed long    int32_t;
typedef signed long    int64_t;     /* 降级 */

#endif /* __STDINT_H */
