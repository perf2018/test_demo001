#ifndef __ADC_PM_H
#define __ADC_PM_H

#include "hardware.h"

/*
PM2.5_Value		PC0		ADC123_IN10
*/

extern void adc_pm_init(void);

extern void adc_pm_start(void);

extern void adc_pm_wait(void);

extern int get_adc_pm_value(void);

#endif




