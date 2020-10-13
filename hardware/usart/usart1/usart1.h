#ifndef __USART1_H
#define __USART1_H
/*
115200	������
1��
8N1			
8				8������λ
N				û����ż����λ
1				1��ֹͣλ
USART1_TX		PA9
USART1_RX		PA10

1.ͨ��RCCʹ��GPIOA���ʱ��
2.ͨ��RCCʹ��USART1��ʱ��
3.��ʼ��GPIO(��ʼ���ɸ���ģʽ)
4.ΪGPIO�ܽ�ѡ�񴮿ڵĸ���ģʽ
5.��ʼ������
6.ʹ�ܴ���
*/
#include "stm32f4xx_conf.h"

typedef void (*usart1_handler)(unsigned char);

extern void usart1_init(void);

extern void usart1_send_byte(unsigned char c);

extern void usart1_send_data(unsigned char *buf);

extern unsigned char usart1_recv_byte(void);

extern void set_usart1_handler(usart1_handler h);

#endif








