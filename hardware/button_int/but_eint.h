#ifndef __BUT_EINT_H
#define __BUT_EINT_H
/*
����:ͨ���ж������ư���
KEY0	PF9		EXTI9
KEY1	PF8		EXTI8
KEY2	PF7		EXTI7
KEY3	PE6		EXTI6
EXTI9_5			����ͬһ���жϺ�,ֻ����һ���жϴ������Ϳ�����
1.ͨ��RCCʹ����ص�GPIOʱ��
2.��ʼ��GPIO�ܽ�
3.Ϊ�ⲿ�ж�ѡ�񴥷���GPIO�ܽ�
4.��ʼ��NVIC
5.��ʼ��EXTI
*/
#include "hardware.h"

typedef void(*eint_handler)(void);

extern void eint_init(void);

extern void set_eint_handler(eint_handler h0, eint_handler h1, eint_handler h2, eint_handler h3);

#endif









