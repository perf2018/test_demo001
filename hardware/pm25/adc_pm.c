#include "adc_pm.h"

void adc_pm_init(void)
{
	GPIO_InitTypeDef Gpio_Value;
	ADC_CommonInitTypeDef Adc_Common_Value;
	ADC_InitTypeDef Adc_Value;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC组时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//使能ADC1的时钟
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_AN;//选择模拟模式
	Gpio_Value.GPIO_OType = GPIO_OType_PP;//选择推挽输出
	Gpio_Value.GPIO_Pin = GPIO_Pin_0;//选择0号管脚
	Gpio_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;//选择无上拉无下拉
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择50MHz
	GPIO_Init(GPIOC, &Gpio_Value);//按照上述配置初始化GPIOC的管脚
	
	Adc_Common_Value.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//关闭DMA的请求
	Adc_Common_Value.ADC_Mode = ADC_Mode_Independent;//选择单次模式
	Adc_Common_Value.ADC_Prescaler = ADC_Prescaler_Div8;//选择8分频
	Adc_Common_Value.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;//选择两次转换的延时周期
	ADC_CommonInit(&Adc_Common_Value);//按照上述配置初始化所有的ADC
	
	Adc_Value.ADC_ContinuousConvMode = DISABLE;//关闭连续转换模式
	Adc_Value.ADC_DataAlign = ADC_DataAlign_Right;//选择数据右对齐
	Adc_Value.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	Adc_Value.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//关闭了外部触发请求
	Adc_Value.ADC_NbrOfConversion = 10;//选择10号通道
	Adc_Value.ADC_Resolution = ADC_Resolution_12b;//选择12bit的量化位
	Adc_Value.ADC_ScanConvMode = DISABLE;//关闭扫描模式
	ADC_Init(ADC1, &Adc_Value);//按照上述配置初始化ADC1
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_480Cycles);
	//配置ADC1的通道10
	ADC_Cmd(ADC1, ENABLE);//使能ADC1
}

void adc_pm_start(void)
{
	ADC_SoftwareStartConv(ADC1);//开启AD转换
}

void adc_pm_wait(void)
{
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//等待AD转换结束
	//超时处理
}

int get_adc_pm_value(void)
{
	return ADC_GetConversionValue(ADC1);//获取转换之后的结果
}











