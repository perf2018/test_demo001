#include "usart1.h"

usart1_handler handler;

void usart1_init(void)
{
	GPIO_InitTypeDef Gpio_Value;
	USART_InitTypeDef Usart_Value;
	NVIC_InitTypeDef Nvic_Value;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//通过RCC使能GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//通过RCC使能USART1的时钟
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_AF;//选择复用模式
	Gpio_Value.GPIO_OType = GPIO_OType_PP;//选择推挽输出
	Gpio_Value.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;//选择管脚
	Gpio_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;//选择无上拉无下拉
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择50MHz
	GPIO_Init(GPIOA, &Gpio_Value);//按照上述配置初始化GPIOA组的管脚
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);//为GPIO管脚选择USART1的复用模式
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	Usart_Value.USART_BaudRate = 115200;//配置波特率
	Usart_Value.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//关闭硬件流控
	Usart_Value.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//选择发送和接收模式
	Usart_Value.USART_Parity = USART_Parity_No;//选择没有奇偶检验
	Usart_Value.USART_StopBits = USART_StopBits_1;//选择1位的停止位
	Usart_Value.USART_WordLength = USART_WordLength_8b;//选择8位的数据位
	USART_Init(USART1, &Usart_Value);//按照上述配置初始化USART1
	
	Nvic_Value.NVIC_IRQChannel = USART1_IRQn;//选择中断号
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;//使能中断
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 2;//配置组优先级别
	Nvic_Value.NVIC_IRQChannelSubPriority = 2;//配置子优先级别
	NVIC_Init(&Nvic_Value);//按照上述配置初始化NVIC
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//配置由接收触发中断
	
	USART_Cmd(USART1, ENABLE);//使能USART1功能
}

void usart1_send_byte(unsigned char c)
{
	USART_SendData(USART1, c);//给USART1发送数据
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//等待发送成功
	USART_ClearFlag(USART1, USART_FLAG_TC);//清除标志位
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)//判断是否是由接收触发的中断
	{
		handler(USART_ReceiveData(USART1));//调用handler函数把接收到的数据传参
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);//清除USART1的接收的中断标志
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
	
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)//判断是否有数据
	{
		save = USART_ReceiveData(USART1);//接收USART1的数据
		USART_ClearFlag(USART1, USART_FLAG_RXNE);//清除标志位
	}
	
	return save;
}
*/








