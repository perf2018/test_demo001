#include "button.h"

void button_init(void)
{
	GPIO_InitTypeDef Button_Value;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF, ENABLE);
	
	Button_Value.GPIO_Mode = GPIO_Mode_IN;
	Button_Value.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_7;
	Button_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOF, &Button_Value);
	
	Button_Value.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOE, &Button_Value);
}

int get_button_status(int nu)
{
	int ret = 0;
	
	switch(nu)
	{
		case 0 : ret = GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_9); break;
		case 1 : ret = GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8); break;
		case 2 : ret = GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7); break;
		case 3 : ret = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6); break;
	}
	return !ret;
}










