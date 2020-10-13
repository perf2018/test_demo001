#ifndef __USART1_H
#define __USART1_H
/*
115200	波特率
1桢
8N1			
8				8个数据位
N				没有奇偶检验位
1				1个停止位
USART1_TX		PA9
USART1_RX		PA10

1.通过RCC使能GPIOA组的时钟
2.通过RCC使能USART1的时钟
3.初始化GPIO(初始化成复用模式)
4.为GPIO管脚选择串口的复用模式
5.初始化串口
6.使能串口
*/
#include "stm32f4xx_conf.h"

typedef void (*usart1_handler)(unsigned char);

extern void usart1_init(void);

extern void usart1_send_byte(unsigned char c);

extern void usart1_send_data(unsigned char *buf);

extern unsigned char usart1_recv_byte(void);

extern void set_usart1_handler(usart1_handler h);

#endif








