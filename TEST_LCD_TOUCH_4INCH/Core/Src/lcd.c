/****************************************************************************************************
//=========================================��Դ����================================================//
//     LCDģ��                STM32��Ƭ��
//      VCC          ��        DC5V/3.3V      //��Դ
//      GND          ��          GND          //��Դ��
//=======================================Һ���������߽���==========================================//
//��ģ��Ĭ��������������ΪSPI����
//     LCDģ��                STM32��Ƭ��    
//    SDI(MOSI)      ��          PB15         //Һ����SPI��������д�ź�
//    SDO(MISO)      ��          PB14         //Һ����SPI�������ݶ��źţ��������Ҫ�������Բ�����
//=======================================Һ���������߽���==========================================//
//     LCDģ�� 					      STM32��Ƭ�� 
//       LED         ��          PD6          //Һ������������źţ��������Ҫ���ƣ���5V��3.3V
//       SCK         ��          PB13         //Һ����SPI����ʱ���ź�
//     LCD_RS        ��          PD5          //Һ��������/��������ź�
//     LCD_RST       ��          PD12         //Һ������λ�����ź�
//     LCD_CS        ��          PD11         //Һ����Ƭѡ�����ź�
//=========================================������������=========================================//
//���ģ�鲻���������ܻ��ߴ��д������ܣ����ǲ���Ҫ�������ܣ�����Ҫ���д���������
//	   LCDģ��                STM32��Ƭ�� 
//     CTP_INT       ��          PH11         //���ݴ������ж��ź�
//     CTP_SDA       ��          PI3          //���ݴ�����IIC�����ź�
//     CTP_RST       ��          PI8          //���ݴ�������λ�ź�
//     CTP_SCL       ��          PH6          //���ݴ�����IICʱ���ź�
**************************************************************************************************/	
#include "lcd.h"
#include "stdlib.h"
//#include "delay.h"	 
#include "spi.h"
#include "pic.h"
#include "core_cm7.h"

_lcd_dev lcddev;

//������ɫ,������ɫ
u16 POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
u16 DeviceCode;	 

/*****************************************************************************
 * @name       :void LCD_WR_REG(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit command to the LCD screen
 * @parameters :data:Command value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_REG(u8 data)
{ 
   LCD_CS_CLR;     
	 LCD_RS_CLR;	  
   SPI2_ReadWriteByte(data);
   LCD_CS_SET;	
}

/*****************************************************************************
 * @name       :void LCD_WR_DATA(u8 data)
 * @date       :2018-08-09 
 * @function   :Write an 8-bit data to the LCD screen
 * @parameters :data:data value to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WR_DATA(u8 data)
{
   LCD_CS_CLR;
	 LCD_RS_SET;
   SPI2_ReadWriteByte(data);
   LCD_CS_SET;
}

u8 LCD_RD_DATA(void)
{
	 u8 data;
	 LCD_CS_CLR;
	 LCD_RS_SET;
	 //SPI2_SetSpeed(SPI_BAUDRATEPRESCALER_32);
	 data = SPI2_ReadWriteByte(0xFF);
	 //SPI2_SetSpeed(SPI_BAUDRATEPRESCALER_8);
	 LCD_CS_SET;
	 return data;
}

/*****************************************************************************
 * @name       :void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
 * @date       :2018-08-09 
 * @function   :Write data into registers
 * @parameters :LCD_Reg:Register address
                LCD_RegValue:Data to be written
 * @retvalue   :None
******************************************************************************/
void LCD_WriteReg(u8 LCD_Reg, u16 LCD_RegValue)
{	
	LCD_WR_REG(LCD_Reg);  
	LCD_WR_DATA(LCD_RegValue);	    		 
}	   

u8 LCD_ReadReg(u8 LCD_Reg)
{
	LCD_WR_REG(LCD_Reg);
  return LCD_RD_DATA();
}

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09 
 * @function   :Write GRAM
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}	 


void LCD_ReadRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.rramcmd);
}	 

/*****************************************************************************
 * @name       :void Lcd_WriteData_16Bit(u16 Data)
 * @date       :2018-08-09 
 * @function   :Write an 16-bit command to the LCD screen
 * @parameters :Data:Data to be written
 * @retvalue   :None
******************************************************************************/	 
void Lcd_WriteData_16Bit(u16 Data)
{	
   LCD_CS_CLR;
   LCD_RS_SET;  
   SPI2_ReadWriteByte(Data>>8);
	 SPI2_ReadWriteByte(Data);
   LCD_CS_SET;
}

u16 Lcd_ReadData_16Bit(void)
{
	u16 r,g;
	LCD_CS_CLR;
	LCD_RS_CLR;	  
	SPI2_ReadWriteByte(lcddev.rramcmd);
	//SPI2_SetSpeed(SPI_BAUDRATEPRESCALER_32);
	LCD_RS_SET;
	SPI2_ReadWriteByte(0xFF);
	r = SPI2_ReadWriteByte(0xFF);
	g = SPI2_ReadWriteByte(0xFF);
	//SPI2_SetSpeed(SPI_BAUDRATEPRESCALER_8);
	LCD_CS_SET;
	r<<=8;
	r|=g;
	return r;
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(u16 x,u16 y)
 * @date       :2018-08-09 
 * @function   :Write a pixel data at a specified location
 * @parameters :x:the x coordinate of the pixel
                y:the y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/	
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_SetCursor(x,y);//���ù��λ�� 
	Lcd_WriteData_16Bit(POINT_COLOR); 
}

u16 LCD_ReadPoint(u16 x,u16 y)
{
	u16 color;
	LCD_SetCursor(x,y);//���ù��λ�� 
	color = Lcd_ReadData_16Bit();
	return color;
}

/*****************************************************************************
 * @name       :void LCD_Clear(u16 Color)
 * @date       :2018-08-09 
 * @function   :Full screen filled LCD screen
 * @parameters :color:Filled color
 * @retvalue   :None
******************************************************************************/	
void LCD_Clear(u16 Color)
{
	/*
  unsigned int i,m;  
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);   
	LCD_CS_CLR;
	LCD_RS_SET;
	for(i=0;i<lcddev.height;i++)
	{
    for(m=0;m<lcddev.width;m++)
    {	
		SPI2_ReadWriteByte(Color>>8);
	 	SPI2_ReadWriteByte(Color);
		}
	}
	 LCD_CS_SET;
	 */
	u32 index = 0;
    u32 total_point = lcddev.width * lcddev.height;
    
    // 1. Set vùng vẽ toàn màn hình
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
    
    LCD_CS_CLR;
    LCD_RS_SET;

    // 2. TẠO BUFFER (XE RÙA)
    // Mẹo: Dùng mảng static để đỡ tốn Stack, kích thước đủ cho 1 dòng ngang (Max 800px)
    // Mỗi pixel 2 byte (High + Low)
    static uint8_t line_buff[480 * 40 * 2]; // Tối đa 480px ngang (4 inch), 40 dòng
    
    // Tính toán màu 1 lần rồi dùng lại (Tiết kiệm CPU)
    uint8_t color_high = Color >> 8;
    uint8_t color_low = Color & 0xFF;
    
    // Lấp đầy xe rùa (Chuẩn bị dữ liệu cho 1 dòng quét)
    for(int i = 0; i < lcddev.width; i++)
    {
        line_buff[i*2] = color_high;
        line_buff[i*2+1] = color_low;
    }

    // 3. BẮN DỮ LIỆU NHANH (Bắn theo dòng)
    // Thay vì bắn 153.600 lần, ta chỉ bắn 480 lần (nếu màn dọc)
    for(index = 0; index < lcddev.height; index++)
    {
        // Gửi cả 1 dòng đi 1 lúc
        HAL_SPI_Transmit(&hspi2, line_buff, lcddev.width * 2, 100);
    }
    
    LCD_CS_SET;
} 

/*****************************************************************************
 * @name       :void LCD_Clear(u16 Color)
 * @date       :2018-08-09 
 * @function   :Initialization LCD screen GPIO
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCD_GPIOInit(void)
{
	/*
		    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOD_CLK_ENABLE();           //ʹ��GPIOFʱ��
    
    //PF6
    GPIO_Initure.Pin=GPIO_PIN_5| GPIO_PIN_6|GPIO_PIN_11| GPIO_PIN_12;            //PF6
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;     //����         
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);     //��ʼ��
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5| GPIO_PIN_6|GPIO_PIN_11|GPIO_PIN_12,GPIO_PIN_SET);
		LCD_LED(1);
	*/
}

/*****************************************************************************
 * @name       :void LCD_RESET(void)
 * @date       :2018-08-09 
 * @function   :Reset LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	
void LCD_RESET(void)
{
	LCD_RST_CLR;
	delay_ms(100);	
	LCD_RST_SET;
	delay_ms(50);
}

/*****************************************************************************
 * @name       :void LCD_RESET(void)
 * @date       :2018-08-09 
 * @function   :Initialization LCD screen
 * @parameters :None
 * @retvalue   :None
******************************************************************************/	 	 
void LCD_Init(void)
{  
	//SPI2_Init();		   			        //��ʼ��SPI
	//LCD_GPIOInit();//LCD GPIO��ʼ��										 
 	LCD_RESET(); //LCD ��λ
//*************4.0 ST7796S TN��ʼ��**********//	
	LCD_WR_REG(0xF0);
	LCD_WR_DATA(0xC3);
	LCD_WR_REG(0xF0);
	LCD_WR_DATA(0x96);
	LCD_WR_REG(0x36);
	LCD_WR_DATA(0x48);	
	LCD_WR_REG(0x3A);
	LCD_WR_DATA(0x05);	
	LCD_WR_REG(0xB0);
	LCD_WR_DATA(0x80);	
	LCD_WR_REG(0xB6);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x02);	
	LCD_WR_REG(0xB5);
	LCD_WR_DATA(0x02);
	LCD_WR_DATA(0x03);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x04);
	LCD_WR_REG(0xB1);
	LCD_WR_DATA(0x80);	
	LCD_WR_DATA(0x10);	
	LCD_WR_REG(0xB4);
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0xB7);
	LCD_WR_DATA(0xC6);
	LCD_WR_REG(0xC5);
	LCD_WR_DATA(0x1C);
	LCD_WR_REG(0xE4);
	LCD_WR_DATA(0x31);
	LCD_WR_REG(0xE8);
	LCD_WR_DATA(0x40);
	LCD_WR_DATA(0x8A);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x29);
	LCD_WR_DATA(0x19);
	LCD_WR_DATA(0xA5);
	LCD_WR_DATA(0x33);
	LCD_WR_REG(0xC2);
	LCD_WR_REG(0xA7);
	
	LCD_WR_REG(0xE0);
	LCD_WR_DATA(0xF0);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x13);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0x2B);
	LCD_WR_DATA(0x3C);
	LCD_WR_DATA(0x44);
	LCD_WR_DATA(0x4B);
	LCD_WR_DATA(0x1B);
	LCD_WR_DATA(0x18);
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x1D);
	LCD_WR_DATA(0x21);

	LCD_WR_REG(0XE1);
	LCD_WR_DATA(0xF0);
	LCD_WR_DATA(0x09);
	LCD_WR_DATA(0x13);
	LCD_WR_DATA(0x0C);
	LCD_WR_DATA(0x0D);
	LCD_WR_DATA(0x27);
	LCD_WR_DATA(0x3B);
	LCD_WR_DATA(0x44);
	LCD_WR_DATA(0x4D);
	LCD_WR_DATA(0x0B);
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x1D);
	LCD_WR_DATA(0x21);

	LCD_WR_REG(0xF0);
	LCD_WR_DATA(0x3C);
	LCD_WR_REG(0xF0);
	LCD_WR_DATA(0x69);
	LCD_WR_REG(0X13);
	LCD_WR_REG(0X11);
	LCD_WR_REG(0X29);
 

	//����LCD���Բ���
	LCD_direction(USE_HORIZONTAL);//����LCD��ʾ���� 
	LCD_Clear(WHITE);//��ȫ����ɫ
}
 
/*****************************************************************************
 * @name       :void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
 * @date       :2018-08-09 
 * @function   :Setting LCD display window
 * @parameters :xStar:the bebinning x coordinate of the LCD display window
								yStar:the bebinning y coordinate of the LCD display window
								xEnd:the endning x coordinate of the LCD display window
								yEnd:the endning y coordinate of the LCD display window
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd)
{	
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(0x00FF&xStar);		
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(0x00FF&xEnd);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(0x00FF&yStar);		
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(0x00FF&yEnd);

	LCD_WriteRAM_Prepare();	//��ʼд��GRAM			
}   

/*****************************************************************************
 * @name       :void LCD_SetCursor(u16 Xpos, u16 Ypos)
 * @date       :2018-08-09 
 * @function   :Set coordinate value
 * @parameters :Xpos:the  x coordinate of the pixel
								Ypos:the  y coordinate of the pixel
 * @retvalue   :None
******************************************************************************/ 
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{	  	    			
	LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);	
} 

/*****************************************************************************
 * @name       :void LCD_direction(u8 direction)
 * @date       :2018-08-09 
 * @function   :Setting the display direction of LCD screen
 * @parameters :direction:0-0 degree
                          1-90 degree
													2-180 degree
													3-270 degree
 * @retvalue   :None
******************************************************************************/ 
void LCD_direction(u8 direction)
{ 
	lcddev.setxcmd=0x2A;
	lcddev.setycmd=0x2B;
	lcddev.wramcmd=0x2C;
	lcddev.rramcmd=0x2E;
			lcddev.dir = direction%4;
	switch(lcddev.dir){		  
		case 0:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;		
			LCD_WriteReg(0x36,(1<<3)|(1<<6));
		break;
		case 1:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(1<<3)|(1<<5));
		break;
		case 2:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;	
			LCD_WriteReg(0x36,(1<<3)|(1<<7));
		break;
		case 3:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(1<<3)|(1<<7)|(1<<6)|(1<<5));
		break;	
		default:break;
	}		
}	 

u16 LCD_Read_ID(void)
{
	u8 i,val[3] = {0};
	LCD_WR_REG(0xF0);     // Command Set Control
	LCD_WR_DATA(0xC3);   

	LCD_WR_REG(0xF0);     
	LCD_WR_DATA(0x96);  
	LCD_CS_CLR;
	for(i=1;i<4;i++)
	{
		LCD_RS_CLR;	  
		SPI2_ReadWriteByte(0xFB);
		LCD_RS_SET;
		SPI2_ReadWriteByte(0x10+i);
		LCD_RS_CLR;	  
		SPI2_ReadWriteByte(0xD3);
		//SPI2_SetSpeed(SPI_BAUDRATEPRESCALER_32);
		LCD_RS_SET;
		val[i-1] = SPI2_ReadWriteByte(0xFF);
		LCD_RS_CLR;	  
		SPI2_ReadWriteByte(0xFB);
		LCD_RS_SET;
		SPI2_ReadWriteByte(0x00);	
	}
	//SPI2_SetSpeed(SPI_BAUDRATEPRESCALER_8);
	LCD_CS_SET;
	LCD_WR_REG(0xF0);     // Command Set Control
	LCD_WR_DATA(0x3C);   
	LCD_WR_REG(0xF0);     
	LCD_WR_DATA(0x69);  
	lcddev.id=val[1];
	lcddev.id<<=8;
	lcddev.id|=val[2];
	return lcddev.id;
}
/* USER CODE BEGIN 0 */

// Hàm vẽ ảnh 40x40 (Fix cứng theo code cũ của sếp)
void Gui_Drawbmp16(uint16_t x, uint16_t y, const unsigned char *p)
{
    int i;
    uint8_t temp_buff[2]; // Buffer tạm để đảo byte

    // 1. Set vùng hiển thị 40x40
    LCD_SetWindows(x, y, x + 40 - 1, y + 40 - 1);

    // 2. Chuẩn bị bắn dữ liệu
    LCD_CS_CLR;
    LCD_RS_SET; // Mode Data

    // 3. Vòng lặp bắn từng Pixel
    // Lưu ý: Mảng ảnh của sếp là "Low Byte First" (Byte thấp trước)
    // Nhưng màn hình LCD cần nhận "High Byte First" (Byte cao trước)
    // -> Nên ta phải tráo vị trí lúc bắn.
    for (i = 0; i < 40 * 40; i++)
    {
        temp_buff[0] = *(p + i * 2 + 1); // Lấy Byte cao (picH)
        temp_buff[1] = *(p + i * 2);     // Lấy Byte thấp (picL)
        
        // Bắn 2 byte màu này đi
        HAL_SPI_Transmit(&hspi2, temp_buff, 2, 10);
    }

    LCD_CS_SET; // Kết thúc gửi

    // 4. Trả lại vùng hiển thị toàn màn hình (như code cũ)
    // Sếp thay 240, 320 bằng kích thước thật màn hình sếp cấu hình
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
}

void Pic_test(void)
{
    // 1. Xóa màn hình trắng (Tùy sếp muốn hay không)
    LCD_Clear(WHITE);

    // 2. Vẽ 3 con chim cánh cụt
    Gui_Drawbmp16(30, 30, gImage_qq);
    
    // Show_Str(...); // Tạm thời bỏ qua hiển thị chữ
    
    Gui_Drawbmp16(90, 30, gImage_qq);
    
    // Show_Str(...); 
    
    Gui_Drawbmp16(150, 30, gImage_qq);
    
    // Show_Str(...);
    
    HAL_Delay(1200);
}

/* Hàm tô màu vùng hình chữ nhật (Dùng để vẽ điểm chạm) */
void LCD_Fill(u16 sx, u16 sy, u16 ex, u16 ey, u16 color)
{
    u16 i;
    u16 width = ex - sx + 1;
    u16 height = ey - sy + 1;
    
    // 1. Khoanh vùng cần vẽ
    LCD_SetWindows(sx, sy, ex, ey);
    
    // 2. Chuẩn bị Buffer (Xe rùa)
    // Tạo buffer đủ chứa 1 dòng ngang của vùng cần vẽ
    // Sếp lưu ý: Nếu vẽ vùng quá lớn > 480px ngang thì cần cẩn thận buffer này
    // Nhưng để vẽ điểm chạm (vài pixel) thì thoải mái.
    static uint8_t fill_buff[480 * 2]; 
    
    // Tách màu 16-bit thành 2 byte
    uint8_t h = color >> 8;
    uint8_t l = color & 0xFF;
    
    // Lấp đầy buffer 1 lần duy nhất
    for(i = 0; i < width; i++)
    {
        fill_buff[i*2] = h;
        fill_buff[i*2+1] = l;
    }

    LCD_CS_CLR;
    LCD_RS_SET;

    // 3. Bắn dữ liệu từng dòng
    for(i = 0; i < height; i++)
    {
        HAL_SPI_Transmit(&hspi2, fill_buff, width * 2, 100);
    }
    
    LCD_CS_SET;
    
    // 4. Trả lại vùng hiển thị full màn hình (để các hàm khác không bị ảnh hưởng)
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
}
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}

#define DMA_BUF_SIZE (480*2)
uint8_t lcd_dma_buffer[DMA_BUF_SIZE];
void LCD_Fill_DMA(u16 sx, u16 sy, u16 ex, u16 ey, u16 color)
{
    u32 total_pixels = (ex - sx + 1) * (ey - sy + 1);
    u32 bytes_per_pixel = 2;
    u32 total_bytes = total_pixels * bytes_per_pixel;
    
    // 1. Chuẩn bị dữ liệu cho Buffer (Lấp đầy 1 lần)
    u16 width_bytes = (ex - sx + 1) * 2;
    if(width_bytes > DMA_BUF_SIZE) width_bytes = DMA_BUF_SIZE; // Cắt nếu quá dài

    u8 h_color = color >> 8;
    u8 l_color = color & 0xFF;
    
    for(int i = 0; i < width_bytes; i += 2)
    {
        lcd_dma_buffer[i] = h_color;
        lcd_dma_buffer[i+1] = l_color;
    }

    // 2. Set vùng vẽ (Cursor)
    LCD_SetWindows(sx, sy, ex, ey);
    
    LCD_CS_CLR;
    LCD_RS_SET; // Gửi dữ liệu

    // 3. Xả Cache cho H7 (BẮT BUỘC - Nếu không màu sẽ bị sai hoặc nhiễu)
    // Lệnh này đẩy dữ liệu từ Cache xuống RAM thật để DMA lấy
    SCB_CleanDCache_by_Addr((uint32_t*)lcd_dma_buffer, width_bytes);

    // 4. Bắn DMA liên tục từng gói
    u32 bytes_sent = 0;
    while(bytes_sent < total_bytes)
    {
        u32 chunk_size = (total_bytes - bytes_sent);
        if(chunk_size > width_bytes) chunk_size = width_bytes; // Chỉ gửi tối đa kích thước buffer đã fill
        
        // Gọi hàm HAL DMA
        // &hspi1 hoặc &hspi2 tùy mạch sếp
        if(HAL_SPI_Transmit_DMA(&hspi2, lcd_dma_buffer, chunk_size) == HAL_OK)
        {
            // Chờ cho đến khi DMA bắn xong gói này (Blocking chờ cờ)
            // Lưu ý: Để tối ưu hơn thì dùng ngắt, nhưng ở mức đơn giản ta chờ ở đây
            // để đảm bảo CS không bị kéo lên sớm.
            while (HAL_SPI_GetState(&hspi2) != HAL_SPI_STATE_READY) {}
            
            bytes_sent += chunk_size;
        }
    }
    
    LCD_CS_SET;
    
    // Reset lại vùng window toàn màn hình
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
}
/* USER CODE END 0 */