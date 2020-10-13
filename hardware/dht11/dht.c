#include "dht.h"


void set_dht_gpio_output(void)
{
	GPIO_InitTypeDef Gpio_Value;
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_OUT;
	Gpio_Value.GPIO_OType = GPIO_OType_PP;
	Gpio_Value.GPIO_Pin = GPIO_Pin_4;
	Gpio_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Gpio_Value);
}

void set_dht_gpio_input(void)
{
	GPIO_InitTypeDef Gpio_Value;
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IN;
	Gpio_Value.GPIO_Pin = GPIO_Pin_4;
	Gpio_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &Gpio_Value);
}

void dht_output_state(int status)
{
	set_dht_gpio_output();
	if(status == 1)
		PAOut(4) = 1;
	else
		PAOut(4) = 0;
}

int dht_input_state(void)
{
	set_dht_gpio_input();
	return PAIn(4);
}

void dht_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
}

void get_dht_value(char *buf)
{
	int status = 0;
	int time = 0;
	int i = 0;
	unsigned char data = 0;
	
	dht_output_state(1);
	dht_output_state(0);
	delay_ms(20);
	dht_output_state(1);
	//while(dht_input_state());
	
	do
	{
		status = dht_input_state();
		time++;
		delay_us(2);
	}while(status != 0 && time < 20);//等待拉低
	
	if(time == 20)
		return;
	
	while(!dht_input_state());//等待拉高
	
	for(i = 0 ; i < 40; i++)
	{
		while(dht_input_state());//等待拉低
		while(!dht_input_state());//等待拉高
		delay_us(40);
		data <<= 1;
		if(dht_input_state())
			data |= 1;
		if((i + 1) % 8 == 0)//i = 7 15 23 31 39
		{
			buf[i / 8] = data;
			data = 0;
		}
	}
	dht_output_state(1);
}






