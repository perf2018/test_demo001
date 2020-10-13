#ifndef __SYSTICK_H
#define __SYSTICK_H 			   
#include "hardware.h" 

#define SYSCLK 168			//ϵͳʱ�ӵĻ���(ע:��168������168M)

typedef uint32_t  u32;
typedef uint16_t  u16;
typedef uint8_t   u8;
	
void systick_init(void);	//��ʱ�����ĳ�ʼ��
void delay_ms(u16 nms);	//���뼶����ʱ����(����Ϊ������)
void delay_us(u32 nus);	//΢�����ʱ����(����Ϊ΢����)

#endif





























