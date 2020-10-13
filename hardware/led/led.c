#include "led.h"

void led_init(void)
{
	GPIO_InitTypeDef Led_Value;//定义结构体类型的变量
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOG, ENABLE);//使能GPIOE组和GPIOG组的时钟	
	
	Led_Value.GPIO_Mode = GPIO_Mode_OUT;//选择输出模式
	Led_Value.GPIO_OType = GPIO_OType_PP;//选择推挽输出
	Led_Value.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;//选择管脚3和管脚4
	Led_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;//选择无上拉无下拉
	Led_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择50MHz的输出速度
	GPIO_Init(GPIOE, &Led_Value);//按照上述配置初始化GPIOE组的管脚

	GPIO_SetBits(GPIOE, GPIO_Pin_3 | GPIO_Pin_4);
	
	Led_Value.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOG, &Led_Value);
	
	GPIO_SetBits(GPIOG, GPIO_Pin_9);	
}

void led_on(int nu)
{
	switch(nu)
	{
		case 0 : GPIO_ResetBits(GPIOG, GPIO_Pin_9); break;
		case 1 : GPIO_ResetBits(GPIOE, GPIO_Pin_4); break;
		case 2 : GPIO_ResetBits(GPIOE, GPIO_Pin_3); break;
	}
}

void led_off(int nu)
{
	switch(nu)
	{
		case 0 : GPIO_SetBits(GPIOG, GPIO_Pin_9); break;
		case 1 : GPIO_SetBits(GPIOE, GPIO_Pin_4); break;
		case 2 : GPIO_SetBits(GPIOE, GPIO_Pin_3); break;
	}
}


int get_led_status(int led_no)
{
	int led_status;
switch(led_no)
	{
		case 0 : led_status = GPIO_ReadOutputDataBit(GPIOG,GPIO_Pin_9); break;
		case 1 : led_status = GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_4); break;
		case 2 : led_status = GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_3); break;
	}
	return led_status;
}
void led_test(void)
{
	u8 i;
	for(i = 0;i < 3;i++)
	{
		led_on(i);
		delay_ms(500);
		led_off(i);
		delay_ms(500);
	}
}







