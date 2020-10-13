#ifndef __BITBAND_H
#define __BITBAND_H

#include "stm32f4xx_conf.h"

#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEMADDR(addr) *(volatile unsigned int *)(addr)
#define BIT_BAND(addr, bitnum) MEMADDR(BITBAND(addr, bitnum))

#define GPIOA_IDR_ADDR	(GPIOA_BASE + 0x10)
#define GPIOA_ODR_ADDR	(GPIOA_BASE + 0x14)

#define GPIOB_IDR_ADDR	(GPIOB_BASE + 0x10)
#define GPIOB_ODR_ADDR	(GPIOB_BASE + 0x14)

#define GPIOC_IDR_ADDR	(GPIOC_BASE + 0x10)
#define GPIOC_ODR_ADDR	(GPIOC_BASE + 0x14)

#define GPIOD_IDR_ADDR	(GPIOD_BASE + 0x10)
#define GPIOD_ODR_ADDR	(GPIOD_BASE + 0x14)

#define GPIOE_IDR_ADDR	(GPIOE_BASE + 0x10)
#define GPIOE_ODR_ADDR	(GPIOE_BASE + 0x14)

#define GPIOF_IDR_ADDR	(GPIOF_BASE + 0x10)
#define GPIOF_ODR_ADDR	(GPIOF_BASE + 0x14)

#define GPIOG_IDR_ADDR	(GPIOG_BASE + 0x10)
#define GPIOG_ODR_ADDR	(GPIOG_BASE + 0x14)

#define GPIOH_IDR_ADDR	(GPIOH_BASE + 0x10)
#define GPIOH_ODR_ADDR	(GPIOH_BASE + 0x14)

#define PAIn(n) BIT_BAND(GPIOA_IDR_ADDR, n)
#define PAOut(n) BIT_BAND(GPIOA_ODR_ADDR, n)

#define PBIn(n) BIT_BAND(GPIOB_IDR_ADDR, n)
#define PBOut(n) BIT_BAND(GPIOB_ODR_ADDR, n)

#define PCIn(n) BIT_BAND(GPIOC_IDR_ADDR, n)
#define PCOut(n) BIT_BAND(GPIOC_ODR_ADDR, n)

#define PDIn(n) BIT_BAND(GPIOD_IDR_ADDR, n)
#define PDOut(n) BIT_BAND(GPIOD_ODR_ADDR, n)

#define PEIn(n) BIT_BAND(GPIOE_IDR_ADDR, n)
#define PEOut(n) BIT_BAND(GPIOE_ODR_ADDR, n)

#define PFIn(n) BIT_BAND(GPIOF_IDR_ADDR, n)
#define PFOut(n) BIT_BAND(GPIOF_ODR_ADDR, n)

#define PGIn(n) BIT_BAND(GPIOG_IDR_ADDR, n)
#define PGOut(n) BIT_BAND(GPIOG_ODR_ADDR, n)

#define PHIn(n) BIT_BAND(GPIOH_IDR_ADDR, n)
#define PHOut(n) BIT_BAND(GPIOH_ODR_ADDR, n)

#endif











