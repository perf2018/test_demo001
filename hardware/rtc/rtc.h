#ifndef __RTC_H
#define __RTC_H

#include "stm32f4xx_conf.h"

struct time_st
{
	int Y;
	int M;
	int D;
	int W;
	int h;
	int m;
	int s;
};

extern void rtc_init(struct time_st *t);

extern void set_time(struct time_st *t);

extern void get_time(struct time_st *t);

#endif






