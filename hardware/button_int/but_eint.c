#include "but_eint.h"

eint_handler handler0, handler1, handler2, handler3;

void eint_init(void)
{
	GPIO_InitTypeDef Gpio_Value;
	NVIC_InitTypeDef Nvic_Value;
	EXTI_InitTypeDef Exti_Value;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOE, ENABLE);
	//通过RCC使能GPIOF和GPIOE的时钟(按键使用PF987 PE6)
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//通过RCC使能SYSCFG的时钟(需要通过syscfg来选择触发外部中断的管脚)
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IN;//选择输入模式
	Gpio_Value.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_7;//选择GPIO管脚
	Gpio_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;//选择无上拉无下拉
	GPIO_Init(GPIOF, &Gpio_Value);//通过上述配置初始化GPIOF组的管脚
	
	Gpio_Value.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOE, &Gpio_Value);
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource9); 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource8); 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource7); 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource6);
	//通过SYSCFG选择触发外部中断的管脚

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置组优先级和子优先级的所占比例
	Nvic_Value.NVIC_IRQChannel = EXTI9_5_IRQn;//选择中断号
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;//使能中断
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 2;//设置组优先级级别
	Nvic_Value.NVIC_IRQChannelSubPriority = 2;//设置子优先级级别
	NVIC_Init(&Nvic_Value);//按照上述配置初始化NVIC控制器
	
	Exti_Value.EXTI_Line = EXTI_Line9 | EXTI_Line8 | EXTI_Line7 | EXTI_Line6;//选择外部中断号
	Exti_Value.EXTI_LineCmd = ENABLE;//使能外部中断
	Exti_Value.EXTI_Mode = EXTI_Mode_Interrupt;//选择中断模式
	Exti_Value.EXTI_Trigger = EXTI_Trigger_Falling;//选择下降沿触发
	EXTI_Init(&Exti_Value);//按照上述配置初始化EXTI
}

void EXTI9_5_IRQHandler(void)//中断处理函数
{
	if(EXTI_GetITStatus(EXTI_Line9) == SET)//如果EXTI9触发的中断
	{
		handler0();//调用处理函数
		EXTI_ClearITPendingBit(EXTI_Line9);//清除中断标志位
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
	handler0 = h0;//转存函数地址
	handler1 = h1;
	handler2 = h2;
	handler3 = h3;
}








