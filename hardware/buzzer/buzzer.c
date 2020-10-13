#include "buzzer.h"

void buzzer_init(void)
{
	GPIO_InitTypeDef Buzzer_Value;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOD���ʱ��

	Buzzer_Value.GPIO_Mode = GPIO_Mode_OUT;
	Buzzer_Value.GPIO_OType = GPIO_OType_PP;
	Buzzer_Value.GPIO_Pin = GPIO_Pin_7;
	Buzzer_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;
	Buzzer_Value.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &Buzzer_Value);
	
	GPIO_ResetBits(GPIOD, GPIO_Pin_7);
}

void buzzer_on(void)
{
	GPIO_SetBits(GPIOD, GPIO_Pin_7);
}

void buzzer_off(void)
{
	GPIO_ResetBits(GPIOD, GPIO_Pin_7);
}

int get_buzzer_status(void)
{
	return GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_7);
}












