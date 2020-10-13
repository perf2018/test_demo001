#include "systick.h"

//����ϵͳ�δ�ʱ����д����ʱ����

static u8  fac_us=0; //us��ʱ������			   
static u16 fac_ms=0; //ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��

/****************************************************************************
* ��    ��: delay_init()
* ��    �ܣ���ʱ������ʼ��
* ��ڲ�������
* ���ز�������
* ˵    ����
****************************************************************************/
void systick_init(void)
{
 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	//Ϊϵͳ��ʱ��ѡ��ʱ��Ϊ	HCLK 8��Ƶ	168MHz / 8 = 21MHz
	fac_us=SYSCLK/8;
	//΢��ı����� = 168 / 8 = 21
	//X * fac_us���൱����X��΢��
	fac_ms=(u16)fac_us*1000; 
	//ÿ��ms��Ҫ��systickʱ����(1ms = 1000us),����fac_us*1000
	//X * fac_ms���൱����X������
}								    

/****************************************************************************
* ��    ��: void delay_us(u32 nus)
* ��    �ܣ���ʱnus
* ��ڲ�����Ҫ��ʱ��΢����
* ���ز�������
* ˵    ����nus��ֵ,��Ҫ����798915us
****************************************************************************/
/*
ͨ������ֲ������˽⵽,����ֵ�Ĵ����͵�ǰֵ�Ĵ�����ֵ���Ϊ16M - 1
���ǵ�΢�����ʱ�����ı�����Ϊ21����16M - 1 / 21 = 798915
*/
void delay_us(u32 nus)
{
	u32 midtime;							//����Ĵ�����״̬
	SysTick->LOAD=nus*fac_us; //ʱ�����(�൱����nus��΢��)
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;	//ʹ��ϵͳ��ʱ������
	do
	{
		midtime=SysTick->CTRL;
	}
	while((midtime&0x01)&&!(midtime&(1<<16)));//�ȴ�ʱ�䵽��
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
}
/****************************************************************************
* ��    ��: void delay_xms(u16 nms)
* ��    �ܣ���ʱnms
* ��ڲ�����Ҫ��ʱ�ĺ�����
* ���ز�������
* ˵    ����SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ: nms<=0xffffff*8*1000/SYSCLK
            ��168M������,nms<=798ms 
****************************************************************************/
void delay_xms(u16 nms)
{	 		  	  
	u32 midtime;		   
	SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;	//��ʼ����
	do
	{
		midtime=SysTick->CTRL;
	}
	while((midtime&0x01)&&!(midtime&(1<<16)));	//�ȴ�ʱ�䵽��
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//�رռ�����
	SysTick->VAL =0X00;       		//��ռ�����
} 
/****************************************************************************
* ��    ��: void delay_ms(u16 nms)
* ��    �ܣ���ʱnms
* ��ڲ�����Ҫ��ʱ�ĺ�����
* ���ز�������
* ˵    ����nms:0~65535
****************************************************************************/
void delay_ms(u16 nms)
{	 	 
	u8 repeat=nms/540;	//������540,�ǿ��ǵ�ĳЩ�ͻ����ܳ�Ƶʹ��,
						          //���糬Ƶ��248M��ʱ��,delay_xms���ֻ����ʱ541ms������
	u16 remain=nms%540;
	while(repeat)
	{
		delay_xms(540);
		repeat--;
	}
	if(remain)delay_xms(remain);
} 

			 
