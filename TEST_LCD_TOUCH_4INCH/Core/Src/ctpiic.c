#include "ctpiic.h"
//#include "delay.h"	 
#include "main.h"

/*****************************************************************************
 * @name       :void CTP_Delay(void)
 * @date       :2020-05-13 
 * @function   :Delay in controlling IIC speed
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void CTP_Delay(void)
{
	delay_us(1);
//	volatile u32 i;
//    for(i=0; i<300; i++) { __NOP(); }
} 


// Hàm delay micro-giây chính xác dùng SysTick
void delay_us(u32 nus)
{       
// Với chip H7 chạy 400-480MHz, hệ số nhân khoảng 200-240 là đẹp cho 1us
    // Nếu I2C chậm quá hoặc nhanh quá sếp chỉnh số này
    u32 i = nus * 200; 
    
    while(i--)
    {
        __NOP(); // Tốn 1 chu kỳ máy, không làm gì cả
    }
}
/*****************************************************************************
 * @name       :void CTP_IIC_Init(void)
 * @date       :2020-05-13 
 * @function   :Initialize IIC
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void CTP_IIC_Init(void)
{	
//		GPIO_InitTypeDef GPIO_Initure;

 //   __HAL_RCC_GPIOC_CLK_ENABLE();			//ʹ��GPIOCʱ
//		__HAL_RCC_GPIOA_CLK_ENABLE();			//ʹGPIOAʱ
    
 //   GPIO_Initure.Pin=GPIO_PIN_6;            //PC6
 //   GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //
 //   GPIO_Initure.Pull=GPIO_PULLUP;          //
 //   GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //����
 //   HAL_GPIO_Init(GPIOC,&GPIO_Initure);     //ʼPC6
	
 //   GPIO_Initure.Pin=GPIO_PIN_3;            //PA3
 //   HAL_GPIO_Init(GPIOA,&GPIO_Initure);     //ʼPA3

		CTP_IIC_SCL(1);
		CTP_IIC_SDA(1);
}

/*****************************************************************************
 * @name       :void CTP_IIC_Start(void)
 * @date       :2020-05-13 
 * @function   :Generating IIC starting signal
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void CTP_IIC_Start(void)
{
	CTP_SDA_OUT();     //sda�����
	CTP_IIC_SDA(1);	  	  
	CTP_IIC_SCL(1);
	CTP_Delay();
 	CTP_IIC_SDA(0);//START:when CLK is high,DATA change form high to low 
	CTP_Delay();
	CTP_IIC_SCL(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	

/*****************************************************************************
 * @name       :void CTP_IIC_Stop(void)
 * @date       :2020-05-13 
 * @function   :Generating IIC stop signal
 * @parameters :None
 * @retvalue   :None
******************************************************************************/   
void CTP_IIC_Stop(void)
{ 
	CTP_SDA_OUT();//sda�����
	CTP_IIC_SCL(0);
	CTP_IIC_SDA(0);
	CTP_Delay();
	CTP_IIC_SCL(1);
	CTP_Delay();
	CTP_IIC_SDA(1);//STOP:when CLK is high DATA change form low to high 
}

/*****************************************************************************
 * @name       :u8 CTP_IIC_Wait_Ack(void)
 * @date       :2020-05-13 
 * @function   :Wait for the response signal
 * @parameters :None
 * @retvalue   :0-receive response signal successfully
								1-receive response signal unsuccessfully
******************************************************************************/ 
u8 CTP_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	CTP_SDA_IN();      //SDA����Ϊ����  
	CTP_IIC_SDA(1);CTP_Delay();	   
	CTP_IIC_SCL(1);CTP_Delay();	 
	while(CTP_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			CTP_IIC_Stop();
			return 1;
		} 
	}
	CTP_IIC_SCL(0);//ʱ�����0 	   
	return 0;  
} 

/*****************************************************************************
 * @name       :void CTP_IIC_Ack(void)
 * @date       :2020-05-13 
 * @function   :Generate ACK response signal
 * @parameters :None
 * @retvalue   :None
******************************************************************************/ 
void CTP_IIC_Ack(void)
{
	CTP_IIC_SCL(0);
	CTP_SDA_OUT();
	CTP_IIC_SDA(0);
	CTP_Delay();
	CTP_IIC_SCL(1);
	CTP_Delay();
	CTP_IIC_SCL(0);
}

/*****************************************************************************
 * @name       :void CTP_IIC_NAck(void)
 * @date       :2020-05-13 
 * @function   :Don't generate ACK response signal
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	    
void CTP_IIC_NAck(void)
{
	CTP_IIC_SCL(0);
	CTP_SDA_OUT();
	CTP_IIC_SDA(1);
	CTP_Delay();
	CTP_IIC_SCL(1);
	CTP_Delay();
	CTP_IIC_SCL(0);
}	

/*****************************************************************************
 * @name       :void CTP_IIC_Send_Byte(u8 txd)
 * @date       :2020-05-13 
 * @function   :send a byte data by IIC bus
 * @parameters :txd:Data to be sent
 * @retvalue   :None
******************************************************************************/					 				     		  
void CTP_IIC_Send_Byte(u8 txd)
{                        
  u8 t;   
	CTP_SDA_OUT(); 	    
  CTP_IIC_SCL(0);//����ʱ�ӿ�ʼ���ݴ���
  for(t=0;t<8;t++)
  {              
    CTP_IIC_SDA((txd&0x80)>>7);
    txd<<=1; 	      
	CTP_IIC_SCL(1);
	CTP_Delay();
	CTP_IIC_SCL(0);	
	CTP_Delay();
  }	 
} 	

/*****************************************************************************
 * @name       :u8 CTP_IIC_Read_Byte(unsigned char ack)
 * @date       :2020-05-13 
 * @function   :read a byte data by IIC bus
 * @parameters :ack:0-send nACK
									  1-send ACK
 * @retvalue   :Data to be read
******************************************************************************/	    
u8 CTP_IIC_Read_Byte(unsigned char ack)
{
	u8 i,receive=0;
 	CTP_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
		CTP_IIC_SCL(0); 	    	   
		delay_us(3);
		CTP_IIC_SCL(1);  
		receive<<=1;
		if(CTP_READ_SDA)receive++;   
	}	  				 
	if (!ack)CTP_IIC_NAck();//����nACK
	else CTP_IIC_Ack(); //����ACK   
 	return receive;
}




























