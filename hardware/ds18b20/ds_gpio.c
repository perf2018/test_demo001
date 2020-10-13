#include "ds_gpio.h"
#include "bitband.h"

void set_ds_gpio_output(void)
{
	GPIO_InitTypeDef Gpio_Value;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_OUT;
	Gpio_Value.GPIO_OType = GPIO_OType_PP;
	Gpio_Value.GPIO_Pin = GPIO_Pin_15;
	Gpio_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &Gpio_Value);
}

void set_ds_gpio_input(void)
{
	GPIO_InitTypeDef Gpio_Value;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IN;
	Gpio_Value.GPIO_Pin = GPIO_Pin_15;
	Gpio_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &Gpio_Value);	
}

void ds_output_state(int status)
{
	set_ds_gpio_output();
	if(status == 1)
		PBOut(15) = 1;
	else
		PBOut(15) = 0;
}

int ds_input_state(void)
{
	set_ds_gpio_input();
	return PBIn(15);
}











