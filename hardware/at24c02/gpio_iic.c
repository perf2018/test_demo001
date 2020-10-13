#include "gpio_iic.h"

/*
��GPIO�ķ�ʽģ��IIC�������ַ���,��Ӳ�����ӵ�GPIO�й�
�ҵ��豸�ӵ���ͬ��GPIO��,��������Ҫ������Ӧ��GPIO
��Ϊ����������EEPROM��ʵ��,������Ҫ�鿴Ӳ��ԭ��ͼ��EEPROM�������ĸ�
�ܽ���
*/
//���´�����Ӳ����صģ���ֲʱ����Ҫ�޸�
GPIO_InitTypeDef  GPIO_InitForSCL;
GPIO_InitTypeDef  GPIO_InitForSDAOut;
GPIO_InitTypeDef  GPIO_InitForSDAIn;

#define IIC_SCL					PBOut(8)
#define IIC_SDA					PBOut(9)
#define IIC_SDA_STATUS 	PBIn(9)

void IIC_Init(void)
{			
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	//B8 scl
  GPIO_InitForSCL.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitForSCL.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitForSCL.GPIO_OType = GPIO_OType_PP;
  GPIO_InitForSCL.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitForSCL.GPIO_PuPd = GPIO_PuPd_UP;
	
	//B9 sda out
  GPIO_InitForSDAOut.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitForSDAOut.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitForSDAOut.GPIO_OType = GPIO_OType_PP;
  GPIO_InitForSDAOut.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitForSDAOut.GPIO_PuPd = GPIO_PuPd_UP;
	
  //B9 sda in
  GPIO_InitForSDAIn.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitForSDAIn.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitForSDAIn.GPIO_OType = GPIO_OType_PP;
  GPIO_InitForSDAIn.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitForSDAIn.GPIO_PuPd = GPIO_PuPd_UP;
	
  GPIO_Init(GPIOB, &GPIO_InitForSDAOut);
  GPIO_Init(GPIOB, &GPIO_InitForSCL);
	
	IIC_SCL = 1;
	IIC_SDA = 1;
}

void IIC_Sda_In(void)
{
	GPIO_Init(GPIOB, &GPIO_InitForSDAIn);
}

void IIC_Sda_Out(void)
{
	GPIO_Init(GPIOB, &GPIO_InitForSDAOut);
}
//���ϴ�����Ӳ����صģ���ֲʱ����Ҫ�޸�

//���´���Ӳ���޹أ�ֻ��iicЭ���й�
void IIC_Start(void)
{
	IIC_Sda_Out();
	IIC_SDA=1;	  	  
	IIC_SCL=1;  
	delay_us(2);
 	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=0;
}	  

void IIC_Stop(void)
{
	IIC_Sda_Out();
	IIC_SCL=0;
	IIC_SDA=0;
 	delay_us(2);
	IIC_SCL=1; 
	delay_us(1);
	IIC_SDA=1;
	delay_us(2);							   	
}

u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	IIC_Sda_In();
	IIC_SCL = 0;
	delay_us(1);	   
	IIC_SCL=1;
	delay_us(1);	 
	while(IIC_SDA_STATUS) {
		ucErrTime++;
		if(ucErrTime>250) {
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0; 	   
	return 0;  
} 

void IIC_Ack(void)
{
	IIC_SCL=0;
	IIC_Sda_Out();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
    
void IIC_NAck(void)
{
	IIC_SCL=0;
	IIC_Sda_Out();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     

void IIC_Send_Byte(u8 txd)
{                        
  u8 t;
	
	IIC_Sda_Out();    

  for (t = 0;t < 8; t++) {  
		IIC_SCL = 0;
		delay_us(1);	
    IIC_SDA = (txd & 0x80) >> 7;
    txd <<= 1; 	  
		delay_us(1);   
		IIC_SCL=1;
		delay_us(2); 
   }	
	IIC_SCL = 0;
} 	    

u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	IIC_Sda_In();
  for(i=0;i<8;i++ ) {
    IIC_SCL=0; 
    delay_us(2);
		IIC_SCL=1;
		delay_us(2);
    receive<<=1;
    if(IIC_SDA_STATUS)
			receive |= 1;   
  }					 
	IIC_SCL = 0;
  if (!ack)
		IIC_NAck();
  else
		IIC_Ack(); 
  return receive;
}
