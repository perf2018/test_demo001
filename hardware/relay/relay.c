#include "relay.h"

void relay_init(void)
{
	GPIO_InitTypeDef relay_Value;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOG, ENABLE);

	relay_Value.GPIO_Mode = GPIO_Mode_OUT;//���Ƴ����ģʽ
	relay_Value.GPIO_OType = GPIO_OType_PP;//���Ƴ��������
	relay_Value.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;//ѡ��ܽ�6�͹ܽ�7
	relay_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;//���Ƴ�������������
	relay_Value.GPIO_Speed = GPIO_Speed_50MHz;//���Ƴ�50MHz
	GPIO_Init(GPIOB, &relay_Value);//�����������ó�ʼ��GPIOB��Ĺܽ�
	
	PBOut(6) = 0;
	PBOut(7) = 0;
	
	relay_Value.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOG, &relay_Value);
	
	PGOut(7) = 0;
}

void relay_on(int nu)
{
	switch(nu)
	{
		case 0 : PBOut(6) = 1; break;
		case 1 : PBOut(7) = 1; break;
		case 2 : PGOut(7) = 1; break;
	}
}

void relay_off(int nu)
{
	switch(nu)
	{
		case 0 : PBOut(6) = 0; break;
		case 1 : PBOut(7) = 0; break;
		case 2 : PGOut(7) = 0; break;
	}	
}


int get_relay_status(int relay_no)
{
	int relay_staus;
	switch(relay_no)
	{
		case 0 : relay_staus = GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_6); break;
		case 1 : relay_staus = GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_7); break;
		case 2 : relay_staus = GPIO_ReadOutputDataBit(GPIOG,GPIO_Pin_7); break;
	}	
	return relay_staus;
}












