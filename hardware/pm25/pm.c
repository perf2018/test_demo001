#include "pm.h"

void pm_init(void)
{
	GPIO_InitTypeDef Gpio_Value;
	
	adc_pm_init();
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_OUT;//ѡ��ģ��ģʽ
	Gpio_Value.GPIO_OType = GPIO_OType_PP;//ѡ���������
	Gpio_Value.GPIO_Pin = GPIO_Pin_13;//ѡ��0�Źܽ�
	Gpio_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;//ѡ��������������
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ��50MHz
	GPIO_Init(GPIOC, &Gpio_Value);//�����������ó�ʼ��GPIOC�Ĺܽ�
	
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












