#ifndef __BUTTON_H
#define __BUTTON_H
/*
KEY0	PF9
KEY1	PF8
KEY2	PF7
KEY3	PE6
检测	高电平	没有按下
检测	低电平	按下
*/
#include "hardware.h"

extern void button_init(void);

extern int get_button_status(int nu);

#endif











