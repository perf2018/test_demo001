#ifndef __BUZZER_H
#define __BUZZER_H
/*
BUZZER	PD7
高电平	响
低电平	不响
*/
#include "hardware.h"

extern void buzzer_init(void);

extern void buzzer_on(void);

extern void buzzer_off(void);

int get_buzzer_status(void);

#endif










