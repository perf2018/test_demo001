#ifndef __PM_H
#define __PM_H
/*
PM2.5_LED		PC13		OUTPUT
*/
#include "hardware.h"

extern void pm_init(void);

extern int get_pm_value(void);

#endif








