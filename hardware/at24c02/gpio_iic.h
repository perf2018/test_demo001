#ifndef __MYIIC_H
#define __MYIIC_H

#include "hardware.h"


typedef unsigned char u8;

/////////////// 	
   	   		   
////IO????
//#define SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9????
//#define SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9????
////IO????	 
//#define IIC_SCL    PBOut(8) //SCL
//#define IIC_SDA    PBOut(9) //SDA	 
//#define READ_SDA   PBIn(9)  //??SDA 

//用GPIO的方式来模拟IIC协议
void IIC_Init(void);                //初始化IIC使用的GPIO				 
void IIC_Start(void);				//产生开始信号
void IIC_Stop(void);	  			//产生结束信号
void IIC_Send_Byte(u8 txd);			//利用IIC总线发送数据(一位一位的发送)
u8 IIC_Read_Byte(unsigned char ack);//利用IIC总线接收数据
u8 IIC_Wait_Ack(void); 				//等待ACK
void IIC_Ack(void);					//产生ACK
void IIC_NAck(void);				//不产生ACK

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);//利用IIC总线写1个字节
//daddr	<从>设备的地址
//addr	EEPROM内部的地址
//data	数据
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);//利用IIC总线读1个字节
#endif
















