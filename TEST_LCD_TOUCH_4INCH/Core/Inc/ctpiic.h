#ifndef __CTPIIC_H
#define __CTPIIC_H
//#include "sys.h"
#include "main.h"	    
  	   		   
//IIC IO��������
#define CTP_SDA_IN()  {CTP_SDA_GPIO_Port->MODER&=~(3<<(3*2));CTP_SDA_GPIO_Port->MODER|=0<<3*2;}
#define CTP_SDA_OUT() {CTP_SDA_GPIO_Port->MODER&=~(3<<(3*2));CTP_SDA_GPIO_Port->MODER|=1<<3*2;}

//IO��������	 
#define CTP_IIC_SCL(n)    (n?HAL_GPIO_WritePin(CTP_SCL_GPIO_Port,GPIO_PIN_6,GPIO_PIN_SET):HAL_GPIO_WritePin(CTP_SCL_GPIO_Port,GPIO_PIN_6,GPIO_PIN_RESET))	//SCL     
#define CTP_IIC_SDA(n)    (n?HAL_GPIO_WritePin(CTP_SDA_GPIO_Port,GPIO_PIN_3,GPIO_PIN_SET):HAL_GPIO_WritePin(CTP_SDA_GPIO_Port,GPIO_PIN_3,GPIO_PIN_RESET))  			//SDA	 
#define CTP_READ_SDA       HAL_GPIO_ReadPin(CTP_SDA_GPIO_Port,GPIO_PIN_3)   			//SDA 

//IIC���в�������
void CTP_IIC_Init(void);                	//��ʼ��IIC��IO��				 
void CTP_IIC_Start(void);				//����IIC��ʼ�ź�
void CTP_IIC_Stop(void);	  				//����IICֹͣ�ź�
void CTP_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 CTP_IIC_Read_Byte(unsigned char ack);	//IIC��ȡһ���ֽ�
u8 CTP_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void CTP_IIC_Ack(void);					//IIC����ACK�ź�
void CTP_IIC_NAck(void);					//IIC������ACK�ź�
void delay_us(u32 us);                    //����

#endif







