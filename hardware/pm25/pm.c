#include "pm.h"

void pm_init(void)
{
	GPIO_InitTypeDef Gpio_Value;
	
	adc_pm_init();
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_OUT;//选择模拟模式
	Gpio_Value.GPIO_OType = GPIO_OType_PP;//选择推挽输出
	Gpio_Value.GPIO_Pin = GPIO_Pin_13;//选择0号管脚
	Gpio_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;//选择无上拉无下拉
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择50MHz
	GPIO_Init(GPIOC, &Gpio_Value);//按照上述配置初始化GPIOC的管脚
	
	PCOut(13) = 1;
}

int get_pm_value(void)
{
	int value;
	
	PCOut(13) = 0;
	delay_us(280);
	adc_pm_start();
	adc_pm_wait();
	value = get_adc_pm_value();
	delay_us(40);
	PCOut(13) = 1;
	delay_us(9680);
	
	return value;
}












