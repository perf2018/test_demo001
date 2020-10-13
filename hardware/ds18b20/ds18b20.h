#ifndef __DS18B20_H
#define __DS18B20_H

#include "hardware.h"


extern void DS18B20_Init(void);
extern void get_temperature(char *buf);

#endif



