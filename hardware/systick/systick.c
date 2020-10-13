#include "systick.h"

//利用系统滴答定时，编写的延时函数

static u8  fac_us=0; //us延时倍乘数			   
static u16 fac_ms=0; //ms延时倍乘数,在ucos下,代表每个节拍的ms数

/****************************************************************************
* 名    称: delay_init()
* 功    能：延时函数初始化
* 入口参数：无
* 返回参数：无
* 说    明：
****************************************************************************/
void systick_init(void)
{
 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	//为系统定时器选择时钟为	HCLK 8分频	168MHz / 8 = 21MHz
	fac_us=SYSCLK/8;
	//微妙的倍乘数 = 168 / 8 = 21
	//X * fac_us就相当于有X个微妙
	fac_ms=(u16)fac_us*1000; 
	//每个ms需要的systick时钟数(1ms = 1000us),所以fac_us*1000
	//X * fac_ms就相当于有X个毫妙
}								    

/****************************************************************************
* 名    称: void delay_us(u32 nus)
* 功    能：延时nus
* 入口参数：要延时的微妙数
* 返回参数：无
* 说    明：nus的值,不要大于798915us
****************************************************************************/
/*
通过相关手册我们了解到,备份值寄存器和当前值寄存器的值最大为16M - 1
我们的微妙级的延时函数的倍乘数为21所以16M - 1 / 21 = 798915
*/
void delay_us(u32 nus)
{
	u32 midtime;							//保存寄存器的状态
	SysTick->LOAD=nus*fac_us; //时间加载(相当于有nus个微妙)
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;	//使能系统定时器计数
	do
	{
		midtime=SysTick->CTRL;
	}
	while((midtime&0x01)&&!(midtime&(1<<16)));//等待时间到达
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}
/****************************************************************************
* 名    称: void delay_xms(u16 nms)
* 功    能：延时nms
* 入口参数：要延时的毫妙数
* 返回参数：无
* 说    明：SysTick->LOAD为24位寄存器,所以,最大延时为: nms<=0xffffff*8*1000/SYSCLK
            对168M条件下,nms<=798ms 
****************************************************************************/
void delay_xms(u16 nms)
{	 		  	  
	u32 midtime;		   
	SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;	//开始倒数
	do
	{
		midtime=SysTick->CTRL;
	}
	while((midtime&0x01)&&!(midtime&(1<<16)));	//等待时间到达
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//关闭计数器
	SysTick->VAL =0X00;       		//清空计数器
} 
/****************************************************************************
* 名    称: void delay_ms(u16 nms)
* 功    能：延时nms
* 入口参数：要延时的毫妙数
* 返回参数：无
* 说    明：nms:0~65535
****************************************************************************/
void delay_ms(u16 nms)
{	 	 
	u8 repeat=nms/540;	//这里用540,是考虑到某些客户可能超频使用,
						          //比如超频到248M的时候,delay_xms最大只能延时541ms左右了
	u16 remain=nms%540;
	while(repeat)
	{
		delay_xms(540);
		repeat--;
	}
	if(remain)delay_xms(remain);
} 

			 
