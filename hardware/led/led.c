#include "led.h"

void led_init(void)
{
	GPIO_InitTypeDef Led_Value;//����ṹ�����͵ı���
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��GPIOE���GPIOG���ʱ��	
	
	Led_Value.GPIO_Mode = GPIO_Mode_OUT;//ѡ�����ģʽ
	Led_Value.GPIO_OType = GPIO_OType_PP;//ѡ���������
	Led_Value.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;//ѡ��ܽ�3�͹ܽ�4
	Led_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;//ѡ��������������
	Led_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ��50MHz������ٶ�
	GPIO_Init(GPIOE, &Led_Value);//�����������ó�ʼ��GPIOE��Ĺܽ�

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







