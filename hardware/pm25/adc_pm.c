#include "adc_pm.h"

void adc_pm_init(void)
{
	GPIO_InitTypeDef Gpio_Value;
	ADC_CommonInitTypeDef Adc_Common_Value;
	ADC_InitTypeDef Adc_Value;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOC��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//ʹ��ADC1��ʱ��
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_AN;//ѡ��ģ��ģʽ
	Gpio_Value.GPIO_OType = GPIO_OType_PP;//ѡ���������
	Gpio_Value.GPIO_Pin = GPIO_Pin_0;//ѡ��0�Źܽ�
	Gpio_Value.GPIO_PuPd = GPIO_PuPd_NOPULL;//ѡ��������������
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ��50MHz
	GPIO_Init(GPIOC, &Gpio_Value);//�����������ó�ʼ��GPIOC�Ĺܽ�
	
	Adc_Common_Value.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//�ر�DMA������
	Adc_Common_Value.ADC_Mode = ADC_Mode_Independent;//ѡ�񵥴�ģʽ
	Adc_Common_Value.ADC_Prescaler = ADC_Prescaler_Div8;//ѡ��8��Ƶ
	Adc_Common_Value.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;//ѡ������ת������ʱ����
	ADC_CommonInit(&Adc_Common_Value);//�����������ó�ʼ�����е�ADC
	
	Adc_Value.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��ģʽ
	Adc_Value.ADC_DataAlign = ADC_DataAlign_Right;//ѡ�������Ҷ���
	Adc_Value.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	Adc_Value.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//�ر����ⲿ��������
	Adc_Value.ADC_NbrOfConversion = 10;//ѡ��10��ͨ��
	Adc_Value.ADC_Resolution = ADC_Resolution_12b;//ѡ��12bit������λ
	Adc_Value.ADC_ScanConvMode = DISABLE;//�ر�ɨ��ģʽ
	ADC_Init(ADC1, &Adc_Value);//�����������ó�ʼ��ADC1
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_480Cycles);
	//����ADC1��ͨ��10
	ADC_Cmd(ADC1, ENABLE);//ʹ��ADC1
}

void adc_pm_start(void)
{
	ADC_SoftwareStartConv(ADC1);//����ADת��
}

void adc_pm_wait(void)
{
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//�ȴ�ADת������
	//��ʱ����
}

int get_adc_pm_value(void)
{
	return ADC_GetConversionValue(ADC1);//��ȡת��֮��Ľ��
}











