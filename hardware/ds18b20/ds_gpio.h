#ifndef __DS_GPIO_H
#define __DS_GPIO_H

#include "stm32f4xx_conf.h"

extern void ds_output_state(int);

extern int ds_input_state(void);

#endif
/*
1.温度超过某一个范围进行报警
2.采集到的温度通过串口输出到串口助手上
*/



