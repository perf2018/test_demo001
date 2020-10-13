#ifndef __BUT_EINT_H
#define __BUT_EINT_H
/*
需求:通过中断来控制按键
KEY0	PF9		EXTI9
KEY1	PF8		EXTI8
KEY2	PF7		EXTI7
KEY3	PE6		EXTI6
EXTI9_5			共用同一个中断号,只调用一个中断处理函数就可以了
1.通过RCC使能相关的GPIO时钟
2.初始化GPIO管脚
3.为外部中断选择触发的GPIO管脚
4.初始化NVIC
5.初始化EXTI
*/
#include "hardware.h"

typedef void(*eint_handler)(void);

extern void eint_init(void);

extern void set_eint_handler(eint_handler h0, eint_handler h1, eint_handler h2, eint_handler h3);

#endif









