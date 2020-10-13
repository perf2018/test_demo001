#ifndef __RELAY_H
#define __RELAY_H
/*
SWITCH0		PB6
SWITCH1		PB7
SWITCH2		PG7
*/
#include "hardware.h"

extern void relay_init(void);

extern void relay_on(int nu);

extern void relay_off(int nu);

int get_relay_status(int relay_no);

#endif




