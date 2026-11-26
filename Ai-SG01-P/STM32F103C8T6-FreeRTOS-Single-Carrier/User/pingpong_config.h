/**
  ******************************************************************************
  * @file    pingpong_config.h
  * @brief   PingPong 对测：只改下面这一个变量，重新编译烧录即可。
  *
  *          一上电就自动开始收发，不需要发任何 AT 命令。
  *
  *             PINGPONG_ROLE = 0  ->  PING（主 / 发送端）：上电先发，等对方回包，循环
  *             PINGPONG_ROLE = 1  ->  PONG（从 / 接收端）：上电先收，收到后回包，循环
  *
  *          两块板分别烧 0 和 1 即可对测。
  *          也可以不改这里，直接烧 Objects 下已经生成好的
  *          Project_PING.hex / Project_PONG.hex 两份固件。
  ******************************************************************************
  */
#ifndef __PINGPONG_CONFIG_H
#define __PINGPONG_CONFIG_H

/* ============ 唯一需要修改的变量：0 = PING 发送, 1 = PONG 接收 ============ */
#ifndef PINGPONG_ROLE
#define PINGPONG_ROLE   1
#endif

#if (PINGPONG_ROLE != 0) && (PINGPONG_ROLE != 1)
#error "PINGPONG_ROLE must be 0 (PING sender) or 1 (PONG receiver)"
#endif

#endif /* __PINGPONG_CONFIG_H */
