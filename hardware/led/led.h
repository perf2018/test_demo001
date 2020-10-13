#ifndef __LED_H
#define __LED_H
/*
LED0	PG9
LED1	PE4
LED2	PE3
高电平	灭
低电平	亮
*/
#include "hardware.h"

extern void led_init(void);

extern void led_on(int nu);

extern void led_off(int nu);

int get_led_status(int led_no);

void led_test(void);
#endif






