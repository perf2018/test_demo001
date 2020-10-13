#include "usart1.h"

usart1_handler handler;

void usart1_init(void)
{
	GPIO_InitTypeDef Gpio_Value;
	USART_InitTypeDef Usart_Value;
	NVIC_InitTypeDef Nvic_Value;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ͨ��RCCʹ��GPIOA��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//ͨ��RCCʹ��USART1��ʱ��
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_AF;//ѡ����ģʽ
	Gpio_Value.GPIO_OType = GPIO_OType_PP;//ѡ���������
	Gpio_Value.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;//ѡ��ܽ�
	Gpio_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;//ѡ��������������
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ��50MHz
	GPIO_Init(GPIOA, &Gpio_Value);//�����������ó�ʼ��GPIOA��Ĺܽ�
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);//ΪGPIO�ܽ�ѡ��USART1�ĸ���ģʽ
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	Usart_Value.USART_BaudRate = 115200;//���ò�����
	Usart_Value.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//�ر�Ӳ������
	Usart_Value.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//ѡ���ͺͽ���ģʽ
	Usart_Value.USART_Parity = USART_Parity_No;//ѡ��û����ż����
	Usart_Value.USART_StopBits = USART_StopBits_1;//ѡ��1λ��ֹͣλ
	Usart_Value.USART_WordLength = USART_WordLength_8b;//ѡ��8λ������λ
	USART_Init(USART1, &Usart_Value);//�����������ó�ʼ��USART1
	
	Nvic_Value.NVIC_IRQChannel = USART1_IRQn;//ѡ���жϺ�
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;//ʹ���ж�
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 2;//���������ȼ���
	Nvic_Value.NVIC_IRQChannelSubPriority = 2;//���������ȼ���
	NVIC_Init(&Nvic_Value);//�����������ó�ʼ��NVIC
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ɽ��մ����ж�
	
	USART_Cmd(USART1, ENABLE);//ʹ��USART1����
}

void usart1_send_byte(unsigned char c)
{
	USART_SendData(USART1, c);//��USART1��������
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//�ȴ����ͳɹ�
	USART_ClearFlag(USART1, USART_FLAG_TC);//�����־λ
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)//�ж��Ƿ����ɽ��մ������ж�
	{
		handler(USART_ReceiveData(USART1));//����handler�����ѽ��յ������ݴ���
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);//���USART1�Ľ��յ��жϱ�־
	}
}

void set_usart1_handler(usart1_handler h)
{
	handler = h;
}

void usart1_send_data(unsigned char *buf)
{
	for(; *buf != '\0'; buf++)
		usart1_send_byte(*buf);
}

/*
unsigned char usart1_recv_byte(void)
{
	unsigned char save = 0;
	
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)//�ж��Ƿ�������
	{
		save = USART_ReceiveData(USART1);//����USART1������
		USART_ClearFlag(USART1, USART_FLAG_RXNE);//�����־λ
	}
	
	return save;
}
*/








