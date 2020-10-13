#ifndef __EEPROM_H
#define __EEPROM_H

#include "stm32f4xx_conf.h"

extern void eeprom_init(void);

extern void eeprom_byte_write(u8 daddr, u8 waddr, u8 data);

extern void eeprom_page_write(u8 daddr, u8 waddr, u8 *data);

extern u8 eeprom_current_read(u8 daddr);

extern u8 eeprom_random_read(u8 daddr, u8 waddr);

extern void eeprom_sequential_read(u8 daddr, u8 waddr, u8 *data);

#endif







