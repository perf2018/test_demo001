#ifndef __IWDG_H
#define __IWDG_H

#include "stm32f4xx_conf.h"

extern void iwdg_init(int ms);

extern void feed_dog(void);

#endif







