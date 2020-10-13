#include "but_eint.h"

eint_handler handler0, handler1, handler2, handler3;

void eint_init(void)
{
	GPIO_InitTypeDef Gpio_Value;
	NVIC_InitTypeDef Nvic_Value;
	EXTI_InitTypeDef Exti_Value;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOE, ENABLE);
	//ͨ��RCCʹ��GPIOF��GPIOE��ʱ��(����ʹ��PF987 PE6)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//ͨ��RCCʹ��SYSCFG��ʱ��(��Ҫͨ��syscfg��ѡ�񴥷��ⲿ�жϵĹܽ�)
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IN;//ѡ������ģʽ
	Gpio_Value.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_7;//ѡ��GPIO�ܽ�
	Gpio_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;//ѡ��������������
	GPIO_Init(GPIOF, &Gpio_Value);//ͨ���������ó�ʼ��GPIOF��Ĺܽ�
	
	Gpio_Value.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOE, &Gpio_Value);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource9); 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource8); 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource7); 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);
	//ͨ��SYSCFGѡ�񴥷��ⲿ�жϵĹܽ�

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���������ȼ��������ȼ�����ռ����
	Nvic_Value.NVIC_IRQChannel = EXTI9_5_IRQn;//ѡ���жϺ�
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж�
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 2;//���������ȼ�����
	Nvic_Value.NVIC_IRQChannelSubPriority = 2;//���������ȼ�����
	NVIC_Init(&Nvic_Value);//�����������ó�ʼ��NVIC������
	
	Exti_Value.EXTI_Line = EXTI_Line9 | EXTI_Line8 | EXTI_Line7 | EXTI_Line6;//ѡ���ⲿ�жϺ�
	Exti_Value.EXTI_LineCmd = ENABLE;//ʹ���ⲿ�ж�
	Exti_Value.EXTI_Mode = EXTI_Mode_Interrupt;//ѡ���ж�ģʽ
	Exti_Value.EXTI_Trigger = EXTI_Trigger_Falling;//ѡ���½��ش���
	EXTI_Init(&Exti_Value);//�����������ó�ʼ��EXTI
}

void EXTI9_5_IRQHandler(void)//�жϴ�����
{
	if(EXTI_GetITStatus(EXTI_Line9) == SET)//���EXTI9�������ж�
	{
		handler0();//���ô�����
		EXTI_ClearITPendingBit(EXTI_Line9);//����жϱ�־λ
	}
	if(EXTI_GetITStatus(EXTI_Line8) == SET)
	{
		handler1();
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
	if(EXTI_GetITStatus(EXTI_Line7) == SET)
	{
		handler2();
		EXTI_ClearITPendingBit(EXTI_Line7);
	}
	if(EXTI_GetITStatus(EXTI_Line6) == SET)
	{
		handler3();
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}

void set_eint_handler(eint_handler h0, eint_handler h1, eint_handler h2, eint_handler h3)
{
	handler0 = h0;//ת�溯����ַ
	handler1 = h1;
	handler2 = h2;
	handler3 = h3;
}








