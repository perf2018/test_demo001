#include "at24c02.h"
#include "gpio_iic.h"

void eeprom_init(void)
{
	IIC_Init();
}

void eeprom_byte_write(u8 daddr, u8 waddr, u8 data)
{
	IIC_Start();
	IIC_Send_Byte(daddr);
	IIC_Wait_Ack();
	IIC_Send_Byte(waddr);
	IIC_Wait_Ack();
	IIC_Send_Byte(data);
	IIC_Wait_Ack();
	IIC_Stop();
}

void eeprom_page_write(u8 daddr, u8 waddr, u8 *data)
{
	
}

u8 eeprom_current_read(u8 daddr)
{
	return 0;
}

u8 eeprom_random_read(u8 daddr, u8 waddr)
{
	u8 save = 0;
	
	IIC_Start();
	IIC_Send_Byte(daddr);
	IIC_Wait_Ack();
	IIC_Send_Byte(waddr);
	IIC_Wait_Ack();
	IIC_Start();
	IIC_Send_Byte(daddr | 1);
	IIC_Wait_Ack();
	save = IIC_Read_Byte(0);
	IIC_Stop();
	
	return save;
}

void eeprom_sequential_read(u8 daddr, u8 waddr, u8 *data)
{
	
}








