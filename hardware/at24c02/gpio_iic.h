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

//��GPIO�ķ�ʽ��ģ��IICЭ��
void IIC_Init(void);                //��ʼ��IICʹ�õ�GPIO				 
void IIC_Start(void);				//������ʼ�ź�
void IIC_Stop(void);	  			//���������ź�
void IIC_Send_Byte(u8 txd);			//����IIC���߷�������(һλһλ�ķ���)
u8 IIC_Read_Byte(unsigned char ack);//����IIC���߽�������
u8 IIC_Wait_Ack(void); 				//�ȴ�ACK
void IIC_Ack(void);					//����ACK
void IIC_NAck(void);				//������ACK

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);//����IIC����д1���ֽ�
//daddr	<��>�豸�ĵ�ַ
//addr	EEPROM�ڲ��ĵ�ַ
//data	����
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);//����IIC���߶�1���ֽ�
#endif
















